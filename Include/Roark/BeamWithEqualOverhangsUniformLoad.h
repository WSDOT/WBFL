///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam forumla, patterned after Roark's formulas
//         for Stress and Strain
// Copyright © 1999-2012  Washington State Department of Transportation
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

#ifndef INCLUDED_ROARK_BEAMWITHEQUALOVERHANGSUNIFORMLOAD_H_
#define INCLUDED_ROARK_BEAMWITHEQUALOVERHANGSUNIFORMLOAD_H_
#pragma once

#include <Roark\RoarkExp.h>
#include <System\SectionValue.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rkBeamWithEqualOverhangsUniformLoad

   Class to get deflections and forces for a beam with equal overhangs and a
   uniform load applied along the entire length.

    ===========================================================
          ^                                             ^
    <- a ->                                             <- a ->
    <-------------------------- L ---------------------------->


DESCRIPTION
   Class to get deflections and forces for a beam with equal overhangs and a
   uniform load applied along the entire length.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 03.16.1999 : Created file
*****************************************************************************/

class ROARKCLASS rkBeamWithEqualOverhangsUniformLoad
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor
   rkBeamWithEqualOverhangsUniformLoad(Float64 length,Float64 overhang, Float64 w,
                                       Float64 e,Float64 i);

   //------------------------------------------------------------------------
   // Copy constructor
   rkBeamWithEqualOverhangsUniformLoad(const rkBeamWithEqualOverhangsUniformLoad& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rkBeamWithEqualOverhangsUniformLoad();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rkBeamWithEqualOverhangsUniformLoad& operator = (const rkBeamWithEqualOverhangsUniformLoad& rOther);

   // GROUP: OPERATIONS
   Float64 GetL() const;
   Float64 GetEI() const;
   Float64 GetOverhang() const;
   Float64 GetW() const; // load/length

   virtual void GetReactions(Float64 *pRa,Float64* pRb) const;
   virtual void GetMoments(Float64* pMa,Float64* pMb) const;
   virtual void GetRotations(Float64* pra,Float64* prb) const;
   virtual void GetDeflections(Float64* pYa,Float64* pYb) const;

   virtual sysSectionValue ComputeShear(Float64 x) const;
   virtual sysSectionValue ComputeMoment(Float64 x) const;
   virtual Float64 ComputeRotation(Float64 x) const;
   virtual Float64 ComputeDeflection(Float64 x) const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const rkBeamWithEqualOverhangsUniformLoad& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const rkBeamWithEqualOverhangsUniformLoad& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_EI;
   Float64 m_L;
   Float64 m_Overhang;
   Float64 m_W;

   // GROUP: LIFECYCLE
   // Default constructor
   rkBeamWithEqualOverhangsUniformLoad();
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

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

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_ROARK_BEAMWITHEQUALOVERHANGSUNIFORMLOAD_H_
