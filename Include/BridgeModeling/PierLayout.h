///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2011  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEMODELING_PIERLAYOUT_H_
#define INCLUDED_BRIDGEMODELING_PIERLAYOUT_H_
#pragma once

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          bmfPierLayout
// SYNOPSIS:      Encapsulates a pier's orientation
// DESCRIPTION:   Describes the orientation of a pier.  A pier is located
//                in an alignment by its station, but that is not enough.
//                The orientation of the plane of the pier must be described.
//                This class encapsulates that information
// EXAMPLES:      
// BUGS:          
// ALSO SEE:
//////////////////X////////////////////X/////////////////////////////////////

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

class BMFCLASS bmfPierLayout
{
public:
   enum Orientation { NormalToAlignment, SkewAngle, Bearing };

   // LIFECYCLE
   
   // Method:      PierLayout
   // Description: Default c'tor
   //              Creates a layout described with a skew angle of 0.0 radians
   // Return:      N/A
   bmfPierLayout();

   // Method:      PierLayout
   // Description: Explicit c'tor
   // Return:      N/A
   bmfPierLayout(IAngle* pSkewAngle);
   bmfPierLayout(IDirection* pDirection);

   // Method:      PierLayout
   // Description: Copy c'tor
   // Return:      N/A
   bmfPierLayout(const bmfPierLayout& pl);

   // Method:      ~PierLayout
   // Description: d'tor
   // Return:      N/A
   ~bmfPierLayout(); 

   // OPERATORS
   
   // Method:      operator =
   // Description: Assignment operator
   // Return:      Referenece to self
   bmfPierLayout& operator = (const bmfPierLayout& pl);

   // OPERATIONS

   // ACCESS

   // Method:      SetLayout
   // Description: Changes the layout parameters
   // Return:      None
   void SetLayout();
   void SetLayout(IAngle* pSkewAngle);
   void SetLayout(IDirection* pDirection);
   void SetLayoutAngle(Float64 angle);
   void SetLayoutBearing(Float64 direction);

   // Method:      GetLayout
   // Description: Retreives the layout parameters
   // Return:      None
   Orientation GetOrientation() const;
   void GetSkewAngle(IAngle** ppAngle) const;
   void GetBearing(IDirection** ppDirection) const;

   // INQUIRY

protected:
   // DATA MEMBERS
   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   // ACCESS
   // INQUIRY

private:
   // DATA MEMBERS
   Orientation m_Orientation;
   CComPtr<IDirection> m_Direction;
   CComPtr<IAngle> m_SkewAngle;

   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   // ACCESS
   // INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_PIERLAYOUT_H_
