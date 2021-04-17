#include "gtest/gtest.h"
#include <trees_lib/node_util/ConsequentLiberator.h>
#include <trees_lib/nodes/SimpleFactory.h>

TEST(LiberatorSuite, Compilation){
    auto replacer = ConsequentLiberator<int>(SimpleFactory<int>::makeNode(0));
}

TEST(LiberatorSuite, LiberateLeftConsequent){
    auto root = SimpleFactory<int>::makeNode(5);
    auto consequent = SimpleFactory<int>::makeNode(3);
    auto consequentChild = SimpleFactory<int>::makeNode(2);
    auto right = SimpleFactory<int>::makeNode(6);
    root->setLeft(consequent);
    consequent->setParent(root);
    root->setRight(right);
    right->setParent(root);
    consequent->setRight(consequentChild);
    consequentChild->setParent(consequent);
    auto liberator = ConsequentLiberator<int>(root);
    liberator.free(consequent);
    root = liberator.obtainRoot();

    ASSERT_EQ(root->getLeft(), consequentChild);
    ASSERT_EQ(root->getRight(), right);
    ASSERT_EQ(root, consequentChild->getParent());
    ASSERT_EQ(root, right->getParent());
}


TEST(LiberatorSuite, LiberateLeftChildless){
    auto root = SimpleFactory<int>::makeNode(5);
    auto consequent = SimpleFactory<int>::makeNode(3);
    root->setLeft(consequent);
    consequent->setParent(root);
    auto liberator = ConsequentLiberator<int>(root);
    liberator.free(consequent);
    root = liberator.obtainRoot();

    ASSERT_TRUE(root->getLeft()->isNil());
}