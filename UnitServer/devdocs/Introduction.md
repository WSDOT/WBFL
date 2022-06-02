WBFL Unit Server {#WBFL_UnitServer}
=========

Introduction
-------------
The WBFL Unit Server provides three basic services. It provides general unit conversions, conversion to and from an application's or component's base units, and conversion and management of display units.

### General Unit Conversions ###
The WBFL Unit Server can be used to convert physical quantities between the Customary U.S. unit system and the International System of Units (SI). Unit conversions can also be performed within a unit system.

### Unit Conversions with Application Base Units ###
In today's world of component based programming, one of the primary goals is to create solutions with reusable components. Many of the components that perform bridge engineering calculations require floating point numbers to be in a given system of units. The problem, by way of example is, Component A expects input and gives output in Kip and Feet units and Component B expects input and gives output in kilonewtons and meters units. To build an application that uses Component A and Component B, you will have to coordinate the unit conversions. The WBFL Unit Server solves this problem by allowing Component A and B to communicate with you in the system of units you specify.

Base units are the most basic internal unit of measure of an application. All values are stored and manipulated in these units of measure. Components may require values in a specific set of units to function properly. The components throught the WBFL are designed to work with consistent base units whenever possible. However, when this is not possible, the components implement the ISupportUnitSystem and ISupportDocUnitSystem interfaces. This puts the burden on the component to deal with unit conversions. You simple assign your unit system object to the component, provide input values in your base units, and get output values in your base unit. The component doesn't need to know what base units the application uses. Unit conversions are handleded seemlessly through the UnitSytem object.

### Display Unit Management ###
At some point, a user will be entering numbers into your program and viewing output. A well designed application will allow the user to work with either the US or SI system of units and to change the unit system on the fly. The WBFL Display Unit Manager enables your code that reads input and writes output to do so seemlessly. The display unit manager defines groups of display units and assigns units of measure to each group. An example would be "LongLength" to represent something that is long, like the distance between points on a map. The US unit might be *miles* and the SI unit would be *kilometers*. All you have to do is format your value from base units to a formatted unit string in "LongLength" units. The display unit manager will take care of the rest. The same is true for input. Supply your input value in "LongLength" units to the display unit manager and it will be converted to the application's base units. Some objects provide user interface elements. These objects can seemlessly convert values between base units and display units without knowing precise units of measure.

General Concepts
----------------
There are several general concepts used consistently throughout the WBFL Unit Server library. The following topics explain them.

\subpage WBFL_UnitServer_ObjectModel

\subpage WBFL_UnitServer_DisplayUnits

\subpage WBFL_UnitServer_Examples

\subpage WBFL_UnitServer_UnitConversions

\subpage WBFL_UnitServer_UnitModes

\subpage WBFL_UnitServer_UnitServer

\subpage WBFL_UnitServer_UnitSystems

\subpage WBFL_UnitServer_DefaultUnitTypes

\subpage WBFL_UnitServer_RuntimeErrors

\subpage WBFL_UnitServer_CustomBaseUnits


