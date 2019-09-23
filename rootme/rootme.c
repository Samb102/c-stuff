#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  setreuid(geteuid(), geteuid());
  system("ls /home/samuel/workspace/c-language/rootme.c");
  return 0;
}