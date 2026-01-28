/*
    Compile: make wish_tree
    Run: ./wish_tree
    Compile & run: make wish_tree && ./wish_tree
*/

#include <stdio.h>
#include "../prog1lib/lib/base.h"
#include <math.h>

typedef struct Element Element;

void free_element(Element* element);


typedef struct Node{
    struct Node* next;
    char* value;
}Node;

/*
    Returns a pointer to a dynamically allocated node.
*/
Node* new_node(char* value, Node* next){
    Node* node = xmalloc(sizeof(Node));
    node->next = next;
    node->value = s_copy(value);
    return node;
}

/* 
    Releases the memory used by node. 
*/
Node* free_node(Node* node){
    Node* next = node->next;
    free(node->value);
    free(node);
    return next;
}

/*
    Returns the length of a list of nodes.
*/
int length(Node* node){
    int count = 0;
    while(node != NULL){
        count++;
        node = node->next;
    }
    return count;
}

/*
    Returns true if the list of nodes contains find.
*/
bool contains(Node* node, char* find){
    while(node != NULL){
        if(strcmp(node->value, find) == 0){
            return true;
        }
        node = node->next;
    }
    return false;
}


/* 
    A TreeNode has a left and right successor of type TreeNode. A successor TreeNode is a TreeNode or NULL
        
            TreeNode root
           /          \
          /            \
    TreeNode left      TreeNode right
    /       \       /           \
   ...      ...    ...          ...
*/

typedef struct TreeNode{
    struct TreeNode* left;
    struct TreeNode* right;
    struct Element* element;
}TreeNode;

/*
    Returns a pointer to a dynamically allocated tree_node.
*/
TreeNode* new_tree_node(Element* element){
    TreeNode* bnode = xmalloc(sizeof(TreeNode));
    bnode->left = NULL;
    bnode->right = NULL;
    bnode->element = element;
    return bnode;
}

/*  TODO: g)
    Releases the memory used by a tree_node and also frees the included element.
*/
void free_tree_node(TreeNode* tree){  // postorder
     if (tree == NULL) return;
    free_tree_node(tree->left);
    free_tree_node(tree->right);
    free_element(tree->element);
    free(tree);
}


//TODO: b)
struct Element{
    char* wish;
    int count;
    Node* children;
};

//TODO: b)
Element* new_element(char* wish, char* child){
    Element* x = xmalloc(sizeof(Element));
    x->wish = s_copy(wish);
    x->count = 1;
    x->children = new_node(child, NULL);
    return x;
}

//TODO: g)
void free_element(Element* element){
 if (element == NULL) return;
    free(element->wish);
    while (element->children != NULL) {
        element->children = free_node(element->children);
    }
    free(element);
}
//TODO: c)
TreeNode* add_wish(TreeNode* tree, char* wish, char* child){
    if (tree == NULL) {
        Element* e = new_element(wish, child);
        return new_tree_node(e);
    }

    int cmp = strcmp(wish, tree->element->wish);

    if (cmp == 0) {
        tree->element->count++;
        tree->element->children = new_node(child, tree->element->children); //prepends
    } 
    else if (cmp < 0) {
        tree->left = add_wish(tree->left, wish, child);
    } 
    else {
        tree->right = add_wish(tree->right, wish, child);
    }

    return tree;
}

typedef struct ElementNode{
    struct ElementNode* next;
    Element* element;
}ElementNode;

ElementNode* new_element_node(Element* element, ElementNode* next){
    ElementNode* en = xmalloc(sizeof(ElementNode));
    en->next = next;
    en->element = element;
    return en;
}
//TODO: g)
void free_element_list(ElementNode* en){
     while (en != NULL) {
        ElementNode* next = en->next;
        free(en);
        en = next;
    }
}

void print_element_list(ElementNode* list, int n){
    printf("%55s\t%6s\n", "Wunsch", "Anzahl");
    while(n > 0 && list != NULL){
        printf("%55s\t%6d\n", list->element->wish, list->element->count); 
        n--;
        list = list->next;
    }
}

ElementNode* flatten(TreeNode* tree, ElementNode* list) {
    if (tree == NULL) return list; // Base case: empty tree

    // 1. Flatten left subtree and get updated head
    list = flatten(tree->left, list);

    // 2. Add current tree node to the front of the list
    ElementNode* node = new_element_node(tree->element, list);
    list = node; // update head

    // 3. Flatten right subtree and get updated head
    list = flatten(tree->right, list);

    return list; // return head of flattened list
}

//TODO: e)
ElementNode* insert_ordered_by_count(ElementNode* result, TreeNode* tree){  //inorder
    if (tree == NULL) return result;

    result = insert_ordered_by_count(result, tree->left);

    ElementNode* new_node = xmalloc(sizeof(ElementNode));
    new_node->element = tree->element;
    new_node->next = NULL;

    if (result == NULL || tree->element->count >= result->element->count) {
        new_node->next = result;
        result = new_node;
    } else {
        ElementNode* current = result;
        while (current->next != NULL && current->next->element->count > tree->element->count) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }

    result = insert_ordered_by_count(result, tree->right);

    return result;
}
//TODO: d)
// TODO: d)
void print_tree_as_list(TreeNode* tree){
    if (tree == NULL) {
        return;
    }

    print_tree_as_list(tree->left);

    printf("%-55s %-10d ", tree->element->wish, tree->element->count);

    Node* current_child = tree->element->children;
    while (current_child != NULL) {
        printf("%s", current_child->value);
        if (current_child->next != NULL) {
            printf(", ");
        }
        current_child = current_child->next;
    }
    printf("\n");

    print_tree_as_list(tree->right);
}


// Skips the rest of the current line.
char* skip_line(char* s) {
    while (*s != '\n' && *s != '\0') s++;
    if (*s == '\n') s++;
    return s;
}

// Skips the current token.
char* skip_token(char* s) {
    while (*s != ',' && *s != '\n' && *s != '\0') s++;
    return s;
}

// Skips spaces.
char* skip_spaces_and_commas(char* s) {
    while (*s == ' ' || *s == ',') s++;
    return s;
}


// Create a new token from s (inclusive) to t (exclusive).
char* new_token(char* s, char* t) {
    char* token = xmalloc(t - s + 1);
    int i = 0;
    while (s < t) {
        token[i] = *s;
        i++;
        s++;
    }
    token[i]= '\0';
    return token;
}

// Returns a new token by first skipping spaces and commas and then reading the token. 
// Sets *s to the first character after the token.
char* next_token(/*INOUT*/char** s) {
    *s = skip_spaces_and_commas(*s);
    char* t = skip_token(*s);
    char* token = new_token(*s, t);
    *s = t; // set *s to the character after the token
    return token;
}


/* 
    This function reads in one line of the wish text file and adds the wishes of a child to tree.
*/
TreeNode* read_wish_list(char** s, TreeNode* tree){
    char* child = next_token(s);
    
    while(**s != '\0' && **s != '\n'){
        char* wish = next_token(s);
        *s = skip_spaces_and_commas(*s);
        tree = add_wish(tree, wish, child); 
        free(wish);
    }
    
    free(child);
    return tree;
}

/*  
    This function reads the whole file and uses the read_wish_list function to parse a single line.
*/
TreeNode* read_wishes(char* filename, TreeNode* tree){
    char* file = s_read_file(filename);
    char* s = file;
    s = skip_line(s);
    while(*s != '\0'){
        tree = read_wish_list(&s, tree);
        s = skip_line(s);
        
    }
    free(file);
    return tree;
}


int main(int argc, char** argv){
    report_memory_leaks(true);
   
    TreeNode* tree = read_wishes("wishes.txt", NULL);
    
    printf("%-50s %-10s %s\n", "Wunsch", "Anzahl", "Kinder");
    print_tree_as_list(tree);
    printf("\n");

    ElementNode* sorted_by_count = insert_ordered_by_count(NULL, tree);
    
    print_element_list(sorted_by_count, 10);
    
    //TODO: f)
    int children_count = 0;
    Node* children_list = NULL;
    ElementNode* current_gift_node = sorted_by_count;
    int gifts_to_check = 11;

    while (current_gift_node != NULL && gifts_to_check > 0) {
        Element* current_gift = current_gift_node->element;
        Node* child_node = current_gift->children;

        while (child_node != NULL) {
            if (!contains(children_list, child_node->value)) {
                children_list = new_node(child_node->value, children_list);
                children_count++;
            }
            child_node = child_node->next;
        }
        
        current_gift_node = current_gift_node->next;
        gifts_to_check--;
    }
    printf("\n");
    printf("Children receiving at least one of the top 11 gifts: %d\n", children_count);
    printf("\n");
    while (children_list != NULL) {
        children_list = free_node(children_list);
    }
    //TODO: g)
    free_element_list(sorted_by_count);
    free_tree_node(tree);
    return 0;
}



/* 
gcc wish_tree.c ../prog1lib/lib/base.c -o x
 
./x
 
*/