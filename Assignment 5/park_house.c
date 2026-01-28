/*
Compile: make park_house
Run: ./park_house
make park_house && ./park_house
*/
#include <stdio.h>
#include "../prog1lib/lib/base.h"
#ifndef CLRSCR_H
#define CLRSCR_H
// Clear screen functionality for Windows, Linux, and macOS: clear_screen();
#ifdef _WIN32
#define clear_screen() system("@cls||clear");
#else
#define clear_screen() printf("\e[1;1H\e[2J")
#endif
#endif
/* Design a function that returns the state of a park house given the number
of free parking spots */

typedef enum ParkHouseState {
    PH_FULL,  // 0
    PH_ALMOST_FULL, // <10
    PH_FREE // >= 10
} ParkHouseState;

ParkHouseState det_park_house_state(int free_spots){
    if (free_spots < 0) {
        printsln("How did you manage to write a negative number that represents free spots. WTF");
        exit(1); //exits the Run
    } else if (free_spots == 0)
        return PH_FULL;
      else if (free_spots < 10)
        return PH_ALMOST_FULL;
      else
        return PH_FREE;
};
// a) TODO
static void det_park_house_state_test() {
    test_equal_i(det_park_house_state(0), PH_FULL);
    test_equal_i(det_park_house_state(9), PH_ALMOST_FULL);    //Tests
    test_equal_i(det_park_house_state(67), PH_FREE);
}

// b) TODO
String print_park_house_state(ParkHouseState state) {
    switch (state) {
        case PH_FULL:
            return "Parkplace is full";
        case PH_ALMOST_FULL:
            return "Parkplace is almost full";
        case PH_FREE:
            return "Parkplace is empty";
        default:
            return "Negative number is given. UNKNOWN."; // Safety exit
    }
}

String park_house_state_input(int input){
    printsln("Give me a number of free parkplaces available: ");
    int free_spots = i_input();
    ParkHouseState state = det_park_house_state(free_spots);
    printsln(print_park_house_state(state));
}

int main(void) {
    det_park_house_state_test();
    printsln(print_park_house_state(det_park_house_state(0)));
    printsln(print_park_house_state(det_park_house_state(8)));
    printsln(print_park_house_state(det_park_house_state(21)));
    park_house_state_input(23); // c)  Input function.
    clear_screen();
    return 0;
}

