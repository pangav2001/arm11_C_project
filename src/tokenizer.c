#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 511

int16_t assign_label_address(char *line, int16_t address)
{
    char *temp = line; //give same pointer
    for (int i = 0; i < MAX_LINE_LENGTH && *temp; i++, temp++) { //*temp should check we are not at /0
        if (*temp == ':') {
            char *label = malloc(i + 1);
            strncpy(label, line, i);
            //TODO
            //Add the label to hashmap
            //and correct address
            free(label);
            return address; //label so address hasn't changed
        }
    }
    return address + 4; //return next address
}
