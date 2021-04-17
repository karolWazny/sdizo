//
// Created by admin on 04.03.2021.
//

#ifndef SDIZO_1_LINKEDLISTITERATOR_H
#define SDIZO_1_LINKEDLISTITERATOR_H

#include <memory>
#include "LinkedList.h"
#include "Iterator.h"

/*template <typename T>
class LinkedListIterator : public Iterator<T>
{
    T current();
    T remove();
    T next();
    T previous();
    bool hasNext();
    bool hasPrevious();
    LinkedListIterator<T> clone();
private:
    LinkedListIterator(int&);
    std::shared_ptr<INextable<T>>  currentItem;
    int& size;
};

template<typename T>
LinkedListIterator<T>::LinkedListIterator(std::shared_ptr<INextable<T>> currentItem, int & size) {
    this->size = size;
    this->currentItem = currentItem;
}

template<typename T>
T LinkedListIterator<T>::current() {
    return currentItem->getContent();
}

template<typename T>
T LinkedListIterator<T>::remove() {
    size--;
    currentItem->remove();
    return nullptr;
}*/

#endif //SDIZO_1_LINKEDLISTITERATOR_H
