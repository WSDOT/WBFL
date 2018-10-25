///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2013  Washington State Department of Transportation
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


#include "stdafx.h"
#include "AMUtils.h"
#include "LBAMAnalysis.hh"
#include "InfluenceLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SubNodeLoc::SubNodeLoc(Float64 locx, Float64 locy, SubNodeReason reason, ISegmentCrossSection* pSegmentCrossSection ):
   m_xLoc(locx),
   m_yLoc(locy),
   m_Reason(reason),
   m_pSegmentCrossSection(pSegmentCrossSection),
   m_FemJointID(-1)
{
}

bool SubNodeLoc::operator< (const SubNodeLoc& other) const
{ 
   return m_yLoc<other.m_yLoc; 
}

bool SubNodeLoc::IsReason(SubNodeReason reason)
{
   return (m_Reason & reason)!=0;
}

void SubNodeLoc::Assimilate(const SubNodeLoc& rother)
{
   // called when another node is too close to this one - take its traits
   m_Reason  |= rother.m_Reason;

   if (m_pSegmentCrossSection==NULL)
   {
      m_pSegmentCrossSection = rother.m_pSegmentCrossSection;
   }
}

void SubNodeLoc::GetSegmentCrossSection(ISegmentCrossSection** ppSegmentCrossSection)
{
   (*ppSegmentCrossSection) = m_pSegmentCrossSection;
   if ( m_pSegmentCrossSection )
      (*ppSegmentCrossSection)->AddRef();
}

void SubNodeLoc::SetSegmentCrossSection(ISegmentCrossSection* section)
{
   ATLASSERT(m_pSegmentCrossSection==NULL);
   ATLASSERT(section!=NULL);
   m_pSegmentCrossSection = section;
}

Float64 SubNodeLoc::GetXLoc()
{
   return m_xLoc;
}

Float64 SubNodeLoc::GetYLoc()
{
   return m_yLoc;
}

Float64 SubNodeLoc::Distance(const SubNodeLoc& rother)
{
   Float64 dx = m_xLoc - rother.m_xLoc;
   Float64 dy = m_yLoc - rother.m_yLoc;
   return sqrt( dx*dx + dy*dy);
}

/////////////////////////////////////////////////////////////

SubNodeLocs::SubNodeLocs():
     m_BC(bcPinned),
     m_TopRelease(VARIANT_FALSE),
     m_LbamTemporarySupportID(0)
{
}

/////////////////////////////////////////////////////////////

SuperNodeLoc::SuperNodeLoc(Float64 loc, SuperNodeReason reason, ISegmentCrossSection* pSegmentCrossSection ):
   m_Loc(loc),
   m_Reason(reason),
   m_pSegmentCrossSection(pSegmentCrossSection),
   m_Release(mrFixed),
   m_LBamTempSupportID(-1),
   m_FemJointID(-1)
{
}

SuperNodeLoc::SuperNodeLoc(const SuperNodeLoc& other)
{
   m_FemJointID = other.m_FemJointID;
   m_LBamTempSupportID = other.m_LBamTempSupportID;
   m_Loc        = other.m_Loc;
   m_Reason     = other.m_Reason;
   m_Release    = other.m_Release;
   m_pSegmentCrossSection = other.m_pSegmentCrossSection;
   m_SubNodeLocs   = other.m_SubNodeLocs;
}

bool SuperNodeLoc::operator< (const SuperNodeLoc& other) const
{ 
   // RAB: There are some numerical problems with numbers that are equal 
   //      returning true for the < comparison. It is a problem with
   //      internal accuracty. Adding a quick check for equality to eliminate
   //      the problem.
   if ( IsEqual(m_Loc,other.m_Loc) )
      return false;


   return m_Loc < other.m_Loc; 
}

bool SuperNodeLoc::IsReason(SuperNodeReason reason)
{
   return (m_Reason & reason)!=0;
}

void SuperNodeLoc::Assimilate(const SuperNodeLoc& rother)
{
   // called when another node is too close to this one - take its traits
   m_Reason  |= rother.m_Reason;
   m_Release |= rother.m_Release;

   if (m_pSegmentCrossSection==NULL)
   {
      m_pSegmentCrossSection = rother.m_pSegmentCrossSection;
   }
}

void SuperNodeLoc::GetSegmentCrossSection(ISegmentCrossSection** ppSegmentCrossSection)
{
   (*ppSegmentCrossSection) = m_pSegmentCrossSection;
   if ( m_pSegmentCrossSection )
      (*ppSegmentCrossSection)->AddRef();
}

void SuperNodeLoc::SetSegmentCrossSection(ISegmentCrossSection* section)
{
   ATLASSERT(m_pSegmentCrossSection==NULL);
   ATLASSERT(section!=NULL);
   m_pSegmentCrossSection = section;
}

Float64 SuperNodeLoc::GetLoc()
{
   return m_Loc;
}

void SuperNodeLoc::SetRelease(MemberRelease rel)
{
   if (rel == mrFixed)
   {
      m_Release = mrFixed;
   }
   else
   {
      m_Release |= rel;
   }
}

bool SuperNodeLoc::IsPinned(Side side)
{
   if (side == ssLeft)
      return (m_Release & mrLeftPinned) != 0;
   else
      return (m_Release & mrRightPinned)!= 0;
}

SubNodeLocs* SuperNodeLoc::GetSubNodeLocs()
{
   ATLASSERT(m_Reason&nrSpanEnd || m_Reason&nrTemporarySupport);

   if (m_SubNodeLocs.get() == 0)
      m_SubNodeLocs = boost::shared_ptr<SubNodeLocs>(new SubNodeLocs);

   return m_SubNodeLocs.get();
}


////////////////////////////////////////////////////////////////////////////////////////

InfluenceLoadLocation::InfluenceLoadLocation(PoiIDType poiID,Float64 globalX, MemberIDType mbrId, Float64 mbrLoc,Float64 P):
   m_LBAMPoiID(poiID),
   m_GlobalX(globalX),
   m_LocationType(iflSingle),
   m_FemMemberID(mbrId),
   m_FemMemberLoc(mbrLoc),
   m_FemLoadCaseID(INVALID_ID),
   m_P(P)
   {;}

// for container life
bool InfluenceLoadLocation::operator< (const InfluenceLoadLocation& other) const
{
   if (IsEqual(m_GlobalX, other.m_GlobalX, 1.0e-06))
   {
      // locations are the same - must use tie breaker
      return m_FemMemberID < other.m_FemMemberID;
   }
   else if (m_GlobalX < other.m_GlobalX)
      return true;
   else 
      return false;
}


////////////////////////////////////////////////////////////////////////////////////////

PoiMap::PoiMap(PoiIDType lbamPoiID):
m_LBAMPoiID(lbamPoiID),
m_InternallyGenerated(false),
m_LBAMMemberType(mtUndefined),
m_LBAMMemberID(-1),
m_GlobalX(-1.),
m_MemberLocationType(mltNotFound)
{
}

PoiMap::PoiMap(PoiIDType lbamPoiID, Float64 globalX, MemberType mType, MemberIDType memberID, Float64 lbamPoiLocation):
m_LBAMPoiID(lbamPoiID),
m_LBAMMemberType(mType),
m_LBAMMemberID(memberID),
m_LBAMPoiLocation(lbamPoiLocation),
m_GlobalX(globalX),
m_InternallyGenerated(false),
m_MemberLocationType(mltNotFound)
{
}

PoiMap::~PoiMap()
{
}


   // virtual functions to get poi results from underlying fem model
void PoiMap::GetDeflection(LoadGroupIDType lgId, IFem2dModel* pFemMdl, Float64* leftDx, Float64* leftDy, Float64* leftRz, Float64* rightDx, Float64* rightDy, Float64* rightRz)
{
   ATLASSERT(0); // should not ask for this from search-only poi
}

void PoiMap::GetForce(LoadGroupIDType lgId, IFem2dModel* pFemMdl, ResultsOrientation Orientation, Float64* fxLeft, Float64* fyLeft, Float64* mzLeft, Float64* fxRight, Float64* fyRight, Float64* mzRight)
{
   ATLASSERT(0); // should not ask for this from search-only poi
}

void PoiMap::GetInfluenceLines(IFem2dModel* pFemMdl, InfluenceLoadSet& influenceLoadSet,
                               ResultsOrientation forceOrientation,  Float64 forceZeroTolerance, Float64 deflZeroTolerance, 
                               IInfluenceLine** pLeftAxialInfl,  IInfluenceLine** pRightAxialInfl,
                               IInfluenceLine** pLeftShearInfl,  IInfluenceLine** pRightShearInfl,
                               IInfluenceLine** pLeftMomentInfl, IInfluenceLine** pRightMomentInfl, 
                               IInfluenceLine** pLeftDxInfl,     IInfluenceLine** pRightDxInfl,
                               IInfluenceLine** pLeftDyInfl,     IInfluenceLine** pRightDyInfl, 
                               IInfluenceLine** pLeftRzInfl,     IInfluenceLine** pRightRzInfl)
{
   ATLASSERT(0); // should not ask for this from search-only poi
}

std::_tstring PoiMap::GetDescription() const
{
   std::_tostringstream os;
   os<< _T("Base PoiMap ID = ")<<m_LBAMPoiID<<_T(" MemberType = ")<<long(m_LBAMMemberType)<<
        _T(" Member ID = ")<<m_LBAMMemberID<<_T("LBAMMemberLocation = ")<<m_LBAMPoiLocation<<
        _T(" Global X = ")<<m_GlobalX<<_T(" Internally Generated = ")<<(m_InternallyGenerated ? _T("True "): _T("False "))<<
        _T(" MemberLocationType = ")<<long(m_MemberLocationType);

   return os.str();
}

PoiIDType PoiMap::GetLBAMPoiID() const
{
   return m_LBAMPoiID;
}

void PoiMap::AddAlternateLBAMPoiID(PoiIDType id)
{
   m_AlternateLBAMPoiIDs.push_back(id);
}

const std::vector<PoiIDType>& PoiMap::GetAlternateLBAMPoiIDs() const
{
   return m_AlternateLBAMPoiIDs;
}

void PoiMap::SetIsInternallyGenerated(bool is)
{
   m_InternallyGenerated=is;
}

bool PoiMap::GetIsInternallyGenerated() const
{
   return m_InternallyGenerated;
}

MemberType PoiMap::GetLBAMMemberType() const
{
   return m_LBAMMemberType;
}

MemberIDType PoiMap::GetLBAMMemberID() const
{
   return m_LBAMMemberID;
}

Float64 PoiMap::GetLBAMPoiLocation() const
{
   return m_LBAMPoiLocation;
}

Float64 PoiMap::GetLocation() const
{
   return m_GlobalX;
}

MemberLocationType PoiMap::GetMemberLocationType() const
{
   ATLASSERT(m_MemberLocationType!=mltNotFound);
   return m_MemberLocationType;
}

void PoiMap::SetSegmentCrossSection(ISegmentCrossSection* leftSegmentCrossSection, ISegmentCrossSection* rightSegmentCrossSection)
{
   m_LeftSegmentCrossSection  = leftSegmentCrossSection;
   m_RightSegmentCrossSection = rightSegmentCrossSection;
}

void PoiMap::GetSegmentCrossSection(ISegmentCrossSection** leftSegmentCrossSection, ISegmentCrossSection** rightSegmentCrossSection)
{
   m_LeftSegmentCrossSection.CopyTo(leftSegmentCrossSection);
   m_RightSegmentCrossSection.CopyTo(rightSegmentCrossSection);
}

void PoiMap::SetStressPoints(IStressPoints* leftStressPoints, IStressPoints* rightStressPoints)
{
   m_LeftStressPoints  = leftStressPoints;
   m_RightStressPoints = rightStressPoints;
}

void PoiMap::GetStressPoints(IStressPoints** leftStressPoints, IStressPoints** rightStressPoints)
{
   m_LeftStressPoints.CopyTo(leftStressPoints);
   m_RightStressPoints.CopyTo(rightStressPoints);
}

bool PoiMap::operator< (const PoiMap& other) const
{
   // use poi id
   return m_LBAMPoiID < other.m_LBAMPoiID; 
}

bool PoiMap::operator==(const PoiMap& other) const
{
   // use poi id
   return m_LBAMPoiID == other.m_LBAMPoiID; 
}

// less operator for sorting by global location - doesn't squeeze out duplicate locations
bool PoiMap::LocLess(PoiMap* left, PoiMap* right) 
{ 
   if (IsEqual(left->m_GlobalX, right->m_GlobalX, 1.0e-8))
   {
      // tie breaker if equal locations - look at underlying fem mapping
      // 
      //                P+   M   P0
      //   --------------o   o   o------------------
      //        mbr                    mbr
      //
      //  P+  is a poi mapped to a fem poi at the end of entering member
      //  M   mapps to member ends
      //  P0  is a poi mapped to the beginning of the exiting member (location==0.0)
      // 
      if (left->m_MemberLocationType != right->m_MemberLocationType)
      {
         return left->m_MemberLocationType < right->m_MemberLocationType;
      }
   }
   else
   {
      return left->m_GlobalX < right->m_GlobalX;
   }

   // fell through location comparisions - use id's as last resort
   return left->m_LBAMPoiID<right->m_LBAMPoiID; 
}

bool PoiMap::LocLessSqueeze(PoiMap* left, PoiMap* right) 
{ 
   if (IsEqual(left->m_GlobalX, right->m_GlobalX, 1.0e-8))
   {
      // tie breaker if equal locations - look at underlying fem mapping
      // 
      //                P+   M   P0
      //   --------------o   o   o------------------
      //        mbr                    mbr
      //
      //  P+  is a poi mapped to a fem poi at the end of entering member
      //  P0  is a poi mapped to the beggining of the exiting member (location==0.0)
      // 
      return left->m_MemberLocationType < right->m_MemberLocationType;  // no fall-through - squeeze out
   }
   else
   {
      return left->m_GlobalX < right->m_GlobalX;
   }
}


// //////////////////////////////////////////////////////////////////
PoiMapToFemPoi::PoiMapToFemPoi(PoiIDType lbamPoiID, Float64 globalX, MemberType mType, MemberIDType memberID, Float64 lbamPoiLocation):
PoiMap(lbamPoiID, globalX, mType, memberID, lbamPoiLocation),
m_FemPoiID(-1)
{
}

void PoiMapToFemPoi::SetFemPoi(PoiIDType id, Float64 femMbrLoc)
{
   m_FemPoiID  = id;
   m_FemMbrLoc = femMbrLoc;
}

PoiIDType PoiMapToFemPoi::GetFemPoiID() const
{
   ATLASSERT(m_FemPoiID!=-1);
   return m_FemPoiID;
}

Float64 PoiMapToFemPoi::GetFemPoiMbrLocation() const
{
   return m_FemMbrLoc;
}

void PoiMapToFemPoi::SetMemberLocationType(MemberLocationType type)
{
   m_MemberLocationType=type;
}

void PoiMapToFemPoi::GetDeflection(LoadGroupIDType loadGroupID, IFem2dModel* pFemMdl, Float64* leftDx, Float64* leftDy, Float64* leftRz, Float64* rightDx, Float64* rightDy, Float64* rightRz)
{
   CComQIPtr<IFem2dModelResults> results(pFemMdl);

   // results map directly to member ends
   PoiIDType fem_poi_id = GetFemPoiID();

   // information is at poi - just get it
   results->ComputePOIDisplacements(loadGroupID, fem_poi_id, lotGlobal, leftDx, leftDy, leftRz);
   *rightDx = *leftDx;
   *rightDy = *leftDy;
   *rightRz = *leftRz;
}

void PoiMapToFemPoi::GetForce(LoadGroupIDType loadGroupID, IFem2dModel* pFemMdl, ResultsOrientation Orientation, Float64* fxLeft, Float64* fyLeft, Float64* mzLeft, Float64* fxRight, Float64* fyRight, Float64* mzRight)
{
   // translate orientation
   Fem2dLoadOrientation fem_or;
   if (Orientation==roGlobal)
	   fem_or = lotGlobal;
   else if (Orientation==roMember)
	   fem_or = lotMember;
   else
      THROW_HR(E_FAIL);

   // forces map directly to fem poi
   CComQIPtr<IFem2dModelResults> results(pFemMdl);

   // get results directly from fem poi
   PoiIDType fem_poi_id = GetFemPoiID();

   HRESULT hr;
   hr = results->ComputePOIForces(loadGroupID, fem_poi_id, mftLeft, fem_or, fxLeft, fyLeft, mzLeft);
   if (FAILED(hr) )
      THROW_HR(hr);

   hr = results->ComputePOIForces(loadGroupID, fem_poi_id, mftRight, fem_or, fxRight, fyRight, mzRight);
   if (FAILED(hr) )
      THROW_HR(hr);
}

void PoiMapToFemPoi::GetInfluenceLines(IFem2dModel* pFemMdl, InfluenceLoadSet& influenceLoadSet,
                               ResultsOrientation forceOrientation,  Float64 forceZeroTolerance, 
                               Float64 deflZeroTolerance, 
                               IInfluenceLine** pLeftAxialInfl,  IInfluenceLine** pRightAxialInfl,
                               IInfluenceLine** pLeftShearInfl,  IInfluenceLine** pRightShearInfl,
                               IInfluenceLine** pLeftMomentInfl, IInfluenceLine** pRightMomentInfl, 
                               IInfluenceLine** pLeftDxInfl,     IInfluenceLine** pRightDxInfl,
                               IInfluenceLine** pLeftDyInfl,     IInfluenceLine** pRightDyInfl, 
                               IInfluenceLine** pLeftRzInfl,     IInfluenceLine** pRightRzInfl)
{
   CHRException hr;

   // reserve some space
   CollectionIndexType num_pts = influenceLoadSet.size();
   if (num_pts==0)
   {
      ATLASSERT(0);
      THROW_LBAMA(NO_INFLUENCE_LOCATIONS);
   }

   // POI mapped pois always only have a left influence line. let's get to creating it
   CComObject<CInfluenceLine>* pLeftInflLines[6];
   CComObject<CInfluenceLine>* pRightInflLines[6];
   for ( int i = 0; i < 6; i++ )
   {
      hr = CComObject<CInfluenceLine>::CreateInstance(&pLeftInflLines[i]);
      pLeftInflLines[i]->Initialize(m_GlobalX,m_LBAMPoiID);
      pLeftInflLines[i]->Reserve(num_pts*12/10);
      pLeftInflLines[i]->SetZeroTolerance(i < 3 ? forceZeroTolerance : deflZeroTolerance);

      hr = CComObject<CInfluenceLine>::CreateInstance(&pRightInflLines[i]);
      pRightInflLines[i]->Initialize(m_GlobalX,m_LBAMPoiID);
      pRightInflLines[i]->Reserve(num_pts*12/10);
      pRightInflLines[i]->SetZeroTolerance(i < 3 ? forceZeroTolerance : deflZeroTolerance);
   }

   InfluenceLoadSetIterator iter( influenceLoadSet.begin() );
   InfluenceLoadSetIterator iterend( influenceLoadSet.end() );
   for (; iter != iterend; iter++)
   {
      const InfluenceLoadLocation& influenceLoadLocation = *iter;

      // get force
      Float64 left[6], right[6];
      GetForce(     influenceLoadLocation.m_FemLoadCaseID, pFemMdl, forceOrientation, &left[FX], &left[FY], &left[MZ], &right[FX], &right[FY], &right[MZ]);
      GetDeflection(influenceLoadLocation.m_FemLoadCaseID, pFemMdl,                   &left[DX], &left[DY], &left[RZ], &right[DX], &right[DY], &right[RZ]);
     
      for ( int i = 0; i < 6; i++ )
      {
         const Float64 tol = 1.0e-09;
         Float64 sign = (i < 3 ? -1 : 1);
         if ( !IsEqual(left[i], sign*right[i], tol ) )
         {
            // there is a jump in the influence line (probably due to a concentrated load)
            pLeftInflLines[i]->Add(iflDualLeft,influenceLoadLocation.m_GlobalX,sign*right[i]);
            pLeftInflLines[i]->Add(iflDualRight,influenceLoadLocation.m_GlobalX,left[i]);

            pRightInflLines[i]->Add(iflDualLeft,influenceLoadLocation.m_GlobalX,right[i]);
            pRightInflLines[i]->Add(iflDualRight,influenceLoadLocation.m_GlobalX,sign*left[i]);
         }
         else
         {
            pLeftInflLines[i]->Add(iflSingle,influenceLoadLocation.m_GlobalX,left[i]);
            pRightInflLines[i]->Add(iflSingle,influenceLoadLocation.m_GlobalX,right[i]);
         }
      } // loop on i
   } // next influence load set

   (*pLeftAxialInfl)  = pLeftInflLines[FX]; (*pLeftAxialInfl)->AddRef();
   (*pLeftShearInfl)  = pLeftInflLines[FY]; (*pLeftShearInfl)->AddRef();
   (*pLeftMomentInfl) = pLeftInflLines[MZ]; (*pLeftMomentInfl)->AddRef();
   (*pLeftDxInfl)     = pLeftInflLines[DX]; (*pLeftDxInfl)->AddRef();
   (*pLeftDyInfl)     = pLeftInflLines[DY]; (*pLeftDyInfl)->AddRef();
   (*pLeftRzInfl)     = pLeftInflLines[RZ]; (*pLeftRzInfl)->AddRef();

   (*pRightAxialInfl)  = pRightInflLines[FX]; (*pRightAxialInfl)->AddRef();
   (*pRightShearInfl)  = pRightInflLines[FY]; (*pRightShearInfl)->AddRef();
   (*pRightMomentInfl) = pRightInflLines[MZ]; (*pRightMomentInfl)->AddRef();
   (*pRightDxInfl)     = pRightInflLines[DX]; (*pRightDxInfl)->AddRef();
   (*pRightDyInfl)     = pRightInflLines[DY]; (*pRightDyInfl)->AddRef();
   (*pRightRzInfl)     = pRightInflLines[RZ]; (*pRightRzInfl)->AddRef();
}


std::_tstring PoiMapToFemPoi::GetDescription() const
{
   std::_tostringstream os;
   os<< _T("PoiMapToFemPoi: POI ID = ")<<m_FemPoiID<<_T(" FemMbrLoc = ")<<m_FemMbrLoc<<PoiMap::GetDescription()<<std::endl;
   return os.str();
}



//////////////////////////////////////////////////////////////////

PoiMapToFemMbr::PoiMapToFemMbr(PoiIDType lbamPoiID, Float64 globalX, MemberType mType, MemberIDType memberID, Float64 lbamPoiLocation):
PoiMap(lbamPoiID, globalX, mType, memberID, lbamPoiLocation),
m_LftMbrID(INVALID_ID),
m_RgtMbrID(INVALID_ID)
{
   m_MemberLocationType = mltStraddle;
}

void PoiMapToFemMbr::SetFemMbrs(MemberIDType leftID, MemberIDType rightID)
{
   m_LftMbrID = leftID;
   m_RgtMbrID = rightID;
}

MemberIDType PoiMapToFemMbr::GetLeftMbrID() const
{
   return m_LftMbrID;
}

MemberIDType PoiMapToFemMbr::GetRightMbrID() const
{
   return m_RgtMbrID;
}

void PoiMapToFemMbr::GetDeflection(LoadGroupIDType loadGroupID, IFem2dModel* pFemMdl, Float64* leftDx, Float64* leftDy, Float64* leftRz, Float64* rightDx, Float64* rightDy, Float64* rightRz)
{
   CComQIPtr<IFem2dModelResults> results(pFemMdl);

   // results map to member ends
   MemberIDType leftMbrID  = GetLeftMbrID();
   MemberIDType rightMbrID = GetRightMbrID();

   *leftDx = 0;
   *leftDy = 0;
   *leftRz = 0;

   *rightDx = 0;
   *rightDy = 0;
   *rightRz = 0;

   // information is at ends of each member
   Float64 dx, dy, rz;
   if ( leftMbrID != INVALID_ID )
      results->ComputeMemberDisplacements(loadGroupID, leftMbrID,   &dx, &dy, &rz, leftDx, leftDy, leftRz);

   if ( rightMbrID != INVALID_ID )
      results->ComputeMemberDisplacements(loadGroupID, rightMbrID,  rightDx, rightDy, rightRz, &dx, &dy, &rz);
}

void PoiMapToFemMbr::GetForce(LoadGroupIDType loadGroupID, IFem2dModel* pFemMdl, ResultsOrientation Orientation, Float64* fxLeft, Float64* fyLeft, Float64* mzLeft, Float64* fxRight, Float64* fyRight, Float64* mzRight)
{
   // orientation is ignored - must not be if this type of poi ever put at supports

   // forces map directly to fem poi
   CComQIPtr<IFem2dModelResults> results(pFemMdl);

   // results map to member ends
   MemberIDType leftMbrID  = GetLeftMbrID();
   MemberIDType rightMbrID = GetRightMbrID(); 

   *fxLeft = 0;
   *fyLeft = 0;
   *mzLeft = 0;

   *fxRight = 0;
   *fyRight = 0;
   *mzRight = 0;

   // information is at ends of each member
   Float64 fx, fy, mz;
   if ( leftMbrID != INVALID_ID )
      results->ComputeMemberForces(loadGroupID, leftMbrID,   &fx, &fy, &mz, fxLeft, fyLeft, mzLeft);

   if ( rightMbrID != INVALID_ID )
      results->ComputeMemberForces(loadGroupID, rightMbrID, fxRight, fyRight, mzRight, &fx, &fy, &mz);
}


void PoiMapToFemMbr::GetInfluenceLines(IFem2dModel* pFemMdl, InfluenceLoadSet& influenceLoadSet,
                               ResultsOrientation forceOrientation,  Float64 forceZeroTolerance, 
                               Float64 deflZeroTolerance, 
                               IInfluenceLine** pLeftAxialInfl,  IInfluenceLine** pRightAxialInfl,
                               IInfluenceLine** pLeftShearInfl,  IInfluenceLine** pRightShearInfl,
                               IInfluenceLine** pLeftMomentInfl, IInfluenceLine** pRightMomentInfl, 
                               IInfluenceLine** pLeftDxInfl,     IInfluenceLine** pRightDxInfl,
                               IInfluenceLine** pLeftDyInfl,     IInfluenceLine** pRightDyInfl, 
                               IInfluenceLine** pLeftRzInfl,     IInfluenceLine** pRightRzInfl)
{
   CHRException hr;

   // Member-mapped poi's always have left and right influence lines for force computations. 
   // This is done for simplicity. There are cases when the right influence line is not needed (i.e., it is equal to the left),
   // such as when the poi is located at a hinge that is not over a support, or for Mz when the top of a support is hinged.
   // However, figuring this out is too much effort for very little optimization.
   // reserve some space
   CollectionIndexType num_pts = influenceLoadSet.size();
   if (num_pts==0)
   {
      ATLASSERT(0);
      THROW_LBAMA(NO_INFLUENCE_LOCATIONS);
   }

   // POI mapped pois always only have a left influence line. let's get to creating it
   CComObject<CInfluenceLine>* pInflLines[2][6]; // 0 = left, 1 = right
   const int leftFace = 0;
   const int rightFace = 1;

   for ( int i = 0; i < 2; i++ )
   {
      for ( int j = 0; j < 6; j++ )
      {
         hr = CComObject<CInfluenceLine>::CreateInstance(&pInflLines[i][j]);
         pInflLines[i][j]->Initialize(m_GlobalX,m_LBAMPoiID);
         pInflLines[i][j]->Reserve(num_pts*12/10);
         pInflLines[i][j]->SetZeroTolerance(j < 3 ? forceZeroTolerance : deflZeroTolerance);
      }
   }

   MemberIDType leftMbrID  = GetLeftMbrID();
   MemberIDType rightMbrID = GetRightMbrID();
   
   ATLASSERT(leftMbrID != INVALID_ID || rightMbrID != INVALID_ID); // one of these must be valid

   VARIANT_BOOL vbIsSupport;

   CComPtr<IFem2dMemberCollection> members;
   pFemMdl->get_Members(&members);

   if ( leftMbrID != INVALID_ID )
   {
      CComPtr<IFem2dMember> leftMbr;
      members->Find(leftMbrID,&leftMbr);

      JointIDType jointID;
      leftMbr->get_EndJoint(&jointID);

      CComPtr<IFem2dJointCollection> joints;
      pFemMdl->get_Joints(&joints);

      CComPtr<IFem2dJoint> joint;
      joints->Find(jointID,&joint);

      joint->IsSupport(&vbIsSupport);
   }
   else
   {
      CComPtr<IFem2dMember> rightMbr;
      members->Find(rightMbrID,&rightMbr);

      JointIDType jointID;
      rightMbr->get_StartJoint(&jointID);

      CComPtr<IFem2dJointCollection> joints;
      pFemMdl->get_Joints(&joints);

      CComPtr<IFem2dJoint> joint;
      joints->Find(jointID,&joint);

      joint->IsSupport(&vbIsSupport);
   }

   InfluenceLoadSetIterator it( influenceLoadSet.begin() );
   InfluenceLoadSetIterator itend( influenceLoadSet.end() );
   for (; it!=itend; it++)
   {
      const InfluenceLoadLocation& ifll = *it;

      Float64 left[6], right[6];
      GetForce(     ifll.m_FemLoadCaseID, pFemMdl, forceOrientation, &left[FX], &left[FY], &left[MZ], &right[FX], &right[FY], &right[MZ]);
      GetDeflection(ifll.m_FemLoadCaseID, pFemMdl,                   &left[DX], &left[DY], &left[RZ], &right[DX], &right[DY], &right[RZ]);

      if ( vbIsSupport == VARIANT_TRUE )
      {
         for ( int i = 0; i < 6; i++ )
         {
            pInflLines[leftFace][i]->Add(iflSingle,ifll.m_GlobalX,left[i]);
            pInflLines[rightFace][i]->Add(iflSingle,ifll.m_GlobalX,right[i]);
         }
      }
      else
      {
         for ( int i = 0; i < 6; i++ )
         {
            const Float64 tol = 1.0e-06;
            if ( !IsEqual(left[i], -right[i], tol ) )
            {
               Float64 sign = (i < 3 ? -1 : 1);
               // there is a jump in the influence line (probably due to a concentrated load)
               pInflLines[leftFace][i]->Add(iflDualLeft,ifll.m_GlobalX,sign*right[i]);
               pInflLines[leftFace][i]->Add(iflDualRight,ifll.m_GlobalX,left[i]);

               pInflLines[rightFace][i]->Add(iflDualLeft,ifll.m_GlobalX,right[i]);
               pInflLines[rightFace][i]->Add(iflDualRight,ifll.m_GlobalX,sign*left[i]);
            }
            else
            {
               pInflLines[leftFace][i]->Add(iflSingle,ifll.m_GlobalX,left[i]);
               pInflLines[rightFace][i]->Add(iflSingle,ifll.m_GlobalX,right[i]);
            }
         }
      }
   }

   (*pLeftAxialInfl)  = pInflLines[leftFace][FX]; (*pLeftAxialInfl)->AddRef();
   (*pLeftShearInfl)  = pInflLines[leftFace][FY]; (*pLeftShearInfl)->AddRef();
   (*pLeftMomentInfl) = pInflLines[leftFace][MZ]; (*pLeftMomentInfl)->AddRef();
   (*pLeftDxInfl)     = pInflLines[leftFace][DX]; (*pLeftDxInfl)->AddRef();
   (*pLeftDyInfl)     = pInflLines[leftFace][DY]; (*pLeftDyInfl)->AddRef();
   (*pLeftRzInfl)     = pInflLines[leftFace][RZ]; (*pLeftRzInfl)->AddRef();

   (*pRightAxialInfl)  = pInflLines[rightFace][FX]; (*pRightAxialInfl)->AddRef();
   (*pRightShearInfl)  = pInflLines[rightFace][FY]; (*pRightShearInfl)->AddRef();
   (*pRightMomentInfl) = pInflLines[rightFace][MZ]; (*pRightMomentInfl)->AddRef();
   (*pRightDxInfl)     = pInflLines[rightFace][DX]; (*pRightDxInfl)->AddRef();
   (*pRightDyInfl)     = pInflLines[rightFace][DY]; (*pRightDyInfl)->AddRef();
   (*pRightRzInfl)     = pInflLines[rightFace][RZ]; (*pRightRzInfl)->AddRef();
}



std::_tstring PoiMapToFemMbr::GetDescription() const
{
   std::_tostringstream os;
   os<< _T("PoiMapToFemMbr: Left Mbr ID = ")<<m_LftMbrID<<_T(" Right Mbr ID = ")<<m_RgtMbrID<<PoiMap::GetDescription()<<std::endl;
   return os.str();
}


////////////////////////////////////////////////////////////////////////////////////////
// utility class to help deal with messy logic required to generate minimum poi spacing
////////////////////////////////////////////////////////////////////////////////////////
SortedPoiMapTracker::SortedPoiMapTracker(PoiMapCollection& PoiMaps, bool squeezeDuplicates)
{
   // fill us up with pois from analysis model
   this->reserve(PoiMaps.size());

   PoiMapIterator it( PoiMaps.begin() );
   PoiMapIterator itend( PoiMaps.end() );
   for (; it!=itend; it++)
   {
      MemberType mt = (*it)->GetLBAMMemberType();
      if (mt==mtSpan || mt==mtSuperstructureMember)
         this->push_back(*it); // NOTE: we don't own our members - the map does.
   }

   if (squeezeDuplicates)
      std::sort(this->begin(), this->end(), PoiMap::LocLessSqueeze);
   else
      std::sort(this->begin(), this->end(), PoiMap::LocLess);

   // our current cursor
   m_Cursor = this->begin();
}

// reset to beginning of collection
void SortedPoiMapTracker::Reset()
{
   m_Cursor = this->begin();
}

// test if a poi is at an exact location along a span or ssm
bool SortedPoiMapTracker::IsPoiAtLocation(MemberType mbrType, MemberIDType mbrID, Float64 globalX, PoiIDType* poiIDAtLoc)
{
   if (mbrType!=mtSpan && mbrType!=mtSuperstructureMember)
   {
      ATLASSERT(0); // not built to deal with substructure
      return false;
   }

   while(true)
   {
      iterator it_end( end() );

      if ( m_Cursor==it_end )
         return false;

      PoiMap& curinf = *(*m_Cursor);
      if ( IsNearby(curinf.GetLocation(), globalX) )
      {
         // we are at right global location - now check if member is right - need to hold cursor here
         iterator loc_cur( m_Cursor );
         while(true)
         {
            if ( loc_cur==it_end )
               return false;

            PoiMap& loc_inf = *(*loc_cur);
            if (IsNearby(loc_inf.GetLocation(), globalX) )
            {
               if (loc_inf.GetLBAMMemberType()==mbrType && loc_inf.GetLBAMMemberID()==mbrID )
               {
                  if (poiIDAtLoc != NULL)
                     *poiIDAtLoc = loc_inf.GetLBAMPoiID();

                  return true;
               }
               else
                  loc_cur++;
            }
            else
               return false;
         }
      }
      else if ( curinf.GetLocation() > globalX )
      {
         // cursor is already past location - we're not going to find it
         return false;
      }
      else
      {
         // cursor is before location - increment
         m_Cursor++;
      }
   }
}

// test if a poi is at or between the next location and the most-recently found location
bool SortedPoiMapTracker::IsPoiAtNextLocation(Float64 nextX, Float64* foundX)
{
   if ( m_Cursor==end() )
      return false;

   PoiMap& curinf = *(*m_Cursor);
   Float64 curloc = curinf.GetLocation();

   if (nextX < curloc)
   {
      // current poi is beyond our location
      return false;
   }
   else
   {
      // increment cursor until we move to the next location
      Float64 next_loc;
      do 
      {
         m_Cursor++;
         if (m_Cursor==end())
            return false;

         PoiMap& nextinf = *(*m_Cursor);
         next_loc = nextinf.GetLocation();

      } while ( IsEqual(next_loc, curloc) );

      if (next_loc <= nextX)
      {
         // we have a poi that's within the minimum spacing
         *foundX = next_loc;
         return true;
      }
      else
         return false;
   }
}

SortedPoiMapTracker::PoiCoveredRes SortedPoiMapTracker::IsPoiCovered(Float64 globalX, IFem2dPOICollection* pFemPois, Float64 tolerance,IDType* pCoveringID)
{
   // loop until we get to (or pass) the location
   *pCoveringID = INVALID_ID;
   while(true)
   {
      if ( m_Cursor==end() )
         return Both;

      PoiMap& curinf = *(*m_Cursor);
      if ( IsNearby(curinf.GetLocation(), globalX, tolerance) )
      {
         // we are at right global location - now check if poi covers location
         int intres = Both;

         while(true)
         {
            if ( m_Cursor==end())
               return (PoiCoveredRes)intres;

            PoiMap& loc_inf = *(*m_Cursor);
            if (IsNearby(loc_inf.GetLocation(), globalX, tolerance) )
            {
               // see which sides of this location are covered
               MemberLocationType loctype = loc_inf.GetMemberLocationType();
               if (loctype==mltStraddle || loctype==mltInternal)
               {
                  intres = None;
               }
               else if (loctype==mltLeftEnd)
               {
                     intres |= Left;
               }
               else if (loctype==mltRightEnd)
               {
                     intres |= Right;
               }
               else
               {
                  ATLASSERT(0); // unknown ?
               }
            }
            else
            {
               if ( intres == None )
               {
                  *pCoveringID = curinf.GetLBAMPoiID();
               }
               return (PoiCoveredRes)intres;;
            }

            m_Cursor++;
         }
      }
      else if ( globalX < curinf.GetLocation() )
      {
         // cursor is already past location - we're not going to find it
         return Both;
      }
      else
      {
         // cursor is before location - increment until we get there
         m_Cursor++;
      }
   }
}
