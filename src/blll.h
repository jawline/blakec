#ifndef _BLAKE_LINKED_LIST_H_
#define _BLAKE_LINKED_LIST_H_
#include <stddef.h>

#define LINKED_LIST_TYPE(NAME, TYPE) \
typedef struct NAME { \
  struct NAME##_elem* start; \
  struct NAME##_elem* end; \
}; \
typedef struct NAME##_elem { \
  TYPE data; \
  struct NAME##_elem* next; \
  struct NAME##_elem* prev; \
};

#define LINKED_LIST_INIT(NAME) void NAME##_init(struct NAME* l) { \
  l->start = NULL; \
  l->end = NULL; \
}

#define LINKED_LIST_PREPEND(NAME, TYPE) void NAME##_prepend(struct NAME** l, TYPE v) { \
  struct NAME_elem* new_node = malloc(sizeof(struct NAME)); \
  new_node->prev = NULL; \
  new_node->next = *l; \
  new_node->data = v; \
  if (*l) { \
    *l->prev = new_node; \
  } \
  *l = new_node; \
}

#define CREATE_LINKED_LIST(NAME, TYPE) \
  LINKED_LIST_TYPE(NAME, TYPE) \
  LINKED_LIST_INIT(NAME) \
  LINKED_LIST_PREPEND(NAME, TYPE)

#endif
