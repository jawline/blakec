#ifndef _BLAKE_LIST_H_
#define _BLAKE_LIST_H_
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

#define DYNAMIC_ARRAY_TYPE(NAME, TYPE) struct NAME { \
  TYPE* data; \
  size_t current; \
  size_t max_capacity; \
};

#define DYNAMIC_ARRAY_INIT(NAME) void NAME##_init(struct NAME* l) { \
  l->data = NULL; \
  l->current = 0; \
  l->max_capacity = 0; \
}

#define DYNAMIC_ARRAY_FREE(NAME) void NAME##_free(struct NAME* l) { \
  free(l->data); \
  NAME##_init(l); \
}

#define DYNAMIC_ARRAY_INCREASE(NAME, TYPE, SIZE) void NAME##_increase(struct NAME* l) { \
  l->max_capacity += SIZE; \
  l->data = realloc(l->data, sizeof(TYPE) * l->max_capacity); \
}

/**
 * Generate a dynamic array shrinking method for pop.
 * TODO: This will shrink the array to the current size 
 */
#define DYNAMIC_ARRAY_SHRINK(NAME, TYPE, SIZE) void NAME##_shrink(struct NAME* l) { \
  if (l->current + SIZE < l->max_capacity) { \
    l->max_capacity -= SIZE; \
    l->data = realloc(l->data, l->max_capacity * sizeof(TYPE)); \
  } \
}

#define DYNAMIC_ARRAY_PUSH(NAME, TYPE) void NAME##_push(struct NAME* l, TYPE v) { \
  if (l->current >= l->max_capacity) { \
    NAME##_increase(l); \
  } \
  *(l->data + l->current) = v; \
  l->current += 1; \
}

#define DYNAMIC_ARRAY_POP(NAME, TYPE) TYPE NAME##_pop(struct NAME* l) { \
  l->current -= 1; \
  TYPE r = l->data[l->current]; \
  NAME##_shrink(l); \
  return r; \
}

#define DYNAMIC_ARRAY_SIZE(NAME) size_t NAME##_size(struct NAME* l) { \
  return l->current; \
}

#define DYNAMIC_ARRAY(name, type, block_size) DYNAMIC_ARRAY_TYPE(name, type); DYNAMIC_ARRAY_INIT(name) DYNAMIC_ARRAY_FREE(name) DYNAMIC_ARRAY_INCREASE(name, type, block_size) DYNAMIC_ARRAY_PUSH(name, type) DYNAMIC_ARRAY_SHRINK(name, type, block_size) DYNAMIC_ARRAY_POP(name, type) DYNAMIC_ARRAY_SIZE(name)

#endif
