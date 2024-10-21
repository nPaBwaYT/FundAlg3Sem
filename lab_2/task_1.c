#include "my_lib/my_string.h"
#include "stdio.h"


int is_num(char c) {
    return (c >= '0' && c <= '9');
}

int is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); 
}

int is_alphanum(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}


int read_uint(char* inp, unsigned int* number) {
    unsigned int result = 0;

    while (*inp != 0) {
        if (*inp < '0' || *inp > '9') {
            return -1;
        }
        result *= 10;
        result += (*inp - '0');
        ++inp;
    }
    *number = result;
    return 0;
}


int length(str* strptr, int* len) {
    *len = strptr->size - 1;
    return 0;
}


int reversed(str* strptr, str** reversed_str) {
    char buff[strptr->size];
    for (size_t i = 0; i < strptr->size - 1; ++i) {
        buff[i] = strptr->begin[strptr->size - 2 - i];
    }
    buff[strptr->size - 1] = 0;

    if (str_create(reversed_str, buff)) {
        return -1;
    }

    return 0;
}


int upper_even(str* strptr, str** upper_even_str) {
    char buff[strptr->size];

    for (size_t i = 0; i < strptr->size; ++i) {
        if ((i % 2 == 1) && ((strptr->begin[i] >= 'a') && (strptr->begin[i] <= 'z'))) {
            (buff[i] = strptr->begin[i] + ('A' - 'a'));
        }
        else {
            buff[i] = strptr->begin[i];
        }
    }

    if (str_create(upper_even_str, buff)) {
        return -1;
    }

    return 0;
}


int num_al_other(str* strptr, str** num_al_other_str) {
    char buff[strptr->size];
    char* w = buff;

    for (size_t i = 0; i < strptr->size; ++i) {
        if (is_num(strptr->begin[i])) {
            *w = strptr->begin[i];
            ++w;
        }
    }
    for (size_t i = 0; i < strptr->size; ++i) {
        if (is_alpha(strptr->begin[i])) {
            *w = strptr->begin[i];
            ++w;
        }
    }
    for (size_t i = 0; i < strptr->size; ++i) {
        if (!is_alphanum(strptr->begin[i])) {
            *w = strptr->begin[i];
            ++w;
        }
    }

    if (str_create(num_al_other_str, buff)) {
        return -1;
    }

    return 0;
}


int rand_concatenate(int argc, str** strings, str** concatenated_str) {
    str* left;
    if (str_create(&left, "")) {
        return -1;
    }
    if (str_create(concatenated_str, "")) {
        return -1;
    }

    str* buff;
    int idx;
    
    for (int i = 0; i < argc; ++i) {
        buff = *concatenated_str;
        *concatenated_str = left;
        left = buff;

        idx = rand() % (argc - i);
        if (str_concatenate(left, strings[idx], concatenated_str)) {
            return -1;
        }

        buff = strings[idx];
        strings[idx] = strings[argc - i - 1];
        strings[argc - i - 1] = buff;
    }

    str_delete(&left);

    return 0;
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("error 1: Wrong number of arguments\n");
        return 1;
    }

    if (argv[1][0] != '-') {
        printf("error 2: First argument must be a flag\n");
        return 2;
    }

    str* strptr = NULL;
    str** strings = NULL;

    switch (argv[1][1]) 
    {
    case 'l':
        if (argc != 3) {
            printf("error 1: Wrong number of arguments\n");
            return 1;
        }

        if (str_create(&strptr, argv[2])) {
            return -1;
        }
        
        int len;
        if (length(strptr, &len)) {
            return -1;
        }
        printf("%d\n", len);

        str_delete(&strptr);

        break;

    case 'r':
        if (argc != 3) {
            printf("error 1: Wrong number of arguments\n");
            return 1;
        }

        if (str_create(&strptr, argv[2])) {
            return -1;
        }
        str* reversed_str = NULL;
        if (reversed(strptr, &reversed_str)) {
            return -1;
        }

        printf("%s\n", reversed_str->begin);
        str_delete(&reversed_str);

        str_delete(&strptr);

        break;

    case 'u':
        if (argc != 3) {
            printf("error 1: Wrong number of arguments\n");
            return 1;
        }

        if (str_create(&strptr, argv[2])) {
            return -1;
        }
        str* upper_even_str = NULL;
        if (upper_even(strptr, &upper_even_str)) {
            return -1;
        }

        printf("%s\n", upper_even_str->begin);
        str_delete(&upper_even_str);

        str_delete(&strptr);

        break;

    case 'n':
        if (argc != 3) {
            printf("error 1: Wrong number of arguments\n");
            return 1;
        }

        if (str_create(&strptr, argv[2])) {
            return -1;
        }
        str* num_al_other_str = NULL;
        if (num_al_other(strptr, &num_al_other_str)) {
            return -1;
        }

        printf("%s\n", num_al_other_str->begin);
        str_delete(&num_al_other_str);

        str_delete(&strptr);

        break;

    case 'c':
        if (argc < 4) {
            printf("error 1: Wrong number of arguments\n");
            return 1;
        }

        unsigned int zxcur_seed;

        if (read_uint(argv[2], &zxcur_seed)) {
            printf("error 4: Second argument must be uint\n");
            return 4;
        }

        srand(zxcur_seed);

        strings = malloc((argc - 3) * sizeof(str*));
        if (strings == NULL) {
            return -1;
        }

        for (int i = 0; i < argc - 3; ++i) {
            if (str_create(&strings[i], argv[i + 3])) {
                return -1;
            }
        }

        str* concatenated_str;

        if (rand_concatenate(argc - 3, strings, &concatenated_str)) {
            return -1;
        }

        printf("%s\n", concatenated_str->begin);
        str_delete(&concatenated_str);

        for (int i = 0; i < argc - 3; ++i) {
            str_delete(&strings[i]);
        }
        free(strings);

        break;

    default:
        printf("error 3: Flag is not supported\n");
        return 3;
    }

    return 0;
}