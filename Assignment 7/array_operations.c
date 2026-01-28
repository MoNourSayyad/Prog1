#include "../prog1lib/lib/base.h"
#include <stdlib.h> 

typedef struct better_array_s {
    int length;
    int *array;
} BetterArray;

// a) 
bool compare(int array_a[], int length_a, int *array_b, int length_b) {
    if (length_a < 0 || length_b < 0)
     return false;
    
  
    if (length_a != length_b) 
    return false;

   
    if (array_a == array_b) 
    return true;
    
 
    if (array_a == NULL || array_b == NULL) 
    return false;

  
    for (int i = 0; i < length_a; i++) {
        if (array_a[i] != array_b[i]) {
            return false;
        }
    }
    return true;
}

// b) 
int remove_negatives(int* array, int length) {
    int write_index = 0;
    for (int read_index = 0; read_index < length; read_index++) {
        if (array[read_index] >= 0) {
            array[write_index] = array[read_index];
            write_index++;
        }
    }
    return write_index;
}

// c) 
BetterArray intersect(int *array_a, int length_a, int* array_b, int length_b) {
    int *target_array;
    int *search_array;
    int target_len;
    int search_len;

   
    if (length_b < length_a) {
        target_array = array_b;
        target_len = length_b;
        search_array = array_a;
        search_len = length_a;
    } else {
        target_array = array_a;
        target_len = length_a;
        search_array = array_b;
        search_len = length_b;
    }

    int write_index = 0;

    // Durch das Ziel-Array iterieren und prüfen, ob Element im Such-Array existiert
    for (int i = 0; i < target_len; i++) {
        int val = target_array[i];
        bool found = false;
        
        // Suche im anderen Array
        for (int j = 0; j < search_len; j++) {
            if (search_array[j] == val) {
                found = true;
                break;
            }
        }

        // Wenn gefunden, im Ziel-Array behalten (an write_index schreiben)
        if (found) {
            target_array[write_index] = val;
            write_index++;
        }
    }

    // Ergebnis-Struktur erstellen
    BetterArray result;
    result.array = target_array;
    result.length = write_index;
    
    return result;
}

// d) 
void merge_sorted_arrays(int *array_a, int length_a, int* array_b, int length_b, int* result, int length_result) {
    int i = 0, j = 0, k = 0;
    
    while (i < length_a && j < length_b) {
        if (array_a[i] < array_b[j]) {
            result[k++] = array_a[i++];
        } else {
            result[k++] = array_b[j++];
        }
    }
    
    while (i < length_a) result[k++] = array_a[i++];
    while (j < length_b) result[k++] = array_b[j++];
}



// e) 
/*
Frage 1: 
Normale C-Arrays kennen ihre eigene Länge nicht. Man muss sie immer extra 
mitgeben, was oft zu Fehlern führt. BetterArray packt das Array und die 
Länge in ein "Paket". So hat man die Größe immer automatisch dabei und 
muss nur eine Sache übergeben.

Frage 2: 
Strings sind Arrays aus Zeichen (char). Damit man weiß, wo der Text endet, 
steht als allerletztes Zeichen immer ein "Null-Byte" ('\0').

Frage 3: 
Die Länge wird nirgendwo gespeichert. Um sie herauszufinden, muss der 
Computer die Zeichen von Anfang an zählen, bis er auf das Null-Byte trifft.

Frage 4:
Theoretisch ja, man bräuchte eine Zahl als "Stopp-Signal". Das ist aber 
schlecht, weil man diese Zahl dann nicht mehr als normalen Wert im Array 
speichern dürfte. Bei char geht das gut, weil '\0' kein sichtbares 
Textzeichen ist.
*/



void test_compare(){
    int a1[] = {1, 2, 3, -4, 8, 9};
    int length_a1 = 6;
    int a2[] = {1, 2, 3, -4, 8, 9};
    int length_a2 = 6;
    int a3[] = {1, -2, 3, 4, 8, 9};
    int length_a3 = 6;
    int a4[] = {1};
    int length_a4 = 1;
    int a5[] = {2};
    int length_a5 = 1;

    test_equal_b(compare(a1, length_a1, a2, length_a2), true);
    test_equal_b(compare(a1, length_a1, a2, 1), false);
    test_equal_b(compare(a1, 0, a2, length_a2), false);
    test_equal_b(compare(NULL, 0, NULL, 0), true);
    test_equal_b(compare(a3, 1, a2, 1), true);
    test_equal_b(compare(a3, length_a3, a2, length_a2), false);
    test_equal_b(compare(a3, 2, a2, 2), false);
    test_equal_b(compare(a1, -2, a2, 2), false);
    test_equal_b(compare(a1, -2, a2, -2), false);
    test_equal_b(compare(a1, -2, a2, -1), false);
    test_equal_b(compare(a1, 2, a2, -2), false);
    test_equal_b(compare(a4, length_a4, a4, length_a4), true);
    test_equal_b(compare(a1, 1, a4, length_a4), true);
    test_equal_b(compare(a1, length_a1, a4, length_a4), false);
    test_equal_b(compare(a4, length_a4, a5, length_a5), false);
}

void test_remove_negatives(){
    int a1[] = {1, 2, 3, -4, 8, 9};
    int length_a1 = 6;
    int a1_expected[] = {1, 2, 3, 8, 9};
    int a2[] = {-1, -2, -3, -4, -8, 9};
    int length_a2 = 6;
    int a2_expected[] = {9};
    int a3[] = {-1, -2, -3, -4, -8, -9};
    int length_a3 = 6;
    int a3_expected[] = {};

    int new_length = remove_negatives(a1, length_a1);
    test_equal_i(new_length, 5);
    test_equal_b(compare(a1, new_length, a1_expected, 5), true);

    new_length = remove_negatives(a2, length_a2);
    test_equal_i(new_length, 1);
    test_equal_b(compare(a2, new_length, a2_expected, 1), true);

    new_length = remove_negatives(a3, length_a3);
    test_equal_i(new_length, 0);
    test_equal_b(compare(a3, new_length, a3_expected, 0), true);
}

void test_intersect(){
    int a1[] = {1, 2, 3, -4, 8, 9};
    int length_a1 = 6;
    int a2[] = {2, -2, 6, -4, -8, 10};
    int length_a2 = 6;
    int a2_a1_intersected[] = {2, -4};
    
    int a3[] = {1, 17, 3, 5, 9, 8};
    int length_a3 = 6;
    int a4[] = {1, 17, 3, 5, 9};
    int length_a4 = 5;
    int a3_a4_intersected[] = {1, 17, 3, 5, 9};
    
    int a5[] = {1, 3 , -18};
    int length_a5 = 3;
    int a6[] = {2, -3, -19};
    int length_a6 = 3;
    int a5_a6_intersected[] = {};
    
    BetterArray result = intersect(a1, length_a1, a2, length_a2);
    test_equal_i(result.length, 2);
    test_equal_b(compare(result.array, result.length, a2_a1_intersected, 2), true);
    
    result = intersect(a3, length_a3, a4, length_a4);
    test_equal_i(result.length, 5);
    test_equal_b(compare(result.array, result.length, a3_a4_intersected, 5), true);
    
    result = intersect(a5, length_a5, a6, length_a6);
    test_equal_i(result.length, 0);
    test_equal_b(compare(result.array, result.length, a5_a6_intersected, 0), true);
}

void test_merge_sorted(){
    int a1[] = {1, 2, 3, 4, 8, 9};
    int length_a1 = 6;
    int a2[] = {-2, -2, 6, 14, 15, 100};
    int length_a2 = 6;
    int a1_a2_merged[] = {-2, -2, 1, 2, 3, 4, 6, 8, 9, 14, 15, 100};
    int result[12];
    
    merge_sorted_arrays(a1, length_a1, a2, length_a2, result, 12);
    test_equal_b(compare(result, 12, a1_a2_merged, 12), true);

    int a3[] = {1};
    int length_a3 = 1;
    int a4[] = {15, 100};
    int length_a4 = 2;
    int a3_a4_merged[] = {1, 15, 100};
    int result2[3];
    
    merge_sorted_arrays(a3, length_a3, a4, length_a4, result2, 3);
    test_equal_b(compare(result2, 3, a3_a4_merged, 3), true);
    
    int a5[] = {1, 3, 17};
    int length_a5 = 3;
    int a6[] = {};
    int length_a6 = 0;
    int a5_a6_merged[] = {1, 3, 17};
    int result3[3];
    
    merge_sorted_arrays(a5, length_a5, a6, length_a6, result3, 3);
    test_equal_b(compare(result3, 3, a5_a6_merged, 3), true);
    
    int result4[3];
    merge_sorted_arrays(a6, length_a6, a5, length_a5, result4, 3);
    test_equal_b(compare(result4, 3, a5_a6_merged, 3), true);
}

int main(void) {
    test_compare();
    test_remove_negatives();
    test_intersect();
    test_merge_sorted();
    return 0;
}

// gcc array_operations.c ../prog1lib/lib/base.c -o x
//./x