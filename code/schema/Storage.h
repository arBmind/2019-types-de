#pragma once
#include "../strong/Strong.h"
#include "Abstract.h"

#include <tuple>
#include <variant>
#include <vector>

// clang-format off

// tag::adl_boilerplate[]
// Storage ADL Boilerplate
namespace storage {

template<class T> struct Wrap {};

template<class T> auto toStorage(T);

template<class T>
using ToStorage = decltype(toStorage(Wrap<T>{}));
// end::adl_boilerplate[]

// tag::abstracts[]
template<class... Ts>
auto toStorage(Wrap<AllOf<Ts...>>)
    -> std::tuple<ToStorage<Ts>...>;

template<class... Ts>
auto toStorage(Wrap<OneOf<Ts...>>)
    -> std::variant<ToStorage<Ts>...>;

template<class Id, class Data>
auto toStorage(Wrap<EntitySet<Id, Data>>)
    -> std::vector<std::tuple<Id, ToStorage<Data>>>;
// end::abstracts[]

// tag::values[]
// storage for values
template<class T>
constexpr bool isValue() {
    if constexpr (std::is_class_v<T>)
        return !std::is_empty_v<T>;
    else
        return std::is_enum_v<T>;
}

template<class T>
auto toStorage(Wrap<T>)
    -> std::enable_if_t<isValue<T>(), T>;
// end::values[]
// end::abstracts[]

// tag::orderedtree[]
// Storage for OrderedTree
template<class Id>
using ParentId = StrongAddTag<Id, struct ParentIdTag>;

template<class Id, class Node, class Leaf>
using TreeNode = std::tuple<
    Id, ParentId<Id>,
    std::variant<ToStorage<Node>, ToStorage<Leaf>>
    >;

template<class Id, class Node, class Leaf>
auto toStorage(Wrap<OrderedTree<Id, Node, Leaf>>)
    -> std::vector<TreeNode<Id, Node, Leaf>>;
// end::orderedtree[]

} // namespace storage
