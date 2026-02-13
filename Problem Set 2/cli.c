#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#include "cli.h"
#include "status.h"

const char * heuristics_to_string(heuristics h) {
    switch (h) {
        case GIVEN:
            return GIVEN_STR;
        case NEAREST:
            return NEAREST_STR;
        case INSERT:
            return INSERT_STR;
        default:
            return NULL;
    }
}

arguments_status heuristics_from_string(const char *string, heuristics *dst)
{
    if (string == NULL)
        return ARGUMENTS_UNKNOWN_HEURISTIC;

    if (string[0] == '-')
        string++;

    if (strcmp(string, GIVEN_STR) == 0)
        *dst = GIVEN;
    else if (strcmp(string, NEAREST_STR) == 0)
        *dst = NEAREST;
    else if (strcmp(string, INSERT_STR) == 0)
        *dst = INSERT;
    else
        return ARGUMENTS_UNKNOWN_HEURISTIC;

    return STATUS_OK;
}

arguments_status arguments_init(arguments **dst, int argc, char *argv[])
{
    arguments_status err;

    heuristics *methods = NULL;
    
    arguments *result = malloc(sizeof(arguments));
    // ERRDEFER free(result);

    if (result == NULL)
    {
        err = ARGUMENTS_MALLOC_ERROR;
        goto ERRDEFER;
    }

    result->cities = NULL;
    result->cities_buf = NULL;
    result->cities_len = 0;
    result->methods = NULL;
    result->path = NULL;

    char *cities_buf = NULL;
    char **cities = NULL;

    if (argc < 2)
    {
        err = ARGUMENTS_USAGE_0;
        goto ERRDEFER;
    }

    char *const path_argv = argv[1];
    size_t path_len = strlen(path_argv);

    size_t methods_len = 0;
    size_t methods_cap = 2;
    methods = calloc(sizeof(heuristics), methods_cap);
    // ERRDEFER: free(methods);

    if (methods == NULL)
    {
        err = ARGUMENTS_MALLOC_ERROR;
        goto ERRDEFER;
    }

    size_t heuristics_i;
    for (heuristics_i = 2; heuristics_i < argc && argv[heuristics_i][0] == '-'; heuristics_i++)
    {
        if (methods_len >= methods_cap)
        {
            size_t methods_cap_new = methods_cap * 2;
            heuristics *methods_tmp = realloc(methods, sizeof(heuristics) * methods_cap_new);
            if (methods_tmp == NULL)
            {
                err = ARGUMENTS_MALLOC_ERROR;
                goto ERRDEFER;
            }
            methods = methods_tmp;
            methods_cap = methods_cap_new;
        }

        heuristics this_heuristic;
        if ((err = heuristics_from_string(argv[heuristics_i], &this_heuristic)) == STATUS_OK)
        {
            methods[methods_len++] = this_heuristic;
        }
        else
        {
            goto ERRDEFER;
        }
    }

    size_t cities_buf_cap = 0;
    const size_t cities_len = argc - heuristics_i;

    cities = calloc(cities_len, sizeof(char *));
    // ERRDEFER free(cities);

    if (cities == NULL && cities_len != 0)
    {
        err = ARGUMENTS_MALLOC_ERROR;
        goto ERRDEFER;
    }

    for (int i = heuristics_i, ci = 0; i < argc; i++, ci++)
    {
        size_t city_len = strlen(argv[i]);
        cities_buf_cap += city_len + 1;
    }

    cities_buf = calloc(cities_buf_cap, sizeof(char));
    // ERRDEFER free(cities_buf)

    if (cities_buf == NULL && cities_buf_cap != 0)
    {
        err = ARGUMENTS_MALLOC_ERROR;
        goto ERRDEFER;
    }

    char *cities_buf_p = cities_buf;

    for (int i = heuristics_i, cities_i = 0; i < argc; i++, cities_i++)
    {
        size_t city_len = strlen(argv[i]);
        cities[cities_i] = cities_buf_p;
        memcpy(cities_buf_p, argv[i], city_len + 1);
        cities_buf_p += city_len + 1;
    }

    result->path = calloc(sizeof(char), path_len + 1);
    // ERRDEFER free(result->path);

    if (result->path == NULL)
    {
        err = ARGUMENTS_MALLOC_ERROR;
        goto ERRDEFER;
    }

    strcpy(result->path, path_argv);

    result->methods = methods;
    result->cities_len = cities_len;
    result->cities_buf = cities_buf;
    result->cities = cities;
    result->methods_len = methods_len;

    *dst = result;

    return STATUS_OK;

ERRDEFER:
    if (result->path != NULL)
        free(result->path);
    if (cities_buf != NULL)
        free(cities_buf);
    if (cities != NULL)
        free(cities);
    if (methods != NULL)
        free(methods);
    if (result != NULL)
        free(result);

    *dst = NULL;
    return err;
}

arguments_status arguments_deinit(arguments **dst)
{
    if (dst == NULL)
        return STATUS_OK;

    if ((*dst)->path != NULL)
        free((*dst)->path);
    if ((*dst)->cities != NULL)
        free((*dst)->cities);
    if ((*dst)->cities_buf != NULL)
        free((*dst)->cities_buf);
    if ((*dst)->methods != NULL)
        free((*dst)->methods);

    free(*dst);

    *dst = NULL;

    return STATUS_OK;
}

void print_arguments(FILE *out, const arguments *args)
{
    fprintf(out, "arguments:\n");
    fprintf(out, "  path: %s\n", args->path);

    fprintf(out, "  passed:\n");

    if (args->methods_len == 0)
    {
        fprintf(out, "    <none>\n");
    }
    else
    {

        for (int i = 0; i < args->methods_len; i++)
        {
            fprintf(out, "    -%s\n", heuristics_to_string(args->methods[i]));
        }
    }

    if (args->cities_len == 0)
    {
        fprintf(out, "  cities:\n    <none>\n");
    }
    else
    {
        fprintf(out, "  cities:\n");
        for (int i = 0; i < args->cities_len; i++)
        {
            fprintf(out, "    %s\n", args->cities[i]);
        }
    }
}