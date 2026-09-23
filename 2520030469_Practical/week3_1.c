#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  
#include <sys/wait.h>   

int main(){
    int pid;
    printf("Start of parent\n");
    pid = fork();
    if(pid==0){
    sleep(15);
    exit(0);
    printf("end of child\n");
    }
    else{
        sleep(10);
        wait(NULL);
        printf("End of parent\n");
    }
    return 0;

}