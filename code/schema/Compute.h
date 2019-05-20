#pragma once
#include "PersonSchema.h"
#include "Storage.h"

#include <sstream>

namespace compute {

using storage::isValue;
using storage::ToStorage;
// clang-format off

template<class T> struct ADL {};

template<class T> auto toComputed(T);

template<class T>
using ToComputed = decltype(toComputed(ADL<T>{}));

// tag::ansprache[]
inline void compute(const ToStorage<PersonData>& s, Ansprache& o) {
  auto anrede = std::get<Anrede>(s);
  auto& nachname = std::get<Nachname>(s);
  auto out = std::stringstream{};
  switch (anrede) {
  case Anrede::Neutral: out << "Hallo " << nachname.v; break;
  case Anrede::Herr: out << "Sehr geehrter Herr " << nachname.v; break;
  case Anrede::Frau: out << "Sehr geehrte Frau " << nachname.v; break;
  }
  o.v = out.str();
}
// end::ansprache[]

template <class... As, class... Bs>
auto join(AllOf<As...>, AllOf<Bs...>) -> AllOf<As...,Bs...>;

template<class A, class B>
using Join = decltype(join(A{}, B{}));

// tag::toComputedValues[]
template<class T>
auto toComputedValues(T) -> AllOf<>; // Fallback

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
