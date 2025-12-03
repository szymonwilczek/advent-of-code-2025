#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <day_number>"
    echo "Example: $0 03"
    exit 1
fi

DAY=$1
SRC_DIR="src/day${DAY}"
INPUT_FILE="inputs/day${DAY}.txt"
CMAKE_FILE="CMakeLists.txt"

# directory
mkdir -p "$SRC_DIR"
echo "Created directory: $SRC_DIR"

# empty input file
touch "$INPUT_FILE"
echo "Created input file: $INPUT_FILE"

# C template for part 1
cat <<EOF > "${SRC_DIR}/day${DAY}.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INPUT_DIR
#define INPUT_DIR "./"
#endif

int main() {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%sday${DAY}.txt", INPUT_DIR);

    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("failed to open input file");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // process line
    }

    fclose(file);

    printf("day ${DAY} solution: TODO\n");

    return 0;
}
EOF
echo "Created source file: ${SRC_DIR}/day${DAY}.c"

# CMakeLists update
if grep -q "day${DAY}" "$CMAKE_FILE"; then
    echo "CMakeLists.txt already contains day${DAY}, skipping update."
else
    echo "" >> "$CMAKE_FILE"
    echo "# Day ${DAY}" >> "$CMAKE_FILE"
    echo "add_executable(day${DAY} src/day${DAY}/day${DAY}.c)" >> "$CMAKE_FILE"
    echo "Updated CMakeLists.txt"
fi

echo "Done! Ready for Day ${DAY}."
