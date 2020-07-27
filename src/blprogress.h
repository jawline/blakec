#ifndef _BL_PROGRESS_DEF_H_
#define _BL_PROGRESS_DEF_H_

#include <sys/ioctl.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define PROGRESS_MAX_BUFFER_SIZE 2048

/**
 * Our progress bar prints an interactive bar to keep track of current progress.
 * It grabs the current terminal width to emit the correct size
 */
struct progress_bar {
  char buffer[PROGRESS_MAX_BUFFER_SIZE];
  size_t current;
  size_t total;
};

static inline void progress_bar_print(struct progress_bar* bar) {

  //Assume 80 line col if we can't ask for the size
  struct winsize w;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) < 0) {
    w.ws_col = 80;
  }

  size_t col_size = PROGRESS_MAX_BUFFER_SIZE < w.ws_col ? PROGRESS_MAX_BUFFER_SIZE : w.ws_col;

  memset(bar->buffer, 0, PROGRESS_MAX_BUFFER_SIZE);

  float finished_percent = (float) bar->current / (float) bar->total;

  int bar_start = snprintf(bar->buffer, col_size, "%.0f%% (%lu/%lu) ", finished_percent * 100.0, bar->current, bar->total);

  if (bar_start < 0) {
    // Cant fit into bar
    return;
  }

  if (bar_start < col_size) {
    size_t progress_size = col_size - bar_start;
    int proportion = finished_percent * progress_size;
    memset(bar->buffer + bar_start, '#', proportion);
  }

  putc('\r', stdout);
  fwrite(bar->buffer, col_size, 1, stdout);
  fflush(stdout);
}

/**
 * Progress bar should be initialised with the total number of work items to be completed
 */
static inline void progress_bar_init(struct progress_bar* bar, size_t total) {
  bar->current = 0;
  bar->total = total;
  progress_bar_print(bar);
}

/**
 * Step the progress bar by 1 work item
 */
static inline void progress_bar_step(struct progress_bar* bar) {
  bar->current += 1;
  progress_bar_print(bar);
}

/**
 * Print a message safely to stdout when using progress bar
 * Avoids corrupting the bar or having the bar overwrite printed message
 */
static inline void progress_bar_interrupt(struct progress_bar* bar, char const* msg) {
  printf("\n%s\n\r", msg);
  progress_bar_print(bar);
}

#endif
