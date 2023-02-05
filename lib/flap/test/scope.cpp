#include "dt/scope.hpp"

#include <gtest/gtest.h>

template <class K, class V>
using Scope = flap::dt::Scope<K, V>;
using namespace std::literals::string_view_literals;

TEST(Scope, Ctor) {
    Scope<int, int> parent{};
    Scope child{&parent};
}

TEST(Add, Single) {
    Scope<int, int> s{};
    ASSERT_FALSE(s.contains(1));
    s.add(1) = 100;
    ASSERT_TRUE(s.contains(1));
    ASSERT_EQ(s.at(1), 100);
    ASSERT_ANY_THROW(s.at(2));
}
TEST(Add, Convert) {
    Scope<std::string, int> s{};
    s.add("foobar") = 0;
    s.add("baz"sv) = 1;
}

TEST(Contains, Parent) {
    Scope<int, int> parent{};
    parent.add(1) = 2;
    parent.add(2) = 3;

    Scope child{&parent};

    ASSERT_TRUE(child.contains(1));
    ASSERT_TRUE(child.contains(2));
    ASSERT_FALSE(child.contains(3));
}

TEST(Contains, Convert) {
    Scope<std::string, std::string> s{};
    s.add("foo") = "bar";
    s.add("bar") = "baz";

    ASSERT_TRUE(s.contains("foo"sv));
    ASSERT_TRUE(s.contains("bar"));
    ASSERT_FALSE(s.contains("baz"sv));
}

TEST(At, Simple) {
    Scope<int, int> s{};
    s.add(1) = 2;
    ASSERT_EQ(s.at(1), 2);
}

TEST(At, Conflict) {
    Scope<int, int> parent{};
    parent.add(1) = 2;
    Scope child{&parent};
    child.add(1) = 3;
    ASSERT_EQ(parent.at(1), 2);
    ASSERT_EQ(child.at(1), 3);
}
