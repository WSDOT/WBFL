WBFL Units {#WBFL_Units}
================
Introduction
------------

The WBFL Units library provides three basic services. It provides general unit conversions, conversion to and from an application's or component's internal system units and conversion and management of display units.

General Unit Conversions
------------------------
The WBFL Units library can be used to convert physical quantities between the Customary U.S. unit system and the International System of Units (SI). Unit conversions can also be performed within a unit system.

Unit Conversions with System Units
---------------------------------------------
Many components that perform engineering calculations require floating point numbers to be in a given system of units. The problem, by way of example is, Component A expects input and gives output in Kip and Feet units and Component B expects input and gives output in kilonewtons and meters units. To build an application that uses Component A and Component B, you will have to coordinate the unit conversions. The WBFL Units library solves this problem by allowing Components A and B to communicate with your applictaion in the system of units you specify.

System units are the most basic internal unit of measure of an application. Examples of system units are KMS (kilogram, meters, second) or PFS (pound, feet, second). All other units of measure are derived from the fundamental units of a unit system. For example, Force is a derived unit of mass, distance, and time. In the KMS system, force is Newton = kilogram meter per second per second. 

Values in your application are stored and manipulated in your chosen system set of fundamental units. The compoments of the WBFL work with your system units. You provide values to these components in system units and retreive vales in system units. If a component needs to perform certain calculations in specific units of measure, the component uses the system unit conversion functions to get values in the required unit of measure, performs the calculations, and coverts the results back to your unit system. This occurs seemlessly to you.

The system unit conversion functions can be used in your appliction as well to convert values to and from any unit of measure without knowing the specific unit of measure.

Display Unit Management
-----------------------
A well designed application allows users to work with either the US or SI system of units and to change the unit system on the fly. Keeping track of the unit system and performing unit conversions can put a lot of burden on the application developer. The WBFL Units library Library and IndirectMeasure objects enable your applications to seemlessly work with US and SI units. The Library object supports the definition of multiple unit systems, though US and SI are generally all that is needed.

IndirectMeasure objects defines groups of display units and assigns units of measure to each group. An example would be "LongLength" to represent something that is long, like the distance between points on a map. The US unit might be miles and the SI unit would be kilometers. When receiving input from the user interface or producing output to be displayed, your application doesn't need to worry about the specific units of measure. Convert values to and from the system units and the indirect unit of measure. Continuing the example, to display a distance to the user, convert it from your system units to the "LongLength" unit. At the point of display, your application does not need to know the current unit system (US or SI) or what the unit of measure of a long length value needs to be for the end user.
