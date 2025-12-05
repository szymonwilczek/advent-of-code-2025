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

  // -1 to 1 for both row and column offsets
  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      // skip the center cell itself
      if (dy == 0 && dx == 0)
        continue;

      int ny = r + dy;
      int nx = c + dx;

      // boundary checks: dont access memory outside the grid
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

  // grid into the 2d array
  while (rows < MAX_ROWS && fgets(grid[rows], MAX_COLS, file)) {
    grid[rows][strcspn(grid[rows], "\n")] = 0;

    if (rows == 0) {
      cols = strlen(grid[rows]);
    }
    rows++;
  }
  fclose(file);

  int accessible_count = 0;

  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      if (grid[y][x] == '@') {
        int neighbors = count_neighbors(y, x);

        if (neighbors < 4) {
          accessible_count++;
        }
      }
    }
  }

  printf("day 4 solution: %d\n", accessible_count);

  return 0;
}
