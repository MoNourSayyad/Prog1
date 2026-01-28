/*
Compile: make primes
Run: ./primes
make primes && ./primes
*/


/*
    F nummer bedeutet Fehler
 */

#include <stdio.h>                                              /*F8:Stellt die Deklarationvon 'printf' bereit.*/
#include <stdbool.h>                                            /*F6：Stellt den bool Typ bereit, damit bool verwendet werden kann. */
#include "../prog1lib/lib/base.h"                               /*F1: no such file "Bas.eh" so falscher Headername und falscher Ort -> include prog1lib*/
/*
    Prints the primes in the given interval [lower, upper)].
*/
int print_primes_in_intervall(int lower, int upper){
    
    if( upper > lower){
        int prime = lower;
        if(prime < 2)
            prime = 2;                                          /*F2:Stehen hier ein doppeltes Semikolom.*/
                                                                /*F3:Stehen hier mehr},sodass F4 passiert, da wegen des Strukturfehlers 'prime' ausserhalb des gueltigen Blockes lag.*/
        int count = 0;

                                                                /*F4:prime undeclared. */
        while (prime < upper){
            int i = 2;                                          /*F5：Fehlten das Semikolon.*/

            bool is_a_prime = true;                             /*F6：bool war nicht verfuegbar, da <stadbool.h> fehlte. bool.*/

            while(i <= (prime >> 1)){
                    if( prime % i == 0 ){                       /*F7:Zuweisung statt Vergleichen*/
                    is_a_prime = false;
                    break;
                }
                i++;
            }

            if(is_a_prime){
                count++;
                printf("Die %2d. Primzahl im Intervall: [%d,%d) ist: %2d\n",/*F8：implicit declaration of function 'printf'*/
                       count, lower, upper, prime);
            }
            prime++;
        }
        return count;
    }
    return 0;                                                   /*F9:control reaches end of non-void function-> So die Funktion int muss in jedem Fall etwas zurueckgeben.*/
}
void test_print_primes_in_intervall(){
    test_equal_i(print_primes_in_intervall(0, 10), 4);
    test_equal_i(print_primes_in_intervall(10, 20), 4);
    test_equal_i(print_primes_in_intervall(20, 30), 2);
    test_equal_i(print_primes_in_intervall(600, 700), 16);
    test_equal_i(print_primes_in_intervall(-10, 0), 0);
    test_equal_i(print_primes_in_intervall(50, 100), 10);
    test_equal_i(print_primes_in_intervall(50, 50), 0);
    test_equal_i(print_primes_in_intervall(80, 50), 0);
}

int main(void){
    
    test_print_primes_in_intervall();
    return 0;
}


