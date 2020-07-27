#include "unity.h"
#include "bllist.h"

DYNAMIC_ARRAY(int_list, int, 32);

struct int_list l1;
struct int_list l2;

void setUp() {
  int_list_init(&l1);
  int_list_init(&l2);
}

void tearDown() {
  int_list_free(&l1);
  int_list_free(&l2);
}

void test_push() {

 for (size_t i = 0; i < 10000; i++) {
   int_list_push(&l1, i * 100);
 }

 for (size_t i = 0; i < int_list_size(&l1); i++) {
   TEST_ASSERT_EQUAL(l1.data[i], i * 100);
 }

 TEST_ASSERT_EQUAL(int_list_size(&l1), 10000);
}

void test_pop() {

 for (size_t i = 0; i < 10000; i++) {
   int_list_push(&l1, i * 100);
 }

 size_t last = int_list_size(&l1);

 for (size_t i = 0; i < 10000; i++) {
   TEST_ASSERT_EQUAL(int_list_pop(&l1), ((10000 - 1) - i) * 100);
   TEST_ASSERT_EQUAL(int_list_size(&l1), last - 1);
   last = int_list_size(&l1);
 }

 TEST_ASSERT_EQUAL(int_list_size(&l1), 0);

 int_list_push(&l1, 5);
 int_list_push(&l1, 10);

 TEST_ASSERT_EQUAL(int_list_remove(&l1, 0), 5);
 TEST_ASSERT_EQUAL(int_list_size(&l1), 1);

 TEST_ASSERT_EQUAL(int_list_remove(&l1, 0), 10);
 TEST_ASSERT_EQUAL(int_list_size(&l1), 0);
}

void test_concat() {

  printf("Filling arrays\n");
  for (size_t i = 0; i < 10000; i++) {
    int_list_push(&l1, i * 100);
    int_list_push(&l2, i);
  }

  printf("Concatenating arrays\n");
  int_list_concat(&l1, &l2);

  printf("Checking Size\n");
  TEST_ASSERT_EQUAL(int_list_size(&l1), 20000);
  TEST_ASSERT_EQUAL(int_list_size(&l2), 10000);

  printf("Checking data\n");
  for (size_t i = 0; i < 10000; i++) {
    TEST_ASSERT_EQUAL(l1.data[i], i * 100);
    TEST_ASSERT_EQUAL(l1.data[i + 10000], i);
  }

  for (size_t i = 0; i < 100000; i++) {
    int_list_push(&l1, i * 100);
  }

  for (size_t i = 0; i < 100000; i++) {
    TEST_ASSERT_EQUAL(l1.data[i + 20000], i * 100);
  }
}
