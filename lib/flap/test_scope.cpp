#include <gtest/gtest.h>

#include <flap/types/scope.hpp>

using flap::make_scope;

TEST(Scope, Create) {
    auto parent = make_scope<int>();
    auto child = make_scope(parent);
}

TEST(Scope, Access) {
    auto scope = make_scope<int>();
    scope->insert("foo", 100);
    ASSERT_EQ(scope->at("foo"), 100);
    ASSERT_ANY_THROW(scope->at("bar"));
}

TEST(Scope, ParentAccess) {
    auto parent = make_scope<int>();
    parent->insert("foo", 1);
    auto child = make_scope(parent);
    ASSERT_EQ(child->at("foo"), 1);
    child->insert("foo", 2);
    ASSERT_EQ(child->at("foo"), 2);
    ASSERT_EQ(parent->at("foo"), 1);
}

TEST(Scope, ParentRef) {
    auto scope = [] {
        auto parent = make_scope<int>();
        parent->insert("bar", 1);
        return make_scope(parent);
    }();

    ASSERT_EQ(scope->at("bar"), 1);
    scope->insert("bar", 4);
    ASSERT_EQ(scope->at("bar"), 4);
    scope->insert("baz", 1);
    ASSERT_EQ(scope->at("baz"), 1);

    scope = scope->parent();
    ASSERT_EQ(scope->at("bar"), 1);
    ASSERT_FALSE(scope->contains("baz"));
}
