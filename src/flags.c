#include <stdio.h>
#include "flags.h"
#include "registers.h"

int check_cond(enum Condition_Code condition_code) {
    return 0;
    uint32_t cpsr = get_reg(CPSR);
}

void set_flag(enum Flag flag) {

}

void reset_flag(enum Flag flag) {

}