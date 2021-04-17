//
// Created by admin on 02.03.2021.
//

#ifndef SDIZO_1_ARRAY_H
#define SDIZO_1_ARRAY_H
#include <memory>
#include <string>
template <typename T>
class Array
{
public:
    Array<T>();
    Array<T>(int initialSize);
    void putAtPosition(T, const int);
    void swap(const int, const int);
    T removeAt(const int index);
    void pushBack(T);
    bool contains(T element);
    void pushFront(T);
    T removeLast();
    T removeFirst();
    T get(const int index);
    bool isEmpty();
    int getLength();
    std::string toString();
    T& operator[](int);
private:
    std::unique_ptr<T[]> elements;
    int length;
};

class IndexOutOfBoundException : public std::exception
{

};

template <typename T>
Array<T>::Array()
{
    length = 0;
    elements = std::make_unique<T[]>(length);
}

template<typename T>
void Array<T>::pushBack(T element)
{
    putAtPosition(element, length);
}

template <typename T>
T Array<T>::removeFirst()
{
    return removeAt(0);
}

template <typename T>
T Array<T>::removeLast()
{
    return removeAt(length - 1);
}

template <typename T>
void Array<T>::pushFront(T element)
{
    putAtPosition(element, 0);
}

template <typename T>
T Array<T>::get(const int index)
{
    return elements[index];
}

template <typename T>
T Array<T>::removeAt(const int index)
{
    auto buffer = elements[index];
    auto newArray = std::make_unique<T[]>(length - 1);
    for(int i = 0; i < index; i++)
    {
        newArray[i] = elements[i];
    }
    for(int i = index + 1; i < length; i++)
    {
        newArray[i-1] = elements[i];
    }
    elements = std::move(newArray);
    length--;
    return buffer;
}

template<typename T>
void Array<T>::swap(const int index1, const int index2)
{
    const auto buffer = elements[index1];
    elements[index1] = elements[index2];
    elements[index2] = buffer;
}

template<typename T>
void Array<T>::putAtPosition(T element, const int index)
{
    if(index > length)
    {
        throw IndexOutOfBoundException();
    }
    auto newArray = std::make_unique<T[]>(length + 1);
    for(int i = 0; i < index; i++)
    {
        newArray[i] = elements[i];
    }
    for(int i = index + 1; i < length; i++)
    {
        newArray[i+1] = elements[i];
    }
    newArray[index] = element;
    elements = std::move(newArray);
    length++;
}

template <typename T>
bool Array<T>::isEmpty()
{
    return !length;
}

template <typename T>
int Array<T>::getLength()
{
    return length;
}

template <typename T>
std::string Array<T>::toString()
{
    std::string output = "[";
    if(length)
    {
        output += std::to_string(elements[0]);
    }
    for(int i = 1; i < length; i++)
    {
        output += ", " + std::to_string(elements[i]);
    }
    output += "]";
    return output;
}

template<typename T>
bool Array<T>::contains(T element) {
    for(int i = 0; i < length; i++)
    {
        if(element == elements[i])
        {
            return true;
        }
    }
    return false;
}

template<typename T>
Array<T>::Array(int initialSize) {
    length = initialSize;
    elements = std::make_unique<T[]>(initialSize);
}

template<typename T>
T &Array<T>::operator[](int index) {
    return elements[index];
}

#endif //SDIZO_1_ARRAY_H
