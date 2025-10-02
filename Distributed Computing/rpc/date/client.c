#include <stdio.h>
#include <stdlib.h>
#include "datetime.h"

int main(int argc, char *argv[]) {
    CLIENT *clnt;
    char *server_host;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s server_host\n", argv[0]);
        exit(1);
    }
    server_host = argv[1];

    clnt = clnt_create(server_host, DATETIMEINFO_PROG, DATETIMEINFO_VERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(server_host);
        exit(1);
    }

    // Call get_datetime
    date_time *dt = get_datetime_1(NULL, clnt);
    if (dt == NULL) {
        clnt_perror(clnt, "call failed");
    } else {
        printf("Current datetime: %s\n", dt->datetime);
    }

    // Call get_year
    year_info *year = get_year_1(NULL, clnt);
    if (year == NULL) {
        clnt_perror(clnt, "call failed");
    } else {
        printf("Current year: %d\n", year->year);
    }

    // Call get_sysinfo
    system_info *sysinfo = get_sysinfo_1(NULL, clnt);
    if (sysinfo == NULL) {
        clnt_perror(clnt, "call failed");
    } else {
        printf("System info: %s\n", sysinfo->info);
    }

    clnt_destroy(clnt);
    return 0;
}

