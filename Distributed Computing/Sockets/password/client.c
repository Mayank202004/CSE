#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUF_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};
    char input[BUF_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n[Client] Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\n[Client] Invalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n[Client] Connection Failed \n");
        return -1;
    }

    while(1) {
        printf("Enter password: ");
        if (!fgets(input, sizeof(input), stdin)) {
            printf("[Client] Input error\n");
            break;
        }
        // Remove newline at end of input
        input[strcspn(input, "\n")] = 0;

        // Send password to server
        send(sock, input, strlen(input), 0);

        // Read server response
        int valread = read(sock, buffer, BUF_SIZE - 1);
        if (valread <= 0) {
            printf("[Client] Server closed connection or error.\n");
            break;
        }
        buffer[valread] = '\0';

        printf("[Server] %s\n", buffer);

        // If greeting message received, exit
        if (strstr(buffer, "Welcome") != NULL) {
            break;
        }
    }

    close(sock);
    return 0;
}

