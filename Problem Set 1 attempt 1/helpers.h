#pragma once
/*
Interface for helper functions for Game of Life assignment for CPSC 223 Spring 2024.

Author: Alan Weide
Modified by: Mateo Rodriguez
Changelog:
1/22/2026 - I wrote a little command line parsing library
*/

#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"

/**
 * Prints the field formatted for the initial state as described in the README.
 *
 * @param field the 2D array to print
 * @does prints the string "Initial Values" on its own line followed by ROWS lines each containing a row of the field, in a space-separated list beginning at column 4
 */
void print_initial(int field[ROWS][COLS]);

/**
 * Prints the field formatted for the gen-th generation as described in the README.
 *
 * @param field the 2D array to print
 * @does prints the string "Step {gen}" on its own line followed by ROWS lines each containing a row of the field, in a space-separated list beginning at column 4
 */
void print_generation(int field[ROWS][COLS], unsigned int gen);

/**
 * @returns whether a character is ' ', '\n', '\t', '\r'
 */
bool is_space(char x);

/**
 * The input to Conway's Game of Life parsed from CLI input
 */
typedef struct
{
    unsigned int time_steps;
    char *init;
    unsigned int init_length;
} ProgramArguments;

/**
 * Status codes from parsing CLI input
 */
typedef enum
{
    CLI_OK = 0,
    CLI_TIME_STEPS_NAN = 1,
    CLI_TIME_STEPS_CAST = 2,
    CLI_INIT_BAD_CHAR = 3,
    CLI_ARGS_LEN_NEQ_2 = 4,
    CLI_INIT_BAD_LENGTH = 5,
} ProgramArgumentsResult;

/**
 * @returns     an error description as a static string
 */
const char *fmt_args_result(ProgramArgumentsResult result);

/**
 * Deletes the ProgramArguments and replaces the reference with NULL
 *
 * @param args  a pointer to the reference at which an initialized ProgramArguments is stored
 */
ProgramArgumentsResult deinit_args(ProgramArguments **args);

/**
 * Initializes program arguments for Problem Set 1.
 *
 * Accept two command-line arguments, which will appear in the
 * following order:
 * time_steps:
 *      a positive integer describing how many "generations" the simulation
 *      will run for.
 * init:
 *      a string consisting of the characters '0' and '1', of length ROWS * COLS,
 *      representing the initial state for this run of Game of Life.
 *
 * @param argc  passed directly from libc
 * @param argv  passed directly from libc
 * @param dst   a pointer to the reference that an initialized ProgramArguments is written to
 * @returns     a ProgramArgumentsResult to match against. `dst` will only be initialized if
 *              the output is `CLI_OK`.
 */
ProgramArgumentsResult init_args(int argc, char *argv[], ProgramArguments **dst);