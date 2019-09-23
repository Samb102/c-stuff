#include <stdio.h>

int iterative_factoriel (int a) {
    int res = 1;
    for (int i = a; i > 1; i--) {
        res *= i;
        printf("res : %i \n", res);
    }
    return res;
}

int recursive_factoriel (int a) {
    if (a <= 1) {
      return 1;
    }
    // printf("a : %i \n", a * recursive_factoriel(a - 1));
    return a * recursive_factoriel(a - 1);
}

int main () {
    // printf("%i \n", recursive_factoriel(10));
    printf("%i \n", iterative_factoriel(10));
}


