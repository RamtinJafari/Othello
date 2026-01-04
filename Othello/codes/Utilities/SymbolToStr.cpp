#include <string>

std::string symbolToStr(char32_t character)
{
    if (character == '⬤')
    {
        return "⬤";
    }
    else if (character == '○')
    {
        return "○";
    }
    else if (character == ' ')
    {
        return " ";
    }
    else if (character == '⦻')
    {
        return "⦻";
    }
    else if (character == '⊙')
    {
        return "⊙";
    }
}