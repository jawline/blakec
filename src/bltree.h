#ifndef _BL_BINARY_TREE_H
#define _BL_BINARY_TREE_H
#include "bllist.h"
#include <stdbool.h>

/**
 * key-data pair binary tree type.
 * Does not store arbitrary sequence elements, this is a binary tree map
 * This flavor of binary tree cannot have two of the same key
 */
#define BINARY_TREE_TYPE(NAME, KEY_TYPE, DATA_TYPE) \
  struct NAME##_entry { \
    KEY_TYPE key; \
    DATA_TYPE data; \
    struct NAME##_entry *left, *right; \
  };

#define BINARY_TREE(NAME, KEY_TYPE, DATA_TYPE, CMP_FN) \
  BINARY_TREE_TYPE(NAME, KEY_TYPE, DATA_TYPE)

#endif //_BL_BINARY_TREE_H
