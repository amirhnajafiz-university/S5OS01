#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define TIMER 2
#define PHILOSOPHER 5

pthread_t philosophers[PHILOSOPHER];
pthread_mutex_t chopstick[PHILOSOPHER];

void eating(int id)
{
    printf("\nPhilosopher %d is hungry !", id);

    pthread_mutex_lock(&chopstick[id]);
    pthread_mutex_lock(&chopstick[(id + 1) % PHILOSOPHER]);

    printf("\nPhilosopher %d is eating using chopstick[%d] and chopstrick[%d] !!", id, id, (id + 1) % PHILOSOPHER);
    printf("\nPhilosopher %d is done !", id);

    pthread_mutex_unlock(&chopstick[id]);
    pthread_mutex_unlock(&chopstick[id + 1 % PHILOSOPHER]);

    sleep(1);
}

void thinking(int id)
{
    printf("\nPhilosopher %d is thinking !!", id);
    sleep(2);
}

void* philosopher(void* vargp)
{
    int* temp = (int *)vargp;
    int id = *temp;
    int i = 0;

    while (i < TIMER)
    {
        thinking(id);
        eating(id);
        i++;
    }
}

int main()
{
    for (int i = 0; i < PHILOSOPHER; i++)
        pthread_create(&philosophers[i], NULL, philosopher, (void *)&i);

    for (int i = 0; i < PHILOSOPHER; i++)
        pthread_join(philosophers[i], NULL);
}