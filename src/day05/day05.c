#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INPUT_DIR
#define INPUT_DIR "./"
#endif

#define MAX_RANGES 2048

typedef struct {
  long long start;
  long long end;
} Range;

Range ranges[MAX_RANGES];
int range_count = 0;

int main() {
  char filepath[256];
  snprintf(filepath, sizeof(filepath), "%sday05.txt", INPUT_DIR);

  FILE *file = fopen(filepath, "r");
  if (!file) {
    perror("failed to open input file");
    return 1;
  }

  char line[64];
  long long fresh_count = 0;

  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\r\n")] = 0;

    if (strlen(line) == 0)
      continue;

    // if line contains '-', which indicates a range definition
    if (strchr(line, '-')) {
      if (range_count < MAX_RANGES) {
        long long s, e;
        if (sscanf(line, "%lld-%lld", &s, &e) == 2) {
          ranges[range_count].start = s;
          ranges[range_count].end = e;
          range_count++;
        }
      }
    }
    // its an ingredient id
    else if (isdigit(line[0])) {
      long long id = atoll(line);

      // check if id falls into any known fresh range
      for (int i = 0; i < range_count; i++) {
        if (id >= ranges[i].start && id <= ranges[i].end) {
          fresh_count++;
          break; // found a match, no need to check other ranges
        }
      }
    }
  }

  fclose(file);

  printf("day 5 solution: %lld\n", fresh_count);

  return 0;
}
