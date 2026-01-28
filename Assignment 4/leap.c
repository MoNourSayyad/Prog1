#include <stdio.h>
#include "../prog1lib/lib/base.h"

int number_of_days(int year) {
    int multiple_of_four = (year % 4 == 0);
    int multiple_of_hundred = (year % 100 == 0);
    int multiple_of_fourhundred = (year % 400 == 0);

    if (!multiple_of_four || (multiple_of_hundred && !multiple_of_fourhundred)) {
        return 365;
    } else {
        return 366;
    }
}

int main(void) {
    test_equal_i(number_of_days(2021), 365);
    test_equal_i(number_of_days(2020), 366);
    test_equal_i(number_of_days(1900), 365);
    test_equal_i(number_of_days(2000), 366);
    return 0;
}

