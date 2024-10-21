#ifndef _MY_STRING
#define _MY_STRING

#include <stdlib.h>

typedef struct my_string str;

struct my_string
{
    char* begin;
    size_t size;
};

int str_create(str**, char*);

int str_concatenate(str*, str*, str**);

int str_delete(str**);

#endif