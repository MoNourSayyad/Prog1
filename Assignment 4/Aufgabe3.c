#include <stdio.h>
#include "../prog1lib/lib/base.h"

/*

 Die Funktion f nimmt eine ganze Zahl i als Eingabe. Zuerst gibt sie den Text called f mit einem Zeilenumbruch auf der Konsole aus. Dann prüft sie, ob i kleiner als 0 ist.
 dann liefert sie den Betrag von i zurück (also -i). Fall 2  i nicht negativ, gibt sie das Dreifache von i zurück (3 * i)

 */

int f(int i) {
    printf("called f\n");
    if (i < 0) {
        return -i;
    } else {
        return 3 * i;
    }
}

int main(void){

    f(1);
}