1. Practical Session 1: Mutex Lock Demonstration

Objective

Demonstrate mutual exclusion using POSIX mutex locks.

Concept

When multiple threads access the same variable simultaneously, a race condition occurs.

A mutex ensures only one thread accesses the shared resource at a time.


#include <stdio.h>
#include <pthread.h>

#define THREADS 5
#define INCREMENTS 100000

int counter = 0;
pthread_mutex_t mutex;

void *increment(void *arg)
{
    for(int i = 0; i < INCREMENTS; i++)
    {
        pthread_mutex_lock(&mutex);

        counter++;

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main()
{
    pthread_t threads[THREADS];

    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < THREADS; i++)
        pthread_create(&threads[i], NULL, increment, NULL);

    for(int i = 0; i < THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("Final Counter = %d\n", counter);

    pthread_mutex_destroy(&mutex);

    return 0;
}


COMPILE 
gcc mutex_demo.c -o mutex_demo -pthread

RUN
./mutex_demo

Expected output 
Final Counter = 500000