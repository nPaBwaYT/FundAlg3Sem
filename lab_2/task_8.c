#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


int to_digit(char x) {
    if (x > 'a') {
        return 10 + x - 'a';
    } else if (x > 'A') {
        return 10 + x - 'A';
    } else {
        return x - '0';
    }
}


int col_sum(int base, char* x, char* y, char** result) {
    char* ptr_x = x;
    char* ptr_y = y;

    while (*ptr_x != 0) {
        ++ptr_x;
    }
    while (*ptr_y != 0) {
        ++ptr_y;
    }

    char* mid_result = (char*)malloc((size_t)(fmax(strlen(x), strlen(y)) + 1) * sizeof(char));
    if (mid_result == NULL){
        return -1;
    }
    char* w = &mid_result[(size_t)fmax(strlen(x), strlen(y))];
    *w = 0;
    --w;

    int dig, x_dig, y_dig;
    int buf = 0;

    while (1) {
        if (ptr_x == x && ptr_y == y) {
            break;
        }

        x_dig = 0;
        y_dig = 0;
        if (ptr_x != x) {
            --ptr_x;

            x_dig = to_digit(*ptr_x);
        }
        if (ptr_y != y) {
            --ptr_y;

            y_dig = to_digit(*ptr_y);
        }

        if (x_dig > base || y_dig > base) {
            return -1;
        }

        dig = buf + x_dig + y_dig;
        buf = dig / base;
        dig %= base;

        if (dig < 10) {
            *w = '0' + dig;
        } else {
            *w = dig - 10 + 'a';
        }
        --w;
    }
    
    if (buf == 0) {
        *result = mid_result;
    } else {
        *result = (char*)malloc(((size_t)strlen(mid_result) + 2) * sizeof(char));
        
        if (*result == NULL) {
            return -1;
        }
        (*result)[0] = '1';
        for (size_t i = 0; i <= strlen(mid_result); ++i) {
            (*result)[i+1] = mid_result[i];
        } 
        free(mid_result);
    }
    return 0;
}


int the_greatest_fuckin_sum_function(char** res, int base, int n, ...) {
    if (base < 2 || base > 36) {
        printf("Invalid base\n");
        return -1;
    }

    va_list numbers;
    va_start(numbers, n);

    *res = malloc(1);
    char* mid_res;

    char* left = va_arg(numbers, char*);
    char* right = va_arg(numbers, char*);

    if (col_sum(base, left, right, &mid_res)) {
        return -1;
    }
    (*res) = (char*)realloc((*res), (size_t)(strlen(mid_res) + 1) * sizeof(char));
    if (*res == NULL) {
        return -1;
    }
    strcpy(*res, mid_res);
    free(mid_res);

    for (int i = 2; i < n; ++i) {
    
        right = va_arg(numbers, char*);
        if (col_sum(base, *res, right, &mid_res)) {
            return -1;
        }
        (*res) = (char*)realloc((*res), (size_t)(strlen(mid_res) + 1) * sizeof(char));
        if (*res == NULL) {
            return -1;
        }
        strcpy(*res, mid_res);
        free(mid_res);
        
    }
    va_end(numbers);
    return 0;
}


int main() {
    char* res;
    if (the_greatest_fuckin_sum_function(&res, 16, 4, 
                                            "fe", 
                                            "1",
                                            "1",
                                            "1"
    )) {
        return -1;
    }

    printf("%s\n", res);
    free(res);
}
