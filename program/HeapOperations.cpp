#include "HeapOperations.h"
#include "TextFileReader.h"
#include "StopWatch.h"

void HeapOperations::run() {
    active = true;
    while(active)
    {
        menu();
        interpretInput();
    }
}

void HeapOperations::menu() {
    displayMenu("OPERACJE NA KOPCU MAKSYMALNYM");
}

void HeapOperations::interpretInput() {
    int option;
    try{
        option = readInt();
        switch(option){
            case 1:
                fromFile();
                break;
            case 2:
                mHeap = heap();
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

void HeapOperations::addElement() {
    std::string text = "Podaj wartosc, ktora chcesz umiescic:\n";
    std::cout << text;
    int value = readInt();
    mHeap.add(value);

    text = "Dodano do kopca wartosc ";
    text += std::to_string(value);
    text += ".\n";
    std::cout << text;
}

void HeapOperations::display() {
    std::cout << mHeap.getRepresentation() << std::endl;
}

void HeapOperations::removeElement() {
    std::string text = "Podaj wartosc klucza, ktory chcesz usunac\n"
                       "(uzyj 'max', zeby usunac element z korzenia kopca):\n";
    std::cout << text;
    read();
    try{
        int keyToRemove;
        if(!mHeap.getSize())
            throw IndexOutOfBoundException();
        if(input == "max")
        {
            keyToRemove = mHeap.extractMax();
            text = "Usunieto pierwszy element o wartosci ";
        } else {
            keyToRemove = std::stoi(input);
            bool removed = mHeap.remove(keyToRemove);
            if(removed){
                text = "Usunieto element o wartosci ";
            } else {
                text = "Kopiec nie zawieral elementu o wartosci ";
            }
        }
        text += std::to_string(keyToRemove);
        text += ".\n";
    } catch (IndexOutOfBoundException& e) {
        text = "Niewlasciwy indeks!\n";
    }

    std::cout << text;
}

void HeapOperations::findElement() {
    std::string text = "Podaj element, ktory chcesz wyszukac:\n";
    std::cout << text;
    int value = readInt();
    bool contains = mHeap.contains(value);
    if(contains)
    {
        text = "Kopiec zawiera element o wartosci ";
    } else {
        text = "Kopiec nie zawiera elementu o wartosci ";
    }
    text += std::to_string(value);
    text += ".\n";
    std::cout << text;
}

void HeapOperations::fromFile() {
    std::string text = "Wprowadz nazwe, sciezke wzgledem aktualnego folderu,\n"
                       "lub pelna sciezke do pliku:\n";
    std::cout << text;
    try {
        TextFileReader reader;
        auto content = reader.fromFile(readStr());
        mHeap = heap();
        for(int i = 1; i <= content[0]; i++)
        {
            mHeap.add(content[i]);
        }
    } catch(...) {
        std::cout << "Wystapil problem.\n"
                     "Operacje anulowano.\n";
    }
}

void HeapOperations::measurements() {
    std::cout << "Co chcesz zmierzyc?\n"
                 "1. Czas dodawania elementu.\n"
                 "2. Czas usuwania elementu.\n"
                 "3. Czas wyszukania elementu.\n";
    auto option = readInt();
    switch(option)
    {
        case 1:
            measPutTime();
            break;
        case 2:
            measRemTime();
            break;
        case 3:
            measFindTime();
            break;
        default:
            throw 4;
            break;
    }
}

void HeapOperations::measPutTime() {
    std::cout << "Dla jakiego rozmiaru struktury chcesz mierzyc czas?\n";
    int options[] = {1000, 2000, 5000, 10000, 20000};
    int numberOfElements = sizeChoiceMenu(options, 5);
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        auto measurementStructure = generateHeap(numberOfElements);
        std::cout << "|";//todo
        int32_t elementToPut = randomInt(numberOfElements/2);
        StopWatch watch;
        watch.start();
        measurementStructure.add(elementToPut);
        watch.stop();
        average += watch.getLastMeasurmentPiccosec();
        if(!watch.getLastMeasurmentPiccosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    std::cout << "Sredni czas dodania elementu dla kopca o rozmiarze "
            << std::to_string(numberOfElements) << std::endl
            << " to " << std::to_string(average) << ".\n";
}

heap HeapOperations::generateHeap(int size) {
    auto measurementsHeap = heap();
    for(int j = 0; j < size; j++)
    {
        measurementsHeap.add(randomInt(size/2));
    }
    return measurementsHeap;
}

void HeapOperations::measFindTime() {
    std::cout << "Dla jakiego rozmiaru struktury chcesz mierzyc czas?\n";
    int options[] = {1000, 2000, 5000, 10000, 20000};
    int numberOfElements = sizeChoiceMenu(options, 5);
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        auto measurementStructure = generateHeap(numberOfElements);
        std::cout << "|";//todo
        int32_t elementToFind = randomInt(numberOfElements);
        StopWatch watch;
        //contains jest sztuczną zmienną zapobiegającą wycięciu
        //wyszukania przez kompilator przy optymalizacji kodu
        bool contains;
        watch.start();
        contains = measurementStructure.contains(elementToFind);
        watch.stop();
        //sztuczny warunek, żeby kompilator nie wyciął
        //pozornie niepotrzebnej zmiennej contains
        if(contains)
            measurementStructure.remove(10);
        average += watch.getLastMeasurmentPiccosec();
        if(!watch.getLastMeasurmentPiccosec())
        {
            i--;
            continue;
        }
    }
    average /= 128;
    std::cout << "Sredni czas wyszukania elementu dla kopca o rozmiarze "
              << std::to_string(numberOfElements) << std::endl
              << " to " << std::to_string(average) << ".\n";
}

void HeapOperations::measRemTime() {
    std::cout << "Dla jakiego rozmiaru struktury chcesz mierzyc czas?\n";
    int options[] = {1000, 2000, 5000, 10000, 20000};
    int numberOfElements = sizeChoiceMenu(options, 5);
    std::cout << "Skad chcesz usuwac element?\n"
                 "1. Z korzenia (extract_max).\n"
                 "2. Z dowolnego miejsca.\n";
    int option = readInt();
    unsigned long long output;
    std::string text = "Sredni czas usuwania elementu z ";
    switch(option)
    {
        case 1:
            text += "korzenia\n";
            output = measRemMax(numberOfElements);
            break;
        case 2:
            text += "dowolnego miejsca\n";
            output = measRemAv(numberOfElements);
            break;
        default:
            throw 4;
    }
    text += "kopca o romiarze ";
    text += std::to_string(numberOfElements);
    text += " elementow to ";
    text += std::to_string(output);
    text += ".\n";
    std::cout << text;
}

unsigned long long HeapOperations::measRemMax(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        auto measurementsHeap = generateHeap(size);
        std::cout << "|";//todo
        StopWatch watch;
        watch.start();
        measurementsHeap.extractMax();
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

unsigned long long HeapOperations::measRemAv(int size) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        auto measurementsHeap = generateHeap(size);
        std::cout << "|";//todo
        int32_t elementToRemove = randomInt(size / 2);
        StopWatch watch;
        watch.start();
        measurementsHeap.remove(elementToRemove);
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

