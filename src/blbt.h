#ifndef _BL_BT_H_
#define _BL_BT_H_

#define BINARY_SET_TYPE(NAME, KEY_TYPE, DATA_TYPE) \
  typedef struct { \
    KEY_TYPE key; \
    DATA_TYPE* data; \
    NAME##_entry* left; \
    NAME##_entry* right; \
  } NAME;

#define BINARY_TREE_ABORT_DUPLICATES(NAME) \
  void NAME##_abort_duplicates(NAME) {
    while 

#define BINARY_SET_INSERT(NAME, KEY_TYPE, DATA_TYPE, CALLOC) \
  void NAME##_insert(NAME** head, KEY_TYPE key, DATA_TYPE data) { \
    NAME* v = (NAME*) CALLOC(1, sizeof(NAME)); \
    v->key = key; \
    v->data = data; \
    /* Key exists, find insert point */ \
    if (*head) { \
    } else { \
      *head = v; \
    } \
  }
    
    

#define BINARY_TREE(NAME, KEY_TYPE, DATA_TYPE, CALLOC) \
  BINARY_TREE_TYPE(NAME, KEY_TYPE,  DATA_TYPE) \
  BINARY_TREE_ABORT_DUPLICATES(NAME) \
  BINARY_SET_INSERT(NAME, KEY_TYPE, DATA_TYPE, CALLOC)

#endif
