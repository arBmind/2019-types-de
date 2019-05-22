#pragma once
#include "../strong/Strong.h"
#include "Abstract.h"

#include <string>

namespace person {

using std::string;
using namespace abstract;

// tag::persons[]
// example usage:
enum class Anrede { Neutral, Herr, Frau };
using Vorname = Strong<string, struct VornameTag>;
using Nachname = Strong<string, struct NachnameTag>;
using PersonData = AllOf<Anrede, Vorname, Nachname>;

using PersonId = Strong<int, struct PersonIdTag>;
using Persons = EntitySet<PersonId, PersonData>;
// end::persons[]

// tag::ansprache[]
using Ansprache = Strong<std::string, struct AnspracheTag>;

auto toComputedValues(PersonData) -> AllOf<Ansprache>;
// end::ansprache[]

} // namespace person
