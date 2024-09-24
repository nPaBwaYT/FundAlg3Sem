# define M_E		2.7182818284590452354	/* e */
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

enum StatusCode a(const double* eps, double* ans) {
    *ans = 0;
    double step = 0.1;
    double x = step / 2;
    double prev = -1;
    while (fabs(*ans - prev) > *eps && step > 1e-7) {
        prev = *ans;
        *ans = 0;
        step /= 2;
        x = step / 2;
        while (x <= 1 - step/2 + *eps) {
            *ans += log(1 + x) / x * step;
            x += step;
        }
    }
    return OK;
}

enum StatusCode d(const double* eps, double* ans) {
    *ans = 0;
    double step = 0.1;
    double x = step / 2;
    double prev = -1;
    while (fabs(*ans - prev) > *eps && step > 1e-7) {
        prev = *ans;
        *ans = 0;
        step /= 2;
        x = step / 2;
        while (x <= 1 - step/2 + *eps) {
            *ans += pow(x, x) * step;
            x += step;
        }
    }
    return OK;
}

enum StatusCode c(const double* eps, double* ans) {
    *ans = 0;
    double step = 0.1;
    double x = step / 2;
    double prev = -1;
    while (fabs(*ans - prev) > *eps && step > 1e-7) {
        prev = *ans;
        *ans = 0;
        step /= 2;
        x = step / 2;
        while (x <= 1 - step/2 + *eps) {
            *ans += log(x / (1 + x)) * step;
            x += step;
        }
    }
    return OK;
}

enum StatusCode b(const double* eps, double* ans) {
    *ans = 0;
    double step = 0.1;
    double x = step / 2;
    double prev = -1;
    while (fabs(*ans - prev) > *eps && step > 1e-7) {
        prev = *ans;
        *ans = 0;
        step /= 2;
        x = step / 2;
        while (x <= 1 - step/2 + *eps) {
            *ans += pow(M_E, - x*x/2) * step;
            x += step;
        }
    }
    return OK;
}

enum StatusCode main (int argc, char* argv[]) {
    if (argc != 2) {
        return WRONG_NUMBER_OF_ARGS;
    }
    double eps;
    enum StatusCode code;
    code = read_double(argv[1], &eps);
    if (code != OK) {
        return code;
    }
    if (eps < 0) {
        return EPS_MUST_BE_POSITIVE;
    }

    double var_a, var_b, var_c, var_d;
    code = fmax(a(&eps, &var_a), fmax(b(&eps, &var_b), fmax(c(&eps, &var_c), d(&eps, &var_d))));
    if (code != OK) {
        return code;
    }
    printf("a. %g\nb. %g\nc. %g\nd. %g\n", var_a, var_b, var_c, var_d);
    return(OK);
}