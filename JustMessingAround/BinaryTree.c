#include <stdio.h>
#include <stdlib.h>
#include "../prog1lib/lib/base.h"
#include <math.h>
#include <limits.h>
#include "BinaryTree.h"


BTNode* createBTNode(int value, BTNode* left, BTNode* right) {
    BTNode* BNode = (BTNode*) xcalloc(1,sizeof(BTNode));
    BNode->value = value;
    BNode->left = left;
    BNode->right = right;
    return BNode;
}

BinTree* createBinTree(void) {
    BinTree* tree = (BinTree*) xcalloc(1, sizeof(BinTree));
    tree->first = NULL; // Good Practice.
    return tree;
}

int sumOfBTNodes(BTNode* tree) {
    if (tree == NULL)
        return 0;
    else 
        return tree->value + sumOfBTNodes(tree->left) + sumOfBTNodes(tree->right);
}

void printTree(BTNode* tree) { 
    if (tree == NULL) 
        printf("_");
    else {
        printf("( ");
        printTree(tree->left);
        printf(" , %d , ", tree->value);
        printTree(tree->right);
        printf(" )");
    }
}

void PrintTreeWithTree(BinTree* tree) {
        printTree(tree->first);
        puts("");
}

int countTreeBTNodes(BTNode* tree) {
    if (tree == NULL)
        return 0;
    else 
        return 1 + countTreeBTNodes(tree->left) + countTreeBTNodes(tree->right);
}

bool containsTreeValue(BTNode* tree, int value) {
    if (!tree)
        return false;
    else return (tree->value) || containsTreeValue(tree->left, value) || containsTreeValue(tree->right, value);
}

bool containsValue(BinTree* tree, int value) {
    containsTreeValue(tree->first, value);
}

int heightTree(BTNode* tree) {
    if (!tree)
        return 0;
    else {
        if (tree->left == NULL && tree->right == NULL) return 0;
        return 1 + fmax(heightTree(tree->left), heightTree(tree->right));
    }
}

int heightOfTree(BinTree* tree) {
    heightTree(tree->first);
}

BTNode* copyTree(BTNode* tree) {
    if (!tree) 
        return NULL;
    else 
        return createBTNode(tree->value, copyTree(tree->left), copyTree(tree->right));
}

BTNode* copyTheTree(BinTree* tree) {
    return copyTree(tree->first);
}

bool treesEqual(BTNode* t1, BTNode* t2) {
    if (t1 == t2) return true;
    if (!t1 || !t2) return false;
    if (t1->value != t2->value) return false;
    return treesEqual(t1->left, t2->left) && treesEqual(t1->right, t2->right);
}
bool treesAreEqual(BinTree* t1, BinTree* t2) {
    return treesEqual(t1->first, t2->first);
}

bool isOrdered(BTNode* tree, int min, int max){
    if (!tree) return true;
    if (tree->value <= min || tree->value >= max) return false;
    return isOrdered(tree->left, min, tree->value) &&
           isOrdered(tree->right, tree->value, max);
}

bool isTreeOrdered(BTNode* tree) {
    return isOrdered(tree, INT_MIN, INT_MAX);
}

bool isBinTreeOrdered(BinTree* tree) {
    return isTreeOrdered(tree->first);
}

BTNode* createLeaf(int value) {
    return createBTNode(value, NULL, NULL);
}

BTNode* createNewLeaf(int value) {
    BinTree* tree;
    tree->first = createLeaf(value);
    return tree->first;
}

BTNode* insertOrdered(BTNode* tree, int value) {
    require("is ordered", isTreeOrdered(tree));
    if (tree == NULL) 
        tree = createLeaf(value);
    else if (value < tree->value) 
        tree->left = insertOrdered(tree->left, value);
    else 
        tree->right = insertOrdered(tree->right, value);
    ensure("is ordered", isTreeOrdered(tree));
    return tree;
}

BTNode* InsertionWithOrder(BinTree* tree, int value) {
    return insertOrdered(tree->first, value);
}

BTNode* InsertOrderedIteration(BTNode* tree, int value) {
    require("is ordered", isTreeOrdered(tree));
    if (!tree) return createLeaf(value);
    else {
        BTNode* t = tree;
        while (true) {
            if (value < t->value) {
                if (t->left)
                    t = t->left;
                else {
                    t->left = createLeaf(value);
                    break;
                }
            } else {
                if (t->right)
                    t = t->right;
                else {
                    t->right = createLeaf(value);
                    break;
                }
            }
        }
    }
    ensure("is ordered", isTreeOrdered(tree));
    return tree;
}

BTNode* InsertionWithOrderIter(BinTree* tree, int value) {
    return InsertOrderedIteration(tree->first, value);
}

void printInorder(BTNode* tree) {
    if (tree) {
        printInorder(tree->left);
        printf("%d ",tree->value);
        printInorder(tree->right);
    }
}

void printWithInorder(BinTree* tree) {
    prints("[ ");
    printInorder(tree->first);
    prints("]");
    puts("");
}

BTNode* efficientSearchingMethod(BTNode* tree, int value) {
    require("is ordered", isTreeOrdered(tree));
    if (!tree) return NULL;
    if (value == tree->value) return tree;
    if (value < tree->value) return efficientSearchingMethod(tree->left, value);
    return efficientSearchingMethod(tree->right, value); 
}

bool efficientSearch(BTNode* tree, int value) {
    return efficientSearchingMethod(tree, value) != NULL;
}

bool efficientTreeSearch(BinTree* tree, int value) {
    return efficientSearch(tree->first, value); 
}

BTNode* efficientSearchIterMethod(BTNode* tree, int value) {
    require("is ordered", isTreeOrdered(tree));
    while (!tree) {
        if (value < tree->value ) tree = tree->left;
        else if (value > tree->value) tree = tree->right;
        else return tree; 
    }
    return NULL;
}

bool efficientSearchIter(BTNode* tree, int value) {
    return efficientSearchIterMethod(tree, value) != NULL;
}

bool efficientTreesSearch(BinTree* tree, int value) {
    return efficientSearchIter(tree->first, value);
}




int main(void) {
    BinTree* tree = createBinTree();
    tree->first = createBTNode(10, createBTNode(8, createLeaf(5), createLeaf(9)), createBTNode(30, NULL, NULL));
    PrintTreeWithTree(tree);
    puts("");
    printb(containsValue(tree, 2));
    puts("");
    printi(heightOfTree(tree));
    puts("");
    printb(isBinTreeOrdered(tree));
    puts("");
    InsertionWithOrderIter(tree, 70);
    InsertionWithOrder(tree, 3);
    PrintTreeWithTree(tree);
    puts("");
    printWithInorder(tree);
    report_memory_leaks(true);
}