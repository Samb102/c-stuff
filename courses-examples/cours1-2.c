#include <stdio.h>
#include <string.h>
#include <stdlib.h>

short int cipherValue (char cipher) {
    switch (cipher) {
        case 'M': return 1000;
        case 'D': return 500;
        case 'C': return 100;
        case 'L': return 50;
        case 'X': return 10;
        case 'V': return 5;
        case 'I': return 1;
    }
}

int parseRomanCiphers (char *ciphers) {
    int res;
    const short int length = strlen(ciphers);
    short int i = length - 1;
    short int cipher;
    short int nextCipher;
 
    while (i >= 0) {
        cipher = cipherValue(ciphers[i]);
        nextCipher = cipherValue(ciphers[i - 1]);

        if (i != 0 && cipher > nextCipher) {
            res += cipher - nextCipher;
            i = i - 2;
        } else {
            res += cipher;
            i--;
        }
    }

    return res;
}

void main (int argc, char **argv) {
    char *romanValue = NULL;
    char defaultValue[] = "MMMCMXCIX";
    char *value = NULL;

    value = (argc > 1) ? argv[1] : defaultValue;

    romanValue = malloc((strlen(value) + 1) * sizeof(char));
    strncpy(romanValue, value, strlen(value) + 1);

    printf("\n%s = %i\n\a", romanValue, parseRomanCiphers(romanValue));

    free(romanValue);
}
