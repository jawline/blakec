#ifndef _BL_PROGRESS_DEF_H_
#define _BL_PROGRESS_DEF_H_
#include <stddef.h>

struct progress_bar {
  size_t current;
  size_t total; 
};

void progress_bar_init(struct progress_bar* bar, size_t max);
void progress_bar_step(struct progress_bar* bar);

#endif
