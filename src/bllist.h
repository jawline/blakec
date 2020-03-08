#ifndef _BLAKE_LIST_H_
#define _BLAKE_LIST_H_
#include <stdint.h>
#include <stddef.h>

struct dynamic_array {
  void* data;
  size_t current;
  size_t max_capacity;
  size_t elem_size;
  size_t buffer;
};

void dynamic_array_init(struct dynamic_array* list, size_t elem_size);
void dynamic_array_free(struct dynamic_array*);
void dynamic_array_pop(struct dynamic_array*, void* item);
void dynamic_array_push(struct dynamic_array*, void* item);
inline size_t dynamic_array_size(struct dynamic_array* list) {
  return list->current;
}
#define dynamic_array_data_with_type(list, type) ((type*) (list)->data)
#define dynamic_array_get(list, type, idx) *(dynamic_array_data_with_type(list, type) + idx)

#endif
