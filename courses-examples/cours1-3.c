#include <stdio.h>
#include <string.h>

void copyString (char *src, char *dst) {
    while (*src != '\0') {
        printf("%c %c\n", *dst, *src);
        *dst++ = *src++;
    }
    *dst = *src; // add 0 to end
}

void main () {
    char dst[] = "mdr";
    char src[] = "loll";
    copyString(src, dst);
    printf("%d %d\n", *(src + 4), *(dst + 4));
}
