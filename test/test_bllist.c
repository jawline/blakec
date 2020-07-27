#include "unity.h"

size_t illegal_ops = 0;

#define LIST_ILLEGAL_OP(msg) illegal_ops += 1; return 0;

#include "bllist.h"

DYNAMIC_ARRAY(int_list, int, 32);

struct int_list l1;
struct int_list l2;

void setUp() {
  int_list_init(&l1);
  int_list_init(&l2);
  illegal_ops = 0;
}

void tearDown() {
  int_list_free(&l1);
  int_list_free(&l2);
}

void test_push() {
  int_list_push(&l1, 5042);
  TEST_ASSERT_EQUAL(l1.data[0], 5042);
  TEST_ASSERT_EQUAL(int_list_size(&l1), 1);
}

void test_pop() {
  int_list_push(&l1, 5042);
  TEST_ASSERT_EQUAL(int_list_pop(&l1), 5042);
  TEST_ASSERT_EQUAL(int_list_size(&l1), 0);
}

void test_pop_empty_triggers_illegal_op_exit() {
  int_list_pop(&l1);
  TEST_ASSERT_EQUAL(illegal_ops, 1);
}

void test_pop_ordering() {
  int_list_push(&l1, 1);
  int_list_push(&l1, 2);
  int_list_push(&l1, 3);
  int_list_push(&l1, 4);
  int_list_push(&l1, 5);
  for (size_t i = 0; i < 5; i++) {
    TEST_ASSERT_EQUAL(l1.data[i], i + 1);
  }
  TEST_ASSERT_EQUAL(int_list_pop(&l1), 5);
  TEST_ASSERT_EQUAL(int_list_pop(&l1), 4);
  TEST_ASSERT_EQUAL(int_list_pop(&l1), 3);
  TEST_ASSERT_EQUAL(int_list_pop(&l1), 2);
  TEST_ASSERT_EQUAL(int_list_pop(&l1), 1);
  TEST_ASSERT_EQUAL(int_list_size(&l1), 0);
}

void test_remove_single() {
  int_list_push(&l1, 50);
  int k = int_list_remove(&l1, 0);
  TEST_ASSERT_EQUAL(int_list_size(&l1), 0);
}

void test_remove_from_big_list() {

  for (size_t i = 0; i < 10000; i++) {
    int_list_push(&l1, i - 3);
  }

  TEST_ASSERT_EQUAL(int_list_remove(&l1, 0), -3);
  TEST_ASSERT_EQUAL(int_list_remove(&l1, 0), -2);
  TEST_ASSERT_EQUAL(int_list_remove(&l1, 0), -1);

  for (size_t i = 0; i < 10000 - 3; i++) {
    TEST_ASSERT_EQUAL(l1.data[i], i);
  }
}

void test_remove_invalid_index_triggers_illegal_op_exit() {

  // Remove a nonexistant element
  int_list_remove(&l1, 0);
  TEST_ASSERT_EQUAL(illegal_ops, 1);

  // Add a new element (legal)
  int_list_push(&l1, 50);
  TEST_ASSERT_EQUAL(illegal_ops, 1);

  // Remove a non-existant element (illegal)
  int_list_remove(&l1, 232131);
  TEST_ASSERT_EQUAL(illegal_ops, 2);

  // Remove the element we just added (legal)
  int_list_remove(&l1, 0);
  TEST_ASSERT_EQUAL(illegal_ops, 2);

  // Double remove (illegal, since the list doesn't have that index now)
  int_list_remove(&l1, 0);
  TEST_ASSERT_EQUAL(illegal_ops, 3);
}

void test_push_many() {

 for (size_t i = 0; i < 10000; i++) {
   int_list_push(&l1, i * 100);
 }

 for (size_t i = 0; i < int_list_size(&l1); i++) {
   TEST_ASSERT_EQUAL(l1.data[i], i * 100);
 }

 TEST_ASSERT_EQUAL(int_list_size(&l1), 10000);
}

void test_pop_many() {

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
