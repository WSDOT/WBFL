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
* Simplified circular column P-M interaction diagram calculator
* Simplified rectangular T-beam moment capacity calculator (WBFL::RCSection::RCSolver), for cases where the full fiber-based analysis of a GeneralSection is more than what's needed

The general section model and biaxial analysis is based on "Ultimate Strength Analysis of Arbitrary Cross Sections Under Biaxial Bending and Axial Loads by Fiber Model and Curvilinear Polygons", Charalampakis, A., and Koumousis, V., 5th GRACM International Congress on Computational Mechanics, Limassol, June 29 - July 1, 2005. 

Using the library is quite simple. The basic concept can be expressed in the following line of pseudo-code:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
solution = solver.Solve(problem);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The problem is a description of a section to be analyzed. The solver.Solve represents a solver object executing its Solve method to produce a solution. The solution, moment capacity, and other related results, are encapsulated in a solution object.

A minimal but complete example - a rectangular tied column with four corner bars, analyzed for
moment capacity about a fixed compression strain of 0.003 at the extreme compression fiber:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
using namespace WBFL::RCSection;

auto concrete = std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Concrete"), 4.0);
auto rebar    = std::make_shared<WBFL::Materials::RebarModel>(_T("Rebar"), 60.0, 29000.0, 0.11);

WBFL::Geometry::Rectangle beam;
beam.SetHeight(24.0);
beam.SetWidth(12.0);

WBFL::Geometry::GenericShape bar1(1.0, WBFL::Geometry::Point2d( 4,  10));
WBFL::Geometry::GenericShape bar2(1.0, WBFL::Geometry::Point2d(-4,  10));
WBFL::Geometry::GenericShape bar3(1.0, WBFL::Geometry::Point2d(-4, -10));
WBFL::Geometry::GenericShape bar4(1.0, WBFL::Geometry::Point2d( 4, -10));

auto section = std::make_shared<GeneralSection>();
section->AddShape(_T("Beam"), beam, concrete, nullptr, nullptr, 1.0, true);
section->AddShape(_T("Bar 1"), bar1, rebar, nullptr, nullptr, 1.0);
section->AddShape(_T("Bar 2"), bar2, rebar, nullptr, nullptr, 1.0);
section->AddShape(_T("Bar 3"), bar3, rebar, nullptr, nullptr, 1.0);
section->AddShape(_T("Bar 4"), bar4, rebar, nullptr, nullptr, 1.0);

MomentCapacitySolver solver;
solver.SetSlices(10);
solver.SetSection(section);

// angle = 0.0, compression on top; k_or_ec = -0.003 fixed strain at the extreme compression fiber
auto solution = solver.Solve(0.0, 0.0, -0.003, 0.0, MomentCapacitySolver::SolutionMethod::FixedCompressionStrain);

Float64 Mn = solution->GetMx(); // resultant moment about the horizontal centroidal axis
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Solutions can be optimized by using variable depth fibers defined by a slice growth factor.

Related Topics
---------------
* \subpage WBFL_RCSection_SolutionMethod - what the `SolutionMethod` parameter controls, and the moment/force sign convention used throughout this library
* \subpage WBFL_RCSection_SliceGrowthFactor

Internals
----------
The Internals topic describes some of the internal implementation details and aims to help future developers understand how this library is designed and implemented.

* \subpage WBFL_RCSection_Internals

