#pragma once
#include "PersonSchema.h"
#include "Storage.h"

#include <sstream>

namespace person {

using storage::ToStorage;

// tag::ansprache[]
inline void computeComputed(const ToStorage<PersonData> &s, Ansprache &o) {
    auto anrede = std::get<Anrede>(s);
    auto &nachname = std::get<Nachname>(s);
    auto out = std::stringstream{};
    switch (anrede) {
    case Anrede::Neutral: out << "Hallo " << nachname.v; break;
    case Anrede::Herr: out << "Sehr geehrter Herr " << nachname.v; break;
    case Anrede::Frau: out << "Sehr geehrte Frau " << nachname.v; break;
    }
    o.v = out.str();
}
// end::ansprache[]

} // namespace person
