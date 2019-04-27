#pragma once

// clang-format off

// schema primitives:
template<class...> struct AllOf {}; // struct
template<class...> struct OneOf {}; // variant
template<class...> struct SomeOf {};
template<class Id, class> struct EntitySet {};
template<class Id, class> struct IdMap {};

template<class Id, class Node, class Leaf>
struct OrderedTree {};
