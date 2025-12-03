cmake_minimum_required(VERSION 3.10)
project(AoC2025 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_definitions(-DINPUT_DIR="${CMAKE_SOURCE_DIR}/inputs/")


# Day 01
add_executable(day01 src/day01/day01.c)
add_executable(day01-part2 src/day01/day01-part2.c)

# Day 02
add_executable(day02 src/day02/day02.c)
add_executable(day02-part2 src/day02/day02-part2.c)

# Day 03
add_executable(day03 src/day03/day03.c)
add_executable(day03-part2 src/day03/day03-part2.c)
