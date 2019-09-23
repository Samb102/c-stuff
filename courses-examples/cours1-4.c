#include <stdio.h>
#include <string.h>

void main () {
    int integer = 12;
    void **adress;
    void ***mdr;
    int *pInteger;
    // int **ppInteger;

    pInteger = &integer;
    *adress = &pInteger;
    **mdr = *adress;
    int lol = 14;
    pInteger = &lol;
    // ppInteger = &pInteger;

    printf("%p %p %p\n", *adress, &pInteger, **mdr);
    // &pInteger, pInteger, *pInteger, ppInteger);
}
