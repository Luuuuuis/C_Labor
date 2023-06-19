#include "listElem.h"
#include <stdio.h>
 
int main() {
    listElement *start;
    start = (listElement *)malloc(sizeof(listElement));
    start->nextElem = NULL;

    curr = addElement(start, genElement("hanoi", 69));
    curr = addElement(curr, genElement("haja", 69));

    printElement(curr);
    printElement(*start.nextElem);
}