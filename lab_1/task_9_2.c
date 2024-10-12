#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct dynamic_array {
    int *begin;
    size_t size;
};

typedef struct dynamic_array da;


enum StatusCode {OK, WRONG_NUMBER_OF_ARGS, NO_MEM};


enum StatusCode da_init(da* arr, size_t size) {
    arr->begin = malloc(size * sizeof(int));
    arr->size = size;

    if (arr->begin == NULL) {
        return NO_MEM;
    }
    return OK;
}


enum StatusCode da_assign_random(da* arr) {
    int *ptr = arr->begin;
    
    for (size_t i = 0; i < arr->size; ++i) {
        *ptr = (rand() % 2001) - 1000;
        ++ptr;
    }
    return OK;
}


enum StatusCode da_find_closest(da* targ, int value, int *result) {
    *result = *(targ->begin);
    for (int i = 1; i < targ->size; ++i) {
        if (abs(targ->begin[i] - value) < abs(*result - value)) {
            *result = targ->begin[i];
        }
        if (*result = value) {
            break;
        }
    }
    return OK;
}


enum StatusCode main(int argc, char* argv[]) {
    if (argc > 1) {
        printf("Terminated with exit code %d\n", WRONG_NUMBER_OF_ARGS);
        return WRONG_NUMBER_OF_ARGS;
    } 
    
    da a, b, c;
    size_t size_a, size_b;
    size_a = (rand() % 9991) + 10;
    size_b = (rand() % 9991) + 10;
    enum StatusCode code = OK;
    code = fmax(code, fmax(da_init(&a, size_a), fmax(da_init(&b, size_b), da_init(&c, size_a))));
    
    if (code == OK) {
        da_assign_random(&a);
        da_assign_random(&b);
        int d;
        for (int i = 0; i < c.size; ++i) {
            da_find_closest(&b, a.begin[i], &d);
            c.begin[i] = a.begin[i] + d;
            //printf("%d %d %d %d\n", a.begin[i], d, c.begin[i]);
        }
    }

    free(a.begin);
    a.begin = NULL;
    free(b.begin);
    b.begin = NULL;
    free(c.begin);
    c.begin = NULL;

    if (code != OK) {
        printf("Terminated with exit code %d\n", code);
    }
    return code;
}