/* client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passwd.h"

int main(int argc, char *argv[]) {
    CLIENT *clnt;
    Password input;
    Response *res;
    char buffer[100];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <server_host>\n", argv[0]);
        exit(1);
    }

    clnt = clnt_create(argv[1], PASSWD_PROG, PASSWD_VERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }

    while (1) {
        printf("Enter password: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // remove newline

        input.text = buffer;

        res = check_password_1(&input, clnt);
        if (res == NULL) {
            clnt_perror(clnt, "RPC call failed");
            exit(1);
        }

        printf("%s\n", res->message);

        if (res->success) break;
    }

    clnt_destroy(clnt);
    return 0;
}

