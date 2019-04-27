#include "Strong.h"

int main() {
    using Distance = double; // Alias

    auto d = Distance{3} + 2; // Ok: just double

    using Velocity = Strong<double, struct VelocityTag>;
    // auto v = Velocity{3} + 2; // Error: no operator

    (void)d;
}
