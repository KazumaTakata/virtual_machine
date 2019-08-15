
#include <string>

using namespace std;

#define ENUM_MACRO(name, ...) \
    enum name                 \
    {                         \
        __VA_ARGS__           \
    };                        \
    const string name_##string[] = {#__VA_ARGS__};

ENUM_MACRO(eee, few);

int main()
{
}