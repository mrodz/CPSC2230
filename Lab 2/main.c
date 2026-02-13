#include <stdio.h>
#include <stdlib.h>
#include "PirateList.h"

int main(void) {
    List pirates;
    piratelist_init(&pirates);

    FILE *file = fopen("pirate_names.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening pirate_names.txt\n");
        return EXIT_FAILURE;
    }

    int result = piratelist_add(&pirates, file);
    
    printf("Ahoy! Pirates in the hookbook:\n");
    piratelist_print(&pirates);
    
    if (!result) {
        fprintf(stderr, "Sorry matey, the ship is full!\n\tLet's not take on any more pirates.\n");
        return EXIT_FAILURE;
    }
    fclose(file);
    return 0;
}
