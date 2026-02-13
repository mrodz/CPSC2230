#pragma once

#include <stdio.h>
#include <stddef.h>

size_t parse_int_array(FILE *stream, int *dst, size_t max_capacity);
FILE *read_file(char *path);