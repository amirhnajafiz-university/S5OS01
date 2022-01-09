#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

// Amirhossein Najafizadeh 
// najafizadeh21@gmail.com

// Server:
//     In server we get the server port to setup our server.
//     Then we create a socket to connect to listen to clients.
//     For each client, we use a thread to have Multi-Client Server.
//     Each user will be handled in handleClient funtion.

#define GCAPACITY 20 // Groups capacity
#define CCAPACITY 20 // Users capacity of each group

// Each group is a struct
struct group
{
    int id;
    int clients[CCAPACITY]; // Clients socket ids
    char names[CCAPACITY][50]; // Clients names
    int useable[CCAPACITY]; // Array availalbe
};

// List of groups
struct group groups[GCAPACITY];

// This method will split a string into parts based on the space.
char* split_input(int part, char buffer[1024]) 
{
    int i = 0;
    char str[1024];
    strcpy(str, buffer);

    char* token = strtok(str, " ");
    while (i < part - 1)
    {
        token = strtok(NULL, " ");
        i++;
    }

    return token;
}

// This method handles the joining group feature.
void join_group(int g_id, int s_id, char name[50])
{
    if (g_id >= 0 && g_id <= GCAPACITY - 1)
    {
        for (int i = 0; i < CCAPACITY; i++)
        {
            if (groups[g_id].clients[i] == s_id)
            {
                return;
            }
        }
        for (int i = 0; i < CCAPACITY; i++)
        {
            if (groups[g_id].useable[i] == 1)
            {
                groups[g_id].useable[i] = 0;
                groups[g_id].clients[i] = s_id;
                strcpy(groups[g_id].names[i], name);
                return;
            }
        }
    }
}

// This method handles the leaving group feature
void leave_group(int g_id, int s_id)
{
    if (g_id >= 0 && g_id <= GCAPACITY - 1)
    {
        for (int i = 0; i < CCAPACITY; i++)
        {
            if (groups[g_id].clients[i] == s_id)
            {
                groups[g_id].clients[i] = -1;
                groups[g_id].useable[i] = 1;
                return;
            }
        }
    }
}

// In this message user will send messages to other people in a group.
void send_message(int g_id, int s_id, char name[50], char message[100])
{
    if (g_id >= 0 && g_id <= GCAPACITY - 1)
    {
        int flag = 0;
        for (int i = 0; i < CCAPACITY; i++)
        {
            if (groups[g_id].useable[i] == 0 && groups[g_id].clients[i] == s_id)
            {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            return;
        }

        char content[1024] = "";
        strcat(content, name);
        strcat(content, ": ");
        strcat(content, message);

        for (int i = 0; i < CCAPACITY; i++)
        {
            if (groups[g_id].useable[i] == 0 && groups[g_id].clients[i] != s_id)
            {
                send(groups[g_id].clients[i], content, 1024, 0);
                printf("Group %d: message send from %s to %s\n", g_id, name, groups[g_id].names[i]);
            }
        }
    }
}

// Each of our threads will handle a client by this method
void *handleClient(void *vargp)
{
    int *temp = (int *)vargp;
    int client_socket = *temp; // Get client socket

    char buffer[1024] = {0}; // Our main buffer for each client
    int valread = read(client_socket, buffer, 1024);
    char name[50];

    strcpy(name, buffer);
    fflush(stdout);
    buffer[0] = '\0';

    while (1)
    {
        // reads a buffer with maximum size 1024 from socket.
        valread = read(client_socket, buffer, 1024);
        if (valread < 0)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        buffer[valread] = '\0';

        char response[100];

        if (strcmp(buffer, "quit") == 0)
        {
            printf("Client quited %s\n", name);
            break;
        } else if (strcmp(split_input(1, buffer), "join") == 0) 
        {
            int group = atoi(split_input(2, buffer));
            join_group(group, client_socket, name);
            strcpy(response, "You have been added to the group.\n");
        } else if (strstr(split_input(1, buffer), "send")) 
        {
            int group = atoi(split_input(2, buffer));
            char message[100];
            strcpy(message, split_input(3, buffer));
            send_message(group, client_socket, name, message);
            strcpy(response,"Message sent.\n");
        } else if (strstr(split_input(1, buffer), "leave")) 
        {
            int group = atoi(split_input(2, buffer));
            leave_group(group, client_socket);
            strcpy(response, "You have left the group.\n");
        } else {
            strcpy(response, "Wrong input.\n");
        }

        // writes to client socket
        send(client_socket, response, 100, 0);
        printf("(s = %d) %s: \' %s \'\n", valread, name, buffer);

        fflush(stdout);
        buffer[0] = '\0';
    }
}

int main(int argc, char const *argv[])
{
    // Groups initialize
    for (int i = 0; i < GCAPACITY; i++)
    {
        groups[i].id = i + 1;
        for (int j = 0; j < CCAPACITY; j++)
        {
            groups[i].clients[j] = -1;
            groups[i].useable[j] = 1;
        }
    }

    // creates socket file descriptor
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(atoi(argv[1])); // host to network -- coverts the ending of the given integer
    const int addrlen = sizeof(address);

    // binding
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // listening on server socket with backlog size 3.
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Listen on %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    while (1)
    {
        // accepting client
        // accept returns client socket and fills given address and addrlen with client address information.
        int client_socket, valread;
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("Accepted client %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

        // Using threads to create a multi-client server
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handleClient, (void *)&client_socket);
    }
    return 0;
}
