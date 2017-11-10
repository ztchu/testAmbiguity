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

