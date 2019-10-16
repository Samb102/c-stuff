#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MYSTRUCT {
  int x;
  char *name;
};

typedef struct MYSTRUCT myStruct;

void main() {
  FILE *f;
  char *fileName = "mydata.blob";
  f = fopen(fileName, "w");

  myStruct *m = (myStruct *)malloc(sizeof(myStruct));
  m->x = 4;
  m->name = (char *)malloc(sizeof(char) * 100);
  strcpy(m->name, "coucou\0");

  printf("m->x = %i\nm->name = %s\n", m->x, m->name);

  fwrite(m, sizeof(myStruct), 1, f);
  fwrite(m->name, (char *)malloc(sizeof(char) * strlen(m->name)), 1, f);
  fclose(f);

  strcpy(m->name, "helloworld\0");
  free(m);

  f = fopen(fileName, "r");

  myStruct *m2 = (myStruct *)malloc(sizeof(myStruct));
  m2->name = (char *)malloc(sizeof(char) * 100);

  fread(m2, sizeof(myStruct), 1, f);
  printf("m2->x = %i\n", m2->x);

  fread(m2->name, (char *)malloc(sizeof(char) * strlen(m2->name)), 1, f);
  printf("m2->name = %s\n", m2->name);

  fclose(f);
  free(m2);
}
