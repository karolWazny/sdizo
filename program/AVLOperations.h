#ifndef SDIZO_1_AVLOPERATIONS_H
#define SDIZO_1_AVLOPERATIONS_H

#include "Operations.h"
#include <structures.h>
#include <iostream>
#include <string>

class AVLOperations : public Operations {
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
    void measRemTime(int size);
    void measFindTime(int size);

    avltree generateTree(int size);
    bool active;

    avltree tree;
};


#endif //SDIZO_1_AVLOPERATIONS_H
