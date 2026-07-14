WBFL Units {#WBFL_Units}
================
Introduction
------------

The WBFL Units library provides four basic services: general unit conversion, conversion to and from an
application's or component's internal system units, conversion and management of display units, and
(for the rare case where a unit's dimensionality isn't known until run time) dynamically-defined units.

General Unit Conversions
------------------------
The WBFL Units library can be used to convert physical quantities between the Customary U.S. unit system and
the International System of Units (SI). Unit conversions can also be performed within a unit system.

Units of measure are represented by instances of `WBFL::Units::PhysicalT<m,l,t,k,a>` (or `PhysicalExT` for
units, such as temperature, whose conversion equation needs a pre- and post-addition term, not just a scale
factor). The template parameters encode the unit's dimensionality - the exponents of mass, length, time,
temperature, and angle - so the compiler will not let you accidentally convert a length into a force. Rather
than construct these by hand, use the ready-made instances in `WBFL::Units::Measure` (e.g. `Measure::Feet`,
`Measure::Meter`, `Measure::KSI`) and the free function `Convert()`:

~~~
using namespace WBFL::Units;

Float64 valueInMeters = Convert(3.0, Measure::Feet, Measure::Meter); // 3 feet, expressed in meters
~~~

`Measure` is not an exhaustive, closed catalog - if it doesn't already have the unit you need but does have
the dimension type (e.g. `Length`, `Force`, `Pressure` - see PhysicalT.h for the full list), you can define
your own named instance directly:

~~~
Length Furlong(201.168, _T("furlong")); // 1 furlong = 201.168 m
Float64 valueInMeters = Convert(3.0, Furlong, Measure::Meter);
~~~

Unit Conversions with System Units
---------------------------------------------
Many components that perform engineering calculations require floating point numbers to be in a given system
of units. The problem, by way of example, is that Component A expects input and gives output in kip and foot
units, and Component B expects input and gives output in kilonewton and meter units. To build an application
that uses Component A and Component B, you would have to coordinate the unit conversions yourself. The WBFL
Units library solves this problem by allowing Components A and B to communicate with your application in the
system of units you specify.

System units are the most basic internal unit of measure of an application, managed by `WBFL::Units::System`
(e.g. KMS - kilogram, meter, second - or PFS - pound, foot, second). All other units of measure are derived
from the fundamental units of a unit system: for example, force is derived from mass, length, and time - in
the KMS system, a Newton is a kilogram-meter per second per second.

Values in your application are stored and manipulated in your chosen system of fundamental units. WBFL
components work with your system units: you provide values to these components in system units and retrieve
values in system units. If a component needs to perform calculations in a specific unit of measure, it uses
the system-unit conversion functions to get values in the required unit, performs the calculations, and
converts the results back to your unit system. This happens seamlessly to you.

~~~
using namespace WBFL::Units;

// Default system units are kg/m/sec/Celsius/radian
Float64 valueInSysUnits = ConvertToSysUnits(20.0, Measure::KSI);   // 20 KSI, expressed in Pa
Float64 valueInKsi      = ConvertFromSysUnits(valueInSysUnits, Measure::KSI); // back to 20.0

// Switch to a US customary system for a scope, then automatically restore the previous system units
{
   AutoSystem as;
   System::SetSystemUnits(Measure::KSlug, Measure::Feet, Measure::Second, Measure::Fahrenheit, Measure::Degree);
   // ... perform calculations in kip-foot-second units ...
} // system units are restored here, even if an exception is thrown
~~~

The system-unit conversion functions (`ConvertToSysUnits()`/`ConvertFromSysUnits()`) can be used in your
application as well, to convert values to and from any unit of measure without knowing what the current
system units are.

Display Unit Management
-----------------------
A well designed application allows users to work with either the US or SI system of units and to change the
unit system on the fly. Keeping track of the unit system and performing unit conversions can put a lot of
burden on the application developer. The WBFL Units library's `Library` and `IndirectMeasure` objects enable
your applications to seamlessly work with US and SI units. A `Library` supports the definition of multiple
named unit systems, though US and SI are generally all that is needed.

`IndirectMeasure` objects define groups of display units and assign a unit of measure to each group - for
example, a "SpanLength" group might display in meters for an SI profile and feet for a US profile. When
receiving input from the user interface or producing output to be displayed, your application doesn't need
to worry about the specific unit of measure: convert values to and from your system units and the indirect
unit of measure. Continuing the example, to display a span length to the user, convert it from your system
units using the current profile's `SpanLength` display unit:

~~~
using namespace WBFL::Units;

IndirectMeasure profile; // defaults to a reasonable SI display profile (SpanLength defaults to meters)
Float64 lengthInSysUnits = ConvertToSysUnits(100.0, Measure::Feet);

LengthTool tool(profile.SpanLength);
// AsString() converts to the profile's unit of measure and formats the number, but does not include the
// unit tag - combine it yourself if you want it in the displayed text.
std::_tstring displayText = tool.AsString(lengthInSysUnits) + _T(" ") + tool.UnitTag(); // "3.048e+01 m"
~~~

At the point of display, your application does not need to know the current unit system (US or SI) or what
the unit of measure for a span length needs to be for the end user - just look up a different named
`IndirectMeasure` from your `Library` when the user switches unit systems.

Dynamically-Defined Units
--------------------------
Everything above assumes the dimensionality of a unit of measure - the exponents of mass, length, time,
temperature, and angle that define, say, "Force" or "Pressure" - is known when the application is written,
since `PhysicalT`'s dimensionality is a compile-time template parameter. Occasionally an application needs to
define a unit type whose dimensionality isn't known until run time - for example, one read from a
configuration file or defined interactively by an end user. For this case, use `DynamicPhysical` (the
run-time counterpart of `PhysicalT`/`PhysicalExT`) and `DynamicUnitTypeManager` (a named catalog of
`DynamicPhysical` unit types and units, analogous to `Measure` but populated at run time instead of compile
time):

~~~
using namespace WBFL::Units;

DynamicUnitTypeManager mgr;
mgr.AddUnitType(_T("Velocity"), 0.0, 1.0, -1.0, 0.0, 0.0); // Length/Time, dimensionality unknown until run time
mgr.AddUnit(_T("Velocity"), _T("mps"), 1.0);
mgr.AddUnit(_T("Velocity"), _T("fps"), 0.3048);

Float64 valueInMps = Convert(60.0, mgr.GetUnit(_T("Velocity"), _T("fps")), mgr.GetUnit(_T("Velocity"), _T("mps")));
~~~

Prefer `PhysicalT`/`PhysicalExT` and the `Measure` catalog whenever a unit's dimensionality is known at
compile time - reach for `DynamicPhysical`/`DynamicUnitTypeManager` only when it isn't.
