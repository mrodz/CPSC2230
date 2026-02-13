/**
 * tsp.h
 * Function declarations and struct definitions for CPSC 223 PSet 2 (TSP)
 *
 * @author CPSC 223 Staff and you
 * @version 2025.01.31.0
 */

#ifndef __TSP_H__
#define __TSP_H__

#include <stdio.h>
#include <stddef.h>

#include "city.h"
#include "location.h"
#include "cli.h"
#include "status.h"

typedef struct _tsp_result {
    heuristics method;
    double distance;
    city **order;
    size_t order_len;
} tsp_result;

tsp_status (*tsp_dyn (heuristics method))(arguments *args, city **cities, size_t cities_len, tsp_result **dst);
tsp_status given(arguments *args, city **cities, size_t cities_len, tsp_result **dst);
tsp_status nearest(arguments *args, city **cities, size_t cities_len, tsp_result **dst);
tsp_status insert(arguments *args, city **cities, size_t cities_len, tsp_result **dst);

tsp_status tsp_result_deinit(tsp_result **t);

#endif