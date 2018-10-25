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

#ifndef INCLUDED_BRIDGEMODELING_BUNDLEPATTERN_H_
#define INCLUDED_BRIDGEMODELING_BUNDLEPATTERN_H_
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
   bmfBundlePattern

   This class encapsulates the bundle pattern for prestressed girder harped
   strands.


DESCRIPTION
   This class encapsulates the bundle pattern for prestressed girder harped
   strands.

   At the harping points in a WSDOT precast girder,  the harped strands are
   gathered into bundles.  The bundles are located on the vertical centerline
   of the precast girder's cross section.  The vertical location bundles are 
   measured up from the bottom of the girder's cross section.

   The bundle location is described by its distance above the bundle immedately
   below it (or the bottom of the girder in the case of the first bundle) and 
   the maximum number of strands allowed in the bundle (except in the case of
   the last bundle where the max number of strands is ignored).

COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.08.1998 : Created file
*****************************************************************************/

class BMFCLASS bmfBundlePattern
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfBundlePattern();

   //------------------------------------------------------------------------
   // Copy constructor
   bmfBundlePattern(const bmfBundlePattern& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfBundlePattern();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   bmfBundlePattern& operator = (const bmfBundlePattern& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Adds a bundle to the pattern.
   //
   // offset is the offset from the bottom of the girder in the case of the
   // first bundle or the offset from the bundle immedately below this one.
   //
   // maxStrands is the maximum number of strands allowed in this bundle. 
   // This parameter is ignored in the last bundle.
   void AddBundle(Float64 offset,StrandIndexType maxStrands);

   //------------------------------------------------------------------------
   // Returns the number of bundles.
   CollectionIndexType GetBundleCount() const;

   //------------------------------------------------------------------------
   // Returns the offset from the specified bundle to the bundle immedately
   // below it, or the offset to the bottom of the girder in the case of
   // the first bundle.
   Float64 GetBundleOffset(CollectionIndexType idx) const;

   //------------------------------------------------------------------------
   // Returns the height(offset) of the specified bundle from the bottom of
   // the girder.
   Float64 GetBundleHeight(CollectionIndexType idx) const;

   //------------------------------------------------------------------------
   // Returns the maximum number of strands that can be added to the 
   // specified bundle.
   StrandIndexType GetMaxStrandCount(CollectionIndexType idx) const;

   //------------------------------------------------------------------------
   // Removes a bundle from the pattern.  If bundles exist above the specified
   // bundle,  they are moved down such that bundle idx+1 is located at the
   // offset for bundle idx+1 above bundle idx-1.
   void RemoveBundle(CollectionIndexType idx);

   //------------------------------------------------------------------------
   // Removes all bundles from the bundle pattern.
   void RemoveAllBundles();

   //------------------------------------------------------------------------
   // Returns the center of gravity for nStrands.
   //
   // If nStrands exceeds the total number of strands for the strand bundles,
   // the extra strands are assumed to be located in the last bundle.
   gpPoint2d GetCenterOfGravity(StrandIndexType nStrands) const;

   //------------------------------------------------------------------------
   // Returns the index of the strand bundle given the index of a strand
   CollectionIndexType GetBundleIdx(StrandIndexType iStrand) const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const bmfBundlePattern& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const bmfBundlePattern& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   typedef struct tagBundleData
   {
      Float64 Offset;
      StrandIndexType MaxStrands;
   } BundleData;
   std::vector<BundleData> m_Bundles;

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

#endif // INCLUDED_BRIDGEMODELING_BUNDLEPATTERN_H_
