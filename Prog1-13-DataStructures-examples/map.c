#include "map.h"
#include "../prog1lib/lib/base.h"


typedef struct MapNode {
    Entry entry; // not a pointer, but inline
    struct MapNode* next;  // next in the list with that hash
} MapNode;

static MapNode* new_map_node(void* key, void* value, MapNode* next) {
    require_not_null(key);
    require_not_null(value);
    MapNode* n = xcalloc(1, sizeof(MapNode));
    n->entry.key = key;
    n->entry.value = value;
    n->next = next;
    return n;
}

struct Map { // buckets is a pointer to an array of MapNode* Each element in this array is a pointer to a linked list of MapNodes (a bucket)
    int n_buckets; // number of buckets
    MapNode** buckets; // array of buckets, length n (each element is a pointer to a key-value pair)  
    HashFun hash; // the hash function for the keys
    EqualFun equal; // function to check if two keys are equal
};

Map* new_map(int n_buckets, HashFun hash, EqualFun equal) {
    Map* m = xcalloc(1, sizeof(Map));
    m->n_buckets = n_buckets;
    m->buckets = xcalloc(n_buckets, sizeof(MapNode*)); // Each element is of size sizeof(MapNode*) (a pointer to a MapNode)
    m->hash = hash;
    m->equal = equal;
    return m;
}

void put_map(Map* m, void* key, void* value) {
    int h = m->hash(key) % m->n_buckets; // turns the key into a number and ensures it fits into one of the bucket indices
    // add key-value association to front of list in bucket h
    // (does not check whether key is already in map!)
    m->buckets[h] = new_map_node(key, value, m->buckets[h]); // Assigning buckets[i] = new_node just updates the head of the linked list for that bucket
}

void* get_map(Map* m, void* key) {
    int h = m->hash(key) % m->n_buckets;
    // walk through the list of bucket h
    for (MapNode* node = m->buckets[h]; node != NULL; node = node->next) { // m->buckets[h] → pointer to the head of the linked list in the bucket
        if (m->equal(key, node->entry.key)) { // use equals method to compare keys
            return node->entry.value; // found key, return associated value
        }
    }
    return NULL; // key not found, return null
}

void free_map(Map* m, FreeFun free_key, FreeFun free_value) {
    MapNode* next; // Temporary pointer to store the next node while we free the current node
    for (int i = 0; i < m->n_buckets; i++) {
        for (MapNode* node = m->buckets[i]; node != NULL; node = next) { // m->buckets[i] points to the head of the linked list in that bucket
            next = node->next; // Once we free node, we cannot access node->next So we save it first
            if (free_key != NULL) free_key(node->entry.key);
            if (free_value != NULL) free_value(node->entry.value);
            free(node); // MapNode structure
        }
    }
    free(m->buckets); // buckets array
    free(m); // Map structure
}

int size_map(Map* m) {
    int count = 0;
    for (int i = 0; i < m->n_buckets; i++) {
        for (MapNode* node = m->buckets[i]; node != NULL; node = node->next) {
            count++;
        }
    }
    return count;
}

Entry* entries_map(Map* m) {
    int n = size_map(m);              // total number of entries
    if (n == 0) return NULL;          // empty map

    Entry* array = calloc(n, sizeof(Entry));
    int index = 0;

    for (int i = 0; i < m->n_buckets; i++) {
        for (MapNode* node = m->buckets[i]; node != NULL; node = node->next) {
            array[index] = node->entry; // copy the entry  array[index] = node->entry; copies the struct, not the actual keys/values
            index++;
        }
    }

    return array;  // caller owns the array, must free it later
}

//////////////////////////////////////////////////////////////

// Maps the elements of the map using f(element, x) and 
// returns a new map with transformed elements.
Map* map_map(Map* m, MapFun f, void* x) {
    Map* result = new_map(m->n_buckets, m->hash, m->equal);
    for (int i = 0; i < m->n_buckets; i++) {
        for (MapNode* node = m->buckets[i]; node != NULL; node = node->next) {
            put_map(result, node->entry.key, f(node->entry.value, x));
        }
    }
    return result;
}

// Maps the elements of the map using f(element, x) and 
// replaces the original with the transformed elements.
void map_map_mutate(Map* m, MapFun f, void* x) {
    for (int i = 0; i < m->n_buckets; i++) {
        for (MapNode* node = m->buckets[i]; node != NULL; node = node->next) {
            node->entry.value = f(node->entry.value, x);
        }
    }
}

// Filters the elements of the map using pred(element, x) and 
// returns a new map containing the result.
Map* filter_map(Map* m, FilterFun pred, void* x) {
    Map* result = new_map(m->n_buckets, m->hash, m->equal);
    for (int i = 0; i < m->n_buckets; i++) {
        for (MapNode* node = m->buckets[i]; node != NULL; node = node->next) {
            if (pred(&(node->entry), x)) {
                put_map(result, node->entry.key, node->entry.value);
            }
        }
    }
    return result;
}

// Filters and maps the elements of the map using pred(element, x) and 
// f(element, x), respectively. Returns a new map containing the result. 
Map* filter_map_map(Map* m, FilterFun pred, void* x, MapFun f, void* y) {
    Map* result = new_map(m->n_buckets, m->hash, m->equal);
    for (int i = 0; i < m->n_buckets; i++) {
        for (MapNode* node = m->buckets[i]; node != NULL; node = node->next) {
            if (pred(&(node->entry), x)) {
                put_map(result, node->entry.key, f(node->entry.value, x));
            }
        }
    }
    return result;
}

// Aggregates the values of the map by sequentially 
// applying state = f(state, element).
void reduce_map(Map* m, ReduceFun f, void* state) {
    for (int i = 0; i < m->n_buckets; i++) {
        for (MapNode* node = m->buckets[i]; node != NULL; node = node->next) {
            f(state, &(node->entry));
        }
    }
}

//////////////////////////////////////////////////////////////
// Iterator













struct Iterator {
    Map* m; // the map over which this iterator iterates
    int bucket_index; // current bucket list index
    MapNode* map_node; // current key-value pair in list
};

Iterator* new_iterator(Map* m) {
    Iterator* i = xcalloc(1, sizeof(Iterator));
    i->m = m;
    i->bucket_index = -1;
    i->map_node = NULL;
    return i;
}

bool has_next(Iterator* iter) { // does not change state of iterator
    if (iter->map_node != NULL && iter->map_node->next != NULL) { // in bucket list
        return true; // there is another element in this bucket list
    } else { // try next bucket lists
        Map* m = iter->m;
        for (int i = iter->bucket_index + 1; i < m->n_buckets; i++) {
            if (m->buckets[i] != NULL) return true; // bucket i is not empty
        }
    }
    return false; // no more elements
}

Entry next(Iterator* iter) { // modifies state of iterator
    Entry result = { NULL, NULL };
    if (iter->map_node != NULL && iter->map_node->next != NULL) {
        iter->map_node = iter->map_node->next; // advance to next pair
        result.key = iter->map_node->entry.key;
        result.value = iter->map_node->entry.value;
        return result;
    } else {
        Map* m = iter->m;
        for (int i = iter->bucket_index + 1; i < m->n_buckets; i++) {
            if (m->buckets[i] != NULL) {
                iter->bucket_index = i; 
                iter->map_node = m->buckets[i]; // advance to next element
                result.key = iter->map_node->entry.key;
                result.value = iter->map_node->entry.value;
                return result;
            }
        }
    }
    return result; // no more elements
}

void free_iterator(Iterator* iter) {
    free(iter);
}

