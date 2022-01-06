#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "include/encryption.h"
#include "include/file_handler.h"


void display_help(void) {
    puts("cryptic {mode [enc/dec]} {filename} {password}\n");
    puts("mode      |  Mode to work with, \"enc\" to encode a file, \"dec\" to decode a file.");
    puts("filename  |  Name of file to act on, must include extension.");
    puts("password  |  Used as the key to decrypt a file with.");
}


void missing_args_alert(int argc) {
    char argdis[3][9] = {"mode", "filename", "password"};
    printf("Missing Argument: most likely {%s}\n", argdis[argc-1]);
    puts("Try help for information\n");
} 


char check_args(int argc, char* args[]) {
    if (argc > 1) {
        if (!strcmp(args[1], "help")) {
            display_help();
            return 2;
        }
    } 

    if (argc < 4) {
        missing_args_alert(argc);
        return 1;

    } else if (strcmp(args[1], "enc") && strcmp(args[1], "dec")) {
        printf("Invalid Argument: mode: \"%s\" is not valid\n", args[1]);
        puts("  \"enc\" to encode, \"dec\" to decode");
        puts("Try help for more information\n");
        return 1;
    
    }
    return 0;
}


char run(int argc, char* args[], unsigned int hash_factor) {
    char t;
    if ((t = check_args(argc, args))) return t;

    char mode[strlen(args[1]) + 1];
    char filename[strlen(args[2]) + 1];
    char password[strlen(args[3]) + 1];

    strcpy(mode, args[1]);
    strcpy(filename, args[2]);
    strcpy(password, args[3]);

    if (strcmp(mode, "enc")) {
        puts("Decrypting...");

        // Copy file in event user wants to revert
        FILE* safe = tmpfile();
        FILE* input = fopen(filename, "r");
        cpyfile(safe, input);
        fclose(input);

        decrypt(filename, password, hash_factor);
        printf("\nYour file, \"%s\", has been decrypted with password \"%s\"\n", filename, password);
        puts("Would you like to revert this decryption? WARNING: This action is irreversable!\n");
        char answer[5];
        do {
            puts("  Enter [y/n]");
            printf("  >>> ");
            scanf("%s", &answer);
        } while (tolower(answer[0]) != 'y' && tolower(answer[0]) != 'n');

        if (!strcmp(answer, "y")) {
            puts("\nReverting file...");
            FILE* output = fopen(filename, "w");
            rewind(safe);
            cpyfile(output, safe);
            fclose(output);
            puts("File reverted! Exiting...");
            return 0;
        } else {
            puts("\nExiting...");
            return 0;
        }


    } else {
        puts("Encrypting...");
        encrypt(filename, password, hash_factor);
        printf("Your file \"%s\" has been encrypted with password \"%s\"\nExiting...", filename, password);
    }
}