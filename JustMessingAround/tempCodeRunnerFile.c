#include <stdlib.h>
#include "../prog1lib/lib/base.h"
#include "list.h"

int main(void){
    List* linkedList = createList();
    Node* n0 = createNode(7,NULL);
    linkedList->first = n0;
    linkedList->first = prependList(5,linkedList->first);
    printi(listAddValues(linkedList));
    puts("");
    linkedList->last = n0; // Only once, appendning does the rest autocmatically.
    efficientAppending(linkedList, 9);
    insertedOrderList(linkedList,8);
    printLis(linkedList);
    
    Node* rest = prependList(5,prependList(7,NULL));
    Node* list = createNode(4,rest);
    printi(listLengthRecursively(list));
    puts("");
    printi(listSum(list));
    puts("");
    printList(list);
    insertOrdered(list, 12);
    printList(list);

    return 0;
}