#include <stdio.h>
#include <stdlib.h>
#define nbIntegers 10
struct TNODE {
  void *item;
  struct TNODE *next;
};
typedef struct TNODE tNode;

struct TLIST {
  int nEntries;
  tNode *first;
  tNode *last;
};
typedef struct TLIST tList;

tList *newList() {
  tList *list = (tList *)malloc(sizeof(tList));
  list->first = NULL;
  list->last = NULL;
}

void freeList(tList *list) {
  tNode *current = list->first;
  tNode *tmp = NULL;

  while (current->next != NULL) {
    tmp = current->next;
    free(current);
    current = tmp;
  }

  free(list->first);
  free(list);
}

tNode *addListNode(tList *list, void *item) {
  tNode *node = (tNode *)malloc(sizeof(tNode));
  node->next = NULL;
  node->item = item;

  if (list->first == NULL) {
    list->first = node;
  } else {
    list->last->next = node;
  }

  list->last = node;
  list->nEntries++;

  return node;
}

void applyFunctionToList(tList *list, void (*fctPtr)(void *)) {
  tNode *current = list->first;
  printf("[");
  do {
    (*fctPtr)(current->item);
    current = current->next;
  } while (current->next != NULL);
  printf("]");
}

void printElement(void *element) { printf("%i,", *((int *)element)); }

void decreaseList(tList *list, tNode *toDelete) {
  list->nEntries--;
  free(toDelete);
}

void deleteNode(tList *list, tNode *nodeToDelete) {
  tNode *current = list->first;
  tNode *toDelete = NULL;

  while (current->next != NULL) {
    if (current == nodeToDelete) { // first element
      list->first = current->next;
      decreaseList(list, current);
      break;
    }

    if (current->next == nodeToDelete) {
      toDelete = current->next;

      if (current->next->next != NULL) { // other elements
        current->next = current->next->next;
      } else { // last element
        current->next = NULL;
        list->last = current;
      }

      decreaseList(list, toDelete);
      break;
    }

    current = current->next;
  };
  applyFunctionToList(list, printElement);
}

int compare(void *a, void *b) {
  int int_a = *((int *)a);
  int int_b = *((int *)b);

  // an easy expression for comparing
  return (int_a > int_b) - (int_a < int_b);
}

void bubble(tList *list, int (*fctCmp)(void *, void *)) {
  tNode **head = &(list->first);

  int done = 0;

  while (!done) {
    tNode **pv = head;
    tNode *nd = *head;
    tNode *nx = (*head)->next;

    done = 1;

    while (nx) {
      if (fctCmp(nd->item, nx->item) > 0) {
        nd->next = nx->next;
        nx->next = nd;
        *pv = nx;

        done = 0;
      }
      pv = &nd->next;
      nd = nx;
      nx = nx->next;
    }
  }

  printf("After sorting : \n");
  applyFunctionToList(list, printElement);
}

void main() {
  int integers[nbIntegers] = {18, 12, 22, 1, 11, 10, 12, 8, 24, 3};

  tList *myList = NULL;
  myList = newList();

  for (int i = 0; i < nbIntegers; i++) {
    addListNode(myList, &integers[i]);
  }
  applyFunctionToList(myList, printElement);

  bubble(myList, compare);
  // deleteNode(myList, myList->first->next->next);
  freeList(myList);

  exit(0);
}