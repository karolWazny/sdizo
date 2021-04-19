#include "ArrayOperations.h"
#include <iostream>
#include <cstdlib>
#include "TextFileReader.h"
#include "StopWatch.h"


void ArrayOperations::run() {
    active = true;
    while(active)
    {
        menu();
        std::getline(std::cin, input);
        interpretInput();
    }
}

void ArrayOperations::menu() {
    std::string header("TABLICA DYNAMICZNA");
    displayMenu(header);

}

void ArrayOperations::interpretInput() {
    int option;
    try{
        option = std::stoi(input);
        switch(option){
            case 1:
                fromFile();
                break;
            case 2:
                tab = array();
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
                displayArray();
                break;
            case 7:
                timeMeasurment();
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

void ArrayOperations::fromFile() {
    std::string text = "Wprowadz nazwe, sciezke wzgledem aktualnego folderu,\n"
                       "lub pelna sciezke do pliku:\n";
    std::cout << text;
    std::string filename;
    std::getline(std::cin, filename);
    try {
        TextFileReader reader;
        auto content = reader.fromFile(filename);
        tab = array(content[0]);
        for(int i = 1; i <= content[0]; i++)
        {
            tab[i -1] = content[i];
        }
    } catch(...) {
        std::cout << "Wystapil problem.\n"
                     "Operacje anulowano.\n";
    }
}

void ArrayOperations::displayArray() {
    std::cout << tab.toString() << std::endl << std::endl;
}

void ArrayOperations::addElement() {
    std::string text = "Podaj wartosc, ktora chcesz umiescic:\n";
    std::cout << text;
    std::getline(std::cin, input);
    int value = std::stoi(input);
    text = "Podaj pozycje, na ktorej chcesz dodac element\n"
                       "(uzyj 'last', zeby dodac na koncu,\n"
                       "lub 'first', zeby dodac na poczatku):\n";
    std::cout << text;
    std::getline(std::cin, input);
    try{
        int position;
        if(input == "first")
        {
            tab.pushFront(value);
            position = 0;
        } else if(input == "last")
        {
            position = tab.getLength();
            tab.pushBack(value);
        } else {
            position = std::stoi(input);
            tab.putAtPosition(value, position);
        }
        text = "Dodano element: ";
        text += std::to_string(value);
        text += " na pozycji o ideksie ";
        text += std::to_string(position);
        text += "\n";
    } catch (IndexOutOfBoundException& e) {
        text = "Niewlasciwy indeks!\n";
    }

    std::cout << text;
}

void ArrayOperations::removeElement() {
    std::string text = "Podaj pozycje, z ktorej chcesz usunac element:\n"
                       "(uzyj 'last', zeby usunac ostatni element,\n"
                       "lub 'first', zeby usunac pierwszy):\n";
    if(tab.getLength() == 0)
    {
        std::cout << "Nie mozna usunac elementu z pustej tablicy.\n"
                     "Operacje anulowano.\n";
        return;
    }
    std::cout << text;
    std::getline(std::cin, input);
    try{
        int position;
        if(input == "first")
        {
            position = 0;
            tab.removeFirst();
        } else if(input == "last")
        {
            position = tab.getLength();
            tab.removeLast();
        } else {
            position = std::stoi(input);
            if(position >= tab.getLength())
                throw IndexOutOfBoundException();
            tab.removeAt(position);
        }
        text = "Usunieto element na pozycji o ideksie ";
        text += std::to_string(position);
        text += "\n";
    } catch (IndexOutOfBoundException& e) {
        text = "Niewlasciwy indeks!\nOperacje anulowano.\n";
    }

    std::cout << text;
}

void ArrayOperations::findElement() {
    std::string text = "Podaj element, ktory chcesz wyszukac:\n";
    std::cout << text;
    std::getline(std::cin, input);
    int value;
    value = std::stoi(input);
    bool contains = tab.contains(value);
    if(contains)
    {
        text = "Tablica zawiera element o wartosci ";
    } else {
        text = "Tablica nie zawiera elementu o wartosci ";
    }
    text += std::to_string(value);
    text += ".\n";
    std::cout << text;
}

void ArrayOperations::timeMeasurment() {
    std::string text = "Co chcesz zmierzyc?\n"
                       "1. Czas wyszukania elementu.\n"
                       "2. Czas dodania elementu.\n"
                       "3. Czas usuwania elementu.\n";
    std::cout << text;
    std::getline(std::cin, input);
    int option = std::stoi(input);
    switch(option)
    {
        case 1:
            measureFindingTime();
            break;
        case 2:
            measurePuttingTime();
            break;
        case 3:
            measureRemovingTime();
            break;
        default:
            std::cout << "Nieprawidlowa opcja.\nPomiar anulowano.\n";
            return;
    }
}

void ArrayOperations::measureFindingTime() {
    std::cout << "Dla ilu elementow chcesz zmierzyc czas wyszukiwania?\n";
    int options[] = {25000, 50000, 125000, 250000, 500000};
    int numberOfElements = sizeChoiceMenu(options, 5);
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        array measurementsArray = generateArray(numberOfElements);
        std::cout << "|";//todo
        int32_t seekedElement = randomInt(numberOfElements);
        StopWatch watch;
        bool contains;
        watch.start();
        contains = measurementsArray.contains(seekedElement);
        watch.stop();
        if(contains)
            average += watch.getLastMeasurmentPiccosec();
        else
        {
            average += watch.getLastMeasurmentPiccosec();
            watch.start();
        }
        if(!watch.getLastMeasurmentPiccosec())
        {
            i--;
            continue;
        }
    }
    std::cout << std::endl;
    average /= 128;
    std::cout << "Sredni czas wyszukania elementu\n"
                 "dla tablicy o dlugosci " << std::to_string(numberOfElements)
                 << " wynosi " << std::to_string(average)
                 << std::endl;
}

void ArrayOperations::measurePuttingTime() {
    std::cout << "Dla jakiego rozmiaru struktury chcesz mierzyc czas?\n";
    int options[] = {250000, 500000, 1250000, 2500000, 5000000};
    int numberOfElements = sizeChoiceMenu(options, 5);
    std::cout << "Gdzie chcesz wstawiac nowy element?\n"
                 "1. Na poczatku.\n"
                 "2. W srodku.\n"
                 "3. Na koncu.\n";
    int option = readInt();
    unsigned long long output;
    std::string text = "Sredni czas dodania elementu ";
    switch(option)
    {
        case 1:
            output = measPutBeg(numberOfElements);
            text += "na poczatku\n";
            break;
        case 2:
            output = measPutMid(numberOfElements);
            text += "w srodku\n";
            break;
        case 3:
            output = measPutEnd(numberOfElements);
            text += "na koncu\n";
            break;
        default:
            throw 4;
    }
    text += "tablicy o rozmiarze ";
    text += std::to_string(numberOfElements);
    text += " elementow\n"
            "to ";
    text += std::to_string(output);
    text += ".\n";
    std::cout << text;
}

array ArrayOperations::generateArray(int numberOfElements) {
    array measurementsArray(numberOfElements);
    for(int j = 0; j < numberOfElements; j++)
    {
        measurementsArray[j] = (randomInt(numberOfElements/2));
    }
    return measurementsArray;
}

unsigned long long ArrayOperations::measPutBeg(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        array measurementsArray = generateArray(size);
        std::cout << "|";//todo
        int32_t elementToPut = randomInt(size/2);
        StopWatch watch;
        watch.start();
        measurementsArray.pushFront(elementToPut);
        watch.stop();
        average += watch.getLastMeasurmentPiccosec();
        if(!watch.getLastMeasurmentPiccosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    return average;
}

unsigned long long ArrayOperations::measPutMid(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        array measurementsArray = generateArray(size);
        std::cout << "|";//todo
        int32_t elementToPut = randomInt(size/2);
        StopWatch watch;
        watch.start();
        measurementsArray.putAtPosition(4, size/2);
        watch.stop();
        average += watch.getLastMeasurmentPiccosec();
        if(!watch.getLastMeasurmentPiccosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    return average;
}

unsigned long long ArrayOperations::measPutEnd(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        array measurementsArray = generateArray(size);
        std::cout << "|";//todo
        int32_t elementToPut = randomInt(size/2);
        StopWatch watch;
        watch.start();
        measurementsArray.pushBack(elementToPut);
        watch.stop();
        average += watch.getLastMeasurmentPiccosec();
        if(!watch.getLastMeasurmentPiccosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    return average;
}

void ArrayOperations::measureRemovingTime() {
    std::cout << "Dla jakiej ilosci danych w tablicy chcesz mierzyc czas?\n";
    int options[] = {250000, 500000, 1250000, 2500000, 5000000};
    int numberOfElements = sizeChoiceMenu(options, 5);
    std::cout << "Skad chcesz usuwac element?\n"
                 "1. Z poczatku.\n"
                 "2. Ze srodka.\n"
                 "3. Ze konca.\n";
    int option = readInt();
    unsigned long long output;
    std::string text = "Sredni czas usuniecia elementu ";
    switch(option)
    {
        case 1:
            output = measRemBeg(numberOfElements);
            text += "na poczatku\n";
            break;
        case 2:
            output = measRemMid(numberOfElements);
            text += "w srodku\n";
            break;
        case 3:
            output = measRemEnd(numberOfElements);
            text += "na koncu\n";
            break;
        default:
            throw 4;
    }
    text += "tablicy o rozmiarze ";
    text += std::to_string(numberOfElements);
    text += " elementow to ";
    text += std::to_string(output);
    text += ".\n";
    std::cout << text;
}

unsigned long long ArrayOperations::measRemBeg(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        array measurementsArray = generateArray(size);
        std::cout << "|";//todo
        StopWatch watch;
        watch.start();
        measurementsArray.removeFirst();
        watch.stop();
        average += watch.getLastMeasurmentPiccosec();
        if(!watch.getLastMeasurmentPiccosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    return average;
}

unsigned long long ArrayOperations::measRemMid(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        array measurementsArray = generateArray(size);
        std::cout << "|";//todo
        StopWatch watch;
        int position = size / 2;
        watch.start();
        measurementsArray.removeAt(position);
        watch.stop();
        average += watch.getLastMeasurmentPiccosec();
        if(!watch.getLastMeasurmentPiccosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    return average;
}

unsigned long long ArrayOperations::measRemEnd(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        array measurementsArray = generateArray(size);
        std::cout << "|";//todo
        StopWatch watch;
        watch.start();
        measurementsArray.removeLast();
        watch.stop();
        average += watch.getLastMeasurmentPiccosec();
        if(!watch.getLastMeasurmentPiccosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    return average;
}

