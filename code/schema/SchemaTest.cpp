#include "Command.h"
#include "Compute.h"
#include "PersonCompute.h"
#include "PersonSchema.h"
#include "Processor.h"
#include "Repository.h"

#include <iostream>

using namespace person;

using command::EntityCreate;
using command::ToCommand;
using processor::to_command_processor;
using repository::ToRepository;

using Command = ToCommand<Persons>;
using Repository = ToRepository<Persons>;
constexpr auto processCommand = to_command_processor<Persons>;

// nest++
void testCreate() {
    auto repo = Repository{};
    using CreateCmd = EntityCreate<PersonData>;
    auto cmd = CreateCmd{Anrede::Herr, Vorname{"Bjarne"}, Nachname{"Stroustrup"}};
    processCommand(cmd, repo);

    std::cout << std::get<Vorname>(repo[PersonId{1}]).v << "\n";
}

using compute::ToComputed;
using OutPersons = ToComputed<Persons>;

void testCompute() {
    using CreateCmd = EntityCreate<PersonData>;
    auto input = CreateCmd{Anrede::Herr, Vorname{"Bjarne"}, Nachname{"Stroustrup"}};
    auto output = Ansprache{};
    computeComputed(input, output);

    std::cout << output.v << "\n";

    using OutCommand = ToCommand<OutPersons>;
    using OutCreateCommand = EntityCreate<ToComputed<PersonData>>;
    using OutRepository = ToRepository<OutPersons>;
    constexpr auto processOutCommand = processor::to_command_processor<OutPersons>;

    OutCommand outCmd1 = OutCreateCommand{
        std::get<Anrede>(input),   //
        std::get<Vorname>(input),  //
        std::get<Nachname>(input), //
        output                     //
    };
    OutRepository outRepo;
    processOutCommand(outCmd1, outRepo);

    // std::cout << std::get<Ansprache>(outRepo[PersonId{1}]).v << "\n";
}

int main() {
    testCreate();
    testCompute();
}
