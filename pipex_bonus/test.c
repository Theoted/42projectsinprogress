#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void fork_test()
{
    pid_t pid;

    pid = fork();
    if (!pid)
    {
        printf("Child\n");
    }
    else
    {
        waitpid(pid, NULL, 0);
        printf("Parent\n");
    }
}

int main()
{
    fork_test();
    return (0);
}