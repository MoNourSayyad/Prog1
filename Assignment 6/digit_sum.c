/*
Compile: make digit_sum
Run: ./digit_sum
make digit_sum && ./digit_sum
*/

#include "../prog1lib/lib/base.h"

/*
    Computes the digit sum of the positive integer (number, which is unsigned). If (bool alternating) is true, the function computes the alternating
    digit sum, where the digits are processed from left to right and added and subtracted alternately. 
    If (alternating) is false, all digits are simply added.
 */

int digit_sum(unsigned number, bool alternating) {

    // TODO 

    if (number == 0) {
        return 0;
    }

    unsigned div = 1;

    while (number / div >= 10) {
        div *= 10;
    }

    int sum = 0;
    int sign = 1;

    while (div > 0) {

        int digit = number / div;

        if (alternating) {
            sum += sign * digit;
            sign = -sign;
        } else 
            sum += digit;
        
        number %= div;
        div /= 10;
    }

    return sum;

}

bool divisible_by_eleven(unsigned number) {

    // TODO

     if (number < 11)
        return number == 0 || number == 11;
    
    int alt = digit_sum(number, true);

    
    while (alt < 0)
        alt += 11;
    

    if (alt == 0 || alt == 11)
        return true;
    
    if (alt < 11) {
        return false;
    }

    return divisible_by_eleven(alt);
}

void digit_sum_test() {

    // TODO
    
    test_equal_i(digit_sum(123456, true), -3);
    test_equal_i(digit_sum(8888888, true), 8);
    test_equal_i(digit_sum(623, false), 11);
    test_equal_i(digit_sum(74582, true), 2);
    test_equal_i(digit_sum(10, false), 1);
    test_equal_i(digit_sum(333, false), 9);

    // TODO

    test_equal_i(divisible_by_eleven(12123213), false);
    test_equal_i(divisible_by_eleven(111), false);
    test_equal_i(divisible_by_eleven(121), true);
    test_equal_i(divisible_by_eleven(12123210), true);
    test_equal_i(divisible_by_eleven(12), false);
    test_equal_i(divisible_by_eleven(11), true);
}

int main(void) {
    digit_sum_test();
    return 0;
}
