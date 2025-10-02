/* server.c */
#include <stdio.h>
#include <string.h>
#include "passwd.h"

#define CORRECT_PASSWORD "open123"

Response *check_password_1_svc(Password *pass, struct svc_req *req) {
    static Response res;

    if (strcmp(pass->text, CORRECT_PASSWORD) == 0) {
        res.success = TRUE;
        res.message = "Welcome! Password accepted.";
    } else {
        res.success = FALSE;
        res.message = "Incorrect password. Try again.";
    }

    printf("[Server] Password received: '%s' => %s\n", pass->text, res.success ? "Accepted" : "Rejected");
    return &res;
}

