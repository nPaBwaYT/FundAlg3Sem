#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define int long long


enum StatusCode {OK, WRONG_NUMBER_OF_ARGS, ARG_MUST_BE_AN_INTEGER_WITH_CERTAIN_BASE,
INVALID_BASE};


enum StatusCode print_integer(int num, int base) {
    int sign = num / abs(num);
    num = abs(num);
    char digit;
    digit = (num % base) + '0';
    if (digit > '9') {
        digit += 'a' - '9' - 1;
    }
    if (num / base != 0) {
        print_integer(sign * (num / base), base);
    } else if (sign == -1) {
        putchar('-');
    }
    putchar(digit);
    return OK;
}


enum StatusCode read_integer(char* inp, int* number, int base) {
    int result = 0;
    int digit;

    int sign = 1;
    if (*inp == '-') {
        sign = -1;
        ++inp;
    }

    while (*inp != 0) {
        digit = *inp - '0';
        if (digit > 9) {
            if (*inp > 'Z') {
                digit -= 'a' - '9' - 1;
            } else {
                digit -= 'A' - '9' - 1;
            }
        }

        if (digit < 0 || digit >= base) {
            return ARG_MUST_BE_AN_INTEGER_WITH_CERTAIN_BASE;
        }
        result *= base;
        result += digit;
        ++inp;
    }
    *number = sign * result;
    return OK;
}


enum StatusCode main(int argc, char* argv[]) {
    if (argc > 1) {
        printf("Terminated with exit code %d\n", WRONG_NUMBER_OF_ARGS);
        return WRONG_NUMBER_OF_ARGS;
    }

    enum StatusCode code = OK;
    int base;
    int ans = 0;
    int next;
    char inp[32];

    printf("Введите основание системы счисления:\n");
    scanf("%s", inp); 
    
    code = read_integer(inp, &base, 10);
    if (code != OK) {
        printf("Terminated with exit code %d\n", INVALID_BASE);
        return code;
    }
    
    if (base < 2 || base > 36) {
        printf("Terminated with exit code %d\n", INVALID_BASE);
        return INVALID_BASE;
    }

    printf("Введите числа (Stop - конец ввода):\n");
    while (1) {
        scanf("%s", inp); 
        if (!strcmp(inp, "Stop")) {
            break;
        }
        code = read_integer(inp, &next, base);
        if (code != OK) {
            printf("Terminated with exit code %d\n", INVALID_BASE);
            return code;
        }
        if (abs(next) > abs(ans)) {
            ans = next;
        }
    }
    printf("Десятичная: ");
    print_integer(ans, 10);
    putchar('\n');
    printf("Осн. 9: ");
    print_integer(ans, 9);
    putchar('\n');
    printf("Осн. 18: ");
    print_integer(ans, 18);
    putchar('\n');
    printf("Осн. 27: ");
    print_integer(ans, 27);
    putchar('\n');
    printf("Осн. 36: ");
    print_integer(ans, 36);
    putchar('\n');

    if (code != OK) {
        printf("Terminated with exit code %d\n", code);
    }

    return OK;
}