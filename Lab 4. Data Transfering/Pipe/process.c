#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

// This method gets a string and then toggles it
void toggleCase(char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - 32;
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
        i++;
    }
}

int main()
{
    // Using two pips
    int filedes[2], nbytes;
    int outputs[2], onbytes;

    pid_t childpid;

    char readbuffer[80];
    char parrent_messages[4][50] = {
        "Hello",
        "How Are You",
        "Wake me up!",
        "Darlin, it was so nice to see you :)"
    };

    // Setting the pips
    pipe(filedes);
    pipe(outputs);

    if ((childpid = fork()) == -1)
    {
        perror("fork"); // Create a child
        exit(1);
    }

    if (childpid == 0)
    {
        // Child process
        close(filedes[0]);
        close(outputs[1]);

        for (int i = 0; i < 4; i++)
        {
            printf("Send: %s\n", parrent_messages[i]);
            write(filedes[1], parrent_messages[i], (strlen(parrent_messages[i]) + 1));
            
            char temp[80];
            onbytes = read(outputs[0], temp, sizeof(temp));

            temp[onbytes] = '\0';

            printf("Recive: %s\n", temp);
        }

        exit(0);
    }
    else
    {
        // Parent process
        close(filedes[1]);
        close(outputs[0]);

        for (int i = 0; i < 4; i++)
        {
            nbytes = read(filedes[0], readbuffer, sizeof(readbuffer));
            readbuffer[nbytes] = '\0';

            toggleCase(readbuffer);

            write(outputs[1], readbuffer, (strlen(readbuffer) + 1));

            readbuffer[0] = '\0';
        }
    }

    return (0);
}