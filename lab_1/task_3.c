#include <stdio.h>
#include <math.h>
#include <stdlib.h>

enum StatusCode {OK, WRONG_NUMBER_OF_ARGS, ARG_MUST_BE_A_DOUBLE, SECOND_ARG_MUST_BE_A_FLAG,
WRONG_FLAG, EPS_MUST_BE_POSITIVE, ARG_MUST_BE_AN_INTEGER, ARG_MUST_BE_A_NON_ZERO_INTEGER,
TRIANGLE_SIDES_LENGTHS_MUST_BE_POSITIVE};

enum StatusCode read_integer(char* inp, int* number) {
    int result = 0;

    int sign = 1;
    if (*inp == '-') {
        sign = -1;
        ++inp;
    }

    while (*inp != 0) {
        if (*inp < '0' || *inp > '9') {
            return ARG_MUST_BE_AN_INTEGER;
        }
        result *= 10;
        result += (*inp - '0');
        ++inp;
    }
    *number = sign * result;
    return OK;
}

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

enum StatusCode equation(int* argc, char* argv[]) {
    if (*argc != 6) {
        return WRONG_NUMBER_OF_ARGS;
    }

    enum StatusCode code;
    double eps;
    code = read_double(argv[2], &eps);
    if (code != OK) {
        return code;
    }
    if (eps < 0) {
        return EPS_MUST_BE_POSITIVE;
    }
    double a, b, c;
    code = read_double(argv[3], &a);
    if (code != OK) {
        return code;
    }
    code = read_double(argv[4], &b);
    if (code != OK) {
        return code;
    }
    code = read_double(argv[5], &c);
    if (code != OK) {
        return code;
    }
    double solutions[12];
    double buff;
    
    for (int i = 0; i < 6; ++i) {
        if (fabs(a) < eps) {
            solutions[i] = NAN;
            solutions[i+6] = NAN;
        } else {
            solutions[i] = (-b + sqrt(b*b - 4*a*c))/(2*a);
            solutions[i+6] = (-b - sqrt(b*b - 4*a*c))/(2*a);
        }

        printf("%gx^2 %gx %g: %g %g\n", a, b, c, solutions[i], solutions[i+6]);

        buff = b;
        b = a;
        a = buff;
        if (i % 2 == 1) {
            buff = c;
            c = b;
            b = a;
            a = buff;
        }
    }
    
    return OK;
}

enum StatusCode is_multiple(int* argc, char* argv[]) {
    if (*argc != 4) {
        return WRONG_NUMBER_OF_ARGS;
    }

    enum StatusCode code;
    int a, b;
    code = read_integer(argv[2], &a);
    if (code != OK) {
        return code;
    }
    code = read_integer(argv[3], &b);
    if (code != OK) {
        return code;
    }
    if (a == 0 || b == 0) {
        return ARG_MUST_BE_A_NON_ZERO_INTEGER;
    }
    if (a % b == 0) {
        printf("a кратно b\n");
    } else {
        printf("a не кратно b\n");
    }
    return OK;
}

enum StatusCode triangle(int* argc, char* argv[]) {
    if (*argc != 6) {
        return WRONG_NUMBER_OF_ARGS;
    }

    enum StatusCode code;
    double eps;
    code = read_double(argv[2], &eps);
    if (code != OK) {
        return code;
    }
    if (eps < 0) {
        return EPS_MUST_BE_POSITIVE;
    }
    double a, b, c;
    code = read_double(argv[3], &a);
    if (code != OK) {
        return code;
    }
    code = read_double(argv[4], &b);
    if (code != OK) {
        return code;
    }
    code = read_double(argv[5], &c);
    if (code != OK) {
        return code;
    }
    if (a < eps || b < eps || c < eps) {
        return TRIANGLE_SIDES_LENGTHS_MUST_BE_POSITIVE;
    }
    double gr;
    gr = fmax(fmax(a, b), c);
    if ((a + b + c - gr) - gr > eps) {
        printf("треугольник\n");
    } else {
        printf("не треугольник\n");
    }
    return OK;
}

enum StatusCode main(int argc, char* argv[]) {
    if (argc < 4) {
        return WRONG_NUMBER_OF_ARGS;
    }
    if (argv[1][0] != '/' && argv[1][0] != '-') {
        return SECOND_ARG_MUST_BE_A_FLAG;
    }

    switch (argv[1][1]) 
    {
    case 'q':
        return equation(&argc, argv);
    case 'm':
        return is_multiple(&argc, argv);
    case 't':
        return triangle(&argc, argv);

    default:
        return WRONG_FLAG;
    }
}
