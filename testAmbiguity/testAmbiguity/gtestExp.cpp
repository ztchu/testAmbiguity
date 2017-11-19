#include <gtest/gtest.h>


bool IsEvenNumber(int val)
{
    return !(val % 2);
}

TEST(IsEvenNumber, test)
{
    EXPECT_FALSE(IsEvenNumber(1));
    EXPECT_FALSE(IsEvenNumber(3));
    EXPECT_FALSE(IsEvenNumber(-1));
    EXPECT_FALSE(IsEvenNumber(-3));
}

class IsEvenNumberParameterized : public ::testing::TestWithParam<int>
{

};

TEST_P(IsEvenNumberParameterized, test)
{
    int val = GetParam();
    EXPECT_FALSE(IsEvenNumber(val));
}

INSTANTIATE_TEST_CASE_P(test, IsEvenNumberParameterized, 
    testing::Values(1, 3, -1, -3));

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

void RunAllGtest(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}