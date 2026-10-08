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

    static constexpr std::array<option, 5> long_options{{{"input", required_argument, nullptr, 'i'},
                                                         {"output", required_argument, nullptr, 'o'},
                                                         {"algorithm", required_argument, nullptr, 'a'},
                                                         {"seed", required_argument, nullptr, 's'},
                                                         {nullptr, 0, nullptr, 0}}};

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
