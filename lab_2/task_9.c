#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>


int lgcd(int x, int y) {
    int buff;
    while (y != 0) {
        x = x % y;
        buff = x;
        x = y;
        y = buff;
    }
    return x;
}


int is_final_in_base(int* ans, int base, int n, ...) {

    if (base < 2) {
        printf("Invalid base\n");
        return -1;
    }

    va_list fractions;
    va_start(fractions, n);

    for (int i = 0; i < n; ++i) {
        double fraction = va_arg(fractions, double);

        int numerator = 0;
        int denominator = 1;

        while (fraction != 0) {
            fraction *= 10;
            numerator *= 10;
            numerator += (int)floor(fraction);
            fraction -= floor(fraction);
            denominator *= 10;
        }

        int gcd = lgcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        if (lgcd(base, denominator) == denominator) {
            ans[i] = 1;
        } else {
            ans[i] = 0;
        }
    }

    va_end(fractions);
    return 0;
}


int main() {
    int result[5];

    if (is_final_in_base(result, 16, 5,
                            0.16,
                            0.2,
                            0.375,
                            0.4,
                            0.5
    )) {
        return -1;
    }

    for (int i = 0; i < 5; ++i) {
        printf("%d ", result[i]);
    }
    putchar('\n');
    return 0;
}