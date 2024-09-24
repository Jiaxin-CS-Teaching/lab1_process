#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
        //close default output (terminal)
    close(STDOUT_FILENO);
    int fd;
    //open new file + error handler
    if ((fd = open("./p8.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU)) < 0){
        perror("open file failed!\n");
        exit(1);
    }
    //create a child process
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        //child write
        char array1[] = "hello world from child!\n";
        if(write(fd, array1, sizeof(array1)) < 0){
            perror("child write failed!\n");
            exit(1);
        }
    } else {
        //parent write
        char array2[] = "hello world from parent!\n";
        if(write(fd, array2, sizeof(array2)) < 0){
            perror("parent write failed!\n");
            exit(1);
        }
        wait(NULL);
    }
    return 0;
}