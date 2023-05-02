# pImpl Idiom {#WBFL_PIMPL}

"Pointer to implementation" or "pImpl" idiom is a C++ programming technique to removes implementation details of a class from its object representation by placing them in a separate class, accessed through an opaque pointer;

There are many excellent references that discuss the *pImpl* idiom.
* https://en.cppreference.com/w/cpp/language/pimpl
* https://learn.microsoft.com/en-us/cpp/cpp/pimpl-for-compile-time-encapsulation-modern-cpp?view=msvc-170
* https://www.geeksforgeeks.org/pimpl-idiom-in-c-with-examples/

There is a minor complication when using `std::unique_ptr` with the pImpl idiom and a default or compiler generated destructor. A good discussion is provided here: https://stackoverflow.com/questions/9020372/how-do-i-use-unique-ptr-for-pimpl

The bottom line is this. Declare the destructor in the header file and implement it in the cpp file.

~~~
// file.h
class MyClass
{
public:
   ~MyClass();
}
~~~

~~~
// file.cpp
MyClass::~MyClass() = default;
~~~

Examples of this technique can be found in most all WBFL classes using the *pImpl* idiom