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

#ifndef INCLUDED_BRIDGEMODELING_LRROWPATTERN_H_
#define INCLUDED_BRIDGEMODELING_LRROWPATTERN_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>


// LOCAL INCLUDES
//
#include <BridgeModeling\LrPattern.h>

// FORWARD DECLARATIONS
//
class matRebar;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfLrRowPattern

   Abstract class to Define a row of rebars in a cross section. 


DESCRIPTION
   Abstract class to Define a pattern of rebars in a cross section that is
   composed of a single row. The row location is defined by an 
   anchor point ( = @ ), center-to-center bar spacing, and orientation.
   The following orientations are possible:

   @ 0 0 0 0    0 0 @ 0 0      0 0 0 0 0 @
     Right       HCenter          HLeft

   @            0              0
   0            0              0
   0  Down      @  VCenter     0  Up 
   0            0              0
   0            0              @
   

COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 05.26.1999 : Created file
*****************************************************************************/

class BMFCLASS bmfLrRowPattern : public bmfLrPattern
{
public:

   // Possible row orientations
   enum Orientation { Right, HCenter, Left, Up, VCenter, Down };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfLrRowPattern();

   //------------------------------------------------------------------------
   // Default constructor
   // NOTE: this class must have a valid matRebar* in order to work properly.
   bmfLrRowPattern(const matRebar* pRebar, gpPoint2d anchor, Orientation orient,
                   Uint32 numBars, Float64 spacing);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfLrRowPattern();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // polymorphic cloning
   virtual bmfLrPattern* CreateClone() const;

   //------------------------------------------------------------------------
   // Get number of bars in pattern
   virtual Uint32 GetNumBars() const;

   //------------------------------------------------------------------------
   // Get the ith bar location. zero-based
   virtual gpPoint2d GetBarLocation(Uint32 barNum) const;

   //------------------------------------------------------------------------
   // Set number of bars in pattern
   void SetNumBars(Uint32 numBars);

   //------------------------------------------------------------------------
   // Get pattern anchor point
   gpPoint2d GetAnchorPoint() const;

   //------------------------------------------------------------------------
   // Set pattern anchor point
   void SetAnchorPoint(const gpPoint2d& point);

   //------------------------------------------------------------------------
   // Get pattern orientation
   Orientation GetOrientation() const;

   //------------------------------------------------------------------------
   // Set pattern orientation
   void SetOrientation(Orientation orient);

   //------------------------------------------------------------------------
   // Get pattern bar spacing
   Float64 GetBarSpacing() const;

   //------------------------------------------------------------------------
   // Set pattern bar spacing
   void SetBarSpacing(Float64 point);
   
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64     m_BarSpacing;
   gpPoint2d   m_AnchorPoint;
   Uint32      m_NumBars;
   Orientation m_Orientation;


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

#endif // INCLUDED_BRIDGEMODELING_LRROWPATTERN_H_
