#pragma once

#ifndef __CITY_H__
#define __CITY_H__

#include <stddef.h>

#include "location.h"
#include "status.h"
#include "cli.h"

typedef struct {
  char *name; // a pointer to the city's name on the command-line
  location loc;     // the city's coordinates
  size_t index;     // the city's index on the command line
} city;

city_status parse_city_from_line(const char *line_buffer, size_t index, city **dst);
city_status city_deinit(city **c);
city_status cityarray_deinit(city ***c, size_t len);

/**
 * Reads lat/lon for given cities into the given array.
 *
 * @param in a file open for reading with lines in the form name,lat,lon
 * @param n a nonnegative integer
 * @param cities an array of size n
 */
city_status read_file(FILE *in, city ***dst, size_t *dst_len);

city *city_copy(city *c);

city_status populate_arg_cities(arguments *args, city **cities_ssot, size_t cities_ssot_len, city ***dst);

#endif