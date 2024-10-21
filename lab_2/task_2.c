#include <stdio.h>
#include <stdarg.h>
#include <math.h>


double g_av(int n, ...) {
    double result = 1.;
    
    va_list numbers;
    va_start(numbers, n);
    for (int i = 0; i < n; ++i) {
        result *= va_arg(numbers, double);
    }
    va_end(numbers);
    return sqrt(result);
}


int bin_pow(double base, int ind, double* res) {
    if (ind == 0) {
        *res = 1;
        return 0;
    }
    int _ind = ind;
    if (ind < 0) {
        _ind = ~ind + 1;
    }

    *res = 1.;

    double rec_res;
    bin_pow(base, _ind >> 1, &rec_res);
    *res = rec_res * rec_res;
    if (_ind & 0b1) {
        *res *= base;
    }

    if (ind < 0) {
        *res = 1 / *res;
    }
    return 0;
}


int main() {
    double base;
    int ind;
    double res;
    
    printf("Введите основание и показатель: <double> <int>\n");
    scanf("%lg %d", &base, &ind);
    bin_pow(base, ind, &res);
    printf("%lg\n", res);


    printf("g_av(0) = %lg\ng_av(2, 4., 4.) = %lg\ng_av(5, 1., 2.2, 3., 4., 16.52) = %lg\n", g_av(0), g_av(2, 4., 4.), g_av(5, 1., 2.2, 3., 4., 16.52));
    return 0;
}