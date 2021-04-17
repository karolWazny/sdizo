#include "gtest/gtest.h"
#include <trees_lib/nodes/SimpleFactory.h>
#include <trees_lib/node_util/NodePutter.h>

TEST(KeyFinderSuite, PutOnTheRight){
    auto node = SimpleFactory<int>::makeNode(2);
    auto putter = NodePutter<int>(node);
    putter.put(5);
    ASSERT_FALSE(node->getRight()->isNil());
    ASSERT_TRUE(node->getLeft()->isNil());
    ASSERT_EQ(node->getRight()->getKey(), 5);
}

TEST(KeyFinderSuite, PutOnTheLeft){
    auto node = SimpleFactory<int>::makeNode(2);
    auto putter = NodePutter<int>(node);
    putter.put(1);
    ASSERT_FALSE(node->getLeft()->isNil());
    ASSERT_TRUE(node->getRight()->isNil());
    ASSERT_EQ(node->getLeft()->getKey(), 1);
}

TEST(KeyFinderSuite, PutIntoEmptyTree){
    auto node = SimpleFactory<int>::makeNode(2);
    node = node->getLeft();
    auto putter = NodePutter<int>(node);
    putter.put(1);
    node = putter.obtainRoot();
    ASSERT_FALSE(node->isNil());
    ASSERT_TRUE(node->getLeft()->isNil());
    ASSERT_TRUE(node->getRight()->isNil());
    ASSERT_EQ(node->getKey(), 1);
}
