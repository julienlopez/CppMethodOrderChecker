#include <gtest/gtest.h>

#include "utils.hpp"

TEST(TestUtilsEndsWith, WorkingTrue)
{
    ASSERT_TRUE(Utils::endsWith("abcde", "cde"));
}

TEST(TestUtilsEndsWith, WorkingFalse)
{
    ASSERT_FALSE(Utils::endsWith("abcde", "dea"));
}

TEST(TestUtilsEndsWith, TokenSmallerThanString)
{
    ASSERT_FALSE(Utils::endsWith("ab", "abcde"));
}

TEST(TestUtilsStartsWith, WorkingTrue)
{
    ASSERT_TRUE(Utils::startsWith("abcde", "abc"));
}

TEST(TestUtilsStartsWith, WorkingFalse)
{
    ASSERT_FALSE(Utils::startsWith("abcde", "dab"));
}

TEST(TestUtilsStartsWith, TokenSmallerThanString)
{
    ASSERT_FALSE(Utils::startsWith("ab", "abcde"));
}