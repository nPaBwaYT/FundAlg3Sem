#include <stdio.h>
#include "my_lib/my_string.h"
#include <stdarg.h>


int str_cmp(str* left, str* right, size_t r_idx) {
    for (size_t idx = 0; idx < left->size - 1; ++idx) {
        if (left->begin[idx] != right->begin[(left->size - 1 + r_idx + idx) % (right->size - 1)]) {
            return 0;
        }
    }
    return 1;
}

int my_func(char* substr, int n, ...) {
    str* string;
    if (str_create(&string, substr)) {
        return -1;
    }

    va_list files;
    va_start(files, n);
    char* filepath;

    for (int i = 0; i < n; ++i) {
        filepath = va_arg(files, char*);
        FILE* file_in;
        if ((file_in = fopen(filepath, "r")) == NULL) {
            printf("file error\n");
            return -1;
        }

        char c = ' ';
        
        str* buff;
        str_create(&buff, substr);
        
        size_t idx = 0;

        int row = 1;
        int sym = 0;

        while (fscanf(file_in, "%c", &c) != EOF) {
            if (c == '\n') {
                ++row;
                sym = 1;
            } else if (c == EOF) {
                break;
            } else {
                ++sym;
            }

            buff->begin[idx] = c;
            idx = (idx + 1) % (buff->size - 1);
            
            if ((str_cmp(string, buff, idx)) && (((row - 1) * string->size + (sym - 1)) > string->size)) {
                printf("%d %ld\n", row, sym - (string->size - 1));
            }
        }   
        str_delete(&buff);
        fclose(file_in);   
    }
    va_end(files);
    str_delete(&string);
    return 0;
}


int main() {
    char* substr = (char*)malloc(32 * sizeof(char));
    scanf("%s", substr);
    if (my_func(substr, 3, "files/task_3_res_1.txt", "files/task_3_res_2.txt", "files/task_3_res_3.txt")) {
        return -1;
    }
    free(substr);

    return 0;
}
