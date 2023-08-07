# Returning Multiple Values {#WBFL_Returning_Multiple_Values}

C++ functions return a single value. In older style programming, multiple return values were handled in a function's argument list with pointers or references. 

An example of using pointers for return values is:

~~~~~~~~~~~
WBFL::Geometry::Point point;
Float64 x,y;
point.Location(&x,&y);
~~~~~~~~~~~

where the `Location` method is implemented as

~~~~~~~~~~~
void WBFL::Geometry::Point::Location(Float64* pX,Float64* pY) const
{
   *pX = m_X;
   *pY = m_Y;
}
~~~~~~~~~~~

The problem with this implementation is that it can be called with invalid pointers leading to undefined behavior. A more robust implementation would validate the pointers and throw exceptions to signal errors.

An example of using references for return values is:
~~~~
WBFL::Geometry::Point point;
Float64 x,y;
point.Location(x,y);
~~~~

where the `Location` method is implemented as

~~~~~~~~~~~
void WBFL::Geometry::Point::Location(Float64& X,Float64& Y) const
{
   X = m_X;
   Y = m_Y;
}
~~~~~~~~~~~

This implementation avoids the problem of invalid pointers. However, for more complex functions taking both input arguments and return parameters, it is difficult to know which are which. For example:

~~~
   object.Function(v1,v2,v3,v4);
~~~

The parameters `v1` and `v2` are input and `v3` and `v4` are output. This is not at all obvious.

The preferred method for returning multiple values is `std::pair`, `std::tuple` or a custom `struct` or `class`.

Some examples of function implementations are:

~~~
std::pair<Float64,Float64> WBFL::Geometry::Point::Location() const
{
   return std::make_pair(m_X,m_Y);
}
~~~

> Note: `std::pair` is automatically converted to `std::tuple` so they are essentinally interchangable.

Calling functions can use *structured bindings* or `std::tie` objects to relate the elements of the returned `std::pair` or `std::tuple` to individual, and well named, parameters. Here is an example for the `Point` class

~~~
   Point p(10,10);

   auto location = p.Location();
   std::cout << "X = " << location.first << ", Y = " << location.second << std::endl;

   // a more readable implementation is to use std::tie

   Float64 x,y;
   std::tie(x,y) = p.Location();
   std::cout << "X = " << x << ", Y = " << y << std::endl;

   // The std::tie method requires the definition of variables that are often uninitialized.
   // Structured bindings, available since C++ 17, allow the variables to be defined and
   // initalized in one statement
   auto [x,y] = p.Location();
   std::cout << "X = " << x << ", Y = " << y << std::endl;
~~~

One problem with structured bindings and `std::tie` is the return values and the order they occur lack contextual meaing. This is especially true for methods that return more than about 3 or 4 parameters. In these situations consider returning a struct or class so the returned values have context.


Structured bindings can also be used to bind variables from structures as show in this example.
~~~
   struct Values {Float64 x, Uint32 y, WBFL::Geometry::Point z};
   Values v{10.0,20,{15.0,15.0}};
   auto [a,b,c] = values;
   std::cout << "X = " << c.X() << ", Y = " << c.Y() << std::endl;
~~~

Structred bindings make looping over maps more readable
~~~
   std::map<IDType,Float64> m{{1,10.0},{2,20.0}};

   // make returned pairs more meaningful
   auto result = m.insert(std::make_pair(3,30.0)); // returns iterator and bool
   CHECK(result.second == true);
   CHECK(result->first.first == 3));
   CHECK(IsEqual(result->first.second,30.0));

   auto [iter,bSucceeded] = m_insert(std::make_pair(4,40.0)); // returns iterator and bool
   CHECK(bSucceeded);
   CHECK(iter->first == 40));
   CHECK(IsEqual(iter->second,40.0));

   // structured bindings make looping over the elements of a std::map more readable 
   for(const auto& p : m)
   {
      DoSomething(p.first,p.second);
   }

   for(const auto& [id,value] : m)
   {
      DoSomething(id,value);
   }
~~~
