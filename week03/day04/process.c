#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int
main(int argc, char ** args)
{
    pid_t p = fork();
    printf("parent: %d, child: %d\n", getppid(), getpid());

    if(p == 0) {
        printf("This is Parrent %d\n", getpid());
    } else if(p > 0){
        printf("This is Parrent from child: %d, this is child: %d\n", getppid(), getpid());
        execv("/bin/ls", NULL);
    } else {
        printf("Faild fork\n");
    }

   return 0;
}
