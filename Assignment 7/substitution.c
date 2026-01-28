
#include <stdio.h>
#include "../prog1lib/lib/base.h"

const String permutation = "SGEMFVYZIDPBUKHARNXQWOLJTC";


// -----------------TODO Aufgabe 4.A--------------------------------------

//Gibt einen neuen String zurück, in dem 'input' nach der
//Zuordnung 'permutation' verschlüsselt ist.
//Nur Großbuchstaben A–Z werden verändert; alle anderen Zeichen bleiben so, wie sie sind.
String encrypt(String input) {

    // Make a writable copy of the input
    String result = s_copy(input);

    int len = s_length(result);
    for (int i = 0; i < len; i++) {
        char c = s_get(result, i);

        // Only encrypt uppercase letters
        if (c >= 'A' && c <= 'Z') {
            int index = c - 'A';          
            char enc = s_get(permutation, index);
            s_set(result, i, enc);        
        }
        
    }

    return result; // caller gets a new encrypted string
}

// -----------------TODO Aufgabe 4B--------------------------------------

int index_of(String s, char c) {

    int len = s_length(s);    

    for (int i = 0; i < len; i++) {
        char current = s_get(s, i);
        if (current == c) {
            return i;           
        }
    }
    // 4. if we finish the loop without finding c → not in string
    return -1;
}

// -----------------TODO Aufgabe 4C--------------------------------------

String decrypt(String input) {
    String result = s_copy(input);

    int len = s_length(result);

    for (int i = 0; i < len; i++) {
        char c = s_get(result, i);

        // Only decrypt uppercase letters
        if (c >= 'A' && c <= 'Z') {

            // 1. Find where the encrypted character appears in permutation
            int idx = index_of(permutation, c);

            // 2. Convert index back to the original letter
            if (idx != -1) {
                char original = 'A' + idx;
                s_set(result, i, original);
            }
        }
    }

    return result;
}

void test_identity(String s) {
    assert("encrypted text must differ from input", !s_equals(s, encrypt(s)));
    test_equal_s(s, decrypt(encrypt(s)));
}

int main(void) {
    test_identity("HELLO WORLD");
    test_identity("SOME SUPER SECRET TEXT");
    test_identity("DOES QUOTATION CAUSE ISSUES? IT SHOULDN'T.");
    test_identity("BE SURE TO DRINK YOUR OVALTINE");

    printsln("The secret text says:");
    printsln(decrypt("VNSKC DSYQ IU PHUABFQQ OFNLSZNBHXQFK QSJI RWFN MWNEZ GSTFNK."));
}

/* 
gcc substitution.c ../prog1lib/lib/base.c -o x
 
./x
 
*/