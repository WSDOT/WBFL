# Scoped Enumerators

Scoped enumerators should be used unless there is a compelling reason to do otherwise.

Scope enumerators offer better type safety compared to unscoped enumerators.

One draw back of scoped enumerators is that they don't implicitly convert to intergers. This makes it difficult to use them as array indicies. However, there is a cleaver technique that is used in the WBFL. The unary + operator is overloaded for scoped enumerators that are intended to be used as array indicies or otherwise need to be converted to an interger.

~~~~~~~~~
enum class MyEnum
{
   Value1,
   Value2
};

constexpr auto operator+(MyEnum a) noexcept
{
   return std::underlying_type<MyEnum>::type(a); // converts a to its underlying type
}

int main()
{
   std::cout << +MyEnum::Value1 << std::endl; // converts MyEnum::Value1 to an integer using unary operator+
   
   std::array<double,2> arr{10.0, 20.0};
   MyEnum index = MyEnum::Value2;
   std::cout << arr[+index] << std::endl; // converts index to an integer - output will be 20.0
   
   return 0;
}
~~~~~~~~~

See Effective Modern C++, Item #10, Scott Meyers

Also see https://www.learncpp.com/cpp-tutorial/scoped-enumerations-enum-classes/
