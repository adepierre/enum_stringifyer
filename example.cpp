#include <iostream>

#include "enum_stringifyer/enum_stringifyer.hpp"

enum class Test : char
{
    neg = -8,
    a = 0,
    more_a = a,
    b = 3,
    c
};
// Looks like someone forgot to update after adding Test::c, no problem
DEFINE_ENUM_STRINGIFYER_RANGE(Test, Test::neg, Test::b);

enum class Test2 : unsigned short
{
    a = 1 << 0,
    b = 1 << 1,
    c = 1 << 2,
    d = 1 << 3,
    e = 1 << 4,
    f = 1 << 5,
    g = 1 << 6,
    h = 1 << 7,
    i = 1 << 8,
    j = 1 << 9,
};
DEFINE_ENUM_STRINGIFYER_LIST(Test2,
    Test2::a,
    Test2::b,
    Test2::c,
    Test2::d,
    Test2::e,
    // forgot f, everything is still fine
    Test2::g,
    Test2::h,
    Test2::i,
    Test2::j);

int main()
{
    std::cout 
        << Test::neg << '\n'    // Test::neg
        << Test::a << '\n'      // Test::a
        << Test::more_a << '\n' // Test::a
        << Test::b << '\n'      // Test::b
        << Test::c << '\n'      // (Test)4
        << '\n'
        << Test2::a << '\n'     // Test2::a
        << Test2::b << '\n'     // Test2::b
        << Test2::c << '\n'     // Test2::c
        << Test2::d << '\n'     // Test2::d
        << Test2::e << '\n'     // Test2::e
        << Test2::f << '\n'     // (Test2)32
        << Test2::g << '\n'     // Test2::g
        << Test2::h << '\n'     // Test2::h
        << Test2::i << '\n'     // Test2::i
        << Test2::j << '\n';    // Test2::j
}
