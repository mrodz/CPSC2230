/*
Driver for Game of Life assignment in CPSC 223 Fall 2023

Author: Mateo Rodriguez
*/

#include "constants.h"
#include "life.h"
#include "helpers.h"

#include <assert.h>
#include <stdio.h>

// I really wanted to display the dimension as a compile-time string.
// https://gcc.gnu.org/onlinedocs/gcc-5.5.0/cpp/Stringification.html
#define view_comptime_dim(x) #x
#define dim(x) view_comptime_dim(x)

static const char command_line_help[] =
    "Usage:\n"
    "  Life <time_steps> <init>\n"
    "\n"
    "Arguments:\n"
    "  time_steps\n"
    "      A positive integer specifying how many generations the\n"
    "      simulation will run.\n"
    "\n"
    "  init\n"
    "      A string of characters consisting only of '0' and '1',\n"
    "      with length (" dim(ROWS) "*" dim(COLS) "), representing the initial state\n"
                                                  "      of the Game of Life grid.\n";

int main(int argc, char *argv[])
{

    ProgramArguments *args;
    ProgramArgumentsResult result;

    if ((result = init_args(argc, argv, &args)) != CLI_OK)
    {
        const char *fmt = fmt_args_result(result);
        fprintf(stderr, "Error: %s\n\n%s", fmt, command_line_help);
        return 1;
    }

    /*
     * Create a new statically-allocated array of size ROWS x COLS
     */

    int matrix[ROWS][COLS];

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            char index = args->init[i * ROWS + j];
            matrix[i][j] = index == '1' ? 1 : 0;
        }
    }

    /*
     * Print the initial values held in the field
     */

    print_initial(matrix);

    /*
     * Run the game time_steps times, printing the field at the end of
     * each step
     */

    int (*matrix_p)[ROWS][COLS] = &matrix;

    int next[ROWS][COLS];
    int (*next_p)[ROWS][COLS] = &next;

    for (int i = 1; i <= args->time_steps; i++)
    {
        compute_next_gen(*matrix_p, *next_p);

        print_generation(*next_p, i);

        int (*tmp)[ROWS][COLS] = matrix_p;
        matrix_p = next_p;
        next_p = tmp;
    }

    /*
     * Print "Done." then exit.
     */
    printf("Done.\n");

    deinit_args(&args);
    assert(args == NULL);

    return 0;
}
