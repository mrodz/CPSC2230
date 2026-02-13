#include <stdio.h>
#include <string.h> 
#include "PirateList.h"

// Initialize the list
void piratelist_init(List *list) {
    list->length = 0;
}


// Read all lines from file and add to list. 
int piratelist_add(List *list, FILE *file) {
    while (list->length < MAX_PIRATES) {
        char line[LINE_MAX] = {0};
        // Read each line from the file with fgets preferably
        // create a Pirate struct for each line and copy it
        // add it to the list if there is space, use return 0 if full

        if (fgets(line, LINE_MAX, file) == NULL) {
            return 1;
        };

        int pirate_id = list->length + 1;

        Pirate p;
        p.pirate_id = pirate_id;

        strcpy(p.name, line);

        list->pirates[list->length++] = p;
    }

    return 0;
}

// Print the whole list
void piratelist_print(const List *list) {
    for (int i = 0; i < list->length; i++) {
        printf("Pirate { .pirate_id = %d, .name = \"%s\" }\n", list->pirates[i].pirate_id, list->pirates[i].name);
    }
    printf("\n");
}
