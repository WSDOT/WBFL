// UnitConversion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Units/Units.h>

Float64 DoSomeCalculation(Float64 length_in_system_units);

int main()
{
   // A simple unit conversion example
   auto value = WBFL::Units::Convert(100.0, WBFL::Units::Measure::Feet, WBFL::Units::Measure::Meter);
   std::_tcout << _T("100 ft = ") << value << _T(" m.") << std::endl;

   // Calculations functions should be designed to work with consistent units so unit conversions aren't required.
   // However, sometimes a calculation must be performed using values with specific units of measure. For example,
   // the equations in Ch. 5 of the LRFD specifications required concrete strength to be in KSI units. 
   // 
   // At the time a function is written, you don't know what unit system a program may be using. It is best to
   // let programmers call your function using values and receive results in their unit system. This makes using
   // your functions much easier.
   // 
   // The challange is converting values to and from an unknown unit system. The WBFL::Units library has a global
   // unit system definition. The default is SI units. Here we show a simple function that takes a length value and 
   // returns a stress value. However, the calculation within the function requires the length to be in feet.
   Float64 result = DoSomeCalculation(value);

   return 0;
}

Float64 DoSomeCalculation(Float64 length_in_system_units)
{
   // This calculation requires the length to be in Feet.
   // This function demonstrates how to convert to and from system units.

   // Generally, we don't know what the system units are, however it is easy to convert from system units to a specific unit of measure
   Float64 length_in_feet = WBFL::Units::ConvertFromSysUnits(length_in_system_units, WBFL::Units::Measure::Feet);
   Float64 stress_in_ksi = 5.5 * length_in_feet; // result of this calculation is in ksi. there are unit conversion constants in the emperical 5.5 factor

   // this function needs to return the stress in system units
   Float64 stress_in_system_units = WBFL::Units::ConvertToSysUnits(stress_in_ksi, WBFL::Units::Measure::KSI);
   return stress_in_system_units;
}
