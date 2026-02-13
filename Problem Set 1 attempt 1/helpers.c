/*
Implementations of helper functions for Game of Life assignment for CPSC 223 Spring 2024.

Author: Alan Weide
Modified by: Mateo Rodriguez
Changelog:
1/22/2026 - I wrote a little command line parsing library
*/
#include "helpers.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "life.h"

#define ALIVE_CH '#'
#define DEAD_CH ' '

void print_initial(int field[ROWS][COLS])
{
    printf("Initial Values\n");
    for (size_t i = 0; i < ROWS; i++)
    {
        printf("    ");
        for (size_t j = 0; j < COLS; j++)
        {
            printf("%c ", is_alive(field, i, j) ? ALIVE_CH : DEAD_CH);
        }
        printf("\n");
    }
}

void print_generation(int field[ROWS][COLS], unsigned int gen)
{
    printf("Step %d\n", gen);
    for (size_t i = 0; i < ROWS; i++)
    {
        printf("    ");
        for (size_t j = 0; j < COLS; j++)
        {
            printf("%c ", is_alive(field, i, j) ? ALIVE_CH : DEAD_CH);
        }
        printf("\n");
    }
}

bool is_space(char x)
{
    return x == ' ' || x == '\n' || x == '\t' || x == '\r';
}

const char *fmt_args_result(ProgramArgumentsResult result)
{
    switch (result)
    {
    case CLI_OK:
        return "Ok";
    case CLI_TIME_STEPS_NAN:
        return "Argument `time_steps` should not contain non-digit characters";
    case CLI_TIME_STEPS_CAST:
        return "Argument `time_steps` should not be negative or too big";
    case CLI_INIT_BAD_CHAR:
        return "Argument `init` should not contain characters other than '0', '1'";
    case CLI_ARGS_LEN_NEQ_2:
        return "Program expected two arguments";
    case CLI_INIT_BAD_LENGTH:
        return "Argument `init` should have length ROWS * COLS";
    default:
        return "Unknown result";
    }
}

ProgramArgumentsResult deinit_args(ProgramArguments **args)
{
    if (args == NULL || *args == NULL)
    {
        return CLI_OK;
    }

    free((*args)->init);
    (*args)->init = NULL;
    free(*args);
    *args = NULL;

    return CLI_OK;
}

ProgramArgumentsResult init_args(int argc, char *argv[], ProgramArguments **dst)
{
    assert(dst != NULL);
    assert(argv != NULL);

    // skip program name
    argv++;
    argc--;

    if (argc != 2)
    {
        return CLI_ARGS_LEN_NEQ_2;
    }

    char *time_steps_str = argv[0];

    // skip any left-padding
    while (is_space(*time_steps_str))
    {
        time_steps_str++;
    }

    char *end_ptr;
    long time_steps = strtol(time_steps_str, &end_ptr, 10);

    // the string did not contain any digits
    if (end_ptr == time_steps_str)
    {
        return CLI_TIME_STEPS_NAN;
    }

    // skip any right-padding
    while (is_space(*end_ptr))
    {
        end_ptr++;
    }

    // the string contains non-digit chars
    if (*end_ptr != '\0')
    {
        return CLI_TIME_STEPS_NAN;
    }

    // negative number
    if (time_steps < 0)
    {
        return CLI_TIME_STEPS_CAST;
    }

    // overflow?
    if (time_steps >= UINT_MAX)
    {
        return CLI_TIME_STEPS_CAST;
    }

    char *init = argv[1];

    unsigned int init_length = 0;

    for (char *init_p = init; *init_p != '\0'; init_p++, init_length++)
    {
        if (*init_p != '0' && *init_p != '1')
        {
            return CLI_INIT_BAD_CHAR;
        }
    }

    if (init_length != ROWS * COLS)
    {
        return CLI_INIT_BAD_LENGTH;
    }

    char *init_dst = malloc(sizeof(char) * init_length);
    strncpy(init_dst, init, init_length);
    ProgramArguments *result = malloc(sizeof(ProgramArguments));

    // safe cast
    result->time_steps = (unsigned int)time_steps;
    result->init = init_dst;
    result->init_length = init_length;

    *dst = result;

    return CLI_OK;
}
