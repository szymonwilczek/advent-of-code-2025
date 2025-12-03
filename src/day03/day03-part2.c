#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INPUT_DIR
#define INPUT_DIR "./"
#endif

// finds the largest 12-digit sequence preserving order
// uses a greedy approach: for each position of the target 12-digit number,
// pick the largest available digit from the valid search window
long long get_max_joltage_12(const char *line) {
  // keep only digits
  char digits[1024];
  int d_len = 0;
  for (int i = 0; line[i]; i++) {
    if (isdigit(line[i])) {
      digits[d_len++] = line[i];
    }
  }

  // safety check
  if (d_len < 12)
    return 0;

  char result[13]; // 12 digits + null terminator
  int current_search_start = 0;

  // building digit by digit
  for (int k = 0; k < 12; k++) {
    int digits_needed_after = 11 - k;

    // the last valid index we can pick from to ensure we have enough digits
    // left
    int search_end = d_len - 1 - digits_needed_after;

    char max_d = -1;
    int max_idx = -1;

    // find the largest digit in the current valid window
    for (int i = current_search_start; i <= search_end; i++) {
      if (digits[i] > max_d) {
        max_d = digits[i];
        max_idx = i;
      }
      // optimization: 9 is the max possible digit, so we can stop searching
      // early
      if (max_d == '9')
        break;
    }

    result[k] = max_d;

    // ensure next search starts after the digit we just picked
    current_search_start = max_idx + 1;
  }
  result[12] = '\0';

  return atoll(result);
}

int main() {
  char filepath[256];
  snprintf(filepath, sizeof(filepath), "%sday03.txt", INPUT_DIR);

  FILE *file = fopen(filepath, "r");
  if (!file) {
    perror("failed to open input file");
    return 1;
  }

  char line[4096];
  long long total_joltage = 0;

  while (fgets(line, sizeof(line), file)) {
    long long bank_max = get_max_joltage_12(line);
    total_joltage += bank_max;
  }

  fclose(file);

  printf("day 3 solution (part 2): %lld\n", total_joltage);

  return 0;
}
