Custom Base Units {#WBFL_UnitServer_CustomBaseUnits}
=================

In addition to performing unit conversions, the UnitServer enables you to use any consistent set of "base units" and seemlessly pass values with a unit dependent object (assuming that object implements the ISupportUnitServer interface).

The code snippet below illustrates how to setup custom base units. For this example we want to work with base units of kips and feet. You cannot directly set kips as a base unit. Kip is a unit of force and force is a derived unit consisting of Mass, Length, and Time. Specificially, Force=Mass*Length/Time2.

We need to set the base units such that Mass, Length and Time produce units of kips. Let's break down kips to atomic units.

1 kip = 1000 lbf = 1000 slug * ft / s2 = 1000 lb * 32.2 ft / s2. (Recall that it takes 1 pound of force to accelerate 1 slug of mass accelerated at 1 ft/s2, or it takes 1 pound of force to accelerate 1 pound of mass accelerated at a rate equal to the Earth's gravitational pull [32.3 ft / s2 or 9.81 m / s2]).

From this, we see that we need to set the base unit for Mass to 1000 slug, or 1 kilo-slug. The WBFL Unit System has a built in mass unit for just this purpose. This unit is "kslug".

The base units would be set like this:

unitServer.SetBaseUnits("kslug","ft","sec","F","deg")

A simple conversion of 12000 lbf-in to base units would produce 1.0 k-ft

value = unitServer.UnitConvert.ConvertToBaseUnits(12000,"lbf-ft")

value is equal to 1.0 kip-ft

Note that when converting units of mass, the fundimental unit for mass is 1000 slug, or 1 kilo-slug. So if we do the following conversion:

value = unitServer.UnitConvert.ConvertToBaseUnits(1.0,"slug")

value will be equal to 0.001 kilo-slug.

Similarly, for base units for kilo-Newtons and meters, you would need to use a mass unit of 1000 kg, or 1 Mg (mega-gram). The base units would be set like this:

unitServer.SetBaseUnits("Mg","m","sec","C","rad")

The WBFL UnitServer offers several odd units of mass so that you can work with base units that engineers are familar with. The table below summarizes the parameters that need to be supplied to SetBaseUnits in order to acheive the desired results.

Desired Base Units | Mass | Length | Time | Temperature | Angle 
-------------------|------|--------|------|-------------|------
N, Pa | kg | m | s | C | rad
kN, kPa | Mg | m | s | C | rad
kip,ksf | kslug | ft | s | F | deg
kip,ksi | 12kslug | in | s | F | deg
lb,psf | slug | ft | s | F | deg
lb,psi | 12slug | in | s | F | deg
