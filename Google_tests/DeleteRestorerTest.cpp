#include "gtest/gtest.h"
#include <trees_lib/nodes/RBFactory.h>
#include <trees_lib/rbutil/DeletePropertyRestorer.h>

TEST(DeleteRestorerSuite, Compilation){
    auto restorer = DeletePropertyRestorer<int>();
}

TEST(DeleteRestorerSuite, SuccessorWasRed){
    auto restorer = DeletePropertyRestorer<int>();
}