#include "bllist.h"
#include <stdio.h>
#include <assert.h>

DYNAMIC_ARRAY(int_list, int, 32);

void test_push() {
 struct int_list l;
 int_list_init(&l);

 for (size_t i = 0; i < 100; i++) {
   int_list_push(&l, i * 100);
 }

 for (size_t i = 0; i < int_list_size(&l); i++) {
   assert(l.data[i] == i * 100);
 }

 assert(int_list_size(&l) == 100);

 int_list_free(&l);
}

void test_pop() {
 struct int_list l;
 int_list_init(&l);

 for (size_t i = 0; i < 100; i++) {
   int_list_push(&l, i * 100);
 }

 size_t last = int_list_size(&l);

 for (size_t i = 0; i < 100; i++) {
   printf("");
   assert(int_list_pop(&l) == (99 - i) * 100);
   assert(int_list_size(&l) == last - 1);
   last = int_list_size(&l);
 }

 assert(int_list_size(&l) == 0);

 int_list_free(&l);

}

int main(void) {
  test_push();
  test_pop();
  printf("Passed\n");
  return 0;
}
