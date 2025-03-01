#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

#define PORT 8080
#define BUFFER_SIZE 4096

const char *server_response = 
    "{"
    "\"version\": {\"name\": \"1.21.4\", \"protocol\": 769},"
    "\"players\": {\"max\": 100, \"online\": 69420},"
    "\"description\": {\"text\": \"Hello World!\"},"
    "\"favicon\": \"data:image/png;base64,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\""
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

    unsigned char buffer[BUFFER_SIZE] = {0};
    int length;

    // Read packet length
    if (!read_varint(client_socket, &length)) {
        printf("Client disconnected (failed to read length).\n");
        close(client_socket);
        return NULL;
    }

    // Read full packet
    if (read(client_socket, buffer, length) <= 0) {
        printf("Client disconnected (failed to read data).\n");
        close(client_socket);
        return NULL;
    }

    // Thanks https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Server_List_Ping
    int packet_id = buffer[0];
    if (packet_id == 0x00) {  // Handshake
        int index = 1, protocol_version, next_state;
        if (!read_varint(client_socket, &protocol_version)) return NULL;

        if (buffer[0] == 0x00) {  // Status request packet
            printf("Sending server status response...\n");

            // Create Response Packet
            unsigned char response_packet[BUFFER_SIZE] = {0};
            int offset = 0;

            response_packet[offset++] = 0x00; // Packet ID (0x00)
            int json_length = strlen(server_response);
            offset += write_varint(response_packet + offset, json_length);
            memcpy(response_packet + offset, server_response, json_length);
            offset += json_length;

            // Send response
            unsigned char packet_length[5];
            int packet_length_size = write_varint(packet_length, offset);
            send(client_socket, packet_length, packet_length_size, 0);
            send(client_socket, response_packet, offset, 0);
        }
    
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
