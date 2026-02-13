#include <string.h>

#include "cli.h"
#include "city.h"
#include "tsp.h"

#define COLON_LOC 11

void print_line_to_spec(tsp_result *result)
{
  // the colon is in column 11 (counting from 1)
  const char *method_str = heuristics_to_string(result->method);
  int number_of_colon_pads = COLON_LOC - strlen(method_str) - 2;
  printf("-%s", method_str);
  for (int j = 0; j < number_of_colon_pads; j++)
    printf(" ");
  printf(":");

  char dist_fmt[11] = {0};

  // https://stackoverflow.com/questions/499939/how-to-extract-the-decimal-part-from-a-floating-point-number-in-c
  int dist_ipart = (int)result->distance;
  int would_write = snprintf(dist_fmt, sizeof(dist_fmt) - 1, "%d", dist_ipart);
  if (would_write > sizeof(dist_fmt))
  {
    // switch to scientific notation when the total distance does not fit the space provided
    // >>>>> with whatever spacing you wish
    // https://www.geeksforgeeks.org/c/format-specifiers-in-c/
    would_write = snprintf(dist_fmt, sizeof(dist_fmt), "%e", result->distance);

    for (int j = 0; j < sizeof(dist_fmt) - would_write - 1; j++)
      printf(" ");
    printf("%s", dist_fmt);
  }
  else
  {
    for (int j = 0; j < sizeof(dist_fmt) - would_write - 1; j++)
      printf(" ");
    printf("%s", dist_fmt);
    memset(dist_fmt, 0, sizeof(dist_fmt));
    snprintf(dist_fmt, sizeof(dist_fmt) - 1, "%.2f", result->distance - dist_ipart);
    printf("%s", dist_fmt + 1);
  }

  for (int j = 0; j < result->order_len; j++)
  {
    printf(" %s", result->order[j]->name);
  }
  printf("\n");
}

int main(int argc, char **argv)
{
  arguments *args;
  arguments_status args_ok = arguments_init(&args, argc, argv);
  // DEFER: arguments_deinit(&args);

  if (args_ok != STATUS_OK)
  {
    fprintf(stderr, "Could not parse command line arguments: %s\n", status_string(args_ok));
    return args_ok;
  }

  city **cities;
  size_t cities_len = 0;

  FILE *file = fopen(args->path, "r");
  city_status city_ok = read_file(file, &cities, &cities_len);
  fclose(file);
  // DEFER: cityarray_deinit(&cities, &cities_len);

  if (city_ok != STATUS_OK)
  {
    fprintf(stderr, "Could not parse cities: %s\n", status_string(city_ok));
    arguments_deinit(&args);
    return city_ok;
  }

  for (int i = 0; i < args->methods_len; i++)
  {
    heuristics method = args->methods[i];
    tsp_result *result;
    tsp_status tsp_ok = tsp_dyn(method)(args, cities, cities_len, &result);
    // DEFER: tsp_result_deinit(&result);

    if (tsp_ok != STATUS_OK)
    {
      fprintf(stderr, "Could not run TSP: %s\n", status_string(city_ok));
      arguments_deinit(&args);
      return city_ok;
    }

    print_line_to_spec(result);

    tsp_result_deinit(&result);
  }

  // DEFER:
  cityarray_deinit(&cities, cities_len);
  arguments_deinit(&args);

  return 0;
}
