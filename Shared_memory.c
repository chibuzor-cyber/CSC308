4. Practical Session 4: Shared Memory Programming

Objective

Implement Inter-Process Communication (IPC) using Shared Memory.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main()
{
    int shmid;

    char *shared_memory;

    shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0666);

    if(shmid < 0)
    {
        perror("shmget");
        exit(1);
    }

    pid_t pid = fork();

    if(pid == 0)
    {
        shared_memory = (char *)shmat(shmid, NULL, 0);

        strcpy(shared_memory,
               "Hello from Child Process!");

        shmdt(shared_memory);

        exit(0);
    }
    else
    {
        wait(NULL);

        shared_memory = (char *)shmat(shmid, NULL, 0);

        printf("Parent Read: %s\n",
               shared_memory);

        shmdt(shared_memory);

        shmctl(shmid,
               IPC_RMID,
               NULL);
    }

    return 0;
}

COMPILE
gcc shared_memory.c -o shared_memory

Expected output
Parent Read: Hello from Child Process!