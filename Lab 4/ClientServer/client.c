#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

// Amirhossein Najafizadeh 
// najafizadeh21@gmail.com

// Client:
//     In client we get host and port with a user name.
//     Then we create a socket to connect to the server.
//     If the connection was sucessfull user has this ability to communicate 
//     with other users.

// Commands:
//     join [group id]
//     leave [group id]
//     send [group id] [message]
//     quit


int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) // Check for socket creation
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    // sets all memory cells to zero
    memset(&serv_addr, '0', sizeof(serv_addr));

    // sets port and address family
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // connects to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Sending the user name
    send(sock, argv[3], strlen(argv[3]), 0);

    // User commands
    char command[50];

    while (1)
    {
        printf(">> ");
        gets(command);

        if (strcmp(command, "update") == 0) // We create the buffer with the update command
        { 
            valread = read(sock, buffer, 1024);
            printf("%s\n", buffer);
            continue; // This will read all of the user messages from the server
        }

        // Sending messages to the server
        send(sock, command, strlen(command), 0);

        if (strcmp(command, "quit") == 0) // We check for user quitting the program
        {
            break;
        }

        valread = read(sock, buffer, 1024);

        if (valread < 0) // Check if the reading was successfull
        {
            perror("read");
            return -1;
        }

        printf("<< %s\n", buffer);
    }

    return 0;
}