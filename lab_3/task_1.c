#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int validate_number(const char* str) {
    int len_str = strlen(str);
    for (int i = 0; i < len_str; ++i) {
        if (str[i] == '-') {
            if (i == 0) {
                continue;
            } else {
                return 0;
            }
        }
        if ('0' > str[i] || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int sub(int a, int b) {
    while (b != 0) {
        int diff = a ^ b;
        int borrow = (~a & b) << 1;

        a = diff;
        b = borrow;
    }
    return a; 
}

int add(int a, int b) {
    while (b != 0) {
        int sum = a ^ b;
        int carry = (a & b) << 1;

        a = sum;
        b = carry;
    }
    return a; 
}

int convert_to_extent(int input, int extent, char* str) {
    if (extent < 1 || extent > 5) {
        return 1;
    }
    unsigned int num = (unsigned int)input;
    char* str_num = malloc(33);
    char* pch = &str_num[33];
    *pch = '\0';
    pch = &pch[-1];
    int temp = 0;
    int mask = sub(2 << sub(extent, 1), 1);
    while(1) {
        temp = (num) & mask;
        num = num >> extent;
        if (0 <= temp && temp <= 9) {
            pch = &pch[-1];
            *pch = add(temp, '0');
        } else {
            // *(--pch) = temp + 'A' - 10;
            pch = &pch[-1];
            *pch = sub(add(temp, 'A'), 10);
        }

        if (num == 0) {
            break;
        }
    }
    strcpy(str, pch);
    free(str_num);
    return 0;
}

int main() {
    char str[33];
    printf("Enter number: ");
    scanf("%s", str);
    if (!validate_number(str)) {
        printf("ERROR: wrong number\n");
        return 1;
    }
    int num = 0;
    num = atoi(str);
    convert_to_extent(num, 1, str); // 255 в 2 -> 11111111
    printf("%s\n", str);
    convert_to_extent(num, 2, str); // 255 в 4 -> 3333
    printf("%s\n", str);
    convert_to_extent(num, 3, str); // 255 в 8 -> 377
    printf("%s\n", str);
    convert_to_extent(num, 4, str); // 255 в 16 -> FF
    printf("%s\n", str);
    convert_to_extent(num, 5, str); // 255 в 32 -> 7V
    printf("%s\n", str);
}