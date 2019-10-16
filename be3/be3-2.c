#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TREE {
  int x;
  struct TREE *fg;
  struct TREE *fd;
};
typedef struct TREE tree;

void displayTree(tree a) {
  printf("node %i\n", a.x);
  if (a.fd) {
    displayTree(*(a.fd));
  }
  if (a.fg) {
    displayTree(*(a.fg));
  }
}

void writeTree(tree a, FILE *f) {
  fwrite(&a, sizeof(tree), 1, f);
  if (a.fg) {
    writeTree(*(a.fg), f);
  }
  if (a.fd) {
    writeTree(*(a.fd), f);
  }
}

tree *newNode(int x) {
  tree *new = (tree *)malloc(sizeof(tree));
  new->x = x;
  new->fg = new->fd = NULL;
  return new;
}

void *insert(tree *first, int key) {
  tree *new = newNode(key);
  tree *node = first;
  tree *tmp = NULL;

  while (node != NULL) {
    tmp = node;
    if (key < node->x)
      node = node->fg;
    else
      node = node->fd;
  }

  if (tmp == NULL)
    tmp = new;
  else if (key < tmp->x)
    tmp->fg = new;
  else
    tmp->fd = new;
}

tree *sortedArrayToBST(int arr[], int start, int end) {
  if (start > end)
    return NULL;

  int mid = (start + end) / 2;
  tree *root = newNode(arr[mid]);

  root->fg = sortedArrayToBST(arr, start, mid - 1);
  root->fd = sortedArrayToBST(arr, mid + 1, end);

  return root;
}

tree *loadFromFile(FILE *file) {
  int i = 0, count = 0;
  int *arr = (int *)malloc(sizeof(int) * 50);

  fscanf(file, "%d", &i);
  while (!feof(file)) {
    arr[count] = i;
    count++;
    fscanf(file, "%d", &i);
  }
  fclose(file);

  int n = sizeof(arr) / sizeof(arr[0]);
  tree *first = sortedArrayToBST(arr, 0, n - 1);

  return first;
}

// for i in {0..50};do printf $[RANDOM % 100]"\n";done > test.tnodet

void readTree(tree *a, FILE *f) {
  fread(a, sizeof(tree), 1, f);

  if (a->fg) {
    a->fg = (tree *)malloc(sizeof(tree));
    readTree(a->fg, f);
  }

  if (a->fd) {
    a->fd = (tree *)malloc(sizeof(tree));
    readTree(a->fd, f);
  }
}

tree *initStatement() {
  tree *a = newNode(30);
  tree *b = newNode(1);
  tree *c = newNode(50);
  tree *d = newNode(5);

  a->fg = b;
  a->fd = c;
  b->fd = d;

  return a;
}

void main() {
  tree *a = initStatement();

  FILE *f;
  char *fileName = "tree.blob";
  f = fopen(fileName, "w");
  writeTree(*a, f);
  fclose(f);
  // todo put all to -1
  // todo free pointers

  f = fopen(fileName, "r");
  tree *first = newNode(-1);
  readTree(first, f);

  insert(first, 60);
  // displayTree(*first);

  fclose(f);

  FILE *f2;
  char *list = "integer_list.txt";
  f2 = fopen(list, "r");
  tree *fromFile = loadFromFile(f);
  displayTree(*fromFile);
}