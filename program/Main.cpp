#include <iostream>
#include "Main.h"

#include "fstream"

int main(){
    srand((unsigned)time(0));
#if DEBUG
    std::cout << "Program is in debug mode!" << std::endl;
    std::cout << "It may affect performance!" << std::endl << std::endl;
#endif
    auto program = Main();
    return program.run();
}

int main1(){
    std::ofstream stream;
    stream.open("plik.txt");
    stream << "Raz dwa trzy, baba jaga patrzy.";
    stream.close();
    return 0;
}

int Main::run() {
    displayGreeting();
    while(keepGoing)
    {
        displayMenu();
        std::getline(std::wcin, input);
        interpretInput();
        //system("cls");
    }
    return 0;
}

void Main::displayGreeting() {
    std::wcout << L"Witamy w programie." << std::endl << std::endl;
}

void Main::displayMenu() {
    String menuText = L"1. Operacje na tablicy.\n";
    menuText += L"2. Operacje na liscie.\n";
    menuText += L"3. Operacje na kopcu.\n";
    menuText += L"4. Operacje na drzewie czerwono-czarnym.\n"
                "5. Operacje na drzewie AVL.\n";
    menuText += L"6. Zakoncz program.\n";
    std::wcout << menuText;
}

void Main::interpretInput() {
    int option;
    try{
        option = std::stoi(input);
        switch(option){
            case 1:
                arrayOperations();
                break;
            case 2:
                listOperations();
                break;
            case 3:
                heapOperations();
                break;
            case 4:
                rbTreeOperations();
                break;
            case 5:
                avlTreeOperations();
                break;
            case 6:
                keepGoing = false;
                break;
            default:
                throw 4;
        }
    } catch (...) {
        std::wcout << L"Niewlasciwy symbol." << std::endl;
        return;
    }
}

void Main::arrayOperations() {
    arrayOperator.run();
}

void Main::listOperations() {
    listOperator.run();
}

void Main::heapOperations() {
    heapOperator.run();
}

void Main::rbTreeOperations() {
    rbOperator.run();
}

void Main::avlTreeOperations() {
    avlOperations.run();
}
