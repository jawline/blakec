#ifndef _BL_PROGRESS_DEF_H_
#define _BL_PROGRESS_DEF_H_

#include <sys/ioctl.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define PROGRESS_BUFFER_SIZE 4096

/**
 * Our progress bar prints an interactive bar to keep track of current progress.
 * It grabs the current terminal width to emit the correct size
 */
struct progress_bar {
  size_t current;
  size_t total;
};

#define PRG_MIN(A, B) A < B ? A : B

static inline void progress_bar_print(struct progress_bar* bar) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  char col_buffer[PROGRESS_BUFFER_SIZE];
  size_t col_size = PRG_MIN(PROGRESS_BUFFER_SIZE, w.ws_col);
  memset(col_buffer, ' ', col_size);

  float finished_percent = (float) bar->current / (float) bar->total;

  snprintf(col_buffer, PROGRESS_BUFFER_SIZE, "%.0f%% (%lu/%lu) ", finished_percent * 100.0, bar->current, bar->total);

  size_t bar_start = strlen(col_buffer);

  if (bar_start < col_size) {
    size_t progress_size = col_size - bar_start;
    int proportion = finished_percent * progress_size;
    memset(col_buffer + bar_start, '#', proportion);
  }

  putc('\r', stdout);
  fwrite(col_buffer, col_size, 1, stdout);
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
