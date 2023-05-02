# Returning Multiple Values {#WBFL_Returning_Multiple_Values}

C++ functions are only permitted to return a single value. In older style programming, multiple return values were handled in a function's argument list with pointers or references. 

An example of using pointers for return values is:

~~~~~~~~~~~
Float64 x,y;
point->Location(&x,&y);
~~~~~~~~~~~

where the `Location` method is implemented as

~~~~~~~~~~~
void Point::Location(Float64* pX,Float64* pY) const
{
   *pX = m_X;
   *pY = m_Y;
}
~~~~~~~~~~~

The problem with this implementation is that it can be called with invalid pointers leading to undefined behavior. A more robust implementation would validate the provided pointers and throw exceptions to signal errors.

An example of using references for return values is:
~~~~
Float64 x,y;
point->Location(x,y);
~~~~

where the `Location` method is implemented as

~~~~~~~~~~~
void Point::Location(Float64& X,Float64& Y) const
{
   X = m_X;
   Y = m_Y;
}
~~~~~~~~~~~

The implementation avoids the problem of invalid pointers. However, for more complex functions taking both input arguments and return parameters, it is difficult to know where are which. For example:

~~~
   object.Function(v1,v2,v3,v4);
~~~

The parameters `v1` and `v2` are input and `v3` and `v4` are output. This is not at all obvious.

The preferred method for returning multiple values is `std::pair`, `std::tuple` or a custom `struct` or `class`.

Some examples of function implementations are:

~~~
std::pair<Float64,Float64> Point::Location() const
{
   return std::make_pair(m_X,m_Y);
}
~~~

Calling functions can use the `std::tie` object to relate the elements of the returned `std::pair` or `std::tuple` to individual, and well named, parameters. Here is an example for the `Point` class

~~~
   Point p(10,10);

   auto location = p.Location();
   std::cout << "X = " << location.first << ", Y = " << location.second << std::endl;

   // a more readable implementation is to use std::tie

   Float64 x,y;
   std::tie(x,y) = p.Location();
   std::cout << "X = " << x << ", Y = " << y << std::endl;
~~~

When these libraries are updated to C++ 17 `std::tie` can be eliminated in favor of *structured bindings*. Structured bindings give us the ability to declare multiple variables that are initialized from a tuple or struct. An example of structured bindings is:

~~~
   Point p(10,10);
   auto [x,y] = p.Location();   
   std::cout << "X = " << x << ", Y = " << y << std::endl;
~~~

> `std::pair` is automatically converted to `std::tuple` so they are essentinally interchangable.