#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INPUT_DIR
#define INPUT_DIR "./"
#endif

// checks if id consists of a repeating pattern (at least twice)
// "121212" (pattern "12" repeated 3 times) -> true
// "111" (pattern "1" repeated 3 times) -> true
int is_invalid_id_extended(long long id) {
  char s[64];
  snprintf(s, sizeof(s), "%lld", id);
  int len = strlen(s);

  // iterate through possible pattern lengths
  // pattern must be short enough to fit at least twice
  for (int p_len = 1; p_len <= len / 2; p_len++) {

    // total length must be divisible by pattern length
    if (len % p_len != 0) {
      continue;
    }

    // check if the rest of the string matches the first chunk (the pattern)
    // compare char at index i with char at index (i % p_len)
    // using modulo ensures that comparing against the reference pattern at
    // start
    int is_match = 1;
    for (int i = p_len; i < len; i++) {
      if (s[i] != s[i % p_len]) {
        is_match = 0;
        break;
      }
    }

    // if loop finished without breaking, found a repeating pattern
    if (is_match) {
      return 1;
    }
  }

  return 0;
}

int main() {
  char filepath[256];
  snprintf(filepath, sizeof(filepath), "%sday02.txt", INPUT_DIR);

  FILE *file = fopen(filepath, "r");
  if (!file) {
    perror("failed to open input file");
    return 1;
  }

  long long start, end;
  long long total_sum = 0;

  // parse ranges following the format "a-b"
  while (fscanf(file, "%lld-%lld", &start, &end) == 2) {
    for (long long i = start; i <= end; i++) {
      if (is_invalid_id_extended(i)) {
        total_sum += i;
      }
    }

    // consume the comma or handle end of file
    char c = fgetc(file);
    if (c == EOF)
      break;
  }

  fclose(file);

  printf("day 2 solution (part 2): %lld\n", total_sum);

  return 0;
}
