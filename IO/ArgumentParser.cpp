#include "IO/ArgumentParser.hpp"
#include <array>
#include <getopt.h>
#include <stdexcept>
#include <string>

namespace MaxCut
{

Configuration ArgumentParser::Parse(int argc, char **argv)
{
    Configuration config;

    static constexpr std::array<option, 5> long_options{
        {{.name = "input", .has_arg = required_argument, .flag = nullptr, .val = 'i'},
         {.name = "output", .has_arg = required_argument, .flag = nullptr, .val = 'o'},
         {.name = "algorithm", .has_arg = required_argument, .flag = nullptr, .val = 'a'},
         {.name = "seed", .has_arg = required_argument, .flag = nullptr, .val = 's'},
         {.name = nullptr, .has_arg = 0, .flag = nullptr, .val = 0}}};

    int opt = 0;
    int option_index = 0;

    optind = 1;

    while ((opt = getopt_long(argc, argv, "i:o:a:s:h", long_options.data(), &option_index)) != -1)
    {
        switch (opt)
        {
        case 'i':
            config.inputPath = optarg;
            break;
        case 'o':
            config.outputPath = std::string(optarg);
            break;
        case 'a':
            config.algorithm = optarg;
            break;
        case 's':
            config.seed = static_cast<unsigned>(std::stoul(optarg));
            break;
        case '?':
        default:
            throw std::invalid_argument("Invalid command-line option passed.");
        }
    }

    return config;
}

} // namespace MaxCut
