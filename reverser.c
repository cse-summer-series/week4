#include <stdio.h>
#include <string.h>
#include "utf8str.c"

int read_size = 100;

int main(int argc, char** argv) {
    char input[read_size];
    char output[read_size];
    while(1) {
        fgets(input, read_size, stdin);
        input[strlen(input) - 1] = 0;

        char* reversed = utf8_reverse(input);
        printf("%s\n", reversed);
        free(reversed);
    }
}
