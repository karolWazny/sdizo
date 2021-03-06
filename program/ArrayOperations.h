#ifndef SDIZO_1_ARRAYOPERATIONS_H
#define SDIZO_1_ARRAYOPERATIONS_H

#include <string>
#include <structures.h>
#include "Operations.h"

class ArrayOperations : public Operations {
public:
    void run();
private:
    void menu();
    void interpretInput();
    void fromFile();
    void displayArray();
    void addElement();
    void removeElement();
    void findElement();
    void timeMeasurment();
    void measureFindingTime();
    void measurePuttingTime();
    unsigned long long measPutBeg(int size);
    unsigned long long measPutMid(int size);
    unsigned long long measPutEnd(int size);
    void measureRemovingTime();

    unsigned long long measRemBeg(int size);
    unsigned long long measRemMid(int size);
    unsigned long long measRemEnd(int size);

     array generateArray(int param);

    array tab = array();

    bool active = true;
    std::string input;
};

#endif //SDIZO_1_ARRAYOPERATIONS_H
