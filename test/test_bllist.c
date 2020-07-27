#include "bllist.h"
#include <stdio.h>
#include <assert.h>

DYNAMIC_ARRAY(int_list, int, 32);

void test_push() {
 struct int_list l;
 int_list_init(&l);

 for (size_t i = 0; i < 10000; i++) {
   int_list_push(&l, i * 100);
 }

 for (size_t i = 0; i < int_list_size(&l); i++) {
   assert(l.data[i] == i * 100);
 }

 assert(int_list_size(&l) == 10000);

 int_list_free(&l);
}

void test_pop() {
 struct int_list l;
 int_list_init(&l);

 for (size_t i = 0; i < 10000; i++) {
   int_list_push(&l, i * 100);
 }

 size_t last = int_list_size(&l);

 for (size_t i = 0; i < 10000; i++) {
   assert(int_list_pop(&l) == ((10000 - 1) - i) * 100);
   assert(int_list_size(&l) == last - 1);
   last = int_list_size(&l);
 }

 assert(int_list_size(&l) == 0);

 int_list_push(&l, 5);
 int_list_push(&l, 10);

 assert(int_list_remove(&l, 0) == 5);
 assert(int_list_size(&l) == 1);

 assert(int_list_remove(&l, 0) == 10);
 assert(int_list_size(&l) == 0);

 int_list_free(&l);
}

void test_concat() {
  struct int_list l1;
  struct int_list l2;
  int_list_init(&l1);
  int_list_init(&l2);

  printf("Filling arrays\n");
  for (size_t i = 0; i < 10000; i++) {
    int_list_push(&l1, i * 100);
    int_list_push(&l2, i);
  }

  printf("Concatenating arrays\n");
  int_list_concat(&l1, &l2);

  printf("Freeing l2\n");
  int_list_free(&l2);

  printf("Checking Size\n");
  assert(int_list_size(&l1) == 20000);
  assert(int_list_size(&l2) == 0);

  printf("Checking data\n");
  for (size_t i = 0; i < 10000; i++) {
    assert(l1.data[i] == i * 100);
    assert(l1.data[i + 10000] == i);
  }

  for (size_t i = 0; i < 100000; i++) {
    int_list_push(&l1, i * 100);
  }

  for (size_t i = 0; i < 100000; i++) {
    assert(l1.data[i + 20000] == i * 100);
  }

  printf("Freeing first list\n");
  int_list_free(&l1);
}
