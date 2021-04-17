#ifndef SDIZO_1_RBTREEOPERATIONS_H
#define SDIZO_1_RBTREEOPERATIONS_H

#include <structures.h>
#include <iostream>
#include <string>
#include "Operations.h"

class RBTreeOperations : public Operations{
public:
    void run();
private:
    void menu();
    void interpretInput();
    void addElement();
    void removeElement();
    void findElement();
    void display();
    void fromFile();

    void measurements();

    void measPutTime(int size);

    rbtree generateTree(int size);
    bool active;

    rbtree tree;
};


#endif //SDIZO_1_RBTREEOPERATIONS_H
