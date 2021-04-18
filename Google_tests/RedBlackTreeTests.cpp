#include "gtest/gtest.h"
#include <trees_lib/RedBlackTree.h>
#include <iostream>

TEST(RedBlackTestSuite, Compilation){
    auto tree = RedBlackTree<int>();
}

TEST(RedBlackTestSuite, PutContains){
    auto tree = RedBlackTree<int>();
    ASSERT_FALSE(tree.containsKey(4));
    tree.put(4);
    ASSERT_TRUE(tree.containsKey(4));
    ASSERT_FALSE(tree.containsKey(5));
    tree.put(5);
    ASSERT_TRUE(tree.containsKey(5));
    ASSERT_TRUE(tree.containsKey(4));
}

TEST(RedBlackTestSuite, RemoveRoot){
    auto tree = RedBlackTree<int>();
    tree.put(23);
    tree.put(50);
    tree.put(10);
    tree.put(60);
    tree.put(40);
    ASSERT_TRUE(tree.containsKey(23));
    ASSERT_TRUE(tree.containsKey(50));
    ASSERT_TRUE(tree.containsKey(10));
    ASSERT_TRUE(tree.containsKey(60));
    ASSERT_TRUE(tree.containsKey(40));
    tree.removeKey(23);
    ASSERT_FALSE(tree.containsKey(23));
    ASSERT_TRUE(tree.containsKey(50));
    ASSERT_TRUE(tree.containsKey(10));
    ASSERT_TRUE(tree.containsKey(60));
    ASSERT_TRUE(tree.containsKey(40));
}


TEST(RedBlackTestSuite, DeletingSmallest){
    auto tree = RedBlackTree<int>();
    for(int i = 0; i < 100; i++)
    {
        tree.put(i);
        for(int j = 0; j <= i; j++)
        {
            ASSERT_TRUE(tree.containsKey(j));
        }
    }
    for(int i = 0; i < 100; i++)
    {
        ASSERT_TRUE(tree.containsKey(i));
        if(i == 2)
            tree.removeKey(i);
        else
            tree.removeKey(i);
        for(int j = 0; j <= i; j++)
        {
            if(j == 99)
                ASSERT_FALSE(tree.containsKey(99));
            else
                ASSERT_FALSE(tree.containsKey(j));
        }
        for(int j = i + 1; j < 100; j++)
        {
            ASSERT_TRUE(tree.containsKey(j));
        }
    }
}

TEST(RedBlackTestSuite, DeletingSmallestSmallAmount){
    auto tree = RedBlackTree<int>();
    for(int i = 0; i < 10; i++)
    {
        tree.put(i);
        for(int j = 0; j <= i; j++)
        {
            ASSERT_TRUE(tree.containsKey(j));
        }
    }
    for(int i = 0; i < 10; i++)
    {
        //std::cout<<tree.toString()<<std::endl;
        ASSERT_TRUE(tree.containsKey(i));
        tree.removeKey(i);
        for(int j = 0; j <= i; j++)
        {
            ASSERT_FALSE(tree.containsKey(j));
        }
        for(int j = i + 1; j < 10; j++)
        {
            ASSERT_TRUE(tree.containsKey(j));
        }
    }
}

TEST(RedBlackTestSuite, DeletingReversedAdding){
    auto tree = RedBlackTree<int>();
    for(int i = 99; i >= 0; i--)
    {
        if(i == 94)
            tree.put(i);
        else
            tree.put(i);
        for(int j = 99; j >= i; j--)
        {
            ASSERT_TRUE(tree.containsKey(j));
        }
    }
    for(int i = 0; i < 100; i++)
    {
        ASSERT_TRUE(tree.containsKey(i));
        tree.removeKey(i);
        for(int j = 0; j <= i; j++)
        {
            if(j == 99)
                ASSERT_FALSE(tree.containsKey(99));
            else
                ASSERT_FALSE(tree.containsKey(j));
        }
        for(int j = i + 1; j < 100; j++)
        {
            ASSERT_TRUE(tree.containsKey(j));
        }
    }
}
TEST(RedBlackTestSuite, DeletingGreatest){
    auto tree = RedBlackTree<int>();
    for(int i = 99; i >= 0; i--)
    {
        tree.put(i);
        for(int j = 99; j >= i; j--)
        {
            ASSERT_TRUE(tree.containsKey(j));
        }
    }
    for(int i = 99; i >= 0; i--)
    {
        ASSERT_TRUE(tree.containsKey(i));
        tree.removeKey(i);
        for(int j = 99; j >= i; j--)
        {
            ASSERT_FALSE(tree.containsKey(j));
        }
        for(int j = i -1; j >=0; j--)
        {
            ASSERT_TRUE(tree.containsKey(j));
        }
    }
}

TEST(RedBlackTestSuite, AddingGreatestDeletingSmallest){
    auto tree = RedBlackTree<int>();
    for(int i = 99; i >= 0; i--)
    {
        tree.put(i);
        for(int j = 99; j >= i; j--)
        {
            ASSERT_TRUE(tree.containsKey(j));
        }
    }
    for(int i = 0; i < 100; i++)
    {
        ASSERT_TRUE(tree.containsKey(i));
        tree.removeKey(i);
        for(int j = 0; j <= i; j++)
        {
            ASSERT_FALSE(tree.containsKey(j));
        }
        for(int j = i + 1; j < 100; j++)
        {
            ASSERT_TRUE(tree.containsKey(j));
        }
    }
}

TEST(RedBlackTestSuite, NonUniqueKeys){
    auto tree = RedBlackTree<int>();
    for(int i = 99; i >= 0; i--)
    {
        for(int k = 0; k < 5; k++)
        {
            if(i == 98 && k == 1)
            {
                tree.put(i);
            }
            else
                tree.put(i);
        }
    }
    for(int i = 0; i < 100; i++)
    {
        ASSERT_TRUE(tree.containsKey(i));
        if(i == 0)
        {
            tree.removeKey(i);
        }
        else
            tree.removeKey(i);
        ASSERT_TRUE(tree.containsKey(i));
    }
    for(int i = 0; i < 100; i++)
    {
        ASSERT_TRUE(tree.containsKey(i));
        tree.removeKey(i);
        for(int j = i + 1; j < 100; j++)
        {
            ASSERT_TRUE(tree.containsKey(j));
        }
    }
}

TEST(RedBlackTestSuite, NonUniqueKeysSmall){
    auto tree = RedBlackTree<int>();
    tree.put(5);
    tree.put(5);
    tree.put(7);
    tree.put(7);
    tree.put(6);
    tree.put(4);
    tree.put(4);
}