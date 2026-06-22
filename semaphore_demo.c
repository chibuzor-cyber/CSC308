3. Practical Session 3: Semaphore Implementation in C

Objective

Protect a shared counter using semaphores.

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define THREADS 5
#define ITERATIONS 100000

int counter = 0;
sem_t semaphore;

void *worker(void *arg)
{
    for(int i = 0; i < ITERATIONS; i++)
    {
        sem_wait(&semaphore);

        counter++;

        sem_post(&semaphore);
    }

    return NULL;
}

int main()
{
    pthread_t threads[THREADS];

    sem_init(&semaphore, 0, 1);

    for(int i = 0; i < THREADS; i++)
        pthread_create(&threads[i], NULL, worker, NULL);

    for(int i = 0; i < THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("Counter = %d\n", counter);

    sem_destroy(&semaphore);

    return 0;
}

COMPILE
gcc semaphore_demo.c -o semaphore_demo -pthread

Expected output
Counter = 500000