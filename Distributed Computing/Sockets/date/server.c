#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/utsname.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUF_SIZE 2048

void get_all_info(char *out) {
    char datetime[128], year[32], sysinfo[1024];

    // Date and Time
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(datetime, sizeof(datetime), "Date & Time : %Y-%m-%d %H:%M:%S", t);
    strftime(year, sizeof(year), "Year        : %Y", t);

    // System Info
    struct utsname u;
    if (uname(&u) == 0) {
        snprintf(sysinfo, sizeof(sysinfo),
            "System Info :\n  OS     : %s\n  Node   : %s\n  Release: %s\n  Version: %s\n  Machine: %s",
            u.sysname, u.nodename, u.release, u.version, u.machine);
    } else {
        snprintf(sysinfo, sizeof(sysinfo), "System Info: Unable to retrieve.");
    }

    // Combine all
    snprintf(out, BUF_SIZE, "%s\n%s\n%s\n", datetime, year, sysinfo);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char response[BUF_SIZE] = {0};

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

    printf("[Server] Client connected. Sending system info...\n");

    get_all_info(response);
    send(client_fd, response, strlen(response), 0);

    printf("[Server] Info sent. Closing connection.\n");

    close(client_fd);
    close(server_fd);
    return 0;
}

