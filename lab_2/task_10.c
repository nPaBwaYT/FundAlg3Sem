#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>


double bin_pow(double base, int ind) {
    double res;

    if (ind == 0) {
        return 1;
    }
    int _ind = ind;
    if (ind < 0) {
        _ind = ~ind + 1;
    }

    res = 1.;

    double rec_res = bin_pow(base, _ind >> 1);
    
    res = rec_res * rec_res;
    if (_ind & 0b1) {
        res *= base;
    }

    if (ind < 0) {
        res = 1 / res;
    }
    return res;
}


int fact(int n) {
    if (n == 0) {
        return 1;
    }
    return n * fact(n-1);
}


int c(int n, int k) {
    return (fact(n) / fact(k) / fact (n-k));
}


int poly_reexpand(double epsilon, double a, double **coefficients, int power, ...) {
    *coefficients = (double*)malloc((power + 1) * sizeof(double));

    if (*coefficients == NULL) {
        return -1;
    }

    va_list args;
    va_start(args, power);

    double initial_coeffs[power + 1];

    for (int i = 0; i <= power; ++i) {
        initial_coeffs[i] = va_arg(args, double);
        (*coefficients)[i] = 0.;
    }
    va_end(args);

    double gi;               // 1 + x + x^2 = g1 + g2(x-a) + g3(x^2 - 2ax + a^2) = (g1 - g2a + g3a^2) + (g2 - 2g3a)x + g3x^2

    for (int i = power; i >= 0; --i) {
        gi = initial_coeffs[i] - (*coefficients)[i];
        (*coefficients)[i] = gi;

        for (int j = i-1; j >= 0; --j) {
            (*coefficients)[j] += ((double)c(i, j) * gi * bin_pow(-a, (i - j)));
        }
    }

    for (int i = 0; i <= power; i++) {
        if (fabs((*coefficients)[i]) < epsilon) {
            (*coefficients)[i] = 0.0;
        }
    }


    return 0;
}


int main() {
    double *coefficients;
    
    if (poly_reexpand(0.001, 1.5, &coefficients, 4,
                        1.,
                        2.5,
                        -4.,
                        2.,
                        1.
    )) {
        return -1;
    }

    for (int i = 0; i <= 4; ++i) {
        printf("%lg ", coefficients[i]);
    }
    putchar('\n');

    free(coefficients);

    return 0;
}