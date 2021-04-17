#ifndef SDIZO_1_HEAPOPERATIONS_H
#define SDIZO_1_HEAPOPERATIONS_H

#include <iostream>
#include <string>
#include <structures.h>
#include "Operations.h"

class HeapOperations : public Operations {
public:
    void run();
private:
    void menu();
    void interpretInput();
    void addElement();
    void display();
    void removeElement();
    void findElement();
    void fromFile();
    void measurements();
    void measPutTime();
    void measFindTime();
    void measRemTime();
    unsigned long long measRemMax(int size);
    unsigned long long measRemAv(int size);
    static heap generateHeap(int size);

    bool active;
    heap mHeap;
};


#endif //SDIZO_1_HEAPOPERATIONS_H
