#include <stdio.h>
#include <string.h>

enum StatusCode {OK, WRONG_NUMBER_OF_ARGS, SECOND_ARG_MUST_BE_A_FLAG,
FILE_ERROR, WRONG_FLAG};


enum StatusCode split_filepath(char* directory_path, char* filename, char* path) {
    char* r = path;
    char* w = directory_path;
    while (*r != 0) {
        ++w; ++r;
    }
    while (*r != '/') {
        *w = 0;
        --w; --r;
    }

    char* rf = r + 1;
    while (r != path - 1) {
        *w = *r;
        --w; --r;
    }
    w = filename;
    while (*rf != 0) {
        *w = *rf;
        ++w; ++rf;
    }
    *w = 0;

    //сука ебка нахуй, нет бы .split("/") "/".join() бля
    return OK;
}

enum StatusCode no_digits(FILE* file_in, FILE* file_out) {
    char c = 0;
    while (fscanf(file_in, "%c", &c) != EOF) {
        if (!(c <= '9' && c >= '0')) {
            fprintf(file_out, "%c", c);
        }
    }
    return OK;
}
enum StatusCode count_latin(FILE* file_in, FILE* file_out) {
    char c = 0;
    long long counter = 0;
    while (fscanf(file_in, "%c", &c) != EOF) {
        if (c == '\n') {
            fprintf(file_out, "%lld\n", counter);
            counter = 0;
        } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            counter += 1;
        }
    }
    fprintf(file_out, "%lld\n", counter);

    return OK;
}
enum StatusCode zzzzzzzzooooooovvvvv(FILE* file_in, FILE* file_out) {
    char c = 0;
    long long counter = 0;
    while (fscanf(file_in, "%c", &c) != EOF) {
        if (c == '\n') {
            fprintf(file_out, "%lld\n", counter);
            counter = 0;
        } else if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
        || (c >= '0' && c <= '9') || (c == ' '))) {
            counter += 1;
        }
    }
    fprintf(file_out, "%lld\n", counter);

    return OK;
}

enum StatusCode hex(FILE* file_in, FILE* file_out) {
    char c = 0;
    char h[2];
    
    while (fscanf(file_in, "%c", &c) != EOF) {
        if (!(c <= '9' && c >= '0')) {
            h[1] = c & 0b1111;
            h[0] = (c >> 4) & (0b1111);

            for (int i = 0; i < 2; ++i) {
                h[i] += '0';
                if (h[i] > '9') {
                    h[i] += 'a' - '9' - 1;
                } 
            }
            fprintf(file_out, "%s ", h);
        } else {
            fprintf(file_out, "%c ", c);
        }
    }
    return OK;
}

enum StatusCode main(int argc, char* argv[]) {
    if (argc < 3) {
        return WRONG_NUMBER_OF_ARGS;
    }
    if (argv[1][0] != '/' && argv[1][0] != '-') {
        return SECOND_ARG_MUST_BE_A_FLAG;
    }

    FILE* file_in; 
    FILE* file_out;
    int n = 0;
    enum StatusCode code = OK;

    if ((file_in = fopen(argv[2], "r")) == NULL) {
        return FILE_ERROR;
    }

    if (argv[1][1] == 'n') {
        if (argc != 4) {
            return WRONG_NUMBER_OF_ARGS;
        }
        if ((file_out = fopen(argv[3], "w")) == NULL) {
            return FILE_ERROR;
        }
        n = 1;
    } else {
        if (argc != 3) {
            return WRONG_NUMBER_OF_ARGS;
        }
        char filename[32];
        char directory_path[128];
        code = split_filepath(directory_path, filename, argv[2]);
        if (code != OK) {
            return code;
        }       
        
        if ((file_out = fopen(strcat(strcat(directory_path, "out_"), filename), "w")) == NULL) {
            return FILE_ERROR;
        }
    }

    switch (argv[1][1+n])
    {
    case 'd':
        code = no_digits(file_in, file_out);
        break;
    case 'i':
        code = count_latin(file_in, file_out);
        break;
    case 's':
        code = zzzzzzzzooooooovvvvv(file_in, file_out);
        break;
    case 'a':
        code = hex(file_in, file_out);
        break;
    
    default:
        code = WRONG_FLAG;
        break;
    }

    fclose(file_in);
    fclose(file_out);

    return code;
}