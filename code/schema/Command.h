#pragma once
#include "../strong/Strong.h"
#include "Abstract.h"
#include "Storage.h"

#include <optional>
#include <tuple>
#include <variant>
#include <vector>

namespace command {

using storage::isValue;
using storage::ToStorage;

// clang-format off
template<class T> struct Wrap {};

template<class T> auto toCommand(T);

template<class T>
using ToCommand = decltype(toCommand(Wrap<T>{}));

// clang-format on

template<class... Ts>
auto toCommand(Wrap<AllOf<Ts...>>) -> std::tuple<ToCommand<Ts>...>;

template<class T>
auto toCommand(Wrap<T>) -> std::enable_if_t<isValue<T>(), std::optional<T>>;

// tag::entitySet[]
template<class Id, class Data>
auto toCommand(Wrap<EntitySet<Id, Data>>) -> std::variant<ToStorage<Data>,                 // Create
                                                          std::tuple<Id, ToCommand<Data>>, // Update
                                                          Id>;                             // Delete
// end::entitySet[]

using storage::ParentId;
template<class Id>
using BeforeId = StrongAddTag<Id, struct BeforeIdTag>;

// clang-format off

// tag::orderedTree[]
// Commands for OrderedTree
template<class Id, class Node, class Leaf>
using TreeCreate = std::tuple<
    ParentId<Id>, BeforeId<Id>, ToStorage<OrderedTree<Id, Node, Leaf>>>;

template<class Id, class Node, class Leaf>
using TreeUpdate = std::tuple<
    Id, std::variant<ToCommand<Node>, ToCommand<Leaf>>>;

template<class Id, class Node, class Leaf>
auto toCommand(Wrap<OrderedTree<Id, Node, Leaf>>)
    -> std::variant<
        TreeCreate<Id, Node, Leaf>,                 // Create
        TreeUpdate<Id, Node, Leaf>,                 // Update
        std::tuple<Id, ParentId<Id>, BeforeId<Id>>, // Move
        Id>;                                        // Delete
// end::orderedTree[]

} // namespace command
