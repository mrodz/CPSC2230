#pragma once

#ifndef __CLI_H__
#define __CLI_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "status.h"

typedef enum _heuristics
{
    NO_METHOD = 0x0,
    GIVEN = 0x1,
    NEAREST = 0x2,
    INSERT = 0x4,
} heuristics;

typedef struct _arguments
{
    size_t cities_len;
    size_t methods_len;
    char *path;
    heuristics *methods;
    char *cities_buf;
    char **cities;
} arguments;

const char* arguments_status_string(arguments_status status);
arguments_status arguments_init(arguments **dst, int argc, char *argv[]);
arguments_status heuristics_from_string(const char *string, heuristics *dst);
const char * heuristics_to_string(heuristics h);
arguments_status arguments_deinit(arguments **dst);
void print_arguments(FILE *out, const arguments *args);

#endif
