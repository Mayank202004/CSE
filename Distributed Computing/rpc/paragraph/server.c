/* server.c */
#include <stdio.h>
#include <string.h>
#include "textproc.h"

Result *process_paragraph_1_svc(Paragraph *para, struct svc_req *req) {
    printf("[Server] : Got a request from client\n");
    static Result result;
    int words = 0, lines = 0, characters = 0;
    int in_word = 0;

    const char *text = para->text;
    characters = strlen(text);

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            lines++;
        }
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    result.words = words;
    result.lines = lines + 1; // Count last line if not ending in '\n'
    result.characters = characters;

    return &result;
}

