#include <stdio.h>
#include <time.h>
#include <sys/utsname.h>
#include "datetime.h"

date_time *get_datetime_1_svc(void *argp, struct svc_req *rqstp) {
    printf("[SERVER] Received request: get_datetime\n");
    static date_time result;
    static char buffer[100];
    time_t now = time(NULL);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    result.datetime = buffer;
    return &result;
}

year_info *get_year_1_svc(void *argp, struct svc_req *rqstp) {
    printf("[SERVER] Received request: get_year\n");
    static year_info result;
    time_t now = time(NULL);
    struct tm *lt = localtime(&now);
    result.year = lt->tm_year + 1900;
    return &result;
}

system_info *get_sysinfo_1_svc(void *argp, struct svc_req *rqstp) {
    printf("[SERVER] Received request: get_sysinfo\n");
    static system_info result;
    static char buffer[1024];
    struct utsname sysinfo;
    if (uname(&sysinfo) != -1) {
        snprintf(buffer, sizeof(buffer),
                 "System: %s, Node: %s, Release: %s, Version: %s, Machine: %s",
                 sysinfo.sysname, sysinfo.nodename, sysinfo.release,
                 sysinfo.version, sysinfo.machine);
    } else {
        snprintf(buffer, sizeof(buffer), "Error retrieving system info");
    }
    result.info = buffer;
    return &result;
}

