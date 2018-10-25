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

#ifndef INCLUDED_BRIDGEMODELING_IBEAMENDBLOCKGIRDERPROFILE_H_
#define INCLUDED_BRIDGEMODELING_IBEAMENDBLOCKGIRDERPROFILE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <BridgeModeling\EndBlockGirderProfile.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfIBeamEndBlockGirderProfile

   Profile object representing an I-beam with end blocks.


DESCRIPTION
   Profile object representing an I-beam with end blocks.

COPYRIGHT
   Copyright (c) 1997-2002
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.03.2002 : Created file
*****************************************************************************/

class BMFCLASS bmfIBeamEndBlockGirderProfile : public bmfEndBlockGirderProfile
{
public:
   // GROUP: LIFECYCLE
   bmfIBeamEndBlockGirderProfile(Float64 w1, Float64 w2, Float64 w3, Float64 w4,
                                 Float64 d1, Float64 d2, Float64 d3, Float64 d4, 
                                 Float64 d5, Float64 d6, Float64 d7,
                                 Float64 t1, Float64 t2, 
                                 Float64 EndBlockWidth, Float64 EndBlockLength);
   ~bmfIBeamEndBlockGirderProfile();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual bmfGirderProfile* CreateClone() const;

   //------------------------------------------------------------------------
   virtual gmIShape* CreateShape(Float64 x,Float64 girderLength) const;

   //------------------------------------------------------------------------
   virtual Float64 GetEndBlockLength() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   Float64 m_W1;
   Float64 m_W2;
   Float64 m_W3;
   Float64 m_W4;
   Float64 m_D1;
   Float64 m_D2;
   Float64 m_D3;
   Float64 m_D4;
   Float64 m_D5;
   Float64 m_D6;
   Float64 m_D7;
   Float64 m_T1;
   Float64 m_T2;
   Float64 m_EndBlockWidth;
   Float64 m_EndBlockLength;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   void GetEndBlockDimension(Float64 x,Float64 girderLength,Float64* pWt,Float64* pWb) const;

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_IBEAMENDBLOCKGIRDERPROFILE_H_

