#include "blprogress.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MIN(A, B) A < B ? A : B

void progress_bar_print(struct progress_bar* bar) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  char col_buffer[4096];
  size_t col_size = MIN(4096, w.ws_col);
  memset(col_buffer, ' ', col_size);

  float finished_percent= (float) bar->current / (float) bar->total;

  snprintf(col_buffer, 4096, "%.0f%% (%lu/%lu) ", finished_percent * 100.0, bar->current, bar->total);

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

void progress_bar_init(struct progress_bar* bar, size_t total) {
  bar->current = 0;
  bar->total = total;
  progress_bar_print(bar);
}

void progress_bar_step(struct progress_bar* bar) {
  bar->current += 1; 
  progress_bar_print(bar);
}

void progress_bar_interrupt(struct progress_bar* bar, char const* msg) {
  printf("\n%s\n\r", msg);
  progress_bar_print(bar);
}
