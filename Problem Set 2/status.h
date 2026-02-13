#ifndef __STATUS_H__
#define __STATUS_H__

#define STATUS_OK 0

#define GIVEN_STR "given"
#define NEAREST_STR "nearest"
#define INSERT_STR "insert"

typedef enum _city_status {
    CITY_MALLOC_ERROR = 1,
    CITY_UNKNOWN_CITY,
    CITY_PARSE_LAT,
    CITY_PARSE_LON,
} city_status;

typedef enum _arguments_status {
    ARGUMENTS_USAGE_0 = CITY_PARSE_LON + 1,
    ARGUMENTS_UNKNOWN_HEURISTIC,
    ARGUMENTS_MALLOC_ERROR,
} arguments_status;

typedef enum _tsp_status {
    TSP_MALLOC_ERROR = ARGUMENTS_MALLOC_ERROR + 1,
    TSP_CITY_SETUP,
} tsp_status;

const char *status_string(int status);
const char *city_status_string(city_status status);
const char *arguments_status_string(arguments_status status);
const char *tsp_status_string(tsp_status status);



#endif