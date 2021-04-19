#ifndef SDIZO_1_OPERATIONS_H
#define SDIZO_1_OPERATIONS_H

#include <string>
#include "Randomizer.h"

class Operations {
public:
    void displayMenu(std::string&);
    void displayMenu(const char*);
    void read();
    int readInt();
    std::string readStr();
    int sizeChoiceMenu(int[], int);
    int randomInt();
    int randomInt(int);
protected:
    std::string input;
    Randomizer randomizer = Randomizer();
};


#endif //SDIZO_1_OPERATIONS_H
