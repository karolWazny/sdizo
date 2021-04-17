#ifndef SDIZO_1_AVLPUTRESTORER_H
#define SDIZO_1_AVLPUTRESTORER_H

#include "trees_lib/node_util/NodeUtility.h"
#include "trees_lib/nodes/AVLNode.h"
#include "trees_lib/node_util/NodeRotator.h"

template <typename T>
class AVLPutRestorer : public NodeUtility<T>
{
public:
    void restoreFrom(AVLNodePtr<T> freshNode);
private:
    Side currentSide;
    AVLNodePtr<T> currentParent;
    AVLNodePtr<T> currentGrand;
};

template<typename T>
void AVLPutRestorer<T>::restoreFrom(AVLNodePtr<T> freshNode) {
    if(freshNode->getParent()->isNil())
    {
        currentNode = freshNode;
        return;
    }
    currentParent = avlcast(freshNode->getParent());

    //jeżeli ojciec dodanego węzła był niezrównoważony o jeden, to teraz
    //na pewno jest zrównoważony
    if(currentParent->getBalanceFactor())
    {
        currentParent->setBalanceFactor(0);
        return;
    }
    //pozyskanie wiedzy, z której strony
    if(currentParent->getRight() == freshNode)
        currentSide = Side::RIGHT;
    else
        currentSide = Side::LEFT;

}

#endif //SDIZO_1_AVLPUTRESTORER_H
