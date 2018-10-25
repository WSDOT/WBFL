///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEMODELING_DUCTS_H_
#define INCLUDED_BRIDGEMODELING_DUCTS_H_
#pragma once

// SYSTEM INCLUDES
//
#include <vector>

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <BridgeModeling\Duct.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class bmfGirder;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfDucts

   A collection of post-tensioning ducts.


DESCRIPTION
   A collection of post-tensioning ducts.

COPYRIGHT
   Copyright (c) 1997 - 2002
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 09.30.2002 : Created file
*****************************************************************************/

class BMFCLASS bmfDucts
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfDucts();

   //------------------------------------------------------------------------
   // Copy constructor
   bmfDucts(const bmfDucts& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfDucts();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operataor
   bmfDucts& operator=(const bmfDucts& rOther);

   // GROUP: OPERATIONS

   // GROUP: INQUIRY

   void EnableReflection(bool bEnable);
   bool IsReflectionEnabled() const;

   void AddDuct(const bmfDuct& duct);
   void RemoveDuct(long index);
   void RemoveAllDucts();
   long GetDuctCount() const;
   bmfDuct& GetDuct(long index);
   const bmfDuct& GetDuct(long index) const;
   gpPoint2d GetDuctLocation(long index,Float64 x) const;
   Float64 GetDuctDiameter(long index) const;

   Uint32 GetMaxStrands() const;

   gpPoint2d GetPTCG(Float64 x) const;

   void SetNumStrands(Uint32 ductIndex,Uint32 nStrands);
   Uint32 GetNumStrands(Uint32 ductIndex) const;
   Uint32 GetNumStrands() const;

   void SetGirder(bmfGirder* m_pGirder);

   Float64 GetDuctSlope(Float64 x,Uint32 ductIndex) const;

   void GetDuctControlPoints(Uint32 ductIndex,gpPoint2d* pe1,gpPoint2d* pe2) const;

protected:
   // GROUP: DATA MEMBERS
   std::vector<bmfDuct> m_Ducts;
   bool m_bEnableReflection;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeCopy( const bmfDucts& rOther );

   //------------------------------------------------------------------------
   void MakeAssignment( const bmfDucts& rOther );

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   const bmfGirder* m_pGirder;

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

#endif // INCLUDED_BRIDGEMODELING_DUCTS_H_

