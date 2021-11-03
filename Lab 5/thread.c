#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

int hist[25];

void printHistogram(int *hist)
{
    for (int i = 0; i < 25; i++)
    {
        printf("> ");
        for (int j = 0; j < hist[i]; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

void *compute(void *vargp)
{
    int counter = 0;
    for (int j = 0; j < 12; j++)
    {
        int r = rand() % 101;
        if (r >= 49)
        {
            counter++;
            counter = fmin(counter, 12);
        }
        else
        {
            counter--;
            counter = fmax(counter, -12);
        }
    }
    hist[counter + 12]++;
}

int main(int argc, char *argv[])
{
    int ORDER = atoi(argv[1]);

    clock_t begin = clock();
    srand(time(NULL));

    for (int i = 0; i < 25; i++)
    {
        hist[i] = 0;
    }

    for (int i = 0; i < ORDER; i++)
    {
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, compute, NULL);
    }

    // printHistogram(hist);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Time: %f seconds\n", time_spent);
    return 0;
}