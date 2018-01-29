#include "Program.hpp"

using namespace MellowPlayer::Main;

int main(int argc, char** argv)
{
    // Init resources embedded in static libraries
    Q_INIT_RESOURCE(infrastructure);
    Q_INIT_RESOURCE(presentation);
    Q_INIT_RESOURCE(imports);

    return Program::main(argc, argv);
}
