///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam forumla, patterned after Roark's formulas
//         for Stress and Strain
// Copyright © 1999-2021  Washington State Department of Transportation
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

#ifndef INCLUDED_ROARK_ROARK_H_
#define INCLUDED_ROARK_ROARK_H_
#pragma once

/************************************************************************
   Refenence:
   Formulas For Stress and Strain 4th Edition R.J. Roark
   Table III pp 104-113

   Naming Convension:
      Class Names -
         Class Names are of the form [C|P|F][C|P|F]{loadtype}
         where :
         [C|P|F] = Cantilever, Pinned, or Fixed end support
         the first one is for the left support and the second for the right
         support.
         {loadtype} can be EndLoad, IntermediateLoad,UniformLoad,PartUniformLoad,
         LeftTriangle,PartLeftTriangle,RightTriangle,PartRightTriangle,
         EndCouple,IntermediateCouple,CenterLoad, or CenterCouple

         Example:  PFRightTriangle - Pinned-Fixed beam with a right triangle
                   load. See Loading 25.
*************************************************************************/

#include <Roark\RoarkExp.h>
#include <System\SectionValue.h>

#include <memory>


class ROARKCLASS rkRoarkBeam
{
// Data Members
protected:
   Float64 L,EI;

// Constructors/Destructor
public:
   rkRoarkBeam(Float64 length,Float64 e,Float64 i);
   rkRoarkBeam(const rkRoarkBeam& rOther);
   virtual ~rkRoarkBeam() {}

// Member Functions
public:
   Float64 GetL() const;
   Float64 GetEI() const;

   virtual rkRoarkBeam* CreateClone() const = 0;

   virtual void GetReactions(Float64 *pRa,Float64* pRb) const = 0;
   virtual void GetMoments(Float64* pMa,Float64* pMb) const = 0;
   virtual void GetRotations(Float64* pra,Float64* prb) const = 0;
   virtual void GetDeflections(Float64* pYa,Float64* pYb) const = 0;

   virtual sysSectionValue ComputeShear(Float64 x) const = 0;
   virtual sysSectionValue ComputeMoment(Float64 x) const = 0;
   virtual Float64 ComputeRotation(Float64 x) const = 0;
   virtual Float64 ComputeDeflection(Float64 x) const = 0;

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

class ROARKCLASS rkComposite : public rkRoarkBeam
{
// Data Members
protected:
   typedef std::vector<std::shared_ptr<rkRoarkBeam> > BeamContainer;
   BeamContainer m_Beams;

// Constructors/Destructor
public:
   rkComposite();
   rkComposite(const rkComposite& rOther);
   virtual ~rkComposite() {}

// Member Functions
public:
   void AddBeam(const rkRoarkBeam& beam);
   CollectionIndexType GetBeamCount() const;
   const rkRoarkBeam* GetBeam(CollectionIndexType index) const;

   void RemoveAllBeams();
   virtual rkRoarkBeam* CreateClone() const;

   virtual void GetReactions(Float64 *pRa,Float64* pRb) const;
   virtual void GetMoments(Float64* pMa,Float64* pMb) const;
   virtual void GetRotations(Float64* pra,Float64* prb) const;
   virtual void GetDeflections(Float64* pYa,Float64* pYb) const;

   virtual sysSectionValue ComputeShear(Float64 x) const;
   virtual sysSectionValue ComputeMoment(Float64 x) const;
   virtual Float64 ComputeRotation(Float64 x) const;
   virtual Float64 ComputeDeflection(Float64 x) const;

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

class ROARKCLASS rkPPIntermediateLoad : public rkRoarkBeam // Loading 12
{
// Data Members
protected:
   Float64 a,b,W;

// Constructors/Destructor
public:
   rkPPIntermediateLoad(Float64 w,Float64 La,Float64 l,Float64 e,Float64 i);
   rkPPIntermediateLoad(const rkPPIntermediateLoad& rOther);
   virtual ~rkPPIntermediateLoad() {}

// Member Functions
public:
   rkRoarkBeam* CreateClone() const;

   Float64 GetLa() const;
   Float64 GetLb() const;
   Float64 GetW() const;

   void GetReactions(Float64 *pRa,Float64* pRb) const;
   void GetMoments(Float64* pMa,Float64* pMb) const;
   void GetRotations(Float64* pra,Float64* prb) const;
   void GetDeflections(Float64* pYa,Float64* pYb) const;

   sysSectionValue ComputeShear(Float64 x) const;
   sysSectionValue ComputeMoment(Float64 x) const;
   Float64 ComputeRotation(Float64 x) const;
   Float64 ComputeDeflection(Float64 x) const;


public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

class ROARKCLASS rkPPPartUniformLoad : public rkRoarkBeam // Loading 14
{
// Data Members
protected:
   Float64 a,b,c,d,W;

// Constructors/Destructor
public:
   rkPPPartUniformLoad(Float64 La,Float64 Lb,Float64 w,Float64 l,Float64 e,Float64 i);
   rkPPPartUniformLoad(const rkPPPartUniformLoad& rOther);
   virtual ~rkPPPartUniformLoad() {}

// Member Functions
public:
   virtual rkRoarkBeam* CreateClone() const;
   Float64 GetLa() const;
   Float64 GetLb() const;
   Float64 GetW() const;

   void GetReactions(Float64 *pRa,Float64* pRb) const;
   void GetMoments(Float64* pMa,Float64* pMb) const;
   void GetRotations(Float64* pra,Float64* prb) const;
   void GetDeflections(Float64* pYa,Float64* pYb) const;

   sysSectionValue ComputeShear(Float64 x) const;
   sysSectionValue ComputeMoment(Float64 x) const;
   Float64 ComputeRotation(Float64 x) const;
   Float64 ComputeDeflection(Float64 x) const;


public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

class ROARKCLASS rkPPIntermediateCouple : public rkRoarkBeam
{
// Data Members
protected:
   Float64 a, M;

// Constructors/Destructor
public:
   rkPPIntermediateCouple(Float64 Mo,Float64 La,Float64 l,Float64 e,Float64 i);
   rkPPIntermediateCouple(const rkPPIntermediateCouple& rOther);
   virtual ~rkPPIntermediateCouple() {}

// Member Functions
public:
   virtual rkRoarkBeam* CreateClone() const;

   Float64 GetLa() const;
   Float64 GetMo() const;

   void GetReactions(Float64 *pRa,Float64* pRb) const;
   void GetMoments(Float64* pMa,Float64* pMb) const;
   void GetRotations(Float64* pra,Float64* prb) const;
   void GetDeflections(Float64* pYa,Float64* pYb) const;

   sysSectionValue ComputeShear(Float64 x) const;
   sysSectionValue ComputeMoment(Float64 x) const;
   Float64 ComputeRotation(Float64 x) const;
   Float64 ComputeDeflection(Float64 x) const;


public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

#endif // INCLUDED_ROARK_ROARK_H_
