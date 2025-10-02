/* textproc.x */
struct Paragraph {
    string text<10000>;
};

struct Result {
    int words;
    int lines;
    int characters;
};

program TEXTPROC_PROG {
    version TEXTPROC_VERS {
        Result PROCESS_PARAGRAPH(Paragraph) = 1;
    } = 1;
} = 0x23451111;

