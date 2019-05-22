#pragma once
#include "Storage.h"

namespace compute {

using namespace abstract;
using storage::isValue;
using storage::ToStorage;
// clang-format off

template <class... As, class... Bs>
auto join(AllOf<As...>, AllOf<Bs...>) -> AllOf<As...,Bs...>;

template<class A, class B>
using Join = decltype(join(std::declval<A>(), std::declval<B>()));


template<class T> struct ADL {};

template<class T>
using ToComputed = decltype(toComputed(ADL<T>{}));

template<class T>
using ToComputedValues = decltype(toComputedValues(std::declval<T>()));

// Schema -> Computed Schema
template<class... Ts>
auto toComputed(ADL<AllOf<Ts...>>)
    -> Join<AllOf<ToComputed<Ts>...>, ToComputedValues<AllOf<Ts...>>>;
// … keep remaining schema
// end::toComputedValues[]

template<class... Ts>
auto toComputed(ADL<OneOf<Ts...>>) -> OneOf<ToComputed<Ts>...>;

template<class T>
auto toComputed(ADL<T>)
    -> std::enable_if_t<isValue<T>(), T>;

template<class Id, class Data>
auto toComputed(ADL<EntitySet<Id, Data>>)
    -> EntitySet<Id, ToComputed<Data>>;

} // namespace compute
