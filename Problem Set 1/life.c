/*
Implementations for core functions for Game of Life assignment in CPSC 223 Spring 2026

Author: Alan Weide
Modified by: Mateo Rodriguez
Changelog:
1/27 @ 3:46pm - implemented `is_alive`
1/27 @ 4:00pm ish - finished implementation details
 */

#include "life.h"

#include <stdio.h>

bool is_alive(int field[ROWS][COLS], size_t i, size_t j)
{
    return field[i][j] == ALIVE;
}

unsigned int num_living_neighbors(int field[ROWS][COLS], size_t i, size_t j)
{
    unsigned int count = 0;

    bool bottom = i < ROWS - 1;
    bool top = i > 0;
    bool right = j < COLS - 1;
    bool left = j > 0;

    if (top)
    {
        if (is_alive(field, i - 1, j))
            count++;
        if (left && is_alive(field, i - 1, j - 1))
            count++;
        if (right && is_alive(field, i - 1, j + 1))
            count++;
    }

    if (bottom)
    {
        if (is_alive(field, i + 1, j))
            count++;
        if (left && is_alive(field, i + 1, j - 1))
            count++;
        if (right && is_alive(field, i + 1, j + 1))
            count++;
    }

    if (left && is_alive(field, i, j - 1))
        count++;
    if (right && is_alive(field, i, j + 1))
        count++;

    return count;
}

int get_next_state(int field[ROWS][COLS], size_t i, size_t j)
{
    unsigned int neighbors = num_living_neighbors(field, i, j);

    bool alive = is_alive(field, i, j);

    if (alive)
    {
        // Any alive cell with fewer than two live neighbors dies
        if (neighbors < 2)
            return DEAD;
        // Any alive cell with more than three live neighbors dies
        if (neighbors > 3)
            return DEAD;
        // Any alive cell with two or three live neighbors stays alive
        return ALIVE;
    }

    // Any dead cell with exactly three live neighbors becomes alive
    if (!alive && neighbors == 3)
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
            next_field[i][j] = get_next_state(cur_field, i, j);
        }
    }
}
