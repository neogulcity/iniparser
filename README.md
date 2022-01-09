# iniparser
 Basic ini parser

## Requirements
* [CMake](https://cmake.org/)
* [spdlog](https://github.com/gabime/spdlog/)

## Build
```
git clone https://github.com/neogulcity/iniparser
cd iniparser
cmake -B build -S .
```

## Install
```
cd build
cmake --install .
```

## Example
```ini
# example.ini
[Section]
variable = Hello World! # example comment.
```

```cpp
// example.cpp
#include <iostream>
#include "iniparser/iniparser.h"

int main()
{
    ini::ini ifile("example.ini");
    std::string istring = ifile.get("[Section]", "variable", "null");
    std::cout << istring << std::endl;
    return 0;
}
```