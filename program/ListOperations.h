#ifndef SDIZO_1_LISTOPERATIONS_H
#define SDIZO_1_LISTOPERATIONS_H

#include <iostream>
#include <string>
#include <structures.h>
#include "Operations.h"

class ListOperations : public Operations{
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
    void measPutTime(int);
    unsigned long long measPutBeg(int);
    unsigned long long measPutEnd(int);
    unsigned long long measPutMid(int);

    void measRemTime(int size);
    unsigned long long measRemBeg(int);
    unsigned long long measRemEnd(int);
    unsigned long long measRemMid(int);

    void measFindTime(int size);

    list generateList(int size);

    bool active{};
    list linkedList;
};


#endif //SDIZO_1_LISTOPERATIONS_H
