#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#define keyBufferSize 32
#define nbAlph 26
#define specialChars " ,.?!:;'"

void checkParameters (int argc, char **argv) { 
    const bool crypt = strcmp(argv[1], "-c") == 0;
    const bool decrypt = strcmp(argv[1], "-d") == 0;

    if ((argc < 4) || (!crypt && !decrypt)) {
        printf("Wrong number of parameters.\n\a");
        exit(0);
    }

    if (crypt && access(argv[2], F_OK) == -1) {
        printf("Please provide clear text file.\n");
        exit(0);
    }  
    
    if (decrypt && access(argv[3], F_OK) == -1) {
        printf("Please provide ciphered text file.\n");
        exit(0);
    }
}

void process (FILE *sourceFile, FILE *outputFile, char *key, char type) {
    const int keyLength = strlen(key) - 1;
    char inputChar, keyCipher;
    bool isUpper;
    int keyCharIndex = 0;
    int keyRank, charRank, delta;

    while ((inputChar = getc(sourceFile)) != EOF) {
        if (strchr(specialChars, inputChar)) {
            fprintf(outputFile, "%c", inputChar);
            continue;
        }

        if (isalpha(inputChar)) {
            keyCipher = key[keyCharIndex % keyLength];
            keyRank = tolower(keyCipher) - 'a';
            charRank = tolower(inputChar) - 'a';
            isUpper = isupper(inputChar);

            if (type == 'c') {
                fprintf(outputFile, "%c", 
                    ((charRank + keyRank) % nbAlph) + (isUpper ? 'A' : 'a')
                );
            } else {
                delta = charRank - keyRank;
                fprintf(outputFile, "%c", 
                    delta + (isUpper ? (delta < 0 ? ('Z' + 1) : 'A') : (delta < 0 ? ('z' + 1) : 'a'))
                );
            }

            keyCharIndex++; 
        }
    }
}

void askUserKey (char *key) {
    printf("Enter key (max : %d): ", keyBufferSize);
    fgets(key, keyBufferSize, stdin);
    printf("\n");
}

char *getKeyFromText (FILE *textFile, char *key) {
    char charToFound, nextLowerChar;
    char keyIndex = 'a';
    FILE *ptr = fopen("text.txt", "r");
    // fdopen (dup (fileno (textFile)), "r");

    while (((charToFound = getc(textFile)) != EOF) || keyIndex == 'z') {
          if (charToFound == keyIndex) {
            fseek(ptr, ftell(textFile), SEEK_SET); 

            while (((nextLowerChar = getc(ptr)) != EOF)) {
                if (isalpha(nextLowerChar) && islower(nextLowerChar)) {
                    key[keyIndex - 'a'] = nextLowerChar;
                    keyIndex++;
                    break;
                }
            }
        }
    }

    printf("%s %li", key, strlen(key));
}

void decryptText () {
    char *key = malloc(sizeof(char) * 26);
    FILE *clearFile, *cipheredFile, *result;

    clearFile = fopen("text.txt", "r");
    getKeyFromText(clearFile, key);
    cipheredFile = fopen("message_crypte.txt", "r");
    result = fopen("result.txt", "w");

    process(cipheredFile, result, key, 'd');
    
    fclose(clearFile);
    fclose(cipheredFile);
    fclose(result);
    free(key);
}

void decriptMyFiles (int argc, char **argv) {
    // char type = strcmp(argv[1], "-c") == 0 ? 'c' : 'd';

    // checkParameters(argc, argv);

    // char key[keyBufferSize];
    // askUserKey(key);

    // FILE *clearFile, *cipheredFile;

    // clearFile = fopen(argv[2], type == 'c' ? "r" : "w");
    // cipheredFile = fopen(argv[3], type == 'c' ? "w" : "r");
    // type == 'c' ? process(clearFile, cipheredFile, key, type) : process(cipheredFile, clearFile, key, type);

    // fclose(clearFile);
    // fclose(cipheredFile);
}

void main (int argc, char **argv) {
    decryptText();
    // decriptMyFiles(argc, argv);
}
