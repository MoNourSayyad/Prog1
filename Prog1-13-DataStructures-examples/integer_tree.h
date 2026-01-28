#ifndef __INTEGER_TREE_H__
#define __INTEGER_TREE_H__

#include "../prog1lib/lib/base.h"
#include "integer_list.h"

// Represents a single tree node.
typedef struct BTNode {
    int value;
    struct BTNode* left; // self-reference
    struct BTNode* right; // self-reference
} BTNode;

// Creates a tree node.
BTNode* new_btnode(int value, BTNode* left, BTNode* right);

// Creates a leaf node.
BTNode* new_leaf(int value);

// Prints the tree.
void print_tree(BTNode* tree);

// Prints tree followed by a line break.
void println_tree(BTNode* tree);

// Frees all nodes of the tree.
void free_tree(BTNode* tree);

// Computes the number of elements of the tree.
int count_tree(BTNode* tree);

// Computes the depth of the tree.
int depth_tree(BTNode* tree);

// Checks whether tree contains element.
bool contains_tree(BTNode* tree, int x);

// Removes all nodes containing value from the tree.
// Does not respect any order in the tree!
BTNode* remove_tree(BTNode* tree, int value);

// Copies the tree.
BTNode* copy_tree(BTNode* tree);

// Checks whether two trees are equal.
bool trees_equal(BTNode* t1, BTNode* t2);

// Inserts value at the right position in the tree such that the following invariant holds.
// For each node n its left subtree (if not empty) contains values smaller than n's value v 
// and its right subtree (if not empty) contains values equal to or larger than v.
BTNode* insert_ordered_tree(BTNode* tree, int value);

// Finds the first node in the ordered tree which contains the value x.
BTNode* search_ordered_tree(BTNode* tree, int x);

// Does an inorder traversal of the tree and prints each element.
void print_inorder(BTNode* tree);

// Does an inorder traversal of the tree and prints each element followed by a line break.
void println_inorder(BTNode* tree);

///////////////////////////////////////////////////////////////////////////

// Transforms element into something else.
// typedef int (*MapFun)(int element, int x);

// Maps the elements of the tree using f(element, x) and 
// returns a new tree with the same structure as the result.
BTNode* map_tree(BTNode* tree, MapFun f, void* x);

// Checks whether x satisfies a predicate.
// typedef bool (*FilterFun)(int element, int x);

// Filters the elements of the tree using pred(element, x) and 
// returns a list containing the result. Initially, result_list is NULL.
Node* filter_tree(BTNode* tree, FilterFun pred, void* x, Node* result_list);

// Filters and maps the elements of the tree using pred(element, x) and 
// f(element, x), resepectively. Returns a list containing the result. 
// Initially, result_list is NULL.
Node* filter_map_tree(BTNode* tree, FilterFun pred, void* x, MapFun map, void* y, Node* result_list);

// Aggregates a list: state is the intermediary aggregation result, element is the current element.
// typedef int (*ReduceFun)(int state, int element);

// Aggregates the values of the tree by sequentally applying state = f(state, element).
int reduce_tree(BTNode* tree, ReduceFun f, int state);

#endif
