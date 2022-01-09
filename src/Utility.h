#pragma once

namespace Utility
{
    // Return curent build process is in debug or not.
    inline bool IsDebug()
    {
        #ifdef _DEBUG
            return true;
        #else
            return false;
        #endif
    }

    inline void remove_comments(std::string &arg)
    {
        int32_t index = arg.find("#") != std::string::npos ? arg.find("#") : -1;
        if (index == -1)
            return;

        arg.replace(arg.begin() + index, arg.end(), "");
    }

    void remove_blank(std::string &arg);
    std::string remove_blank_copy(std::string arg);
}