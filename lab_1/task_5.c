#include <stdio.h>
#include <math.h>
#include <stdlib.h>


enum StatusCode {OK, WRONG_NUMBER_OF_ARGS, ARG_MUST_BE_A_DOUBLE, EPS_MUST_BE_POSITIVE};


enum StatusCode read_double(char* inp, double* number) {
    double int_part = 0;
    double frac_part = 0;
    double sign = 1;
    if (*inp == '-') {
        sign = -1;
        ++inp;
    }

    while (*inp != '.' && *inp != ',' && *inp != 0) {
        if (*inp < '0' || *inp > '9') {
            
            return ARG_MUST_BE_A_DOUBLE;
        }
        int_part *= 10;
        int_part += (*inp - '0');
        ++inp;
    }
    if (*inp == 0) {
        *number = sign * int_part;
        return OK;
    }
    while (*inp != 0) {++inp;}
    --inp;
    while (*inp != '.' && *inp != ',') {
        if (*inp < '0' || *inp > '9' || *inp == 0) {
            return ARG_MUST_BE_A_DOUBLE;
        }
        frac_part += (*inp - '0');
        frac_part /= 10;
        --inp;
    } 
    *number = sign * (int_part + frac_part);
    return OK;
}

enum StatusCode a(const double* x, const double* eps, double* ans) {
    *ans = 1;
    double fract = 1;
    double n = 0;
    double numerator_mult;
    double denominator_mult;
    while (fabs(fract) > *eps && n<1e7) {
        ++n;
        numerator_mult = *x;
        denominator_mult = n;
        fract *= (numerator_mult / denominator_mult);
        *ans += fract;
    }
    return OK;
}

enum StatusCode d(const double* x, const double* eps, double* ans) {
    double fract = -1 * (*x) * (*x) / 2;
    *ans = fract;
    double n = 1;
    double numerator_mult;
    double denominator_mult;
    while (fabs(fract) > *eps && n<1e7) {
        ++n;
        numerator_mult = -1 * (2*n-1) * (*x) * (*x);
        denominator_mult = 2*n;
        fract *= (numerator_mult / denominator_mult);
        *ans += fract;
    }
    return OK;
}

enum StatusCode c(const double* x, const double* eps, double* ans) {
    *ans = 1;
    double fract = 1;
    double n = 0;
    double numerator_mult;
    double denominator_mult;
    while (fabs(fract) > *eps && n<1e7) {
        ++n;
        numerator_mult = 3*3*3 * n*n*n * (*x) * (*x);
        denominator_mult = (3*n) * (3*n-1) * (3*n-2);
        fract *= (numerator_mult / denominator_mult);
        *ans += fract;
    }
    return OK;
}

enum StatusCode b(const double* x, const double* eps, double* ans) {
    *ans = 1;
    double fract = 1;
    double n = 0;
    double numerator_mult;
    double denominator_mult;
    while (fabs(fract) > *eps && n<1e7) {
        ++n;
        numerator_mult = -1 * (*x) * (*x);
        denominator_mult = (2*n) * (2*n-1);
        fract *= (numerator_mult / denominator_mult);
        *ans += fract;
    }
    return OK;
}

enum StatusCode main (int argc, char* argv[]) {
    if (argc != 3) {
        return WRONG_NUMBER_OF_ARGS;
    }
    double eps;
    double x;
    enum StatusCode code;
    code = read_double(argv[1], &eps);
    if (code != OK) {
        return code;
    }
    if (eps < 0) {
        return EPS_MUST_BE_POSITIVE;
    }
    code = read_double(argv[2], &x);
    if (code != OK) {
        return code;
    }

    double var_a, var_b, var_c, var_d;
    code = fmax(a(&x, &eps, &var_a), fmax(b(&x, &eps, &var_b), fmax(c(&x, &eps, &var_c), d(&x, &eps, &var_d))));
    if (code != OK) {
        return code;
    }
    printf("a. %g\nb. %g\nc. %g\nd. %g\n", var_a, var_b, var_c, var_d);
    return(OK);
}