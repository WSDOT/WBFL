///////////////////////////////////////////////////////////////////////
// WBFL - Washington Bridge Foundation Libraries
// Copyright © 1999-2014  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#pragma once

// Factors the value of an element in a collection
// Use with std::transform to multiplya constant to every element in a collection
//
// Multiply every element in a collection by 25, put the results back into the collection
// std::transform(myCollection.begin(),myCollection.end(),myCollection.begin(),FactorElements<Float64>(25.0));
//
// Multiply every element in a collection by 25, put the results into a different collection
// std::transform(myCollection.begin(),myCollection.end(),std::back_inserter(myOtherCollection),FactorElements<Float64>(25.0));
template <class ElementType>
class FactorElements
{
public:
   FactorElements(Float64 factor) : Factor(factor) {}
   ElementType operator() (ElementType& element) const
   {
      return element*Factor;
   }

   Float64 Factor;
};

// Increments the value of an element in a collection
// Use with std::transform to add a constant to every element in a collection
//
// Add 25 to every element in a collection, put the results back into the collection
// std::transform(myCollection.begin(),myCollection.end(),myCollection.begin(),IncrementElements<Float64>(25.0));
//
// Add 25 to every element in a collection, put the results into a different collection
// std::transform(myCollection.begin(),myCollection.end(),std::back_inserter(myOtherCollection),IncrementElements<Float64>(25.0));
template <class ElementType>
class IncrementElements
{
public:
   IncrementElements(Float64 increment) : Increment(increment) {}
   ElementType operator() (ElementType& element) const
   {
      return element+Increment;
   }

   Float64 Increment;
};

// Increments a value...
// Use with std::generate to fill a container with sequential values
// std::vector<int> myContainer;
// myContainer.resize(theSize);
// std::generate(myContainer.begin(),myContainer.end(),IncrementValue<int>(0));
// myContainer will contain 0,1,2,3,...,theSize-1
template<class T>
class IncrementValue
{
public:
   T current;
   IncrementValue(const T& start) : current(start) {}
   T operator()(){return current++;}
};

// Functor class for giving tolerance for finding floats in map containers
// usage
// std::map<Float64,ValueType,Float64_less> myMap;
class Float64_less
{
public:
   bool operator()(const Float64& d1,const Float64& d2) const { return ::IsLT(d1,d2); }
};
