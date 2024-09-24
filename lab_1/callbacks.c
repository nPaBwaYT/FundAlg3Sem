#include <stdio.h>
#include <stdlib.h>

typedef int (*callback) (int a, int b);

int sum(int a, int b) {
    return a+b;
}

int mult(int a, int b) {
    return a*b;
}

int main() {
    callback operations[2];
    operations[0] = sum;
    operations[1] = mult;

    for (int i = 0; i < 2; ++i) {
        printf("%d\n", operations[i](2, 3));
    }
}