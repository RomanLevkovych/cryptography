#ifndef TST_EXAMPLECASE_H
#define TST_EXAMPLECASE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(Example, ExampleCase)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

#endif // TST_EXAMPLECASE_H
