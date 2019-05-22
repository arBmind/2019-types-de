#pragma once
#include "Abstract.h"

#include <tuple>
#include <type_traits>
#include <variant>

namespace storage {

using namespace abstract;

template<class T>
auto toStorage(T);

template<class T>
using ToStorage = decltype(toStorage(std::declval<T>()));

template<class... Ts>
auto toStorage(AllOf<Ts...>) -> std::tuple<ToStorage<Ts>...>;

// using Test = ToStorage<AllOf<>>; // error

} // namespace storage
