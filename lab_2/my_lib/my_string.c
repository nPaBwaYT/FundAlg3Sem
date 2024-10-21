#include <stdlib.h>
#include "my_string.h"


int str_create(str** strptr, char* string) {
    (*strptr) = (str*)malloc(sizeof(str));
    if ((*strptr) == NULL) {
        return -1;
    }

    (*strptr)->size = 1;
    char* ptr = string;

    while (*ptr != 0) {
        ++((*strptr)->size);
        ++ptr;
    }

    (*strptr)->begin = (char*)malloc(((*strptr)->size) * sizeof(char));
    if ((*strptr)->begin == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i < (*strptr)->size; ++i) {
        (*strptr)->begin[i] = string[i];
    }

    return 0;
}


int str_delete(str** targ) {
    free((*targ)->begin);
    free(*targ);
    targ = NULL;

    return 0;
}


int str_concatenate(str* left, str* right, str** result) {
    (*result)->size = left->size + right->size - 1;
    (*result)->begin = (char*)realloc((*result)->begin, (*result)->size * sizeof(char));
    if ((*result)->begin == NULL) {
        return -1;
    }

    for (size_t i = 0; i < left->size - 1; ++i) {
        (*result)->begin[i] = left->begin[i];
    }
    for (size_t j = left->size - 1; j < (*result)->size; ++j) {
        (*result)->begin[j] = right->begin[j - (left->size - 1)];
    }

    return 0;
}