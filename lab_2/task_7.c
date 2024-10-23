#include <stdio.h>
#include <math.h>

typedef double (*func) (double x);


double _y(double x) {
    return 2*x*x + 4*x -3;
}

int binary_search(double x1, double x2, double eps, func f, double* x) {
    if (eps <= 0) {
        printf("eps must be positive\n");
        return -1;
    }

    double left, right;
    left = fmin(x1, x2);
    right = x1 + x2 -left;

    if (f(right) * f(left) > 0) {
        printf("function must intersect x axis odd numder of times on the interval and != const\n");
        return -1;
    }
    double sign = (f(right) - f(left)) / fabs(f(right) - f(left));
    double step = (right - left) / 2;
    *x = left + step;
    double y = f(*x);

    while (fabs(y) > eps) {
        step /= 2;
        if (y > eps) {
            *x -= sign * step;
        } else if (y < -eps) {
            *x += sign * step;
        }

        y = f(*x);
    }

    return 0;
}


int main() {
    double x1, x2, eps, x;
    func f = _y;

    scanf("%lg %lg %lg", &x1, &x2, &eps);

    if (binary_search(x1, x2, eps, f, &x)) {
        return -1;
    }
    printf("%lg\n", x);

    return 0;
}