#include "Operations.h"
#include <iostream>

void Operations::displayMenu(std::string& header) {
    std::string menuText;
    menuText += header;
    menuText += "\n1. Zbuduj z pliku\n"
                "2. Stworz nowa tablice\n"
                "3. Dodaj element\n"
                "4. Usun element\n"
                "5. Znajdz element\n"
                "6. Wyswietl\n"
                "7. Pomiar czasu\n"
                "8. Wroc do menu glownego\n\n";
    std::cout << menuText;
}

void Operations::read() {
    std::getline(std::cin, input);
}

int Operations::readInt() {
    read();
    return std::stoi(input);
}

int Operations::sizeChoiceMenu(int *possibilities, int numberOfPossibilities) {
    std::string text;
    for(int i = 0; i < numberOfPossibilities; i++)
    {
        text += std::to_string(i + 1);
        text += ". ";
        text += std::to_string(possibilities[i]);
        text += "\n";
    }
    std::cout << text;
    int option = readInt();
    if(option > numberOfPossibilities)
        throw 4;
    return possibilities[option - 1];
}

void Operations::displayMenu(const char * header) {
    std::string menuText;
    menuText += header;
    menuText += "\n1. Zbuduj z pliku\n"
                "2. Stworz nowa strukture\n"
                "3. Dodaj element\n"
                "4. Usun element\n"
                "5. Znajdz element\n"
                "6. Wyswietl\n"
                "7. Pomiar czasu\n"
                "8. Wroc do menu glownego\n\n";
    std::cout << menuText;
}

std::string Operations::readStr() {
    read();
    return input;
}
