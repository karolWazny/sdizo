#include "gtest/gtest.h"
#include <array_lib/Array.h>

TEST(ArrayTestSuite, ContainsFalse){ // 12/0/2020 -> 0
    auto array = Array<int>();
    ASSERT_FALSE(array.contains(5));
    ASSERT_TRUE(array.isEmpty());
}

TEST(ArrayTestSuite, ContainsTrue){ // 12/0/2020 -> 0
    auto array = Array<int>();
    for(int i = 0; i < 5; i++)
    {
        ASSERT_EQ(array.getLength(), i);
        ASSERT_FALSE(array.contains(i));
        array.pushBack(i);
        ASSERT_TRUE(array.contains(i));
        ASSERT_FALSE(array.isEmpty());
        ASSERT_EQ(array.getLength(), i+1);
    }
    ASSERT_TRUE(array.contains(3));
}

TEST(ArrayTestSuite, PushFront){ // 12/0/2020 -> 0
    auto array = Array<int>();
    array.pushFront(5);
    ASSERT_TRUE(array.get(0) == 5);
    array.pushFront(4);
    ASSERT_EQ(array.get(1), 5);
    ASSERT_TRUE(array.get(0) == 4);
}

TEST(ArrayTestSuite, PushFrontLot){ // 12/0/2020 -> 0
    auto array = Array<int>();
    for(int i = 1; i < 150; i++)
    {
        array.pushFront(i);
        std::cout << array.toString() << std::endl;
        for(int k = 1; k <= i; k++)
        {
            ASSERT_TRUE(array.contains(k));
        }
        for(int k = i + 1; k < 150; k++)
        {
            ASSERT_FALSE(array.contains(k));
        }
    }
}

TEST(ArrayTestSuite, PushBack){ // 12/0/2020 -> 0
    auto array = Array<int>();
    array.pushBack(5);
    ASSERT_TRUE(array.get(0) == 5);
    array.pushBack(4);
    ASSERT_TRUE(array.get(0) == 5);
    ASSERT_TRUE(array.get(1) == 4);
}

TEST(ArrayTestSuite, PushBackLot){ // 12/0/2020 -> 0
    auto array = Array<int>();
    for(int i = 1; i < 150; i++)
    {
        //std::cout << array.toString() << std::endl;
        array.pushBack(i);
        for(int k = 1; k <= i; k++)
        {
            ASSERT_TRUE(array.contains(k));
        }
        for(int k = i + 1; k < 150; k++)
        {
            ASSERT_FALSE(array.contains(k));
        }
    }
}


TEST(ArrayTestSuite, RemoveMiddle){
    auto array = Array<int>();
    for(int i = 0; i < 100; i++)
    {
        array.pushBack(i);
    }
    array.removeAt(50);
    for(int i = 0; i < 50; i++)
    {
        ASSERT_TRUE(array.contains(i));
    }
    ASSERT_FALSE(array.contains(50));
    for(int i = 51; i < 100; i++)
    {
        ASSERT_TRUE(array.contains(i));
    }
}

TEST(ArrayTestSuite, RemoveFirst){
    auto array = Array<int>();
    for(int i = 0; i < 5; i++)
    {
        array.pushBack(i);
    }
    ASSERT_TRUE(array.removeFirst() == 0);
    ASSERT_TRUE(array.getLength() == 4);
    ASSERT_TRUE(array.get(0) == 1);
}

TEST(ArrayTestSuite, RemoveLast){
    auto array = Array<int>();
    for(int i = 0; i < 5; i++)
    {
        array.pushBack(i);
    }
    ASSERT_TRUE(array.removeLast() == 4);
    ASSERT_TRUE(array.getLength() == 4);
    ASSERT_TRUE(array.removeLast() == 3);
}

TEST(ArrayTestSuite, IsEmptyTrue){
    auto array = Array<int>();
    ASSERT_TRUE(array.isEmpty());
}

TEST(ArrayTestSuite, IsEmptyFalse){
    auto array = Array<int>();
    for(int i = 0; i < 5; i++)
    {
        array.pushBack(i);
    }
    ASSERT_FALSE(array.isEmpty());
}

TEST(ArrayTestSuite, SwapNeighbours){
    auto array = Array<int>();
    for(int i = 0; i < 5; i++)
    {
        array.pushBack(i);
    }
    array.swap(2,3);
    ASSERT_TRUE(array.get(2) == 3);
    ASSERT_TRUE(array.get(3) == 2);
}

TEST(ArrayTestSuite, SwapWithTheFirst){
    auto array = Array<int>();
    for(int i = 0; i < 5; i++)
    {
        array.pushBack(i);
    }
    array.swap(0,3);
    ASSERT_TRUE(array.get(0) == 3);
    ASSERT_TRUE(array.get(3) == 0);
}

TEST(ArrayTestSuite, SwapWithTheLast){
    auto array = Array<int>();
    for(int i = 0; i < 5; i++)
    {
        array.pushBack(i);
    }
    array.swap(1,4);
    ASSERT_EQ(array.get(1), 4);
    ASSERT_EQ(array.removeLast(), 1);
}

TEST(ArrayTestSuite, RemoveFirstLot){
    auto array = Array<int>();
    for(int i = 0; i < 150; i++)
    {
        array.pushBack(i);
        for(int k = 0; k <= i; k++)
        {
            ASSERT_TRUE(array.contains(k));
        }
        for(int k = i + 1; k < 150; k++)
        {
            ASSERT_FALSE(array.contains(k));
        }
    }
    while(!array.isEmpty())
    {
        array.removeFirst();
    }
}

TEST(ArrayTestSuite, RemoveLastLot){
    auto array = Array<int>();
    for(int i = 0; i < 150; i++)
    {
        array.pushBack(i);
        for(int k = 0; k <= i; k++)
        {
            ASSERT_TRUE(array.contains(k));
        }
        for(int k = i + 1; k < 150; k++)
        {
            ASSERT_FALSE(array.contains(k));
        }
    }
    while(!array.isEmpty())
    {
        array.removeLast();
    }
}

TEST(ArrayTestSuite, PutAfterLength){
    auto array = Array<int>();
    for(int i = 0; i < 150; i++)
    {
        array.pushBack(i);
        for(int k = 0; k <= i; k++)
        {
            ASSERT_TRUE(array.contains(k));
        }
        for(int k = i + 1; k < 150; k++)
        {
            ASSERT_FALSE(array.contains(k));
        }
    }
    ASSERT_EQ(array.getLength(), 150);
    array.putAtPosition(10, 40);
    ASSERT_EQ(array.getLength(), 151);
}

