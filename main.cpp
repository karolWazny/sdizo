#include <iostream>
#include <red_black_tree_lib/RedBlackTree.h>
#include <linked_list_lib/LinkedList.h>

int main() {
    auto tree = RedBlackTree<int>();
    auto lista = LinkedList<int>();
    lista.pushBack(3);
    lista.pushBack(5);
    lista.pushFront(7);
    lista.remove(5);
    lista.remove(8);
    lista.get(1);
    lista.toString();
}
