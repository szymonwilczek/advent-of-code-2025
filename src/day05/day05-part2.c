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

int compare_ranges(const void *a, const void *b) {
  Range *r1 = (Range *)a;
  Range *r2 = (Range *)b;
  if (r1->start < r2->start)
    return -1;
  if (r1->start > r2->start)
    return 1;
  return 0;
}

int main() {
  char filepath[256];
  snprintf(filepath, sizeof(filepath), "%sday05.txt", INPUT_DIR);

  FILE *file = fopen(filepath, "r");
  if (!file) {
    perror("failed to open input file");
    return 1;
  }

  char line[64];

  // 1. parse all ranges
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\r\n")] = 0;
    if (strlen(line) == 0)
      continue;

    // ranges containing '-'
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
  }
  fclose(file);

  // 2. sort ranges by start position
  qsort(ranges, range_count, sizeof(Range), compare_ranges);

  long long total_fresh_ids = 0;

  if (range_count > 0) {
    long long current_start = ranges[0].start;
    long long current_end = ranges[0].end;

    for (int i = 1; i < range_count; i++) {
      // check for overlap or adjacency
      // note: if range A ends at 5 and range B starts at 6, they are contiguous
      // integers so we check if start <= end + 1
      if (ranges[i].start <= current_end + 1) {
        // merge: extend current end if the new range goes further
        if (ranges[i].end > current_end) {
          current_end = ranges[i].end;
        }
      } else {
        // gap detected. add the length of the completed merged range
        // length = end - start + 1
        total_fresh_ids += (current_end - current_start + 1);

        // start a new active range
        current_start = ranges[i].start;
        current_end = ranges[i].end;
      }
    }
    // add the last range processed
    total_fresh_ids += (current_end - current_start + 1);
  }

  printf("day 5 solution (part 2): %lld\n", total_fresh_ids);

  return 0;
}
