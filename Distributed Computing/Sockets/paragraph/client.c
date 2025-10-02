#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUF_SIZE 4096

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char input[BUF_SIZE] = {0};
    char buffer[BUF_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("[Client] Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("[Client] Invalid address or unsupported format\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("[Client] Connection failed\n");
        return -1;
    }

    printf("Enter a paragraph (end with an empty line):\n");

    char line[1024];
    input[0] = '\0';

    while (1) {
        if (!fgets(line, sizeof(line), stdin)) break;
        if (strcmp(line, "\n") == 0) break;  // Empty line to stop input
        strcat(input, line);
    }

    send(sock, input, strlen(input), 0);

    int valread = read(sock, buffer, BUF_SIZE - 1);
    if (valread > 0) {
        buffer[valread] = '\0';
        printf("\n[Server Response]\n%s\n", buffer);
    } else {
        printf("[Client] No response from server.\n");
    }

    close(sock);
    return 0;
}

