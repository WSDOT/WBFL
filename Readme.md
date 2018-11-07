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
* Reporter - Report content definition
* ReportManager - Report management
* ReportManagerAgent - A wrapper on the ReportManager for use with the Agent/Broker architecture
* System - Provides common services such as object persistence, string manipulations, debugging and diagnostics.
* Units - Definition of units of measure
* UnitMgt and UnitServer - Management of a system of units (SI/US) and indirect display units
* Tools - Miscellaneous tools such as object persistence, progress monitors, and generic containers
* Transactions - Support for transactional based actions (Undo, Redo support)
* Types - System independent data type definitions

## Engineering Services Layer
The engineering services layer (ESL) provides libraries for building engineering applications. The libraries include
* COGO - Coordinate geometry modeling
* EngTools - Engineering tools such as Mohr's circle and biaxial strain plane modeling
* Fem2d - 2D, plane frame, finite element analysis
* GenericBridge - Genertic bridge modeling
* GenericBridgeTools - Tools for manipulating and extracting data from a generic bridge model
* GeometricPrimitives - Geometric primitives such as points, lines, and shapes
* GeomModel - Modeling of geometric shapes such as girder cross sections
* GraphicsLib - a library for graphing and plotting
* LBAM - Longitudinal Bridge Analysis Model, high level modeling of plane frame bridges for dead and live load analysis.
* Library - A general library system
* Loading - Bridge load modeling and management
* LRFD - Support procedures for the AASHTO LRFD Bridge Design Specification
* Material - Modeling of engineering materials such as concrete and steel
* Math - Math routines include equation modeling, root finding, and numerical integration
* RCCapacity - Nominal flexural capacity calculations for reinforced concrete elements (uniaxial and biaxial analysis)
* Roark - Closed form beam equations for moment, shear, and deflection based on Roark's Formulas for Stress and Strain
* Sections - Modeling of structural sections comprised of a variety of materials.
* Stability - Stability analysis precast concrete girders


## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

You will need to download and install the following projects before you can build the WBFL
* [Boost libraries](http://www.boost.org)
* [Code Synthesis XSD 3.3](https://codesynthesis.com/products/xsd/)

Define BOOSTDIR and XSDDIR environment variables for the location where the boost and code synthesis libraries are installed.

## Authors
This project is jointly developed by the Washington State and Texas Departments of Transportation

* **Richard Brice, PE** - [WSDOT](https://github.com/RickBrice)
* **Richard Pickings, PE** - [BridgeSight Inc](http://www.bridgesight.com)

## License

This project is licensed under the [Alternate Route Library Open Source License](http://www.wsdot.wa.gov/eesc/bridge/alternateroute/arlosl.htm)
