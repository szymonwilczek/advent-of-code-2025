#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INPUT_DIR
#define INPUT_DIR "./"
#endif

// -10 % 100 = -10. i want that to be 90.
// ((a % n) + n) % n
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
  int password_count = 0;

  char line[32];

  while (fgets(line, sizeof(line), file)) {
    char direction;
    int distance;

    // %c is char (L/R), %d is a number
    if (sscanf(line, "%c%d", &direction, &distance) == 2) {

      if (direction == 'L') {
        // move left (substract)
        current_pos -= distance;
      } else if (direction == 'R') {
        // move right (addition)
        current_pos += distance;
      }

      // position normalisation to the range of 0-99
      current_pos = circular_mod(current_pos, 100);

      // puzzle condition
      if (current_pos == 0) {
        password_count++;
      }
    }
  }

  fclose(file);

  printf("Day 1 solution: %d\n", password_count);

  return 0;
}
