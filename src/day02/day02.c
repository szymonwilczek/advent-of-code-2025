#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INPUT_DIR
#define INPUT_DIR "./"
#endif

/**
 * checks whether the number has a double sequence
 * 55 -> YES (5, 5)
 * 123123 -> YES (123, 123)
 * 101 -> NO (odd length)
 */
int is_invalid_id(long long id) {
  char s[64];

  // conversion of number to string
  snprintf(s, sizeof(s), "%lld", id);
  int len = strlen(s);

  // if length is odd it cannot be invalid
  if (len % 2 != 0) {
    return 0; // false
  }

  int half = len / 2;

  // compare first half with second half
  // returns 0 if equal
  if (strncmp(s, s + half, half) == 0) {
    return 1; // true -> invalid
  }

  return 0;
}

int main() {
  char filepath[256];
  snprintf(filepath, sizeof(filepath), "%sday02.txt", INPUT_DIR);

  FILE *file = fopen(filepath, "r");
  if (!file) {
    perror("Could not open input file");
    return 1;
  }

  long long start, end;
  long long total_sum = 0;

  // format: A-B,C-D,E-F
  // fscanf("%lld-%lld", ...) reads two long long numbers separated by '-'
  while (fscanf(file, "%lld-%lld", &start, &end) == 2) {

    for (long long i = start; i <= end; i++) {
      if (is_invalid_id(i)) {
        total_sum += i;
      }
    }

    // consume the comma or newline after the pair
    char c = fgetc(file);
    if (c == EOF)
      break;
  }

  fclose(file);

  printf("Day 2 Solution: %lld\n", total_sum);

  return 0;
}
