#include <stdio.h>
#include <string.h>

enum StatusCode {OK, WRONG_NUMBER_OF_ARGS, SECOND_ARG_MUST_BE_A_FLAG,
FILE_ERROR, WRONG_FLAG};


enum StatusCode skip_spaces(FILE* file_in, char* c) {
    while (*c == ' ' || *c == '\t' || *c == '\n') {
        if (fscanf(file_in, "%c", c) == EOF) {
            *c = ' ';
            break;
        }
    }
    return OK;
}


enum StatusCode comb(FILE* file_in_1, FILE* file_in_2, FILE* file_out) {
    char c = ' ';
    int end_1 = 0;
    int end_2 = 0;
    
    while ((!end_1) || (!end_2)) {
        if (!end_1) {
            skip_spaces(file_in_1, &c);
            if (c == ' ') {
                end_1 = 1;
            }
            
            while ((c != ' ') && (c != '\t') && (c != '\n') && (!end_1)) {
                fprintf(file_out, "%c", c);
                
                if (fscanf(file_in_1, "%c", &c) == EOF) {
                    end_1 = 1;
                    c = ' ';
                    fprintf(file_out, " ");
                    break;
                }
            }
            if (!end_1) {
                fprintf(file_out, " ");
            }
        }
        
        if (!end_2) {
            skip_spaces(file_in_2, &c);
            if (c == ' ') {
                end_2 = 1;
            }
            
            while ((c != ' ') && (c != '\t') && (c != '\n') && (!end_2)) {
                fprintf(file_out, "%c", c);
                
                if (fscanf(file_in_2, "%c", &c) == EOF) {
                    end_2 = 1;
                    c = ' ';
                    fprintf(file_out, " ");
                    break;
                }
            }
            if (!end_2) {
                fprintf(file_out, " ");
            }
        }
    }
    return OK;
}

enum StatusCode quad(char* c, char* res) {
    res[3] = ((*c) & 0b11) + '0';
    res[2] = ((*c >> 2) & 0b11) + '0';
    res[1] = ((*c >> 4) & 0b11) + '0';
    res[0] = ((*c >> 6) & 0b11) + '0';
}

enum StatusCode oct(char* c, char* res) {
    
    res[2] = ((*c) & 0b111) + '0';
    res[1] = ((*c >> 3) & 0b111) + '0';
    res[0] = ((*c >> 6) & 0b111) + '0';
}

enum StatusCode strange(FILE* file_in, FILE* file_out) {
    char c = ' ';
    int end = 0;
    int n = 0;
    
    while (!end) {
        skip_spaces(file_in, &c);
        if (c == ' ') {
            break;
        }
        ++n;
        while ((c != ' ') && (c != '\t') && (c != '\n') && (!end)) {
            if (n % 2 == 0) {
                if (c >= 'A' && c <= 'Z') {
                    c -= 'A' - 'a';
                }
            }   
            if (n % 5 == 0) {
                char mod[4];
                if (n % 2 == 0) {
                    quad(&c, mod);
                } else {
                    mod[3] = 0;
                    oct(&c, mod);
                }
                fprintf(file_out, "%s", mod);
            } else {
                fprintf(file_out, "%c", c);
            }
            
            if (fscanf(file_in, "%c", &c) == EOF) {
                end = 1;
                c = ' ';
                break;
            }
        }
        fprintf(file_out, " ");
    }
    return OK;
}

enum StatusCode main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Terminated with exit code %d\n", WRONG_NUMBER_OF_ARGS);
        return WRONG_NUMBER_OF_ARGS;
    }
    if (argv[1][0] != '/' && argv[1][0] != '-') {
        printf("Terminated with exit code %d\n", SECOND_ARG_MUST_BE_A_FLAG);
        return SECOND_ARG_MUST_BE_A_FLAG;
    }

    FILE* file_in_1, *file_out;
    enum StatusCode code = OK;

    if ((file_in_1 = fopen(argv[2], "r")) == NULL) {
        printf("Terminated with exit code %d\n", FILE_ERROR);
        return FILE_ERROR;
    }
    

    switch (argv[1][1])
    {
    case 'r':
        if (argc != 5) {
            printf("Terminated with exit code %d\n", WRONG_NUMBER_OF_ARGS);
            return WRONG_NUMBER_OF_ARGS;
        }
        FILE *file_in_2;
        if ((file_in_2 = fopen(argv[3], "r")) == NULL) {
            printf("Terminated with exit code %d\n", WRONG_NUMBER_OF_ARGS);
            return FILE_ERROR;
        }
        if ((file_out = fopen(argv[4], "w")) == NULL) {
            printf("Terminated with exit code %d\n", FILE_ERROR);
            return FILE_ERROR;
        }
        code = comb(file_in_1, file_in_2, file_out);
        fclose(file_in_2);
        break;
        
    case 'a':
        if (argc != 4) {
            printf("Terminated with exit code %d\n", WRONG_NUMBER_OF_ARGS);
            return WRONG_NUMBER_OF_ARGS;
        }
        if ((file_out = fopen(argv[3], "w")) == NULL) {
            printf("Terminated with exit code %d\n", FILE_ERROR);
            return FILE_ERROR;
        }
        code = strange(file_in_1, file_out);
        break;
    
    default:
        code = WRONG_FLAG;
        break;
    }

    fclose(file_in_1);
    fclose(file_out);
    
    if (code != OK) {
        printf("Terminated with exit code %d\n", code);
    }
    return code;
}