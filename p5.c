#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

static int idata = 111;             /* Allocated in data segment */

int  main(int argc, char *argv[])
{
    int istack = 222;               /* Allocated in stack segment */
    pid_t childPid;

    childPid = fork();

    if (childPid == -1)
    {
        exit(-1);
    }
    else if (childPid == 0)
    {
        idata *= 3;
        istack *= 3;
    }           /* Child Process: modify data */
    else
    {
        sleep(3);
    } /* Parent process: give child a chance to execute */

    /* Both parent and child come here */
    printf("PID=%ld %s idata=%d istack=%d\n", (long) getpid(), (childPid == 0) ? "(child) " : "(parent)", idata, istack);

    exit(0);
}

