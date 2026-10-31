#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <errno.h>


/* =========================================================
   CONSTANTS
   ========================================================= */

#define SOURCE_DIR "source"
#define BACKUP_DIR "backup"
#define LOG_FILE "backup_log.txt"
#define LOCK_FILE ".backup.lock"

#define BUFFER_SIZE 4096


/* =========================================================
   STRUCTURE FOR SYNCHRONIZATION STATISTICS
   ========================================================= */

typedef struct {

    int new_files;
    int modified_files;
    int deleted_files;
    int unchanged_files;
    int errors;

} SyncStats;


/* =========================================================
   GLOBAL VARIABLE FOR AUTOMATIC BACKUP
   ========================================================= */

volatile sig_atomic_t auto_backup_running = 1;


/* =========================================================
   FUNCTION DECLARATIONS
   ========================================================= */

void write_log(const char *message);

int acquire_lock();

void release_lock(int lock_fd);

int copy_file(const char *source_path,
              const char *backup_path);

int files_are_same(const char *source_path,
                   const char *backup_path);

int synchronize_files(SyncStats *stats,
                      int verbose);

void display_source_files();

void display_backup_files();

void display_file_information();

void display_log();

void display_statistics();

void print_sync_summary(SyncStats *stats);

void automatic_backup_handler(int signal_number);

void automatic_backup_process(int interval);

void manual_synchronization();

void start_automatic_backup(pid_t *auto_pid);

void stop_automatic_backup(pid_t *auto_pid);


/* =========================================================
   WRITE TIMESTAMPED LOG
   ========================================================= */

void write_log(const char *message)
{
    int fd;

    char log_entry[512];
    char timestamp[64];

    time_t current_time;
    struct tm *time_info;


    current_time = time(NULL);

    time_info = localtime(&current_time);


    if (time_info == NULL) {

        return;
    }


    strftime(timestamp,
             sizeof(timestamp),
             "%Y-%m-%d %H:%M:%S",
             time_info);


    snprintf(log_entry,
             sizeof(log_entry),
             "[%s] %s\n",
             timestamp,
             message);


    fd = open(LOG_FILE,
              O_WRONLY | O_CREAT | O_APPEND,
              0644);


    if (fd == -1) {

        perror("Error opening activity log");
        return;
    }


    if (write(fd,
              log_entry,
              strlen(log_entry)) == -1) {

        perror("Error writing activity log");
    }


    close(fd);
}


/* =========================================================
   ACQUIRE FILE LOCK
   ========================================================= */

int acquire_lock()
{
    int lock_fd;


    lock_fd = open(LOCK_FILE,
                   O_WRONLY | O_CREAT,
                   0644);


    if (lock_fd == -1) {

        perror("Error opening lock file");

        return -1;
    }


    /*
       LOCK_EX  = exclusive lock
       LOCK_NB  = do not wait if already locked
    */

    if (flock(lock_fd,
              LOCK_EX | LOCK_NB) == -1) {

        if (errno == EWOULDBLOCK) {

            printf("\nAnother backup process is currently running.\n");

        }

        else {

            perror("Error acquiring file lock");
        }


        close(lock_fd);

        return -1;
    }


    return lock_fd;
}


/* =========================================================
   RELEASE FILE LOCK
   ========================================================= */

void release_lock(int lock_fd)
{
    if (lock_fd >= 0) {

        flock(lock_fd, LOCK_UN);

        close(lock_fd);
    }
}


/* =========================================================
   COPY FILE USING SYSTEM CALLS
   ========================================================= */

int copy_file(const char *source_path,
              const char *backup_path)
{
    int source_fd;
    int backup_fd;

    char buffer[BUFFER_SIZE];

    ssize_t bytes_read;
    ssize_t bytes_written;


    source_fd = open(source_path,
                     O_RDONLY);


    if (source_fd == -1) {

        perror("Error opening source file");

        return -1;
    }


    backup_fd = open(backup_path,
                     O_WRONLY |
                     O_CREAT |
                     O_TRUNC,
                     0644);


    if (backup_fd == -1) {

        perror("Error creating backup file");

        close(source_fd);

        return -1;
    }


    while ((bytes_read =
            read(source_fd,
                 buffer,
                 sizeof(buffer))) > 0) {


        bytes_written =
            write(backup_fd,
                  buffer,
                  bytes_read);


        if (bytes_written != bytes_read) {

            perror("Error writing backup file");

            close(source_fd);
            close(backup_fd);

            return -1;
        }
    }


    if (bytes_read < 0) {

        perror("Error reading source file");

        close(source_fd);
        close(backup_fd);

        return -1;
    }


    close(source_fd);
    close(backup_fd);


    return 0;
}


/* =========================================================
   COMPARE TWO FILES
   ========================================================= */

int files_are_same(const char *source_path,
                   const char *backup_path)
{
    int source_fd;
    int backup_fd;

    char source_buffer[BUFFER_SIZE];
    char backup_buffer[BUFFER_SIZE];

    ssize_t source_bytes;
    ssize_t backup_bytes;

    struct stat source_info;
    struct stat backup_info;


    /*
       First compare file sizes.
       If sizes are different, files are definitely different.
    */

    if (stat(source_path,
             &source_info) == -1) {

        return 0;
    }


    if (stat(backup_path,
             &backup_info) == -1) {

        return 0;
    }


    if (source_info.st_size !=
        backup_info.st_size) {

        return 0;
    }


    source_fd = open(source_path,
                     O_RDONLY);


    if (source_fd == -1) {

        return 0;
    }


    backup_fd = open(backup_path,
                     O_RDONLY);


    if (backup_fd == -1) {

        close(source_fd);

        return 0;
    }


    /*
       Compare actual file contents.
    */

    while (1) {

        source_bytes =
            read(source_fd,
                 source_buffer,
                 sizeof(source_buffer));


        backup_bytes =
            read(backup_fd,
                 backup_buffer,
                 sizeof(backup_buffer));


        if (source_bytes !=
            backup_bytes) {

            close(source_fd);
            close(backup_fd);

            return 0;
        }


        if (source_bytes == 0) {

            break;
        }


        if (memcmp(source_buffer,
                   backup_buffer,
                   source_bytes) != 0) {

            close(source_fd);
            close(backup_fd);

            return 0;
        }
    }


    close(source_fd);
    close(backup_fd);


    return 1;
}


/* =========================================================
   SYNCHRONIZE FILES
   ========================================================= */

int synchronize_files(SyncStats *stats,
                      int verbose)
{
    DIR *source_dir;
    DIR *backup_dir;

    struct dirent *entry;
    struct dirent *backup_entry;

    struct stat source_info;
    struct stat backup_info;

    char source_path[512];
    char backup_path[512];

    char log_message[512];

    int lock_fd;


    /*
       Initialize statistics.
    */

    stats->new_files = 0;
    stats->modified_files = 0;
    stats->deleted_files = 0;
    stats->unchanged_files = 0;
    stats->errors = 0;


    /*
       Acquire exclusive lock.
       This prevents two backup operations from
       modifying the backup directory simultaneously.
    */

    lock_fd = acquire_lock();


    if (lock_fd == -1) {

        stats->errors++;

        return -1;
    }


    /*
       Open source directory.
    */

    source_dir =
        opendir(SOURCE_DIR);


    if (source_dir == NULL) {

        perror("Error opening source directory");

        release_lock(lock_fd);

        stats->errors++;

        return -1;
    }


    if (verbose) {

        printf("\n----------------------------------------\n");
        printf("Starting synchronization\n");
        printf("----------------------------------------\n");
    }


    /* =====================================================
       CHECK SOURCE FILES
       ===================================================== */

    while ((entry =
            readdir(source_dir)) != NULL) {


        /*
           Ignore . and ..
        */

        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {

            continue;
        }


        snprintf(source_path,
                 sizeof(source_path),
                 "%s/%s",
                 SOURCE_DIR,
                 entry->d_name);


        snprintf(backup_path,
                 sizeof(backup_path),
                 "%s/%s",
                 BACKUP_DIR,
                 entry->d_name);


        /*
           Get source file information.
        */

        if (stat(source_path,
                 &source_info) == -1) {

            stats->errors++;

            continue;
        }


        /*
           Only process regular files.
        */

        if (!S_ISREG(source_info.st_mode)) {

            continue;
        }


        /*
           Check whether backup exists.
        */

        if (stat(backup_path,
                 &backup_info) == -1) {


            /*
               NEW FILE
            */

            if (errno == ENOENT) {

                if (verbose) {

                    printf("[NEW] %s\n",
                           entry->d_name);
                }


                if (copy_file(source_path,
                              backup_path) == 0) {

                    stats->new_files++;


                    snprintf(log_message,
                             sizeof(log_message),
                             "[BACKUP] New file created: %s",
                             entry->d_name);


                    write_log(log_message);
                }

                else {

                    stats->errors++;
                }
            }

            else {

                stats->errors++;
            }
        }


        else {


            /*
               EXISTING FILE
            */

            if (files_are_same(source_path,
                               backup_path)) {


                /*
                   FILE IS UNCHANGED
                */

                stats->unchanged_files++;


                if (verbose) {

                    printf("[UNCHANGED] %s\n",
                           entry->d_name);
                }
            }


            else {


                /*
                   FILE WAS MODIFIED
                */

                if (verbose) {

                    printf("[MODIFIED] %s\n",
                           entry->d_name);
                }


                if (copy_file(source_path,
                              backup_path) == 0) {

                    stats->modified_files++;


                    snprintf(log_message,
                             sizeof(log_message),
                             "[UPDATE] Modified file backed up: %s",
                             entry->d_name);


                    write_log(log_message);
                }

                else {

                    stats->errors++;
                }
            }
        }
    }


    closedir(source_dir);


    /* =====================================================
       CHECK FOR DELETED FILES
       ===================================================== */

    backup_dir =
        opendir(BACKUP_DIR);


    if (backup_dir != NULL) {


        while ((backup_entry =
                readdir(backup_dir)) != NULL) {


            if (strcmp(backup_entry->d_name, ".") == 0 ||
                strcmp(backup_entry->d_name, "..") == 0) {

                continue;
            }


            snprintf(source_path,
                     sizeof(source_path),
                     "%s/%s",
                     SOURCE_DIR,
                     backup_entry->d_name);


            snprintf(backup_path,
                     sizeof(backup_path),
                     "%s/%s",
                     BACKUP_DIR,
                     backup_entry->d_name);


            /*
               Check whether source file still exists.
            */

            if (access(source_path,
                       F_OK) == -1) {


                if (errno == ENOENT) {


                    if (verbose) {

                        printf("[DELETED] %s\n",
                               backup_entry->d_name);
                    }


                    if (unlink(backup_path) == 0) {

                        stats->deleted_files++;


                        snprintf(log_message,
                                 sizeof(log_message),
                                 "[DELETE] Backup removed: %s",
                                 backup_entry->d_name);


                        write_log(log_message);
                    }

                    else {

                        perror("Error deleting backup file");

                        stats->errors++;
                    }
                }
            }
        }


        closedir(backup_dir);
    }


    else {

        stats->errors++;
    }


    release_lock(lock_fd);


    if (verbose) {

        printf("----------------------------------------\n");
        printf("Synchronization completed\n");
        printf("----------------------------------------\n");
    }


    return 0;
}


/* =========================================================
   PRINT SYNCHRONIZATION SUMMARY
   ========================================================= */

void print_sync_summary(SyncStats *stats)
{
    printf("\n");
    printf("========================================\n");
    printf("      SYNCHRONIZATION SUMMARY\n");
    printf("========================================\n");

    printf("New files       : %d\n",
           stats->new_files);

    printf("Modified files  : %d\n",
           stats->modified_files);

    printf("Deleted files   : %d\n",
           stats->deleted_files);

    printf("Unchanged files : %d\n",
           stats->unchanged_files);

    printf("Errors          : %d\n",
           stats->errors);

    printf("========================================\n");
}


/* =========================================================
   MANUAL SYNCHRONIZATION
   ========================================================= */

void manual_synchronization()
{
    pid_t pid;

    int pipe_fd[2];

    SyncStats stats;

    ssize_t bytes_read;


    /*
       Create pipe for parent-child communication.
    */

    if (pipe(pipe_fd) == -1) {

        perror("pipe failed");

        return;
    }


    printf("\nStarting backup process...\n");


    /*
       Create child process.
    */

    pid = fork();


    if (pid < 0) {

        perror("fork failed");

        close(pipe_fd[0]);
        close(pipe_fd[1]);

        return;
    }


    /* =====================================================
       CHILD PROCESS
       ===================================================== */

    if (pid == 0) {

        close(pipe_fd[0]);


        printf("\nChild Process PID: %d\n",
               getpid());


        printf("Child: Performing synchronization...\n");


        synchronize_files(&stats, 1);


        /*
           Send statistics to parent through pipe.
        */

        write(pipe_fd[1],
              &stats,
              sizeof(stats));


        close(pipe_fd[1]);


        printf("Child: Synchronization finished.\n");


        exit(0);
    }


    /* =====================================================
       PARENT PROCESS
       ===================================================== */

    else {

        close(pipe_fd[1]);


        printf("Parent Process PID: %d\n",
               getpid());


        printf("Parent: Waiting for child process...\n");


        waitpid(pid,
                NULL,
                0);


        /*
           Receive statistics from child.
        */

        bytes_read =
            read(pipe_fd[0],
                 &stats,
                 sizeof(stats));


        close(pipe_fd[0]);


        if (bytes_read ==
            sizeof(stats)) {

            print_sync_summary(&stats);
        }


        printf("Parent: Backup process completed.\n");
    }
}


/* =========================================================
   DISPLAY SOURCE FILES
   ========================================================= */

void display_source_files()
{
    DIR *dir;

    struct dirent *entry;

    struct stat file_info;


    dir = opendir(SOURCE_DIR);


    if (dir == NULL) {

        perror("Error opening source directory");

        return;
    }


    printf("\n");
    printf("========================================\n");
    printf("             SOURCE FILES\n");
    printf("========================================\n");


    while ((entry =
            readdir(dir)) != NULL) {


        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {

            continue;
        }


        char path[512];


        snprintf(path,
                 sizeof(path),
                 "%s/%s",
                 SOURCE_DIR,
                 entry->d_name);


        if (stat(path,
                 &file_info) == 0 &&
            S_ISREG(file_info.st_mode)) {

            printf("%s\n",
                   entry->d_name);
        }
    }


    printf("========================================\n");


    closedir(dir);
}


/* =========================================================
   DISPLAY BACKUP FILES
   ========================================================= */

void display_backup_files()
{
    DIR *dir;

    struct dirent *entry;

    struct stat file_info;


    dir = opendir(BACKUP_DIR);


    if (dir == NULL) {

        perror("Error opening backup directory");

        return;
    }


    printf("\n");
    printf("========================================\n");
    printf("             BACKUP FILES\n");
    printf("========================================\n");


    while ((entry =
            readdir(dir)) != NULL) {


        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {

            continue;
        }


        char path[512];


        snprintf(path,
                 sizeof(path),
                 "%s/%s",
                 BACKUP_DIR,
                 entry->d_name);


        if (stat(path,
                 &file_info) == 0 &&
            S_ISREG(file_info.st_mode)) {

            printf("%s\n",
                   entry->d_name);
        }
    }


    printf("========================================\n");


    closedir(dir);
}


/* =========================================================
   DISPLAY FILE INFORMATION
   ========================================================= */

void display_file_information()
{
    char filename[256];

    char path[512];

    struct stat file_info;

    char time_buffer[64];

    struct tm *time_info;


    printf("\nEnter file name: ");

    scanf("%255s",
          filename);


    snprintf(path,
             sizeof(path),
             "%s/%s",
             SOURCE_DIR,
             filename);


    if (stat(path,
             &file_info) == -1) {

        perror("Error getting file information");

        return;
    }


    time_info =
        localtime(&file_info.st_mtime);


    if (time_info != NULL) {

        strftime(time_buffer,
                 sizeof(time_buffer),
                 "%Y-%m-%d %H:%M:%S",
                 time_info);
    }

    else {

        strcpy(time_buffer,
               "Unknown");
    }


    printf("\n");
    printf("========================================\n");
    printf("            FILE INFORMATION\n");
    printf("========================================\n");

    printf("File Name        : %s\n",
           filename);

    printf("File Size        : %ld bytes\n",
           (long)file_info.st_size);

    printf("File Permissions : %o\n",
           file_info.st_mode & 0777);

    printf("Last Modified    : %s\n",
           time_buffer);

    printf("Inode Number     : %ld\n",
           (long)file_info.st_ino);

    printf("========================================\n");
}


/* =========================================================
   DISPLAY ACTIVITY LOG
   ========================================================= */

void display_log()
{
    int fd;

    char buffer[1024];

    ssize_t bytes_read;


    fd = open(LOG_FILE,
              O_RDONLY);


    if (fd == -1) {

        printf("\nNo backup activity recorded yet.\n");

        return;
    }


    printf("\n");
    printf("========================================\n");
    printf("           BACKUP ACTIVITY LOG\n");
    printf("========================================\n");


    while ((bytes_read =
            read(fd,
                 buffer,
                 sizeof(buffer) - 1)) > 0) {


        buffer[bytes_read] = '\0';


        printf("%s",
               buffer);
    }


    printf("========================================\n");


    close(fd);
}


/* =========================================================
   DISPLAY ACCURATE BACKUP STATISTICS
   ========================================================= */

void display_statistics()
{
    DIR *source_dir;
    DIR *backup_dir;

    struct dirent *entry;

    struct stat source_info;
    struct stat backup_info;

    char source_path[512];
    char backup_path[512];

    int source_count = 0;
    int backup_count = 0;

    int matching_count = 0;
    int new_count = 0;
    int modified_count = 0;
    int deleted_count = 0;


    /* =====================================================
       COUNT SOURCE FILES AND COMPARE WITH BACKUP
       ===================================================== */

    source_dir =
        opendir(SOURCE_DIR);


    if (source_dir != NULL) {


        while ((entry =
                readdir(source_dir)) != NULL) {


            if (strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0) {

                continue;
            }


            snprintf(source_path,
                     sizeof(source_path),
                     "%s/%s",
                     SOURCE_DIR,
                     entry->d_name);


            snprintf(backup_path,
                     sizeof(backup_path),
                     "%s/%s",
                     BACKUP_DIR,
                     entry->d_name);


            if (stat(source_path,
                     &source_info) != 0) {

                continue;
            }


            if (!S_ISREG(source_info.st_mode)) {

                continue;
            }


            source_count++;


            /*
               Backup does not exist.
            */

            if (stat(backup_path,
                     &backup_info) == -1) {

                new_count++;

                continue;
            }


            /*
               Compare actual contents.
            */

            if (files_are_same(source_path,
                               backup_path)) {

                matching_count++;
            }

            else {

                modified_count++;
            }
        }


        closedir(source_dir);
    }


    /* =====================================================
       COUNT BACKUP FILES
       ===================================================== */

    backup_dir =
        opendir(BACKUP_DIR);


    if (backup_dir != NULL) {


        while ((entry =
                readdir(backup_dir)) != NULL) {


            if (strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0) {

                continue;
            }


            snprintf(backup_path,
                     sizeof(backup_path),
                     "%s/%s",
                     BACKUP_DIR,
                     entry->d_name);


            if (stat(backup_path,
                     &backup_info) != 0) {

                continue;
            }


            if (!S_ISREG(backup_info.st_mode)) {

                continue;
            }


            backup_count++;


            snprintf(source_path,
                     sizeof(source_path),
                     "%s/%s",
                     SOURCE_DIR,
                     entry->d_name);


            /*
               Backup exists but source does not.
            */

            if (access(source_path,
                       F_OK) == -1) {

                if (errno == ENOENT) {

                    deleted_count++;
                }
            }
        }


        closedir(backup_dir);
    }


    printf("\n");
    printf("========================================\n");
    printf("          BACKUP STATISTICS\n");
    printf("========================================\n");

    printf("Files in source      : %d\n",
           source_count);

    printf("Files in backup      : %d\n",
           backup_count);

    printf("Matching files       : %d\n",
           matching_count);

    printf("New files            : %d\n",
           new_count);

    printf("Modified files       : %d\n",
           modified_count);

    printf("Deleted files        : %d\n",
           deleted_count);

    printf("----------------------------------------\n");


    if (new_count == 0 &&
        modified_count == 0 &&
        deleted_count == 0 &&
        source_count == backup_count) {

        printf("Synchronization      : COMPLETE\n");
    }

    else {

        printf("Synchronization      : REQUIRED\n");
    }


    printf("========================================\n");
}


/* =========================================================
   SIGNAL HANDLER FOR AUTOMATIC BACKUP
   ========================================================= */

void automatic_backup_handler(int signal_number)
{
    if (signal_number == SIGTERM) {

        auto_backup_running = 0;
    }
}


/* =========================================================
   AUTOMATIC BACKUP PROCESS
   ========================================================= */

void automatic_backup_process(int interval)
{
    SyncStats stats;


    /*
       Register SIGTERM handler.
    */

    signal(SIGTERM,
           automatic_backup_handler);


    printf("\nAutomatic backup process started.\n");

    printf("Automatic Process PID: %d\n",
           getpid());


    while (auto_backup_running) {


        /*
           Perform synchronization.
        */

        synchronize_files(&stats, 1);


        /*
           Wait before next scan.
        */

        for (int i = 0;
             i < interval && auto_backup_running;
             i++) {

            sleep(1);
        }
    }


    printf("\nAutomatic backup process stopped.\n");


    exit(0);
}


/* =========================================================
   START AUTOMATIC BACKUP
   ========================================================= */

void start_automatic_backup(pid_t *auto_pid)
{
    int interval;

    pid_t pid;


    if (*auto_pid != -1) {

        printf("\nAutomatic backup is already running.\n");

        printf("Process PID: %d\n",
               *auto_pid);

        return;
    }


    printf("\nEnter synchronization interval in seconds: ");

    scanf("%d",
          &interval);


    if (interval < 1) {

        printf("Invalid interval.\n");

        return;
    }


    pid = fork();


    if (pid < 0) {

        perror("fork failed");

        return;
    }


    if (pid == 0) {

        automatic_backup_process(interval);
    }


    else {

        *auto_pid = pid;


        printf("\nAutomatic backup started successfully.\n");

        printf("Background Process PID: %d\n",
               pid);

        printf("Synchronization interval: %d seconds\n",
               interval);
    }
}


/* =========================================================
   STOP AUTOMATIC BACKUP
   ========================================================= */

void stop_automatic_backup(pid_t *auto_pid)
{
    if (*auto_pid == -1) {

        printf("\nAutomatic backup is not running.\n");

        return;
    }


    printf("\nStopping automatic backup process...\n");


    if (kill(*auto_pid,
             SIGTERM) == -1) {

        perror("Error stopping automatic backup");

        *auto_pid = -1;

        return;
    }


    waitpid(*auto_pid,
            NULL,
            0);


    printf("Automatic backup stopped successfully.\n");


    *auto_pid = -1;
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */

int main()
{
    int choice;

    pid_t auto_pid = -1;


    /*
       Create required directories if they do not exist.
    */

    mkdir(SOURCE_DIR,
          0755);

    mkdir(BACKUP_DIR,
          0755);


    while (1) {


        printf("\n\n");

        printf("============================================\n");
        printf("       LINUX FILE BACKUP & SYNC SYSTEM\n");
        printf("============================================\n");

        printf("1.  Manual Synchronization\n");
        printf("2.  Start Automatic Backup\n");
        printf("3.  Stop Automatic Backup\n");
        printf("4.  View Source Files\n");
        printf("5.  View Backup Files\n");
        printf("6.  View File Information\n");
        printf("7.  View Activity Log\n");
        printf("8.  Backup Statistics\n");
        printf("9.  Exit\n");

        printf("============================================\n");


        if (auto_pid != -1) {

            printf("Automatic Backup Status: RUNNING (PID %d)\n",
                   auto_pid);
        }

        else {

            printf("Automatic Backup Status: STOPPED\n");
        }


        printf("============================================\n");


        printf("Enter your choice: ");

        scanf("%d",
              &choice);


        /* =================================================
           OPTION 1
           MANUAL SYNCHRONIZATION
           ================================================= */

        if (choice == 1) {

            manual_synchronization();
        }


        /* =================================================
           OPTION 2
           START AUTOMATIC BACKUP
           ================================================= */

        else if (choice == 2) {

            start_automatic_backup(&auto_pid);
        }


        /* =================================================
           OPTION 3
           STOP AUTOMATIC BACKUP
           ================================================= */

        else if (choice == 3) {

            stop_automatic_backup(&auto_pid);
        }


        /* =================================================
           OPTION 4
           SOURCE FILES
           ================================================= */

        else if (choice == 4) {

            display_source_files();
        }


        /* =================================================
           OPTION 5
           BACKUP FILES
           ================================================= */

        else if (choice == 5) {

            display_backup_files();
        }


        /* =================================================
           OPTION 6
           FILE INFORMATION
           ================================================= */

        else if (choice == 6) {

            display_file_information();
        }


        /* =================================================
           OPTION 7
           ACTIVITY LOG
           ================================================= */

        else if (choice == 7) {

            display_log();
        }


        /* =================================================
           OPTION 8
           STATISTICS
           ================================================= */

        else if (choice == 8) {

            display_statistics();
        }


        /* =================================================
           OPTION 9
           EXIT
           ================================================= */

        else if (choice == 9) {


            /*
               Stop automatic backup before exiting.
            */

            if (auto_pid != -1) {

                stop_automatic_backup(&auto_pid);
            }


            printf("\nExiting Linux Backup System...\n");

            printf("Goodbye!\n");


            break;
        }


        /* =================================================
           INVALID OPTION
           ================================================= */

        else {

            printf("\nInvalid choice! Please try again.\n");
        }
    }


    return 0;
}
