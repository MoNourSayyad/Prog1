/*
Compile: make test_set
Run: ./test_set
make test_set && ./test_set
*/

#include "set.h"
#include "../prog1lib/lib/base.h"

int hash_string(void* x) {
    String element = x;
    int n = s_length(element);
    int hash = 0;
    for (int i = 0; i < n; i++) {
        hash = hash * 31 + element[i];
    }
    if (hash < 0) hash = -hash;
    return hash;
}

void free_string(void* s) {
    free(s);
}

bool strings_equal(void* x, void* y) {
    return s_equals(x, y);
}

int main(void) {
    report_memory_leaks(true);
    
    Set* s = new_set(4, hash_string, strings_equal);
    printbln(is_empty_set(s));
    add_set(s, "dog"); // hash("dog") = 0
    printbln(is_empty_set(s));
    printiln(size_set(s));
    add_set(s, "cat"); // hash("cat") = 2
    add_set(s, "whale"); // hash("whale") = 1
    add_set(s, "cow"); // hash("cow") = 3
    add_set(s, "donelement"); // hash("donelement") = 0      
    printbln(contains_set(s, "cow")); // Kuh
    printbln(contains_set(s, "dog")); // Hund
    printbln(contains_set(s, "donelement")); // Esel
    printbln(contains_set(s, "hamster")); // <null>, not in m
    printiln(size_set(s));
    
    printsln("iterators:");
    Iterator* iter = new_iterator(s);
    while (has_next(iter)) {
        String element = next(iter);
        printf("iterator: %s\n", element);
    }
    free_iterator(iter);
    
    Set* t = new_set(4, hash_string, strings_equal);
    add_set(t, "dog");
    add_set(t, "cat");
    add_set(t, "hamster");
    add_set(t, "hamster"); // not added again
    printiln(size_set(t));
    
    Set* r = intersect_set(s, t);
    iter = new_iterator(r);
    while (has_next(iter)) {
        String element = next(iter);
        printf("intersect_set: %s\n", element);
    }
    free_iterator(iter);
    
    free_set(s, NULL);
    free_set(t, NULL);
    free_set(r, NULL);
    
    String key = "dog";
    int h = hash_string(key);
    printf("%s: %d, %d\n", key, h, h % 4);
    key = "donkey";
    h = hash_string(key);
    printf("%s: %d, %d\n", key, h, h % 4);
    key = "cow";
    h = hash_string(key);
    printf("%s: %d, %d\n", key, h, h % 4);

    key = "c";
    h = hash_string(key);
    printf("%s: %d, %d\n", key, h, h % 3);
    key = "f";
    h = hash_string(key);
    printf("%s: %d, %d\n", key, h, h % 3);
    key = "z";
    h = hash_string(key);
    printf("%s: %d, %d\n", key, h, h % 3);
    
    return 0;
}
