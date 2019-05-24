#pragma once
#include "Strong.h"

#include <type_traits>

struct PersonId;

constexpr auto makeOpaque(Strong<int, struct PersonIdTag>) -> PersonId;

struct PersonId : Strong<int, PersonIdTag> {
    using Strong::Strong;
};

static_assert(                                                          //
    std::is_same_v<                                                     //
        decltype(makeOpaque(std::declval<Strong<int, PersonIdTag>>())), //
        PersonId>);
