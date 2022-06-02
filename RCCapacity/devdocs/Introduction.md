WBFL RCCapacity {#WBFL_RCCapacity}
========================
This library provides services for computing the section capacity of reinforced and prestressed concrete beams and columns. The objects implemented in this library are OLE Automation Compatible. This means you can use the services of this library from Visual Basic, Visual Basic for Applications, Visual C++ and Java.

This library is comprised of two categories of classes. One category focuses on the capacity of symmetric concrete beams subjected to uniaxial bending. The other focuses on general analysis biaxial bending analysis.

Four methods of uniaxial capacity analysis are provided for basic concrete T-beam sections. These methods are:
* AASHTO LRFD Equations
* AASHTO Standard Specification Equations
* PCI Bridge Design Manual Strain Compatibility Method
* Nonlinear Strain Compatibility Method

These analysis methods where developed to investigate the validity of flexural strength prediction models in various design references. The results of the investigation are published in "Flexural Strength of Reinforced and Prestressed Concrete T-Beams", Seguirant, Brice, Khaleghi, PCI Journal, Jan-Feb 2005, pp44-73.

The biaxial analysis objects offer capacity methods including:
* General Section Analysis (analysis based on a fixed strain plane)
* Moment Capacity Analysis (iterates on neutral axis location until the internal and external loads are in equilibrium)
* Moment Curvature Analysis (finds the equilibrium condition for varying degree of curvature)
* Axial Load Interaction Analysis (computes the values for a P-M interaction diagram)
* Moment Interaction Analysis (computes the values for a Mx-My interaction diagram)

The general section model and biaxial analysis is based on "Ultimate Strength Analysis of Arbitrary Cross Sections Under Biaxial Bending and Axial Loads by Fiber Model and Curvilinear Polygons", Charalampakis, A., and Koumousis, V., 5th GRACM International Congress on Computational Mechanicas, Limassol, June 29 - July 1, 2005. 

Solutions can be optimized by using variable depth fibers defined by a slice growth factor.

* \subpage WBFL_RCCapacity_SliceGrowthFactor

Several material models are also provided in this library including:
* Unconfined Concrete
* Confined Concrete (Mander Model)
* Elasto-Plastic Rebar
* Strain Hardened Rebar
* Prestressing Strand - Power Formula

Using the library is quite simple. The basic concept can be expressed in the following line of pseudo-code:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
solution = solver.Solve(problem);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The problem is a description of a section to be analyzed. The solver.Solve represents a solver object executing its Solve method to produce a solution. The solution, moment capacity, and other related results, are encapsualated in a solution object.

Units
------
Several of the components in this library depend upon specific units of measure to function properly. For example, the UnconfinedConcrete object uses a formula that requires concrete strengths to be in KSI. To allow you to use whatever units of measure you like, the unit dependent components allow you to specify a UnitServer object. All input and output from this library will be in your units of measure. The library will use the UnitServer to convert from your units to the units that are required for specific formulas. The following objects implement the ISupportUnitServer interface: RCBeam, RCBeam2, UnconfinedConcrete, and PSPowerFormula.

If the WBFL default units of kilogram, meter, second, centigrade, and radians is adequate for your application, then there is nothing you need to do. However, if you wish to work with different base units you must create and configure a UnitServer and supply that unit server to the unit dependent objects. See the WBFL Unit Server documentation for information on configuring a unit server.

If you are using your own material models for concrete, pretensioning steel, and mild reinforcement, you will have to configure them with the appropriate unit server as well.
