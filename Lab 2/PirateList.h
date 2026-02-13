#ifndef PIRATELIST_H
#define PIRATELIST_H

#include <stddef.h>
#include <stdio.h>  

#define MAX_PIRATES 10
#define LINE_MAX 128

typedef struct {
    int pirate_id;
    char name[LINE_MAX];
} Pirate;

typedef struct {
    int length;
    Pirate pirates[MAX_PIRATES];
} List;

// Initialize an empty list
void piratelist_init(List *list);

// Add a pirate by name; returns 1 if added, 0 otherwise
int piratelist_add(List *list, FILE *file);

// Print the whole list
void piratelist_print(const List *list);



#endif
