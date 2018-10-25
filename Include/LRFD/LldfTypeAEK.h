///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_LLDFTYPEAEK_H_
#define INCLUDED_LRFD_LLDFTYPEAEK_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <Lrfd\LldfTypeAEKIJ.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdLldfTypeAEK

   Live load distribution factor calculator for cross section types A, E, K 
   when cross frames or diaphragms are present.


DESCRIPTION
   Live load distribution factor calculator for cross section types A, E, K 
   when cross frames or diaphragms are present.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.12.1998 : Created file
*****************************************************************************/

class LRFDCLASS lrfdLldfTypeAEK : public lrfdLldfTypeAEKIJ
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdLldfTypeAEK(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                   Uint32 Nl, Float64 wLane,
                   Float64 L,Float64 ts,Float64 n,
                   Float64 I, Float64 A, Float64 eg,
                   bool bXFrames, // if true, the statical (rigid) method is used
                   Float64 skewAngle1, Float64 skewAngle2,
                   bool bSkewMoment,
                   bool bSkewShear);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdLldfTypeAEK(const lrfdLldfTypeAEK& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdLldfTypeAEK();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdLldfTypeAEK& operator = (const lrfdLldfTypeAEK& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const lrfdLldfTypeAEK& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const lrfdLldfTypeAEK& rOther);

   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_2_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_2_Strength() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   bool m_bXFrames;

   // GROUP: LIFECYCLE
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


/*****************************************************************************
CLASS 
   lrfdWsdotLldfTypeAEK

   Live load distribution factor calculator for cross section types A, E, K,
   accounting for WSDOT modifications.


DESCRIPTION
   Live load distribution factor calculator for cross section types A, E, K,
   accounting for WSDOT modifications.  These modifications are documented
   in a memorandum by C. C. Ruth, dated February 22, 1999.

   The WSDOT modifications are:
   1. For exterior girders with a slab cantilever length less than or equal to
      one-half of the adjacent interior girder spacing,  compute the distribution
      factor using the equations for an interior girder.  The slab cantilever
      length is defined as the distance from the centerline of the exterior girder
      to the edge of the slab.
   2. For exterior girders with a slab cantilever length exceeding one-half
      of the adjacent interior girder spacing, compute the live load distribution
      factor in accordance with the LRFD specification, except use a multiple
      presence factor of 1.0 for one design lane loaded.
   3. The special analysis based on the conventional approximation of loads on 
      piles per AASHTO-LRFD Article C4.6.2.2.2d shall not be used unless the
      effectiveness of diaphragms on the laterial distribution of truck loads
      is investigated.
   4. Do not use rigid method


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.12.1998 : Created file
*****************************************************************************/

class LRFDCLASS lrfdWsdotLldfTypeAEK : public lrfdLldfTypeAEKIJ
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor
   lrfdWsdotLldfTypeAEK(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                        Uint32 Nl, Float64 wLane,
                        Float64 L,Float64 ts,Float64 n,
                        Float64 I, Float64 A, Float64 eg,
                        Float64 leftSlabOverhang,Float64 rightSlabOverhang,
                        bool bXFrames,
                        Float64 skewAngle1, Float64 skewAngle2,
                        bool bSkewMoment,
                        bool bSkewShear);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdWsdotLldfTypeAEK(const lrfdWsdotLldfTypeAEK& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdWsdotLldfTypeAEK();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdWsdotLldfTypeAEK& operator = (const lrfdWsdotLldfTypeAEK& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   Float64 m_LeftSlabOverhang;
   Float64 m_RightSlabOverhang;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   

   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_2_Strength() const;

   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_2_Strength() const;

   //------------------------------------------------------------------------
   void MakeCopy(const lrfdWsdotLldfTypeAEK& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const lrfdWsdotLldfTypeAEK& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   // GROUP: LIFECYCLE
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

#endif // INCLUDED_LRFD_LLDFTYPEAEK_H_
