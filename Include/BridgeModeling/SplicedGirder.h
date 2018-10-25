///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
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

#ifndef INCLUDED_BRIDGEMODELING_SPLICEDGIRDER_H_
#define INCLUDED_BRIDGEMODELING_SPLICEDGIRDER_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <BridgeModeling\SplicedGirderTemplate.h>
#include <BridgeModeling\Girder.h>
#include <BridgeModeling\StrandPattern.h>
#include <BridgeModeling\BundlePattern.h>
#include <BridgeModeling\LrLayout.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class matConcreteEx;
class matPsStrand;
class gmSection;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfSplicedGirder

   Extends bmfGirder to included attributes of a precast prestressed girder.


DESCRIPTION
   Extends bmfGirder to included attributes of a precast prestressed girder.
   These attributes consist of prestressing strands and girder material
   (i.e. concrete).

COPYRIGHT
   Copyright (c) 1997 - 2002
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 08.19.2002 : Created file
*****************************************************************************/

class BMFCLASS bmfSplicedGirder : public bmfGirder
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfSplicedGirder( bmfSplicedGirderTemplate* pTpl );

   //------------------------------------------------------------------------
   // Copy constructor
   bmfSplicedGirder(const bmfSplicedGirder& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfSplicedGirder();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operataor
   bmfSplicedGirder& operator=(const bmfSplicedGirder& rOther);

   // GROUP: OPERATIONS
   SegmentIndexType GetNumSegments() const;
   CollectionIndexType GetNumSplices() const;
   Float64 GetSpliceLocation(CollectionIndexType splice) const;

   //------------------------------------------------------------------------
   void PlanView(HDC hDC,const grlibPointMapper& mapper) const;

   //------------------------------------------------------------------------
   virtual gpRect2d GetBoundingBox() const;

   //------------------------------------------------------------------------
   // Called by the associated girder path when it changes.
   virtual void OnGirderPathChanged();

   //------------------------------------------------------------------------
   // Creates a section object that will represent the girder's cross section
   // at distFromStart from the start of the girder.  You are
   // responsible for the destruction of this shape object.
   bmfIGirderSection* CreateGirderSection(Float64 distFromStart) const;

   //------------------------------------------------------------------------
   // Returns the eccentricity of the straight strands at distFromStart 
   // from the start of the girder.
   // Temporary strands are not included
   Float64 GetStrandEccentricity( SegmentIndexType segment, Float64 distFromStart ) const;

   //------------------------------------------------------------------------
   // Returns the eccentricity of the straight strands at distFromStart 
   // from the start of the girder for nStrands strands. 
   // Temporary strands are not included
   Float64 GetStrandEccentricity( SegmentIndexType segment, StrandIndexType nStrands, Float64 distFromStart ) const;

   gpPoint2d GetTendonEccentricity( Float64 distFromStart ) const;
   gpPoint2d GetTendonEccentricity( Float64 distFromStart, Uint32 ductIdx ) const;
//   Float64 GetTendonEccentricity( Float64 distFromStart, Uint32 nStrands ) const;
   gpPoint2d GetDuctEccentricity( Float64 distFromStart, Uint32 ductIndex ) const;
   gpPoint2d GetDuctLocation( Float64 distFromStart, Uint32 ductIndex ) const;

   //------------------------------------------------------------------------
   // Returns the eccentricity of the temporary strands at distFromStart 
   // from the start of the girder.
   Float64 GetTemporaryStrandEccentricity( Float64 distFromStart ) const;

   //------------------------------------------------------------------------
   // Returns the eccentricity of the temporary strands at distFromStart 
   // from the start of the girder for nStrands strands.
   Float64 GetTemporaryStrandEccentricity( StrandIndexType nStrands, Float64 distFromStart ) const;

   //------------------------------------------------------------------------
   // Returns the coordinate in the cross section where the specified straight
   // strand is.
   gpPoint2d GetStrandPosition(SegmentIndexType segment,Float64 distFromStart, StrandIndexType strIdx) const;

   //------------------------------------------------------------------------
   // Returns the coordinate in the cross section where a strand might
   // be positioned. This is the coordinate in the strand pattern whereas
   // GetStraightStrandPosition returns the coordinate of a strand.
   gpPoint2d GetStrandPoint(SegmentIndexType segment,Float64 distFromStart, StrandIndexType strIdx) const;

   //------------------------------------------------------------------------
   // Returns the coordinate in the cross section where the specified temporary
   // strand is.
   gpPoint2d GetTemporaryStrandPosition(Float64 distFromStart, StrandIndexType strIdx) const;

   //------------------------------------------------------------------------
   // Returns the coordinate in the cross section where a strand might
   // be positioned. This is the coordinate in the strand pattern whereas
   // GetTemporaryStrandPosition returns the coordinate of a strand.
   gpPoint2d GetTemporaryStrandPoint(Float64 distFromStart, StrandIndexType strIdx) const;

   //------------------------------------------------------------------------
   // does not include temporary strands
   StrandIndexType GetMaxStrands(SegmentIndexType segment) const;

   //------------------------------------------------------------------------
   StrandIndexType GetMaxTemporaryStrands() const;

   //------------------------------------------------------------------------
   // Adds a straight strand in accordance with the strand pattern. Returns
   // true if successful, otherwise false.
   bool AddStrand(SegmentIndexType segment);

   //------------------------------------------------------------------------
   // Remove a straight strand in accordance with the strand pattern. Returns
   // true if successful, otherwise false.
   bool RemoveStrand(SegmentIndexType segment);

   //------------------------------------------------------------------------
   // Adds a temporary strand in accordance with the strand pattern. Returns
   // true if successful, otherwise false.
   bool AddTemporaryStrand();

   //------------------------------------------------------------------------
   // Removes a temporary strand in accordance with the strand pattern. Returns
   // true if successful, otherwise false.
   bool RemoveTemporaryStrand();

   //------------------------------------------------------------------------
   // Sets the number of straight strands.  If nStrands does not fit correctly
   // into the strand pattern, the number of strands in the girder is not
   // changed and the next highest number of strands is returned, or the max
   // number of strands if nStrands is greater than the max.  Zero is returned
   // if the strand cound is modified successfully.
   StrandIndexType SetNumStrands( SegmentIndexType segment, StrandIndexType nStrands );

   //------------------------------------------------------------------------
   // Returns the number of straight strands in the girder.
   StrandIndexType GetNumStrands(SegmentIndexType segment) const;

   //------------------------------------------------------------------------
   // Returns the number of debonded strands in the girder.
   StrandIndexType GetNumDebondedStrands(SegmentIndexType segment) const;
   void SetNumDebondedStrands(SegmentIndexType segment,StrandIndexType nStrands);

   //------------------------------------------------------------------------
   // Returns true if the strand at the index is debonded
   bool IsStrandDebonded(SegmentIndexType segment, StrandIndexType strIdx) const;

   //------------------------------------------------------------------------
   // Returns the debond length (same for all debonded strands)
   Float64 GetDebondLength(SegmentIndexType segment) const;
   void SetDebondLength(SegmentIndexType segment,Float64 l);

   //------------------------------------------------------------------------
   // Sets the number of temporary strands.  If nStrands does not fit correctly
   // into the strand pattern, the number of strands in the girder is not
   // changed and the next highest number of strands is returned, or the max
   // number of strands if nStrands is greater than the max.  Zero is returned
   // if the strand cound is modified successfully.
   StrandIndexType SetNumTemporaryStrands( StrandIndexType nStrands );

   //------------------------------------------------------------------------
   // Returns the number of temporary strands in the girder.
   StrandIndexType GetNumTemporaryStrands() const;

   //------------------------------------------------------------------------
   // Returns the maximum number of PT strands
   StrandIndexType GetMaxPTStrands() const;

//   //------------------------------------------------------------------------
//   // Adds a PT strand to the tendon ducts. Returns true if successful, otherwise
//   // return false.
//   bool AddPTStrand();
//
//   //------------------------------------------------------------------------
//   // Removes a PT strand from the tendon ducts. Returns true if successful,
//   // otherwise returns false.
//   bool RemovePTStrand();

   //------------------------------------------------------------------------
   // Sets the number of PT strands. If nStrands does not fit correctly into
   // the ducts defined by the girder template, the number of strands is not changed
   // and the next highest number of strands is returned, or the max number of
   // strands is returned if nStrands i greater than max. Zero is returned if
   // the strand count is modifed successfully.
   StrandIndexType SetNumPTStrands(DuctIndexType ductIndex, StrandIndexType nStrands );

   //------------------------------------------------------------------------
   // Returns the number of PT strands in a specified duct.
   StrandIndexType GetNumPTStrands( DuctIndexType ductIndex ) const;

   //------------------------------------------------------------------------
   // Returns the total number of PT strands.
   StrandIndexType GetNumPTStrands() const;

   //------------------------------------------------------------------------
   // returns the number of ducts with strand in it
   DuctIndexType GetNumDucts() const;

   //------------------------------------------------------------------------
   // Returns the slope of a duct
   Float64 GetDuctSlope(Float64 x,DuctIndexType ductIndex) const;

   //------------------------------------------------------------------------
   // Returns the dimensions that locate the duct (defines the parabola)
   void GetDuctControlPoints(DuctIndexType ductIndex,gpPoint2d* pe1,gpPoint2d* pe2);

   Float64 GetDuctDiameter(DuctIndexType ductIndex) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns the concrete material for this girder.
   const matConcreteEx* GetConcrete() const;

   //------------------------------------------------------------------------
   // Returns the prestressing strand material for this girder.
   const matPsStrand* GetStrand() const;

   //------------------------------------------------------------------------
   // Returns the post-tensioning strand material for this girder.
   const matPsStrand* GetPTStrand() const;

   //------------------------------------------------------------------------
   // Returns the strand pattern
   const bmfStrandPattern& GetStrandPattern(SegmentIndexType semgent) const;
   bmfStrandPattern& GetStrandPattern(SegmentIndexType semgent);

   //------------------------------------------------------------------------
   // Returns a copy of the temporary strand pattern
   bmfStrandPattern GetTemporaryStrandPattern() const;

   //------------------------------------------------------------------------
   bmfSplicedGirderTemplate* GetTemplate();
   const bmfSplicedGirderTemplate* GetTemplate() const;

   //------------------------------------------------------------------------
   // Get long. reinforcement layout
   const bmfLrLayout& GetLrLayout(SegmentIndexType segment) const;

   //------------------------------------------------------------------------
   // Set long. reinforcement layout
   void SetLrLayout(SegmentIndexType segment, const bmfLrLayout& rLayout);

   //------------------------------------------------------------------------
   // Returns the length of a precast segment. Segment lengths do not
   // include the size of the closure pour
   Float64 GetSegmentLength(SegmentIndexType segment) const;

   //------------------------------------------------------------------------
   // Returns the size of the closure pour
   Float64 GetClosurePourSize(CollectionIndexType splice) const;

   //------------------------------------------------------------------------
   // Indicates if the ducts are grouted. If the ducts are grouted then
   // the girder cross section is taken to be the gross section, otherwise
   // the area of the ducts (for the number of tendons used) is deducted
   // from the cross section
   bool AreDuctsGrouted() const;
   void Grout(bool bGrout);

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void UpdateTopFlangeCorners();

   //------------------------------------------------------------------------
   void MakeCopy( const bmfSplicedGirder& rOther );

   //------------------------------------------------------------------------
   void MakeAssignment( const bmfSplicedGirder& rOther );

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // Four corner points for the top flange rectangle
   CComPtr<IPoint2d> m_StartLeft;
   CComPtr<IPoint2d> m_StartRight;
   CComPtr<IPoint2d> m_EndLeft;
   CComPtr<IPoint2d> m_EndRight;

   // Need to keep a local copy because the template's copy is read-only
   bmfStrandPattern m_StrandPtrn[3];
   bmfStrandPattern m_TmpPtrn;       // temporary

   bmfDucts m_Ducts;
   bool m_bGrouted;

   // need local copy of layout since layout points back to this
   bmfLrLayout m_LrLayout[3];

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

#endif // INCLUDED_BRIDGEMODELING_SPLICEDGIRDER_H_

