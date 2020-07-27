#include "blll.h"
#include <assert.h>
#include <stdio.h>

CREATE_LINKED_LIST(int_list, int);

void test_prepend() {
  struct int_list t;
  int_list_init(&t);
  int_list_prepend(&t, 53);
  assert(int_list_size(&t) == 1);
  assert(int_list_iter(&t) != NULL);
  assert(int_list_iter(&t)->data == 53);
}
