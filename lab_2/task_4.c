#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


typedef struct point point;
struct point {
    double x, y;
};


int is_convex(int n, ...) {
    va_list coordinates;
    va_start(coordinates, n);

    point first, second, left, center, right;
    center.x = va_arg(coordinates, double);
    center.y = va_arg(coordinates, double);
    right.x = va_arg(coordinates, double);
    right.y = va_arg(coordinates, double);

    first.x = center.x;
    first.y = center.y;
    second.x = right.x;
    second.y = right.y;

    double x1, x2, y1, y2;

    for (int i = 2; i < n; ++i) {
        left = center;
        center = right;
        right.x = va_arg(coordinates, double);
        right.y = va_arg(coordinates, double);
        
        x1 = center.x - left.x;
        y1 = center.y - left.y;

        x2 = center.x - right.x;
        y2 = center.y - right.y;

        if (x1 * y2 - x2 * y1 <= 0) {
            return 0;
        }
    }
    va_end(coordinates);

    x1 = right.x - center.x;
    y1 = right.y - center.y;

    x2 = right.x - first.x;
    y2 = right.y - first.y;


    if (x1 * y2 - x2 * y1 <= 0) {
        return 0;
    }

    x1 = first.x - right.x;
    y1 = first.y - right.y;

    x2 = first.x - second.x;
    y2 = first.y - second.y;

    if (x1 * y2 - x2 * y1 <= 0) {
        return 0;
    }

    return 1;
}


int polynomial(double x, int ind, double* res, ...) {
    *res = 0.;
    va_list coeffs;
    va_start(coeffs, res);

    for (int i = 0; i < ind + 1; ++i) {
        *res *= x;
        *res += va_arg(coeffs, double);
    }

    va_end(coeffs);
    return 0;
}


int to_base(long long num, int base, char* str) {
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char buff[64];
    int i = 0;

    while (num > 0) {
        buff[i++] = digits[num % base];
        num /= base;
    }

    int j = 0;
    while (i > 0) {
        str[j++] = buff[--i];
    }
    str[j] = '\0';
    return 0;
}


int is_kaprekar(int num, int base) {
    long long square = (long long)num * num;
    char square_str[64];

    to_base(square, base, square_str);

    int len = strlen(square_str);
    for (int i = 1; i < len; i++) {
        char left_part[32], right_part[32];

        strncpy(left_part, square_str, i);
        left_part[i] = '\0';
        strcpy(right_part, square_str + i);


        int left = strtol(left_part, NULL, base);
        int right = strtol(right_part, NULL, base);

        if ((right != 0) && (left + right == num)) {
            return 1;
        }
    }

    return 0;
}


int is_kaprekar_nums(int* ans, int base, int count, ...) {

    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        char* str_num = va_arg(args, char*);
        int num = strtol(str_num, NULL, base);


        if (is_kaprekar(num, base)) {
            ans[i] = 1;
        } else {
            ans[i] = 0;
        }
    }

    va_end(args);
    return 0;
}



int main() {
    printf("%d ", is_convex(3, 
                            0.,0.,
                            1.,1.,
                            2.,0.
    ));

    printf("%d ", is_convex(4, 
                            0.,0.,
                            1.,1.,
                            2.,0.,
                            1.,-1.
    ));

    printf("%d ", is_convex(5,
                            0.,0.,
                            1.,1.,
                            2.,0.,
                            1.,-1.,
                            1.,0.
    ));

    putchar('\n');


    double res;
    polynomial(1., 0, &res,
                1.
    );
    printf("%lg ", res);

    polynomial(2., 2, &res,
                2.,
                3.,
                -3.
    );
    printf("%lg ", res);

    polynomial(1., 5, &res,
                1.,
                2.,
                3.,
                4.,
                5.,
                -10.
    );
    printf("%lg ", res);


    putchar('\n');
    int kap[5];
    is_kaprekar_nums(kap, 10, 5, 
                        "7",
                        "17",
                        "45",
                        "56",
                        "115"
    );
    for (int i = 0; i < 5; ++i) {
        printf("%d ", kap[i]);
    }

    putchar('\n');
    return 0;
}