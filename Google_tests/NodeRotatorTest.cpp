#include "gtest/gtest.h"
#include <trees_lib/node_util/NodeRotator.h>
#include <trees_lib/nodes/SimpleFactory.h>

TEST(NodeRotatorSuite, Compilation){
    auto node = SimpleFactory<int>().createNode(2);
    auto rotator = NodeRotator<int>();
}

TEST(NodeRotatorSuite, RotationRightNoParentNoAdditionalChilds){
    auto nodeToRotate = SimpleFactory<int>().createNode(2);
    auto child = SimpleFactory<int>().createNode(3);
    nodeToRotate->setLeft(child);
    child->setParent(nodeToRotate);
    auto rotator = NodeRotator<int>();
    rotator.rotateRight(nodeToRotate);
    ASSERT_TRUE(nodeToRotate->getLeft()->isNil());
    ASSERT_TRUE(nodeToRotate->getRight()->isNil());
    ASSERT_TRUE(child->getLeft()->isNil());
    ASSERT_TRUE(child->getParent()->isNil());
    ASSERT_EQ(nodeToRotate, child->getRight());
    ASSERT_EQ(nodeToRotate->getParent(), child);
    auto root = rotator.obtainRoot();
    ASSERT_EQ(root, child);
}

TEST(NodeRotatorSuite, RotationLeftNoParentNoAdditionalChilds){
    auto nodeToRotate = SimpleFactory<int>().createNode(2);
    auto child = SimpleFactory<int>().createNode(1);
    nodeToRotate->setRight(child);
    child->setParent(nodeToRotate);
    auto rotator = NodeRotator<int>();
    rotator.rotateLeft(nodeToRotate);
    ASSERT_TRUE(nodeToRotate->getRight()->isNil());
    ASSERT_TRUE(nodeToRotate->getLeft()->isNil());
    ASSERT_TRUE(child->getRight()->isNil());
    ASSERT_TRUE(child->getParent()->isNil());
    ASSERT_EQ(nodeToRotate, child->getLeft());
    ASSERT_EQ(nodeToRotate->getParent(), child);
    auto root = rotator.obtainRoot();
    ASSERT_EQ(root, child);
}

TEST(NodeRotatorSuite, RotationRightLeftChildNoAdditionalChilds){
    auto parent = SimpleFactory<int>().createNode(5);
    auto nodeToRotate = SimpleFactory<int>().createNode(2);
    auto child = SimpleFactory<int>().createNode(3);
    nodeToRotate->setLeft(child);
    child->setParent(nodeToRotate);
    parent->setLeft(nodeToRotate);
    nodeToRotate->setParent(parent);
    auto rotator = NodeRotator<int>();
    rotator.rotateRight(nodeToRotate);
    ASSERT_TRUE(nodeToRotate->getLeft()->isNil());
    ASSERT_TRUE(nodeToRotate->getRight()->isNil());
    ASSERT_TRUE(child->getLeft()->isNil());
    ASSERT_EQ(child->getParent(), parent);
    ASSERT_EQ(child, parent->getLeft());
    ASSERT_EQ(nodeToRotate, child->getRight());
    ASSERT_EQ(nodeToRotate->getParent(), child);
    auto root = rotator.obtainRoot();
    ASSERT_EQ(root, parent);
}

TEST(NodeRotatorSuite, RotationRightRightChildNoAdditionalChilds){
    auto parent = SimpleFactory<int>().createNode(0);
    auto nodeToRotate = SimpleFactory<int>().createNode(2);
    auto child = SimpleFactory<int>().createNode(3);
    nodeToRotate->setLeft(child);
    child->setParent(nodeToRotate);
    parent->setRight(nodeToRotate);
    nodeToRotate->setParent(parent);
    auto rotator = NodeRotator<int>();
    rotator.rotateRight(nodeToRotate);
    ASSERT_TRUE(nodeToRotate->getLeft()->isNil());
    ASSERT_TRUE(nodeToRotate->getRight()->isNil());
    ASSERT_TRUE(child->getLeft()->isNil());
    ASSERT_EQ(child->getParent(), parent);
    ASSERT_EQ(child, parent->getRight());
    ASSERT_EQ(nodeToRotate, child->getRight());
    ASSERT_EQ(nodeToRotate->getParent(), child);
    auto root = rotator.obtainRoot();
    ASSERT_EQ(root, parent);
}

TEST(NodeRotatorSuite, RotationLeftRightChildNoAdditionalChilds){
    auto parent = SimpleFactory<int>().createNode(0);
    auto nodeToRotate = SimpleFactory<int>().createNode(2);
    auto child = SimpleFactory<int>().createNode(3);
    nodeToRotate->setRight(child);
    child->setParent(nodeToRotate);
    parent->setRight(nodeToRotate);
    nodeToRotate->setParent(parent);
    auto rotator = NodeRotator<int>();
    rotator.rotateLeft(nodeToRotate);
    ASSERT_TRUE(nodeToRotate->getRight()->isNil());
    ASSERT_TRUE(nodeToRotate->getLeft()->isNil());
    ASSERT_TRUE(child->getRight()->isNil());
    ASSERT_EQ(child->getParent(), parent);
    ASSERT_EQ(child, parent->getRight());
    ASSERT_EQ(nodeToRotate, child->getLeft());
    ASSERT_EQ(nodeToRotate->getParent(), child);
    auto root = rotator.obtainRoot();
    ASSERT_EQ(root, parent);
}

TEST(NodeRotatorSuite, RotationRightNoParentAdditionalChilds){
    auto nodeToRotate = SimpleFactory<int>().createNode(2);
    auto child = SimpleFactory<int>().createNode(3);
    auto otherChild = SimpleFactory<int>().createNode(3);
    auto leftGrand = SimpleFactory<int>().createNode(3);
    auto rightGrand = SimpleFactory<int>().createNode(3);
    nodeToRotate->setLeft(child);
    child->setParent(nodeToRotate);
    auto rotator = NodeRotator<int>();

    otherChild->setParent(nodeToRotate);
    nodeToRotate->setRight(otherChild);

    leftGrand->setParent(child);
    rightGrand->setParent(child);

    child->setRight(rightGrand);
    child->setLeft(leftGrand);

    rotator.rotateRight(nodeToRotate);
    ASSERT_EQ(nodeToRotate->getRight(), otherChild);
    ASSERT_EQ(nodeToRotate, otherChild->getParent());

    ASSERT_EQ(nodeToRotate->getLeft(), rightGrand);
    ASSERT_EQ(nodeToRotate, rightGrand->getParent());

    ASSERT_EQ(child->getLeft(), leftGrand);
    ASSERT_EQ(child, leftGrand->getParent());

    ASSERT_TRUE(child->getParent()->isNil());

    ASSERT_EQ(nodeToRotate, child->getRight());
    ASSERT_EQ(nodeToRotate->getParent(), child);



    auto root = rotator.obtainRoot();
    ASSERT_EQ(root, child);
}

TEST(NodeRotatorSuite, RotationLeftNoParentAdditionalChilds){
    auto nodeToRotate = SimpleFactory<int>().createNode(2);
    auto child = SimpleFactory<int>().createNode(3);
    auto otherChild = SimpleFactory<int>().createNode(3);
    auto leftGrand = SimpleFactory<int>().createNode(3);
    auto rightGrand = SimpleFactory<int>().createNode(3);
    nodeToRotate->setRight(child);
    child->setParent(nodeToRotate);
    auto rotator = NodeRotator<int>();

    otherChild->setParent(nodeToRotate);
    nodeToRotate->setLeft(otherChild);

    leftGrand->setParent(child);
    rightGrand->setParent(child);

    child->setRight(rightGrand);
    child->setLeft(leftGrand);

    rotator.rotateLeft(nodeToRotate);
    ASSERT_EQ(nodeToRotate->getLeft(), otherChild);
    ASSERT_EQ(nodeToRotate, otherChild->getParent());

    ASSERT_EQ(nodeToRotate->getRight(), leftGrand);
    ASSERT_EQ(nodeToRotate, leftGrand->getParent());

    ASSERT_EQ(child->getRight(), rightGrand);
    ASSERT_EQ(child, rightGrand->getParent());

    ASSERT_TRUE(child->getParent()->isNil());

    ASSERT_EQ(nodeToRotate, child->getLeft());
    ASSERT_EQ(nodeToRotate->getParent(), child);



    auto root = rotator.obtainRoot();
    ASSERT_EQ(root, child);
}