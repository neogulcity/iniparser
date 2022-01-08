#include <fstream>
#include "Utility.h"
#include "spdlog/spdlog.h"

namespace ini
{
    class ini
    {
        std::string path;
    public:
        ini(std::string _path) : path(_path) {}
        std::string get(std::string _section, std::string _arg, std::string _default);
    };
    
    std::string ini::get(std::string _section, std::string _arg, std::string _default)
    {
        std::string result = _default;
        std::ifstream file(path);

        if (file.is_open()) {
            bool inSection = false, isFind = false;
            while (file) {
                std::string line;
                getline(file, line);

                Utility::remove_comments(line);

                if (line == "")
                    continue;

                if (line != _section && !inSection)
                    continue;
                
                if (line == _section) {
                    inSection = true;
                    continue;
                }
                
                if (inSection && line.find("[") != std::string::npos)
                    break;

                auto index = line.find("=") != std::string::npos ? line.find("=") : (size_t)0;
                auto temparg = line;
                temparg.replace(temparg.begin() + index, temparg.end(), "");
                if (Utility::remove_blank_copy(temparg) == _arg) {
                    isFind = true;
                    if (index > line.size())
                        break;
                    
                    temparg = line;
                    temparg.replace(temparg.begin(), temparg.begin() + index + 1, "");
                    Utility::remove_blank(temparg);
                    
                    result = temparg;

                    break;
                }
            }

            file.close();
        } else {
            spdlog::warn("Failed to open file.");
        }

        return result;
    }
    
}

int main()
{
    return 0;
}