#include "median.h"

#include <stddef.h>

double median(int *array, size_t len) {
    size_t middle_index = len / 2;

    if (len % 2 == 0) {
        return (array[middle_index] + array[middle_index - 1]) / 2.0;
    }
    
    return (double) array[middle_index];
}