/* datetimeinfo.x */

struct date_time {
    string datetime<100>;
};

struct year_info {
    int year;
};

struct system_info {
    string info<256>;
};

program DATETIMEINFO_PROG {
    version DATETIMEINFO_VERS {
        date_time GET_DATETIME(void) = 1;
        year_info GET_YEAR(void) = 2;
        system_info GET_SYSINFO(void) = 3;
    } = 1;
} = 0x23451111;

