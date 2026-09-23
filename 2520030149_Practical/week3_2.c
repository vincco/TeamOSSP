#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  
#include <sys/wait.h> 
#include <sys/types.h>

int main(){
    int num;
    pid_t pid;
    long long factorial=1;
    printf("enter a numder: ");
    scanf("%d", &num);
    pid=fork();
    if(pid<0){
        printf("fork failed\n");
        return 1;

    }
    else if(pid==0){
        printf("\n--- Child Process ---\n");
    }
}