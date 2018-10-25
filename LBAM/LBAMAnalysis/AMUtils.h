///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
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

#include <MathEx.h>

#include <boost\shared_ptr.hpp>

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
   SubNodeLoc(Float64 locx, Float64 locy, SubNodeReason reason, ISegmentCrossSection* pSegmentCrossSection=NULL );
   bool operator< (const SubNodeLoc& other) const;
   bool IsReason(SubNodeReason reason);
   void Assimilate(const SubNodeLoc& rother);
   void GetSegmentCrossSection(ISegmentCrossSection** ppSegmentCrossSection);
   void SetSegmentCrossSection(ISegmentCrossSection* section);
   Float64 GetXLoc();
   Float64 GetYLoc();
   Float64 Distance(const SubNodeLoc& rother);

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

typedef SubNodeLocs::iterator SubNodeLocIterator;


////////////////////////////////////////////////////////////////////////////////////////
// utility class for extracting superstructure node layout information
////////////////////////////////////////////////////////////////////////////////////////
enum SuperNodeReason{ nrSpanEnd=1, nrTemporarySupport=2, nrTemporarySupportLoc=4, nrMemberEnd=8, nrSegmentEnd=16};
enum MemberRelease {mrFixed=0, mrLeftPinned=1, mrRightPinned=4};

class SuperNodeLoc
{
public:
   SuperNodeLoc(Float64 loc, SuperNodeReason reason, ISegmentCrossSection* pSegmentCrossSection=NULL );
   SuperNodeLoc(const SuperNodeLoc& other);
   bool operator< (const SuperNodeLoc& other) const;
   bool IsReason(SuperNodeReason reason);
   void Assimilate(const SuperNodeLoc& rother);
   void GetSegmentCrossSection(ISegmentCrossSection** ppSegmentCrossSection);
   void SetSegmentCrossSection(ISegmentCrossSection* section);
   Float64 GetLoc();
   void SetRelease(MemberRelease rel);
   bool IsPinned(Side side);
   SubNodeLocs* GetSubNodeLocs();

public:
   JointIDType                m_FemJointID;        // joint ID in the fem model
   SupportIDType              m_LBamTempSupportID; // temporary support id - only valid if this is a temporary support location

private:
   Float64                    m_Loc;
   long                       m_Reason;
   long                       m_Release;
   CComPtr<ISegmentCrossSection>     m_pSegmentCrossSection; // applies to member to left of node
   boost::shared_ptr<SubNodeLocs> m_SubNodeLocs;   // only applicable if m_Reason is nrSpanEnd or nrTemporarySupport
private:
   SuperNodeLoc();
};

typedef std::set<SuperNodeLoc>  SuperNodeLocs;
typedef SuperNodeLocs::iterator SuperNodeLocIterator;


////////////////////////////////////////////////////////////////////////////////////////
// Utility class for influence load location information
//////////////////////////////////////////////////////////
struct InfluenceLoadLocation
{
   Float64                m_GlobalX;  // X in LBAM global coordinates
   InfluenceLocationType m_LocationType;
   MemberIDType           m_FemMemberID;
   Float64                m_FemMemberLoc;
   LoadCaseIDType         m_FemLoadCaseID;  // Fem load case assigned to this unit load

   // constructor for member-based locations
   InfluenceLoadLocation(Float64 globalX, MemberIDType mbrId, Float64 mbrLoc);

   // for container life
   bool operator< (const InfluenceLoadLocation& other) const;

private:
   InfluenceLoadLocation();
};

typedef std::set<InfluenceLoadLocation>    InfluenceLoadSet;
typedef InfluenceLoadSet::iterator         InfluenceLoadSetIterator;


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
   virtual void GetDeflection(long lgId, IFem2dModel* pFemMdl, Float64* leftDx, Float64* leftDy, Float64* leftRz, Float64* rightDx, Float64* rightDy, Float64* rightRz);
   virtual void GetForce(long lgId, IFem2dModel* pFemMdl, ResultsOrientation Orientation, Float64* fxLeft, Float64* fyLeft, Float64* mzLeft, Float64* fxRight, Float64* fyRight, Float64* mzRight);
   virtual void GetInfluenceLines(IFem2dModel* pFemMdl, InfluenceLoadSet& influenceLoadSet,
                                  ResultsOrientation forceOrientation,  Float64 forceZeroTolerance, Float64 deflZeroTolerance, 
                                  IInfluenceLine** pLeftAxialInfl,  IInfluenceLine** pRightAxialInfl,
                                  IInfluenceLine** pLeftShearInfl,  IInfluenceLine** pRightShearInfl,
                                  IInfluenceLine** pLeftMomentInfl, IInfluenceLine** pRightMomentInfl, 
                                  IInfluenceLine** pLeftDxInfl,     IInfluenceLine** pRightDxInfl,
                                  IInfluenceLine** pLeftDyInfl,     IInfluenceLine** pRightDyInfl, 
                                  IInfluenceLine** pLeftRzInfl,     IInfluenceLine** pRightRzInfl);
   virtual std::string GetDescription() const;
   PoiIDType GetLBAMPoiID() const;
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
   void SetFemPoi(PoiIDType id, Float64 femMbrLoc);
   PoiIDType GetFemPoiID() const;
   Float64 GetFemPoiMbrLocation() const;
   void SetMemberLocationType(MemberLocationType type);
   virtual void GetDeflection(LoadGroupIDType loadGroupID, IFem2dModel* pFemMdl, Float64* leftDx, Float64* leftDy, Float64* leftRz, Float64* rightDx, Float64* rightDy, Float64* rightRz);
   virtual void GetForce(LoadGroupIDType loadGroupID, IFem2dModel* pFemMdl, ResultsOrientation Orientation, Float64* fxLeft, Float64* fyLeft, Float64* mzLeft, Float64* fxRight, Float64* fyRight, Float64* mzRight);
   virtual void GetInfluenceLines(IFem2dModel* pFemMdl, InfluenceLoadSet& influenceLoadSet,
                                  ResultsOrientation forceOrientation,  Float64 forceZeroTolerance, 
                                  Float64 deflZeroTolerance, 
                                  IInfluenceLine** pLeftAxialInfl,  IInfluenceLine** pRightAxialInfl,
                                  IInfluenceLine** pLeftShearInfl,  IInfluenceLine** pRightShearInfl,
                                  IInfluenceLine** pLeftMomentInfl, IInfluenceLine** pRightMomentInfl, 
                                  IInfluenceLine** pLeftDxInfl,     IInfluenceLine** pRightDxInfl,
                                  IInfluenceLine** pLeftDyInfl,     IInfluenceLine** pRightDyInfl, 
                                  IInfluenceLine** pLeftRzInfl,     IInfluenceLine** pRightRzInfl);

   virtual std::string GetDescription() const;

private:
   PoiIDType  m_FemPoiID;
   Float64 m_FemMbrLoc;

};


// A poimap that maps lbam pois to fem2d member ends
class PoiMapToFemMbr: public PoiMap
{
public:
   PoiMapToFemMbr(PoiIDType lbamPoiID, Float64 globalX, MemberType mType, MemberIDType memberID, Float64 lbamPoiLocation);
   void SetFemMbrs(MemberIDType leftID, MemberIDType rightID);
   MemberIDType GetLeftMbrID() const;
   MemberIDType GetRightMbrID() const;
   virtual void GetDeflection(LoadGroupIDType loadGroupID, IFem2dModel* pFemMdl, Float64* leftDx, Float64* leftDy, Float64* leftRz, Float64* rightDx, Float64* rightDy, Float64* rightRz);
   virtual void GetForce(LoadGroupIDType loadGroupID, IFem2dModel* pFemMdl, ResultsOrientation Orientation, Float64* fxLeft, Float64* fyLeft, Float64* mzLeft, Float64* fxRight, Float64* fyRight, Float64* mzRight);
   virtual void GetInfluenceLines(IFem2dModel* pFemMdl, InfluenceLoadSet& influenceLoadSet,
                                  ResultsOrientation forceOrientation,  Float64 forceZeroTolerance, 
                                  Float64 deflZeroTolerance, 
                                  IInfluenceLine** pLeftAxialInfl,  IInfluenceLine** pRightAxialInfl,
                                  IInfluenceLine** pLeftShearInfl,  IInfluenceLine** pRightShearInfl,
                                  IInfluenceLine** pLeftMomentInfl, IInfluenceLine** pRightMomentInfl, 
                                  IInfluenceLine** pLeftDxInfl,     IInfluenceLine** pRightDxInfl,
                                  IInfluenceLine** pLeftDyInfl,     IInfluenceLine** pRightDyInfl, 
                                  IInfluenceLine** pLeftRzInfl,     IInfluenceLine** pRightRzInfl);
   virtual std::string GetDescription() const;


private:
   MemberIDType   m_LftMbrID;
   MemberIDType   m_RgtMbrID;
};


// some useful predicates and stl container typedefs for PoiMap's
struct PoiMapLess: public std::binary_function<PoiMap*,PoiMap*,int>
{
   bool operator ()(PoiMap* left, PoiMap* right) const
   {
      return left->GetLBAMPoiID() < right->GetLBAMPoiID();
   }
};


struct PoiMapIdMatch: public std::unary_function<PoiMap*,bool>
{
   PoiMapIdMatch(PoiIDType id):
   m_ID(id)
   {;}

   bool operator ()(PoiMap* val) const
   {
      return m_ID == val->GetLBAMPoiID();
   }

private:
   PoiIDType m_ID;
};


typedef std::set<PoiMap*, PoiMapLess>           PoiMapCollection;
typedef PoiMapCollection::iterator PoiMapIterator;


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
   bool IsPoiAtLocation(MemberType mbrType, MemberIDType mbrID, Float64 globalX, PoiIDType* poiIDAtLoc=NULL);

   // test if a poi is at or between the next location and the most-recently found location
   bool IsPoiAtNextLocation(Float64 nextX, Float64* foundX);

   // Determine if adequate pois are at a location to cover a jump in values. 
   // This is needed for Hinges, TemporarySupports and SSM's over supports
   // Returns what pois are needed to 'cover' this location.
   enum PoiCoveredRes {Both=0, Left=1, Right=2, None=3};

   PoiCoveredRes IsPoiCovered(Float64 globalX, IFem2dPOICollection* pFemPois, Float64 tolerance);

private:
   SortedPoiMapTracker();

   // cursor
   iterator m_Cursor;

};

#endif