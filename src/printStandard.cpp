#include <iostream>

const int numStandards = 7;
const long stdCode[numStandards] = {199711L, 201103L, 201402L, 201703L, 202002L, 202302L, 202612L};
const char *stdName[numStandards] = {"Pre-C++11", "C++11", "C++14", "C++17", "C++20", "C++23", "C++26"};

long getCppStandard()
{
#if defined(_MSVC_LANG)
    return _MSVC_LANG;
#elif defined(_MSC_VER)
    return -1;
#else
    return __cplusplus;
#endif
}

void getStandard()
{
    long standard = getCppStandard();

    if (standard == -1)
    {
        std::cout << "Error: Unable to determine your (language) standards. Sorry\n";
    }

    for (int i = 0; i < numStandards; ++i)
    {
        if (standard == stdCode[i])
        {
            std::cout << "Your Compiler is Using: " << stdName[i]
                      << "(language) standard code " << standard << "\n";
            break;
        }

        if (standard < stdCode[i])
        {
            std::cout << "Your compiler is using a preview/pre-release of " << stdName[i]
                      << " (language standard code " << standard << "L)\n";
            break;
        }
    }
    std::cout << "\n\n";
}