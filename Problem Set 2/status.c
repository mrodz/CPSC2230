#include "status.h"
#include <stdlib.h>

const char *status_string(int status) {
    const char *result = NULL;

    if ((result = city_status_string(status)) != NULL) {
        return result;
    }

    if ((result = arguments_status_string(status)) != NULL) {
        return result;
    }

    if ((result = tsp_status_string(status)) != NULL) {
        return result;
    }

    return "Unknown error";
}

const char *city_status_string(city_status status)
{
    if (status == STATUS_OK)
        return "Success";
        
    switch (status)
    {
    case CITY_MALLOC_ERROR:
        return "City: memory allocation failed";
    case CITY_UNKNOWN_CITY:
        return "Encountered an unknown city";
    case CITY_PARSE_LAT:
        return "Could not parse latitude";
    case CITY_PARSE_LON:
        return "Could not parse longitude";
    default:
        return NULL;
    }
}

const char *arguments_status_string(arguments_status status)
{
    if (status == STATUS_OK)
        return "Success";
        
    switch (status)
    {
    case ARGUMENTS_USAGE_0:
        return "Expected file path";
    case ARGUMENTS_UNKNOWN_HEURISTIC:
        return "Unknown heuristic value (expected one of: " GIVEN_STR ", " NEAREST_STR ", " INSERT_STR ")";
    case ARGUMENTS_MALLOC_ERROR:
        return "Arguments: memory allocation failed";
    default:
        return NULL;
    }
}

const char *tsp_status_string(tsp_status status)
{
    if (status == STATUS_OK)
        return "Success";
        
    switch (status)
    {
    case TSP_MALLOC_ERROR:
        return "TSP: memory allocation failed";
    case TSP_CITY_SETUP:
        return "Could not set up user inputted cities";
    default:
        return NULL;
    }
}

