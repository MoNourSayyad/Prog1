#ifndef BINTREE_H
#define BINTREE_H

#include <stdbool.h>
#include <limits.h>

/* Struct definitions */

typedef struct BTNode {
    int value;
    struct BTNode* left;
    struct BTNode* right;
} BTNode;

typedef struct BinTree {
    BTNode* first;
} BinTree;

/* Creation functions */

BTNode* createBTNode(int value, BTNode* left, BTNode* right);
BinTree* createBinTree(void);
BTNode* createLeaf(int value);
BTNode* createNewLeaf(int value);

/* Utility functions */

int sumOfBTNodes(BTNode* tree);
int countTreeBTNodes(BTNode* tree);
int heightTree(BTNode* tree);
int heightOfTree(BinTree* tree);

/* Printing functions */

void printTree(BTNode* tree);
void PrintTreeWithTree(BinTree* tree);
void printInorder(BTNode* tree);
void printWithInorder(BinTree* tree);

/* Searching and checking */

bool containsTreeValue(BTNode* tree, int value);
bool containsValue(BinTree* tree, int value);

bool treesEqual(BTNode* t1, BTNode* t2);
bool treesAreEqual(BinTree* t1, BinTree* t2);

bool isOrdered(BTNode* tree, int min, int max);
bool isTreeOrdered(BTNode* tree);
bool isBinTreeOrdered(BinTree* tree);

/* Copying */

BTNode* copyTree(BTNode* tree);
BTNode* copyTheTree(BinTree* tree);

/* Ordered insertion */

BTNode* insertOrdered(BTNode* tree, int value);
BTNode* InsertionWithOrder(BinTree* tree, int value);
BTNode* InsertOrderedIteration(BTNode* tree, int value);
BTNode* InsertionWithOrderIter(BinTree* tree, int value);

/* Efficient search */

BTNode* efficientSearchingMethod(BTNode* tree, int value);
bool efficientSearch(BTNode* tree, int value);
bool efficientTreeSearch(BinTree* tree, int value);

BTNode* efficientSearchIterMethod(BTNode* tree, int value);
bool efficientSearchIter(BTNode* tree, int value);

#endif /* BINTREE_H */
