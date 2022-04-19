# Washington Bridge Foundation Libraries (WBFL)

The Washington Bridge Foundation Libraries (WBFL) provides a foundation upon which to build bridge engineering software.

The WBFL consists of the Application Services Layer and the Engineering Services Layer.

## Application Services Layer
The application services layer (ASL) provides libraries for building applications. The libraries include
* Core - Core features of the Agent/Broker architecture
* DManip - GUI direct manipulation framework
* DManipTools - Tools for making use of the DManip library easier
* EAF - Engineering Application Framework
* GraphManager - A ready to use graph manager
* GraphManagerAgent - A wrapper on the GraphManager for use with the Agent/Broker architecture
* MFCTools - Extensions to the Microsoft Foundation Class (MFC) library
* \subpage WBFL_Reporter - Report content definition
* ReportManager - Report management
* ReportManagerAgent - A wrapper on the ReportManager for use with the Agent/Broker architecture
* System - Provides common services such as object persistence, string manipulations, debugging and diagnostics.
* Units - Definition of units of measure
* UnitMgt and \subpage WBFL_UnitServer - Management of a system of units (SI/US) and indirect display units
* \subpage WBFL_Tools - Miscellaneous tools such as object persistence, progress monitors, and generic containers
* Transactions - Support for transactional based actions (Undo, Redo support)
* Types - System independent data type definitions

## Engineering Services Layer
The engineering services layer (ESL) provides libraries for building engineering applications. The libraries include
* \subpage WBFL_COGO - Coordinate geometry modeling
* EngTools - Engineering tools such as Mohr's circle and biaxial strain plane modeling
* Fem2d - 2D, plane frame, finite element analysis
* GenericBridge - Generic bridge modeling
* GenericBridgeTools - Tools for manipulating and extracting data from a generic bridge model
* GeometricPrimitives - Geometric primitives such as points, lines, and shapes
* \subpage WBFL_GeomModel - Modeling of geometric shapes such as girder cross sections
* \subpage WBFL_Graphing - a library for graphing and plotting
* LBAM - Longitudinal Bridge Analysis Model, high level modeling of plane frame bridges for dead and live load analysis.
* Library - A general library system
* Loading - Bridge load modeling and management
* LRFD - Support procedures for the AASHTO LRFD Bridge Design Specification
* Material - Modeling of engineering materials such as concrete and steel
* Math - Math routines include equation modeling, root finding, and numerical integration
* \subpage WBFL_RCCapacity - Nominal flexural capacity calculations for reinforced concrete elements (uniaxial and biaxial analysis)
* Roark - Closed form beam equations for moment, shear, and deflection based on Roark's Formulas for Stress and Strain
* \subpage WBFL_Stability - Stability analysis precast concrete girders

## COM Wrappers
To enable more widespread usage of the WBFL, some services are implemented with a Component Object Model (COM) wrapper. These libraries include
* \subpage WBFL_Geometry - Geometric primitives such as points, lines, and shapes
* Sections - Modeling of structural sections comprised of a variety of materials.


## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

You will need to download and install the following projects before you can build the WBFL
* [Boost libraries](http://www.boost.org)
* [Code Synthesis XSD 3.3](https://codesynthesis.com/products/xsd/)

Define BOOSTDIR and XSDDIR environment variables for the location where the boost and code synthesis libraries are installed.

Clone the repository into **drive letter**:/ARP/ and create an environment variable ARPDIR to this folder.

#### Objective Grid
WBFL forms the basis of the BridgeLink application suite. If your intent is to build the BridgeLink suite, you will need the Stingray ObjectiveGrid library from Preforce software. If you do not have ObjectiveGrid,
you can still build the BridgeLink suite by following these steps:

1. Open WBFL/Include/WBFLGrid.h and uncomment the `#define _NOGRID macro'
2. Create a C:/Program Files/Preforce/Stingray Stuido 2021.1/Src folder
3. Copy the dummy props file WBFL/SS-X64-PropSheet16.props into that folder.

This will permit you to build the code. The substitute grid code does not simulate grid functionality. Dialogs and windows that use ObjectiveGrid are likely to crash the application when using the substitute code.

The no-grid option is not well maintained. If you find that some methods are missing, please stub them out and submit a pull request.

## Authors
This project is jointly developed by the Washington State and Texas Departments of Transportation

* **Richard Brice, PE** - [WSDOT](https://github.com/RickBrice)
* **Richard Pickings, PE** - [BridgeSight Inc](http://www.bridgesight.com) for TxDOT

## License

This project is licensed under the [Alternate Route Library Open Source License](http://www.wsdot.wa.gov/eesc/bridge/alternateroute/arlosl.htm)
