Reinforced Concrete Section Analysis {#WBFL_RCSection}
========================================================
This library provides the WBFL Engineering Services Layer with concrete section analysis services for reinforced and prestressed concrete beams and columns

The analysis services including:
* General Section Analysis (computes P, Mx, and My for a given set of strains)
* Moment Capacity Analysis (iterates the location of the neutral axis until P_external = P_internal)
* Moment Curvature Analysis (finds the equilibrium moment capacity for varying degree of curvature)
* Axial Load Interaction Analysis (computes the values for a P-M interaction diagram for a specified direction of the neutral axis)
* Moment Interaction Analysis (computes the values for a Mx-My interaction diagram for a specified value of axial force)
* Cracked Section Analysis (computes cracked section properties)
* Utility to build simple circular and rectangular column sections
* Simplied circular column P-M interaction diargram calculator

The general section model and biaxial analysis is based on "Ultimate Strength Analysis of Arbitrary Cross Sections Under Biaxial Bending and Axial Loads by Fiber Model and Curvilinear Polygons", Charalampakis, A., and Koumousis, V., 5th GRACM International Congress on Computational Mechanicas, Limassol, June 29 - July 1, 2005. 

Using the library is quite simple. The basic concept can be expressed in the following line of pseudo-code:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
solution = solver.Solve(problem);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The problem is a description of a section to be analyzed. The solver.Solve represents a solver object executing its Solve method to produce a solution. The solution, moment capacity, and other related results, are encapsualated in a solution object.

Solutions can be optimized by using variable depth fibers defined by a slice growth factor.

* \subpage WBFL_RCSection_SliceGrowthFactor

Internals
----------
The Internals topic describes some of the internal implementation details and aims to help future developers understand how this library is designed and implemented.

* \subpage WBFL_RCSection_Internals

