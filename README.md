Simple C++17 header only library to convert enum to string.

# Examples

```cpp
enum class Test : char
{
    a = -2,
    b,
    c = 3,
    d
};
DEFINE_ENUM_STRINGIFYER_RANGE(Test, Test::a, Test::c);
std::cout << Test::b << std::endl;
// Known value --> Test::b
std::cout << Test::d << std::endl;
// Unknown value --> (Test)4
```

```cpp
enum class Test : unsigned short
{
    a = 100,
    b = 1000,
    c = 10000
};
DEFINE_ENUM_STRINGIFYER_LIST(Test2, Test2::a, Test2::b, Test2::c);
std::cout << Test::b << std::endl;
// --> Test::b
```

[Live example](https://godbolt.org/z/vWvWbnTjY)

# Features

- enum to string only (no string to enum)
- can be added on top of legacy code (no change in enum declaration)
- mapping generated at compile time
- uses __PRETTY_FUNCTION__ (clang/gcc) or __FUNCSIG__ (msvc), but with a fallback on compilers without them: "(EnumName)enum_value"
- works on enum declared inside a class
- works on enum with duplicate values (they will have identical string representations though)
- works on small contiguous enums as well as ones with large arbitrary gaps between values
- donesn't crash at runtime if enum was updated with new values but not the string conversion call (fallback to "(EnumName)enum_value" string representations for the unknown values)
- is simple enough so future me will still be able to understand what's going on

# Usage

Just include [enum_stringifyer.hpp](enum_stringifyer/enum_stringifyer.hpp) and call the macro to generate the <<operator for your enum.

Note that DEFINE macros can only be used in one file for each enum. If you are in a hpp file that needs to be included in mutliple compilation units you can use ``DECLARE_ENUM_STRINGIFYER(Enum)`` to only declare the operator and then add the ``DEFINE_ENUM_STRINGIFYER_RANGE`` or ``DEFINE_ENUM_STRINGIFYER_LIST`` in any cpp file (once).

## Range

``DEFINE_ENUM_STRINGIFYER_RANGE`` should be used for continuous enums or non continuous ones when gaps are small with regard to the enum range. It takes an enum, a min and a max value. All values between min and max (included) will be mapped to a representation string. If some values inside are not part of the enum, they will still have an associated (useless) string. If you have large gaps in your enum, prefer using the LIST macro.

## List

``DEFINE_ENUM_STRINGIFYER_LIST`` can be used for any kind of enums. Only one string will be generated per unique enum value. The drawback is that you need to specify all values manually when calling the macro. This one is slightly less performant as it creates an array of (enum, string) pairs that needs to be searched for at runtime. However, it's much more size-efficient as gaps are not present in the array.
