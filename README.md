# Информация для выполнения лабораторных по фундаментальным алгоритмам
Тут размещена информация необходимая для успешного выполнения лабораторных работ

## Оглавление
1. [Полезные ссылки](#полезные-ссылки)
2. [Общие правила](#общие-правила)
3. [Лабораторные](#лабораторные)
    1. [№1](#1)

## Полезные ссылки
1. [Visual Studio Code](https://code.visualstudio.com/download)
2. [C Documentation](https://en.cppreference.com/w/c)
3. [Ответы на все вопросы](https://yandex.ru/)

## Общие правила

1. Нельзя использовать функцию _exit_ вне функции _main_ (в самой функции _main_ она не имеет смысла, т.к. можно вызвать return).

2. При работе с потоком вывода информации запрещено передавать туда что то кроме переменных или констант.</br>
    Верный вариант:
    ```c
    #include <stdio.h>
    int main(void) {
        int i = 0, j = 1;
        printf("i=%d, j=%d", i, j);
        return 0;
    }
    ```
    Неверный вариант:
    ```c
    #include <stdio.h>
    int main(void) {
        int i = 0, j = 1;
        printf("i=%d, j=%d", i+1, j-i);
        return 0;
    }
    ```

3. Все входные данные программы должны быть проверены на адекватность и корректность, нельзя использовать "сырой" ввод. Также необходимо контролировать количество переданных в командной строке аргументов.</br>
    Верный вариант:
    ```c
    #include <stdio.h>
    int main(int argc, char* argv[]) {
        if (argc > 1) {
            return -1;
        } 
        int i = 0;
        scanf("%d", &i);
        if (i < 100) {
            return 0;
        }
        return -1;
    }
    ```
    Неверный вариант:
    ```c
    #include <stdio.h>
    int main(int argc, char* argv[]) {
        int i = 0;
        scanf("%d", &i);
        return 0;
    } 
    ```

4. Если в коде выделяется динамическая память обязательно необходимо предусматривать ситуации, в которых память не может выделиться или перевыделиться. Также нельзя забывать очищать выделенную память.</br>
    Верный вариант:
    ```c
    #include <stdlib.h>
    int main(void) {
        int* ptr = (int*)malloc(sizeof(int) * 12);
        if (!ptr) {
            return -1;
        }

        ptr = (int*)realloc((void*)ptr, sizeof(int) * 20);
        if (!ptr) {
            return -1;
        }

        free(ptr);
        return 0;
    }
    ```
    Неверный вариант:
    ```c
    #include <stdio.h>
    int main(void) {
        int* ptr = (int*)malloc(sizeof(int) * 12);
        ptr = (int*)realloc((void*)ptr, sizeof(int) * 20);
        return 0;
    }   
    ```

5. При работе с файлами нужно проверять что он открылся и потом закрывать его.</br>
    Верный вариант:
    ```c
    #include <stdio.h>
    int main(void) {
        FILE* fp = fopen("traps.mp4", "r");
        if (!fp) {
            return -1;
        }

        fclose(fp);
        return 0;
    }
    ```
    Неверный вариант:
    ```c
    #include <stdio.h>
    int main(void) {
        FILE* fp = fopen("traps.mp4", "r");
        return 0;
    }
    ```

6. Глобальные переменные использовать нельзя.</br>
    Верный вариант:
    ```c
    int main(void) {
        return 0;
    }
    ```

    Неверный вариант:
    ```c
    int a = 12;

    int main(void) {
        return 0;
    }
    ```

7. Каждая функция должна возвращать код успешности ее выполнения.</br>
    Верный вариант:
    ```c
    #include <stdio.h>
    int foo(int a) {
        if (a > 2) {
            printf("Success");
            return 0;
        }
        return 1;
    }

    int main(void) {
        if (foo(2)) {
            return -1;
        }
        return 0;
    }
    ```

    Неверный вариант:
    ```c
    #include <stdio.h>
    void foo(int a) {
        if (a > 2) {
            printf("Success");
        }
    }

    int main(void) {
        foo(2);
        return 0;
    }
    ```

8. При сравнении чисел с плавающей точкой необходимо задавать допустимую &Delta;.</br>

    Верный вариант:
    ```c
    #include <math.h>
    int equal(double a, double b, double delta) {
        if (abs(a - b) < delta) {
            return 1;
        }
        return 0;
    }

    int main(void) {
        int eq = equal(1.2, 1.3, 0.0001);
        return 0;
    }
    ```

    Неверный вариант:
    ```c
    int equal(double a, double b) {
        if (a == b) {
            return 1;
        }
        return 0;
    }

    int main(void) {
        int eq = equal(1.2, 1.3);
        return 0;
    }
    ```

9. Все передаваемые в функции переменные, которые не предполагается модифицировать, должны иметь модификатор доступа _const_.</br>
    Верный вариант:
    ```c
    #include <string.h>
    #include <stdio.h>
    int str_act(const char* str) {
        printf("%s", str);
        return 0;
    }

    int main(void) {
        str_act("Hello world");
        return 0;
    }
    ```

    Неверный вариант:
    ```c
    #include <string.h>
    #include <stdio.h>
    int str_act(char* str) {
        printf("%s", str);
        return 0;
    }

    int main(void) {
        str_act("Hello world");
        return 0;
    }
    ```

10. Использование оператора _goto_ недопустимо и его наличие означает несдачу лабораторной работы.
## Лабораторные
### №1

[Файл](./Lab1.pdf) с заданием
