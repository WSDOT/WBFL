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

#ifndef INCLUDED_BRIDGEMODELING_PRECASTGIRDER_H_
#define INCLUDED_BRIDGEMODELING_PRECASTGIRDER_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <BridgeModeling\PrecastGirderTemplate.h>
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
   bmfPrecastGirder

   Extends bmfGirder to included attributes of a precast prestressed girder.


DESCRIPTION
   Extends bmfGirder to included attributes of a precast prestressed girder.
   These attributes consist of prestressing strands and girder material
   (i.e. concrete).

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 03.28.1997 : Created file
*****************************************************************************/

class BMFCLASS bmfPrecastGirder : public bmfGirder
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfPrecastGirder( bmfPrecastGirderTemplate* pTpl );

   //------------------------------------------------------------------------
   // Copy constructor
   bmfPrecastGirder(const bmfPrecastGirder& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfPrecastGirder();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operataor
   bmfPrecastGirder& operator=(const bmfPrecastGirder& rOther);

   // GROUP: OPERATIONS

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
   // Returns the eccentricity of the harped strands at distFromStart 
   // from the start of the girder.
   Float64 GetHarpedStrandEccentricity( Float64 distFromStart ) const;

   //------------------------------------------------------------------------
   // Returns the eccentricity of the harped strands at distFromStart 
   // from the start of the girder for nStrands strands.
   Float64 GetHarpedStrandEccentricity( StrandIndexType nStrands, Float64 distFromStart,const gpSize2d& endShift,const gpSize2d& hpShift ) const;

   //------------------------------------------------------------------------
   // Returns the eccentricity of the straight strands at distFromStart 
   // from the start of the girder.
   Float64 GetStraightStrandEccentricity( Float64 distFromStart ) const;

   //------------------------------------------------------------------------
   // Returns the eccentricity of the straight strands at distFromStart 
   // from the start of the girder for nStrands strands.
   Float64 GetStraightStrandEccentricity( StrandIndexType nStrands, Float64 distFromStart ) const;

   //------------------------------------------------------------------------
   // Returns the eccentricity of the temporary strands at distFromStart 
   // from the start of the girder.
   Float64 GetTemporaryStrandEccentricity( Float64 distFromStart ) const;

   //------------------------------------------------------------------------
   // Returns the eccentricity of the temporary strands at distFromStart 
   // from the start of the girder for nStrands strands.
   Float64 GetTemporaryStrandEccentricity( StrandIndexType nStrands, Float64 distFromStart ) const;

   //------------------------------------------------------------------------
   // Returns the eccentricity of the prestressing strands at distFromStart
   // from the start of the girder.  If bIncTemp is true, the temporary
   // strand are included otherwise they are not.
   Float64 GetStrandEccentricity( Float64 distFromStart, bool bIncTemp = false ) const;

   //------------------------------------------------------------------------
   // Returns the eccentricity of the prestressing strands at distFromStart
   // from the start of the girder for nStrands strands.
   Float64 GetStrandEccentricity( StrandIndexType nStraight, StrandIndexType nHarped, StrandIndexType nTemp,Float64 distFromStart, const gpSize2d& endShift, const gpSize2d& hpShift  ) const;

   //------------------------------------------------------------------------
   // Returns the coordinate in the cross section where the specified straight
   // strand is.
   gpPoint2d GetStraightStrandPosition(Float64 distFromStart, StrandIndexType strIdx) const;

   //------------------------------------------------------------------------
   // Returns the coordinate in the cross section where a strand might
   // be positioned. This is the coordinate in the strand pattern whereas
   // GetStraightStrandPosition returns the coordinate of a strand.
   gpPoint2d GetStraightStrandPoint(Float64 distFromStart, StrandIndexType strIdx) const;

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
   // Returns the coordinate in the cross section where the specified harped
   // strand is.
   gpPoint2d GetHarpedStrandPosition(Float64 distFromStart, StrandIndexType strIdx) const;
   gpPoint2d GetHarpedStrandPosition(Float64 distFromStart, StrandIndexType strIdx,const gpSize2d& endShift,const gpSize2d& hpShift) const;
   gpPoint2d GetHarpedStrandPoint(Float64 distFromStart, StrandIndexType strIdx) const;
   gpPoint2d GetHarpedStrandPoint(Float64 distFromStart, StrandIndexType strIdx,StrandIndexType numHarpedStrands) const;
   gpPoint2d GetHarpedStrandPoint(Float64 distFromStart, StrandIndexType strIdx,const gpSize2d& endShift,const gpSize2d& hpShift) const;
   gpPoint2d GetHarpedStrandPoint(Float64 distFromStart, StrandIndexType strIdx,const gpSize2d& endShift,const gpSize2d& hpShift,StrandIndexType numHarpedStrands) const;

   //------------------------------------------------------------------------
   // Returns the slope of the harped strand in the form 1:n. If the
   // strands are horizontal, n = Float64_Max.
   Float64 GetHarpedStrandSlope( Float64 distFromStart ) const;

   //------------------------------------------------------------------------
   // Returns the slope of the specified number harped strand in the form 1:n. 
   // If the strands are horizontal, n = DBL_MAX.
   Float64 GetHarpedStrandSlope( StrandIndexType nStrands, Float64 distFromStart,const gpSize2d& endShift,const gpSize2d& hpShift ) const;

   //------------------------------------------------------------------------
   StrandIndexType GetMaxStraightStrands() const;

   //------------------------------------------------------------------------
   StrandIndexType GetMaxHarpedStrands() const;

   //------------------------------------------------------------------------
   StrandIndexType GetMaxTemporaryStrands() const;

   //------------------------------------------------------------------------
   StrandIndexType GetMaxStrands(bool bIncTemp = false) const;

   //------------------------------------------------------------------------
   // Adds a harped strand in accordance with the strand pattern. Returns true
   // if successful, otherwise false.
   bool AddHarpedStrand();

   //------------------------------------------------------------------------
   // Adds a straight strand in accordance with the strand pattern. Returns
   // true if successful, otherwise false.
   bool AddStraightStrand();

   //------------------------------------------------------------------------
   // Adds a temporary strand in accordance with the strand pattern. Returns
   // true if successful, otherwise false.
   bool AddTemporaryStrand();

   //------------------------------------------------------------------------
   // Remove a harped strand in accordance with the strand pattern. Returns true
   // if successful, otherwise false.
   bool RemoveHarpedStrand();

   //------------------------------------------------------------------------
   // Remove a straight strand in accordance with the strand pattern. Returns
   // true if successful, otherwise false.
   bool RemoveStraightStrand();

   //------------------------------------------------------------------------
   // Removes a temporary strand in accordance with the strand pattern. Returns
   // true if successful, otherwise false.
   bool RemoveTemporaryStrand();

   //------------------------------------------------------------------------
   // Sets the number of harped strands.  If nStrands does not fit correctly
   // into the strand pattern, the number of strands in the girder is not
   // changed and the next highest number of strands is returned, or the max
   // number of strands if nStrands is greater than the max.  Zero is returned
   // if the strand cound is modified successfully.
   StrandIndexType SetNumHarpedStrands( StrandIndexType nStrands );

   //------------------------------------------------------------------------
   // Sets the number of straight strands.  If nStrands does not fit correctly
   // into the strand pattern, the number of strands in the girder is not
   // changed and the next highest number of strands is returned, or the max
   // number of strands if nStrands is greater than the max.  Zero is returned
   // if the strand cound is modified successfully.
   StrandIndexType SetNumStraightStrands( StrandIndexType nStrands );

   //------------------------------------------------------------------------
   // Sets the number of temporary strands.  If nStrands does not fit correctly
   // into the strand pattern, the number of strands in the girder is not
   // changed and the next highest number of strands is returned, or the max
   // number of strands if nStrands is greater than the max.  Zero is returned
   // if the strand cound is modified successfully.
   StrandIndexType SetNumTemporaryStrands( StrandIndexType nStrands );

   //------------------------------------------------------------------------
   // Returns the number of straight strands in the girder.
   StrandIndexType GetNumStraightStrands() const;

   //------------------------------------------------------------------------
   // Returns the number of harped strands in the girder.
   StrandIndexType GetNumHarpedStrands() const;

   //------------------------------------------------------------------------
   // Returns the number of temporary strands in the girder.
   StrandIndexType GetNumTemporaryStrands() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns the concrete material for this girder.
   const matConcreteEx* GetConcrete() const;

   //------------------------------------------------------------------------
   // Returns the prestressing strand material for this girder.
   const matPsStrand* GetStrand() const;

   //------------------------------------------------------------------------
   // Returns a copy of the straight strand pattern
   bmfStrandPattern GetStraightStrandPattern() const;

   //------------------------------------------------------------------------
   // Returns a copy of the harped strand pattern
   bmfStrandPattern GetEndStrandPattern() const;

   //------------------------------------------------------------------------
   // Returns a copy of the harped strand pattern
   bmfStrandPattern GetHPStrandPattern() const;

   //------------------------------------------------------------------------
   // Returns a copy of the temporary strand pattern
   bmfStrandPattern GetTemporaryStrandPattern() const;

   //------------------------------------------------------------------------
   // Shifts the strand pattern at the ends of the girder, toward the bottom
   // of the girder by the amount dy.
   void ShiftHarpedStrandPattern(Float64 dy);

   //------------------------------------------------------------------------
   // Returns the distance that the harped strand pattern is shifted.
   Float64 GetHarpedStrandPatternShift() const;

   //------------------------------------------------------------------------
   // Shifts the harped strand bundle pattern by dy.  If dy is greater than
   // zero, the bundle is moved towards the top of the girder.
   void ShiftBundlePattern(Float64 dy);

   //------------------------------------------------------------------------
   // Returns the bundle pattern shift.
   Float64 GetBundlePatternShift() const;

   //------------------------------------------------------------------------
   // Resets the harped strand and bundle pattern shifts.
   void ResetHarpedStrandShift();

   //------------------------------------------------------------------------
   // Number of hs bundles
   Uint32 GetNumberOfBundles() const;

   //------------------------------------------------------------------------
   // Position of the ith bundle measured from bottom of girder
   Float64 GetBundlePosition(Uint32 bundleIdx) const;

   //------------------------------------------------------------------------
   // Max number of strands that can be place in ith bundle. 
   Int16 GetMaxStrandsInBundle(Uint32 bundleIdx) const;

   //------------------------------------------------------------------------
   // Returns the number of harping points in the girder.
   Uint32 GetHarpingPointCount() const;

   //------------------------------------------------------------------------
   // Returns the location of the harping points, measured from left
   // end of the girder.
   void GetHarpingPointLocations(Float64* pHpLoc1, Float64* pHpLoc2) const;

   //------------------------------------------------------------------------
   bmfPrecastGirderTemplate* GetTemplate();
   const bmfPrecastGirderTemplate* GetTemplate() const;

   //------------------------------------------------------------------------
   // Get long. reinforcement layout
   const bmfLrLayout& GetLrLayout() const;

   //------------------------------------------------------------------------
   // Set long. reinforcement layout
   void SetLrLayout(const bmfLrLayout& rLayout);


   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void UpdateTopFlangeCorners();

   //------------------------------------------------------------------------
   void MakeCopy( const bmfPrecastGirder& rOther );

   //------------------------------------------------------------------------
   void MakeAssignment( const bmfPrecastGirder& rOther );

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // Four corner points for the top flange rectangle
   CComPtr<IPoint2d> m_StartLeft;
   CComPtr<IPoint2d> m_StartRight;
   CComPtr<IPoint2d> m_EndLeft;
   CComPtr<IPoint2d> m_EndRight;

   gpSize2d m_EndShift;
   gpSize2d m_HpShift;

   Float64 m_HpLoc1;
   Float64 m_HpLoc2;

   // Need to keep a local copy because the template's copy is read-only
   bmfStrandPattern m_SsPtrn;
   bmfStrandPattern m_TmpPtrn;
   bmfStrandPattern m_EndPtrn;
   bmfStrandPattern m_HPPtrn;

   // need local copy of layout since layout points back to this
   bmfLrLayout m_LrLayout;

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

#endif // INCLUDED_BRIDGEMODELING_PRECASTGIRDER_H_

