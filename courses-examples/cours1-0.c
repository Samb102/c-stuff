#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHORT_LENGTH 10

int main() {
    struct Personne {
        int age;
    };

    struct Personne Raymond, Richard;

    Raymond.age = 24;
    Richard = Raymond;
}