#ifndef _BL_PROGRESS_DEF_H_
#define _BL_PROGRESS_DEF_H_
#include <stddef.h>

/**
 * Our progress bar prints an interactive bar to keep track of current progress.
 * It grabs the current terminal width to emit the correct size
 */
struct progress_bar {
  size_t current;
  size_t total; 
};

/**
 * Progress bar should be initialised with the total number of work items to be completed
 */
void progress_bar_init(struct progress_bar* bar, size_t max);

/**
 * Step the progress bar by 1 work item
 */
void progress_bar_step(struct progress_bar* bar);

/**
 * Print a message safely to stdout when using progress bar
 * Avoids corrupting the bar or having the bar overwrite printed message
 */
void progress_bar_interrupt(struct progress_bar* bar, char const* msg);

#endif
