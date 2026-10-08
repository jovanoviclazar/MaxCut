#include "IO/Output.hpp"

namespace MaxCut
{
void Output::Write(std::ostream &output, const CutResult &cut)
{
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
