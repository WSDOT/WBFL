///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
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

#ifndef INCLUDED_BRIDGEMODELING_DUCT_H_
#define INCLUDED_BRIDGEMODELING_DUCT_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfDuct

   Defines the path and size of a post-tensioning duct


DESCRIPTION
   Defines the path and size of a post-tensioning duct. The duct is limited
   to a symmetrical parabola.

COPYRIGHT
   Copyright (c) 1997 - 2002
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 09.30.2002 : Created file
*****************************************************************************/

class BMFCLASS bmfDuct
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfDuct(Float64 x1,Float64 y1, Float64 x2,Float64 y2, Float64 diaDuct,Float64 diaStrand,Float64 maxEccentricity,Uint32 nStrands,Uint32 maxStrands);

   //------------------------------------------------------------------------
   // Copy constructor
   bmfDuct(const bmfDuct& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfDuct();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operataor
   bmfDuct& operator=(const bmfDuct& rOther);

   // GROUP: OPERATIONS

   // GROUP: INQUIRY
   Float64 GetDuctDiameter() const;
   void SetDuctDiameter(Float64 dia);

   Float64 GetStrandDiameter() const;
   void SetStrandDiameter(Float64 dia);

   // Tendon eccentricity when maximum number of strands are used
   Float64 GetMaxTendonEccentricity() const;
   void SetMaxTendonEccentricity(Float64 ecc);

   StrandIndexType GetMaxStrands() const;
   void SetMaxStrands(StrandIndexType max);

   StrandIndexType GetNumStrands() const;
   void SetNumStrands(StrandIndexType nStrands);

   void GetDuctPosition(Float64* px1,Float64* py1,Float64* px2,Float64* py2) const;
   void SetDuctPosition(Float64 x1,Float64 y1, Float64 x2,Float64 y2);

   void GetTendonCG(Float64 z,Float64 L,Float64 *pX,Float64 *pY) const;
   void GetDuctLocation(Float64 z,Float64 L,Float64 *pX,Float64 *pY) const;
   Float64 GetDuctSlope(Float64 z,Float64 L) const;

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeCopy( const bmfDuct& rOther );

   //------------------------------------------------------------------------
   void MakeAssignment( const bmfDuct& rOther );

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_X1; // offset from the center of the girder to the duct at the end of the girder
   Float64 m_Y1; // height from the bottom of the girder to the center of the duct at the end of the girder
   Float64 m_X2; // offset from the center of the girder to the duct at the centerline of the girder
   Float64 m_Y2; // height from the bottom of the girder to the center of the duct at the centerline of the girder
   Float64 m_DuctDiameter; // duct diameter
   Float64 m_StrandDiameter; // diameter of 1 strand
   Float64 m_Ecc; // eccentricity of tendon when max number of strands are used
   StrandIndexType m_MaxStrands; // maximum number of strands that can be placed in the duct
   StrandIndexType m_nStrands; // number of strands in this duct

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

#endif // INCLUDED_BRIDGEMODELING_DUCT_H_

