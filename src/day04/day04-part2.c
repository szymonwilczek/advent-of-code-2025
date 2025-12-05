#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INPUT_DIR
#define INPUT_DIR "./"
#endif

#define MAX_ROWS 1024
#define MAX_COLS 1024

char grid[MAX_ROWS][MAX_COLS];
int rows = 0;
int cols = 0;

int count_neighbors(int r, int c) {
  int count = 0;
  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      if (dy == 0 && dx == 0)
        continue;

      int ny = r + dy;
      int nx = c + dx;

      if (ny >= 0 && ny < rows && nx >= 0 && nx < cols) {
        if (grid[ny][nx] == '@') {
          count++;
        }
      }
    }
  }
  return count;
}

int main() {
  char filepath[256];
  snprintf(filepath, sizeof(filepath), "%sday04.txt", INPUT_DIR);

  FILE *file = fopen(filepath, "r");
  if (!file) {
    perror("failed to open input file");
    return 1;
  }

  while (rows < MAX_ROWS && fgets(grid[rows], MAX_COLS, file)) {
    grid[rows][strcspn(grid[rows], "\n")] = 0;
    if (rows == 0)
      cols = strlen(grid[rows]);
    rows++;
  }
  fclose(file);

  int total_removed = 0;
  int changed = 1;

  while (changed) {
    changed = 0;

    // temporary buffer to store removal markers for this round
    // 0 = keep, 1 = remove
    // using static to avoid stack overflow on large grids, or malloc
    static char to_remove[MAX_ROWS][MAX_COLS];
    memset(to_remove, 0, sizeof(to_remove));

    int round_removed_count = 0;

    // pass 1: identify candidates for removal
    for (int y = 0; y < rows; y++) {
      for (int x = 0; x < cols; x++) {
        if (grid[y][x] == '@') {
          int neighbors = count_neighbors(y, x);
          if (neighbors < 4) {
            to_remove[y][x] = 1;
            changed = 1;
            round_removed_count++;
          }
        }
      }
    }

    // pass 2: apply removal
    if (changed) {
      for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
          if (to_remove[y][x]) {
            grid[y][x] = '.'; // remove the roll
          }
        }
      }
      total_removed += round_removed_count;
    }
  }

  printf("day 4 solution (part 2): %d\n", total_removed);

  return 0;
}
