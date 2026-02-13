/**
 * tsp.c
 * Builds tours of cities in input according to one of three possible
 * heuristics.  Names of cities are given on the command line along
 * with the heuristics to use and the name of a file containing the
 * locations (latitude, longitude) of the cities.  For example,
 *
 * ./TSP ne_6.dat -given -nearest -insert HVN ALB MHT BDL ORH PVD
 *
 * where ne_6.dat could contain
 *
 * HVN,41.26388889,-72.88694444
 * ALB,42.74916667,-73.80194444
 * MHT,42.93277778,-71.43583333
 * BDL,41.93916667,-72.68333333
 * ORH,42.26722222,-71.87555556
 * PVD,41.72388889,-71.42833333
 *
 * @author CPSC 223 Staff and Mateo Rodriguez
 * @version 2025.01.31.1
 */

#define _GNU_SOURCE

// SEE THIS FILE FOR DECLARATIONS AND DOCUMENTATION OF SUGGESTED FUNCTIONS
#include "tsp.h"

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#include "city.h"
#include "cli.h"
#include "location.h"

tsp_status (*tsp_dyn (heuristics method))(arguments *args, city **cities, size_t cities_len, tsp_result **dst) {
  switch (method) {
    case GIVEN:
      return &given;
    case NEAREST:
      return &nearest;
    case INSERT:
      return &insert;
    default:
      return NULL;
  }
}

tsp_status given(arguments *args, city **cities, size_t cities_len, tsp_result **dst)
{
  tsp_status err;
  city **input = NULL;
  city **order = NULL;

  tsp_result *result = malloc(sizeof(tsp_result));
  // ERRDEFER: free(result);

  if (result == NULL)
  {
    err = TSP_MALLOC_ERROR;
    goto ERRDEFER;
  }

  if (args->cities_len == 0)
  {
    result->method = GIVEN;
    result->distance = 0;
    result->order = NULL;
    result->order_len = 0;
    goto DEFER;
  }

  order = calloc(args->cities_len + 1, sizeof(city *));
  // ERRDEFER: cityarray_deinit(&order);

  if (order == NULL)
  {
    err = TSP_MALLOC_ERROR;
    goto ERRDEFER;
  }

  city_status city_ok = populate_arg_cities(args, cities, cities_len, &input);
  // DEFER: cityarray_deinit(&input);

  if (city_ok != STATUS_OK)
  {
    err = TSP_CITY_SETUP;
    goto ERRDEFER;
  }

  // guaranteed to be at least one
  city *first_city = input[0];
  city *const final_destination = first_city;

  city *first_city_copy = city_copy(first_city); // first_city is deleted in defer

  if (first_city_copy == NULL)
  {
    err = TSP_MALLOC_ERROR;
    goto ERRDEFER;
  }

  order[0] = first_city_copy;

  if (args->cities_len == 1)
  {
    result->distance = 0;
    result->method = GIVEN;
    result->order_len = 1;
    result->order = order;

    goto DEFER;
  }

  double total_distance = 0;

  for (size_t i = 1; i < args->cities_len; i++)
  {
    city *next_city = input[i];

    city *next_city_copy = city_copy(next_city); // first_city is deleted in defer

    if (next_city_copy == NULL)
    {
      err = TSP_MALLOC_ERROR;
      goto ERRDEFER;
    }

    order[i] = next_city_copy;

    total_distance += location_distance(&first_city->loc, &next_city->loc);

    first_city = next_city;
  }

  total_distance += location_distance(&first_city->loc, &final_destination->loc);
  order[args->cities_len] = city_copy(final_destination);

  result->method = GIVEN;
  result->distance = total_distance;
  result->order = order;
  result->order_len = args->cities_len + 1;

DEFER:
  cityarray_deinit(&input, args->cities_len);

  *dst = result;
  return STATUS_OK;

ERRDEFER:
  cityarray_deinit(&input, args->cities_len);

  if (order != NULL)
    cityarray_deinit(&order, args->cities_len + 1);

  if (result != NULL)
    free(result);

  return err;
}

tsp_status nearest(arguments *args, city **cities, size_t cities_len, tsp_result **dst)
{
  tsp_status err;
  city **input = NULL;
  city *end_destination = NULL;
  tsp_result *result = malloc(sizeof(tsp_result));
  // ERRDEFER: free(result);

  if (result == NULL)
  {
    err = TSP_MALLOC_ERROR;
    goto ERRDEFER;
  }

  if (args->cities_len == 0)
  {
    result->method = NEAREST;
    result->distance = 0;
    result->order = NULL;
    result->order_len = 0;
    goto DEFER;
  }

  city **order = calloc(args->cities_len + 1, sizeof(city *));
  // ERRDEFER: cityarray_deinit(&order);

  if (order == NULL)
  {
    err = TSP_MALLOC_ERROR;
    goto ERRDEFER;
  }

  city_status city_ok = populate_arg_cities(args, cities, cities_len, &input);
  // DEFER: cityarray_deinit(&input);

  if (city_ok != STATUS_OK)
  {
    err = TSP_CITY_SETUP;
    goto ERRDEFER;
  }

  city *last = input[0];

  end_destination = city_copy(last);
  // ERRDEFER: city_deinit(&end_destination);

  if (end_destination == NULL)
  {
    err = TSP_MALLOC_ERROR;
    goto ERRDEFER;
  }

  if (args->cities_len == 1)
  {
    order[0] = end_destination;
    end_destination = NULL;

    result->distance = 0;
    result->method = NEAREST;
    result->order_len = 1;
    result->order = order;
    goto DEFER;
  }

  order[0] = city_copy(end_destination); // cleanup deffered in order

  if (order[0] == NULL)
  {
    err = TSP_MALLOC_ERROR;
    goto ERRDEFER;
  }

  double total_distance = 0;

  double winning_distance = DBL_MAX;

  for (int order_i = 1; order_i < args->cities_len; order_i++)
  {
    size_t closest = 1;

    for (int i = 1; i < args->cities_len; i++)
    {
      if (input[i] == NULL)
        continue;

      city *candidate = input[i];
      double candidate_distance = location_distance(&candidate->loc, &last->loc);
      if (candidate_distance < winning_distance)
      {
        closest = i;
        winning_distance = candidate_distance;
      }
    }

    total_distance += winning_distance;
    // https://stackoverflow.com/questions/23278930/what-is-dbl-max-in-c
    winning_distance = DBL_MAX;
    order[order_i] = city_copy(input[closest]);

    if (order[order_i] == NULL)
    {
      err = TSP_MALLOC_ERROR;
      goto ERRDEFER;
    }

    last = order[order_i];
    city_deinit(&input[closest]);
    input[closest] = NULL;
  }

  total_distance += location_distance(&end_destination->loc, &last->loc);
  order[args->cities_len] = end_destination;
  end_destination = NULL;

  result->method = NEAREST;
  result->distance = total_distance;
  result->order = order;
  result->order_len = args->cities_len + 1;

DEFER:
  cityarray_deinit(&input, args->cities_len);

  *dst = result;
  return STATUS_OK;
ERRDEFER:
  city_deinit(&end_destination);

  cityarray_deinit(&input, args->cities_len);

  if (order != NULL)
    cityarray_deinit(&order, args->cities_len + 1);

  if (result != NULL)
    free(result);

  return err;
}

tsp_status insert(arguments *args, city **cities, size_t cities_len, tsp_result **dst) {
  tsp_status err;

  tsp_result *result = malloc(sizeof(tsp_result));
  // ERRDEFER: free(result);

  if (result == NULL)
  {
    err = TSP_MALLOC_ERROR;
    goto ERRDEFER;
  }

  result->method = INSERT;
  result->order_len = 0;
  result->order = NULL;
  result->distance = 0;

  *dst = result;

  return STATUS_OK;

ERRDEFER:
  free(result);
  return err;
}

tsp_status tsp_result_deinit(tsp_result **t)
{
  if (t == NULL)
    return STATUS_OK;

  // order is null when there is no input
  if ((*t)->order != NULL)
    cityarray_deinit(&(*t)->order, (*t)->order_len); // ignore fail for now

  free(*t);

  *t = NULL;

  return STATUS_OK;
}