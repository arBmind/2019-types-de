#pragma once
#include "../strong/Strong.h"
#include "Abstract.h"
#include "Storage.h"

#include <map>
#include <optional>
#include <tuple>
#include <variant>
#include <vector>

namespace repository {

using namespace abstract;
using storage::isValue;
using storage::ToStorage;

// clang-format off
template<class T> struct ADL {};
template<class T>
using ToRepository = decltype(toRepository(ADL<T>{}));
// clang-format on

template<class... Ts>
auto toRepository(ADL<AllOf<Ts...>>) -> std::tuple<ToRepository<Ts>...>;

template<class T>
auto toRepository(ADL<T>) -> std::enable_if_t<isValue<T>(), T>;

namespace simple {

// tag::simpleEntitySet[]
template<class Id, class Data>
auto toRepository(ADL<EntitySet<Id, Data>>) -> std::map<Id, ToRepository<Data>>;
// end::simpleEntitySet[]

} // namespace simple

template<class Id>
struct Less {
    constexpr bool operator()(Id l, Id r) const noexcept { return l.v < r.v; }
};

// tag::entityRepository[]
template<class Id, class Data>
class EntityRepository {
    std::map<Id, ToRepository<Data>, Less<Id>> m;

public:
    auto operator[](Id) -> ToRepository<Data> &;
    auto operator[](Id) const -> const ToRepository<Data> &;
    void create(const ToStorage<Data> &);
    void remove(Id);
};

template<class Id, class Data>
auto toRepository(ADL<EntitySet<Id, Data>>) //
    -> EntityRepository<Id, Data>;
// end::entityRepository[]

// implementation
template<class Id, class Data>
auto EntityRepository<Id, Data>::operator[](Id id) -> ToRepository<Data> & {
    return m[id];
}
template<class Id, class Data>
auto EntityRepository<Id, Data>::operator[](Id id) const -> const ToRepository<Data> & {
    return m[id];
}

template<class Id, class Data>
auto EntityRepository<Id, Data>::create(const ToStorage<Data> &data) -> void {
    static auto id = 0;
    m.insert_or_assign(Id{++id}, data);
}

template<class Id, class Data>
auto EntityRepository<Id, Data>::remove(Id id) -> void {
    m.erase(id);
}

} // namespace repository
