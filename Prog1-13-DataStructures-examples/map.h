#ifndef __MAP_H__
#define __MAP_H__
#include "../prog1lib/lib/base.h"

typedef int (*HashFun)(void*);

typedef bool (*EqualFun)(void* object1, void* object2);

typedef struct Map Map;

typedef struct Entry { //  key-value pair
    void* key;  // e.g., dog
    void* value; // e.g., Hund
} Entry;

// Creates a new map.
Map* new_map(int n_buckets, HashFun hash, EqualFun equal);

// Puts a key-value pair into the map.
void put_map(Map* m, void* key, void* value);

// Returns the value associated with the key 
// (or NULL if no value is associated with the key).
void* get_map(Map* m, void* key);

// Frees an object.
typedef void (*FreeFun)(void* object);

// Release the map (and the keys and/or values if the free-functions are not NULL).
void free_map(Map* m, FreeFun free_key, FreeFun free_value);

// Number of entries in the map.
int size_map(Map* m);

// A dynamically allocated array of map entries. Does not copy the keys or values.
Entry* entries_map(Map* m);

//////////////////////////////////////////////////////////////

// Entry*, void* -> bool
// Checks whether x satisfies a predicate.
typedef bool (*FilterFun)(void* element, void* x);

// void*, void* -> void*
// Transforms element into something else.
typedef void* (*MapFun)(void* element, void* x);

// void*, Entry* -> void
// Aggregates a map: state is the intermediary aggregation 
// result, element is the current element. May modify state.
typedef void (*ReduceFun)(void* state, void* element);

// Map*s the elements of the map using f(element, x) and 
// returns a new map with transformed elements.
Map* map_map(Map* m, MapFun f, void* x);

// Map*s the elements of the map using f(element, x) and 
// replaces the original with the transformed elements.
void map_map_mutate(Map* m, MapFun f, void* x);

// Filters the elements of the map using pred(element, x) and 
// returns a new map containing the result.
Map* filter_map(Map* m, FilterFun pred, void* x);

// Filters and maps the elements of the map using pred(element, x) and 
// f(element, x), respectively. Returns a new map containing the result. 
Map* filter_map_map(Map* m, FilterFun pred, void* x, MapFun f, void* y);

// Aggregates the values of the map by sequentially 
// applying state = f(state, element).
void reduce_map(Map* m, ReduceFun f, void* state);

//////////////////////////////////////////////////////////////
// Iterator

typedef struct Iterator Iterator;

// Create an iterator for m (on the stack).
Iterator* new_iterator(Map* m);

// Check whether iter has more elements.
// Coes not change state of iterator.
bool has_next(Iterator* iter);

// Advances to and returns the next element.
// Modifies state of iterator. Returns Entry(NULL, NULL) if the iterator is exhausted.
Entry next(Iterator* iter);

// Frees the iterator.
void free_iterator(Iterator* iter);

#endif
