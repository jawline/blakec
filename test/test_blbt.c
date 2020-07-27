#include "bltree.h"

int key_cmp(int a, int b) {
  return a - b;
}

BINARY_TREE(inttree, int, int, key_cmp);
