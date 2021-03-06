#include "RBTreeOperations.h"
#include "TextFileReader.h"
#include "StopWatch.h"

void RBTreeOperations::run() {
    active = true;
    while(active)
    {
        menu();
        interpretInput();
    }
}

void RBTreeOperations::menu() {
    displayMenu("OPERACJE NA DRZEWIE CZERWONO CZARNYM");
}

void RBTreeOperations::interpretInput() {
    int option;
    try{
        option = readInt();
        switch(option){
            case 1:
                fromFile();
                break;
            case 2:
                tree = rbtree();
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

void RBTreeOperations::addElement() {
    std::string text = "Podaj wartosc, ktora chcesz umiescic:\n";
    std::cout << text;
    std::getline(std::cin, input);
    int value = std::stoi(input);
    tree.put(value);
    text = "Dodano element ";
    text += std::to_string(value);
    text += ".\n";

    std::cout << text;
}

void RBTreeOperations::removeElement() {
    if(tree.isEmpty())
    {
        std::cout << "Nie mozna usunac klucza z pustego drzewa.\n"
                     "Operacje anulowano.\n";
        return;
    }
    std::string text = "Podaj wartosc klucza, ktory chcesz usunac:\n";
    std::cout << text;
    std::getline(std::cin, input);
    int keyToRemove;
    keyToRemove = std::stoi(input);
    if(!tree.contains(keyToRemove)){
        std::cout << "Drzewo nie zawiera klucza o wartosci "
            << std::to_string(keyToRemove) << ".\n"
            << "Operacje anulowano.\n";
        return;
    }
    tree.remove(keyToRemove);
    std::cout << "Usunieto klucz o wartosci "
        << std::to_string(keyToRemove)
        << ".\n";
}

void RBTreeOperations::findElement() {
    std::string text = "Podaj element, ktory chcesz wyszukac:\n";
    std::cout << text;
    std::getline(std::cin, input);
    int value;
    value = std::stoi(input);
    bool contains = tree.contains(value);
    if(contains)
    {
        text = "Drzewo zawiera element o wartosci ";
    } else {
        text = "Drzewo nie zawiera elementu o wartosci ";
    }
    text += std::to_string(value);
    text += ".\n";
    std::cout << text;
}

void RBTreeOperations::display() {
#if DEBUG
#else
    std::cout << tree.getRepresentation() << std::endl;
#endif
}

void RBTreeOperations::fromFile() {
    std::string text = "Wprowadz nazwe, sciezke wzgledem aktualnego folderu,\n"
                       "lub pelna sciezke do pliku:\n";
    std::cout << text;
    std::string filename;
    std::getline(std::cin, filename);
    try {
        TextFileReader reader;
        auto content = reader.fromFile(filename);
        tree = rbtree();
        for(int i = 1; i <= content[0]; i++)
        {
            tree.put(content[i]);
        }
    } catch(...) {
        std::cout << "Wystapil problem.\n"
                     "Operacje anulowano.\n";
    }
}

void RBTreeOperations::measurements() {
    std::cout << "Dla jakiej operacji chcesz mierzyc czas?\n"
                 "1. Dla dodawania elementu.\n"
                 "2. Dla usuwania elementu.\n"
                 "3. Dla wyszukiwania elementu.\n";
    int option = readInt();
    std::cout << "Dla jakiej wielkosci struktury chcesz mierzyc czas?\n";
#if DEBUG
    int options[] = {2500, 5000, 12500, 25000, 50000};
    int numberOfElements = sizeChoiceMenu(options, 5);
#else
    int options[] = {1000, 2000, 5000, 10000, 20000};
    int numberOfElements = sizeChoiceMenu(options, 5);
#endif

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
    }
}

void RBTreeOperations::measPutTime(int numberOfElements) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        auto measurementStructure = generateTree(numberOfElements);
        std::cout << "|";//todo
        int32_t elementToPut = randomInt(numberOfElements/2);
        StopWatch watch;
        watch.start();
        measurementStructure->put(elementToPut);
        watch.stop();
        average += watch.getLastMeasurmentPiccosec();
        if(!watch.getLastMeasurmentPiccosec())
        {
            i--;
            continue;
        }
        delete measurementStructure;
    }
    average /= 128;
    std::cout << "Sredni czas dodania elementu dla drzewa CC o rozmiarze "
              << std::to_string(numberOfElements) << std::endl
              << " to " << std::to_string(average) << ".\n";
}

rbtree* RBTreeOperations::generateTree(int size) {
    auto measurementsStructure = new rbtree();
    for(int j = 0; j < size; j++)
    {
        measurementsStructure->put(randomInt(size/2));
    }
    return measurementsStructure;
}

void RBTreeOperations::measRemTime(int numberOfElements) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        auto measurementStructure = generateTree(numberOfElements);
        std::cout << "|";//todo
        int32_t elementToRemove = randomInt(numberOfElements / 2);
        StopWatch watch;
        watch.start();
        measurementStructure->remove(elementToRemove);
        watch.stop();
        average += watch.getLastMeasurmentPiccosec();
        if(!watch.getLastMeasurmentPiccosec())
        {
            i--;
            continue;
        }
        delete measurementStructure;
    }
    average /= 128;
    std::cout << "Sredni czas usuniecia elementu dla drzewa CC o rozmiarze "
              << std::to_string(numberOfElements) << std::endl
              << " to " << std::to_string(average) << ".\n";
}

void RBTreeOperations::measFindTime(int numberOfElements) {
    unsigned long long average = 0;
    for(int i = 0; i < 128; i++)
    {
        auto measurementStructure = generateTree(numberOfElements);
        std::cout << "|";//todo
        int32_t elementToFind = randomInt(numberOfElements);
        StopWatch watch;
        bool contains;
        watch.start();
        contains = measurementStructure->contains(elementToFind);
        watch.stop();
        if(contains)
            measurementStructure->put(0);
        average += watch.getLastMeasurmentPiccosec();
        if(!watch.getLastMeasurmentPiccosec())
        {
            i--;
            continue;
        }
        delete measurementStructure;
    }
    average /= 128;
    std::cout << "Sredni czas wyszukania elementu dla drzewa CC o rozmiarze "
              << std::to_string(numberOfElements) << std::endl
              << " to " << std::to_string(average) << ".\n";
}
