#include "gtest/gtest.h"
#include <trees_lib/nodes/SimpleFactory.h>
#include <trees_lib/node_util/KeyFinder.h>
#include <trees_lib/node_util/PlaceToPutFinder.h>
#include <trees_lib/node_util/ConsequentFinder.h>

TEST(KeyFinderSuite, KeyFoundInInitialNode){
    auto node = SimpleFactory<int>::makeNode(2);
    auto finder = KeyFinder<int>(node);
    finder.setDesiredKey(2);
    ASSERT_FALSE(finder.nodeFound());
    finder.find();
    ASSERT_TRUE(finder.nodeFound());
    ASSERT_EQ(finder.getFound(), node);
}

TEST(KeyFinderSuite, KeyNotFoundInSingleNode){
    auto node = SimpleFactory<int>::makeNode(2);
    auto finder = KeyFinder<int>(node);
    finder.setDesiredKey(3);
    ASSERT_FALSE(finder.nodeFound());
    finder.find();
    ASSERT_FALSE(finder.nodeFound());
}

TEST(KeyFinderSuite, KeyFoundInLeftNode){
    auto parent = SimpleFactory<int>::makeNode(5);
    auto left = SimpleFactory<int>::makeNode(2);
    auto right = SimpleFactory<int>::makeNode(8);
    parent->setLeft(left);
    parent->setRight(right);
    auto finder = KeyFinder<int>(parent);
    finder.setDesiredKey(2);
    ASSERT_FALSE(finder.nodeFound());
    finder.find();
    ASSERT_TRUE(finder.nodeFound());
    ASSERT_EQ(finder.getFound(), left);
}

TEST(KeyFinderSuite, KeyFoundInRightNode){
    auto parent = SimpleFactory<int>::makeNode(5);
    auto left = SimpleFactory<int>::makeNode(2);
    auto right = SimpleFactory<int>::makeNode(8);
    parent->setLeft(left);
    parent->setRight(right);
    auto finder = KeyFinder<int>(parent);
    finder.setDesiredKey(8);
    ASSERT_FALSE(finder.nodeFound());
    finder.find();
    ASSERT_TRUE(finder.nodeFound());
    ASSERT_EQ(finder.getFound(), right);
}

TEST(PlaceFinderSuite, Compilation){
    auto parent = SimpleFactory<int>::makeNode(5);
    auto finder = PlaceToPutFinder<int>(parent);
    finder.setKeyToBePut(4);
    finder.find();
    finder.nodeFound();
    finder.getFound();
}

TEST(PlaceFinderSuite, FindRightSide){
    auto parent = SimpleFactory<int>::makeNode(5);
    auto left = SimpleFactory<int>::makeNode(2);
    auto right = SimpleFactory<int>::makeNode(8);
    parent->setLeft(left);
    parent->setRight(right);
    auto finder = PlaceToPutFinder<int>(parent);
    finder.setKeyToBePut(4);
    ASSERT_FALSE(finder.nodeFound());
    finder.find();
    ASSERT_TRUE(finder.nodeFound());
    ASSERT_EQ(finder.getFound(), left);
    ASSERT_EQ(finder.getPlaceSide(), Side::RIGHT);
}

TEST(PlaceFinderSuite, FindLeftSide){
    auto parent = SimpleFactory<int>::makeNode(5);
    auto left = SimpleFactory<int>::makeNode(2);
    auto right = SimpleFactory<int>::makeNode(8);
    parent->setLeft(left);
    parent->setRight(right);
    auto finder = PlaceToPutFinder<int>(parent);
    finder.setKeyToBePut(1);
    ASSERT_FALSE(finder.nodeFound());
    finder.find();
    ASSERT_TRUE(finder.nodeFound());
    ASSERT_EQ(finder.getFound(), left);
    ASSERT_EQ(finder.getPlaceSide(), Side::LEFT);
}

TEST(PlaceFinderSuite, FindNoConsequent){
    auto parent = SimpleFactory<int>::makeNode(20);
    auto finder = ConsequentFinder<int>(parent);
    finder.find();
    ASSERT_TRUE(finder.getFound()->isNil());
}

TEST(PlaceFinderSuite, FindRightConsequent){
    auto parent = SimpleFactory<int>::makeNode(20);
    auto node2 = SimpleFactory<int>::makeNode(21);
    auto node3 = SimpleFactory<int>::makeNode(19);
    auto node4 = SimpleFactory<int>::makeNode(18);
    parent->setRight(node2);
    node2->setLeft(node3);
    node3->setLeft(node4);
    auto finder = ConsequentFinder<int>(parent);
    finder.find();
    ASSERT_EQ(finder.getFound(), node4);
}

TEST(PlaceFinderSuite, FindLeftConsequent){
    auto parent = SimpleFactory<int>::makeNode(20);
    auto node2 = SimpleFactory<int>::makeNode(21);
    auto node3 = SimpleFactory<int>::makeNode(19);
    auto node4 = SimpleFactory<int>::makeNode(18);
    parent->setLeft(node2);
    node2->setRight(node3);
    node3->setRight(node4);
    auto finder = ConsequentFinder<int>(parent);
    finder.find();
    ASSERT_EQ(finder.getFound(), node4);
}