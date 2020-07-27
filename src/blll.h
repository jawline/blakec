#ifndef _BLAKE_LINKED_LIST_H_
#define _BLAKE_LINKED_LIST_H_
#include <stddef.h>
#include <stdlib.h>

#define LINKED_LIST_TYPE(NAME, TYPE) \
struct NAME##_elem { \
  TYPE data; \
  struct NAME##_elem* next; \
  struct NAME##_elem* prev; \
};\
struct NAME { \
  struct NAME##_elem* start; \
  struct NAME##_elem* end; \
  size_t size; \
};

#define LINKED_LIST_INIT(NAME) \
  static inline void NAME##_init(struct NAME* l) { \
    l->start = NULL; \
    l->end = NULL; \
    l->size = 0; \
  }

#define LINKED_LIST_PREPEND(NAME, TYPE) \
  static inline void NAME##_prepend(struct NAME* l, TYPE v) { \
    struct NAME##_elem* new_node = malloc(sizeof(struct NAME##_elem)); \
    new_node->prev = NULL; \
    new_node->next = l->start; \
    new_node->data = v; \
    if (l->start) { \
      l->start->prev = new_node; \
    } \
    l->start = new_node; \
    if (!l->end) { \
      l->end = new_node; \
    } \
    l->size += 1; \
  }

#define LINKED_LIST_ITER(NAME) struct NAME##_elem* NAME##_iter(struct NAME* l) { \
  return l->start; \
}

#define LINKED_LIST_SIZE(NAME) size_t NAME##_size(struct NAME* l) { \
  return l->size; \
}

#define CREATE_LINKED_LIST(NAME, TYPE) \
  LINKED_LIST_TYPE(NAME, TYPE) \
  LINKED_LIST_INIT(NAME) \
  LINKED_LIST_PREPEND(NAME, TYPE) \
  LINKED_LIST_ITER(NAME) \
  LINKED_LIST_SIZE(NAME)

#endif
