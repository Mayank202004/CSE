#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUF_SIZE 1024
#define PASSWORD "open123"

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUF_SIZE] = {0};
    char *correct_password = PASSWORD;

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to the port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any IP
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("[Server] Listening on port %d...\n", PORT);

    // Accept client connection
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("[Server] Client connected.\n");

    while (1) {
        memset(buffer, 0, BUF_SIZE);

        // Read password from client
        int valread = read(client_fd, buffer, BUF_SIZE - 1);
        if (valread <= 0) {
            printf("[Server] Client disconnected or read error.\n");
            break;
        }
        buffer[valread] = '\0';

        printf("[Server] Received password: %s\n", buffer);

        // Check password
        if (strcmp(buffer, correct_password) == 0) {
            char *message = "Welcome! Password is correct.";
            send(client_fd, message, strlen(message), 0);
            printf("[Server] Sent greeting message. Closing connection.\n");
            break;  // close after success
        } else {
            char *message = "Incorrect password. Try again.";
            send(client_fd, message, strlen(message), 0);
        }
    }

    close(client_fd);
    close(server_fd);
    return 0;
}

