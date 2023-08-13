#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SZ BUFSIZ * BUFSIZ
static char buffer[BUFFER_SZ];

void push_buff(char *start, int n)
{
    for (int i = 0; i < n; i++) {
        char *end = &start[strlen(start)];

        while (end > start) {
            *end = *(end - 1);
            end--;
        }
    }
}

int main(int argc, char **argv)
{
    int doemote = 0;
    char *buffer_ptr = &buffer[0];

    int opt, optcount = 0;
    while ((opt = getopt(argc, argv, "e")) != -1) {
        switch(opt) {
        case 'e': doemote = 1; optcount++; break;
        default: fputs("usage: txt2owo [-e] [...]\n", stderr); return 1;
        }
    }

    /* start output with '>:3 ' */
    if (doemote) {
        memcpy(buffer_ptr, ">:3 ", sizeof(char) * 4);
        buffer_ptr += 4;
    }

    if (optcount == (argc - 1))
        fread(buffer_ptr, sizeof(char), BUFFER_SZ, stdin);
    else {
        int n = 0;
        for (int i = 1 + optcount; i < argc; i++) {
            memcpy(&buffer_ptr[n], argv[i], strlen(argv[i]));
            n = strlen(buffer_ptr);
            buffer_ptr[n++] = ' ';
        }
    }

    size_t sz = strlen(buffer_ptr);
    for (size_t i = 0; i < sz; i++) {
        /* replace R/r and L/l with W/w */
        if (toupper(buffer_ptr[i]) == 'R')
            buffer_ptr[i] += 5;
        if (toupper(buffer_ptr[i]) == 'L')
            buffer_ptr[i] += 11;

        if (sz - i > 3) {
            /* replace OO/oo with OwO/owo */
            if (toupper(buffer_ptr[i]) == 'O' && toupper(buffer_ptr[i + 1]) == 'O') {
                char tmpp = buffer_ptr[i + 2],
                     tmp = buffer_ptr[i + 1];
                buffer_ptr[i + 1] = 'w';
                buffer_ptr[i + 2] = tmp;
                if (sz - i > 4) {
                    push_buff(&buffer_ptr[i + 3], 1);
                    buffer_ptr[i + 3] = tmpp;
                }
            }

            /* replace UU/uu with UwU/uwu */
            if (toupper(buffer_ptr[i]) == 'U' && toupper(buffer_ptr[i + 1]) == 'U') {
                char tmpp = buffer_ptr[i + 2],
                     tmp = buffer_ptr[i + 1];
                buffer_ptr[i + 1] = 'w';
                buffer_ptr[i + 2] = tmp;
                if (sz - i > 4) {
                    push_buff(&buffer_ptr[i + 3], 1);
                    buffer_ptr[i + 3] = tmpp;
                }
            }
        }
    }

    /* if it ends on a newline, exclude it since puts() already terminates with one */
    if (buffer_ptr[strlen(buffer_ptr) - 1] == '\n')
        buffer_ptr[strlen(buffer_ptr) - 1] = '\0';

    /* end output with ' >.<' */
    if (doemote)
        memcpy(&buffer_ptr[strlen(buffer_ptr) - 1], " >.<", sizeof(char) * 4);

    puts(buffer);

    return 0;
}
