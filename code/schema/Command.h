#pragma once
#include "../strong/Strong.h"
#include "Abstract.h"
#include "Storage.h"

#include <optional>
#include <tuple>
#include <variant>
#include <vector>

namespace command {

using namespace abstract;
using storage::isValue;
using storage::ToStorage;

// clang-format off
template<class T> struct ADL {};
template<class T> auto toCommand(T);
template<class T>
using ToCommand = decltype(toCommand(ADL<T>{}));
// clang-format on

template<class... Ts>
auto toCommand(ADL<AllOf<Ts...>>) -> std::tuple<ToCommand<Ts>...>;

template<class T>
auto toCommand(ADL<T>) -> std::enable_if_t<isValue<T>(), std::optional<T>>;

template<class Data>
using EntityCreate = ToStorage<Data>;
template<class Id, class Data>
using EntityUpdate = std::tuple<Id, ToCommand<Data>>;
template<class Id>
using EntityDelete = Id;

template<class Id, class Data>
auto toCommand(ADL<EntitySet<Id, Data>>) -> std::variant<
    EntityCreate<Data>, EntityUpdate<Id, Data>, EntityDelete<Id>>;

using storage::ParentId;
template<class Id>
using BeforeId = StrongAddTag<Id, struct BeforeIdTag>;

// clang-format off

// Commands for OrderedTree
template<class Id, class Node, class Leaf>
using TreeCreate = std::tuple<
    ParentId<Id>, BeforeId<Id>, ToStorage<OrderedTree<Id, Node, Leaf>>>;

template<class Id, class Node, class Leaf>
using TreeUpdate = std::tuple<
    Id, std::variant<ToCommand<Node>, ToCommand<Leaf>>>;

template<class Id, class Node, class Leaf>
auto toCommand(ADL<OrderedTree<Id, Node, Leaf>>)
    -> std::variant<
        TreeCreate<Id, Node, Leaf>,                 // Create
        TreeUpdate<Id, Node, Leaf>,                 // Update
        std::tuple<Id, ParentId<Id>, BeforeId<Id>>, // Move
        Id>;                                        // Delete

} // namespace command
