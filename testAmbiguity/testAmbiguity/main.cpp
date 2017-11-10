#include "testString.h"
#include "commonTools.h"
#include "Macro.h"
#include "infixToPostfix.h"
#include "Container.h"
#include "filePath.h"
#include "time.h"
#include "dump.h"
#include <gtest/gtest.h>

TEST(EqualTest, ExpectTest)
{
    EXPECT_EQ(3, 6);
    EXPECT_EQ(4, 4);
    EXPECT_EQ(3, 7);
}

TEST(EqualTest, assertTest)
{
    EXPECT_EQ(3, 3);
    ASSERT_EQ(3, 4);
    EXPECT_EQ(3, 6);
    EXPECT_EQ(4, 4);
}



int main(int argc, char *argv[])
{  
    //::testing::InitGoogleTest(&argc, argv);
    //RUN_ALL_TESTS();
    StaticMember mem1(1), mem2(2);
    mem1 = mem2;
    mem1 = StaticMember(2);
}