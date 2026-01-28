#include <stdio.h>
#include <stdlib.h>
#include "../prog1lib/lib/base.h"

typedef enum {R, B} Color;
typedef struct RBNode {
    Color color;
    int value;
    struct RBNode* left;
    struct RBNode* right;
}RBNode;

RBNode* rotateLeft(RBNode* t) {
    RBNode* r = t->right;
    t->right = r->left;
    r->left = t;
    return r;
}

RBNode* rotateRight(RBNode* t) {
    RBNode* l = t->left;
    t->left = l->right;
    l->right = t;
    return l;
}
RBNode* balance(RBNode* t) {
    if (t == NULL) return NULL;
    bool lRed = t->left != NULL && t->left->color == R; // is left red?
    bool rRed = t->right != NULL && t->right->color == R; // is left red?
    if (!lRed && !rRed) return t;
    RBNode * ll = (t->left == NULL) ? NULL : t->left->left;
    RBNode * lr = (t->left == NULL) ? NULL : t->left->right;
    RBNode * rl = (t->right == NULL) ? NULL : t->right->left;
    RBNode * rr = (t->right == NULL) ? NULL : t->right->right;
    bool llRed = ll != NULL && ll->color == R;
    bool lrRed = lr != NULL && lr->color == R;
    bool rlRed = rl != NULL && rl->color == R;
    bool rrRed = rr != NULL && rr->color == R;
    RBNode *a, *b, *c, *d;
    int x, y, z;
    if (lRed && llRed) {
        /*
        a = ll->left;
        b = ll->right;
        c = t->left->right;
        d = t->right;
        x = ll->value;
        y= t->left->value;
        z = t->value;
        */
        RBNode* newRoot = rotateRight(t);
        newRoot->color = B;
        newRoot->left->color = R;
        newRoot->right->color = R;
        return newRoot;
    } else if (lRed && lrRed) {
        /*
        a = ll;
        b = lr->left;
        c = lr->right;
        d = t->right;
        x = t->left->value;
        y = lr->value;
        z = t->value;
        t->right = lr;
        */
        t->left = rotateLeft(t->left);
        RBNode* newRoot = rotateRight(t);
        newRoot->color = B;
        newRoot->left->color = R;
        newRoot->right->color = R;
        return newRoot;
    } else if (rRed && rlRed) {
        /*
        a = t->left;
        b = rl->left;
        c = rl->right;
        d = rr;
        x = t->value;
        y = rl->value;
        z = t->right->value;
        t->left = rl;
        */
        t->right = rotateRight(t->right);
        RBNode* newRoot = rotateLeft(t);
        newRoot->color = B;
        newRoot->left->color = R;
        newRoot->right->color = R;
        return newRoot;
    } else if (rRed && rrRed) {
        /*
        a = t->left;
        b = rl;
        c = rr->left;
        d = rr->right;
        x = t->value;
        y = t->right->value;
        z = rr->value;
        t->left = rr;
        */
        RBNode* newRoot = rotateLeft(t);
        newRoot->color = B;
        newRoot->left->color = R;
        newRoot->right->color = R;
        return newRoot;
    } else if (lRed && rRed) {
        t->color = R;
        t->left->color = B;
        t->right->color = B;
        return t;
    } 
    return t;
}    