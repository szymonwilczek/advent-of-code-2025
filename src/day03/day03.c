#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INPUT_DIR
#define INPUT_DIR "./"
#endif

// calculates the maximum joltage for a single bank of batteries
// input: a string of digits (eg "8111119")
// logic: find two digits d1 and d2 at indices i and j (where i < j)
// such that (d1 * 10 + d2) is maximized
int get_max_joltage(const char *line) {
  int max_val = 0;
  int len = strlen(line);

  // every possible first digit
  for (int i = 0; i < len; i++) {
    if (!isdigit(line[i]))
      continue; // whitespace/newlines

    // every possible second digit that appears AFTER the first
    for (int j = i + 1; j < len; j++) {
      if (!isdigit(line[j]))
        continue;

      int d1 = line[i] - '0';
      int d2 = line[j] - '0';

      int current_val = d1 * 10 + d2;

      if (current_val > max_val) {
        max_val = current_val;
      }
    }
  }
  return max_val;
}

int main() {
  char filepath[256];
  snprintf(filepath, sizeof(filepath), "%sday03.txt", INPUT_DIR);

  FILE *file = fopen(filepath, "r");
  if (!file) {
    perror("failed to open input file");
    return 1;
  }

  char line[1024];
  long long total_joltage = 0;

  while (fgets(line, sizeof(line), file)) {
    int bank_max = get_max_joltage(line);
    total_joltage += bank_max;
  }

  fclose(file);

  printf("day 3 solution: %lld\n", total_joltage);

  return 0;
}
