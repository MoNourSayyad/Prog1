/*
Compile: make dam_control
Run: ./dam_control
make dam_control && ./dam_control
*/

#include <stdio.h>
#include "../prog1lib/lib/base.h"

enum dam_mode_e {
    DM_IDLE,
    DM_PUMP_ONE,
    DM_PUMP_TWO,
    DM_PUMP_EMERGENCY,
};


typedef enum dam_mode_e DamMode;

DamMode dam_control(double water_level) {
    if (water_level >= 0.0 && water_level < 20.0) 
        return DM_IDLE;
     else if (water_level > 0.0 && water_level <40.0)
        return DM_PUMP_ONE;
     else if (water_level > 0.0 && water_level <= 67.5)
        return DM_PUMP_TWO;
     else if (water_level > 0.0 && water_level > 67.5)
        return DM_PUMP_EMERGENCY;

    printsln("Water level can not be negative :( ");
    exit(1);
    
}

void dam_control_test(void) {
    test_equal_i(dam_control(17.0), DM_IDLE);
    test_equal_i(dam_control(21.0), DM_PUMP_ONE);
    test_equal_i(dam_control(67.0), DM_PUMP_TWO);
    test_equal_i(dam_control(69.0), DM_PUMP_EMERGENCY);
}

int main(void) {
    dam_control_test();
    return 0;
}
