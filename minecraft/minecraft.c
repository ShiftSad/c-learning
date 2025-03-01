#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

#define PORT 8080
#define BUFFER_SIZE 1024

const char *server_response = 
    "{"
    "\"version\": {\"name\": \"1.20.4\", \"protocol\": 764},"
    "\"players\": {\"max\": 100, \"online\": 5},"
    "\"description\": {\"text\": \"Hello from C Server!\"}"
    "}";

/**
What is a VarInt?
- It is a (Variable-Length Integer), a number enconding format used in Minecraft's protocol, (and Google's protobuf) to efficiently store
integers in smaller values, taking up less space.
How that is done?
- The most significant bit is dedicated as a continuation, if it is set to 1, continue reading, else, stop.
*/

// https://stackoverflow.com/questions/19758270/read-varint-from-linux-sockets
int read_varint(int socket, int *out) {
    int result = 0, shift = 0;
    unsigned char byte;
    do {
        if (read(socket, &byte, 1) <= 0) return 0;
        result |= (byte & 0x7F) << shift;
        shift += 7;
    } while (byte & 0x80);
    *out = result;
    return 1;
}

// Writes a VarInt to a buffer
int write_varint(unsigned char *buffer, int value) {
    int i = 0;
    while (1) {
        if ((value & ~0x7F) == 0) {
            buffer[i++] = value;
            break;
        }
        buffer[i++] = (value & 0x7F) | 0x80;
        value >>= 7;
    }
    return i;
}

void *handle_client(void *socket_desc) {
    int client_socket = *(int *)socket_desc;
    free(socket_desc);

    char buffer[BUFFER_SIZE] = {0};
    while (1) {
        int valread = read(client_socket, buffer, BUFFER_SIZE);
        if (valread <= 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Received: %s\n", buffer);
        send(client_socket, buffer, valread, 0); // Echo back
        memset(buffer, 0, BUFFER_SIZE);
    }

    close(client_socket);
    return NULL;
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Make port immediately reusable after restarting
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Error setting socket options");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Any network interface
    address.sin_port = htons(PORT);       // Convert port to network byte order

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Port bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    // 10 is the size of the queue
    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        int *new_socket = malloc(sizeof(int)); // Allocate memory for each client socket
        *new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (*new_socket < 0) {
            perror("Accept failed");
            free(new_socket);
            continue;
        }

        printf("New client connected.\n");

        pthread_t client_thread;
        if (pthread_create(&client_thread, NULL, handle_client, new_socket) != 0) {
            perror("Could not create thread");
            free(new_socket);
        }
        pthread_detach(client_thread); // Automatically cleans up thread resources
    }

    close(server_fd);
    return 0;
}
