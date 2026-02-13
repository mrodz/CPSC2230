/*
Implementations for core functions for Game of Life assignment in CPSC 223 fall 2024

Author: Alan Weide
Modified by: Mateo Rodriguez
Changelog:
1/22/2025 @ 3:21pm - implement `is_alive`
1/22/2025 @ 3:23pm - implement `num_living_neighbors`
1/22/2025 @ 6:00pm -
 */

#include "life.h"

#include <stdio.h>

/**
 *  we'll let `0` represent a `DEAD` cell and `1` represent an `ALIVE` cell):
 *
 */
bool is_alive(int field[ROWS][COLS], size_t i, size_t j)
{
    return field[i][j] == 1;
}

// cheeky macro to make the code cleaner.
// behavior in words:
// > "if there can be a neighbor at i, j and the neighbor is
// > dead, then remove the neighbor from the mask"
//
// when macros output blocks like an if statement, you're
// supposed to wrap it in a do-while:
// https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Macros.html
#define STATE_CHECK(mask, i, j)                            \
    do                                                     \
    {                                                      \
        if ((state & mask) == mask && field[i][j] == DEAD) \
        {                                                  \
            state ^= mask;                                 \
        }                                                  \
    } while (0);

/**
 * @returns a bitmask that represents where alive neighbors are found
 * around the cell at i, j. The key to the bitmask is:
 *
 * 10000000 - top
 * 01000000 - top-left
 * 00100000 - top-right
 * 00010000 - bottom
 * 00001000 - bottom-left
 * 00000100 - bottom-right
 * 00000010 - left
 * 00000001 - right
 *
 * I learned about bitmasks from my work doing low level embedded programming.
 */
char state_of_piece(int field[ROWS][COLS], size_t i, size_t j)
{
    unsigned char t = 0x80;
    unsigned char tl = 0x40;
    unsigned char tr = 0x20;
    unsigned char b = 0x10;
    unsigned char bl = 0x08;
    unsigned char br = 0x04;
    unsigned char l = 0x02;
    unsigned char r = 0x01;

    unsigned char state = t | tl | tr | b | bl | br | l | r;

    if (i == 0)
        state &= ~(t | tl | tr);

    if (j == 0)
        state &= ~(l | tl | bl);

    if (i == ROWS - 1)
        state &= ~(bl | b | br);

    if (j == COLS - 1)
        state &= ~(tr | r | br);

    // begin checks

    STATE_CHECK(t, i - 1, j);
    STATE_CHECK(tl, i - 1, j - 1);
    STATE_CHECK(tr, i - 1, j + 1);

    STATE_CHECK(l, i, j - 1);
    STATE_CHECK(r, i, j + 1);

    STATE_CHECK(b, i + 1, j);
    STATE_CHECK(bl, i + 1, j - 1);
    STATE_CHECK(br, i + 1, j + 1);

    return state;
}

unsigned int num_living_neighbors(int field[ROWS][COLS], size_t i, size_t j)
{
    char state = state_of_piece(field, i, j);

    unsigned int result = 0;

    // Brian Kernighan's algorithm
    while (state)
    {
        state &= (state - 1);
        result++;
    }

    return result;
}

/**
 * Any alive cell with fewer than two live neighbors dies
 * Any alive cell with two or three live neighbors stays alive
 * Any alive cell with more than three live neighbors dies
 * Any dead cell with exactly three live neighbors becomes alive
 */
int get_next_state(int field[ROWS][COLS], size_t i, size_t j)
{
    unsigned int living_neighbors_count = num_living_neighbors(field, i, j);

    // printf("[%ld,%ld] living_neighbors_count = %d\n", i,j,living_neighbors_count);

    int alive = field[i][j] == ALIVE;

    // Any alive cell with fewer than two live neighbors dies
    if (alive && living_neighbors_count < 2)
    {
        return DEAD;
    }

    // Any alive cell with two or three live neighbors stays alive
    if (alive && (living_neighbors_count == 2 || living_neighbors_count == 3))
    {
        return ALIVE;
    }

    // Any alive cell with more than three live neighbors dies
    if (alive && living_neighbors_count > 3)
    {
        return DEAD;
    }

    // Any dead cell with exactly three live neighbors becomes alive
    if (!alive && living_neighbors_count == 3)
    {
        return ALIVE;
    }

    return DEAD;
}

void compute_next_gen(int cur_field[ROWS][COLS], int next_field[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            int next_state = get_next_state(cur_field, i, j);

            next_field[i][j] = next_state;
        }
    }
}
