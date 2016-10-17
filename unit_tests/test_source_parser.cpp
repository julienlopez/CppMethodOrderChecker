#include <gtest/gtest.h>

#include "sourceparser.hpp"

TEST(TestSourceParser, SimpleCase)
{
    Utils::StringList_t lines{"#include \"a.hpp\"",  "A::A()", "{", "}", "A::A(const B& b)", "{", "}",
                              "void A::run() const", "{",      "}"};
    SourceParser p("A", lines);
    const auto res = p.run();
    Utils::StringList_t expected_methods{"A()", "A(const B& b)", "void run() const"};
    EXPECT_EQ(expected_methods, res);
}

TEST(TestSourceParser, ConstructorWithInitializationList)
{
    Utils::StringList_t lines{"#include \"a.hpp\"",
                              "A::A() : B()",
                              "{",
                              "}",
                              "A::A(const B& b):B(b)",
                              "{",
                              "}",
                              "void A::run() const",
                              "{",
                              "}"};
    SourceParser p("A", lines);
    const auto res = p.run();
    Utils::StringList_t expected_methods{"A()", "A(const B& b)", "void run() const"};
    EXPECT_EQ(expected_methods, res);
}

TEST(TestSourceParser, CaseWithNamespaceInMethodArgument)
{
    Utils::StringList_t lines{
        "#include \"a.hpp\"", "A::A()", "{", "}", "void A::run(const std::string& str) const", "{", "}"};
    SourceParser p("A", lines);
    const auto res = p.run();
    Utils::StringList_t expected_methods{"A()", "void run(const std::string& str) const"};
    EXPECT_EQ(expected_methods, res);
}

TEST(TestSourceParser, DefaultConstructor)
{
    Utils::StringList_t lines{"#include \"a.hpp\"", "A::A() = default;", "void A::run(const std::string& str) const",
                              "{", "}"};
    SourceParser p("A", lines);
    const auto res = p.run();
    Utils::StringList_t expected_methods{"A()", "void run(const std::string& str) const"};
    EXPECT_EQ(expected_methods, res);
}
