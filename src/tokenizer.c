#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 511

//returns 0 if not label
//returns length of label otherwise
int16_t is_label(char *line) {
    char *temp = line; //give same pointer
    for (int i = 0; i < MAX_LINE_LENGTH && *temp; i++, temp++) { //*temp should check we are not at /0
        if (*temp == ':') {
            return i;
        }
    }
    return 0;
}


int16_t assign_label_address(char *line, int16_t address)
{
    int16_t length = is_label(line);
    if (length) {
        char *label = malloc(length + 1);
        strncpy(label, line, length);
        //TODO
        //Add the label to hashmap
        //and correct address
        free(label);
        return address; //label so address hasn't changed
    }
    return address + 4; //return next address
}