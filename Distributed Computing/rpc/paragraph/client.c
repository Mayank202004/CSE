/* client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "textproc.h"

#define MAX_TEXT 10000

int main(int argc, char *argv[]) {
    CLIENT *clnt;
    Paragraph para;
    Result *res;
    char buffer[MAX_TEXT];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <server_host>\n", argv[0]);
        exit(1);
    }

    clnt = clnt_create(argv[1], TEXTPROC_PROG, TEXTPROC_VERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }

    printf("Enter a paragraph (end with CTRL+D):\n");
    size_t len = fread(buffer, 1, MAX_TEXT - 1, stdin);
    buffer[len] = '\0';
    para.text = buffer;

    res = process_paragraph_1(&para, clnt);
    if (res == NULL) {
        clnt_perror(clnt, "RPC call failed");
        exit(1);
    }

    printf("\n--- Result ---\n");
    printf("Words: %d\n", res->words);
    printf("Lines: %d\n", res->lines);
    printf("Characters: %d\n", res->characters);

    clnt_destroy(clnt);
    return 0;
}

