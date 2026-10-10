#include "IO/Output.hpp"
#include <fstream>

namespace MaxCut
{
void Output::Write(std::ostream &output, const CutResult &cut)
{
    output << cut;
}

void Output::WriteToFile(const std::string &filePath, const CutResult &cut)
{
    std::ofstream output(filePath);
    if (!output.is_open())
    {
        throw std::runtime_error("Cannot open output file: " + filePath);
    }
    output << cut;
    output.close();
}

std::ostream &operator<<(std::ostream &output, const CutResult &cut)
{
    output << cut.CutCost() << '\n';

    std::string separator;

    for (const size_t element : cut.VectorA())
    {
        output << separator << element;
        separator = " ";
    }
    output << '\n';

    separator = "";

    for (const size_t element : cut.VectorB())
    {
        output << separator << element;
        separator = " ";
    }
    output << '\n';

    return output;
}
} // namespace MaxCut
