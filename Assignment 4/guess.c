#include <stdio.h>
#include "../prog1lib/lib/base.h"

int main(void) {
    
    const int RANDOM_NUMBER = i_rnd(100);
    int guess;
    printf("Guess my number!\n");
    do {

         guess = i_input();

        if (guess > RANDOM_NUMBER) {
          
            printsln("Too large!");
        } else if (guess < RANDOM_NUMBER) {
            
            printsln("Too small!");
        }
       
    } while (guess != RANDOM_NUMBER);

    printf("Match!\n");

    return 0;
}