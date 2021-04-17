#include "ListOperations.h"
#include "TextFileReader.h"
#include "StopWatch.h"

void ListOperations::run() {
    active = true;
    while(active)
    {
        menu();
        interpretInput();
    }
}

void ListOperations::menu() {
    displayMenu("OPERACJE NA LISCIE DWUKIERUNKOWEJ");
}

void ListOperations::interpretInput() {
    int option;
    try{
        option = readInt();
        switch(option){
            case 1:
                fromFile();
                break;
            case 2:
                linkedList = list();
                break;
            case 3:
                addElement();
                break;
            case 4:
                removeElement();
                break;
            case 5:
                findElement();
                break;
            case 6:
                display();
                break;
            case 7:
                measurements();
                break;
            case 8:
                active = false;
                break;
            default:
                throw 4;
        }
    } catch (...) {
        std::wcout << L"Niewlasciwy symbol." << std::endl;
        return;
    }
}

void ListOperations::addElement() {
    std::string text = "Podaj wartosc, ktora chcesz umiescic:\n";
    std::cout << text;
    int value = readInt();
    text = "Podaj wartosc, po ktorej chcesz dodac element\n"
           "(uzyj 'last', zeby dodac na koncu,\n"
           "lub 'first', zeby dodac na poczatku):\n";
    std::cout << text;
    read();
    try{
        std::string sideText;
        if(input == "first")
        {
            linkedList.pushFront(value);
            sideText = " na poczatku listy.\n";
        } else if(input == "last")
        {
            linkedList.pushBack(value);
            sideText = " na koncu listy.\n";
        } else {
            int predecessor = std::stoi(input);
            if(linkedList.contains(predecessor)){
                sideText = " po elemencie ";
                sideText += std::to_string(predecessor);
                sideText += ".\n";
            } else {
                sideText = " na poczatku listy.\n";
            }
            linkedList.putAfter(predecessor, value);
        }
        text = "Dodano element ";
        text += std::to_string(value);
        text += sideText;
    } catch (IndexOutOfBoundException& e) {
        text = "Niewlasciwy indeks!\n";
    }

    std::cout << text;
}

void ListOperations::removeElement() {
    std::string text = "Podaj wartosc klucza, ktory chcesz usunac:\n"
                       "(uzyj 'last', zeby usunac ostatni element,\n"
                       "lub 'first', zeby usunac pierwszy):\n";
    try{
        if(linkedList.isEmpty())
            throw IndexOutOfBoundException();
        int keyToRemove;
        std::cout << text;
        read();
        if(input == "first")
        {
            linkedList.removeFirst();
            text = "Usunieto pierwszy element.\n";
        } else if(input == "last")
        {
            linkedList.removeLast();
            text = "Usunieto ostatni element.\n";
        } else {
            keyToRemove = std::stoi(input);
            bool removed = linkedList.remove(keyToRemove);
            if(removed){
                text = "Usunieto element o wartosci ";
            } else {
                text = "Lista nie zawierala elementu o wartosci ";
            }
            text += std::to_string(keyToRemove);
            text += ".\n";
        }
    } catch (IndexOutOfBoundException& e) {
        text = "Nie mozna usunac elementu z pustej listy.\n"
               "Operacje anulowano.\n";
    }

    std::cout << text;
}

void ListOperations::findElement() {
    std::string text = "Podaj element, ktory chcesz wyszukac:\n";
    std::cout << text;
    int value = readInt();
    bool contains = linkedList.contains(value);
    if(contains)
    {
        text = "Lista zawiera element o wartosci ";
    } else {
        text = "Lista nie zawiera elementu o wartosci ";
    }
    text += std::to_string(value);
    text += ".\n";
    std::cout << text;
}

void ListOperations::display() {
    std::cout << linkedList.toString() << std::endl;
}

void ListOperations::fromFile() {
    std::string text = "Wprowadz nazwe, sciezke wzgledem aktualnego folderu,\n"
                       "lub pelna sciezke do pliku:\n";
    std::cout << text;
    std::string filename;
    read();
    filename = input;
    try {
        TextFileReader reader;
        auto content = reader.fromFile(filename);
        linkedList = list();
        for(int i = 1; i <= content[0]; i++)
        {
            linkedList.pushBack(content[i]);
        }
    } catch(...) {
        std::cout << "Wystapil problem.\n"
                     "Operacje anulowano.\n";
    }
}

void ListOperations::measurements() {
    std::cout << "Dla jakiej operacji chcesz mierzyc czas?\n"
                 "1. Dodawanie elementu.\n"
                 "2. Usuwanie elementu.\n"
                 "3. Wyszukanie elementu.\n";
    int option = readInt();
    std::cout << "Dla jakiego rozmiaru struktury chcesz mierzyc czas?\n";
    int options[] = {2500, 5000, 12500, 25000, 50000};
    int numberOfElements = sizeChoiceMenu(options, 5);
    switch(option)
    {
        case 1:
            measPutTime(numberOfElements);
            break;
        case 2:
            measRemTime(numberOfElements);
            break;
        case 3:
            measFindTime(numberOfElements);
            break;
        default:
            throw 4;
            break;
    }
}

void ListOperations::measPutTime(int size) {
    std::cout << "Gdzie chcesz dodawac element?\n"
                 "1. Na poczatku.\n"
                 "2. Na koncu.\n"
                 "3. W srodku.\n";
    int option = readInt();
    std::string text = "Sredni czas dodania elementu ";
    unsigned long long output;
    switch(option)
    {
        case 1:
            text += "na poczatku";
            output = measPutBeg(size);
            break;
        case 2:
            text += "na koncu";
            output = measPutEnd(size);
            break;
        case 3:
            text += "w srodku";
            output = measPutMid(size);
            break;
        default:
            throw 4;
    }
    text += "listy o dlugosci ";
    text += std::to_string(size);
    text += " to ";
    text += std::to_string(output);
    text += ".\n";
    std::cout << text;
}

unsigned long long ListOperations::measPutBeg(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        auto measurementsStructure = generateList(size);
        std::cout << "|";//todo
        StopWatch watch;
        watch.start();
        measurementsStructure.pushFront(89);
        watch.stop();
        average += watch.getLastMeasurmentMicrosec();
        if(!watch.getLastMeasurmentMicrosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    return average;
}

list ListOperations::generateList(int size) {
    auto measurementsStructure = list();
    for(int j = 0; j < size; j++)
    {
        measurementsStructure.pushBack(rand() % (size / 2));
    }
    return measurementsStructure;
}

unsigned long long ListOperations::measPutEnd(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        auto measurementsStructure = generateList(size);
        std::cout << "|";//todo
        StopWatch watch;
        watch.start();
        measurementsStructure.pushBack(89);
        watch.stop();
        average += watch.getLastMeasurmentMicrosec();
        if(!watch.getLastMeasurmentMicrosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    return average;
}

unsigned long long ListOperations::measPutMid(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        auto measurementsStructure = generateList(size);
        std::cout << "|";//todo
        StopWatch watch;
        int index = size / 2;
        watch.start();
        //dodajemy dokładnie w połowie listy
        measurementsStructure.addAtPosition(89, index);
        watch.stop();
        average += watch.getLastMeasurmentMicrosec();
        if(!watch.getLastMeasurmentMicrosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    return average;
}

void ListOperations::measRemTime(int size) {
    std::cout << "Z ktorego miejsca chcesz usuwac element?\n"
                 "1. Z poczatku.\n"
                 "2. Z konca.\n"
                 "3. Ze srodka.\n";
    int option = readInt();
    unsigned long long output;
    std::string text = "Sredni czas usuwania elementu ";
    switch(option)
    {
        case 1:
            output = measRemBeg(size);
            text += "z poczatku";
            break;
        case 2:
            output = measRemEnd(size);
            text += "z konca";
            break;
        case 3:
            output = measRemMid(size);
            text += "ze srodka";
            break;
        default:
            throw 4;
    }
    text += " listy o dlugosci ";
    text += std::to_string(size);
    text += " to ";
    text += std::to_string(output);
    text += ".\n";
    std::cout << text;
}

unsigned long long ListOperations::measRemBeg(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        auto measurementsStructure = generateList(size);
        std::cout << "|";//todo
        StopWatch watch;
        watch.start();
        measurementsStructure.removeFirst();
        watch.stop();
        average += watch.getLastMeasurmentMicrosec();
        if(!watch.getLastMeasurmentMicrosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    return average;
}

unsigned long long ListOperations::measRemEnd(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        auto measurementsStructure = generateList(size);
        std::cout << "|";//todo
        StopWatch watch;
        watch.start();
        measurementsStructure.removeLast();
        watch.stop();
        average += watch.getLastMeasurmentMicrosec();
        if(!watch.getLastMeasurmentMicrosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    return average;
}

unsigned long long ListOperations::measRemMid(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        auto measurementsStructure = generateList(size);
        std::cout << "|";//todo
        StopWatch watch;
        int index = size / 2;
        watch.start();
        measurementsStructure.removeAt(index);
        watch.stop();
        average += watch.getLastMeasurmentMicrosec();
        if(!watch.getLastMeasurmentMicrosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    return average;
}

void ListOperations::measFindTime(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        auto measurementsStructure = generateList(size);
        std::cout << "|";//todo
        StopWatch watch;
        int32_t elementToFind = rand() % size;
        bool contains;
        watch.start();
        contains = measurementsStructure.contains(elementToFind);
        watch.stop();
        if(contains)
            measurementsStructure.removeFirst();
        average += watch.getLastMeasurmentMicrosec();
        if(!watch.getLastMeasurmentMicrosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    std::string text = "Sredni czas wyszukania elementu w liscie o dlugosci ";
    text += std::to_string(size);
    text += " wynosi ";
    text += std::to_string(average);
    text += ".\n";
    std::cout << text;
}
