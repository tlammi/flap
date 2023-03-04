#include <gtest/gtest.h>

#include "flap/algo.hpp"

static_assert(flap::any_of_eq(1, 1, 2, 3, 4, 5));
static_assert(!flap::any_of_eq(1, 2, 3, 4, 5, 6));

static_assert(flap::none_of_eq(1, 2, 3, 4, 5));
static_assert(!flap::none_of_eq(1, 2, 3, 1, 4, 5));

static_assert(flap::all_of_eq(1, 1, 1, 1, 1, 1, 1, 1));
static_assert(!flap::all_of_eq(1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1));

