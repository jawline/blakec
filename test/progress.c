#include "blprogress.h"

int main(int argc, char** argv) {

  size_t test_size = 10000;

  struct progress_bar pb;
  progress_bar_init(&pb, test_size);
 
  for (size_t i = 0; i < test_size; i++) {
    progress_bar_step(&pb);
    if (i == 5000) {
       progress_bar_interrupt(&pb, "Half way");
    }
  }
}
