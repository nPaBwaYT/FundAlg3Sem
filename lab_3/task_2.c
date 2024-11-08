#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

typedef double (*norma)(double* x, int n);

typedef struct vector {
    int n;
    double* x; 
} vector;

int validate_number(const char* str) {
    int len_str = strlen(str);
    for (int i = 0; i < len_str; ++i) {
        if ('0' > str[i] || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int validate_float(const char* str) {
    int len_str = strlen(str);
    int was_sep = 0;
    for (int i = 0; i < len_str; ++i) {
        if (str[i] == '-') {
            if (i == 0) {
                continue;
            } else {
                return 0;
            }
        }
        if (str[i] == '.' || str[i] == ','){
            if (was_sep) {
                return 0;
            } 
            was_sep = 1;
        } else if (('0' > str[i] || str[i] > '9') && str[i] != '.' && str[i] != ',') {
            return 0;
        }
    }
    return 1;
}

double first_norma(double* x, int n) {
    if (n <= 0) {
        return -1;
    }
    double max = 0;
    for (int i = 0; i < n; ++i) {
        int is_negative = x[i] < 0 ? -1: 1;
        if (x[i] * is_negative > max) {
            max = x[i];
        }
    }
    return max;
}

double calculate_sum(double* x, int n, int p) {
    if (n <= 0 || p <= 0) {
        return -1;
    }
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        int is_negative = x[i] < 0 ? -1: 1;
        sum += pow(is_negative * x[i], p);
    }
    sum = pow(sum, 1.0 / p);
    return sum;
}

double second_norma(double* x, int n) {
    int p = 2;
    return calculate_sum(x, n, p);
}

double mul_matrix_vec(double* A, double* x, int n) {
    double new_x[n];
    double result = 0;
    for (int i = 0; i < n ; ++i) {
        new_x[i] = 0;
        for (int j = 0; j < n; ++j) {
            new_x[i] += A[(i * n) + j] * x[j];
        }
    }
    
    for (int i = 0; i < n; ++i) {
        result += new_x[i] * x[i];
    }
    return result;
}

double third_norma(double* x, int n) {
    double A[] = {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };
    double res = pow(mul_matrix_vec(A, x, n), 0.5);
    return res;
}

int display_result(int norm_vectors_count[], vector** max_vectors, int num_norm, int n) {
    for (int i = 0; i < num_norm; ++i) {
        printf("There are %d vectors for %d norm:\n", norm_vectors_count[i], i + 1);
        for (int j = 0; j < norm_vectors_count[i]; ++j) {
            printf("* (");
            for (int z = 0; z < n; ++z) {
                if (z == n - 1) {
                    printf("%.3f", max_vectors[i][j].x[z]);
                } else {
                    printf("%.3f, ", max_vectors[i][j].x[z]);
                }
            }
            printf(")\n");
        }
        printf("\n");
    }
    return 0;
}

vector** find_max(int n, int num_vec, int num_norm, ...) {

    if (n <= 0 || num_vec <= 0 || num_norm <= 0) {
        return NULL;
    }
    vector vectors[num_vec];
    norma normas[num_norm];

    va_list args;
    va_start(args, num_norm);

    for (int i = 0; i < num_vec; ++i) {
        vectors[i].n = n;
        vectors[i] = va_arg(args, vector);
    }

    for (int i = 0; i < num_norm; ++i) {
        normas[i] = va_arg(args, norma);
    }
    
    int norm_vectors_count[num_norm]; // содержит количество максимальных векторов для каждой нормы
    vector **max_vectors = malloc(num_norm * sizeof(vector *));// содержит максимальные векторы для каждой нормы
    for (int i = 0; i < num_norm; i++) {
        max_vectors[i] = malloc(num_vec * sizeof(int));
    }
    for (int i = 0; i < num_norm; ++i) {    

        double max = normas[i](vectors[0].x, n);
        int indx = 0;
        for (int j = 0; j < num_vec; ++j) {

            if (max < normas[i](vectors[j].x, n)) {
                max_vectors[i][0] = vectors[j];
                indx = 1;
            } else if (max == normas[i](vectors[j].x, n)) {
                max_vectors[i][indx] = vectors[j];
                indx++;
            }

        }
        norm_vectors_count[i] = indx;
    }

    va_end(args);

    display_result(norm_vectors_count, max_vectors, num_norm, n);

    return max_vectors;
} 

double* create_vector(int n, double* x, vector* vec) {
    vec->n = n;
    vec->x = (double*)malloc(sizeof(double) * n);
    for (int i = 0; i < n; ++i) {
        vec->x[i] = x[i];
    }
    return vec->x;
}

int main() {
    vector x1;
    vector x2;
    vector x3;
    char buff[15]; 
    int n = 0; 
    printf("Enter dimension: ");
    scanf("%s", buff);
    if (!validate_number(buff)) {
        printf("ERROR: dimension must be number greater than 0\n");
        return 1;
    }
    n = atoi(buff);

    double coords[3][n];

    printf("Enter 3 vector with %d dim:\n", n);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%s", buff);
            if (!validate_float(buff)) {
                printf("ERROR: wrong number\n");
                return 1;
            }
            coords[i][j] = atoi(buff);
        }
    }
    
    double* pch1 = create_vector(n, coords[0], &x1);
    double* pch2 = create_vector(n, coords[1], &x2);
    double* pch3 = create_vector(n, coords[2], &x3);

    vector** vectors = find_max(n, 3, 3, x1, x2, x3, &first_norma, &second_norma, &third_norma);
    free(pch1);
    free(pch2);
    free(pch3);
    free(vectors);
    return 0;
}