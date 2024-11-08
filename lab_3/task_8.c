#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_lib/poly.h"


typedef polynom *(*callback)(polynom *, polynom *);


int skip_short_comment(FILE *file, char *c) {
    while ((*c) != '\n' && (*c) != EOF) {
        (*c) = getc(file);
    }
    (*c) = getc(file);
    return 0;
}

int skip_long_comment(FILE *file, char *c) {
    while ((*c) != ']' && (*c) != EOF) {
        (*c) = getc(file);
    }
    if ((*c) != ']') {
        printf("syntax error\n");
        return -1;
    }
    (*c) = getc(file);
    return 0;
}

int read_until_char(FILE *file,char *c, char *targ, char *stop, int allow_spaces) {
    int i = 0;
    int n = strlen(stop);
    int f = 0;
    while (1) {
        if ((*c) == EOF) {
            f = 1;
            break;
        }
        for (int j = 0; j < n; ++j) {
            if ((*c) == stop[j]) {
                f = 1;
                break;
            }
        }
        if (f) {
            break;
        }
        if (!allow_spaces || ((*c) != ' ' && (*c) != '\t' && (*c) != '\n')) {
            targ[i] = (*c);
            ++i;
        }
        (*c) = getc(file);
    }
    targ[i] = 0;
    return 0;
}


int read_command(FILE *file, polynom **a, polynom **b) {
    char c = ' ';
    char cmd[5];
    char poly_repr[64];
    
    while (c == ' ' || c == '\t' || c == '\n') { // skip spaces, tabs, \n's and comments
        c = getc(file);
        if (c == '%') {
            if (skip_short_comment(file, &c)) {
                if (*a != NULL) {
                    poly_delete(a);
                }
                if (*b != NULL) {
                    poly_delete(b);
                }
                return -1;
            }
        }
        if (c == '[') {
            if (skip_long_comment(file, &c)) {
                if (*a != NULL) {
                    poly_delete(a);
                }
                if (*b != NULL) {
                    poly_delete(b);
                }
                return -1;
            }
        } 
        if (c == EOF) {
            return -2;
        }
    }

    read_until_char(file, &c, cmd, "(", 0); // read command
    
    c = getc(file);
    if (c != ')' && c != EOF) { 
        read_until_char(file, &c, poly_repr, ",)", 1); // read first poly

        if (spoly_init(a, poly_repr)) {
            return -1;
        }
    } else {
        *a = NULL;
    }

    if (c == ',') {
        c = getc(file);
        read_until_char(file, &c, poly_repr, ")", 1); // read second poly

        if (spoly_init(b, poly_repr)) {
            return -1;
        }
    } else {
        *b = NULL;
    }

    c = getc(file);
    while (c != ';') { // find line end
        if (c != ' ' && c != '\t' && c != '\n') {
            if (*a != NULL) {
                poly_delete(a);
            }
            if (*b != NULL) {
                poly_delete(b);
            }
            printf("syntax error\n");
            return -1;
        }
        c = getc(file);
    }
    

    if (!strcmp("Add", cmd)) {
        return 0;
    } else if ((!strcmp("Sub", cmd))) {
        return 1;
    } else if ((!strcmp("Mult", cmd))) {
        return 2;
    } else if ((!strcmp("Div", cmd))) {
        return 3;
    } else if ((!strcmp("Mod", cmd))) {
        return 4;
    } else if ((!strcmp("Cmps", cmd))) {
        return 5;
    } else if ((!strcmp("Eval", cmd))) {
        return 6;
    } else if ((!strcmp("Diff", cmd))) {
        return 7;
    } else {
        if (*a != NULL) {
            poly_delete(a);
        }
        if (*b != NULL) {
            poly_delete(b);
        }
        printf("command error\n");
        return -1;
    }
}


int main() {
    FILE *file_in;
    if ((file_in = fopen("files/task_8_res.txt", "r")) == NULL) {
        printf("file error\n");
        return -1;
    }

    callback func[7] = {poly_add, poly_sub, poly_mult, poly_div, poly_mod, poly_cmps, poly_cmps};

    polynom *adder;
    if (poly_init(&adder)) {
        return -1;
    }
    polynom *buff;
    polynom *a;
    polynom *b;

    int cmd = -1;
    while (cmd != -2) {
        cmd = read_command(file_in, &a, &b);
        if (cmd == -2) {
            break;
        }
        if (cmd == -1) {
            poly_delete(&adder);
            if (a != NULL) {
                poly_delete(&a);
            }
            if (b != NULL) {
                poly_delete(&b);
            }
            return -1;
        }
        
        if (b != NULL) {
            if (cmd < 6) {
                poly_delete(&adder);
                adder = func[cmd](a, b);
                
            } else if (cmd == 6) {
                buff = func[cmd](a, b);
                printf("P(");
                poly_print(b);
                printf(") = ");
                poly_print(buff);
                printf("; ");
                poly_delete(&buff);

            } else {
                poly_delete(&adder);
                if (a != NULL) {
                    poly_delete(&a);
                }
                if (b != NULL) {
                    poly_delete(&b);
                }
                printf("too many arguments in function call\n");
                return -1;
            }
            
        } else if (a != NULL) {
            if (cmd < 6) {
                buff = func[cmd](adder, a);
                poly_delete(&adder);
                adder = buff;
                
            } else if (cmd == 6) {
                buff = func[cmd](adder, a);
                printf("Adder(");
                poly_print(a);
                printf(") = ");
                poly_print(buff);
                printf("; ");
                poly_delete(&buff);

            } else if (cmd == 7) {
                buff = poly_diff(a);
                poly_delete(&adder);
                adder = buff;
            }
            
        } else if (cmd == 7) {
            buff = poly_diff(adder);
            poly_delete(&adder);
            adder = buff;

        } else {
            poly_delete(&adder);
            if (a != NULL) {
                poly_delete(&a);
            }
            if (b != NULL) {
                poly_delete(&b);
            }
            printf("too few arguments in function call\n");
            return -1;
        }

        if (a != NULL) {
            poly_delete(&a);
        }
        if (b != NULL) {
            poly_delete(&b);
        }
        if (adder == NULL) {
            return -1;
        }
        printf("Adder value: ");
        poly_print(adder);
        putchar('\n');
    }
    poly_delete(&adder);
    return 0;
}