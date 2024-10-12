#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define int long long

enum StatusCode {OK, WRONG_NUMBER_OF_ARGS, FIRST_ARG_MUST_BE_AN_INTEGER,
SECOND_ARG_MUST_BE_A_FLAG, WRONG_FLAG, OUT_OF_RANGE};

enum StatusCode read_number(char* inp, int* number) {
    int result = 0;

    int sign = 1;
    if (*inp == '-') {
        sign = -1;
        ++inp;
    }

    while (*inp != 0) {
        if (*inp < '0' || *inp > '9') {
            return FIRST_ARG_MUST_BE_AN_INTEGER;
        }
        result *= 10;
        result += (*inp - '0');
        ++inp;
    }
    *number = sign * result;
    return OK;
}

enum StatusCode multiples(const int* number) {
    if (abs(*number) > 100 || *number == 0) {
        printf("Нет кратных чисел\n");
    } else {
        for (int i = abs(*number); i < 101; i += abs(*number)) {
            printf("%lld\n", i);
        }
    }
    return OK;
}

enum StatusCode is_prime(const int* number) {
    if (*number < 0) {
        printf("Отрицательное число не может быть простым\n");
    } else if (*number < 2){
        printf("Не является ни простым, ни составным\n");
    } else {
        for (int div = 2; div <= sqrt(*number); ++div) {
            if (*number % div == 0) {
                printf("Составное\n");
                return OK;
            }
        }
        printf("Простое\n");
    }
    return OK;
}

enum StatusCode hex(const int* number) {
    char hex_num[8];
    int mask = 0b1111;

    for (int i = 0; i < 8; ++i) {
        hex_num[7-i] = '0' + ((*number >> (4 * i)) & mask);
        if (hex_num[7-i] > '9') {
            hex_num[7-i] += 'A' - '9' - 1;
        }
    }

    char* ptr = hex_num;
    while (*ptr == '0') {++ptr;}
    while (*ptr != 0) {
        printf("%c ", *ptr);
        ++ptr;
    }
    putchar('\n');
    return OK;
}

enum StatusCode exp_tab(const int* number) {
    if (*number < 1 || *number > 10) {
        return OUT_OF_RANGE;
    }

    int exp;
    for (int base = 1; base < 11; ++base) {
        
        for (int i = 1; i <= *number; ++i) {
            putchar('+');
            for (int j = 0; j <= i; ++j) {putchar('-');}
        }
        printf("+\n");

        for (int ind = 1; ind <= *number; ++ind) {
            exp = (int)pow(base, ind);
            printf("|%lld", exp);
            for (int spaces = ind; (int)(pow(10, spaces) > exp); --spaces) {putchar(' ');}
        }
        printf("|\n");
    }

    for (int i = 1; i <= *number; ++i) {
            putchar('+');
            for (int j = 0; j <= i; ++j) {putchar('-');}
        }
        printf("+\n");

    return OK;
}

enum StatusCode sum(const int* number) {
    if (*number < 1) {
        printf("0\n");
        return OK;
    }
    printf("%lld\n", (1 + *number) * (*number) / 2);
    return OK;
}

enum StatusCode fact(const int* number) {
    if (*number < 0) {
        printf("Не определён\n");
        return OK;
    }
    int fact = 1;
    for (int k = 2; k <= *number; ++k) {fact *= k;}
    printf("%lld\n", fact);
    return OK;
}

enum StatusCode main(int argc, char* argv[]) {
    if (argc != 3) {
        return WRONG_NUMBER_OF_ARGS;
    }

    enum StatusCode code;
    int number;
    code = read_number(argv[1], &number);
    if (code != OK) {
        printf("Terminated with exit code %d\n", code);
        return code;
    }

    if (argv[2][0] != '-' && argv[2][0] != '/') {
        printf("Terminated with exit code %d\n", SECOND_ARG_MUST_BE_A_FLAG);
        return SECOND_ARG_MUST_BE_A_FLAG;
    }

    switch (argv[2][1]) 
    {
    case 'h':
        code = multiples(&number);
        break;
    case 'p':
        code = is_prime(&number);
        break;
    case 's':
        code = hex(&number);
        break;
    case 'e':
        code = exp_tab(&number);
        break;
    case 'a':
        code = sum(&number);
        break;
    case 'f':
        code = fact(&number);
        break;
    default:
        code = WRONG_FLAG;
        break;
    }

    if (code != OK) {
        printf("Terminated with exit code %d\n", code);
    }
    return code;
}
