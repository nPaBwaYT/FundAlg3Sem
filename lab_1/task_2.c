#include <stdio.h>
#include <math.h>

enum StatusCode {OK, WRONG_NUMBER_OF_ARGS, FIRST_ARG_MUST_BE_A_NOT_NEGATIVE_DOUBLE};

enum StatusCode read_number(char* inp, double* number) {
    double int_part = 0;
    double frac_part = 0;

    while (*inp != '.' && *inp != ',') {
        if (*inp < '0' || *inp > '9' || *inp == 0) {
            
            return FIRST_ARG_MUST_BE_A_NOT_NEGATIVE_DOUBLE;
        }
        int_part *= 10;
        int_part += (*inp - '0');
        ++inp;
    } 
    while (*inp != 0) {++inp;}
    --inp;
    while (*inp != '.' && *inp != ',') {
        if (*inp < '0' || *inp > '9' || *inp == 0) {
            return FIRST_ARG_MUST_BE_A_NOT_NEGATIVE_DOUBLE;
        }
        frac_part += (*inp - '0');
        frac_part /= 10;
        --inp;
    } 
    *number = int_part + frac_part;
    return OK;
}

enum StatusCode e(const double* eps, double result[3]) {
    double first = 0;
    double prev;
    double n = 1;
    do {
        prev = first;
        first = pow(1 + 1/n, n);
        ++n;
    } while (fabs(first - prev) >= *eps && n < 1e7);

    double second = 1;
    double denominator = 1;
    double next = 1;
    n = 2;
    do {
        second += next;
        denominator *= n;
        ++n;
        next = 1 / denominator;
    } while (next > *eps && n < 1e7);

    double third = 2;
    double step = 1;
    int sign = 1;
    do {
        third += sign * step;
        step /= 2;
        if (log(third) - 1 > *eps) {
            sign = -1;
        } else if (log(third) - 1 < -(*eps)) {
            sign = 1;
        } else {
            break;
        }
    } while (fabs(step) > (*eps) / 2);

    result[0] = first;
    result[1] = second;
    result[2] = third;
    return OK;
}

enum StatusCode p(const double* eps, double result[3]) {
    double first = 4;
    double prev;
    double n = 2;
    double numerator_diff = 16;
    double denominator_diff = 4;
    do {
        prev = first;
        numerator_diff = pow(2 * n, 4);
        denominator_diff = pow(2 * n * (2 * n - 1), 2);
        first *= (n - 1) * numerator_diff; 
        first /= (n * denominator_diff);
        ++n;
    } while (fabs(first - prev) >= *eps && n < 1e7);

    double second = 0;
    double next = 4;
    n = 2;
    do {
        second += next;
        next = 4 * pow(-1, n-1) / (2 * n - 1);
        ++n;
    } while (fabs(next) > *eps && n < 1e7);

    double third = 4;
    double step = 1;
    int sign = -1;
    do {
        third += sign * step;
        step /= 2;
        if (sin(third) < *eps) {
            sign = -1;
        } else if (sin(third) > -(*eps)) {
            sign = 1;
        } else {
            break;
        }
    } while (fabs(step) > (*eps) / 2);

    result[0] = first;
    result[1] = second;
    result[2] = third;
    return OK;
}

enum StatusCode ln(const double* eps, const double* ei, double result[3]) {
    double first = 1;
    double prev;
    double n = 2;
    do {
        prev = first;
        first = n * (pow(2, 1 / n) - 1);
        ++n;
    } while (fabs(first - prev) >= *eps && n < 1e7);

    double second = 0;
    double next = 1;
    n = 2;
    do {
        second += next;
        next = pow(-1, n-1) / n;
        ++n;
    } while (fabs(next) > *eps && n < 1e7);

    double third = 2;
    double step = 1;
    int sign = -1;
    do {
        third += sign * step;
        step /= 2;
        if (pow(*ei, third) - 2 > *eps) {
            sign = -1;
        } else if (pow(*ei, third) - 2 < -(*eps)) {
            sign = 1;
        } else {
            break;
        }
    } while (fabs(step) > (*eps) / 2);

    result[0] = first;
    result[1] = second;
    result[2] = third;
    return OK;
}

enum StatusCode sq(const double* eps, double result[3]) {
    double first = -0.5;
    double prev = -0.5;
    double n = 1;
    do {
        prev = first;
        first = first - pow(first, 2) / 2 + 1;
        ++n;
    } while (fabs(first - prev) >= *eps && n < 1e7);

    double second = pow(2, 1./4.);
    prev = 1;
    n = 3;
    do {
        prev = second;
        second *= pow(2, pow(2, -n));
        ++n;
    } while (fabs(second - prev) > *eps && n < 1e7);

    double third = 2;
    double step = 1;
    int sign = -1;
    do {
        third += sign * step;
        step /= 2;
        if (pow(third, 2) - 2 > *eps) {
            sign = -1;
        } else if (pow(third, 2) - 2 < -(*eps)) {
            sign = 1;
        } else {
            break;
        }
    } while (fabs(step) > (*eps) / 2);

    result[0] = first;
    result[1] = second;
    result[2] = third;
    return OK;
}

enum StatusCode main(int argc, char* argv[]) {
    
    if (argc != 2) {
        return WRONG_NUMBER_OF_ARGS;
    }
    
    enum StatusCode code;
    double eps;
    code = read_number(argv[1], &eps);
    if (code != OK) {
        printf("Terminated with exit code %d\n", code);
        return code;
    }
    
    double ei[3];
    code = e(&eps, ei);
    if (code != OK) {
        printf("Terminated with exit code %d\n", code);
        return code;
    }
    double pi[3];
    code = p(&eps, pi);
    if (code != OK) {
        printf("Terminated with exit code %d\n", code);
        return code;
    }
    double ln2[3];
    code = ln(&eps, &ei[2], ln2);
    if (code != OK) {
        printf("Terminated with exit code %d\n", code);
        return code;
    }
    double root2[3];
    code = sq(&eps, root2);
    if (code != OK) {
        printf("Terminated with exit code %d\n", code);
        return code;
    }
    double gamma[3];
    printf("Точность вычислений ограничена 10е7 итераций\n\n");

    printf("ei:    %g | %g | %g\n",ei[0], ei[1], ei[2]);
    printf("pi:    %g | %g | %g\n",pi[0], pi[1], pi[2]);
    printf("ln2:   %g | %g | %g\n",ln2[0], ln2[1], ln2[2]);
    printf("root2: %g | %g | %g\n",root2[0], root2[1], root2[2]);
    return OK;
}