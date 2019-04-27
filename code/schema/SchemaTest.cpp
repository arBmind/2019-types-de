#include "Command.h"
#include "Compute.h"
#include "PersonSchema.h"
#include "Processor.h"
#include "Repository.h"

#include <iostream>

using Repository = repository::ToRepository<Persons>;
using Command = command::ToCommand<Persons>;
using CreateCommand = command::ToStorage<PersonData>;
constexpr auto commandProcessor = processor::to_command_processor<Persons>;

using OutPersons = compute::ToComputed<Persons>;
using OutCommand = command::ToCommand<OutPersons>;
using OutCreateCommand = command::ToStorage<compute::ToComputed<PersonData>>;
using OutRepository = repository::ToRepository<OutPersons>;
constexpr auto outCommandProcessor = processor::to_command_processor<OutPersons>;

int main() {
    Command cmd1 = CreateCommand{
        Anrede::Herr,         //
        Vorname{"Andreas"},   //
        Nachname{"Reischuck"} //
    };

    Repository repo;
    commandProcessor(cmd1, repo);

    std::cout << std::get<Vorname>(repo[PersonId{1}]).v << "\n";

    OutCommand outCmd1 = OutCreateCommand{
        Anrede::Herr,          //
        Vorname{"Andreas"},    //
        Nachname{"Reischuck"}, //
        Ansprache{"TODO"}      //
    };
    compute::compute(repo[PersonId{1}], std::get<Ansprache>(std::get<OutCreateCommand>(outCmd1)));

    OutRepository outRepo;
    outCommandProcessor(outCmd1, outRepo);

    std::cout << std::get<Ansprache>(outRepo[PersonId{1}]).v << "\n";
}
