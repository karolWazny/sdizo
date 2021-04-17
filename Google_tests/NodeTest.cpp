#include "gtest/gtest.h"
#include <trees_lib/nodes/SimpleFactory.h>

TEST(NodeSuite, Compilation){
    auto node = NodeImpl<int>(2);
}

TEST(Nodesuite, GetKey){
    auto node = NodeImpl<int>(2);
    ASSERT_EQ(node.getKey(), 2);
}

TEST(Nodesuite, GetLeftEmpty){
    auto node = NodeImpl<int>(2);
    auto child = node.getLeft();
    ASSERT_TRUE(child->isNil());
}