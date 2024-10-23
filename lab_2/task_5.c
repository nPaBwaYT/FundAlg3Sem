#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

int compare_check(char* mode1, char* mode2) {
    if (mode1 != NULL) {
        if (strstr(mode1, mode2) != NULL) {
            return 1;
        }
    }
    return 0;
}

void to_lowercase(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

int string_eq(const char* l, const char* r) {
    return !strcmp(l, r);
}

void print_memory_dump_uns_int(unsigned int num, char* result) {
    unsigned char *ptr = (unsigned char*)&num;  // Преобразуем указатель на число в указатель на байты
    char* start_str = result;
    for (int i = 0; i < 4; i++) {
        for (int bit = 7; bit >= 0; bit--) {
            sprintf(result, "%d", (ptr[3 - i] >> bit) & 1);  
            result++;
        }
        strcat(result, " ");  
        result++;
    }
    result = start_str;
}

void print_memory_dump_int(int num, char* result) {
    unsigned char *ptr = (unsigned char*)&num;  // Преобразуем указатель на число в указатель на байты
    char* start_str = result;
    for (int i = 0; i < 4; i++) {
        for (int bit = 7; bit >= 0; bit--) {
            sprintf(result, "%d", (ptr[3 - i] >> bit) & 1);  
            result++;
        }
        strcat(result, " ");  
        result++;
    }
    result = start_str;
}

void print_memory_dump_double(double num, char* result) {
    unsigned char *ptr = (unsigned char*)&num;  // Преобразуем указатель на число в указатель на байты
    char* start_str = result;
    for (int i = 0; i < 8; i++) {
        for (int bit = 7; bit >= 0; bit--) {
            sprintf(result, "%d", (ptr[7 - i] >> bit) & 1);  
            result++;
        }
        strcat(result, " ");  
        result++;
    }
    result = start_str;
}

void print_memory_dump_float(float num, char* result) {
    unsigned char *ptr = (unsigned char*)&num;  // Преобразуем указатель на число в указатель на байты
    char* start_str = result;
    for (int i = 0; i < 4; i++) {
        for (int bit = 7; bit >= 0; bit--) {
            sprintf(result, "%d", (ptr[3 - i] >> bit) & 1);  
            result++;
        }
        strcat(result, " ");  
        result++;
    }
    result = start_str;
}

int validate_number(const char* str) {
    int len_str = strlen(str);
    for (int i = 0; i < len_str; ++i) {
        if (('0' > str[i] || str[i] > '9') && str[i] != '-') {
            return 0;
        }
    }
    return 1;
}

char* int_to_string(int num) {

    int length = 0;
    int temp = num;

    while (temp != 0) {
        length++;
        temp /= 10;
    }


    char* str = (char*)malloc(length + 2); 
    if (str == NULL) {
        return NULL; 
    }

    str[length + 1] = '\0'; 
    str[length] = ' '; 

    for (int i = length - 1; i >= 0; i--) {
        str[i] = (num % 10) + '0';
        num /= 10; 
    }

    return str; 
}

int find_base(const char* num) {
    int len_num = strlen(num);
    int base = 0;
    char buffer = ' ';
    for (int i = 0; i < len_num; ++i) {
        if (num[i] >= 'a' && num[i] <= 'z') {
            buffer = num[i] - 32;

        } else {
            buffer = num[i];
        }
        if (buffer > base) {
            base = buffer;
        }
    }

    if (base >= '0' && base <= '9') {
        base = (base - '0');
    } else if (base >= 'a' && base <= 'z') {
        base = (base - 'a' + 10);
    } else if (base >= 'A' && base <= 'Z') {
        base = (base - 'A' + 10);
    }
    base++;
    return base;
}

int convert_to_int(const char* num, int base) {
    int len_num = strlen(num);
    int ans = 0;
    int extent = 1;
    
    for (int i = len_num - 1; i >= 0; --i) {
        if (num[i] == '-') {
            continue;
        } else if (num[i] >= '0' && num[i] <= '9') {
            ans += (num[i] - '0') * extent;
            extent *= base;
        } else if (num[i] >= 'a' && num[i] <= 'z') {
            ans += (num[i] - 'a' + 10) * extent;
            extent *= base;
        } else if (num[i] >= 'A' && num[i] <= 'Z') {
            ans += (num[i] - 'A' + 10) * extent;
            extent *= base;
        }
    }

    if (num[0] == '-') {
        return -ans;
    } else {
        return ans;
    }
}

int convert_to_base(int number, unsigned int base, char *result, int is_capital) {

    const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned int unsigned_number;
    char buffer[BUFSIZ];
    int index = 0;

    if (number < 0) {
        unsigned_number = (unsigned int)(number); 
    } else {
        unsigned_number = (unsigned int)number;
    }

    if (unsigned_number == 0) {
        result[0] = '0';
        result[1] = '\0';
        return 1;
    }

    while (unsigned_number > 0) {
        buffer[index++] = digits[unsigned_number % base];
        unsigned_number /= base;
    }

    for (int i = 0; i < index; i++) {
        result[i] = buffer[index - i - 1];
    }

    result[index] = '\0'; 
    if (is_capital) {
        to_lowercase(result);
    }
    return 0;
}

int int_to_fibb(int num, char* result) {

    if (num <= 0) {
        return 1;
    }

    int values[num];
    int indx = 1;
    int copy_num = num;
    int fib_sum[num];
    int indx_for_fibb = 0;
    values[0] = 1;
    values[1] = 1;

    while(values[indx] < num) { // формируем числа фиббоначи
        ++indx;
        values[indx] = values[indx - 1] + values[indx - 2];
    }

    while (num > 0) {
        if (num - values[indx] >= 0) {
            num -= values[indx];
            fib_sum[indx_for_fibb] = values[indx];
            indx_for_fibb += 1;
            indx -= 2;
        } else {
            indx -= 1;
        }
    }
    int ind = 0;
    for (int i = 0; i < copy_num; ++i) {
        if (values[i] == fib_sum[indx_for_fibb - ind - 1]) {
            ind++;
            strcat(result, "1");
            if (ind == indx_for_fibb) {
                break;
            }
        } else {
            strcat(result, "0");
        }
    }
    return 0;
}

int romanletter_to_int(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return -1;
    }
}

int roman_to_integer(const char *s) {
    int total = 0;
    int prev_value = 0;
    
    for (int i = strlen(s) - 1; i >= 0; i--) {
        int current_value = romanletter_to_int(s[i]);
        
        if (current_value == -1) {
            return -1;
        }
        if (current_value < prev_value) {
            total -= current_value;
        } else {
            total += current_value;
        }

        prev_value = current_value;
    }
    
    return total;
}

char* print_str_from_mode(FILE* file, char* mode) {
    while (*mode != '\0') {
        if (*mode != '%') {
            fputc(*mode, file);
            mode++;
        } else {
            return mode;
        }
    }
    return mode;
}

int oversprintf(char* file, char* mode_orig,  ...) {
    va_list args;
    char* mode = (char*)malloc(strlen(mode_orig) + 1);
    strcpy(mode, mode_orig);
    mode[strlen(mode_orig) + 1] = '\0';
    va_start(args, mode_orig);
    int check_err = 0;
    char* str = (char*)malloc(BUFSIZ); 
    char* buffer = (char*)malloc(BUFSIZ); 
    while(*mode) {
        if (*mode == '%') {
            mode++;
            switch (*mode) {
                case 'R': { // %Ro
                    if (*(mode + 1) == 'o') {
                        mode++;
                        char* input = va_arg(args, char*);
                        check_err = roman_to_integer(input);
                        if (check_err == -1) {
                            return 1;
                        }
                        sprintf(buffer, "%d", check_err);
                        strcat(file, buffer);
                    }
                } break;
                case 'Z': { // %Zr
                    if (*(mode + 1) == 'r') {
                        mode++;
                        int num = va_arg(args, int);
                        check_err = int_to_fibb(num, str);
                        if (check_err) {
                            return 1;
                        }
                        sprintf(buffer, "%s1", str);
                        strcat(file, buffer);
                    }
                } break;
                case 'C': { // %Cv
                    if (*(mode + 1) == 'v') {
                        mode++;
                        int num = va_arg(args, int);
                        int base = va_arg(args, int);
                        if (base > 36 || base < 2) {
                            sprintf(buffer, "%d", num);
                            strcat(file, buffer);
                            return 0;
                        }
                        char result[BUFSIZ];
                        check_err = convert_to_base(num, base, result, 1);
                        if (check_err) {
                            return 1;
                        }
                        sprintf(buffer, "%s", result);
                        strcat(file, buffer);
                    } else if (*(mode + 1) == 'V') {
                        mode++;
                        int num = va_arg(args, int);
                        int base = va_arg(args, int);
                        if (base > 36 || base < 2) {
                            sprintf(buffer, "%d", num);
                            strcat(file, buffer);
                            return 0;
                        }
                        char result[BUFSIZ];
                        check_err = convert_to_base(num, base, result, 0);
                        if (check_err) {
                            return 1;
                        }
                        sprintf(buffer, "%s", result);
                        strcat(file, buffer);
                    }
                } break;
                case 't': { // %to
                    if (*(mode + 1) == 'o') {
                        mode++;
                        char* input = va_arg(args, char*);
                        int base = va_arg(args, int);
                        if (find_base(input) > base) {
                            return 1;
                        }
                        int result;
                        result = convert_to_int(input, base);
                        sprintf(buffer, "%d", result);
                        strcat(file, buffer);
                    }
                } break;
                case 'T': { // %TO
                    if (*(mode + 1) == 'O') {
                        mode++;
                        char* input = va_arg(args, char*);
                        int base = va_arg(args, int);
                        if (find_base(input) > base) {
                            return 1;
                        }
                        int result;
                        result = convert_to_int(input, base);
                        sprintf(buffer, "%d", result);
                        strcat(file, buffer);
                    }
                } break;
                case 'm': { 
                    if (*(mode + 1) == 'i') { // %mi
                        mode++;
                        int num = va_arg(args, int);
                        char result[BUFSIZ];
                        print_memory_dump_int(num, result);
                        sprintf(buffer, "%s", result);
                        strcat(file, buffer);
                    } else if (*(mode + 1) == 'u') { // %mu
                        mode++;
                        int num = va_arg(args, int);
                        if (num < 0) {
                            return 1;
                        }
                        char result[BUFSIZ];
                        print_memory_dump_uns_int(num, result);
                        sprintf(buffer, "%s", result);
                        strcat(file, buffer);
                    } else if (*(mode + 1) == 'f') { // %mf
                        mode++;
                        float num = va_arg(args, double);
                        char result[BUFSIZ];
                        print_memory_dump_float(num, result);
                        sprintf(buffer, "%s", result);
                        strcat(file, buffer);
                    } else if (*(mode + 1) == 'd') { // %md
                        mode++;
                        double num = va_arg(args, double);
                        char result[BUFSIZ];
                        print_memory_dump_double(num, result);
                        sprintf(buffer, "%s", result);
                        strcat(file, buffer);
                    }
                } break;
                case 'd': {
                    int num = va_arg(args, int);
                    sprintf(buffer, "%d", num);
                    strcat(file, buffer);
                } break;
                case 'i': {
                    int num = va_arg(args, int);
                    sprintf(buffer, "%i", num);
                    strcat(file, buffer);
                } break;
                case 'o': {
                    int num = va_arg(args, int);
                    sprintf(buffer, "%o", num);
                    strcat(file, buffer);
                } break;
                case 'x': {
                    int num = va_arg(args, int);
                    sprintf(buffer, "%x", num);
                    strcat(file, buffer);
                } break;
                case 'u': {
                    int num = va_arg(args, int);
                    sprintf(buffer, "%u", num);
                    strcat(file, buffer);
                } break;
                case 'f': {
                    double num = va_arg(args, double);
                    sprintf(buffer, "%f", num);
                    strcat(file, buffer);
                } break;
                case 'e': {
                    double num = va_arg(args, double);
                    sprintf(buffer, "%e", num);
                    strcat(file, buffer);
                } break;
                case 'E': {
                    double num = va_arg(args, double);
                    sprintf(buffer, "%E", num);
                    strcat(file, buffer);
                } break;
                case 'g': {
                    double num = va_arg(args, double);
                    sprintf(buffer, "%g", num);
                    strcat(file, buffer);
                } break;
                case 'G': {
                    double num = va_arg(args, double);
                    sprintf(buffer, "%G", num);
                    strcat(file, buffer);
                } break;
                case 'c': {
                    char num = va_arg(args, int);
                    sprintf(buffer, "%c", num);
                    strcat(file, buffer);
                } break;
                case 's': {
                    char* num = va_arg(args, char*);
                    sprintf(buffer, "%s", num);
                    strcat(file, buffer);
                } break;
                case 'p': {
                    int num = va_arg(args, int);
                    sprintf(buffer, "%p", &num);
                    strcat(file, buffer);
                } break;
                case '%': {
                    sprintf(buffer, "%c", '%');
                    strcat(file, buffer);
                } break;
                default:
                    break;
            }
        }
        else {
            sprintf(buffer, "%c", *mode);
            strcat(file, buffer);
        }
        mode++;
    }

    va_end(args);
    return 0;
}

int overfprintf(FILE* file, char* mode_orig,  ...) {
    va_list args;
    char* mode = (char*)malloc(strlen(mode_orig) + 1);
    strcpy(mode, mode_orig);
    mode[strlen(mode_orig) + 1] = '\0';
    va_start(args, mode_orig);
    int check_err = 0;
    char* str = (char*)malloc(BUFSIZ); 
    while(*mode) {
        if (*mode == '%') {
            mode++;
            switch (*mode) {
                case 'R': { // %Ro
                    if (*(mode + 1) == 'o') {
                        mode++;
                        char* input = va_arg(args, char*);
                        check_err = roman_to_integer(input);
                        if (check_err == -1) {
                            return 1;
                        }
                        fprintf(file, "%d", check_err);
                    }
                } break;
                case 'Z': { // %Zr
                    if (*(mode + 1) == 'r') {
                        mode++;
                        int num = va_arg(args, int);
                        check_err = int_to_fibb(num, str);
                        if (check_err) {
                            return 1;
                        }
                        fprintf(file, "%s1", str);
                    }
                } break;
                case 'C': { // %Cv
                    if (*(mode + 1) == 'v') {
                        mode++;
                        int num = va_arg(args, int);
                        int base = va_arg(args, int);
                        if (base > 36 || base < 2) {
                            fprintf(file, "%d", num);
                            return 0;
                        }
                        char result[BUFSIZ];
                        check_err = convert_to_base(num, base, result, 1);
                        if (check_err) {
                            return 1;
                        }
                        fprintf(file, "%s", result);
                    } else if (*(mode + 1) == 'V') {
                        mode++;
                        int num = va_arg(args, int);
                        int base = va_arg(args, int);
                        if (base > 36 || base < 2) {
                            fprintf(file, "%d", num);
                            return 0;
                        }
                        char result[BUFSIZ];
                        check_err = convert_to_base(num, base, result, 0);
                        if (check_err) {
                            return 1;
                        }
                        fprintf(file, "%s", result);
                    }
                } break;
                case 't': { // %to
                    if (*(mode + 1) == 'o') {
                        mode++;
                        char* input = va_arg(args, char*);
                        int base = va_arg(args, int);
                        if (find_base(input) > base) {
                            return 1;
                        }
                        int result;
                        result = convert_to_int(input, base);
                        fprintf(file, "%d", result);
                    }
                } break;
                case 'T': { // %to
                    if (*(mode + 1) == 'O') {
                        mode++;
                        char* input = va_arg(args, char*);
                        int base = va_arg(args, int);
                        if (find_base(input) > base) {
                            return 1;
                        }
                        int result;
                        result = convert_to_int(input, base);
                        fprintf(file, "%d", result);
                    }
                } break;
                case 'm': { 
                    if (*(mode + 1) == 'i') { // %mi
                        mode++;
                        int num = va_arg(args, int);
                        char result[BUFSIZ];
                        print_memory_dump_int(num, result);
                        fprintf(file, "%s", result);
                    } else if (*(mode + 1) == 'u') { // %mu
                        mode++;
                        int num = va_arg(args, int);
                        if (num < 0) {
                            return 1;
                        }
                        char result[BUFSIZ];
                        print_memory_dump_uns_int(num, result);
                        fprintf(file, "%s", result);
                    } else if (*(mode + 1) == 'f') { // %mf
                        mode++;
                        float num = va_arg(args, double);
                        char result[BUFSIZ];
                        print_memory_dump_float(num, result);
                        fprintf(file, "%s", result);
                    } else if (*(mode + 1) == 'd') { // %md
                        mode++;
                        double num = va_arg(args, double);
                        char result[BUFSIZ];
                        print_memory_dump_double(num, result);
                        fprintf(file, "%s", result);
                    }
                } break;
                case 'd': {
                    int num = va_arg(args, int);
                    fprintf(file, "%d", num);
                } break;
                case 'i': {
                    int num = va_arg(args, int);
                    fprintf(file, "%i", num);
                } break;
                case 'o': {
                    int num = va_arg(args, int);
                    fprintf(file, "%o", num);
                } break;
                case 'x': {
                    int num = va_arg(args, int);
                    fprintf(file, "%x", num);
                } break;
                case 'u': {
                    int num = va_arg(args, int);
                    fprintf(file, "%u", num);
                } break;
                case 'f': {
                    double num = va_arg(args, double);
                    fprintf(file, "%f", num);
                } break;
                case 'e': {
                    double num = va_arg(args, double);
                    fprintf(file, "%e", num);
                } break;
                case 'E': {
                    double num = va_arg(args, double);
                    fprintf(file, "%E", num);
                } break;
                case 'g': {
                    double num = va_arg(args, double);
                    fprintf(file, "%g", num);
                } break;
                case 'G': {
                    double num = va_arg(args, double);
                    fprintf(file, "%G", num);
                } break;
                case 'c': {
                    char num = va_arg(args, int);
                    fprintf(file, "%c", num);
                } break;
                case 's': {
                    char* num = va_arg(args, char*);
                    fprintf(file, "%s", num);
                } break;
                case 'p': {
                    int num = va_arg(args, int);
                    fprintf(file, "%p", &num);
                } break;
                case '%': {
                    fprintf(file, "%c", '%');
                } break;
                default:
                    break;
            }
        }
        else {
            // Если не форматный символ, просто печатаем его
            fputc(*mode, file);
        }
        mode++;
    }

    va_end(args);
    return 0;
}

int main() {

    FILE* file = fopen("files/task_5_out.txt", "w");
    if (file == NULL){
        printf("file error\n");
        return 1;
    }
    int error_code = 0;
    int error_code_str = 0;
    error_code += overfprintf(file, "roman - %Ro\n", "MIX", 10); 
    error_code += overfprintf(file, "to - %to\n", "10", 16); 
    error_code += overfprintf(file, "mi - %mi\n", 10); 
    if (error_code) {
        printf("error\n");
        return 1;
    }

    char str[BUFSIZ];
    error_code_str += oversprintf(str, "zekerfov - %Zr\n", 10); 
    error_code_str += oversprintf(str, "convert - %CV\n", 10); 
    error_code_str += oversprintf(str, "dump double - %md\n", -1.0246); 
    error_code_str += oversprintf(str, "string - %s\n", "meow"); 
    if (error_code_str) {
        printf("error\n");
        return 1;
    }
    printf("from oversprintf:\n%s\n", str);
    fclose(file);
    return 0;
}