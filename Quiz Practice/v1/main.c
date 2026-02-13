#include "io.h"
#include "median.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        perror("Usage: median <path/to/file.txt> capacity");
        return 1;
    }

    char *path = argv[1];
    char *capacity_str = argv[2];

    size_t capacity = atol(capacity_str);

    FILE *file = read_file(path);

    int *array = malloc(sizeof(int) * capacity);

    size_t len = parse_int_array(file, array, capacity);

    double input_median = median(array, len);

    printf("The median is: %lf\n", input_median);

    free(array);
    fclose(file);

    return 0;
}