#include "gtest/gtest.h"
#include <trees_lib/nodes/RBFactory.h>

TEST(RBNodeSuite, Compilation){
    auto node = RBFactory<int>().createNode(2);
}

TEST(RBNodesuite, GetKey){
    auto node = RBFactory<int>().createNode(2);
    ASSERT_EQ(node->getKey(), 2);
}

TEST(RBNodesuite, GetLeftEmpty){
    auto node = RBFactory<int>().createNode(2);
    auto child = node->getLeft();
    ASSERT_TRUE(child->isNil());
    ASSERT_TRUE((std::dynamic_pointer_cast<RBNode<int>>(child))->isBlack());
}

TEST(RBNodesuite, GetRightEmpty){
    auto node = RBFactory<int>().createNode(2);
    auto child = node->getRight();
    ASSERT_TRUE(child->isNil());
    ASSERT_TRUE((std::dynamic_pointer_cast<RBNode<int>>(child))->isBlack());
}

TEST(RBNodesuite, GetParentEmpty){
    auto node = RBFactory<int>().createNode(2);
    auto parent = node->getParent();
    ASSERT_TRUE(parent->isNil());
    ASSERT_TRUE((std::dynamic_pointer_cast<RBNode<int>>(parent))->isBlack());
}
