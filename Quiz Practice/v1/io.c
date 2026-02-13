#include "io.h"
#include <stdio.h>

size_t parse_int_array(FILE *stream, int *dst, size_t max_capacity) {
    size_t len = 0;

    for (int p; fscanf(stream, "%d", &p) > 0 && len < max_capacity; len++) {
        dst[len] = p;
    }

    return len;
}

FILE *read_file(char *path) {
    return fopen(path, "r");
}