#include <stdio.h>

void cpyfile(FILE* dest, FILE* src) {
    char c;
    while ((c = getc(src)) != EOF) {
        putc(c, dest);
    }
}