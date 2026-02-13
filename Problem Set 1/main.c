/*
Driver for Game of Life assignment in CPSC 223 Spring 2026

Author: Mateo Rodriguez
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "life.h"
#include "helpers.h"

int main(int argc, char *argv[])
{
    /*
     * Accept two command-line arguments.
     * time_steps:
     *      a positive integer describing how many "generations" the simulation
     *      will run for.
     * init:
     *      a string consisting of the characters '0' and '1', of length ROWS * COLS,
     *      representing the initial state for this run of Game of Life.
     */
    assert(argc == 3);

    char *time_steps_str = argv[1];
    int time_steps = atoi(time_steps_str);
    assert(time_steps > 0);

    char *init_str = argv[2];

    // useful when testing locally, to make sure I don't mess up an input
    size_t dim = 0;

    for (char *init_str_p = init_str; *init_str_p != '\0'; init_str_p++)
    {
        dim++;
        assert(*init_str_p == '0' || *init_str_p == '1');
    }

    assert(dim == COLS * ROWS);

    /*
     * Create a new statically-allocated array of size ROWS x COLS
     */

    int field[ROWS][COLS];

    for (size_t i = 0; i < ROWS; i++)
    {
        for (size_t j = 0; j < COLS; j++)
        {
            field[i][j] = init_str[i * COLS + j] == '0' ? DEAD : ALIVE;
        }
    }

    /*
     * TODO: Print the initial values held in the field
     */
    print_initial(field);

    int next_field[ROWS][COLS];

    int (*field_p)[ROWS][COLS] = &field;
    int (*next_field_p)[ROWS][COLS] = &next_field;

    /*
     * TODO: Run the game time_steps times, printing the field at the end of
     * each step
     */
    for (size_t i = 1; i <= time_steps; i++)
    {
        compute_next_gen(*field_p, *next_field_p);
        print_generation(*next_field_p, i);

        int (*tmp)[ROWS][COLS] = field_p;
        field_p = next_field_p;
        next_field_p = tmp;
    }

    /*
     * Print "Done." then exit.
     */
    printf("Done.\n");
    return 0;
}
