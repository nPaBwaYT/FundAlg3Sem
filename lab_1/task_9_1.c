#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10000


enum StatusCode {OK, WRONG_NUMBER_OF_ARGS};


enum StatusCode extremums(long long array[ARRAY_SIZE], long long** array_min, long long** array_max) {
    long long *ptr = array;
    *array_min = array;
    *array_max = array;

    for (int i = 1; i < ARRAY_SIZE; ++i) {
        ++ptr;
        if (*ptr > **array_max) {
            *array_max = ptr;
        }
        if (*ptr < **array_min) {
            *array_min = ptr;
        }
    }

    return OK;
}

enum StatusCode main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Terminated with exit code %d\n", WRONG_NUMBER_OF_ARGS);
        return WRONG_NUMBER_OF_ARGS;
    } 
    long long a, b;

    char* endptr = argv[1];

    while (*endptr != 0) {++endptr;}
    a = strtoll(argv[1], &endptr, 10);

    endptr = argv[2];
    while (*endptr != 0) {++endptr;}
    b = strtoll(argv[2], &endptr, 10);

    long long array[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = (rand() % (1 + b - a)) + a;
    }

    long long *array_min, *array_max;
    extremums(array, &array_min, &array_max);
    printf("%Ld %Ld\n", *array_min, *array_max);

    return OK;
}