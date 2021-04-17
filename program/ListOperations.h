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
    static unsigned long long measPutBeg(int);
    static unsigned long long measPutEnd(int);
    static unsigned long long measPutMid(int);

    void measRemTime(int size);
    static unsigned long long measRemBeg(int);
    static unsigned long long measRemEnd(int);
    static unsigned long long measRemMid(int);

    void measFindTime(int size);

    static list generateList(int size);

    bool active{};
    list linkedList;
};


#endif //SDIZO_1_LISTOPERATIONS_H
