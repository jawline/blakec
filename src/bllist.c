#include "bllist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DEFAULT_INCREASE_SIZE 8

void dynamic_array_init(struct dynamic_array* list, size_t elem_size) {
  list->data = NULL;
  list->current = 0;
  list->elem_size = 0;
  list->max_capacity = 0;
  list->elem_size = elem_size;
}

void dynamic_array_free(struct dynamic_array* list) {
  free(list->data);
  list->data = NULL;
}

/**
 * Increase a list size by a specified number of elements
 */
void dynamic_array_increase(struct dynamic_array* list, size_t by_elems) {
  list->data = realloc(list->data, (list->max_capacity + by_elems) * list->elem_size);
}

void dynamic_array_push(struct dynamic_array* list, void* item) {
  
  if (list->current >= list->max_capacity) {
    dynamic_array_increase(list, DEFAULT_INCREASE_SIZE);
  }

  memcpy(list->data + (list->current * list->elem_size), item, list->elem_size);
  list->current += 1;
}

void dynamic_array_pop(struct dynamic_array* list, void* item) {

}

void main(void) {
  struct dynamic_array t;
  dynamic_array_init(&t, sizeof(int));
  int ti;
  ti = 4;
  dynamic_array_push(&t, &ti);
  dynamic_array_push(&t, &ti);
  ti = 6;
  dynamic_array_push(&t, &ti);
  int* data = dynamic_array_data_with_type(&t, int);
  printf("%i\n", *data);
  printf("%i\n", dynamic_array_get(&t, int, 0));
}
