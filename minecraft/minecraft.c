#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

#define PORT 8080

int main() {
    int server_fd;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Make port immediatly reusable after restarting
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Error setting socket options");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Any network interface
    address.sin_port = htons(PORT);       // Convert port to network byte order

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Port bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    // 3 is the size of the queue
    if (listen(server_fd, 3) < 0) { // returns 0 on success and -1 on failure
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);
}