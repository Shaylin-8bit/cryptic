#include <stdio.h>
#include <string.h>
#include "include/file_handler.h"

int hash(char* key, int max) {
    int result = 1;
    unsigned long sze = strlen(key);
    for (unsigned long i = 0; i < sze; i++) {
        if (result + (key[i] * key[i] - key[i])) result += (key[i] * key[i] - key[i]);
    }
    return (result % max) + 1;
}


void encrypt(char* fn, char* key, unsigned int hash_factor) {
    FILE* input = fopen(fn, "r");
    FILE* tmp = tmpfile();

    int new;
    int hashed = hash(key, hash_factor);
    while ((new = getc(input)) != EOF) {
        new = new * hashed + hashed;
        fwrite(&new, sizeof(int), 1, tmp); 
    }
    fclose(input);
    
    FILE* output = fopen(fn, "w");
    rewind(tmp);
    
    cpyfile(output, tmp);
    fclose(output);
}


void decrypt(char* fn, char* key, unsigned int hash_factor) {
    FILE* input = fopen(fn, "r");
    FILE* tmp = tmpfile();

    unsigned int c;
    int hashed = hash(key, hash_factor);
    char new;
    while (fread(&c, sizeof(int), 1, input)) {
        new = (c - hashed) / hashed;
        fwrite(&new, 1, 1, tmp); 
    }

    fclose(input);
    FILE* output = fopen(fn, "w");
    rewind(tmp);

    cpyfile(output, tmp);
    fclose(output);
}