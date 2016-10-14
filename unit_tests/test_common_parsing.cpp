#include <gtest/gtest.h>

#include "commonparsing.hpp"

TEST(TestFindClassName, ThrowsIfEmpty)
{
    ASSERT_THROW(CommonParsing::findClassName({}), std::runtime_error);
}

TEST(TestFindClassName, SimpleClassCase)
{
    Utils::StringList_t lines{"#pragma one", "class A", "{", "public:", "A() = default;", "};"};
    std::string class_name;
    ASSERT_NO_THROW(class_name = CommonParsing::findClassName(lines));
    ASSERT_EQ(class_name, "A");
}

TEST(TestFindClassName, SimpleClassCaseWithSpaces)
{
    Utils::StringList_t lines{"#pragma one", "  class A", "  {", "    public:", "    A() = default;", "  };"};
    std::string class_name;
    ASSERT_NO_THROW(class_name = CommonParsing::findClassName(lines));
    ASSERT_EQ(class_name, "A");
}

TEST(TestFindClassName, SimpleStructCase)
{
    Utils::StringList_t lines{"#pragma one", "struct A", "{", "A() = default;", "};"};
    std::string class_name;
    ASSERT_NO_THROW(class_name = CommonParsing::findClassName(lines));
    ASSERT_EQ(class_name, "A");
}

TEST(TestFindClassName, SimpleCaseWithHeritage)
{
    Utils::StringList_t lines{
        "#pragma one", "#include \"b.hpp\"", "class A : public B", "{", "public:", "A() = default;", "};"};
    std::string class_name;
    ASSERT_NO_THROW(class_name = CommonParsing::findClassName(lines));
    ASSERT_EQ(class_name, "A");
}

TEST(TestFindClassName, SimpleCaseWithMultipleHeritage)
{
    Utils::StringList_t lines{"#pragma one",
                              "#include \"b.hpp\"",
                              "#include \"c.hpp\"",
                              "class A : public B, C",
                              "{",
                              "public:",
                              "A() = default;",
                              "};"};
    std::string class_name;
    ASSERT_NO_THROW(class_name = CommonParsing::findClassName(lines));
    ASSERT_EQ(class_name, "A");
}

TEST(TestFindClassName, SimpleCaseWithPreDeclarations)
{
    Utils::StringList_t lines{"#pragma one",    "class B;", "class C;", "class A", "{", "public:",
                              "A() = default;", "private:", "B m_b;",   "C& m_b;", "};"};
    std::string class_name;
    ASSERT_NO_THROW(class_name = CommonParsing::findClassName(lines));
    ASSERT_EQ(class_name, "A");
}