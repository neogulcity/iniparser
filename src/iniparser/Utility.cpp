#include <string>
#include "Utility.h"

namespace Utility
{
    void remove_blank(std::string &arg)
    {
        while (arg.find(" ") == 0) {
            arg.replace(arg.begin(), arg.begin() + 1, "");
        }
        while (arg.rfind(" ") == arg.size() - 1) {
            arg.replace(arg.end() - 1, arg.end(), "");
        }
    }

    std::string remove_blank_copy(std::string arg)
    {
        std::string result = arg;
        while (result.find(" ") == 0) {
            result.replace(result.begin(), result.begin() + 1, "");
        }
        while (result.rfind(" ") == result.size() - 1) {
            result.replace(result.end() - 1, result.end(), "");
        }
        return result;
    }
}