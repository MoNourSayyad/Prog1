/*
Compile: make test_map
Run: ./test_map
make test_map && ./test_map
*/

#include "map.h"
#include "../prog1lib/lib/base.h"

static int hash_string(void* x) {
    String key = x; // Converts the void* to a char* so we can work with it as a string.
    int n = s_length(key);
    int hash = 0;
    for (int i = 0; i < n; i++) {
        hash = hash * 31 + key[i];  // key[i] is the ASCII value of the character.
    }
    if (hash < 0) hash = -hash;  // Buckets are array indices, so we need non-negative integers.
    return hash;
}

static void free_string(void* s) {
    free(s);
}

static bool strings_equal(void* x, void* y) {
    return s_equals(x, y);
}

static String s_upper_case(String s) {
    require_not_null(s);
    int n = strlen(s);
    String t = xmalloc((n + 1) * sizeof(char));
    for (int i = 0; i < n; i++) {
        t[i] = toupper(s[i]);
    }
    t[n] = '\0';
    return t;
}

static void* to_upper(void* element, void* x) {
    String s = element;
    return s_upper_case(s);
}

static void count_chars(void* state, void* element) {
    int* n = state;
    Entry* e = element;
    *n += s_length(e->value);
}

static void print_key_value(void* state, void* element) {
    Entry* e = element;
    printf("%s --> %s\n", (char*)e->key, (char*)e->value);
}

int main(void) {
    Map* m = new_map(4, hash_string, strings_equal);
    put_map(m, "dog", "Hund"); // hash("dog") = 0
    put_map(m, "cat", "Katze"); // hash(”cat") = 2
    put_map(m, "whale", "Wal"); // hash(”whale") = 1
    put_map(m, "cow", "Kuh"); // hash(”cow") = 3
    put_map(m, "donkey", "Esel"); // hash(”donkey") = 0      
    printsln(get_map(m, "cow")); // Kuh
    printsln(get_map(m, "dog")); // Hund
    printsln(get_map(m, "donkey")); // Esel
    char* s = get_map(m, "hamster"); // <null>, not in m
    printsln(s ? s : "not in m");
    
    Map* m2 = map_map(m, to_upper, NULL);
    printsln(get_map(m2, "cow")); // Kuh
    printsln(get_map(m2, "dog")); // Hund
    printsln(get_map(m2, "donkey")); // Esel
    s = get_map(m2, "hamster"); // <null>, not in m
    printsln(s ? s : "not in m");
    
    map_map_mutate(m, to_upper, NULL);
    printsln(get_map(m, "cow")); // Kuh
    printsln(get_map(m, "dog")); // Hund
    printsln(get_map(m, "donkey")); // Esel
    s = get_map(m, "hamster"); // <null>, not in m
    printsln(s ? s : "not in m");
    
    int i = 0;
    reduce_map(m, count_chars, &i);
    printiln(i);
    reduce_map(m, print_key_value, NULL);
    
    printsln("iterators:");
    Iterator* iter = new_iterator(m);
    while (has_next(iter)) { // abstracts from complicated iteration
        Entry e = next(iter);
        printf("iterator: %s --> %s\n", (char*)e.key, (char*)e.value);
    }
    free(iter);
    
    free_map(m, NULL, free_string);
    free_map(m2, NULL, free_string);
    
    return 0;
}
