#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INPUT_DIR
#define INPUT_DIR "./"
#endif

int circular_mod(int value, int max) { return ((value % max) + max) % max; }

int main() {
  char filepath[256];
  snprintf(filepath, sizeof(filepath), "%sday01.txt", INPUT_DIR);

  FILE *file = fopen(filepath, "r");
  if (!file) {
    perror("Could not open input file");
    return 1;
  }

  int current_pos = 50;
  long long password_count = 0;

  char line[32];

  while (fgets(line, sizeof(line), file)) {
    char direction;
    int distance;

    if (sscanf(line, "%c%d", &direction, &distance) == 2) {

      // handling full circles
      // if the shield has 100 positions, then 100 clicks in any way
      // guarantees that we will pass 0 exactly once

      // R1000 is 10 passes through zero
      int full_circles = distance / 100;
      password_count += full_circles;

      // handling rest of the movement
      int remaining_steps = distance % 100;

      for (int i = 0; i < remaining_steps; i++) {
        if (direction == 'L') {
          current_pos--;
        } else {
          current_pos++;
        }

        // position normalisation
        current_pos = circular_mod(current_pos, 100);

        // checking "click" into 0
        if (current_pos == 0) {
          password_count++;
        }
      }
    }
  }

  fclose(file);

  printf("Day 1 Solution (Part 2): %lld\n", password_count);

  return 0;
}
