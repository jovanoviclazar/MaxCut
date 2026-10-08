#include "Core/Core.hpp"
#include "IO/ArgumentParser.hpp"
#include "Model/Configuration.hpp"

int main(int argc, char **argv)
{
    const MaxCut::Configuration config = MaxCut::ArgumentParser::Parse(argc, argv);
    const MaxCut::Core core(config);
    return core.Run();
}
