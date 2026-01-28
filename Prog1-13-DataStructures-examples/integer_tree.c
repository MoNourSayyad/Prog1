/*
Compile: make integer_tree
Run: ./integer_tree
make integer_tree && ./integer_tree
*/

#include "integer_tree.h"

// Creates a tree node.
BTNode* new_btnode(int value, BTNode* left, BTNode* right) {
    BTNode* node = xcalloc(1, sizeof(BTNode));
    node->value = value;
    node->left = left;
    node->right = right;
    return node;
}

// Creates a leaf node.
BTNode* new_leaf(int value) {
    return new_btnode(value, NULL, NULL);
}

// Prints the tree.
#if 1
void print_tree(BTNode* tree) {
    if (tree == NULL) {
        printf("_");
    } else {
        if (tree->left == NULL && tree->right == NULL) {
            printf("%d", tree->value);
        } else {
            printf("(");
            print_tree(tree->left);
            printf(", %d, ", tree->value);
            print_tree(tree->right);
            printf(")");
        }
    }
}
#else
void print_tree(BTNode* tree) {
    // (c) todo: implement
    if (tree == NULL) {
        printf("_");
    } else {
        printf("(");
        print_tree(tree->left);
        printf(", %d, ", tree->value);
        print_tree(tree->right);
        printf(")");
    }
}
#endif

// Prints tree followed by a line break.
void println_tree(BTNode* tree) {
    print_tree(tree);
    printsln("");
}

// Frees all nodes of the tree.
void free_tree(BTNode* tree) {
    // (b) todo: implement
    if (tree != NULL) {
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree);
    }
}

// Computes the number of elements of the tree.
int count_tree(BTNode* tree) {
    if (tree == NULL) return 0;
    else return 1 + count_tree(tree->left) + count_tree(tree->right);
}

// Computes the depth of the tree.
int depth_tree(BTNode* tree) {
    if (tree == NULL) {
        return 0;
    } else {
        int left_depth = depth_tree(tree->left);
        int right_depth = depth_tree(tree->right);
        return 1 + ((left_depth > right_depth) ? left_depth : right_depth);
    }
}

// Checks whether tree contains element.
bool contains_tree(BTNode* tree, int x) {
    if (tree == NULL) return false;
    else return (tree->value == x) || 
        contains_tree(tree->left, x) || 
        contains_tree(tree->right, x);
}

// Removes all nodes containing value from the tree.
// Does not respect any order in the tree!
BTNode* remove_tree(BTNode* tree, int value) {
    if (tree == NULL) return NULL;
    tree->left = remove_tree(tree->left, value);
    tree->right = remove_tree(tree->right, value);
    if (tree->value == value) {
        if (tree->left == NULL) {
            BTNode* right = tree->right;
            free(tree);
            return right;
        }
        if (tree->right == NULL) {
            BTNode* left = tree->left;
            free(tree);
            return left;
        }
        // assert: tree->left != NULL && tree->right != NULL
        BTNode* left = tree->left;
        BTNode* right = tree->right;
        BTNode* insertion_point = left;
        while (insertion_point->left != NULL) {
            insertion_point = insertion_point->left;
        }
        // assert: insertion_point->left == NULL
        insertion_point->left = right;
        return left;
    }
    return tree;
}

// Copies the tree.
BTNode* copy_tree(BTNode* tree) {
    if (tree == NULL) return NULL;
    return new_btnode(tree->value, copy_tree(tree->left), copy_tree(tree->right));
}

// Checks whether two trees are equal.
bool trees_equal(BTNode* t1, BTNode* t2) {
    if (t1 == t2) return true; // same address (or both NULL)
    // assert: t1 != t2
    if (t1 == NULL || t2 == NULL) return false; // one tree is NULL, the other is not
    // assert: t1 != NULL && t2 != NULL
    if (t1->value != t2->value) return false; // trees differ at current node
    // assert: t1->value == t2->value
    return trees_equal(t1->left, t2->left) && trees_equal(t1->right, t2->right);
}

// Inserts value at the right position in the tree such that the following invariant holds.
// For each node n its left subtree (if not empty) contains values smaller than n's value v 
// and its right subtree (if not empty) contains values equal to or larger than v.
BTNode* insert_ordered_tree(BTNode* tree, int value) {
    if (tree == NULL) { // empty tree
        return new_leaf(value);
    } else if (value < tree->value) {
        tree->left = insert_ordered_tree(tree->left, value);
        return tree;
    } else {
        tree->right = insert_ordered_tree(tree->right, value);
        return tree;
    }
}

// Finds the first node in the ordered tree which contains the value x.
BTNode* search_ordered_tree(BTNode* tree, int x) {
    if (tree == NULL) return NULL;
    if (x == tree->value) return tree;
    if (x < tree->value) return search_ordered_tree(tree->left, x);
    return search_ordered_tree(tree->right, x);
}

// Does an inorder traversal of the tree and prints each element.
void print_inorder(BTNode* tree) {
    if (tree != NULL) {
        print_inorder(tree->left);
        printf("%d ", tree->value);
        print_inorder(tree->right);
    }
}

// Does an inorder traversal of the tree and prints each element followed by a line break.
void println_inorder(BTNode* tree) {
    print_inorder(tree);
    printsln("");
}

///////////////////////////////////////////////////////////////////////////

// Maps the elements of the tree using f(element, x) and 
// returns a new tree with the same structure as the result.
BTNode* map_tree(BTNode* tree, MapFun f, void* x) {
    if (tree == NULL) return NULL;
    return new_btnode(f(tree->value, x), 
        map_tree(tree->left, f, x), 
        map_tree(tree->right, f, x));
}

// Filters the elements of the tree using pred(element, x) and 
// returns a list containing the result. Initially, result_list is NULL.
Node* filter_tree(BTNode* tree, FilterFun pred, void* x, Node* result_list) {
    if (tree == NULL) return result_list;
    if (pred(tree->value, x)) result_list = new_node(tree->value, result_list);
    result_list = filter_tree(tree->left, pred, x, result_list);
    result_list = filter_tree(tree->right, pred, x, result_list);
    return result_list;
}

// Filters and maps the elements of the tree using pred(element, x) and 
// f(element, x), resepectively. Returns a list containing the result. 
// Initially, result_list is NULL.
Node* filter_map_tree(BTNode* tree, FilterFun pred, void* x, MapFun map, void* y, Node* result_list) {
    if (tree == NULL) return result_list;
    if (pred(tree->value, x)) result_list = new_node(map(tree->value, y), result_list);
    result_list = filter_map_tree(tree->left, pred, x, map, y, result_list);
    result_list = filter_map_tree(tree->right, pred, x, map, y, result_list);
    return result_list;
}

// Aggregates the values of the tree by sequentally applying state = f(state, element).
int reduce_tree(BTNode* tree, ReduceFun f, int state) {
    if (tree == NULL) return state;
    state = reduce_tree(tree->left, f, state);
    state = f(state, tree->value);
    state = reduce_tree(tree->right, f, state);
    return state;
}

///////////////////////////////////////////////////////////////////////////////

#if 0
int f(int element, int x) {
    return element * x;
}

int sum(int state, int element) {
    return state + element;
}

bool greater_than(int element, int x) {
    return element > x;
}

int times(int element, int factor) {
    return element * factor;
}

int main(void) {
    report_memory_leaks(true);

    BTNode* t = new_btnode(0, new_btnode(1, new_btnode(11, NULL, NULL), new_btnode(12, NULL, NULL)), new_btnode(2, NULL, NULL));
    println_tree(t);
    printiln(depth_tree(t));

    BTNode* t3 = new_btnode(0, new_btnode(1, new_btnode(11, NULL, NULL), new_btnode(12, NULL, NULL)), new_btnode(2, NULL, NULL));
    printbln(trees_equal(t, t3));
    free_tree(t3);

    t3 = new_btnode(0, new_btnode(1, new_btnode(10, NULL, NULL), new_btnode(12, NULL, NULL)), new_btnode(2, NULL, NULL));
    printbln(trees_equal(t, t3));
    free_tree(t3);

    free_tree(t);

    t = new_btnode(0, new_btnode(1, new_leaf(11), new_leaf(12)), new_leaf(2));
    println_tree(t);
    
    printiln(count_tree(t));
    free_tree(t);

    t = new_btnode(0, new_btnode(1, new_leaf(11), NULL), new_leaf(2));
    println_tree(t);
    
    printiln(count_tree(t));
    free_tree(t);
    
    t = NULL;
    t = insert_ordered_tree(t, 3);
    t = insert_ordered_tree(t, 2);
    t = insert_ordered_tree(t, 1);
    t = insert_ordered_tree(t, 0);
    println_tree(t);
    println_inorder(t);
//    t = remove_tree(t, 0);
//    t = remove_tree(t, 1);
//    t = remove_tree(t, 2);
//    t = remove_tree(t, 3);
    println_tree(t);
    free_tree(t);

    t = NULL;
    t = insert_ordered_tree(t, 1);
    t = insert_ordered_tree(t, 2);
    t = insert_ordered_tree(t, 3);
    t = insert_ordered_tree(t, 4);
    println_tree(t);
    println_inorder(t);
    
    prints("filter_map_tree: ");
    Node* list = filter_map_tree(t, greater_than, 2, times, 10, NULL);
    println_list(list);
    free_list(list);

    free_tree(t);

    t = NULL;
    t = insert_ordered_tree(t, 20);
    t = insert_ordered_tree(t, 10);
    t = insert_ordered_tree(t, 30);
    t = insert_ordered_tree(t, 5);
    println_tree(t);
    println_preorder(t);
    println_inorder(t);
    println_postorder(t);
    printsln("search_ordered:");
    printbln(search_ordered_tree(t, 5) != NULL);
    printbln(search_ordered_tree(t, 10) != NULL);
    printbln(search_ordered_tree(t, 20) != NULL);
    printbln(search_ordered_tree(t, 30) != NULL);
    printbln(search_ordered_tree(t, -55) != NULL);
    printbln(search_ordered_tree(t, 25) != NULL);
    printbln(search_ordered_tree(t, 55) != NULL);
    
    BTNode* t2 = map_tree(t, f, 2);
    println_tree(t2);
    println_inorder(t2);

    printiln(reduce_tree(t2, sum, 0));

    free_tree(t);
    free_tree(t2);

    return 0;
}
#endif
