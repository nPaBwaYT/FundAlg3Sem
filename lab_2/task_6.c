#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

int roman_to_int(const char *s) {
    int total = 0;
    int lastValue = 0;
    int currentValue;
    
    while (*s) {
        switch (*s) {
            case 'I': currentValue = 1; break;
            case 'V': currentValue = 5; break;
            case 'X': currentValue = 10; break;
            case 'L': currentValue = 50; break;
            case 'C': currentValue = 100; break;
            case 'D': currentValue = 500; break;
            case 'M': currentValue = 1000; break;
            default: return -1; 
        }
        
        if (currentValue > lastValue) {
            total += currentValue - 2 * lastValue; 
        } else {
            total += currentValue;
        }
        
        lastValue = currentValue;
        s++;
    }
    return total;
}

int fibb_to_int(const char *s, unsigned int* res) {
    unsigned int result = 0;
    int fib[32] = {1, 1};
    int i = 2;
    
    while(i < 32) { // формируем числа фиббоначи
        fib[i] = fib[i - 1] + fib[i - 2];
        ++i;
    }
    
    int j = 0;
    for (; s[j] != '\0'; ++j) {
        if (s[j] == '1') {
            result += fib[j];
        }
    }
    if (s[j - 1] == '1') {
        *res = result - fib[j - 1]; 
    } else {
        *res = result;
    }

    return 0;
}

int base_to_int(const char *s, int base) {
    int result = 0;
    while (*s) {
        int value;
        if (isdigit(*s)) {
            value = *s - '0';
        } else if (islower(*s)) {
            value = *s - 'a' + 10;
        } else if (isupper(*s)) {
            value = *s - 'A' + 10;
        } else {
            return -1; 
        }
        
        if (value >= base) {
            return -1; 
        }
        
        result = result * base + value;
        s++;
    }
    return result;
}

int overfscanf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    char buffer[256];
    int scanned = 0;

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'R': { // %Ro
                    if (*(format + 1) == 'o') {
                        format++;
                        fscanf(stream, "%s", buffer);
                        int *result = va_arg(args, int *);
                        *result = roman_to_int(buffer);
                        scanned++;
                    }
                    break;
                }
                case 'Z': { // %Zr
                    if (*(format + 1) == 'r') {
                        format++;
                        fscanf(stream, "%s", buffer);
                        unsigned int *result = va_arg(args, unsigned int *);
                        fibb_to_int(buffer, result);
                        scanned++;
                    }
                    break;
                }
                case 'C': { // %Cv
                    if (*(format + 1) == 'v') {
                        format++;
                        int *result = va_arg(args, int *);
                        int base = va_arg(args, int);
                        if (base < 2 || base > 36) {
                            base = 10; 
                        }
                        fscanf(stream, "%s", buffer);
                        *result = base_to_int(buffer, base);
                        scanned++;
                    } else if (*(format + 1) == 'V') {
                        format++;
                        int *result = va_arg(args, int *);
                        int base = va_arg(args, int);
                        if (base < 2 || base > 36) {
                            base = 10; 
                        }
                        fscanf(stream, "%s", buffer);
                        for (char *p = buffer; *p; p++) {
                            *p = toupper(*p); 
                        }
                        *result = base_to_int(buffer, base);
                        scanned++;
                    }
                    break;
                }
                case 'f': { // %f
                    fscanf(stream, "%s", buffer);
                    float *result = va_arg(args, float *);
                    *result = atof(buffer);
                    scanned++;
                    break;
                }
                case 'd': { // %d
                    fscanf(stream, "%s", buffer);
                    int *result = va_arg(args, int *);
                    *result = atoi(buffer);
                    scanned++;
                    break;
                }
                case 'i': { // %i
                    fscanf(stream, "%s", buffer);
                    int *result = va_arg(args, int *);
                    *result = atoi(buffer);
                    scanned++;
                    break;
                }
                case 'o': { // %o
                    fscanf(stream, "%s", buffer);
                    int *result = va_arg(args, int *);
                    *result = atoi(buffer);
                    scanned++;
                    break;
                }
                case 'x': { // %x
                    fscanf(stream, "%s", buffer);
                    int *result = va_arg(args, int *);
                    *result = atoi(buffer);
                    scanned++;
                    break;
                }
                case 'u': { // %u
                    fscanf(stream, "%s", buffer);
                    int *result = va_arg(args, int *);
                    *result = atoi(buffer);
                    scanned++;
                    break;
                }
                case 'e': { // %e
                    fscanf(stream, "%s", buffer);
                    int *result = va_arg(args, int *);
                    *result = atoi(buffer);
                    scanned++;
                    break;
                }
                case 's': { // %s
                    fscanf(stream, "%s", buffer);
                    char *result = va_arg(args, char *);
                    strcpy(result, buffer);
                    scanned++;
                    break;
                }
                case 'c': { // %c
                    fscanf(stream, "%c", buffer);
                    char* result = va_arg(args, char *);
                    *result = *buffer;
                    scanned++;
                    break;
                }
                case 'p': { // %p 
                    fscanf(stream, "%s", buffer);
                    int *result = va_arg(args, int * );
                    *result = atoi(buffer);
                    scanned++;
                    break;
                }
                default:
                    break;
            }
        } else {
            // Если не форматный символ, просто пропускаем
            fgetc(stream);
        }
        format++;
    }
    
    va_end(args);
    return scanned;
}

int oversscanf(const char* str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    FILE *stream = fmemopen((void *)str, strlen(str), "r");
    char buffer[256];
    int scanned = 0;

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'R': { // %Ro
                    if (*(format + 1) == 'o') {
                        format++;
                        fscanf(stream, "%s", buffer);
                        int *result = va_arg(args, int *);
                        *result = roman_to_int(buffer);
                        scanned++;
                    }
                    break;
                }
                case 'Z': { // %Zr
                    if (*(format + 1) == 'r') {
                        format++;
                        fscanf(stream, "%s", buffer);
                        unsigned int *result = va_arg(args, unsigned int *);
                        if (result == NULL) printf("chee");
                        fibb_to_int(buffer, result);
                        scanned++;
                    }
                    break;
                }
                case 'C': { // %Cv
                    if (*(format + 1) == 'v') {
                        format++;
                        int *result = va_arg(args, int *);
                        int base = va_arg(args, int);
                        if (base < 2 || base > 36) {
                            base = 10; 
                        }
                        fscanf(stream, "%s", buffer);
                        *result = base_to_int(buffer, base);
                        scanned++;
                    } else if (*(format + 1) == 'V') {
                        format++;
                        int *result = va_arg(args, int *);
                        int base = va_arg(args, int);
                        if (base < 2 || base > 36) {
                            base = 10; 
                        }
                        fscanf(stream, "%s", buffer);
                        for (char *p = buffer; *p; p++) {
                            *p = toupper(*p); 
                        }
                        *result = base_to_int(buffer, base);
                        scanned++;
                    }
                    break;
                }
                case 'f': { // %f
                    fscanf(stream, "%s", buffer);
                    float *result = va_arg(args, float *);
                    *result = atof(buffer);
                    scanned++;
                    break;
                }
                case 'd': { // %d
                    fscanf(stream, "%s", buffer);
                    int *result = va_arg(args, int *);
                    *result = atoi(buffer);
                    scanned++;
                    break;
                }
                case 'i': { // %i
                    fscanf(stream, "%s", buffer);
                    int *result = va_arg(args, int *);
                    *result = atoi(buffer);
                    scanned++;
                    break;
                }
                case 'o': { // %o
                    fscanf(stream, "%s", buffer);
                    int *result = va_arg(args, int *);
                    *result = atoi(buffer);
                    scanned++;
                    break;
                }
                case 'x': { // %x
                    fscanf(stream, "%s", buffer);
                    int *result = va_arg(args, int *);
                    *result = atoi(buffer);
                    scanned++;
                    break;
                }
                case 'u': { // %u
                    fscanf(stream, "%s", buffer);
                    int *result = va_arg(args, int *);
                    *result = atoi(buffer);
                    scanned++;
                    break;
                }
                case 'e': { // %e
                    fscanf(stream, "%s", buffer);
                    int *result = va_arg(args, int *);
                    *result = atoi(buffer);
                    scanned++;
                    break;
                }
                case 's': { // %s
                    fscanf(stream, "%s", buffer);
                    char *result = va_arg(args, char *);
                    strcpy(result, buffer);
                    scanned++;
                    break;
                }
                case 'c': { // %c
                    fscanf(stream, "%c", buffer);
                    char* result = va_arg(args, char *);
                    *result = *buffer;
                    scanned++;
                    break;
                }
                case 'p': { // %p 
                    fscanf(stream, "%s", buffer);
                    int *result = va_arg(args, int *);
                    *result = atoi(buffer);
                    scanned++;
                    break;
                }
                default:
                    break;
            }
        } else {
            // Если не форматный символ, просто пропускаем
            fgetc(stream);
        }
        format++;
    }
    
    va_end(args);
    return scanned;
}

int main() {
    FILE* file = fopen("files/task_6_res.txt", "r");
    if (file == NULL){
        printf("file error\n");
        return 1;
    }

    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int num4 = 0;
    float num5 = 0;
    char test_str[100];

    overfscanf(file, "%Ro", &num1);
    overfscanf(file, "%Ro", &num2);
    overfscanf(file, "%Zr", &num3);
    overfscanf(file, "%Cv", &num4, 2);
    overfscanf(file, "%f", &num5);
    overfscanf(file, "%s", test_str);

    printf("%d \n", num1);
    printf("%d \n", num2);
    printf("%d \n", num3);
    printf("%d \n", num4);
    printf("%s \n", test_str);
    printf("%f \n\n", num5);

    const char *str = "C VIII 1101 10101 fuck 2.28";
    oversscanf(str, "%Cv %Ro %Zr %CV %s %f", &num1, 16, &num2, &num3, &num4, 2, test_str, &num5);

    printf("%d \n", num1);
    printf("%d \n", num2);
    printf("%d \n", num3);
    printf("%d \n", num4);
    printf("%s \n", test_str);
    printf("%f \n\n", num5);

    fclose(file);
    return 0;
}