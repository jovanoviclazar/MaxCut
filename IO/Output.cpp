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
    std::fstream output(filePath);
    output << cut;
}

std::ostream &operator<<(std::ostream &output, const CutResult &cut)
{
    output << cut.CutCost() << '\n';

    std::string separator;

    for (const int element : cut.VectorA())
    {
        output << separator << element;
        separator = " ";
    }
    output << '\n';

    separator = "";

    for (const int element : cut.VectorB())
    {
        output << separator << element;
        separator = " ";
    }
    output << '\n';

    return output;
}
} // namespace MaxCut
