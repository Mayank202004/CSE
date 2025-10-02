#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUF_SIZE 4096

int count_chars(const char *text) {
    int count = 0;
    for (int i = 0; text[i]; i++) {
        if (!isspace(text[i])) count++; // Exclude spaces/newlines
    }
    return count;
}

int count_words(const char *text) {
    int count = 0;
    int in_word = 0;
    for (int i = 0; text[i]; i++) {
        if (isspace(text[i])) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
    }
    return count;
}

int count_lines(const char *text) {
    int count = 0;
    for (int i = 0; text[i]; i++) {
        if (text[i] == '\n') count++;
    }
    // Add 1 if the last line doesn't end in newline and text is not empty
    if (strlen(text) > 0 && text[strlen(text) - 1] != '\n') count++;
    return count;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUF_SIZE] = {0}, response[BUF_SIZE];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("[Server] Waiting for connection on port %d...\n", PORT);

    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("[Server] Client connected.\n");

    int valread = read(client_fd, buffer, BUF_SIZE - 1);
    if (valread > 0) {
        buffer[valread] = '\0';  // Null-terminate

        printf("[Server] Paragraph received:\n%s\n", buffer);

        int chars = count_chars(buffer);
        int words = count_words(buffer);
        int lines = count_lines(buffer);

        snprintf(response, BUF_SIZE,
                 "Characters (no spaces/newlines): %d\nWords: %d\nLines: %d\n",
                 chars, words, lines);

        send(client_fd, response, strlen(response), 0);
        printf("[Server] Response sent.\n");
    }

    close(client_fd);
    close(server_fd);
    return 0;
}

