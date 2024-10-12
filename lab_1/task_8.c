#include <stdio.h>
#include <stdlib.h>


enum StatusCode {OK, WRONG_NUMBER_OF_ARGS, BAD_INPUT,
FILE_ERROR};


enum StatusCode cringe(FILE* file_in, FILE* file_out) {
    char c = ' ';
    int base = 0;
    int decimal = 0;

    while ((fscanf(file_in, "%c", &c)) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (base != 0) {
                fprintf(file_out, " %d %d\n", base, decimal);
                base = 0;
                decimal = 0;
            }
        } else {
            fprintf(file_out, "%c", c);
            if (c >= 'A' && c <= 'Z') {
                c -= 'A';
                c += 'a';
            }

            c -= '0';
            if (c > 9) {
                c -= 'a' - '9' - 1;
            }
            
            if (c < 0 || c > 35) {
                return BAD_INPUT;
            }

            if (c >= base) {
                base = c + 1;
            }

            decimal *= 10;
            decimal += c;
        }
    }
    if (base != 0) {
        fprintf(file_out, " %d %d\n", base, decimal);
        base = 0;
        decimal = 0;
    }

    return OK;
}


enum StatusCode main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Terminated with exit code %d\n", WRONG_NUMBER_OF_ARGS);
        return WRONG_NUMBER_OF_ARGS;
    }

    FILE* file_in, *file_out;

    if ((file_in = fopen(argv[1], "r")) == NULL) {
        printf("Terminated with exit code %d\n", FILE_ERROR);
        return FILE_ERROR;
    }
    if ((file_out = fopen(argv[2], "w")) == NULL) {
        printf("Terminated with exit code %d\n", FILE_ERROR);
        return FILE_ERROR;
    }

    enum StatusCode code;
    code = cringe(file_in, file_out);

    fclose(file_in);
    fclose(file_out);
    
    if (code != OK) {
        printf("Terminated with exit code %d\n", code);
    }
    return code;
}