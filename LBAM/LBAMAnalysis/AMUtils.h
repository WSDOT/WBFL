///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2024  Washington State Department of Transportation
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

#ifndef __AMUtils_H_
#define __AMUtils_H_

#pragma once

#include "resource.h"

#include <WBFLFem2d.h>

#include "WBFLLBAMAnalysis.h"
#include "LBAMUtils.h"

#include <set>
#include <vector>
#include <algorithm>
#include <sstream>

#include <memory>

#include <MathEx.h>



#define FX 0
#define FY 1
#define MZ 2
#define DX 3
#define DY 4
#define RZ 5


/////////////////////////////////////////////////////////
// local helper classes and utilities

// Mapping type to a location on LBam member to a Fem2d member
   enum MemberLocationType {mltRightEnd , mltInternal, mltStraddle, mltLeftEnd, mltNotFound=-1};

//////////////////////////////////////////////////////////
// utility class for keeping track of node locations on Substructure (supports)
//////////////////////////////////////////////////////////
enum SubNodeReason{ sbnrSupportEnd=1, sbnrSegmentEnd=2};

class SubNodeLoc
{
public:
   SubNodeLoc(Float64 locx, Float64 locy, SubNodeReason reason, ISegmentCrossSection* pSegmentCrossSection=nullptr );
   bool operator< (const SubNodeLoc& other) const;
   bool IsReason(SubNodeReason reason) const;
   void Assimilate(const SubNodeLoc& rother);
   void GetSegmentCrossSection(ISegmentCrossSection** ppSegmentCrossSection);
   void SetSegmentCrossSection(ISegmentCrossSection* section);
   Float64 GetXLoc() const;
   Float64 GetYLoc() const;
   Float64 Distance(const SubNodeLoc& rother) const;

public:
   JointIDType m_FemJointID;

private:
   Float64                 m_xLoc;
   Float64                 m_yLoc;
   long                   m_Reason;
   CComPtr<ISegmentCrossSection> m_pSegmentCrossSection; // applies to member to left (below) node
private:
   SubNodeLoc();
};

class SubNodeLocs: public std::set<SubNodeLoc>

{
public:
   SubNodeLocs();

   BoundaryConditionType m_BC; // bc at support bottom
   VARIANT_BOOL          m_TopRelease; // is a hinge at the top
   SupportIDType         m_LbamTemporarySupportID; // applicable to temporary supports only
};

using SubNodeLocIterator = SubNodeLocs::iterator;


////////////////////////////////////////////////////////////////////////////////////////
// utility class for extracting superstructure node layout information
////////////////////////////////////////////////////////////////////////////////////////
enum SuperNodeReason{ nrSpanEnd=1, nrTemporarySupport=2, nrTemporarySupportLoc=4, nrMemberEnd=8, nrSegmentEnd=16};
enum MemberRelease {mrFixed=0, mrLeftPinned=1, mrRightPinned=4, mrLeftAxial=8, mrRightAxial=16};

// If superstructure elements are very short, they can be "condensed" out of the model. This means that they
// assimilate with the node to the left or right in order to avoid numerical badness
enum CondenseType {notCondensed,
                   leftCondensed,  // assimilated to ssm on left
                   rightCondensed};// assimilated to ssm on right

class SuperNodeLoc
{
public:

   SuperNodeLoc(Float64 loc, SuperNodeReason reason, ISegmentCrossSection* pSegmentCrossSection=nullptr );
   SuperNodeLoc(const SuperNodeLoc& other);
   bool operator< (const SuperNodeLoc& other) const;
   bool IsReason(SuperNodeReason reason) const;
   void Assimilate(SuperNodeLoc& rother, CondenseType side);
   void GetSegmentCrossSection(ISegmentCrossSection** ppSegmentCrossSection);
   void SetSegmentCrossSection(ISegmentCrossSection* section);
   Float64 GetLoc() const;
   void SetRelease(MemberRelease rel);
   bool IsPinned(Side side) const;
   bool HasAxialRelease(Side side) const;
   SubNodeLocs* GetSubNodeLocs();
   CondenseType GetCondenseType() const;
   

public:
   JointIDType                m_FemJointID;        // joint ID in the fem model
   SupportIDType              m_LBamTempSupportID; // temporary support id - only valid if this is a temporary support location

private:
   Float64                    m_Loc;
   long                       m_Reason;
   long                       m_Release;
   CComPtr<ISegmentCrossSection>     m_pSegmentCrossSection; // applies to member to left of node
   std::shared_ptr<SubNodeLocs> m_SubNodeLocs;   // only applicable if m_Reason is nrSpanEnd or nrTemporarySupport
   CondenseType m_CondenseType;
private:
   SuperNodeLoc();
};

using SuperNodeLocs = std::set<SuperNodeLoc>;
using SuperNodeLocIterator = SuperNodeLocs::iterator;


////////////////////////////////////////////////////////////////////////////////////////
// Utility class for influence load location information
//////////////////////////////////////////////////////////
struct InfluenceLoadLocation
{
   PoiIDType              m_LBAMPoiID;
   Float64                m_GlobalX;  // X in LBAM global coordinates
   InfluenceLocationType m_LocationType;
   MemberIDType           m_FemMemberID;
   Float64                m_FemMemberLoc;
   LoadCaseIDType         m_FemLoadCaseID;  // Fem load case assigned to this unit load

   Float64 m_P;

   // constructor for member-based locations
   InfluenceLoadLocation(PoiIDType poiID,Float64 globalX, MemberIDType mbrId, Float64 mbrLoc,Float64 P);

   // for container life
   bool operator< (const InfluenceLoadLocation& other) const;

private:
   InfluenceLoadLocation();
};

using InfluenceLoadSet = std::vector<InfluenceLoadLocation>;
using InfluenceLoadSetIterator = InfluenceLoadSet::iterator;


////////////////////////////////////////////////////////////////////////////////////////
// Utility class for storing poi information locally
//
// This class caches information about how lbam pois relate the fem model, and also stress factors
//////////////////////////////////////////////////////////
class PoiMap
{
public:
   // Base utility class for storing poi creation data meant to live in a set container. 
   // Each poi can be either internal or externally generated. External
   // External POI's are pois in the LBAM Model. Internal POI's are used by the analysis engine and are not
   // accessible by outside clients.


   // Instantiations of this base class are used for searching purposes only 
   PoiMap(PoiIDType lbamPoiID);

protected:
   // used by offspring
   PoiMap(PoiIDType lbamPoiID, Float64 globalX, MemberType mType, MemberIDType memberID, Float64 lbamPoiLocation);

public:
   virtual ~PoiMap();


   // virtual functions to get poi results from underlying fem model
   virtual void GetDeflection(LoadGroupIDType lgId, IFem2dModel* pFemMdl, Float64* leftDx, Float64* leftDy, Float64* leftRz, Float64* rightDx, Float64* rightDy, Float64* rightRz);
   virtual void GetForce(LoadGroupIDType lgId, IFem2dModel* pFemMdl, ResultsOrientation Orientation, Float64* fxLeft, Float64* fyLeft, Float64* mzLeft, Float64* fxRight, Float64* fyRight, Float64* mzRight);
   virtual void GetInfluenceLines(IFem2dModel* pFemMdl, InfluenceLoadSet& influenceLoadSet,
                                  ResultsOrientation forceOrientation,  Float64 forceZeroTolerance, Float64 deflZeroTolerance, 
                                  IInfluenceLine** pLeftAxialInfl,  IInfluenceLine** pRightAxialInfl,
                                  IInfluenceLine** pLeftShearInfl,  IInfluenceLine** pRightShearInfl,
                                  IInfluenceLine** pLeftMomentInfl, IInfluenceLine** pRightMomentInfl, 
                                  IInfluenceLine** pLeftDxInfl,     IInfluenceLine** pRightDxInfl,
                                  IInfluenceLine** pLeftDyInfl,     IInfluenceLine** pRightDyInfl, 
                                  IInfluenceLine** pLeftRzInfl,     IInfluenceLine** pRightRzInfl);
   virtual std::_tstring GetDescription() const;
   PoiIDType GetLBAMPoiID() const;
   void AddAlternateLBAMPoiID(PoiIDType id);
   const std::vector<PoiIDType>& GetAlternateLBAMPoiIDs() const;
   void SetIsInternallyGenerated(bool is);
   bool GetIsInternallyGenerated() const;
   MemberType GetLBAMMemberType() const;
   MemberIDType GetLBAMMemberID() const;
   Float64 GetLBAMPoiLocation() const;
   Float64 GetLocation() const;
   MemberLocationType GetMemberLocationType() const;
   void SetSegmentCrossSection(ISegmentCrossSection* leftSegmentCrossSection, ISegmentCrossSection* rightSegmentCrossSection);
   void GetSegmentCrossSection(ISegmentCrossSection** leftSegmentCrossSection, ISegmentCrossSection** rightSegmentCrossSection);
   void SetStressPoints(IStressPoints* leftStressPoints, IStressPoints* rightStressPoints);
   void GetStressPoints(IStressPoints** leftStressPoints, IStressPoints** rightStressPoints);
   bool operator< (const PoiMap& other) const;
   bool operator==(const PoiMap& other) const;

   // less operator for sorting by global location - doesn't squeeze out duplicate locations
   static bool LocLess(PoiMap* left, PoiMap* right);
   static bool LocLessSqueeze(PoiMap* left, PoiMap* right);

protected:
   PoiMap();

   PoiIDType    m_LBAMPoiID;
   std::vector<PoiIDType> m_AlternateLBAMPoiIDs;
   MemberType   m_LBAMMemberType;
   MemberIDType m_LBAMMemberID;
   Float64      m_LBAMPoiLocation;

   bool m_InternallyGenerated;
   Float64 m_GlobalX;
   MemberLocationType     m_MemberLocationType;
   CComPtr<ISegmentCrossSection> m_LeftSegmentCrossSection;
   CComPtr<ISegmentCrossSection> m_RightSegmentCrossSection;

   CComPtr<IStressPoints> m_LeftStressPoints;
   CComPtr<IStressPoints> m_RightStressPoints;

};


// A poimap that maps lbam pois to fem2d pois
class PoiMapToFemPoi: public PoiMap
{
public:
   PoiMapToFemPoi(PoiIDType lbamPoiID, Float64 globalX, MemberType mType, MemberIDType memberID, Float64 lbamPoiLocation);
   void SetFemPoi(PoiIDType id);
   PoiIDType GetFemPoiID() const;
   void SetMemberLocationType(MemberLocationType type);
   virtual void GetDeflection(LoadGroupIDType loadGroupID, IFem2dModel* pFemMdl, Float64* leftDx, Float64* leftDy, Float64* leftRz, Float64* rightDx, Float64* rightDy, Float64* rightRz) override;
   virtual void GetForce(LoadGroupIDType loadGroupID, IFem2dModel* pFemMdl, ResultsOrientation Orientation, Float64* fxLeft, Float64* fyLeft, Float64* mzLeft, Float64* fxRight, Float64* fyRight, Float64* mzRight) override;
   virtual void GetInfluenceLines(IFem2dModel* pFemMdl, InfluenceLoadSet& influenceLoadSet,
                                  ResultsOrientation forceOrientation,  Float64 forceZeroTolerance, 
                                  Float64 deflZeroTolerance, 
                                  IInfluenceLine** pLeftAxialInfl,  IInfluenceLine** pRightAxialInfl,
                                  IInfluenceLine** pLeftShearInfl,  IInfluenceLine** pRightShearInfl,
                                  IInfluenceLine** pLeftMomentInfl, IInfluenceLine** pRightMomentInfl, 
                                  IInfluenceLine** pLeftDxInfl,     IInfluenceLine** pRightDxInfl,
                                  IInfluenceLine** pLeftDyInfl,     IInfluenceLine** pRightDyInfl, 
                                  IInfluenceLine** pLeftRzInfl,     IInfluenceLine** pRightRzInfl) override;

   virtual std::_tstring GetDescription() const override;

private:
   PoiIDType  m_FemPoiID;
};


// A poimap that maps lbam pois to fem2d member ends
// Actually maps to fem POI at the end of the left member and at the start of the right member
class PoiMapToFemMbr: public PoiMap
{
public:
   PoiMapToFemMbr(PoiIDType lbamPoiID, Float64 globalX, MemberType mType, MemberIDType memberID, Float64 lbamPoiLocation);
   void SetFemPoiID(PoiIDType leftPoiID, PoiIDType rightPoiID);
   MemberIDType GetLeftPoiID() const;
   MemberIDType GetRightPoiID() const;
   virtual void GetDeflection(LoadGroupIDType loadGroupID, IFem2dModel* pFemMdl, Float64* leftDx, Float64* leftDy, Float64* leftRz, Float64* rightDx, Float64* rightDy, Float64* rightRz) override;
   virtual void GetForce(LoadGroupIDType loadGroupID, IFem2dModel* pFemMdl, ResultsOrientation Orientation, Float64* fxLeft, Float64* fyLeft, Float64* mzLeft, Float64* fxRight, Float64* fyRight, Float64* mzRight) override;
   virtual void GetInfluenceLines(IFem2dModel* pFemMdl, InfluenceLoadSet& influenceLoadSet,
                                  ResultsOrientation forceOrientation,  Float64 forceZeroTolerance, 
                                  Float64 deflZeroTolerance, 
                                  IInfluenceLine** pLeftAxialInfl,  IInfluenceLine** pRightAxialInfl,
                                  IInfluenceLine** pLeftShearInfl,  IInfluenceLine** pRightShearInfl,
                                  IInfluenceLine** pLeftMomentInfl, IInfluenceLine** pRightMomentInfl, 
                                  IInfluenceLine** pLeftDxInfl,     IInfluenceLine** pRightDxInfl,
                                  IInfluenceLine** pLeftDyInfl,     IInfluenceLine** pRightDyInfl, 
                                  IInfluenceLine** pLeftRzInfl,     IInfluenceLine** pRightRzInfl) override;
   virtual std::_tstring GetDescription() const override;


private:
   PoiIDType   m_LeftPoiID;
   PoiIDType   m_RightPoiID;
};


// some useful predicates and stl container typedefs for PoiMap's
struct PoiMapLess
{
   bool operator ()(PoiMap* left, PoiMap* right) const
   {
      return left->GetLBAMPoiID() < right->GetLBAMPoiID();
   }
};


struct PoiMapIdMatch
{
   PoiMapIdMatch(PoiIDType id):
   m_ID(id)
   {;}

   bool operator ()(PoiMap* val) const
   {
      if ( m_ID == val->GetLBAMPoiID() )
         return true;

      const std::vector<PoiIDType>& vAlternates(val->GetAlternateLBAMPoiIDs());
      std::vector<PoiIDType>::const_iterator iter(vAlternates.begin());
      std::vector<PoiIDType>::const_iterator end(vAlternates.end());
      for ( ; iter != end; iter++ )
      {
         if ( m_ID == *iter )
            return true;
      }

      return false;
   }

private:
   PoiIDType m_ID;
};


using PoiMapCollection = std::set<PoiMap*, PoiMapLess>;
using PoiMapIterator = PoiMapCollection::iterator;


////////////////////////////////////////////////////////////////////////////////////////
// utility class to help deal with messy logic required to generate minimum poi spacing
////////////////////////////////////////////////////////////////////////////////////////
class SortedPoiMapTracker: public std::vector<PoiMap*>
{
public:
   SortedPoiMapTracker(PoiMapCollection& PoiMaps, bool squeezeDuplicates=false);

   // reset to beginning of collection
   void Reset();

   // test if a poi is at an exact location along a span or ssm
   bool IsPoiAtLocation(MemberType mbrType, MemberIDType mbrID, Float64 globalX, PoiIDType* poiIDAtLoc=nullptr);

   // test if a poi is at or between the next location and the most-recently found location
   bool IsPoiAtNextLocation(Float64 nextX, Float64* foundX);

   // Determine if adequate pois are at a location to cover a jump in values. 
   // This is needed for Hinges, TemporarySupports and SSM's over supports
   // Returns what pois are needed to 'cover' this location.
   enum PoiCoveredRes {Both=0, Left=1, Right=2, None=3};

   // Tests to see if there is already a POI at the specified location. If the result type is None
   // there is a POI there and pCoveredID holds the LBAMPoiID for that POI.
   PoiCoveredRes IsPoiCovered(Float64 globalX, IFem2dPOICollection* pFemPois, Float64 tolerance,PoiIDType* pCoveredID);

private:
   SortedPoiMapTracker();

   // cursor
   iterator m_Cursor;

};

#endif