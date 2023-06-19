#pragma once

struct listEle {
    char name[50];
    int age;
    struct listEle *nextElem;
};

typedef struct listEle listElement;

listElement genElement(char name[50], int age);
listElement addElement(listElement currEle, listElement nextEle);
void printElement(listElement lstEle);

