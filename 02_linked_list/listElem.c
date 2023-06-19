#include "listElem.h"
#include <string.h>
#include <stdio.h>

listElement genElement(char name[], int age) {
    listElement newEle;

    strcpy(newEle.name, name);
    newEle.age = age;

    return newEle;
}

listElement addElement(listElement currEle, listElement nextEle) {
    currEle.nextElem = &nextEle;
    return nextEle;
}

void printElement(listElement lstEle) {
    printf("name: %s alter: %d nxt: %d\n", lstEle.name, lstEle.age, lstEle.nextElem);
}