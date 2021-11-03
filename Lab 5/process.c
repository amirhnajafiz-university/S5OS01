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

#define FORKS 1000 // Maximum

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

int main(int argc, char *argv[])
{
    int ORDER = atoi(argv[1]);

    clock_t begin = clock();

    int hist[25];

    for (int i = 0; i < 25; i++)
    {
        hist[i] = 0;
    }

    pid_t pid;

    int fd[2];

    for (int i = 0; i < FORKS; i++)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe failed");
            continue;
        }

        pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0)
        {
            srand(time(NULL) ^ getpid());

            char buff[50];
            close(fd[0]);

            for (int k = 0; k < ORDER / FORKS; k++)
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

                sprintf(buff, "%d", counter);
                write(fd[1], buff, strlen(buff) + 1);
            }

            exit(0);
        }
        else
        {
            char buff[50];
            close(fd[1]);

            for (int k = 0; k < ORDER / FORKS; k++)
            {
                read(fd[0], buff, sizeof(buff));
                int counter = atoi(buff);

                hist[counter + 12]++;
            }
        }
    }

    // printHistogram(hist);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Time: %f seconds\n", time_spent);
    return 0;
}