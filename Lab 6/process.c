#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define LIMIT 10
#define THREADS 5

int buffer = 0;
pthread_mutex_t lock;

void *reader(void *vargp)
{
    int* temp = (int *)vargp;
    int id = *temp;

    while (1)
    {
        if (buffer >= LIMIT)
            break;
        
        pthread_mutex_lock(&lock);

        printf("\nPID Reader:%d -> %d", id, buffer);

        pthread_mutex_unlock(&lock);

        sleep(1);
    }
}

void *writer(void *vargp)
{
    int* temp = (int *)vargp;
    int id = *temp;

    while (1)
    {
        if (buffer >= LIMIT)
            break;

        pthread_mutex_lock(&lock);
        
        buffer++;
        printf("\nPID Writer:%d -> %d", id, buffer);

        pthread_mutex_unlock(&lock);

        sleep(1);
    }
    
}

int main()
{
    srand(time(NULL));

    pthread_t tid[THREADS];
    int chance;

    for (int i = 0; i < THREADS; i++) {
        chance = rand() % 2;
        if (chance == 1)
            pthread_create(&tid[i], NULL, writer, (void *)&tid[i]);
        else 
            pthread_create(&tid[i], NULL, reader, (void *)&tid[i]);
    }

    for (int i = 0; i < THREADS; i++)
        pthread_join(tid[i], NULL);
}