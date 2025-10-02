/* passwd.x */
struct Password {
    string text<100>;
};

struct Response {
    bool success;
    string message<100>;
};

program PASSWD_PROG {
    version PASSWD_VERS {
        Response CHECK_PASSWORD(Password) = 1;
    } = 1;
} = 0x31234567;

