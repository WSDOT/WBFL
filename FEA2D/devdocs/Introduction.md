# FEA2D (2D Finite Element Analysis) {#WBFL_FEA2D}

FEA2D is a low-level, high-performance native C++ component for 2D plane-frame analysis. It has no ATL/COM dependency anywhere in its implementation or public interface - it is a plain, self-contained C++ library, built entirely on C++ classes and references.

The interfaces should be intuitive for anyone who has used a general-purpose finite element program like GT-STRUDL or NASTRAN, though the feature set is much narrower than one of those comprehensive engines.

## Analysis Features

FEA2D supports a wide array of features for modeling 2D linear-elastic frames. Both axial and bending behaviors are modeled; shear deformation is not. The main features are:

* 2D linear-elastic prismatic beam elements (`Member`)
* Model size is limited only by available memory
* Member end releases for moment (`MemberReleaseType::Mz`) and axial force (`MemberReleaseType::Fx`)
* An unlimited number of load cases (`Loading`)
* Many load types:
  * Concentrated loads applied to joints (`JointLoad`)
  * Concentrated loads applied along members (`PointLoad`)
  * Trapezoidally distributed loads applied to members (`DistributedLoad`)
  * Axial and curvature strains applied to members (`MemberStrain`)
  * Joint displacements / support settlements (`JointDisplacement`)
* An unlimited number of analysis points (`POI`) along members - this eliminates the need to add joints purely to get results at a particular location (see @ref WBFL_FEA2D_Performance)
* Native (non-COM) file persistence of model data, via `WBFL::System::IStructuredSave`/`IStructuredLoad`

It's also worth noting the features this engine deliberately does **not** support:

* Automatic bandwidth reduction - you have to number your own joints efficiently (see @ref WBFL_FEA2D_Performance)
* Master-slave relationships
* Plate and shell-type elements
* A fine-grained, per-mutation event model (fine for GUI programs, costly for performance) - see @ref WBFL_FEA2D_On_Demand_Computation
* Non-prismatic members
* Zero-size spring elements
* Inclined supports

## Getting Started

@subpage WBFL_FEA2D_Object_Model

@subpage WBFL_FEA2D_Using_this_library

@subpage WBFL_FEA2D_On_Demand_Computation

@subpage WBFL_FEA2D_Sign_Conventions

@subpage WBFL_FEA2D_Performance
