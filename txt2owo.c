#include <stdio.h>
#include <string.h>

static char buffer[BUFSIZ];

int main(int argc, char **argv)
{
    if (argc < 2)
        fread(buffer, sizeof(char), BUFSIZ, stdin);
    else {
        int n = 0;
        for (int i = 1; i < argc; i++) {
            memcpy(&buffer[n], argv[i], strlen(argv[i]));
            n = strlen(buffer);
            buffer[n++] = ' ';
        }
    }

    size_t sz = strlen(buffer);
    for (size_t i = 0; i < sz; i++) {
        if (buffer[i] == 'r' || buffer[i] == 'l')
            buffer[i] = 'w';
        if (buffer[i] == 'R' || buffer[i] == 'L')
            buffer[i] = 'W';
        if (sz - i > 3) {
            if (buffer[i] == 'o' && buffer[i + 1] == 'o') {
                buffer[i] = 'o';
                buffer[i + 1] = 'w';
                buffer[i + 2] = 'o';
            }
        }
    }

    puts(buffer);

    return 0;
}
