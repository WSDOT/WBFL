///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
// Copyright © 1999-2019  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_REINFORCEDCONCRETE_CAPACITYPROBLEM_H_
#define INCLUDED_REINFORCEDCONCRETE_CAPACITYPROBLEM_H_
#pragma once

// SYSTEM INCLUDES
//
#include <map>

#include <ReinforcedConcrete\ReinfConcExp.h>
#include <System\Exception.h>
#include <GeometricPrimitives\GeometricPrimitives.h>
#include <GeomModel\CompositeShape.h>
#include <Engtools\BiaxialBeamStrain.h>

// FORWARD DECLARATIONS
//
class matConcrete;
class matMetal;
class matPsStrand;
class matMildSteel;
class gmIShape;
class gmCompositeShape;
class gpLine2d;
class grlibPointMapper;
class matYieldStressStrainCurve;
class rcaConcreteElement;
class rcaReinforcementElement;

// MISCELLANEOUS
//

struct REINFCONCCLASS rcaReinforcementForceDetails
{
   Float64 Ab;
   gpPoint2d LocBar;
   Float64 ConcreteStrain;
   Float64 InitialStrain;
   Float64 BarStrain;
   Float64 BarStress;
   Float64 BarForce;

#if defined _DEBUG
   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   void Dump(dbgDumpContext& os) const;
#endif // _DEBUG
};

struct REINFCONCCLASS rcaSectionForceDetails
{
   Float64 Fz;
   Float64 Mx;
   Float64 My;
   Float64 CompForce;
   gpPoint2d LocCompForce;
   Float64 TensForce;
   gpPoint2d LocTensForce;
   gpPoint2d PlasticCentroid;
   gpLine2d NeutralAxis;
   Float64 Beta1;

   Float64 Pc, Mxc, Myc;
   Float64 Pt, Mxt, Myt;

   Float64 CompArea;
   Float64 EffCompArea;

   std::vector<rcaReinforcementForceDetails> ReinforcementForceDetails;

#if defined _DEBUG
   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   void Dump(dbgDumpContext& os) const;
#endif // _DEBUG
};

/*****************************************************************************
CLASS 
   rcaXRcCapProbError

   Exception class for solver errors. Derived from sysXBase.


DESCRIPTION
   Exception class for solver errors. Derived from sysXBase.

LOG
   rdp : 01.20.1998 : Created file
*****************************************************************************/

class REINFCONCCLASS rcaXRcCapProbError : public sysXBase
{
public:
   // Define a common tolerance for solution schemes to work with. This tolerance
   // is for positioning of the neutral axis.
   enum Reason { MaterialNotFound,    // The specified material could not be found
                 ElementNotFound,     // The specified element could not be found
                 InvalidProblemRep    // The model is invalid
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.  Supply the file and line number where the 
   // exception occured.
   rcaXRcCapProbError(Reason reason, LPCTSTR file, Int16 line);

   //------------------------------------------------------------------------
   // Copy constructor
   rcaXRcCapProbError(const rcaXRcCapProbError& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rcaXRcCapProbError();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rcaXRcCapProbError& operator = (const rcaXRcCapProbError& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Throw
   // Implements the Throw() interface
   void Throw() const;

   //------------------------------------------------------------------------
   // GetReason
   // Returns the reason the solver failed in int format to satisfy base class
   // rcaXRcCapProbError::Reason 
   Int32 GetReason() const;

   //------------------------------------------------------------------------
   // GetReasonCode
   // Returns the reason the solver failed.
   // rcaXRcCapProbError::Reason 
   Reason GetReasonCode() const;

   //------------------------------------------------------------------------
   // GetErrorMessage
   // Overrides the standard error message with the error messages listed below
   //    Reason                Message
   // MaterialNotFound	    "Material not found"
   // ElementNotFound	    "Element not found"
   // InvalidProblemRep	    "The problem representation is invalid"
   void GetErrorMessage(std::_tstring* pMsg,Int32 reserved) const;


   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const rcaXRcCapProbError& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const rcaXRcCapProbError& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Reason m_Reason;
   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Default constructor
   rcaXRcCapProbError();
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();
   void Clean();

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

/*****************************************************************************
CLASS 
   rcaCapacityProblem

   Abstract base class for concrete section capacity problems using a uniform
   stress block approach.  This class is subclassed for the Whitney and
   Naaman analysis methods. 


DESCRIPTION
   Abstract base class for concrete section capacity problems using a uniform
   stress block approach.  This class is subclassed for the Whitney and
   Naaman analysis methods. 

LOG
   rdp : 01.19.1998 : Created file
*****************************************************************************/

class REINFCONCCLASS rcaCapacityProblem
{
public:
   static const Float64 PositionTolerance;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rcaCapacityProblem();

   //------------------------------------------------------------------------
   // Copy constructor
   rcaCapacityProblem(const rcaCapacityProblem& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rcaCapacityProblem();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rcaCapacityProblem& operator = (const rcaCapacityProblem& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // AddConcrete
   // Adds a concrete material to the problem. Returns a key that can be used
   // to get it later.
   CollectionIndexType AddConcrete(const matConcrete& concrete);

   //------------------------------------------------------------------------
   // GetConcrete
   // Gets a concrete material from the problem.
   const matConcrete& GetConcrete(CollectionIndexType concreteIdx) const;

   //------------------------------------------------------------------------
   // GetNumConcretes
   // Gets number of concrete materials in the problem. Can use this to iterate
   // around GetConcrete.
   CollectionIndexType GetNumConcretes() const;

   //------------------------------------------------------------------------
   // SetBaseConcreteMaterial
   // Sets the concrete material for which n factors are based on.
   // (defaults to Material 0)
   void SetBaseConcreteMaterial(CollectionIndexType concreteIdx);
   CollectionIndexType GetBaseConcreteMaterial() const;

   //------------------------------------------------------------------------
   // AddMildSteel
   // Adds a mild steel material to the problem.  Calls 
   // DoCreateMildSteelMaterialModel() to create the stress strain curve and 
   // then stores the material model in a library.  Returns a key which can be
   // used to identify this material when creating elements.
   CollectionIndexType AddMildSteel(const matMetal& steel);

   //------------------------------------------------------------------------
   // AddStrand
   // Adds a strand material to the problem.  Calls 
   // DoCreateStrandMaterialModel() to create the stress strain curve and 
   // then stores the material model in a library.  Returns a key which can
   // be used to identify this material when creating elements.
   CollectionIndexType AddStrand(const matPsStrand& strand);

   //------------------------------------------------------------------------
   // RemoveMaterial
   // Removes a material (concrete, mild steel,  or strand) from the problem.
   // Returns true if the material was successfully removed,  otherwise false.
   bool RemoveMaterial(CollectionIndexType id);

   //------------------------------------------------------------------------
   // MildSteelMaterialCount
   // Returns the number of mild steel materials in the problem.
   CollectionIndexType MildSteelMaterialCount() const;

   //------------------------------------------------------------------------
   // StrandMaterialCount
   // Returns the number of strand materials in the problem.
   CollectionIndexType StrandMaterialCount() const;

   //------------------------------------------------------------------------
   // MaterialCount
   // Returns the total number of materials in the problem.
   CollectionIndexType MaterialCount() const;

   //------------------------------------------------------------------------
   // AddConcreteElement
   // Adds a concrete element in the problem.  Returns a key which can be 
   // used to identify this element.  Throws a rcaXRcCapProbError exception
   // with reason code MaterialNotFound, if the element could not be created.
   // This version allows specification of the n factor explicitely - real n from material is not used
   CollectionIndexType AddConcreteElement(const gmIShape& shape, CollectionIndexType concreteKey, Float64 nFactor);

   //------------------------------------------------------------------------
   // AddConcreteElement
   // Adds a concrete element in the problem.  Returns a key which can be 
   // used to identify this element.  Throws a rcaXRcCapProbError exception
   // with reason code MaterialNotFound, if the element could not be created.
   // For this version, the n factor is calculated from the concrete materials in the model.
   CollectionIndexType AddConcreteElement(const gmIShape& shape, CollectionIndexType concreteKey);

   //------------------------------------------------------------------------
   // AddReinforcementElement
   // Adds a reinforcement element in the problem.  Returns a key which can 
   // be used to identify this element.  Throws a rcaemXRcCapProbError 
   // exception,  with reason code MaterialNotFound,  if the element could 
   // not be created. The initial strain should be equal to the difference 
   // between the strain in the concrete and the strain in the rebar element
   // after losses have occurred.
   CollectionIndexType AddReinforcementElement(const gmIShape& shape, CollectionIndexType matId, Float64 initStrain = 0.);

   //------------------------------------------------------------------------
   // RemoveElement
   // Removes an element from the problem.  Returns true if the element was 
   // successfully removed,  otherwise false.
   bool DestroyElement(CollectionIndexType id);

   //------------------------------------------------------------------------
   // ConcreteElementCount
   // Returns the number of concrete elements in the problem.
   CollectionIndexType ConcreteElementCount() const;

   //------------------------------------------------------------------------
   // ReinforcementElementCount
   // Returns the number of reinforcement elements in the problem.
   CollectionIndexType ReinforcementElementCount() const;

   //------------------------------------------------------------------------
   // ElementCount
   // Returns the total number of elements in the problem.
   CollectionIndexType ElementCount() const;

   //------------------------------------------------------------------------
   // SetNeutralAxisLocation
   // Sets the location and orientation of the neutral axis.  The compression
   // side is always on the left side of the line.
   // The neutral axis line is described in the same coordinate space as the
   // cross section.
   void SetNeutralAxisLocation(const gpLine2d& line);

   //------------------------------------------------------------------------
   // GetNeutralAxisLocation
   // Retrieves the location and orientation of the neutral axis.
   void GetNeutralAxisLocation(gpLine2d* line) const;

   //------------------------------------------------------------------------
   // SetMaxCompressiveStrain
   // Sets the maximum compressive strain at the farthest concrete compressive
   // fiber in the section. This value is -0.003 by default.
   void SetMaxCompressiveStrain(Float64 strain);

   //------------------------------------------------------------------------
   // GetMaxCompressiveStrain
   // Returns the maximum compressive strain at the farthest concrete 
   // compressive fiber in the section.
   Float64 GetMaxCompressiveStrain() const;

   //------------------------------------------------------------------------
   // GetCompressionBlockBoundary
   // Gets the location of the compression block boundary.  The first form 
   // returns the location of the compression block boundary as an offset 
   // from the neutral axis.  The second form returns two points on the 
   // compression block boundary line. The compression block is to the 
   // left of the boundary line.
   Float64 GetCompressionBlockBoundary() const;
   void GetCompressionBlockBoundary(gpLine2d* line) const;

   //------------------------------------------------------------------------
   // GetFurthest Distance
   // Returns the farthest distance, measured normal and to the left of the neutral axis
   // line to the point on the section where the maximum compressive strain
   // is desired. This value is calculated by DoCalculateFurthestDistance and
   // set by SetFurthestDistance.
   // By default, this point is the farthest out location on all
   // concrete shapes in the section
   Float64 GetFurthestDistance() const;

   //------------------------------------------------------------------------
   // GetStrain
   // Returns the strain at the given point.  In the third form,  the strain 
   // at the centroid of the element identified by elId is returned.  If the 
   // specified element could not be found,  a rcaemXRcCapProbError exception,
   // with reason code ElementNotFound,  will be thrown.
   Float64 GetStrain( const gpPoint2d& p ) const;
   Float64 GetStrain( Float64 x, Float64 y) const;
   Float64 GetStrain( CollectionIndexType elId ) const;

   //------------------------------------------------------------------------
   // GetSectionForcesEx
   // Returns the axial force and moments, with respect to the plastic 
   // centroid,  on the section for its current neutral axis position.  A 
   // rcaemXRcCapProbError exception,  with reason code InvalidModel,  
   // will be thrown if the section forces can not be determined.
   void GetSectionForcesEx(Float64* pFz,
                           Float64* pMx,
                           Float64* pMy,
                           Float64* compRes, gpPoint2d* compLoc,
                           Float64* tensRes, gpPoint2d* tensLoc) const;
   void GetSectionForcesEx(rcaSectionForceDetails* pDetails) const;

   //------------------------------------------------------------------------
   // GetSectionForces
   // Returns the axial force and moments, with respect to the plastic 
   // centroid,  on the section for its current neutral axis position.  A 
   // rcaemXRcCapProbError exception,  with reason code InvalidModel,  
   // will be thrown if the section forces can not be determined.
   void GetSectionForces(Float64* pFz,
                         Float64* pMx,
                         Float64* pMy) const;

   //------------------------------------------------------------------------
   // GetTensileCapacity()
   // Computes the ultimate tensile axial force which can be applied to the 
   // section. This capacity is determined by assuming all of the reinforcement
   // has yielded. The resultant tensile force occurs at the plastic centroid
   // of the section.  If the section is unsymetrical moments will exist.
   void GetTensileCapacity(Float64* pPt,Float64* pMxt,Float64* pMyt) const;

   //------------------------------------------------------------------------
   // GetCompressiveCapacity
   // Returns the ultimate compressive axial force which can be applied to 
   // the section. This capacity is determined by applying a uniform 
   // compressive strain equal to .003 to the model.  The resultant compressive
   // force occurs at the plastic centroid of the section. If the section
   // is unsymetrical moments will exist.
   //
   // A rcaXRcCapProbError exception,  with reason code InvalidModel,  will be
   // thrown if the section forces can not be determined.
   void GetCompressiveCapacity(Float64* pPc,Float64* pMxc,Float64* pMyc) const;

   //------------------------------------------------------------------------
   // GetPlasticCentroid
   // Returns the location of the plastic centroid (defined as the center of 
   // force when a uniform compressive strain of 0.003 is applied to the model).
   // A rcaemXRcCapProbError exception,  with reason code InvalidModel,  will be
   // thrown if the plastic centroid can not be determined.
   gpPoint2d GetPlasticCentroid() const;

   //------------------------------------------------------------------------
   // GetClippedConcreteArea
   // Returns the area of concrete on the given side of the clipLine. This area
   // is multiplied by the N factor of all concretes in the model.
   Float64 GetClippedConcreteArea(const gpLine2d& clipLine, gpLine2d::Side) const;

   //------------------------------------------------------------------------
   // GetClippedConcreteArea
   // Returns the area of concrete on the given side of the clipLine for the given
   // concrete material.
   // This area is multiplied by the N factor of all concretes in the model.
   Float64 GetClippedConcreteArea(CollectionIndexType concreteIdx, const gpLine2d& clipLine, gpLine2d::Side) const;
   
   //------------------------------------------------------------------------
   // GetConcreteArea
   // Returns the area of concrete. This area is multiplied by the N factor of
   // all concretes in the model.
   Float64 GetConcreteArea() const;

   //------------------------------------------------------------------------
   // GetBeta1
   // Pure abstract call to get Beta1 for the current nuetral axis configuration
   // for the model. This can be based on an average, or a specific material 
   // depending on the implementation
   virtual Float64 GetBeta1() const = 0;

   //------------------------------------------------------------------------
   // Returns the area on the compression side of the neutral axis.
   // This area is adjusted with the N factors of the concrete elements
   Float64 GetCompressionArea() const;

   //------------------------------------------------------------------------
   // Returns the area on the compression side of the neutral axis, and above
   // the compresison block boundary.
   // This area is adjusted with the N factors of the concrete elements
   Float64 GetEffectiveCompressionArea() const;

   //------------------------------------------------------------------------
   // GetBoundingBox
   // Returns the bounding box of the problem.
   gpRect2d GetBoundingBox() const;

   //------------------------------------------------------------------------
   // Draw
   // Draws the problem on the given device context using the given mapper.
   void Draw(HDC hDC, const grlibPointMapper& mapper) const;


   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST


protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // DoCalculateCompressionBlockBoundary
   // Sets the location of the compression block boundary.  The offset is 
   // measured normal to the neutral axis line.
   virtual Float64 DoCalculateCompressionBlockBoundary() = 0;

   //------------------------------------------------------------------------
   // DoCalculateFurthestDistance
   // Calculates the farthest distance, measured normal and to the left of the
   // neutral axis line to the point on the section where the maximum 
   // compressive strain is specified. 
   // By default, this point is the distance to the farthest out location on
   // all concrete shapes in the section
   virtual Float64 DoCalculateFurthestDistance();

   //------------------------------------------------------------------------
   // OnNeutralAxisChanged
   // Pure abstract function to calculate the location of the compression 
   // block boundary. Implement this function to determine the compression 
   // block location for the Whitney or Naaman approach.  Returns the offset
   // measured normal to the neutral axis line.
   // Called by SetNeutralAxisLocation() when ever the neutral axis changes.  
   // This method does calls DoCalculateCompressionBlockBoundary() and then 
   // SetCompressionBlockBoundary() by default.
   virtual void OnNeutralAxisChanged();

   //------------------------------------------------------------------------
   // DoCreateMildSteelMaterialModel
   // Called by AddMildSteel() when a steel material is added to the problem.
   // This is a factory method that creates a stress strain curve for mild steel.
   // The default behavior of this method is to create a matBilinearCurve 
   // material model.
   virtual matYieldStressStrainCurve* DoCreateMildSteelMaterialModel(const matMetal& steel);

   //------------------------------------------------------------------------
   // DoCreateStrandMaterialModel
   // Called by AddStrand() when a strand material is added to the problem.  
   // This is a factory method that creates a stress strain curve for prestress
   // strands.  The default behavior of this method is to create a 
   // matPsStrandCurve material model.
   virtual matYieldStressStrainCurve* DoCreateStrandMaterialModel(const matPsStrand& strand);

   //------------------------------------------------------------------------
   // GetNextAvailableKey
   // Returns the next avialable unique item key for this class
   CollectionIndexType GetNextAvailableKey();

   //------------------------------------------------------------------------
   // OnGeometryChange
   // Call this function on all geometry changes
   void OnGeometryChange();

   //------------------------------------------------------------------------
   void MakeCopy(const rcaCapacityProblem& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const rcaCapacityProblem& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   // first some typedefs...
   typedef std::shared_ptr<matYieldStressStrainCurve> MatCurvePtr;
   typedef std::pair<CollectionIndexType, MatCurvePtr>               MatCurveEntry;
   typedef std::map<CollectionIndexType,MatCurvePtr>                 MatCurveContainer;
   typedef MatCurveContainer::iterator                  MatCurveIterator;
   typedef MatCurveContainer::const_iterator            ConstMatCurveIterator;

   typedef std::shared_ptr<matConcrete>           ConcretePtr;
   typedef std::vector<ConcretePtr>                 ConcreteContainer;
   typedef ConcreteContainer::iterator              ConcreteIterator;
   typedef ConcreteContainer::const_iterator        ConstConcreteIterator;

   typedef std::shared_ptr<rcaConcreteElement> ConcElementPtr;
   typedef std::pair<CollectionIndexType, ConcElementPtr>     ConcElementEntry;
   typedef std::map<CollectionIndexType,ConcElementPtr>       ConcElementContainer;
   typedef ConcElementContainer::iterator        ConcElementIterator;
   typedef ConcElementContainer::const_iterator  ConstConcElementIterator;

   typedef std::shared_ptr<rcaReinforcementElement> ReinfElementPtr;
   typedef std::pair<CollectionIndexType, ReinfElementPtr>         ReinfElementEntry;
   typedef std::map<CollectionIndexType,ReinfElementPtr>           ReinfElementContainer;
   typedef ReinfElementContainer::iterator            ReinfElementIterator;
   typedef ReinfElementContainer::const_iterator      ConstReinfElementIterator;

   // next, the real data...
   ConcreteContainer     m_ConcreteContainer;
   CollectionIndexType   m_BaseConcrete;
   MatCurveContainer     m_MsCurveContainer;
   MatCurveContainer     m_PsCurveContainer;
   ConcElementContainer  m_ConcElementContainer;
   ReinfElementContainer m_ReinfElementContainer;

   gpLine2d  m_NeutralAxisLocation;
   Float64   m_FurthestDistance; // farthest distance from na to edge of section
   Float64   m_MaxCompressiveStrain; // max strain at farthest fiber
   CollectionIndexType m_LastKey;  // last key used for items (material,rebar,etc...)
   mutable Float64   m_CbOffset; // distance from n.a. to compression block.
   mutable etBiaxialBeamStrain m_BeamStrain; // beam strain function
   mutable Float64 m_CompArea; // area of compression block
   mutable Float64 m_EffCompArea; // area of effective compression block

   mutable gpPoint2d m_PlasticCentroid;    // cache plastic centroid for efficiency
   mutable bool      m_PcHasChanged;       // update flag to facilitate caching

   mutable gmCompositeShape m_ConcreteShape; // cache shape for efficiency
   mutable bool             m_CsHasChanged;  // update flag for caching


   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Get forces in global coordinates.
   void GetGlobalSectionForces(Float64* pFz,
                               Float64* pMx,
                               Float64* pMy) const;

   void GetGlobalSectionForcesEx(Float64* pFz,
                                 Float64* pMx,
                                 Float64* pMy,
                                 Float64* compRes, gpPoint2d* compLoc,
                                 Float64* tensRes, gpPoint2d* tensLoc) const;
   void Init();
   void Clean();

   // GROUP: ACCESS

   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REINFORCEDCONCRETE_CAPACITYPROBLEM_H_
