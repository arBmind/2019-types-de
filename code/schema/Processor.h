#pragma once
#include "Command.h"
#include "Repository.h"

namespace processor {

using command::ToCommand;
using repository::ToRepository;
using storage::isValue;
using storage::ToStorage;

// clang-format off

// tag::boilerplate[]
template<class T> struct Wrap {};

template<class T>
constexpr auto toCommandProcessor(T); // Lambda(cmd, repo&)

template<class T>
constexpr auto to_command_processor = toCommandProcessor(Wrap<T>{});
// end::boilerplate[]

// clang-format on

template<class... Ts>
constexpr auto toCommandProcessor(Wrap<AllOf<Ts...>>) {
    return [](const ToCommand<AllOf<Ts...>> &cmd, ToRepository<AllOf<Ts...>> &repo) {
        return (to_command_processor<Ts>(std::get<ToCommand<Ts>>(cmd), std::get<ToRepository<Ts>>(repo)), ...);
    };
}

template<class T, std::enable_if_t<isValue<T>(), void *> = nullptr>
constexpr auto toCommandProcessor(Wrap<T>) {
    return [](const ToCommand<T> &cmd, ToRepository<T> &repo) {
        if (cmd) repo = *cmd;
    };
}

// clang-format off
template<class... Fs> struct Overloaded : Fs... { using Fs::operator()...; };
template<class... Fs> Overloaded(Fs...) -> Overloaded<Fs...>;
// clang-format on

template<class V, class... Fs>
auto oneVisit(V &&v, Fs &&... fs) {
    return std::visit(Overloaded{fs...}, v);
}

// clang-format off
// tag::entitySet[]
template<class Id, class Data>
constexpr auto toCommandProcessor(Wrap<EntitySet<Id, Data>>) {
  return [](const ToCommand<EntitySet<Id, Data>> &cmd,
            ToRepository<EntitySet<Id, Data>> &repo) {
    oneVisit(cmd,
        [&repo](const ToStorage<Data> &storage) {
          repo.create(storage);
        },
        [&repo](const std::tuple<Id, ToCommand<Data>> &update) {
          auto [id, dataCmd] = update;
          to_command_processor<Data>(dataCmd, repo[id]);
        },
        [&repo](Id id) { repo.remove(id); });
  };
}
// end::entitySet[]

} // namespace processor
