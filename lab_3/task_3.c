#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int (*callback)(const char* first_file, const char* second_file);

typedef struct Employee 
{
    float wage;
    char second_name[BUFSIZ];
    char first_name[BUFSIZ];
    unsigned int id;

} Employee;


int string_eq(const char* l, const char* r) {
    return !strcmp(l, r);
}

int validate_str(const char* str) {
    int len_str = strlen(str);

    for (int i = 0; i < len_str; ++i) {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))) {
            return 0;
        }
    }

    return 1;
}

int validate_wage(const char* str) {
    int len_str = strlen(str);
    int was_sep = 0;
    for (int i = 0; i < len_str; ++i) {
        if (str[i] == '.'){
            if (was_sep) {
                return 0;
            } 
            was_sep = 1;
        } else if (('0' > str[i] || str[i] > '9') && str[i] != '.') {
            return 0;
        }
    }
    return 1;
}

int validate_id(const char* str) {
    int len_str = strlen(str);
    for (int i = 0; i < len_str; ++i) {
        if ('0' > str[i] || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int validate_all(const char* id, const char* first_name, const char* second_name, const char* wage) {
    return validate_id(id) && validate_str(first_name) && validate_str(second_name) && validate_wage(wage);
}

int find_flag(const char* arg, const char** f_arr, int f_arr_sz) {
    for (int i =0; i < f_arr_sz; i++) {
        if (string_eq(arg, f_arr[i])) {
            return i;
        }
    }
    return -1;
}

int comparator_a(const void* a, const void* b) {
    Employee* first = (Employee*)a;
    Employee* second = (Employee*)b;
    if (first->wage != second->wage) {
        return (first->wage > second->wage);
    }
    if (strcmp(first->first_name, second->first_name) > 0) {
        return 1;
    } else if (strcmp(first->first_name, second->first_name) < 0) {
        return 0;
    }

    if (strcmp(first->second_name, second->second_name) > 0) {
        return 1;
    } else if (strcmp(first->second_name, second->second_name) < 0) {
        return 0;
    } 

    return (first->id < second->id);
}

int comparator_d(const void* a, const void* b) {
    Employee* first = (Employee*)a;
    Employee* second = (Employee*)b;
    if (first->wage != second->wage) {
        return first->wage < second->wage;
    }

    if (strcmp(first->first_name, second->first_name) > 0) {
        return 0;
    } else if (strcmp(first->first_name, second->first_name) < 0) {
        return 1;
    }

    if (strcmp(first->second_name, second->second_name) > 0) {
        return 0;
    } else if (strcmp(first->second_name, second->second_name) < 0) {
        return 1;
    } 

    return first->id > second->id;
}

int for_a(const char* first_file, const char* second_file) {
    FILE* input_file = fopen(first_file, "r");
    if (input_file  == NULL){
        return 1;
    }

    FILE* output_file = fopen(second_file, "w");
    if (output_file == NULL){
        return 1;
    }

    int index = 0;
    int len = 10;
    Employee *employees = (Employee*)malloc(sizeof(Employee) * len);

    char id[BUFSIZ];
    char first_name[BUFSIZ];
    char second_name[BUFSIZ];
    char wage[BUFSIZ];

    while(1) {
        if (fscanf(input_file, "%s %s %s %s", id, first_name, second_name, wage) == EOF) {
            break;
        }

        if (!validate_all(id, first_name, second_name, wage)) {
            return 1;
        }

        employees[index].id = atoi(id);
        strcpy(employees[index].first_name, first_name);
        strcpy(employees[index].second_name, second_name);
        employees[index].wage = atof(wage);
        index++;

        if (index == len) {
            len *= 2;
            employees = (Employee*)realloc(employees, sizeof(Employee) * len);
        }

    }
    
    qsort(employees, index, sizeof(Employee), comparator_a);

    for (int i; i < index; ++i) {
        fprintf(output_file, "%d %s %s %f\n", employees[i].id, employees[i].first_name, employees[i].second_name, employees[i].wage);
    }

    return 0;
}

int for_d(const char* first_file, const char* second_file) {
    FILE* input_file = fopen(first_file, "r");
    if (input_file  == NULL){
        return 1;
    }

    FILE* output_file = fopen(second_file, "w");
    if (output_file == NULL){
        return 1;
    }

    

    int index = 0;
    int len = 10;
    Employee *employees = (Employee*)malloc(sizeof(Employee) * len);

    char id[BUFSIZ];
    char first_name[BUFSIZ];
    char second_name[BUFSIZ];
    char wage[BUFSIZ];

    while(1) {
        
        if (fscanf(input_file, "%s %s %s %s", id, first_name, second_name, wage) == EOF) {
            break;
        }

        if (!validate_all(id, first_name, second_name, wage)) {
            return 1;
        }

        employees[index].id = atoi(id);
        strcpy(employees[index].first_name, first_name);
        strcpy(employees[index].second_name, second_name);
        employees[index].wage = atof(wage);
        index++;

        if (index == len) {
            len *= 2;
            employees = (Employee*)realloc(employees, sizeof(Employee) * len);
        }

    }
    
    qsort(employees, index, sizeof(Employee), comparator_d);

    for (int i; i < index; ++i) {
        fprintf(output_file, "%d %s %s %f\n", employees[i].id, employees[i].first_name, employees[i].second_name, employees[i].wage);
    }

    return 0;
}

int main(int argc, char *argv[]) {
    const char* flags[] = {"-a", "/a", "-d", "/d"}; 
    callback callbacks[] = {&for_a, &for_d};
    callback callback_finded = 0;

    if (argc != 4) {
        printf("USAGE: <input_file> <flag> <output_file>\n");
        return 1;
    }

    int res = find_flag(argv[2], flags, sizeof(flags) / sizeof(const char*));
    if (res == -1) {
        printf("ERROR: unknown flag\n");
        return 2;
    }

    if (string_eq(argv[1], argv[3])) {
        printf("ERROR: files must be different\n");
        return 3;
    }

    callback_finded = callbacks[res / 2];
    int error = callback_finded(argv[1], argv[3]);
    if (error) {
        printf("ERROR: program has failed\n");
        return 1;
    }
}