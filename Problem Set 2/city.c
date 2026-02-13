#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "city.h"
#include "location.h"
#include "cli.h"

city_status read_file(FILE *in, city ***dst, size_t *dst_len)
{
  city_status err;
  city **cities = NULL;
  char *line_buffer = NULL;

  size_t cities_len = 0;
  size_t cities_cap = 3;

  cities = calloc(cities_cap, sizeof(city *));
  // ERRDEFER: free(cities);

  if (cities == NULL)
  {
    err = CITY_MALLOC_ERROR;
    goto ERRDEFER;
  }

  size_t line_buffer_len;
  size_t line_buffer_cap = 16;

  line_buffer = malloc(sizeof(char) * line_buffer_cap);
  // ERRDEFER: free(line_buffer);

  if (line_buffer == NULL)
  {
    err = CITY_MALLOC_ERROR;
    goto ERRDEFER;
  }

  bool eof = false;

  while (!eof)
  {
    while (cities_len < cities_cap)
    {
      line_buffer_len = 0;

      while (true)
      {
        while (line_buffer_len < line_buffer_cap - 1)
        {
          int c = fgetc(in);

          if (c == EOF)
          {
            eof = true;
            goto end;
          }
          if (c == '\n')
            goto end;

          line_buffer[line_buffer_len++] = (char)c;
        }

        size_t line_buffer_cap_new = line_buffer_cap + line_buffer_cap / 2;
        char *line_buffer_tmp = realloc(line_buffer, sizeof(char) * line_buffer_cap_new);
        if (line_buffer_tmp == NULL)
        {
          err = CITY_MALLOC_ERROR;
          goto ERRDEFER;
        }

        line_buffer = line_buffer_tmp;
        line_buffer_cap = line_buffer_cap_new;
      }
    end:
      if (line_buffer_len == 0)
        goto continue_eof;
      
      line_buffer[line_buffer_len] = '\0';
      city *city;
      city_status city_ok = parse_city_from_line(line_buffer, cities_len, &city);
      if (city_ok != STATUS_OK)
      {
        err = city_ok;
        goto ERRDEFER;
      }
      cities[cities_len++] = city;
    }

    // capacity was not big enough

    size_t cities_cap_new = cities_cap + cities_cap / 2;
    city **cities_tmp = realloc(cities, sizeof(city *) * cities_cap_new);
    if (cities_tmp == NULL)
    {
      err = CITY_MALLOC_ERROR;
      goto ERRDEFER;
    }

    for (size_t i = cities_cap; i < cities_cap_new; cities_tmp[i++] = NULL)

    cities = cities_tmp;
    cities_cap = cities_cap_new;

continue_eof:;
  }

  if (line_buffer != NULL)
    free(line_buffer);

  *dst = cities;
  *dst_len = cities_len;

  return STATUS_OK;

ERRDEFER:
  cityarray_deinit(&cities, cities_len);
  
  if (line_buffer != NULL)
    free(line_buffer);

  *dst = NULL;
  *dst_len = 0;

  return err;
}

city_status parse_city_from_line(const char *line_buffer, size_t index, city **dst) {
    city_status err;

    city *result = NULL;
    char *name = NULL;

    result = malloc(sizeof(city));
    // ERRDEFER: free(result);

    if (result == NULL) {
        err = CITY_MALLOC_ERROR;
        goto ERRDEFER;
    }

    size_t name_len;
    const char *name_start = line_buffer;
    
    for (name_len = 0; *line_buffer != '\0' && *line_buffer != ','; line_buffer++, name_len++);

    name = calloc(name_len + 1, sizeof(char));
    // ERRDEFER: free(name);

    if (name == NULL) {
        err = CITY_MALLOC_ERROR;
        goto ERRDEFER;
    }

    memcpy(name, name_start, name_len);

    if (*line_buffer == '\0') {
      err = CITY_PARSE_LAT;
      goto ERRDEFER;
    }

    if (*line_buffer == ',') line_buffer++;
    // for (line_buffer++; *line_buffer != '\0' && *line_buffer == ','; line_buffer++);

    char *end_p = NULL;
    // https://cplusplus.com/reference/cstdlib/strtof/
    long double lat = strtold(line_buffer, &end_p);

    if (line_buffer == end_p) {
      err = CITY_PARSE_LAT;
      goto ERRDEFER;
    }

    line_buffer = end_p;

    if (*line_buffer == '\0') {
      err = CITY_PARSE_LON;
      goto ERRDEFER;
    }

    if (*line_buffer == ',') line_buffer++;
    // for (line_buffer++; *line_buffer != '\0' && *line_buffer == ','; line_buffer++);

    // https://cplusplus.com/reference/cstdlib/strtof/
    long double lon = strtold(line_buffer, &end_p);

    if (line_buffer == end_p) {
      err = CITY_PARSE_LON;
      goto ERRDEFER;
    }

    location loc = {lat, lon};
    result->loc = loc;
    result->name = name;
    result->index = index;

    *dst = result;

    return STATUS_OK;
ERRDEFER:
    if (name != NULL)
        free(name);

    if (result != NULL)
        free(result);

    *dst = NULL;

    return err;
}

city_status city_deinit(city **c) {
    if (c == NULL) return STATUS_OK;
    
    if ((*c)->name != NULL) free((*c)->name);

    free(*c);
    *c = NULL;

    return STATUS_OK;
}

city_status cityarray_deinit(city ***c, size_t len) {
    if (c == NULL || (*c == NULL)) return STATUS_OK;

    for (int i = 0; i < len; i++) {
      city *element = (*c)[i];
      if (element != NULL)
        city_deinit(&element);
    }
    
    free(*c);
    *c = NULL;

    return STATUS_OK;
}

city *city_copy(city *c) {
    city *result = malloc(sizeof(city));
    if (result == NULL) return NULL;
    result->index = c->index;
    result->loc = c->loc;
    result->name = calloc(strlen(c->name) + 1, sizeof(char));
    strcpy(result->name, c->name);
    return result;
}

city_status populate_arg_cities(arguments *args, city **cities_ssot, size_t cities_ssot_len, city ***dst) {
    city_status err;
    city **cities = NULL;
    
    cities = calloc(args->cities_len, sizeof(city*));
    // ERRDEFER: free(cities);

    if (cities == NULL) {
        err = CITY_MALLOC_ERROR;
        goto ERRDEFER;
    }

    for (int i = 0; i < args->cities_len; i++) {
        char *this_name = args->cities[i];

        city *this_ssot_city_copy = NULL;

        for (int j = 0; j < cities_ssot_len; j++) {
            city *this_ssot_city = cities_ssot[j];
            if (strcmp(this_ssot_city->name, this_name) == 0) {
                this_ssot_city_copy = city_copy(this_ssot_city);
                if (this_ssot_city_copy == NULL) {
                    err = CITY_MALLOC_ERROR;
                    goto ERRDEFER;
                }
            }
        }

        if (this_ssot_city_copy == NULL) {
            err = CITY_UNKNOWN_CITY;
            goto ERRDEFER;
        }

        cities[i] = this_ssot_city_copy;
    }

    *dst = cities;
    return STATUS_OK;

ERRDEFER:
    cityarray_deinit(&cities, args->cities_len);
    *dst = NULL;
    return err;
}