///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
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

// AnalysisModel.cpp: implementation of the CAnalysisModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AnalysisModel.h"
#include "resource.h"
#include "WBFLLBAMAnalysis.h"
#include "LBAMAnalysis.hh"
#include "LBAM.hh"
#include "Fem2dErrors.h"

#include <MathEx.h>
#include <algorithm>
#include "Interpolate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// some handy types and constants
////////////////////////////////////////////
static const Float64 LAYOUT_TOLERANCE = 1/10000.0;

////////////////////////////////////////////
//////// Hard-Coded Load Case ID's /////////
////////////////////////////////////////////
// Starting influence fem load case id. There is one load case for each influence load location and
// new load cases are incremented by -1
static const LoadCaseIDType INFLUENCE_LC     = -1000;

// Fem load case id for contraflexure anlaysis
static const LoadCaseIDType CONTRAFLEXURE_LC = -2;  

// local helper functions
/////////////////////////
static void InsertSuperSegmentNode(SuperNodeLocs* node_locs, Float64 loc, ISegmentCrossSection* pcs, SuperNodeReason reason);
static void CondenseSuperNodeSections(SuperNodeLocs*  super_node_locs, Float64 layoutTolerance);
static void AssignSectionsToNodes(SuperNodeLocs* node_locs);

static void InsertSubSegmentNode(SubNodeLocs* node_locs, Float64 xloc, Float64 yloc, ISegmentCrossSection* pcs, SubNodeReason reason);
static void CondenseSupportNodeSections(SubNodeLocs* node_locs, Float64 layoutTolerance);
static void LayoutSupportSegments(BSTR stage, IFilteredSegmentCollection* pFilteredSegs, const XyLoc& bottom, const XyLoc& top, Float64 supportLength, Float64 lTolerance, SubNodeLocs* pNodeLocs);
static void SetNodeNumbering(SuperNodeLocs* pNodeLocs);
static void SetNodeNumberForSupport(SubNodeLocs* psnls, JointIDType* pcurrNode);

enum XSRes {xsAefNeg, xsAifNeg, xsAedNeg, xsAidNeg, xsDepthNeg, xsThermalNeg};
static void CheckSegmentCrossSection(ISegmentCrossSection* pCs);
static CComBSTR CreateXsErrorMsg(LPCTSTR proptype);
void GetMemberEnd(MemberIDType mbrID, IFem2dMemberCollection* Members, IFem2dJointCollection* Joints, Fem2dMbrEndType end, JointIDType* jointID, Float64* xLoc, Float64* yLoc);

inline Float64 InterpolateDlTrapezoid(Float64 x, Float64 xStart, Float64 xEnd, Float64 yStart, Float64 yEnd)
{
   ATLASSERT(xEnd>xStart);
   ATLASSERT(x>=xStart);
   ATLASSERT(x<=xEnd);

   Float64 slope = (yEnd-yStart)/(xEnd-xStart);
   return yStart + slope*(x-xStart);
}

inline void delete_pointer(PoiMap* pinfo)
{
   delete pinfo;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAnalysisModel::CAnalysisModel(ILBAMModel* pModel, BSTR stage, IStageOrder* pStageOrder, ILoadGroupOrder* pLoadGroupOrder, 
                               PoiIDType minSpanPoiIncr, PoiIDType minCantileverPoiIncr, bool forForce):
m_pLBAMModel(pModel),
m_Stage(stage),
m_pStageOrder(pStageOrder),
m_pLoadGroupOrder(pLoadGroupOrder),
m_bForcesModel(forForce),
m_IsPoiMapUpdated(false),
m_LastFemPoiID(0),
m_LastInternalPoiID(0),
m_MinSpanPoiIncrement(minSpanPoiIncr),
m_MinCantileverPoiIncrement(minCantileverPoiIncr)
{
   ATLASSERT(pModel!=NULL);
   ATLASSERT(pStageOrder!=NULL);
   ATLASSERT(pLoadGroupOrder!=NULL);

   CHRException hr;
   hr = m_ContraflexureLocations.CoCreateInstance(CLSID_DblArray);
}

CAnalysisModel::~CAnalysisModel()
{
   std::for_each(m_PoiMap.begin(),m_PoiMap.end(),delete_pointer);
}

void CAnalysisModel::BuildModel()
{
   CHRException hr;

   // make sure we're starting with an empty fem model
   ATLASSERT(m_pFem2d==NULL);

   // get length of superstructure
   CComPtr<ISuperstructureMembers> pmembers;
   hr = m_pLBAMModel->get_SuperstructureMembers(&pmembers);

   Float64 super_length;
   hr = pmembers->get_Length(&super_length);

   CollectionIndexType super_cnt;
   hr = pmembers->get_Count(&super_cnt);

   Float64 left_overhang;
   hr = pmembers->get_Offset(&left_overhang);

   CComPtr<ISpans> pspans;
   hr = m_pLBAMModel->get_Spans(&pspans);

   Float64 spans_length;
   hr = pspans->get_Length(&spans_length);

   SpanIndexType spans_cnt;
   hr = pspans->get_Count(&spans_cnt);

   // some basic checking
   if (spans_cnt <= 0.0)
      THROW_LBAMA(MUST_HAVE_ONE_SPAN);

   if (super_cnt <= 0.0)
      THROW_LBAMA(MUST_HAVE_ONE_SSM);

   if (spans_length <= 0.0)
   {
      THROW_LBAMA(SPAN_LENGTH_MUST_BE_GT_ZERO);
   }

   Float64 right_overhang = super_length-left_overhang-spans_length;
   right_overhang = IsZero(right_overhang) ? 0.0 : right_overhang; // RAB: eliminate noise
   if (right_overhang<0.0)
      THROW_LBAMA(SPAN_LENGTH_EXCEEDS_SUPERSTRUCTUREMEMBERS);

   // set layout tolerance - this value affects placement of cross sections
   m_TotalLength   = super_length;
   m_LeftOverhang  = left_overhang;
   m_RightOverhang = right_overhang;
   m_LayoutTolerance = super_length * LAYOUT_TOLERANCE;

   // tolerance of internally-generated pois
   m_PoiTolerance = m_LayoutTolerance/1.0e3;

   // get supports
   CComPtr<ISupports> psupports;
   hr = m_pLBAMModel->get_Supports(&psupports);

   SupportIndexType supports_cnt;
   hr = psupports->get_Count(&supports_cnt);

   if (supports_cnt != spans_cnt+1)
   {
      CComBSTR msg = ::CreateErrorMsg2L(IDS_E_INVALID_SUPPORTS, spans_cnt,spans_cnt+1);
      THROW_LBAMA_MSG(INVALID_SUPPORTS,msg);
   }

   // lay out superstructure and supports
   SuperNodeLocs super_node_locs;
   LayoutSuperstructure(pmembers, pspans, psupports, &super_node_locs);

   // optimize node numbering and then generate the fem model
   SetNodeNumbering(&super_node_locs);
   GenerateFemModel(&super_node_locs);

   // generate loads for all load groups
   GenerateLoads();

   // generate POI's
   GeneratePOIs();
}

void CAnalysisModel::GetDeflection(LoadGroupIDType lgId, PoiIDType poiId, Float64* leftDx, Float64* leftDy, Float64* leftRz, Float64* rightDx, Float64* rightDy, Float64* rightRz)
{
   ATLASSERT(m_pFem2d!=NULL);

   try
   {
      // Location of results depends on poi type
      PoiMapIterator it(m_PoiMap.find( &PoiMap(poiId) ));
      if (it != m_PoiMap.end() )
      {
         PoiMap& rinfo = *(*it);
         rinfo.GetDeflection(lgId, m_pFem2d, leftDx, leftDy, leftRz, rightDx, rightDy, rightRz);
      }
      else
      {
         CComBSTR msg = ::CreateErrorMsg1L(IDS_E_POI_NOT_FOUND, poiId);
         THROW_LBAMA_MSG(POI_NOT_FOUND,msg);
      }
   }
   catch (...)
   {
      DealWithFem2dExceptions();
   }
}

void CAnalysisModel::GetForce(LoadGroupIDType lgId, PoiIDType poiId, ResultsOrientation Orientation, Float64* fxLeft, Float64* fyLeft, Float64* mzLeft, Float64* fxRight, Float64* fyRight, Float64* mzRight)
{
   ATLASSERT(m_pFem2d!=NULL);

   try
   {
      // get poi information and call local function
      PoiMapIterator it(m_PoiMap.find( &PoiMap(poiId) ));
      if (it != m_PoiMap.end() )
      {
         PoiMap& rinfo = *(*it);
         rinfo.GetForce(lgId, m_pFem2d, Orientation, fxLeft, fyLeft, mzLeft, fxRight, fyRight, mzRight);
      }
      else
      {
         CComBSTR msg = ::CreateErrorMsg1L(IDS_E_POI_NOT_FOUND, poiId);
         THROW_LBAMA_MSG(POI_NOT_FOUND,msg);
      }
   }
   catch (...)
   {
      DealWithFem2dExceptions();
   }
}


void CAnalysisModel::GetStress(LoadGroupIDType lg_id, PoiIDType poiId, std::vector<Float64>& sLeft, std::vector<Float64>& sRight, bool* wasComputed)
{
   CHRException hr;

   // assume the worst
   sLeft.clear();
   sRight.clear();
   *wasComputed = false;

   PoiMapIterator it(m_PoiMap.find( &PoiMap(poiId) ));
   if (it != m_PoiMap.end() )
   {
      PoiMap& info = *(*it);

      // get force results
      Float64 fx_left, fx_right, fy_left, fy_right, mz_left, mz_right;
      info.GetForce(lg_id, m_pFem2d, roMember, &fx_left, &fy_left, &mz_left, &fx_right, &fy_right, &mz_right);

      // get stress factors for poi from cached data
      CComPtr<IStressPoints> left_sps, right_sps;
      info.GetStressPoints(&left_sps, &right_sps);
      if (left_sps != NULL)
      {
         CollectionIndexType num_sps;
         hr = left_sps->get_Count(&num_sps);
         sLeft.reserve(num_sps);

         for (CollectionIndexType isp=0; isp<num_sps; isp++)
         {
            CComPtr<IStressPoint> left_stress_point;
            hr = left_sps->get_Item(isp, &left_stress_point);

            // now we can compute stress
            Float64 sa, sm;
            hr = left_stress_point->get_Sa(&sa);
            hr = left_stress_point->get_Sm(&sm);

            Float64 s_left =  fx_left*sa  + mz_left*sm;

            sLeft.push_back(s_left);
         }

         // get right stress point if it is available, otherwise use value from left
         if (right_sps == NULL)
            right_sps = left_sps;

         hr = right_sps->get_Count(&num_sps);

         sRight.reserve(num_sps);

         for (CollectionIndexType isp=0; isp<num_sps; isp++)
         {
            CComPtr<IStressPoint> right_stress_point;
            hr = right_sps->get_Item(isp, &right_stress_point);

            // now we can compute stress
            Float64 sa, sm;
            hr = right_stress_point->get_Sa(&sa);
            hr = right_stress_point->get_Sm(&sm);

            Float64 s_right = -fx_right*sa - mz_right*sm;

            sRight.push_back(s_right);
         }

            *wasComputed = true;
      }
   }
   else
   {
      // this should never happen since GetForce should already have told us if the poi exists
      ATLASSERT(0);
      CComBSTR msg = ::CreateErrorMsg1L(IDS_E_POI_NOT_FOUND, poiId);
      THROW_LBAMA_MSG(POI_NOT_FOUND,msg);
   }
}

void CAnalysisModel::GetReaction(LoadGroupIDType loadGroupID, SupportIDType supportID, Float64* pFx, Float64* pFy, Float64* pMz)
{
   try
   {
      // first need to find support joint
      JointIDType jointID;
      if (0 <= supportID && supportID < SupportIDType(m_SupportNodes.size()) )
      {
         // permanant support is requested
         jointID = m_SupportNodes[supportID];
      }
      else
      {
         // see if a temporary support is requested
         IdMapIterator itm(m_TemporarySupportNodes.find(supportID));
         if (itm != m_TemporarySupportNodes.end())
         {
            jointID = itm->second;
         }
         else
         {
            // No joint found for sptId
            CComBSTR msg=CreateErrorMsg1L(IDS_E_SUPPORT_NOT_EXIST, supportID);
            THROW_LBAMA_MSG(SUPPORT_NOT_EXIST,msg);
         }
      }

      // if here, we found our joint
      CComQIPtr<IFem2dModelResults> results(m_pFem2d);

      try 
      {
         results->ComputeReactions(loadGroupID, jointID, pFx, pFy, pMz);
      }
      catch (...)
      {
         DealWithFem2dExceptions();
      }
   }
   catch (CComException& re)
   {
      _bstr_t msg=CreateErrorMsg1S(IDS_STAGE_CONTEXT, m_Stage);
      re.AppendToMessage((TCHAR*)msg);
      throw re;
   }
}

void CAnalysisModel::GetSupportDeflection(LoadGroupIDType loadGroupID, SupportIDType supportID, Float64* pDx, Float64* pDy, Float64* pRz)
{
   try
   {
      // first need to find support joint
      JointIDType jointID;
      if (0 <= supportID && supportID < SupportIDType(m_SupportNodes.size()) )
      {
         // permanent support is requested
         jointID = m_SupportNodes[supportID];
      }
      else
      {
         // see if a temporary support is requested
         IdMapIterator itm(m_TemporarySupportNodes.find(supportID));
         if (itm != m_TemporarySupportNodes.end())
         {
            jointID = itm->second;
         }
         else
         {
            // No joint found for sptId
            CComBSTR msg=CreateErrorMsg1L(IDS_E_SUPPORT_NOT_EXIST, supportID);
            THROW_LBAMA_MSG(SUPPORT_NOT_EXIST,msg);
         }
      }

      // if here, we found our joint
      CComQIPtr<IFem2dModelResults> results(m_pFem2d);

      try
      {
         results->ComputeJointDisplacements(loadGroupID, jointID, pDx, pDy, pRz);
      }
      catch (...)
      {
         DealWithFem2dExceptions();
      }
   }
   catch (CComException& re)
   {
      _bstr_t msg=CreateErrorMsg1S(IDS_STAGE_CONTEXT, m_Stage);
      re.AppendToMessage((TCHAR*)msg);
      throw re;
   }
}

void CAnalysisModel::GetTemporarySupportReaction(LoadGroupIDType loadGroupID, SupportIDType tempSupportID, Float64* pFx, Float64* pFy, Float64* pMz)
{
   // temporary support is either zero-length or has elements (fixed length).
   // Look for fixed length first
   ElementLayoutMapIterator it(m_TemporarySupportElements.find(tempSupportID));
   ATLASSERT(it != m_TemporarySupportElements.end());
   ElementLayoutVec& rvec = it->second;
   if (!rvec.empty())
   {
      // fixed length support - reaction force is at end of last element
      MemberIDType mbrID = rvec.back().m_FemMemberID;

      CComQIPtr<IFem2dModelResultsEx> results( m_pFem2d );

      Float64 fxs, fys, mzs, fxe, fye, mze;
      // fem global member force - assumes that superstructure is horizontal
      results->ComputeMemberForcesEx(loadGroupID, mbrID, lotGlobal, &fxs, &fys, &mzs, &fxe, &fye, &mze);
      // reaction is equal and opposite member end force
      *pFx = -fxe;
      *pFy = -fye;
      *pMz = -mze;
   }
   else
   {
      // zero-length support
      // see if ts has a support node
      IdMapIterator itm(m_TemporarySupportNodes.find(tempSupportID));
      if (itm != m_TemporarySupportNodes.end())
      {
         CComQIPtr<IFem2dModelResults> results(m_pFem2d);

         // we have a zero-length temporary support
         JointIDType jointID = itm->second;

         try
         {
            results->ComputeReactions(loadGroupID, jointID, pFx, pFy, pMz);
         }
         catch (...)
         {
            DealWithFem2dExceptions();
         }
      }
      else
      {
         THROW_HR(E_FAIL); // should never happen
      }
   }
}

void CAnalysisModel::ApplyTemporarySupportReaction(LoadCaseIDType tempSupportLoadCaseID, SupportIDType tempSupportID, Float64 fx, Float64 fy, Float64 mz)
{
   IdMapIterator iter(m_TemporarySupportNodeLocs.find(tempSupportID));
   if (iter != m_TemporarySupportNodeLocs.end())
   {
      JointIDType jointID = iter->second;

      // need to find the loading for this load case
      CComPtr<IFem2dLoadingCollection> fem_loadings;
      m_pFem2d->get_Loadings(&fem_loadings);
      
      CComPtr<IFem2dLoading> fem_loading;
      fem_loadings->Find(tempSupportLoadCaseID,&fem_loading);

      CComPtr<IFem2dJointLoadCollection> fem_joint_loads;
      fem_loading->get_JointLoads(&fem_joint_loads);

      CollectionIndexType nLoads;
      fem_joint_loads->get_Count(&nLoads);

      LoadIDType jointLoadID = -(LoadIDType(nLoads) + LoadIDType(tempSupportLoadCaseID));
      CComPtr<IFem2dJointLoad> jointLoad;
      fem_joint_loads->Create(jointLoadID, jointID, fx, fy, mz, &jointLoad);
   }
   else
   {
      THROW_HR(E_FAIL); // node not found - should never happen
   }
}

void CAnalysisModel::GetFemLocForLBAMLoc(MemberType lbamMbrType, MemberIDType lbamMbrId, Float64 lbamLoc, MemberLocationType* locType, 
                                         MemberIDType* pfemId, Float64* pfemLoc)
{
   ATLASSERT(m_pLBAMModel!=NULL);
   ATLASSERT(m_pFem2d!=NULL);

   try
   {
      switch (lbamMbrType)
      {
      // we have some members - are they horizontal or vertically oriented?
      case mtSpan:
         {
            // only use left values for this function
            GetFemMemberLocationAlongSpan(lbamMbrId, lbamLoc, locType, pfemId, pfemLoc);
         }
         break;
      case mtSuperstructureMember:
         {
            GetFemMemberLocationAlongSSM(lbamMbrId, lbamLoc, locType, pfemId, pfemLoc);
         }
         break;
      case mtSupport:
      case mtTemporarySupport:
         {
            GetFemLocAtSupport(lbamMbrType, lbamMbrId, lbamLoc, locType, pfemId, pfemLoc);
         }
         break;
      default:
         THROW_HR(E_FAIL);
      }
   }
   catch (CComException& re)
   {
      CComBSTR msg = CreateLBAMContextMsg(lbamMbrType, lbamMbrId);
      re.AppendToMessage((BSTR)msg);
      throw re;
   }
}

void CAnalysisModel::GetFemLocAtSupport(MemberType supportType, MemberIDType lbamMbrId, Float64 lbamLoc, MemberLocationType* locType, MemberIDType* pfemId, Float64* pfemLoc)
{
   ATLASSERT(supportType==mtSupport || supportType==mtTemporarySupport);

   // see if there are any elements associated with this location
   const ElementLayoutVec* pfem_mbr_list = 0;
   GetFemMembersForLBAMMember(supportType, lbamMbrId, &pfem_mbr_list );

   ATLASSERT(pfem_mbr_list !=0 );
   if (!pfem_mbr_list->empty())
   {
      GetFemMemberLocationAlongSupport(pfem_mbr_list, lbamLoc, locType, pfemId, pfemLoc);
   }
   else
   {
      // no fem members associated with location - we have to be looking at a zero-length support
      // we're supposed to be returning members here
      *locType = mltNotFound;
   }
}


void CAnalysisModel::GetFemMembersForLBAMMember(MemberType mbrType, MemberIDType mbrId, const ElementLayoutVec* *pFemMbrList )
{
   // finds a list of fem members based on a member in the LBAM
   // RETURNS A POINTER TO THE INTERNAL LIST - don't free or change!
   ATLASSERT(m_pLBAMModel!=NULL);
   ATLASSERT(m_pFem2d!=NULL);
   ATLASSERT(*pFemMbrList==0);

   // switch on member type
   switch (mbrType)
   {
   case mtSpan:
      {
         SpanIndexType num_spans = m_SpanEnds.size();
         if (mbrId < 0 || num_spans <= SpanIndexType(mbrId) )
         {
            CComBSTR msg =CreateErrorMsg1L(IDS_E_SPAN_NOT_EXIST, mbrId);
            THROW_LBAMA_MSG(SPAN_NOT_EXIST,msg);
         }

         ElementLayoutVec& rlist = m_SpanElements[mbrId];
         *pFemMbrList = &rlist;
      }
      break;
   case mtSuperstructureMember:
      {
         CollectionIndexType num_ssms = m_SuperstructureMemberEnds.size();
         if (mbrId < 0 || num_ssms <= CollectionIndexType(mbrId) )
         {
            CComBSTR msg =CreateErrorMsg1L(IDS_E_SSM_NOT_EXIST, mbrId);
            THROW_LBAMA_MSG(SSM_NOT_EXIST,msg);
         }

         ElementLayoutVec& rlist = m_SuperstructureMemberElements[mbrId];
         *pFemMbrList = &rlist;
      }
      break;
   case mtSupport:
      {
         // make sure poi is on a valid support
         SupportIDType num_supports = m_SupportElements.size();
         if (mbrId<0 || num_supports <= mbrId)
         {
            CComBSTR msg =CreateErrorMsg1L(IDS_E_SUPPORT_NOT_EXIST, mbrId);
            THROW_LBAMA_MSG(SUPPORT_NOT_EXIST,msg);
         }

         // get members for this support
         ElementLayoutVec& rlist = m_SupportElements[mbrId];
         *pFemMbrList = &rlist;
      }
      break;
   case mtTemporarySupport:
      {
         ElementLayoutMapIterator tst(m_TemporarySupportElements.find(mbrId));
         if (tst == m_TemporarySupportElements.end())
         {
            CComBSTR msg =CreateErrorMsg1L(IDS_E_TEMPSUPPORT_NOT_EXIST,mbrId);
            // don't use THROW_LBAMA_MSG macro because this is not always an error. (the macro contains an ATLASSERT).
            throw CComException(_T(__FILE__),__LINE__, msg, LBAMA_E_TEMPSUPPORT_NOT_EXIST, IDH_E_TEMPSUPPORT_NOT_EXIST);
         }
         else
         {
            ElementLayoutVec& rlist = tst->second;
            *pFemMbrList = &rlist;
         }
      }
      break;
   default:
      THROW_HR(E_FAIL);
   }
}


void CAnalysisModel::GetFemMemberLocationAlongSSM( CollectionIndexType ssmIdx, Float64 lbamLoc, MemberLocationType* locType, MemberIDType* pfemMbrId, Float64* pfemLoc)
{
   try
   {
      if ( !m_SuperstructureMemberElements.empty() )
      {
         CollectionIndexType nSSMbrs = m_SuperstructureMemberEnds.size();
         if (ssmIdx < 0 || nSSMbrs <= ssmIdx)
         {
            THROW_HR(E_FAIL); // should already have been blocked
         }

         // get locations of ends of ssm
         Float64 left_end   = ssmIdx==0? -m_LeftOverhang: m_SuperstructureMemberEnds[ssmIdx-1];
         Float64 right_end  = m_SuperstructureMemberEnds[ssmIdx];
         Float64 ssm_length = right_end - left_end;

         Float64 ssm_loc;
         // get location wrt start of lbam (location==0.0)
         try
         {
            ssm_loc = GetFracDistance(lbamLoc, ssm_length);
         }
         catch(FracRes&)
         {
            CComBSTR msg =CreateErrorMsg1D(IDS_E_LOCATION_OOR,lbamLoc);
            THROW_LBAMA_MSG(LOCATION_OOR,msg);
         }

         ssm_loc += left_end;

         ATLASSERT(ssm_loc>=left_end && ssm_loc<=right_end);

         // next can find element that this location lies along
         ElementLayoutVec& member_list = m_SuperstructureMemberElements[ssmIdx];
         ATLASSERT(!member_list.empty());

         GetFemMemberLocationAlongMemberList( ssm_loc, left_end, right_end, member_list, 
                                              locType, pfemMbrId, pfemLoc);
      }
      else
      {
         // no fem members for ssm
         ATLASSERT(0);
      }
   }
   catch(...)
   {
      ATLASSERT(0);
      throw;
   }
}

void CAnalysisModel::GetFemMemberLocationAlongMemberList( Float64 globalLoc, Float64 leftEnd, Float64 rightEnd, 
                                                         ElementLayoutVec& memberList,
                                                         MemberLocationType* plocType, MemberIDType* pfemMbrId, Float64* pfemLoc)
{
   *plocType=mltNotFound;
   *pfemMbrId=-1;
   *pfemLoc=0;

   // We need to check if this location is at the junction of two members.
   // In order to check this, we need a tolerance
   Float64 total_length = rightEnd-leftEnd;
   ATLASSERT(total_length>0.0);
   Float64 LOC_TOL= total_length*1.0e-07; // expected tolerance due to round-off errors for a Float64

   CComPtr<IFem2dMemberCollection> members;
   m_pFem2d->get_Members(&members);

   CComPtr<IFem2dJointCollection> joints;
   m_pFem2d->get_Joints(&joints);

   // check end conditions first
   if ( IsEqual(globalLoc,leftEnd, LOC_TOL) )
   {
      // location is at start of elements
      MemberIDType mbr_id = memberList.front().m_FemMemberID;
      *plocType = mltLeftEnd;
      *pfemMbrId = mbr_id;
      *pfemLoc = 0.0;
   }
   else if ( IsEqual(globalLoc,rightEnd, LOC_TOL) )
   {
      // location is at right end
      MemberIDType mbr_id = memberList.back().m_FemMemberID;
      *plocType    = mltRightEnd;
      *pfemMbrId  = mbr_id;
      *pfemLoc = -1.0;
   }
   else
   {
      // location is out in the member list somewhere - need to loop to find it
      Float64 start_loc, end_loc, yloc;
      JointIDType start_joint_id, end_joint_id;
      bool first = true;
      bool found = false;
      MemberIDType last_mbr_id = memberList.back().m_FemMemberID;
      ElementLayoutVecIterator idi(memberList.begin());
      ElementLayoutVecIterator idend(memberList.end());
      for(; idi!=idend; idi++)
      {
         MemberIDType mbr_id = idi->m_FemMemberID;

         if (first)
         {
            GetMemberEnd(mbr_id, members, joints, metStart, &start_joint_id, &start_loc, &yloc);
            first = false;
         }

         GetMemberEnd(mbr_id, members, joints, metEnd, &end_joint_id, &end_loc, &yloc);

         if (end_loc >=globalLoc-LOC_TOL)
         {
            if (end_loc <= globalLoc+LOC_TOL)
            {
               // location is within tolerance of junction of two members
              // report location as straddling two members
               *plocType = mltStraddle;
               *pfemMbrId   = mbr_id;
               *pfemLoc  = end_loc-start_loc;

               found = true;
               break;
            }
            else if (end_loc>=globalLoc)
            {
               // location is simply within this member - fill in left member only
               *plocType = mltInternal;
               *pfemMbrId   = mbr_id;
               *pfemLoc  = globalLoc - start_loc;

               found = true;
               break;
            }
            else
            {
               ;// location is just a skoosh past this element - loop should catch next try
            }
         }

         start_loc = end_loc;
         start_joint_id = end_joint_id;
      }

      ATLASSERT(found); // not found in loop - should be impossible
   }
}

Float64 CAnalysisModel::GetLBAMMemberLength(MemberType mbrType, MemberIDType mbrId)
{
   CHRException hr;
   Float64 length = 0.0;

   switch (mbrType)
   {
   case mtSpan:
      {
         SpanIndexType nSpans = m_SpanEnds.size();
         if (mbrId < 0 || nSpans <= SpanIndexType(mbrId) )
         {
            CComBSTR msg =CreateErrorMsg1L(IDS_E_SPAN_NOT_EXIST, mbrId);
            THROW_LBAMA_MSG(SPAN_NOT_EXIST,msg);
         }

         // get locations of ends of span
         Float64 left_end   = mbrId==0? 0.0: m_SpanEnds[mbrId-1];
         Float64 right_end  = m_SpanEnds[mbrId];
         length = right_end - left_end;
      }
      break;

   case mtSuperstructureMember:
      {
         SpanIndexType nSpans = m_SuperstructureMemberEnds.size();
         if (mbrId < 0 || nSpans <= SpanIndexType(mbrId) )
         {
            CComBSTR msg =CreateErrorMsg1L(IDS_E_SSM_NOT_EXIST, mbrId);
            THROW_LBAMA_MSG(SSM_NOT_EXIST,msg);
         }

         // get locations of ends of ssm
         Float64 left_end   = mbrId==0? -m_LeftOverhang : m_SuperstructureMemberEnds[mbrId-1];
         Float64 right_end  = m_SuperstructureMemberEnds[mbrId];
         length = right_end - left_end;
      }
      break;
   case mtSupport:
      {
         CComPtr<ISupports> supports;
         hr = m_pLBAMModel->get_Supports(&supports);

         CComPtr<ISupport> support;
         HRESULT hrr = supports->get_Item(mbrId, &support);
         if (FAILED(hr))
         {
            CComBSTR msg =CreateErrorMsg1L(IDS_E_SUPPORT_NOT_EXIST, mbrId);
            THROW_LBAMA_MSG(SUPPORT_NOT_EXIST,msg);
         }

         hr = support->get_Length(&length);
      }
      break;
   case mtTemporarySupport:
      {
         CComPtr<ITemporarySupport> temp_support;
         SpanIndexType span_no;
         FindTemporarySupport(m_pLBAMModel, mbrId, &temp_support, &span_no);

         if (!temp_support)
         {
            // the support was not found - huck
            CComBSTR msg =CreateErrorMsg1L(IDS_E_TEMPSUPPORT_NOT_EXIST, mbrId);
            THROW_LBAMA_MSG(TEMPSUPPORT_NOT_EXIST,msg);
         }

         hr = temp_support->get_Length(&length);
      }
      break;
   default:
      THROW_LBAMA(INVALID_MEMBER_TYPE);
   }

   return length;
}

void CAnalysisModel::GetFemMemberLocationAlongSpan( SpanIndexType spanIdx, Float64 lbamLoc, MemberLocationType* locType, MemberIDType* pfemId, Float64* pfemLoc)
{
   try
   {
      if ( !m_SpanElements.empty() )
      {
         SpanIndexType nSpans = m_SpanEnds.size();
         if (spanIdx < 0 || nSpans <= spanIdx)
         {
            THROW_HR(E_FAIL); // should already have been blocked
         }

         // get locations of ends of span
         Float64 left_end   = spanIdx==0? 0.0: m_SpanEnds[spanIdx-1];
         Float64 right_end  = m_SpanEnds[spanIdx];
         Float64 span_length = right_end - left_end;

         Float64 span_loc;
         // get location wrt start of lbam (location==0.0)
         try
         {
            span_loc = GetFracDistance(lbamLoc, span_length);
         }
         catch(FracRes&)
         {
            CComBSTR msg =CreateErrorMsg1D(IDS_E_LOCATION_OOR,lbamLoc);
            ATLASSERT(0);
            THROW_LBAMA_MSG(LOCATION_OOR,msg);
         }

         span_loc += left_end;

         ATLASSERT(span_loc>=left_end && span_loc<=right_end+0.0000001); // This assert keeps firing when
                                                                         // span_loc is equal to right_end
                                                                         // so I added a little tweak

         // next need to find element that this location lies along
         ElementLayoutVec& member_list = m_SpanElements[spanIdx];
         ATLASSERT(!member_list.empty());

         GetFemMemberLocationAlongMemberList( span_loc, left_end, right_end, member_list, locType, pfemId, pfemLoc);
      }
      else
      {
         // no fem members for span
         ATLASSERT(0);
      }
   }
   catch(...)
   {
      ATLASSERT(0);
      throw;
   }
}

void CAnalysisModel::GetFemMemberLocationAlongSupport(const ElementLayoutVec* pMemberList, Float64 lbamLoc, MemberLocationType* locType, MemberIDType* pfemMbrId, Float64* pfemLoc)
{
   ATLASSERT(!(pMemberList->empty()));

   try
   {
      CollectionIndexType num_members = pMemberList->size();

      // get length of support from fe model
      CComPtr<IFem2dMemberCollection> members;
      m_pFem2d->get_Members(&members);

      CComPtr<IFem2dJointCollection> joints;
      m_pFem2d->get_Joints(&joints);

      // location of top and bottom of support
      XyLoc top, bottom;
      MemberIDType bottom_id = (*pMemberList)[0].m_FemMemberID;
      MemberIDType top_id    = (*pMemberList)[num_members-1].m_FemMemberID;
      JointIDType top_joint_id, bottom_joint_id;
      GetMemberEnd( bottom_id, members, joints, metStart, &bottom_joint_id, &bottom.m_X , &bottom.m_Y );
      GetMemberEnd( top_id,    members, joints, metEnd,   &top_joint_id,    &top.m_X ,    &top.m_Y );

      Float64 support_length = top.Distance(bottom);

      // set up tolerance for joint
      Float64 LOC_TOL=support_length*1.0e-07;

      Float64 local_dist; // distance along support from bottom of support
      try
      {
         local_dist = GetFracDistance(lbamLoc, support_length);
      }
      catch(FracRes&)
      {
         CComBSTR msg =CreateErrorMsg1D(IDS_E_LOCATION_OOR,lbamLoc);
         THROW_LBAMA_MSG(LOCATION_OOR,msg);
      }

      // check end conditions first
      if ( IsEqual(local_dist,0.0, LOC_TOL) )
      {
         // location is at start of elements
         *locType = mltLeftEnd;
         *pfemMbrId  = bottom_id;
         *pfemLoc = 0.0;
      }
      else if ( IsEqual(local_dist,support_length, LOC_TOL) )
      {
         // location is at right end
         MemberIDType mbr_id = top_id;
         *locType    = mltRightEnd;
         *pfemMbrId  = mbr_id;
         *pfemLoc = -1.0;
      }
      else
      {
         // compute coordinates of our location in xy
         XyLoc local_loc;
         ComputeSubNodeLocation(bottom, top, local_dist, support_length, &local_loc);

         // loop over elements and find element our location is
         JointIDType  start_joint_id = bottom_joint_id;
         JointIDType  end_joint_id;
         XyLoc start_loc = bottom;
         XyLoc end_loc;
         bool found = false;
         ElementLayoutVec::const_iterator idi( pMemberList->begin() );
         ElementLayoutVec::const_iterator idend( pMemberList->end() );
         for( ; idi!=idend; idi++)
         {
            MemberIDType mbr_id = idi->m_FemMemberID;

            GetMemberEnd(mbr_id, members, joints, metEnd, &end_joint_id, &end_loc.m_X , &end_loc.m_Y);

            // check within member
            if (local_loc.m_Y<=end_loc.m_Y)
            {
               // location is within this member.
               *pfemMbrId   = mbr_id;
               *pfemLoc  = start_loc.Distance(local_loc);
               *locType = mltInternal;
               found = true;
               break;
            }

            start_loc = end_loc;
            start_joint_id = end_joint_id;
         }

         ATLASSERT(found);
      }
   }
   catch(...)
   {
      ATLASSERT(0);
      throw;
   }
}

void CAnalysisModel::ClearLoads()
{
   // clear all loadgroup loads from our fe model
   // know that all loadgroup loads have positive ids.
   // first build list of loads to be removed
   std::vector<LoadCaseIDType> remove_list;
   CComPtr<IFem2dLoadingCollection> fem_loadings;
   m_pFem2d->get_Loadings(&fem_loadings);

   CollectionIndexType num_loadings;
   fem_loadings->get_Count(&num_loadings);

   for (CollectionIndexType ild = 0; ild<num_loadings; ild++)
   {
      CComPtr<IFem2dLoading> fem_loading;
      fem_loadings->get_Item(ild,&fem_loading);

      LoadCaseIDType fem_lc_id;
      fem_loading->get_ID(&fem_lc_id);
      if (0 <= fem_lc_id)
      {
         remove_list.push_back(fem_lc_id);
      }
   }

   // then do removal
   std::vector<LoadCaseIDType>::iterator iid(remove_list.begin());
   std::vector<LoadCaseIDType>::iterator iidend(remove_list.end());
   for (; iid!= iidend; iid++)
   {
      LoadCaseIDType rem_id = *iid;
      LoadCaseIDType id;
      fem_loadings->Remove(rem_id, atID,&id);
      ATLASSERT(id==rem_id);
   }
}

void CAnalysisModel::GenerateLoads()
{
   CollectionIndexType num_loadgroups = m_pLoadGroupOrder->LoadGroupCount();
   for (CollectionIndexType ilg = 0; ilg<num_loadgroups; ilg++)
   {
      CComBSTR load_group = m_pLoadGroupOrder->LoadGroup(ilg);
      GenerateLoadsForLoadGroup(load_group);
   }
}

void CAnalysisModel::GenerateLoadsForLoadGroup(BSTR loadGroup)
{
   ATLASSERT(m_pLBAMModel!=NULL);
   ATLASSERT(m_pFem2d!=NULL);

   try
   {
      // get sequence order for load group - this is used to reference loadings in fem
      LoadGroupIDType fem_lgid;
      bool is_transient;
      m_pLoadGroupOrder->GetLoadGroupInfo(loadGroup,&fem_lgid, &is_transient);

      // create load group in fem model
      CComPtr<IFem2dLoadingCollection> fem_loadings;
      m_pFem2d->get_Loadings(&fem_loadings);

      CComPtr<IFem2dLoading> fem_loading;
      fem_loadings->Create(fem_lgid,&fem_loading);
      ATLASSERT(fem_loading != NULL);

      bool were_loads_applied=false;
      bool wla;
      GeneratePointLoadsForLoadGroup(loadGroup, fem_loading, &wla);
      were_loads_applied |= wla;

      GenerateDistributedLoadsForLoadGroup(loadGroup, fem_loading, &wla);
      were_loads_applied |= wla;

      GenerateStrainLoadsForLoadGroup(loadGroup, fem_loading, &wla);
      were_loads_applied |= wla;

      GenerateTemperatureLoadsForLoadGroup(loadGroup, fem_loading, &wla);
      were_loads_applied |= wla;

      GenerateSettlementLoadsForLoadGroup(loadGroup, fem_loading, &wla);
      were_loads_applied |= wla;

      if (were_loads_applied)
      {
         m_pLoadGroupOrder->SetLoadGroupAsActive(loadGroup);
      }
   }
   catch(_com_error re)
   {
      ATLASSERT(0);
   }
}

void CAnalysisModel::GeneratePointLoadsForLoadGroup(BSTR loadGroup, IFem2dLoading* femLoading, bool *wereLoadsApplied)
{
   CHRException hr;

   *wereLoadsApplied=false;

   CComPtr<IPointLoads> lbam_point_loads;
   hr = m_pLBAMModel->get_PointLoads(&lbam_point_loads);

   CComPtr<IPointLoads> filtered_loads;
   hr = lbam_point_loads->FilterByStageGroup(m_Stage,loadGroup, &filtered_loads);

   CollectionIndexType cnt=0;
   if (filtered_loads!=NULL)
   {
      hr = filtered_loads->get_Count(&cnt);
   }

   if (cnt>0)
   {
      *wereLoadsApplied = true;

      // load could be a point load or joint load depending on location - take this call out of loop
      CComPtr<IFem2dPointLoadCollection> fem_point_loads;
      femLoading->get_PointLoads(&fem_point_loads);

      CComPtr<IFem2dJointLoadCollection> fem_joint_loads;
      femLoading->get_JointLoads(&fem_joint_loads);

      for (CollectionIndexType il=0; il<cnt; il++)
      {
         CComPtr<IPointLoadItem> lbam_point_load_item;
         hr = filtered_loads->get_Item(il, &lbam_point_load_item);

         CComPtr<IPointLoad> lbam_point_load;
         hr = lbam_point_load_item->get_Load(&lbam_point_load);

         MemberType mtype;
         hr = lbam_point_load->get_MemberType(&mtype);

         MemberIDType member_id;
         hr = lbam_point_load->get_MemberID(&member_id);

         Float64 location;
         hr = lbam_point_load->get_Location(&location);

         Float64 fx, fy, mz;
         hr = lbam_point_load->GetForce(&fx, &fy, &mz);

         // two possible cases here. Load was applied on a member, or at the bottom of a support
         if ( (mtype == mtSupport || mtype == mtTemporarySupport) && location==0.0 )
         {
            // load is applied at the bottom of a support. this will be applied as a fem joint load
            JointIDType joint_id;
            if (mtype == mtSupport)
            {
               if (0 <= member_id && member_id < MemberIDType(m_SupportNodes.size()) )
               {
                  joint_id = m_SupportNodes[member_id];
               }
               else
               {
                  CComBSTR msg=CreateErrorMsg1L(IDS_E_SUPPORT_NOT_EXIST, member_id);
                  THROW_LBAMA_MSG(SUPPORT_NOT_EXIST,msg);
               }
            }
            else
            {
               // temporary support
               IdMapIterator it( m_TemporarySupportNodes.find(member_id) );
               if (it!=m_TemporarySupportNodes.end())
               {
                  joint_id = it->second;
               }
               else
               {
                  CComBSTR msg=CreateErrorMsg1L(IDS_E_TEMPSUPPORT_NOT_EXIST, member_id);
                  THROW_LBAMA_MSG(TEMPSUPPORT_NOT_EXIST,msg);
               }
            }

            // found the joint, now apply the load
            try
            {
               CComPtr<IFem2dJointLoad> jointLoad;
               fem_joint_loads->Create(il, joint_id, fx, fy, mz, &jointLoad);
            }
            catch(_com_error re)
            {
               THROW_LBAMA(POINT_LOAD_UNKNOWN);
            }
         }
         else
         {
            // load is applied along an lbam member
            // get fem member and location for load
            MemberLocationType mbl_type;
            MemberIDType       fem_id;
            Float64            fem_loc;

            try
            {
               GetFemLocForLBAMLoc(mtype, member_id, location, &mbl_type, &fem_id, &fem_loc);
            }
            catch(CComException& re)
            {
               // location not on structure - create a message
               CComBSTR msg =CreateErrorMsg1S(IDS_E_POINT_LOAD_LOC, loadGroup);
               msg += re.GetErrorMessage();
               THROW_LBAMA_MSG(POINT_LOAD_LOC,msg);
            }

            try
            {
               if (mltLeftEnd==mbl_type || mltInternal==mbl_type  || mltRightEnd==mbl_type)
               {
                  // to lbam member so map to fem member
                  CComPtr<IFem2dPointLoad> pointLoad;
                  fem_point_loads->Create(il,fem_id, fem_loc, fx, fy, mz,lotGlobal,&pointLoad);
               }
               else if (mltStraddle==mbl_type)
               {
                  // load straddles two members. need to apply joint load  
                  // get joint id - straddle always returns member to right of location
                  CComPtr<IFem2dMemberCollection> members;
                  m_pFem2d->get_Members(&members);

                  CComPtr<IFem2dMember> member;
                  members->Find(fem_id,&member);

                  JointIDType joint_id;
                  member->get_EndJoint(&joint_id);

                  CComPtr<IFem2dJointLoad> jointLoad;
                  fem_joint_loads->Create(il, joint_id, fx, fy, mz, &jointLoad);
               }
               else
                  THROW_HR(E_FAIL); // should be impossible
            }
            catch(_com_error re)
            {
               THROW_LBAMA(POINT_LOAD_UNKNOWN);
            }
         }
      }
   }
}

void CAnalysisModel::GenerateDistributedLoadsForLoadGroup(BSTR loadGroup, IFem2dLoading* pFemLoading, bool *wereLoadsApplied)
{
   CHRException hr;

   *wereLoadsApplied = false;

   try
   {
      CComPtr<IDistributedLoads> lbam_distr_loads;
      hr = m_pLBAMModel->get_DistributedLoads(&lbam_distr_loads);

      CComPtr<IDistributedLoads> filtered_loads;
      hr = lbam_distr_loads->FilterByStageGroup(m_Stage,loadGroup, &filtered_loads);

      CollectionIndexType cnt=0;
      if (filtered_loads!=NULL)
      {
         hr = filtered_loads->get_Count(&cnt);
      }

      if (cnt>0)
      {
         *wereLoadsApplied = true;

         CComPtr<IFem2dDistributedLoadCollection> fem_distr_loads;
         pFemLoading->get_DistributedLoads(&fem_distr_loads);

         LoadIDType last_load_id = 1;

         for (CollectionIndexType il=0; il<cnt; il++)
         {
            CComPtr<IDistributedLoadItem> lbam_distr_load_item;
            hr = filtered_loads->get_Item(il, &lbam_distr_load_item);

            CComPtr<IDistributedLoad> lbam_distr_load;
            hr = lbam_distr_load_item->get_Load(&lbam_distr_load);

            MemberType mtype;
            hr = lbam_distr_load->get_MemberType(&mtype);

            MemberIDType member_id;
            hr = lbam_distr_load->get_MemberID(&member_id);

            Float64 start_location, end_location;
            hr = lbam_distr_load->get_StartLocation(&start_location);
            hr = lbam_distr_load->get_EndLocation(&end_location);

            Float64 w_start, w_end;
            hr = lbam_distr_load->get_WStart(&w_start);
            hr = lbam_distr_load->get_WEnd(&w_end);

            LoadOrientation orientation;
            hr = lbam_distr_load->get_Orientation(&orientation);

            LoadDirection direction;
            hr = lbam_distr_load->get_Direction(&direction);

            Float64 mbr_length = GetLBAMMemberLength(mtype, member_id);

            // get real start and end locations
            try
            {
               start_location = GetFracDistance(start_location, mbr_length, true);
               end_location   = GetFracDistance(end_location, mbr_length, true);
            }
            catch(FracRes&)
            {
               THROW_LBAMA(INVALID_DISTR_LOAD_LOCATION);
            }

            // swap locations if end is before start
            if (end_location < start_location)
            {
               std::swap(end_location, start_location);
               std::swap(w_end, w_start);
            }

            // generate loads only for non-zero cases
            if ( (start_location!=end_location) && !(w_start==0.0 && w_end==0.0) )
            {
               // get fem elements associated with this member
               const ElementLayoutVec* pfem_mbr_list = 0;
               GetFemMembersForLBAMMember(mtype, member_id, &pfem_mbr_list );
               ATLASSERT(pfem_mbr_list !=0 );

               if (pfem_mbr_list->empty())
               {
                  CComBSTR msg1=CreateLBAMContextMsg(mtype, member_id);
                  CComBSTR msg =CreateErrorMsg1S(IDS_E_INVALID_DIST_LOC, msg1);
                  THROW_LBAMA_MSG(INVALID_DIST_LOC,msg);
               }

               // generate distributed load along line of elements
               GenDistributedLoadAlongElements(fem_distr_loads, orientation, direction,
                                               start_location, end_location, mbr_length, 
                                               w_start, w_end, pfem_mbr_list, &last_load_id );
            }
         }
      }
   }
   catch (CComException& re)
   {
      // add some more information
      _bstr_t msg =CreateErrorMsg1S(IDS_E_GENERATING_DISTR_LOAD, loadGroup);
      re.AppendToMessage((TCHAR*)msg);
      throw;
   }
}


void CAnalysisModel::GenDistributedLoadAlongElements(IFem2dDistributedLoadCollection* pFemDistrLoads,
                                                     LoadOrientation orientation, LoadDirection direction,
                                                     Float64 startLocation, Float64 endLocation, 
                                                     Float64 mbrLength, Float64 wStart, Float64 wEnd, 
                                                     const ElementLayoutVec* pfemMbrList, LoadIDType* lastLoadID)
{
   // generic routine to generate a distributed load that is described along a vector of Fem2d members
   // next need to find element that this location lies along
   CComPtr<IFem2dMemberCollection> members;
   m_pFem2d->get_Members(&members);

   CComPtr<IFem2dJointCollection> joints;
   m_pFem2d->get_Joints(&joints);

   // translate load orientation and direction
   Fem2dLoadOrientation f2d_orientation;
   if (orientation==loGlobal)
   {
      f2d_orientation = lotGlobal;
   }
   else if(orientation==loMember)
   {
      f2d_orientation = lotMember;
   }
   else if (orientation==loGlobalProjected)
   {
      f2d_orientation = lotGlobalProjected;
   }
   else
   {
      THROW_LBAMA(INVALID_LOAD_ORIENTATION);
   }

   Fem2dLoadDirection f2d_direction;
   if (direction==ldFx)
   {
      f2d_direction = loadDirFx;
   }
   else if (direction==ldFy)
   {
      f2d_direction = loadDirFy;
   }
   else
   {
      THROW_LBAMA(INVALID_LOAD_DIRECTION);
   }

   // create list of element locations along member
   CollectionIndexType num_elements = pfemMbrList->size();
   std::vector<Float64> locations;
   locations.reserve(num_elements+1);
   locations.push_back(0.0);

   MemberIDType start_id = (*pfemMbrList)[0].m_FemMemberID;
   XyLoc start_loc;
   JointIDType joint_id;
   GetMemberEnd(start_id, members, joints, metStart, &joint_id, &(start_loc.m_X), &(start_loc.m_Y));

   XyLoc cur_loc;
   ElementLayoutVec::const_iterator i(pfemMbrList->begin());
   ElementLayoutVec::const_iterator iend(pfemMbrList->end());
   for (; i!=iend; i++)
   {
      MemberIDType id = i->m_FemMemberID;
      GetMemberEnd(id, members, joints, metEnd, &joint_id, &(cur_loc.m_X), &(cur_loc.m_Y));
      Float64 location = start_loc.Distance(cur_loc);
      locations.push_back(location);
   }

   Float64 tmp_len = locations.back();
   ATLASSERT(mbrLength==locations.back());

   // loop through elements and apply loads
   bool did_end=false;
   for (CollectionIndexType ie=0; ie<num_elements; ie++)
   {
      MemberIDType mbr_id = pfemMbrList->at(ie).m_FemMemberID;
      Float64 mbr_start = locations[ie];
      Float64 mbr_end   = locations[ie+1];

      if (mbr_end>startLocation)
      {
         // load is on this member - get load start/end location/values
         Float64 lloc_start, lloc_end;
         Float64 lw_start, lw_end;

         if (mbr_start<=startLocation)
         {
            lloc_start = startLocation-mbr_start;
            lw_start   = wStart;
         }
         else
         {
            lloc_start = 0.0;
            lw_start = InterpolateDlTrapezoid(mbr_start, startLocation, endLocation, wStart, wEnd);
         }

         if (mbr_end>=endLocation)
         {
            lloc_end = endLocation-mbr_start;
            lw_end   = wEnd;
            did_end = true; // we are finished
         }
         else
         {
            lloc_end = mbr_end-mbr_start;
            lw_end = InterpolateDlTrapezoid(mbr_end, startLocation, endLocation, wStart, wEnd);
         }

         // finally have the information - create the load
         CComPtr<IFem2dDistributedLoad> distLoad;
         pFemDistrLoads->Create(*lastLoadID,mbr_id,f2d_direction,lloc_start,lloc_end,lw_start,lw_end,f2d_orientation,&distLoad);

         (*lastLoadID)++;

         if (did_end)
            break;
      }
   }
}


void CAnalysisModel::GenerateStrainLoadsForLoadGroup(BSTR loadGroup, IFem2dLoading* pFemLoading, bool *wereLoadsApplied)
{
   CHRException hr;

   *wereLoadsApplied = false;

   try
   {
      CComPtr<IStrainLoads> lbam_strain_loads;
      hr = m_pLBAMModel->get_StrainLoads(&lbam_strain_loads);

      CComPtr<IStrainLoads> filtered_loads;
      hr = lbam_strain_loads->FilterByStageGroup(m_Stage,loadGroup, &filtered_loads);

      CollectionIndexType cnt=0;
      if (filtered_loads!=NULL)
      {
         hr = filtered_loads->get_Count(&cnt);
      }

      if (cnt>0)
      {
         *wereLoadsApplied = true;

         CComPtr<IFem2dMemberStrainCollection> fem_strain_loads;
         pFemLoading->get_MemberStrains(&fem_strain_loads);

         LoadIDType last_load_id = 1;

         for (CollectionIndexType il=0; il<cnt; il++)
         {
            CComPtr<IStrainLoadItem> lbam_strain_load_item;
            hr = filtered_loads->get_Item(il, &lbam_strain_load_item);

            CComPtr<IStrainLoad> lbam_strain_load;
            hr = lbam_strain_load_item->get_Load(&lbam_strain_load);

            MemberType mtype;
            hr = lbam_strain_load->get_MemberType(&mtype);

            MemberIDType member_id;
            hr = lbam_strain_load->get_MemberID(&member_id);

            Float64 axial_strain, curvature_strain;
            hr = lbam_strain_load->get_AxialStrain(&axial_strain);
            hr = lbam_strain_load->get_CurvatureStrain(&curvature_strain);

            // get fem elements associated with this member
            const ElementLayoutVec* pfem_mbr_list = 0;
            GetFemMembersForLBAMMember(mtype, member_id, &pfem_mbr_list );
            ATLASSERT(pfem_mbr_list !=0 );

            CollectionIndexType num_elements = pfem_mbr_list->size();

            if (num_elements==0)
            {
               CComBSTR msg1=CreateLBAMContextMsg(mtype, member_id);
               CComBSTR msg =CreateErrorMsg1S(IDS_E_INVALID_STRAIN_LOC, msg1);
               THROW_LBAMA_MSG(INVALID_STRAIN_LOC,msg);
            }

            // iterate over fem elements and apply curvature load for this load case
            for (CollectionIndexType ie=0; ie<num_elements; ie++)
            {
               MemberIDType mbr_id = pfem_mbr_list->at(ie).m_FemMemberID;
               CComPtr<IFem2dMemberStrain> strainLoad;
               fem_strain_loads->Create(last_load_id, mbr_id, axial_strain, curvature_strain,&strainLoad);
               last_load_id++;
            }
         }
      }
   }
   catch (CComException& re)
   {
      // add some more information
      _bstr_t msg =CreateErrorMsg1S(IDS_E_GENERATING_STRAIN_LOAD, loadGroup);
      re.AppendToMessage((TCHAR*)msg);
      throw;
   }
}

void CAnalysisModel::GenerateTemperatureLoadsForLoadGroup(BSTR loadGroup, IFem2dLoading* pFemLoading, bool *wereLoadsApplied)
{
   CHRException hr;

   *wereLoadsApplied=false;

   try
   {
      CComPtr<ITemperatureLoads> lbam_temperature_loads;
      hr = m_pLBAMModel->get_TemperatureLoads(&lbam_temperature_loads);

      CComPtr<ITemperatureLoads> filtered_loads;
      hr = lbam_temperature_loads->FilterByStageGroup(m_Stage,loadGroup, &filtered_loads);

      CollectionIndexType cnt=0;
      if (filtered_loads!=NULL)
      {
         hr = filtered_loads->get_Count(&cnt);
      }

      if (cnt>0)
      {
         *wereLoadsApplied = true;

         // we will convert temperature load into strains below
         CComPtr<IFem2dMemberStrainCollection> fem_strain_loads;
         pFemLoading->get_MemberStrains(&fem_strain_loads);

         LoadIDType last_load_id = 1;

         for (CollectionIndexType il=0; il<cnt; il++)
         {
            CComPtr<ITemperatureLoadItem> lbam_temperature_load_item;
            hr = filtered_loads->get_Item(il, &lbam_temperature_load_item);

            CComPtr<ITemperatureLoad> lbam_temperature_load;
            hr = lbam_temperature_load_item->get_Load(&lbam_temperature_load);

            MemberType mtype;
            hr = lbam_temperature_load->get_MemberType(&mtype);

            MemberIDType member_id;
            hr = lbam_temperature_load->get_MemberID(&member_id);

            Float64 ttop, tbottom;
            hr = lbam_temperature_load->get_TTop(&ttop);
            hr = lbam_temperature_load->get_TBottom(&tbottom);

            Float64 avg_t   = (ttop+tbottom)/2.0;
            Float64 delta_t = tbottom-ttop;

            // get fem elements associated with this member
            const ElementLayoutVec* pfem_mbr_list = 0;
            GetFemMembersForLBAMMember(mtype, member_id, &pfem_mbr_list );
            ATLASSERT(pfem_mbr_list !=0 );

            CollectionIndexType num_elements = pfem_mbr_list->size();

            if (num_elements==0)
            {
               CComBSTR msg1=CreateLBAMContextMsg(mtype, member_id);
               CComBSTR msg =CreateErrorMsg1S(IDS_E_INVALID_TEMPERATURE_LOC, msg1);
               THROW_LBAMA_MSG(INVALID_TEMPERATURE_LOC,msg);
            }

            // iterate over fem elements and apply temperature load for this load case
            for ( CollectionIndexType ie=0; ie<num_elements; ie++)
            {
               MemberIDType mbr_id = pfem_mbr_list->at(ie).m_FemMemberID;
               CComPtr<ISegmentCrossSection> psect = pfem_mbr_list->at(ie).m_XSect;

               // compute strains due to temperature change
               Float64 gamma,depth;
               hr = psect->get_ThermalCoeff(&gamma);
               hr = psect->get_Depth(&depth);

               Float64 axial_strain = avg_t * gamma;

               // zero-depth members have a problem with curvature strains
               Float64 curvature_strain = 0;
               if (delta_t!=0.0 && depth<=0.0)
               {
                  THROW_LBAMA(TEMPERATURE_ZERO_DEPTH);
               }
               else
               {
                  curvature_strain= delta_t * gamma/depth;
               }

               CComPtr<IFem2dMemberStrain> strainLoad;
               fem_strain_loads->Create(last_load_id, mbr_id, axial_strain, curvature_strain, &strainLoad);
               last_load_id++;
            }
         }
      }
   }
   catch (CComException& re)
   {
      // add some more information
      _bstr_t msg =CreateErrorMsg1S(IDS_E_GENERATING_TEMPERATURE_LOAD, loadGroup);
      re.AppendToMessage((TCHAR*)msg);
      throw;
   }
}

void CAnalysisModel::GenerateSettlementLoadsForLoadGroup(BSTR loadGroup, IFem2dLoading* pFemLoading, bool *wereLoadsApplied)
{
   CHRException hr;

   *wereLoadsApplied = false;

   try
   {
      CComPtr<ISettlementLoads> lbam_settlement_loads;
      hr = m_pLBAMModel->get_SettlementLoads(&lbam_settlement_loads);

      CComPtr<ISettlementLoads> filtered_loads;
      hr = lbam_settlement_loads->FilterByStageGroup(m_Stage,loadGroup, &filtered_loads);

      CollectionIndexType cnt=0;
      if (filtered_loads!=NULL)
      {
         hr = filtered_loads->get_Count(&cnt);
      }

      if (cnt>0)
      {
         *wereLoadsApplied = true;

         CComPtr<IFem2dJointDisplacementCollection> fem_settlement_loads;
         pFemLoading->get_JointDisplacements(&fem_settlement_loads);

         LoadIDType last_load_id = 1;

         for (CollectionIndexType il=0; il<cnt; il++)
         {
            CComPtr<ISettlementLoadItem> lbam_settlement_load_item;
            hr = filtered_loads->get_Item(il, &lbam_settlement_load_item);

            CComPtr<ISettlementLoad> lbam_settlement_load;
            hr = lbam_settlement_load_item->get_Load(&lbam_settlement_load);

            MemberIDType support_id;
            hr = lbam_settlement_load->get_MemberID(&support_id);

            Float64 dx, dy, rz;
            hr = lbam_settlement_load->get_Dx(&dx);
            hr = lbam_settlement_load->get_Dy(&dy);
            hr = lbam_settlement_load->get_Rz(&rz);

            // get fem Joint to be loaded
            JointIDType jointID;
            bool found=false;
            // first try supports
            if (0 <= support_id && support_id < SupportIDType(m_SupportNodes.size()) )
            {
               // at a regular support
               jointID = m_SupportNodes[support_id];
               found = true;
            }
            else
            {
               // check temporary supports
               IdMapIterator idi(m_TemporarySupportNodes.find(support_id));
               if (idi != m_TemporarySupportNodes.end())
               {
                  jointID = idi->second;
                  found = true;
               }
            }

            if (found)
            {
               CComPtr<IFem2dJointDisplacement> jointLoad;
               fem_settlement_loads->Create(last_load_id, jointID, dx, dy, rz, &jointLoad);
               last_load_id++;
            }
            else
            {
               CComBSTR msg =CreateErrorMsg1L(IDS_E_SETTLEMENT_LOC, support_id);
               THROW_LBAMA_MSG(SETTLEMENT_LOC,msg);
            }
         }
      }
   }
   catch (CComException& re)
   {
      // add some more information
      _bstr_t msg =CreateErrorMsg1S(IDS_E_GENERATING_SETTLEMENT_LOAD, loadGroup);
      re.AppendToMessage((TCHAR*)msg);
      throw;
   }
}

void CAnalysisModel::ClearPOIs()
{
   // clears out all pois in fem model
   CComPtr<IFem2dPOICollection> fem_pois;
   m_pFem2d->get_POIs(&fem_pois);
   ClearPOIs(fem_pois);
}

void CAnalysisModel::ClearPOIs(IFem2dPOICollection* pFemPois)
{
   // Clear out pois in fem engine
   pFemPois->Clear();
   m_LastFemPoiID=0;

   // clear out our local poi tracking data structure
   std::for_each(m_PoiMap.begin(),m_PoiMap.end(),delete_pointer);
   m_PoiMap.clear();

   m_pPoiTracker = PoiTrackerHolder(NULL);

   m_LastInternalPoiID = 0;
   m_IsPoiMapUpdated   = false;
}

void CAnalysisModel::GeneratePOIs()
{
   // generate pois defined in the LBAM
   GenerateUserDefinedPOIs();

   // Generate pois to "fill in the cracks"
   GenerateInternalPOIs();

   // Perform contraflexure analysis and generate contraflexure pois
   ClearContraflexureLoads();
   GenerateContraflexureLoads();
   GenerateContraflexurePOIs();

   // set up sorted pois
   m_pPoiTracker = PoiTrackerHolder(new SortedPoiMapTracker(m_PoiMap));

#if defined(_DEBUG_LOGGING)
   ATLTRACE(_T("Sorted POIs\n"));
   for (SortedPoiMapTracker::iterator it=m_pPoiTracker->begin(); it!=m_pPoiTracker->end(); it++)
   {
      PoiMap& poi_map = *(*it);

      ATLTRACE( poi_map.GetDescription().c_str() );
   }
#endif

}

void CAnalysisModel::GenerateInternalPOIs()
{
   // This routine checks to see if there are adequate pois for the
   // analysis. If there are not, it generates them.
   GenerateInternalPOIsAtSpans();
   GenerateInternalPOIsAtCantilevers();
   GenerateInternalPOIsAtSuperstructureMembers();
   GenerateInternalPOIsAtTemporarySupports();
}

void CAnalysisModel::GenerateInternalPOIsAtSpans()
{
   CHRException hr;

   // Establish minimum spacings for contraflexure curve
   ATLASSERT(m_MinSpanPoiIncrement>0);

   // Sort all currently defined pois in superstructure by their global X location
   SortedPoiMapTracker poi_tracker(m_PoiMap);

   // Cycle through all spans and make sure we have an adequate number of pois in each
   CComPtr<ISpans> pspans;
   hr = m_pLBAMModel->get_Spans(&pspans);

   SpanIndexType spans_cnt;
   hr = pspans->get_Count(&spans_cnt);
   
   Float64 span_start = 0.0;
   Float64 span_end = 0.0;
   for (SpanIndexType ispan=0; ispan<spans_cnt; ispan++)
   {
      CComPtr<ISpan> pspan;
      hr = pspans->get_Item(ispan, &pspan);

      Float64 span_length;
      hr = pspan->get_Length(&span_length);

      span_start = span_end;
      span_end +=  span_length;
      Float64 min_spacing = span_length/m_MinSpanPoiIncrement;

      // make sure we have a poi at the start of the span
      Float64 curr_location = span_start;
      if (! poi_tracker.IsPoiAtLocation(mtSpan, ispan, curr_location) )
      {
         // no poi here add one
         m_LastInternalPoiID--;
         CreateSpanPOI(m_LastInternalPoiID, ispan, 0.0);
      }

      // increment along length of span making sure we have pois at the minimum spacing
      curr_location += min_spacing;
      while(curr_location < span_end)
      {
         Float64 nearest_location;
         if ( poi_tracker.IsPoiAtNextLocation(curr_location, &nearest_location) )
         {
            // there is already a poi at the min spacing requirement - no need to add on
            curr_location = nearest_location;
         }
         else
         {
            // create an internally generated poi
            m_LastInternalPoiID--;
            CreateSpanPOI(m_LastInternalPoiID, ispan, curr_location-span_start);
         }

         curr_location += min_spacing;
      }

      // check end of span to make sure there is a poi
      if (! poi_tracker.IsPoiAtLocation(mtSpan, ispan, span_end) )
      {
         // no poi here add one
         m_LastInternalPoiID--;
         CreateSpanPOI(m_LastInternalPoiID, ispan, span_length);
      }
   }
}

void CAnalysisModel::GenerateInternalPOIsAtCantilevers()
{

   // Establish minimum spacings for contraflexure curve
   ATLASSERT(m_MinSpanPoiIncrement>0);

   // Sort all currently defined pois in superstructure by their global X location
   SortedPoiMapTracker poi_tracker(m_PoiMap);

   // Check if there is a left overhang and make sure there are adequate pois
   if (m_LeftOverhang>0.0)
   {
      Float64 min_spacing = m_LeftOverhang/m_MinCantileverPoiIncrement;

      for (long is=0; is<=m_MinCantileverPoiIncrement; is++)
      {
         Float64 xloc = -m_LeftOverhang + is*min_spacing;
         CollectionIndexType ssm_idx;
         Float64 ssm_loc;
         if (GetSuperstructureMemberForGlobalX(xloc, &ssm_idx, &ssm_loc))
         {
            if ( !poi_tracker.IsPoiAtLocation(mtSuperstructureMember, ssm_idx, xloc) )
            {
               // Need to create an internally-generated poi on the cantilever
               m_LastInternalPoiID--;
               CreateSsmPOI(m_LastInternalPoiID, ssm_idx, ssm_loc);
            }
         }
         else
         {
            // location not found - this is a big error since we control all input
            ATLASSERT(0);
            THROW_HR(E_FAIL);
         }
      }
   }

   // look at right overhang
   if (m_RightOverhang>0.0)
   {
      Float64 min_spacing = m_RightOverhang/m_MinCantileverPoiIncrement;

      Float64 start_loc = m_TotalLength - m_LeftOverhang - m_RightOverhang;
      for (long is=0; is<=m_MinCantileverPoiIncrement; is++)
      {
         Float64 xloc = start_loc + is*min_spacing;
         CollectionIndexType ssm_idx;
         Float64 ssm_loc;
         if (GetSuperstructureMemberForGlobalX(xloc, &ssm_idx, &ssm_loc))
         {
            if ( !poi_tracker.IsPoiAtLocation(mtSuperstructureMember, ssm_idx, xloc) )
            {
               // Need to create an internally-generated poi on the cantilever
               m_LastInternalPoiID--;
               CreateSsmPOI(m_LastInternalPoiID, ssm_idx, ssm_loc);
            }
         }
         else
         {
            // location not found - this is a big error since we control all input
            ATLASSERT(0);
            THROW_HR(E_FAIL);
         }
      }
   }
}

void CAnalysisModel::GenerateInternalPOIsAtSuperstructureMembers()
{
   CHRException hr;

   CComPtr<ISuperstructureMembers> pssms;
   hr = m_pLBAMModel->get_SuperstructureMembers(&pssms);

   CollectionIndexType ssms_cnt;
   hr = pssms->get_Count(&ssms_cnt);

   // don't need to worry if there is only one ssm
   if (ssms_cnt>1)
   {
      CComPtr<IFem2dPOICollection> fem_pois;
      m_pFem2d->get_POIs(&fem_pois);

      // Sort all currently defined pois in superstructure by their global X location
      SortedPoiMapTracker poi_tracker(m_PoiMap);

      Float64 ssm_start = -m_LeftOverhang;
      Float64 ssm_end = ssm_start;
      Float64 prev_ssm_length=0.0;
      Float64 ssm_length=0.0;
      for (CollectionIndexType issm=0; issm<ssms_cnt; issm++)
      {
         CComPtr<ISuperstructureMember> pssm;
         hr = pssms->get_Item(issm, &pssm);

         prev_ssm_length = ssm_length;
         hr = pssm->get_Length(&ssm_length);

         ssm_start = ssm_end;
         ssm_end +=  ssm_length;

         // update tracker
         poi_tracker.Reset();

         // see if poi is covered and create needed poi if it is not
         // left first
         SortedPoiMapTracker::PoiCoveredRes res = poi_tracker.IsPoiCovered(ssm_start, fem_pois, m_PoiTolerance);
         if (res==SortedPoiMapTracker::Both || res==SortedPoiMapTracker::Right)
         {
            m_LastInternalPoiID--;
            CreateSsmPOI(m_LastInternalPoiID, issm, 0.0);
         }

         // next add at right end if needed
         res = poi_tracker.IsPoiCovered(ssm_end, fem_pois, m_PoiTolerance);
         if (res==SortedPoiMapTracker::Both || res==SortedPoiMapTracker::Left)
         {
            m_LastInternalPoiID--;
            CreateSsmPOI(m_LastInternalPoiID, issm, ssm_length);
         }
      }
   }
}

void CAnalysisModel::GenerateInternalPOIsAtTemporarySupports()
{
   CHRException hr;

   // no need to go farther if there are no temp supports
   if (!m_TemporarySupportElements.empty())
   {
      CComPtr<IFem2dPOICollection> fem_pois;
      m_pFem2d->get_POIs(&fem_pois);

      // Sort all currently defined pois in superstructure by their global X location
      SortedPoiMapTracker poi_tracker(m_PoiMap);

      // Cycle through all spans and make sure we have an adequate number of pois at temporary supports
      CComPtr<ISpans> pspans;
      hr = m_pLBAMModel->get_Spans(&pspans);

      SpanIndexType spans_cnt;
      hr = pspans->get_Count(&spans_cnt);
   
      Float64 span_start = 0.0;
      Float64 span_end = 0.0;
      for (SpanIndexType ispan=0; ispan<spans_cnt; ispan++)
      {
         CComPtr<ISpan> pspan;
         hr = pspans->get_Item(ispan, &pspan);

         // see if span has any temporary supports
         CComPtr<ITemporarySupports> ptss;
         hr = pspan->get_TemporarySupports(&ptss);

         SupportIndexType ts_cnt;
         hr = ptss->get_Count(&ts_cnt);

         if (ts_cnt>0)
         {
            Float64 span_length;
            hr = pspan->get_Length(&span_length);

            span_start = span_end;
            span_end +=  span_length;

            for (SupportIndexType its=0; its<ts_cnt; its++)
            {
               CComPtr<ITemporarySupport> pts;
               hr = ptss->get_Item(its, &pts);

               SupportIDType ts_id;
               hr = pts->get_ID(&ts_id);

               if ( IsTempSupportInModel(ts_id) )
               {
                  // have a ts, need its location
                  Float64 ts_loc;
                  hr = pts->get_Location(&ts_loc);

                  Float64 ts_local_loc = GetFracDistance(ts_loc, span_length);
                  Float64 ts_global_loc = ts_local_loc + span_start;

                  // see if a poi already has it covered - unfortunately we have to reset tracker 
                  // to the start location because temp supports are not necessarily in sorted order
                  poi_tracker.Reset();

                  SortedPoiMapTracker::PoiCoveredRes res = poi_tracker.IsPoiCovered(ts_global_loc, fem_pois, m_PoiTolerance);
                  if (res==SortedPoiMapTracker::Both)
                  {
                     m_LastInternalPoiID--;
                     CreateSpanPOI(m_LastInternalPoiID, ispan, ts_local_loc); // will map to left
                     m_LastInternalPoiID--;
                     Float64 tol = span_length*LAYOUT_TOLERANCE; // want poi just a smidge to the right
                     CreateSpanPOI(m_LastInternalPoiID, ispan, ts_local_loc+tol); // will map to right
                  }
                  else if (res==SortedPoiMapTracker::Left)
                  {
                     m_LastInternalPoiID--;
                     CreateSpanPOI(m_LastInternalPoiID, ispan, ts_local_loc); // will map to left
                  }
                  else if (res==SortedPoiMapTracker::Right)
                  {
                     m_LastInternalPoiID--;
                     Float64 tol = span_length*LAYOUT_TOLERANCE; // want poi just a smidge to the right
                     CreateSpanPOI(m_LastInternalPoiID, ispan, ts_local_loc+tol); // will map to right
                  }
               }
            }
         }
      }
   }
}


void CAnalysisModel::GenerateUserDefinedPOIs()
{
   CHRException hr;
   ATLASSERT(m_pLBAMModel!=NULL);
   ATLASSERT(m_pFem2d!=NULL);

   CComPtr<IFem2dPOICollection> fem_pois;
   m_pFem2d->get_POIs(&fem_pois);

   CComPtr<IPOIs> lbam_pois;
   hr = m_pLBAMModel->get_POIs(&lbam_pois);

   CComPtr<IEnumPOI> enum_pois;
   hr = lbam_pois->get__EnumElements(&enum_pois);

   CComPtr<IPOI> lbam_poi;
   while ( enum_pois->Next(1,&lbam_poi,NULL) != S_FALSE )
   {
      MemberType mtype;
      hr = lbam_poi->get_MemberType(&mtype);

      MemberIDType mbr_id;
      hr = lbam_poi->get_MemberID(&mbr_id);

      Float64 poi_loc;
      hr = lbam_poi->get_Location(&poi_loc);

      PoiIDType poi_id;
      hr = lbam_poi->get_ID(&poi_id);

      // create pois in fem model to correspond with our lbam pois
      if (mtype==mtSpan)
      {
         CreateSpanPOI(poi_id, mbr_id, poi_loc, lbam_poi);
      }
      else if (mtype==mtSuperstructureMember)
      {
         CreateSsmPOI(poi_id, mbr_id, poi_loc, lbam_poi);
      }
      else if (mtype==mtSupport)
      {
         CreateSupportPOI(poi_id, mbr_id, poi_loc, lbam_poi);
      }
      else if (mtype==mtTemporarySupport)
      {
         CreateTemporarySupportPOI(poi_id, mbr_id, poi_loc, lbam_poi);
      }
      else
      {
         CComBSTR msg =CreateErrorMsg1L(IDS_E_INVALID_POI_MEMBER_TYPE, poi_id);
         THROW_LBAMA_MSG(INVALID_POI_MEMBER_TYPE,msg);
      }

      lbam_poi.Release();
   }

#if defined(_DEBUG_LOGGING)
   for (PoiMapIterator it=m_PoiMap.begin(); it!=m_PoiMap.end(); it++)
   {
      PoiMap& poi_map = *(*it);
      ATLTRACE( poi_map.GetDescription().c_str() );
   }
#endif

}


void CAnalysisModel::CreateTemporarySupportPOI(PoiIDType poiID, SupportIDType supportID, Float64 supportLoc, IPOI* poi)
{
   // see if support is in model
   bool is_here;
   try
   {
      is_here = IsTempSupportInModel(supportID);
   }
   catch(CComException& re)
   {
      // location not found. add some context and rethrow
      _bstr_t msg =CreateErrorMsg1L(IDS_POI_INFO, poiID);
      re.AppendToMessage((TCHAR*)msg);
      throw;
   }

   // if support is in this model - process poi. if not, don't
   if (is_here)
   {
      // get fem member and location for poi
      MemberLocationType mbl_type;
      MemberIDType       fem_id;
      Float64            fem_loc;

      try
      {
         GetFemLocForLBAMLoc(mtTemporarySupport, supportID, supportLoc, &mbl_type, &fem_id, &fem_loc);
      }
      catch(CComException& re)
      {
         // location not found. add some context and rethrow
         _bstr_t msg =CreateErrorMsg1L(IDS_POI_INFO, poiID);
         re.AppendToMessage((TCHAR*)msg);
         throw;
      }

      if (mltStraddle==mbl_type)
      {
         // poi straddles two fem members - we want to block this for supports since we would need to write 
         // extra code to transform member coordinates to local cordinates, and that nothing really interesting
         // happens along supports
         ATLASSERT(fem_loc==-1.0); // we should always be mapped to end of right member

         mbl_type = mltInternal;
      }


      if (mltLeftEnd==mbl_type || mltInternal==mbl_type  || mltRightEnd==mbl_type)
      {
         // create poi at member location
         CreateFemPOI(poiID, mtTemporarySupport, supportID, supportLoc, fem_id, fem_loc, mbl_type, poi);
      }
      else
      {
         // location is probably at a joint - this means that the support is zero length.
         // it's illegal to place pois at zero length supports.
         CComBSTR msg =CreateErrorMsg1L(IDS_E_POI_ZERO_LENGTH_SUPPORT, poiID);
         THROW_LBAMA_MSG(POI_ZERO_LENGTH_SUPPORT,msg);
      }
   }
}

void CAnalysisModel::CreateSupportPOI(PoiIDType poiID, SupportIDType supportID, Float64 supportLoc, IPOI* poi)
{
   // get fem member and location for poi
   MemberLocationType mbl_type;
   MemberIDType       fem_id;
   Float64            fem_loc;

   try
   {
      GetFemLocForLBAMLoc(mtSupport, supportID, supportLoc, &mbl_type, &fem_id, &fem_loc);
   }
   catch(CComException& re)
   {
      // location not found. add some context and rethrow
      _bstr_t msg =CreateErrorMsg1L(IDS_POI_INFO, poiID);
      re.AppendToMessage((TCHAR*)msg);
      throw;
   }

   if (mltStraddle==mbl_type)
   {
      // poi straddles two fem members - we want to block this for supports since we would need to write 
      // extra code to transform member coordinates to local cordinates, and that nothing really interesting
      // happens along supports
      ATLASSERT(fem_loc==-1.0); // we should always be mapped to end of right member

      mbl_type = mltInternal;
   }


   if (mltLeftEnd==mbl_type || mltInternal==mbl_type  || mltRightEnd==mbl_type)
   {
      // create poi at member location
      CreateFemPOI(poiID, mtSupport, supportID, supportLoc, fem_id, fem_loc, mbl_type, poi);
   }
   else
   {
      // location is at a joint - this means that the support is zero length.
      // it's illegal to place pois at zero length supports.
      CComBSTR msg =CreateErrorMsg1L(IDS_E_POI_ZERO_LENGTH_SUPPORT, poiID);
      THROW_LBAMA_MSG(POI_ZERO_LENGTH_SUPPORT,msg);
   }
}


void CAnalysisModel::CreateSsmPOI(PoiIDType poiID, CollectionIndexType ssmIdx, Float64 ssmLoc, IPOI* poi)
{
   // get fem member and location for poi
   MemberLocationType mbl_type;
   MemberIDType       fem_id;
   Float64            fem_loc;
   try
   {
      GetFemMemberLocationAlongSSM(ssmIdx, ssmLoc, &mbl_type, &fem_id, &fem_loc);
   }
   catch(CComException& re)
   {
      // location not found. add some context and rethrow
      _bstr_t msg =CreateErrorMsg1L(IDS_POI_INFO, poiID);
      re.AppendToMessage((TCHAR*)msg);
      throw;
   }

   if (mltLeftEnd==mbl_type || mltInternal==mbl_type  || mltRightEnd==mbl_type)
   {
      // create poi at member location
      CreateFemPOI(poiID, mtSuperstructureMember, ssmIdx, ssmLoc, fem_id, fem_loc, mbl_type, poi);
   }
   else if (mltStraddle==mbl_type)
   {
      CreateFemMbrPOI(poiID, mtSuperstructureMember, ssmIdx, ssmLoc, fem_id, poi);
   }
   else
      THROW_HR(E_FAIL); // should be impossible. Logic in GetFemMemberLocationAlongSSM is hosed
}

void CAnalysisModel::CreateSpanPOI(PoiIDType poiID, SpanIndexType spanIdx, Float64 spanLoc, IPOI* poi)
{
   // get fem member and location for poi
   MemberLocationType mbl_type;
   MemberIDType       fem_mbr_id;
   Float64            fem_loc;
   try
   {
      GetFemMemberLocationAlongSpan(spanIdx, spanLoc, &mbl_type, &fem_mbr_id, &fem_loc);
   }
   catch(CComException& re)
   {
      // location not found. add some context and rethrow
      _bstr_t msg =CreateErrorMsg1L(IDS_POI_INFO, poiID);
      re.AppendToMessage((TCHAR*)msg);
      throw;
   }

   if (mltLeftEnd==mbl_type || mltInternal==mbl_type  || mltRightEnd==mbl_type)
   {
      // create poi at member location
      CreateFemPOI(poiID, mtSpan, spanIdx, spanLoc, fem_mbr_id, fem_loc, mbl_type, poi);
   }
   else if (mltStraddle==mbl_type)
   {
      CreateFemMbrPOI(poiID, mtSpan, spanIdx, spanLoc, fem_mbr_id, poi);
   }
   else
      THROW_HR(E_FAIL); // should be impossible. Logic in GetFemMemberLocationAlongSpan is hosed
}

void CAnalysisModel::GetSegmentCrossSectionAtLocation(MemberType mbrType, MemberIDType mbrID, Float64 mbrLoc, ISegmentCrossSection* *leftSegmentCrossSection, ISegmentCrossSection* *rightSegmentCrossSection)

{
   CHRException hr;
   *leftSegmentCrossSection  = NULL;
   *rightSegmentCrossSection = NULL;

   if (mbrType==mtSpan)
   {
      // on a span - need to get section from ssm's
      Float64 xloc, yloc; // location from start of superstructure
      hr = m_pLBAMModel->ComputeLocation(mbrID, mbrType, mbrLoc, &xloc, &yloc);

      CComPtr<ISuperstructureMembers> ssms;
      hr = m_pLBAMModel->get_SuperstructureMembers(&ssms);

      CollectionIndexType ssm_cnt;
      hr = ssms->get_Count(&ssm_cnt);

      // we need to deal with the case where the poi location is at the junction of two ssm's
      // set up a tolerance to determine if this is true.
      Float64 ssms_length;
      hr = ssms->get_Length(&ssms_length);

      Float64 LOC_TOL = ssms_length*1.0e-05;

      // loop over ssms until we find the one with our poi in it
      Float64 ssm_start=0.0;
      Float64 ssm_end=0.0;
      for (CollectionIndexType i_ssm=0; i_ssm<ssm_cnt; i_ssm++)
      {
         CComPtr<ISuperstructureMember> ssm;
         hr = ssms->get_Item(i_ssm, &ssm);

         Float64 ssm_length;
         hr = ssm->get_Length(&ssm_length);

         ssm_end = ssm_start+ssm_length;

         if (ssm_end+LOC_TOL>=xloc)
         {
            // We have our ssm - determine if we are at a ssm junction
            if (ssm_end-(xloc+LOC_TOL)<0.0)
            {
               // We are at the junction of two ssm's (or at the begining or end)
               // Left section will be at right end of current ssm
               CComPtr<ISegmentItem> left_segi, right_segi;
               hr = ssm-> GetSegmentForMemberLocation(m_Stage, -1.0, &left_segi, &right_segi);

               // if left segment is zero - there are no segments for this ssm - just return;
               if (left_segi==NULL)
               {
                  break;
               }
               else
               {
                  // only need left segment item (we are at end of ssm)
                  CComPtr<ISegment> left_seg;
                  hr = left_segi->get_Segment(&left_seg);

                  CComPtr<ISegmentCrossSection> left_cs;
                  hr = left_seg->get_SegmentCrossSection(&left_cs);

                  // got it - make assigment
                  *leftSegmentCrossSection = left_cs.Detach();

                  // right section will be at left end of right ssm ( if there is one)
                  if (i_ssm<ssm_cnt-1)
                  {
                     left_segi.Release();  // recycle
                     right_segi.Release();

                     CComPtr<ISuperstructureMember> ssmr; // ssm to right of xloc
                     hr = ssms->get_Item(i_ssm+1, &ssmr);

                     hr = ssmr-> GetSegmentForMemberLocation(m_Stage, 0.0, &left_segi, &right_segi);

                     if (left_segi==NULL)
                     {
                        break; // no segments in this ssm
                     }
                     else
                     {
                        left_seg.Release();
                        hr = left_segi->get_Segment(&left_seg);

                        left_cs.Release();
                        hr = left_seg->get_SegmentCrossSection(&left_cs);

                        // got it - make assigment
                        *rightSegmentCrossSection = left_cs.Detach();
                     }
                  }

                  break; // we got what we came for
               }
            }
            else
            {
               // not at a junction - just in a ssm
               Float64 ssm_loc = xloc - ssm_start;

               CComPtr<ISegmentItem> left_segi, right_segi;
               hr = ssm-> GetSegmentForMemberLocation(m_Stage, ssm_loc, &left_segi, &right_segi);

               // if left segment is zero - there are no segments for this ssm - just return;
               if (left_segi==NULL)
               {
                  break;
               }
               else
               {
                  // left side first
                  CComPtr<ISegment> left_seg;
                  hr = left_segi->get_Segment(&left_seg);

                  CComPtr<ISegmentCrossSection> left_cs;
                  hr = left_seg->get_SegmentCrossSection(&left_cs);

                  // got it - make assigment
                  *leftSegmentCrossSection = left_cs.Detach();

                  // next, assign right cs if there is one
                  if ( right_segi != NULL)
                  {
                     CComPtr<ISegment> right_seg;
                     hr = right_segi->get_Segment(&right_seg);

                     CComPtr<ISegmentCrossSection> right_cs;
                     hr = right_seg->get_SegmentCrossSection(&right_cs);

                     // got it - make assigment
                     *rightSegmentCrossSection = right_cs.Detach();
                  }

                  break; // we have our cs - get outta here
               }
            }
         }

         ssm_start = ssm_end;
      }
   }
   else if (mbrType==mtSuperstructureMember)
   {
      // on superstucturemember - get cross section directly
      CComPtr<ISuperstructureMembers> ssms;
      hr = m_pLBAMModel->get_SuperstructureMembers(&ssms);

      CollectionIndexType ssm_cnt;
      hr = ssms->get_Count(&ssm_cnt);

      CComPtr<ISuperstructureMember> ssm;
      hr = ssms->get_Item(mbrID, &ssm);

      // we have our ssm
      CComPtr<ISegmentItem> left_segi, right_segi;
      hr = ssm-> GetSegmentForMemberLocation(m_Stage, mbrLoc, &left_segi, &right_segi);

      // if left segment is zero - there are no segments for this ssm - just return;
      if (left_segi!=NULL)
      {
         CComPtr<ISegment> left_seg;
         hr = left_segi->get_Segment(&left_seg);

         CComPtr<ISegmentCrossSection> left_cs;
         hr = left_seg->get_SegmentCrossSection(&left_cs);

         // got it - make assigment
         *leftSegmentCrossSection = left_cs.Detach();

         // next, assign right cs if there is one
         if ( right_segi != NULL)
         {
            CComPtr<ISegment> right_seg;
            hr = right_segi->get_Segment(&right_seg);

            CComPtr<ISegmentCrossSection> right_cs;
            hr = right_seg->get_SegmentCrossSection(&right_cs);

            // got it - make assigment
            *rightSegmentCrossSection = right_cs.Detach();
         }
      }
   }
   else if (mbrType==mtSupport)
   {
      // poi is at a support - get it
      CComPtr<ISupports> supports;
      hr = m_pLBAMModel->get_Supports(&supports);

      CComPtr<ISupport> support;
      hr = supports->get_Item(mbrID, &support);

      CComPtr<ISegmentItem> left_segi, right_segi;
      hr = support-> GetSegmentForMemberLocation(m_Stage, mbrLoc, &left_segi, &right_segi);

      // if left segment is zero - there are no segments for this support - just return;
      if (left_segi!=NULL)
      {
         CComPtr<ISegment> left_seg;
         hr = left_segi->get_Segment(&left_seg);

         CComPtr<ISegmentCrossSection> left_cs;
         hr = left_seg->get_SegmentCrossSection(&left_cs);

         // got it - make assigment
         *leftSegmentCrossSection = left_cs.Detach();

         // next, assign right cs if there is one
         if ( right_segi != NULL)
         {
            CComPtr<ISegment> right_seg;
            hr = right_segi->get_Segment(&right_seg);

            CComPtr<ISegmentCrossSection> right_cs;
            hr = right_seg->get_SegmentCrossSection(&right_cs);

            // got it - make assigment
            *rightSegmentCrossSection = right_cs.Detach();
         }
      }
   }
   else if (mbrType==mtTemporarySupport)
   {
      CComPtr<ITemporarySupport> ts;
      SpanIndexType span_no;
      FindTemporarySupport(m_pLBAMModel, mbrID, &ts, &span_no);

      if (ts != NULL)
      {
         CComPtr<ISegmentItem> left_segi, right_segi;
         hr = ts->GetSegmentForMemberLocation(m_Stage, mbrLoc, &left_segi, &right_segi);

         // if left segment is zero - there are no segments for this support - just return;
         if (left_segi!=NULL)
         {
            CComPtr<ISegment> left_seg;
            hr = left_segi->get_Segment(&left_seg);

            CComPtr<ISegmentCrossSection> left_cs;
            hr = left_seg->get_SegmentCrossSection(&left_cs);

            // got it - make assigment
            *leftSegmentCrossSection = left_cs.Detach();

            // next, assign right cs if there is one
            if ( right_segi != NULL)
            {
               CComPtr<ISegment> right_seg;
               hr = right_segi->get_Segment(&right_seg);

               CComPtr<ISegmentCrossSection> right_cs;
               hr = right_seg->get_SegmentCrossSection(&right_cs);

               // got it - make assigment
               *rightSegmentCrossSection = right_cs.Detach();
            }
         }
      }
      else
      {
         CComBSTR msg =CreateErrorMsg1L(IDS_E_POI_TEMP_SUPPORT_OOR, mbrID);
         THROW_LBAMA_MSG(POI_TEMP_SUPPORT_OOR,msg);
      }
   }
   else
   {
      THROW_LBAMA(INVALID_MEMBER_TYPE);
   }
}

void CAnalysisModel::GetSegmentCrossSectionAtPOI(PoiIDType poiId, ISegmentCrossSection* *leftCs, ISegmentCrossSection* *rightCs)
{
   *leftCs = NULL;
   *rightCs = NULL;

   // get from cached data
   PoiMapIterator it(m_PoiMap.find( &PoiMap(poiId) ));
   if (it != m_PoiMap.end() )
   {
      PoiMap& info = *(*it);

      CComPtr<ISegmentCrossSection> left_sps, right_sps;
      info.GetSegmentCrossSection(&left_sps, &right_sps);
      if (left_sps != NULL)
      {
         left_sps.CopyTo(leftCs);
      }

      if (right_sps != NULL)
      {
         right_sps.CopyTo(rightCs);
      }
   }
   else
   {
      CComBSTR msg = ::CreateErrorMsg1L(IDS_E_POI_NOT_FOUND, poiId);
      THROW_LBAMA_MSG(POI_NOT_FOUND,msg);
   }
}

void CAnalysisModel::GetStressPointsAtPOI(PoiIDType poiId, IStressPoints* *leftSps, IStressPoints* *rightSps)
{
   *leftSps = NULL;
   *rightSps = NULL;

   // get from cached data
   PoiMapIterator it(m_PoiMap.find( &PoiMap(poiId) ));
   if (it != m_PoiMap.end() )
   {
      PoiMap& info = *(*it);

      CComPtr<IStressPoints> left_sps, right_sps;
      info.GetStressPoints(&left_sps, &right_sps);
      if (left_sps != NULL)
      {
         left_sps.CopyTo(leftSps);
      }

      if (right_sps != NULL)
      {
         right_sps.CopyTo(rightSps);
      }
   }
   else
   {
      CComBSTR msg = ::CreateErrorMsg1L(IDS_E_POI_NOT_FOUND, poiId);
      THROW_LBAMA_MSG(POI_NOT_FOUND,msg);
   }
}


void CAnalysisModel::GetPOIDistributionFactor(PoiIDType POI, IDistributionFactor* *leftFactor, IDistributionFactor* *rightFactor)
{
   CHRException hr;

   *leftFactor = NULL;
   *rightFactor= NULL;

   // Perform model look up for each call.
   // Could cache distribution factors here for more performance if lookups become too expensive
   MemberType member_type;
   MemberIDType member_id;
   Float64 member_location;

   hr = this->GetPoiInfo(POI, &member_type, &member_id, &member_location);

   if (member_type==mtSpan || member_type==mtSuperstructureMember)
   {
      // get df segment at superstructure location
      Float64 x, y;
      hr = m_pLBAMModel->ComputeLocation(member_id, member_type, member_location, &x, &y);

      CComPtr<IDistributionFactors> factors;
      hr = m_pLBAMModel->get_DistributionFactors(&factors);

      x += m_LeftOverhang; // put into coord's starting at begining of superstructure

      CComPtr<IDistributionFactorSegment> left_seg, right_seg;
      hr = factors->GetSegmentForLocation(x, m_TotalLength, &left_seg, &right_seg);

      if (left_seg!=NULL)
      {
         hr = left_seg->get_DistributionFactor(leftFactor);
      }
      else
         ATLASSERT(0);

      if (right_seg!=NULL)
      {
         hr = right_seg->get_DistributionFactor(rightFactor);
      }
   }
   else if (member_type==mtSupport)
   {
      // df is at support object
      CComPtr<ISupports> supports;
      hr = m_pLBAMModel->get_Supports(&supports);

      CComPtr<ISupport> support;
      hr = supports->get_Item(member_id, &support);

      hr = support->get_DistributionFactor(leftFactor);
   }
   else if (member_type==mtTemporarySupport)
   {
      CComPtr<ITemporarySupport> temp_support;
      SpanIndexType span_no;
      FindTemporarySupport(m_pLBAMModel, member_id, &temp_support, &span_no);

      if (temp_support!=NULL)
      {
         hr = temp_support->get_DistributionFactor(leftFactor);
      }
      else
      {
         CComBSTR msg(::CreateErrorMsg1L(IDS_E_POI_TEMP_SUPPORT_OOR, POI));
         THROW_LBAMA_MSG(POI_TEMP_SUPPORT_OOR,msg);
      }
   }
   else
      ATLASSERT(0);
}

void CAnalysisModel::GetSupportDistributionFactor(SupportIndexType supportIdx, IDistributionFactor **Factor)
{
   CHRException hr;
   // see if support
   CComPtr<ISupports> supports;
   hr = m_pLBAMModel->get_Supports(&supports);

   SupportIndexType nSupports;
   hr = supports->get_Count(&nSupports);

   if (0 <= supportIdx && supportIdx < nSupports)
   {
      CComPtr<ISupport> support;
      hr = supports->get_Item(supportIdx, &support);

      hr = support->get_DistributionFactor(Factor);
   }
   else
   {
      // not a regular support - mabe a temporary support
      CComPtr<ITemporarySupport> temp_support;
      SpanIndexType spanIdx;
      FindTemporarySupport(m_pLBAMModel, supportIdx, &temp_support, &spanIdx);
      if (temp_support!=NULL)
      {
         hr = temp_support->get_DistributionFactor(Factor);
      }
      else
      {
         // support not found
         *Factor = NULL;
         CComBSTR msg(::CreateErrorMsg1L(IDS_E_SUPPORT_NOT_EXIST, supportIdx));
         THROW_LBAMA_MSG(SUPPORT_NOT_EXIST,msg);
      }
   }
}

void CAnalysisModel::CreateFemPOI(PoiIDType poiID, MemberType mbrType, MemberIDType lbamMbrID, Float64 lbamMbrLoc, 
                                  MemberIDType femMbrID, Float64 femMbrLoc, MemberLocationType locType, IPOI* poi)
{
   CHRException hr;

   // get location in global coords
   Float64 xloc,yloc;
   m_pLBAMModel->ComputeLocation(lbamMbrID,mbrType,lbamMbrLoc,&xloc,&yloc);

   // Create a PoiMap to store creation data
   std::auto_ptr<PoiMapToFemPoi> poi_map(new PoiMapToFemPoi(poiID, xloc, mbrType, lbamMbrID, lbamMbrLoc));

   ATLASSERT(locType!=mltNotFound && locType!=mltStraddle);
   poi_map->SetMemberLocationType(locType);

   // set stress points and other data
   ConfigurePoiMap(mbrType, lbamMbrID, lbamMbrLoc, poi, poi_map.get());

   // create a fem poi - map using fem id
   m_LastFemPoiID++;

   CComPtr<IFem2dPOICollection> fem_pois;
   m_pFem2d->get_POIs(&fem_pois);

   CComPtr<IFem2dPOI> femPoi;
   fem_pois->Create(m_LastFemPoiID, femMbrID, femMbrLoc, &femPoi);

   poi_map->SetFemPoi(m_LastFemPoiID, femMbrLoc);
   poi_map->SetIsInternallyGenerated(poi==NULL);

   // cache away poi information for later
   m_PoiMap.insert( poi_map.release() );
}

void CAnalysisModel::CreateFemMbrPOI(PoiIDType poiID, MemberType mbrType, MemberIDType lbamMbrID, Float64 lbamMbrLoc, 
                                     MemberIDType leftMbrID, IPOI* poi)
{
   // Create a poi that maps to the ends of two members (straddles them).
   CHRException hr;

   // get location in global coords
   Float64 xloc,yloc;
   m_pLBAMModel->ComputeLocation(lbamMbrID,mbrType,lbamMbrLoc,&xloc,&yloc);

   // Create a PoiMap to store creation data
   std::auto_ptr<PoiMapToFemMbr> poi_map(new PoiMapToFemMbr(poiID, xloc, mbrType, lbamMbrID, lbamMbrLoc));

   // Tricky note here: this poi straddles two members. the id of the left member is passed into this function and
   // it is assumed that the id of the right member is 1+ that id. This is true on the superstructure, but probably not
   // for supports. However, assumptions in other code in this module say that straddle pois do not occur in supports.
   // beware if you want to change this.
   poi_map->SetFemMbrs(leftMbrID, leftMbrID+1);

   // set stress points and other data
   ConfigurePoiMap(mbrType, lbamMbrID, lbamMbrLoc, poi, poi_map.get());

   poi_map->SetIsInternallyGenerated(poi==NULL);

   // cache away poi information for later
   m_PoiMap.insert( poi_map.release() );
}


void CAnalysisModel::ConfigurePoiMap(MemberType mbrType, MemberIDType lbamMbrID, Float64 lbamMbrLoc, IPOI* poi, PoiMap* poi_map)
{
   CHRException hr;

   // Cache cross information along with poi for efficiency
   CComPtr<ISegmentCrossSection> left_cs, right_cs;
   GetSegmentCrossSectionAtLocation(mbrType, lbamMbrID, lbamMbrLoc, &left_cs, &right_cs);

   poi_map->SetSegmentCrossSection(left_cs, right_cs);

   // Cache stress points as well
   CComPtr<IStressPoints> left_sps, right_sps;
   hr = left_cs->get_StressPoints(&left_sps);
   if (right_sps!=NULL)
   {
      hr = right_cs->get_StressPoints(&right_sps);
   }
   else
   {
      right_sps = left_sps;
   }

   if (poi!=NULL)  // See if stress points are defined explicitely at poi
   {
      CComPtr<IPOIStressPoints> poi_sps;
      hr = poi->get_POIStressPoints(&poi_sps);

      CComPtr<IPOIStressPointsItem> poi_spsitem;
      HRESULT hrr;
      hrr = poi_sps->get_Item(CComVariant(m_Stage), &poi_spsitem);
      if (SUCCEEDED(hrr))
      {
         // We have stress point collections defined at this poi for this stage
         CComPtr<IStressPoints> poi_left_sps, poi_right_sps;
         hr = poi_spsitem->get_LeftStressPoints(&poi_left_sps);
         hr = poi_spsitem->get_RightStressPoints(&poi_right_sps);

         // Next, check if poi stress points override
         // Left side
         CollectionIndexType num_cs_left_sps, num_poi_left_sps;
         hr = left_sps->get_Count(&num_cs_left_sps);
         hr = poi_left_sps->get_Count(&num_poi_left_sps);
         if (num_poi_left_sps>0)
         {
            if (num_poi_left_sps>=num_cs_left_sps)
            {
               // number of stress points at poi is gte num at cross section, just replace
               left_sps = poi_left_sps;
            }
            else
            {
               // number of sp's defined at poi is less than at cross section. we must create a new stresspoints
               // collection and fill it partially with each
               CComPtr<IStressPoints> new_sps;
               hr = new_sps.CoCreateInstance(CLSID_StressPoints);
               for (CollectionIndexType i=0; i<num_poi_left_sps; i++) // fill first with poi sps
               {
                  CComPtr<IStressPoint> sp;
                  hr = poi_left_sps->get_Item(i, &sp);
                  hr = new_sps->Add(sp);
               }

               for (CollectionIndexType i=num_poi_left_sps; i<num_cs_left_sps; i++) // next with cs sps
               {
                  CComPtr<IStressPoint> sp;
                  hr = left_sps->get_Item(i, &sp);
                  hr = new_sps->Add(sp);
               }

               left_sps = new_sps;
            }
         }

         // Right side
         CollectionIndexType num_cs_right_sps, num_poi_right_sps;
         hr = right_sps->get_Count(&num_cs_right_sps);
         hr = poi_right_sps->get_Count(&num_poi_right_sps);
         if (num_poi_right_sps>0)
         {
            if (num_poi_right_sps>=num_cs_right_sps)
            {
               // number of stress points at poi is gte num at cross section, just replace
               right_sps = poi_right_sps;
            }
            else
            {
               // number of sp's defined at poi is less than at cross section. we must create a new stresspoints
               // collection and fill it partially with each
               CComPtr<IStressPoints> new_sps;
               hr = new_sps.CoCreateInstance(CLSID_StressPoints);
               for (CollectionIndexType i=0; i<num_poi_right_sps; i++) // fill first with poi sps
               {
                  CComPtr<IStressPoint> sp;
                  hr = poi_right_sps->get_Item(i, &sp);
                  hr = new_sps->Add(sp);
               }

               for (CollectionIndexType i=num_poi_right_sps; i<num_cs_right_sps; i++) // next with cs sps
               {
                  CComPtr<IStressPoint> sp;
                  hr = right_sps->get_Item(i, &sp);
                  hr = new_sps->Add(sp);
               }

               right_sps = new_sps;
            }
         }
      }
      else
      {
         // stress points not at this poi for this stage - no big deal
         ATLASSERT(hrr==LBAM_E_POI_NO_STAGE); // if another error occurred, there is a problem
      }
   }

   poi_map->SetStressPoints(left_sps, right_sps);
}


bool CAnalysisModel::IsTempSupportInModel(SupportIDType tmpSupportID)
{
   // this tests if it exists in the lbam at all
   IdSetIterator idsi( m_TemporarySupportIDs.find(tmpSupportID) );
   if ( idsi != m_TemporarySupportIDs.end() )
   {
      // see if it has a support node - if it does, it's in this model
      IdMapIterator itm( m_TemporarySupportNodes.find(tmpSupportID) );
      if (itm != m_TemporarySupportNodes.end())
         return true;
      else
         return false;
   }
   else
   {
      CComBSTR msg =CreateErrorMsg1L(IDS_E_TEMPSUPPORT_NOT_EXIST,tmpSupportID);
      THROW_LBAMA_MSG(TEMPSUPPORT_NOT_EXIST,msg);
   }

   return false;
}

bool CAnalysisModel::GetSuperstructureMemberForGlobalX(Float64 xLoc, CollectionIndexType* ssmIdx, Float64* ssmXLoc)
{
   CHRException hr;

   CComPtr<ISuperstructureMembers> pssms;
   hr = m_pLBAMModel->get_SuperstructureMembers(&pssms);

   CollectionIndexType ssm_cnt;
   hr = pssms->get_Count(&ssm_cnt);

   // we need to deal with the case where the location is in dispute
   // set up a tolerance to determine if this is true.
   Float64 ssms_length;
   hr = pssms->get_Length(&ssms_length);

   Float64 LOC_TOL = ssms_length*1.0e-05;

   // left overhang
   Float64 left_oh;
   hr = pssms->get_Offset(&left_oh);

   // loop over ssms until we find the one with our location in it
   Float64 start_loc = -left_oh;

   if (xLoc<start_loc)
   {
      ATLASSERT(0); // location off of left end
      return false;
   }

   for (CollectionIndexType i_ssm=0; i_ssm<ssm_cnt; i_ssm++)
   {
      CComPtr<ISuperstructureMember> ssm;
      hr = pssms->get_Item(i_ssm, &ssm);

      Float64 ssm_length;
      hr = ssm->get_Length(&ssm_length);

      Float64 end_loc = start_loc + ssm_length;

      if (xLoc <= end_loc)
      {
         Float64 ssm_loc = xLoc - start_loc;
         *ssmIdx = i_ssm;
         *ssmXLoc = ssm_loc;
         return true;
      }

      if (i_ssm==ssm_cnt-1)
      {
         // we hit the end and did not find our location - let's see if we're within tolerance
         if (xLoc-end_loc<LOC_TOL)
         {
            *ssmIdx = i_ssm;
            *ssmXLoc = ssm_length;
            return true;
         }
         else
            ATLASSERT(0); // off of right end
      }

      start_loc = end_loc;
   }

   return false;
}


void GetMemberEnd(MemberIDType mbrID, IFem2dMemberCollection* pMembers, IFem2dJointCollection* pJoints, Fem2dMbrEndType end, JointIDType* jointID, Float64* xLoc, Float64* yLoc)
{
   CComPtr<IFem2dMember> member;
   pMembers->Find(mbrID,&member);

   if(member==NULL)
      THROW_HR(E_FAIL); 

   JointIDType joint_id;
   if (end== metStart)
   {
      member->get_StartJoint(&joint_id);
   }
   else
   {
      member->get_EndJoint(&joint_id);
   }

   CComPtr<IFem2dJoint> joint;
   pJoints->Find(joint_id,&joint);

   if(joint==NULL)
      THROW_HR(E_FAIL); 

   *jointID = joint_id;
   joint->get_X(xLoc);
   joint->get_Y(yLoc);
}

void SetNodeNumbering(SuperNodeLocs* pNodeLocs)
{
   // cycle through model from left to right and number nodes
   JointIDType curr_node=0;

   SuperNodeLocIterator isn(pNodeLocs->begin());
   SuperNodeLocIterator isnend(pNodeLocs->end());
   for (; isn!=isnend; isn++)
   {
      SuperNodeLoc& rsnl = *isn;

      rsnl.m_FemJointID = curr_node;

      if (rsnl.IsReason(nrSpanEnd) || rsnl.IsReason(nrTemporarySupport))
      {
         // node has a support attached - walk down support and apply node numbers
         SubNodeLocs* psnl = rsnl.GetSubNodeLocs();
         ATLASSERT(psnl!=0);

         SetNodeNumberForSupport(psnl, &curr_node);
      }

      curr_node++;
   }
}

void SetNodeNumberForSupport(SubNodeLocs* pSnls, JointIDType* pcurrNode)
{
   // number of top node at support is same as currNode coming in
   // support nodes are ordered from bottom up
   bool first = true;
   typedef SubNodeLocs::reverse_iterator SnRi;
   SnRi ri(pSnls->rbegin());
   SnRi riend(pSnls->rend());
   for ( ; ri!=riend; ri++)
   {
      SubNodeLoc& rsnl = *ri;
      if (!first)
      {
         rsnl.m_FemJointID = ++(*pcurrNode);
      }
      else
      {
         // top node of support
         rsnl.m_FemJointID = *pcurrNode;
         first = false;
      }
   }
}

void CAnalysisModel::GenerateFemModel(SuperNodeLocs* pNodeLocs)
{
   // create our fem model
   m_pFem2d.CoCreateInstance(CLSID_Fem2dModel);
   ATLASSERT(m_pFem2d != NULL);
   // If this assert fails, check to see that the CLSID has not changed
   // This CLSID is defined in the WBFLFem2d IDL file and is COPIED in LBAMAnalysis.cpp
   if ( m_pFem2d == NULL )
   {
      throw;
   }

   CComPtr<IFem2dJointCollection> pJoints;
   m_pFem2d->get_Joints(&pJoints);

   CComPtr<IFem2dMemberCollection> pMembers;
   m_pFem2d->get_Members(&pMembers);

   // ID's for our elements to be generated 
   // NOTE: other locations in this module assume that element numbers are >=0. Don't muck with this!
   MemberIDType nextFemMemberID = 0;

   GenerateSuperstructureFemModel(pNodeLocs, pJoints, pMembers, &nextFemMemberID);
   GenerateSubstructureFemModel(pNodeLocs, pJoints, pMembers, &nextFemMemberID);

   // check for unstable nodes at ssm ends and supports
   CheckFemModelStability(pNodeLocs, pJoints, pMembers);

}

void CAnalysisModel::GenerateSuperstructureFemModel(SuperNodeLocs* pNodeLocs,  IFem2dJointCollection* pJoints, IFem2dMemberCollection* pMembers, MemberIDType* pNextFemMemberID)
{
   CHRException hr;
   // gather some statistics and pre allocate some space for element numbers
   SpanIndexType nSpans = m_SpanEnds.size();
   CollectionIndexType nSuperstructureMembers  = m_SuperstructureMemberEnds.size();

   m_SpanElements.reserve(nSpans);
   for (SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++)
   {
      m_SpanElements.push_back( ElementLayoutVec() );
   }

   m_SuperstructureMemberElements.reserve(nSuperstructureMembers);
   for (CollectionIndexType ssmbrIdx = 0; ssmbrIdx < nSuperstructureMembers; ssmbrIdx++)
   {
      m_SuperstructureMemberElements.push_back( ElementLayoutVec() );
   }

   long curr_span    = -1;  // current span
   long curr_ssm     =  0;  // current superstructuremember

   // walk our superstructure layout and create only superstructure elements (members)
   SuperNodeLocIterator lefty(pNodeLocs->begin());
   SuperNodeLocIterator righty(lefty);
   righty++;
   ATLASSERT(righty!= pNodeLocs->end());

   // have to set up loop entry
   if (lefty->IsReason(nrSpanEnd))
      curr_span = 0;

   if ( !lefty->IsReason(nrMemberEnd) )
      THROW_HR(E_FAIL); // leftmost node should always be a member end. model building logic should assure this

   // create left-most node
   CComPtr<IFem2dJoint> left_joint;
   pJoints->Create(lefty->m_FemJointID, lefty->GetLoc(), 0.0, &left_joint);

   // loop through node layout and generate members
   while ( righty != pNodeLocs->end() )
   {
      SuperNodeLoc& right_node = *righty;
      SuperNodeLoc& left_node  = *lefty;

      // create joint
      CComPtr<IFem2dJoint> joint;
      pJoints->Create(right_node.m_FemJointID, right_node.GetLoc(), 0.0, &joint);

      // get section information and create element (member)
      Float64 ea, ei;
      CComPtr<ISegmentCrossSection> SegmentCrossSection;
      right_node.GetSegmentCrossSection(&SegmentCrossSection);
      if (SegmentCrossSection == NULL)
         THROW_HR(E_FAIL);

      if (m_bForcesModel)
      {
         hr = SegmentCrossSection->get_EAForce(&ea);
         hr = SegmentCrossSection->get_EIForce(&ei);
      }
      else
      {
         hr = SegmentCrossSection->get_EADefl(&ea);
         hr = SegmentCrossSection->get_EIDefl(&ei);
      }

      MemberIDType femMemberID = *pNextFemMemberID;
      (*pNextFemMemberID)++;

      CComPtr<IFem2dMember> pmbr;
      pMembers->Create(femMemberID, left_node.m_FemJointID, right_node.m_FemJointID, ea, ei, &pmbr);

      // add element number to our lists
      m_SuperstructureMemberElements[curr_ssm].push_back( ElementLayout(femMemberID, SegmentCrossSection) );

      if ( (curr_span != -1) && (curr_span < long(nSpans)) )
      {
         m_SpanElements[curr_span].push_back( ElementLayout(femMemberID, SegmentCrossSection) );
      }

      // deal with end releases
      if (left_node.IsPinned(ssRight))
      {
         pmbr->ReleaseEnd(metStart, mbrReleaseMz);
      }

      if (right_node.IsPinned(ssLeft))
      {
         pmbr->ReleaseEnd(metEnd, mbrReleaseMz);
      }

      // update span and ssm numbers for next go around
      if (right_node.IsReason(nrSpanEnd))
         curr_span++;

      if (right_node.IsReason(nrMemberEnd))
         curr_ssm++;

      lefty=righty;
      righty++;
   }

   ATLASSERT(curr_span == nSpans);
   ATLASSERT(curr_ssm == nSuperstructureMembers);
}

void CAnalysisModel::CheckFemModelStability(SuperNodeLocs* pNodeLocs,  IFem2dJointCollection* pJoints, IFem2dMemberCollection* pMembers)
{
   // FEM model is built, but there may be some supports that are not connected to members and some
   // ssm nodes that were generated but never attached to anything
   // iterator over all nodes and check to see if ssm and span ends are connected to members
   SuperNodeLocIterator superstructureNodeIter(pNodeLocs->begin());
   SuperNodeLocIterator superstructureNodeIterEnd(pNodeLocs->end());
   for (; superstructureNodeIter != superstructureNodeIterEnd; superstructureNodeIter++)
   {
      SuperNodeLoc& superstructureNodeLocation = *superstructureNodeIter;
      if (superstructureNodeLocation.IsReason(nrSpanEnd) || 
          superstructureNodeLocation.IsReason(nrMemberEnd))
      {
         // check to see it node is connected
         JointIDType jointID = superstructureNodeLocation.m_FemJointID;
         CComPtr<IFem2dJoint> joint;
         pJoints->Find(jointID,&joint);

         if (joint != NULL)
         {
            CComPtr<ILongArray> femMemberIDs;
            joint->get_Members(&femMemberIDs);

            CollectionIndexType nMembers;
            femMemberIDs->get_Count(&nMembers);
            if (0 < nMembers)
            {
               // have some members attached to joint - make sure it is stable rotationally
               bool is_stable=false;
               for (CollectionIndexType mbrIdx = 0; mbrIdx < nMembers; mbrIdx++)
               {
                  MemberIDType mbrID;
                  femMemberIDs->get_Item(mbrIdx,&mbrID);
                  CComPtr<IFem2dMember> member;
                  pMembers->Find(mbrID,&member);

                  if (member != NULL)
                  {
                     JointIDType startJointID;
                     member->get_StartJoint(&startJointID);

                     JointIDType endJointID;
                     member->get_EndJoint(&endJointID);

                     if (jointID == startJointID) 
                     {
                        VARIANT_BOOL vbIsReleased;
                        member->IsReleased(metStart,&vbIsReleased);
                        if (vbIsReleased == VARIANT_FALSE)
                        {
                           is_stable = true;
                           break;
                        }
                     }
                     else if (jointID == endJointID)
                     {
                        VARIANT_BOOL vbIsReleased;
                        member->IsReleased(metEnd,&vbIsReleased);
                        if (vbIsReleased == VARIANT_FALSE)
                        {
                           is_stable = true;
                           break;
                        }
                     }
                     else
                     {
                        ATLASSERT(0);
                        THROW_HR(E_FAIL);
                     }
                  }
                  else
                  {
                     ATLASSERT(0);
                     THROW_HR(E_FAIL); // should never happen
                  }
               }

               // fix up rotation if joint is not stable
               if (!is_stable)
               {
                  // joint interface is less than optimal for doing this
                  VARIANT_BOOL is_fx;
                  joint->IsDofReleased(jrtFx,&is_fx);

                  VARIANT_BOOL is_fy;
                  joint->IsDofReleased(jrtFy,&is_fy);

                  joint->Support();
                  if (is_fx==VARIANT_TRUE)
                  {
                     joint->ReleaseDof(jrtFx);
                  }

                  if (is_fy==VARIANT_TRUE)
                  {
                     joint->ReleaseDof(jrtFy);
                  }
               }
            }
            else
            {
               // no members attached to joint - support it completely
               joint->Support();
            }
         }
         else
         {
            ATLASSERT(0);
            THROW_HR(E_FAIL); // this should never happen
         }

      }
   }
}

void CAnalysisModel::GenerateSubstructureFemModel(SuperNodeLocs* pNodeLocs,  IFem2dJointCollection* pJoints, IFem2dMemberCollection* pMembers, MemberIDType* pNextFemMemberID)
{
   // gather some statistics and pre allocate some space for element numbers
   SupportIndexType nSupports = m_SpanEnds.size()+1;
   m_SupportNodes.reserve(nSupports);

   m_SupportElements.reserve(nSupports);
   for (SupportIndexType i = 0; i < nSupports; i++)
   {
      m_SupportElements.push_back( ElementLayoutVec() );
   }

   SupportIDType nextSupportID = 0;

   // walk our superstructure layout looking for supports
   // loop through node layout and generate members
   SuperNodeLocIterator superstructureNodeIter(pNodeLocs->begin());
   SuperNodeLocIterator send(pNodeLocs->end());
   for (; superstructureNodeIter != send; superstructureNodeIter++ )
   {
      SuperNodeLoc superstructureNodeLocation = *superstructureNodeIter;

      // is a support at this node?
      if (superstructureNodeLocation.IsReason(nrSpanEnd))
      {
         SubNodeLocs* substructureNodeLocations = superstructureNodeLocation.GetSubNodeLocs();
         ATLASSERT(substructureNodeLocations != NULL);

         GenerateSupportFemModel(substructureNodeLocations, pJoints, pMembers, &m_SupportElements[nextSupportID], pNextFemMemberID);

         // store location of support bottom node
         SubNodeLocs::iterator substructureNodeIter(substructureNodeLocations->begin());
         m_SupportNodes.push_back(substructureNodeIter->m_FemJointID);

         nextSupportID++;
      }
      else if (superstructureNodeLocation.IsReason(nrTemporarySupport))
      {
         // we have a temporary support - build its model
         SubNodeLocs* substructureNodeLocations = superstructureNodeLocation.GetSubNodeLocs();
         ATLASSERT(substructureNodeLocations != NULL);

         // store element ids generated for temp support
         SupportIDType lbamTempSupportID = substructureNodeLocations->m_LbamTemporarySupportID;
         std::pair<ElementLayoutMapIterator, bool> result;
         result = m_TemporarySupportElements.insert( ElementLayoutMap::value_type(lbamTempSupportID, ElementLayoutVec()));
         if (!result.second)
         {
            // there are two temporary supports with the same id
            // this should never happen because it should be blocked by previous code
            CComBSTR msg =CreateErrorMsg1L(IDS_E_TEMPORARY_SUPPORT_ID, lbamTempSupportID);
            THROW_LBAMA_MSG(TEMPORARY_SUPPORT_ID,msg);
         }

         ElementLayoutVec& rvec = (*(result.first)).second;
         GenerateSupportFemModel(substructureNodeLocations, pJoints, pMembers, &rvec, pNextFemMemberID);

         // store node number at bottom of temporary support
         SubNodeLocs::iterator isnl(substructureNodeLocations->begin());
         JointIDType jointID = isnl->m_FemJointID;
         std::pair<IdMapIterator, bool> result2;
         result2 = m_TemporarySupportNodes.insert(IdMap::value_type(lbamTempSupportID, jointID));
         if (!result2.second)
            THROW_HR(E_FAIL); // should have been caught by the insert above
      }
      else if (superstructureNodeLocation.IsReason(nrTemporarySupportLoc))
      {
         // This is a location for a temporary support that occurred in a previous stage
         // We need to save its id so reaction forces can be applied by our client
         SupportIDType lbamTempSupportID = superstructureNodeLocation.m_LBamTempSupportID;
         JointIDType jointID = superstructureNodeLocation.m_FemJointID;
         m_TemporarySupportNodeLocs.insert(IdMap::value_type(lbamTempSupportID, jointID));
      }
   }

   ATLASSERT(nextSupportID == nSupports);
}


void ApplyJointBC(IFem2dJoint* pjnt, BoundaryConditionType bc)
{
   if (bc == bcFixed)
   {
      pjnt->Support();
   }
   else if (bc == bcRoller)
   {
      pjnt->Support();
      pjnt->ReleaseDof(jrtMz);
      pjnt->ReleaseDof(jrtFx);
   }
   else if (bc == bcPinned)
   {
      pjnt->Support();
      pjnt->ReleaseDof(jrtMz);
   }
   else
      THROW_HR(E_FAIL);
}

void CAnalysisModel::GenerateSupportFemModel(SubNodeLocs* pSnls, 
                                             IFem2dJointCollection* pJoints, 
                                             IFem2dMemberCollection* pMembers, 
                                             ElementLayoutVec* pLayoutVec, MemberIDType* pNextFemMemberID)
{
   ATLASSERT(!pSnls->empty());
   CHRException hr;
   try
   {  
      CollectionIndexType nSubstructureNodeLocations = pSnls->size();

      if (nSubstructureNodeLocations == 1)
      {
         // we have a zero-length support. We only need concern ourselves with boundary conditions
         SubNodeLocIterator substructureNodeLocationIter(pSnls->begin());
         SubNodeLoc& substructureNodeLocation = *substructureNodeLocationIter;
         CComPtr<IFem2dJoint> pjnt;
         pJoints->Find(substructureNodeLocation.m_FemJointID,&pjnt);

         ApplyJointBC(pjnt, pSnls->m_BC);
      }
      else
      {
         // support has members. generate them
         // walk list from bottom up
         Uint32 nSubstructureMembers = 2;
         SubNodeLocIterator lefty(pSnls->begin());
         SubNodeLocIterator righty(lefty);
         righty++;

         SubNodeLocIterator send(pSnls->end());
         while( righty != send )
         {
            SubNodeLoc& rlefty  = *lefty;
            SubNodeLoc& rrighty = *righty;

            if (nSubstructureMembers == 2)
            {
               // create bottom joint and apply boundary conditions
               CComPtr<IFem2dJoint> pbot;
               pJoints->Create(lefty->m_FemJointID, lefty->GetXLoc(), lefty->GetYLoc(), &pbot );
               ApplyJointBC(pbot, pSnls->m_BC);
            }

            // create right joint if not last. (last joint is already part of superstructure).
            if (nSubstructureMembers < nSubstructureNodeLocations)
            {
               CComPtr<IFem2dJoint> right_joint;
               pJoints->Create(righty->m_FemJointID, righty->GetXLoc(), righty->GetYLoc(), &right_joint );
            }

            Float64 ea, ei;
            CComPtr<ISegmentCrossSection> SegmentCrossSection;
            righty->GetSegmentCrossSection(&SegmentCrossSection);
            ATLASSERT(SegmentCrossSection != NULL);
            if (m_bForcesModel)
            {
               hr = SegmentCrossSection->get_EAForce(&ea);
               hr = SegmentCrossSection->get_EIForce(&ei);
            }
            else
            {
               hr = SegmentCrossSection->get_EADefl(&ea);
               hr = SegmentCrossSection->get_EIDefl(&ei);
            }

            // create element
            MemberIDType femMemberID = (*pNextFemMemberID);
            (*pNextFemMemberID)++;
            CComPtr<IFem2dMember> pmember;
            pMembers->Create(femMemberID, lefty->m_FemJointID, righty->m_FemJointID, ea, ei, &pmember);

            // save element number and section for later use
            pLayoutVec->push_back( ElementLayout(femMemberID, SegmentCrossSection) );

            // Deal with member top release
            if (nSubstructureMembers == nSubstructureNodeLocations)
            {
               if (pSnls->m_TopRelease == VARIANT_TRUE)
               {
                  ATLASSERT(pmember!=NULL);
                  pmember->ReleaseEnd(metEnd, mbrReleaseMz);
               }
            }

            nSubstructureMembers++;
            lefty = righty;
            righty++;
         }
      }
   }
   catch (_com_error cre)
   {
      ATLASSERT(0);// try to catch bugs where they happen.
      throw;
   }
}

void CAnalysisModel::LayoutSuperstructure(ISuperstructureMembers* pMembers, ISpans* pSpans, ISupports* pSupports, SuperNodeLocs* pSuperNodeLocs)
{
   // place nodes for spans and supports
   LayoutSpanNodes(pMembers, pSpans, pSupports, pSuperNodeLocs);
   // nodes for superstructuremembers
   LayoutSuperstructureMemberNodes(pMembers, pSuperNodeLocs);
   // place member hinges
   PlaceHinges(pMembers, m_LeftOverhang, pSuperNodeLocs);
   // make sure nodes are not too close to each other
   CondenseSuperNodeSections(pSuperNodeLocs, m_LayoutTolerance);
   // insure that that a cross section is assigned to every node 
   AssignSectionsToNodes(pSuperNodeLocs);
}

void CAnalysisModel::LayoutSpanNodes(ISuperstructureMembers* pMembers, ISpans* pSpans, ISupports* pSupports, SuperNodeLocs* pSuperNodeLocs)
{
   CHRException hr;
   // layout node locations for spans and supports
   // start of span 0 and support 0
   std::pair<SuperNodeLocIterator, bool> result;
   result = pSuperNodeLocs->insert( SuperNodeLoc(0.0, nrSpanEnd) );
   if (!result.second)
      THROW_HR(E_FAIL); // should never happen

   // lay out support 0
   SubNodeLocs* plocs = result.first->GetSubNodeLocs();
   LayoutSupport( 0, pSupports, plocs );

   SpanIndexType nSpans;
   hr = pSpans->get_Count(&nSpans);

   Float64 span_start=0.0;
   Float64 span_end=0.0;
   for (SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++)
   {
      Float64 span_length;
      CComPtr<ISpan> span;
      hr = pSpans->get_Item(spanIdx, &span);

      hr = span->get_Length(&span_length);

      if (span_length <= m_LayoutTolerance*2)
      {
         THROW_LBAMA(SPAN_LENGTH_MUST_BE_GT_ZERO);
      }

      // insert location of span end and lay out support
      span_end = span_start + span_length;
      m_SpanEnds.push_back(span_end);

      m_AllSpanEnds.insert(span_end);

      result = pSuperNodeLocs->insert( SuperNodeLoc(span_end, nrSpanEnd) );
      if (!result.second)
         THROW_HR(E_FAIL); // should never happen

      // lay out support 
      SubNodeLocs* plocs = result.first->GetSubNodeLocs();
      LayoutSupport( SupportIDType(spanIdx+1), pSupports, plocs );

      // now look for temporary supports in the span and place super s nodes for them
      CComPtr<ITemporarySupports> temporarySupports;
      hr = span->get_TemporarySupports(&temporarySupports);

      SupportIndexType nTempSupports;
      hr = temporarySupports->get_Count(&nTempSupports);

      for (SupportIndexType tempSupportIdx = 0; tempSupportIdx < nTempSupports; tempSupportIdx++ )
      {
         CComPtr<ITemporarySupport> tempSupport;
         hr = temporarySupports->get_Item(tempSupportIdx, &tempSupport);

         SupportIDType tempSupportID;
         hr = tempSupport->get_ID(&tempSupportID);

         // add to list of all temporary supports. This will save us from having to hunt this down later
         std::pair<IdSetIterator,bool> ids( m_TemporarySupportIDs.insert(tempSupportID));
         if (!ids.second)
         {
            // there are two temporary supports with the same id
            CComBSTR msg =CreateErrorMsg1L(IDS_E_TEMPORARY_SUPPORT_ID, tempSupportID);
            THROW_LBAMA_MSG(TEMPORARY_SUPPORT_ID,msg);
         }

         Float64 tempSupportFractionalLocation;
         hr = tempSupport->get_Location(&tempSupportFractionalLocation);

         // temporary supports must have unique id from support numbers
         if (0 <= tempSupportID && tempSupportID < SupportIDType(nSpans+1))
         {
            CComBSTR msg =CreateErrorMsg2L(IDS_E_INVALID_TS_ID_SUPPORT,tempSupportIdx, spanIdx);
            THROW_LBAMA_MSG(INVALID_TS_ID_SUPPORT,msg);
         }

         try
         {
            Float64 tempSupportLocation = GetFracDistance(tempSupportFractionalLocation, span_length);
            tempSupportLocation += span_start;

            // make sure temporary support is not too close to span ends
            if ( (tempSupportLocation-span_start) < m_LayoutTolerance || (span_end-tempSupportLocation) < m_LayoutTolerance)
            {
               CComBSTR msg =CreateErrorMsg2L(IDS_E_TEMPSUPPORT_DIST,tempSupportIdx, spanIdx);
               THROW_LBAMA_MSG(TEMPSUPPORT_DIST,msg);
            }

            if ( IsTempSupportInStage(tempSupport) )
            {
               // temporary support belongs in this model
               SuperNodeLoc tempSupportNodeLocation(tempSupportLocation, nrTemporarySupport);
               tempSupportNodeLocation.m_LBamTempSupportID = tempSupportID;
               result = pSuperNodeLocs->insert( tempSupportNodeLocation );
               if (!result.second)
                  THROW_HR(E_FAIL); // should never happen

               // lay out temporary support 
               SubNodeLocs* plocs = result.first->GetSubNodeLocs();
               LayoutTemporarySupport( SupportIDType(spanIdx), tempSupportLocation, tempSupport, plocs );

               // add temp support location to list of all span ends
               m_AllSpanEnds.insert(tempSupportLocation);
            }
            else
            {
               // temporary support was in a previous stage - put a node at the ts location
               // so we can apply reaction loads later
               SuperNodeLoc tempSupportNodeLocation(tempSupportLocation, nrTemporarySupportLoc);
               tempSupportNodeLocation.m_LBamTempSupportID = tempSupportID;
               result = pSuperNodeLocs->insert( tempSupportNodeLocation );
               if (!result.second)
                  THROW_HR(E_FAIL); // should never happen
            }
         }
         catch(FracRes&)
         {
            CComBSTR msg =CreateErrorMsg2L(IDS_E_INVALID_TS_LOCATION,tempSupportIdx,spanIdx);
            THROW_LBAMA_MSG(INVALID_TS_LOCATION,msg);
         }
      }

      span_start = span_end;
   }

   ATLASSERT(IsEqual(m_SpanEnds.back()+m_LeftOverhang+m_RightOverhang, m_TotalLength));
}

void CAnalysisModel::LayoutSuperstructureMemberNodes(ISuperstructureMembers* pMembers, SuperNodeLocs* pSuperNodeLocs)
{
   CHRException hr;

   // left end of first member   
   InsertSuperSegmentNode(pSuperNodeLocs, -m_LeftOverhang, NULL, nrMemberEnd);

   CollectionIndexType nMembers;
   hr = pMembers->get_Count(&nMembers);
   Float64 loc = -m_LeftOverhang;
   for (CollectionIndexType mbrIdx = 0; mbrIdx < nMembers; mbrIdx++)
   {
      Float64 mbr_length;

      CComPtr<ISuperstructureMember> pmbr;
      hr = pMembers->get_Item(mbrIdx, &pmbr);

      hr = pmbr->get_Length(&mbr_length);

      if (mbr_length <= m_LayoutTolerance)
      {
         THROW_LBAMA(MEMBER_LENGTH_MUST_BE_GT_ZERO);
      }

      // member segments
      // GetMemberSegments returns correct number of segments whether the member is symmetrical
      CComPtr<IFilteredSegmentCollection> pFilteredSegs;
      hr = pmbr->GetMemberSegments(m_Stage, &pFilteredSegs);

      SegmentIndexType nSegments;
      Float64 segment_lengths=0;
      hr = pFilteredSegs->get_Count(&nSegments);

      if (nSegments <= 0)
      {
         USES_CONVERSION;
         LPTSTR bstg = W2T(m_Stage);
         TCHAR str[256];
         ::LoadString( _Module.GetModuleInstance(), IDS_E_NO_SEGMENT_FOR_MEMBER, str, 256);
         TCHAR msg[256];
         int cOut = _stprintf_s( msg, 256, str, mbrIdx, bstg);
         ATLASSERT( cOut < 256 );
         THROW_LBAMA_MSG(NO_SEGMENT_FOR_MEMBER, msg);
      }

      for( SegmentIndexType segmentIdx = 0; segmentIdx < nSegments; segmentIdx++)
      {
         CComPtr<ISegment> segment;
         hr = pFilteredSegs->get_Item(segmentIdx, &segment);

         Float64 segment_length;
         hr = segment->get_Length(&segment_length);

         // segment length could be fractional
         try
         {
            segment_length = GetFracDistance(segment_length, mbr_length, true);
         }
         catch(FracRes&)
         {
            CComBSTR msg =CreateErrorMsg1L(IDS_E_INVALID_SEGMENT_LENGTH, segmentIdx);
            THROW_LBAMA_MSG(INVALID_SEGMENT_LENGTH,msg);
         }


         if (segment_length <= m_LayoutTolerance)
         {
            CComBSTR msg(::CreateErrorMsg1L(IDS_E_SEGMENT_LENGTH_MUST_BE_GT_ZERO, segmentIdx));
            CComBSTR msg2(::CreateErrorMsg1L(IDS_SUPERSTRUCTUREMEMBER_INFO, mbrIdx));
            msg += msg2;
            THROW_LBAMA_MSG(SEGMENT_LENGTH_MUST_BE_GT_ZERO,msg);
         }

         CComPtr<ISegmentCrossSection> SegmentCrossSection;
         hr = segment->get_SegmentCrossSection(&SegmentCrossSection);

         // Check the cross section here, while it's in context for error messaging
         try
         {
            CheckSegmentCrossSection(SegmentCrossSection);
         }
         catch (CComException& re)
         {
            _bstr_t msg1(::CreateErrorMsg2L(IDS_SS_SEGMENT_INFO, mbrIdx, segmentIdx));
            re.AppendToMessage( (TCHAR*)msg1);
            throw re;
         }

         segment_lengths += segment_length;

         if (segmentIdx == nSegments-1)
         {
            // end of the line - make sure we are at member end
            ATLASSERT( IsEqual(segment_lengths, mbr_length) );

            InsertSuperSegmentNode(pSuperNodeLocs, loc+mbr_length, SegmentCrossSection, nrMemberEnd);
         }
         else
         {
            // segments are within this member
            InsertSuperSegmentNode(pSuperNodeLocs, loc+segment_lengths, SegmentCrossSection, nrSegmentEnd);
         }

      }

      loc+= mbr_length;
      m_SuperstructureMemberEnds.push_back(loc);
   }

   ATLASSERT( IsEqual(loc, m_TotalLength-m_LeftOverhang) );
}

bool CAnalysisModel::IsMemberEndReleased(ISuperstructureMember* pMember, Side side)
{
   CHRException hr;

   CComBSTR bstrHingeRemovalStage;
   MemberReleaseType releaseType;
   hr = pMember->GetEndRelease(side, &bstrHingeRemovalStage, &releaseType);

   if (releaseType == mrtNone)
   {
      return false; // not hinged and never will be
   }

   if (bstrHingeRemovalStage.Length() == 0)
   {
      // no removal stage defined - just use release given
      return (releaseType == mrtPinned ? true : false);
   }
   else
   {
      // need to compare our current stage with hinge removal stage
      StageIndexType hingeRemovalStageIdx;
      if ( !m_pStageOrder->GetStageIndex(bstrHingeRemovalStage,&hingeRemovalStageIdx) )
      {
         CComBSTR msg(::CreateErrorMsg1S(IDS_E_INVALID_HINGE_REMOVAL_STAGE, bstrHingeRemovalStage));
         THROW_LBAMA_MSG(INVALID_HINGE_REMOVAL_STAGE,msg);
      }

      StageIndexType stageIdx;
      if ( !m_pStageOrder->GetStageIndex(m_Stage,&stageIdx) )
      {
         THROW_HR(E_FAIL); // this should never happen since stage should already be identified
      }

      // return true if the current stage is before removal stage
      if(stageIdx < hingeRemovalStageIdx)
         return true;
      else
         return false;
   }
}     


void CAnalysisModel::PlaceHinges(ISuperstructureMembers* pMembers, Float64 LeftOverhang, SuperNodeLocs* node_locs)
{
   CHRException hr;

   // superstructure members
   CollectionIndexType nMembers;
   hr = pMembers->get_Count(&nMembers);
   Float64 start_loc = -LeftOverhang;
   for (CollectionIndexType mbrIdx = 0; mbrIdx < nMembers; mbrIdx++)
   {
      CComPtr<ISuperstructureMember> member;
      hr = pMembers->get_Item(mbrIdx, &member);

      Float64 mbr_length;
      hr = member->get_Length(&mbr_length);

      Float64 end_loc = start_loc + mbr_length;

      // check release on right and left sides
      // left first
      if (IsMemberEndReleased(member, ssLeft))
      {
         SuperNodeLoc nodeLocation(start_loc, nrSegmentEnd); // SuperNodeReason has no consequence
         SuperNodeLocIterator found (node_locs->find(nodeLocation));
         if (found != node_locs->end())
         {
            found->SetRelease(mrRightPinned); // pin right side of node
         }
         else
            THROW_HR(E_FAIL); // node not there? This should not happen
      }

      // next look at right end
      if (IsMemberEndReleased(member, ssRight))
      {
         SuperNodeLoc nodeLocation(end_loc, nrSegmentEnd); // SuperNodeReason has no consequence
         SuperNodeLocIterator found( node_locs->find(nodeLocation) );
         if (found != node_locs->end())
         {
            found->SetRelease(mrLeftPinned);
         }
         else
            THROW_HR(E_FAIL); // node not there? This should not happen
      }

      // loop
      start_loc = end_loc;
   }
}


void InsertSuperSegmentNode(SuperNodeLocs* node_locs, Float64 loc, ISegmentCrossSection* pcs, SuperNodeReason reason)
{
   SuperNodeLoc seg_end(loc, reason, pcs);

   std::pair<SuperNodeLocIterator, bool> result(node_locs->insert( seg_end ));

   if (result.second == false)
   {
      // Insert failed, there must already a node there, 
      // It must be a span end. get it and set its cross section;
      SuperNodeLocIterator found = node_locs->find(seg_end);
      if (found != node_locs->end())
      {
         found->Assimilate(seg_end);
      }
      else
      {
         // this should never happen. the insert above failed for an unexpected reason
         THROW_HR(E_FAIL);
      }
   }
}

void CondenseSuperNodeSections(SuperNodeLocs* node_locs, Float64 layoutTolerance)
{
   // walk node list and get rid of nodes that are too close together 
   SuperNodeLocIterator lefty( node_locs->begin());
   SuperNodeLocIterator righty( lefty );
   SuperNodeLocIterator snend( node_locs->end() );
   righty++;
   while(  righty != snend )
   {
      Float64 leftyloc = lefty->GetLoc();
      Float64 rightyloc = righty->GetLoc();
      Float64 diff = rightyloc - leftyloc;
      if (diff <= layoutTolerance)
      {
         // We have two nodes that are too close together - one needs to go
         // Use node type to determine which one to blast
         if ( lefty->IsReason(nrSpanEnd) )
         {
            // span ends are the most important types of nodes - they don't move
            if ( righty->IsReason(nrSpanEnd) || 
                 righty->IsReason(nrTemporarySupport) || 
                 righty->IsReason(nrTemporarySupportLoc) )
            {
               // calling code should block this from ever happening
               THROW_HR(E_FAIL); 
            }
            else if (righty->IsReason(nrMemberEnd) || righty->IsReason(nrSegmentEnd))
            {
               // member end or segment end is just after span end - assimilate it and blast it, 
               lefty->Assimilate(*righty);

               lefty = node_locs->erase(righty);
               righty = lefty;
               righty++;
            }
            else
            {
               // if reason type was not assigned, this is an error
               THROW_HR(E_FAIL); 
            }
         }
         else if ( lefty->IsReason(nrTemporarySupport) || lefty->IsReason(nrTemporarySupportLoc) )
         {
            // temporary support locations don't move
            if (righty->IsReason(nrTemporarySupport) || righty->IsReason(nrTemporarySupportLoc) )
            {
               // two temporary supports too close together
               THROW_LBAMA(TEMPORARY_SUPPORTS_TOO_CLOSE);
            }
            else if ( righty->IsReason(nrSpanEnd) )
            {
               // calling code should block this from ever happening
               THROW_HR(E_FAIL); 
            }
            else if (righty->IsReason(nrMemberEnd) || righty->IsReason(nrSegmentEnd))
            {
               // member end or segment end is just after temporary support location assimilate it and blast it, 
               lefty->Assimilate(*righty);

               lefty = node_locs->erase(righty);
               righty = lefty;
               righty++;
            }
            else
            {
               // if reason type was not assigned, this is an error
               THROW_HR(E_FAIL); 
            }
         }
         else if (lefty->IsReason(nrMemberEnd) )
         {
            // left node is a member end 
            if (righty->IsReason(nrSpanEnd))
            {
               // right node is a span end - blast member end, but extend its section first
               righty->Assimilate(*lefty);

               lefty = node_locs->erase(lefty);
               righty = lefty;
               righty++;
            }
            else if (righty->IsReason(nrMemberEnd))
            {
               // have two member ends within tolerance? this should be blocked by previous code
               ATLASSERT(0);
               lefty = node_locs->erase(righty);
               righty = lefty;
               righty++;
            }
            else if (righty->IsReason(nrSegmentEnd))
            {
               // have two member end to left and segment end within tolerance - this should never 
               // happen as well.
               ATLASSERT(0);
               lefty = node_locs->erase(righty);
               righty = lefty;
               righty++;
            }
            else
            {
               // if reason type was not assigned, this is an error
               THROW_HR(E_FAIL); 
            }
         }
         else if (lefty->IsReason(nrSegmentEnd))
         {
            // left node is a member end 
            if (righty->IsReason(nrSpanEnd) || righty->IsReason(nrMemberEnd))
            {
               // second node is a span or member end - blast segment end, but extend its section first
               righty->Assimilate(*lefty);

               lefty = node_locs->erase(lefty);
               righty = lefty;
               righty++;
            }
            else if (righty->IsReason(nrSegmentEnd))
            {
               // somehow got two segment ends within tolerance - this should never happen
               ATLASSERT(0);
               lefty = node_locs->erase(righty);
               righty = lefty;
               righty++;
            }
            else
            {
               // if reason type was not assigned, this is an error
               THROW_HR(E_FAIL); 
            }
         }
         else
         {
            // if reason type was not assigned, this is an error
            THROW_HR(E_FAIL); 
         }
      }
      else
      {
         lefty = righty;
         righty++;
      }
   }
}

void AssignSectionsToNodes(SuperNodeLocs* node_locs)
{
   // sections have not been assigned to all nodes yet -we need to assign unassigned 
   // nodes to the closest section to the left of a section. The easiest way to do this
   // is to walk the list in reverse.
   SuperNodeLocs::reverse_iterator righty( node_locs->rbegin() );
   SuperNodeLocs::reverse_iterator lefty( righty );
   lefty++;

   // have to be able to get the ball rolling here. If the right-most node in the list
   // doesn't have a valid pointer, code before this point has failed.
   CComPtr<ISegmentCrossSection> SegmentCrossSection;
   righty->GetSegmentCrossSection(&SegmentCrossSection);
   if (SegmentCrossSection == NULL)
   {
      THROW_HR(E_FAIL);
   }

   while( lefty != node_locs->rend() )
   {
      CComPtr<ISegmentCrossSection> leftSegmentCrossSection;
      lefty->GetSegmentCrossSection(&leftSegmentCrossSection);
      if (leftSegmentCrossSection == NULL)
      {
         CComPtr<ISegmentCrossSection> rightSegmentCrossSection;
         righty->GetSegmentCrossSection(&rightSegmentCrossSection);
         lefty->SetSegmentCrossSection(rightSegmentCrossSection);
      }

      righty = lefty;
      lefty++;
   }
}

void CondenseSupportNodeSections(SubNodeLocs* nodeLocs, Float64 layoutTolerance)
{
   // nothing to condense for zero length supports
   if (nodeLocs->size()<=1)
      return;

   // layout for support nodes is straightforward. The only chance for a tolerancing
   // problem is on the last (top) node.
   SubNodeLocs::reverse_iterator righty( nodeLocs->rbegin() );
   SubNodeLocs::reverse_iterator lefty (righty);
   lefty++;

   Float64 dist = righty->Distance(*lefty);
   if (dist<layoutTolerance)
   {
      righty->Assimilate(*lefty);
      nodeLocs->erase(*lefty);   // have to use key - can't erase using reverse_iterator
   }
  
#if defined _DEBUG
   CComPtr<ISegmentCrossSection> rightSegmentCrossSection;
   righty->GetSegmentCrossSection(&rightSegmentCrossSection);
   ATLASSERT(rightSegmentCrossSection != NULL);
#endif
}


bool CAnalysisModel::IsTempSupportInStage(ITemporarySupport* pTempSupport)
{
   CHRException hr;
   CComBSTR bstrTempSupportRemovalStage;

   hr = pTempSupport->get_StageRemoved(&bstrTempSupportRemovalStage);

   if (bstrTempSupportRemovalStage.Length() == 0)
   {
      return true;
   }
   else
   {
      // get orders of this stage and stage where support is removed
      StageIndexType tempSupportRemovalStageIdx;
      if (!m_pStageOrder->GetStageIndex(bstrTempSupportRemovalStage,&tempSupportRemovalStageIdx))
      {
         CComBSTR msg(::CreateErrorMsg1S(IDS_E_NO_REM_STAGE_FOR_TS, bstrTempSupportRemovalStage));
         THROW_LBAMA_MSG(NO_REM_STAGE_FOR_TS,msg);
      }

      StageIndexType stageIdx;
      if ( !m_pStageOrder->GetStageIndex(m_Stage,&stageIdx) )
      {
         THROW_HR(E_FAIL); // this should never happen since stage should already be identified
      }

      // can finally make determination
      if (stageIdx < tempSupportRemovalStageIdx)
         return true;
      else
         return false;
   }
}

void CheckSegmentCrossSection(ISegmentCrossSection* pSegmentCrossSection)
{
   // function to check the validity of a cross section for use in a model
   CHRException hr;
   Float64 d;

   hr = pSegmentCrossSection->get_EAForce(&d);
   if (d<=0.0)
   {
      CComBSTR msg = CreateXsErrorMsg(_T("EAForce"));
      THROW_LBAMA_MSG(INVALID_SECTION_PROP,msg);
   }

   hr = pSegmentCrossSection->get_EIForce(&d);
   if (d<=0.0)
   {
      CComBSTR msg = CreateXsErrorMsg(_T("EIForce"));
      THROW_LBAMA_MSG(INVALID_SECTION_PROP,msg);
   }

   hr = pSegmentCrossSection->get_EADefl(&d);
   if (d<=0.0)
   {
      CComBSTR msg = CreateXsErrorMsg(_T("EADefl"));
      THROW_LBAMA_MSG(INVALID_SECTION_PROP,msg);
   }

   hr = pSegmentCrossSection->get_EIDefl(&d);
   if (d<=0.0)
   {
      CComBSTR msg = CreateXsErrorMsg(_T("EIDefl"));
      THROW_LBAMA_MSG(INVALID_SECTION_PROP,msg);
   }

   hr = pSegmentCrossSection->get_Depth(&d);
   if (d<=0.0)
   {
      CComBSTR msg = CreateXsErrorMsg(_T("Depth"));
      THROW_LBAMA_MSG(INVALID_SECTION_PROP,msg);
   }

   hr = pSegmentCrossSection->get_ThermalCoeff(&d);
   if (d<0.0)
   {
      CComBSTR msg = CreateXsErrorMsg(_T("Thermal Coefficient"));
      THROW_LBAMA_MSG(INVALID_SECTION_PROP,msg);
   }
}

CComBSTR CreateXsErrorMsg(LPCTSTR proptype)
{
   CComBSTR pt(proptype);
   return ::CreateErrorMsg1S(IDS_E_INVALID_SECTION_PROP, pt);
}

void CAnalysisModel::LayoutTemporarySupport(SpanIndexType spanIdx, Float64 tempSupportLocation, ITemporarySupport* pSupport, SubNodeLocs* pNodeLocs)
{
   LayoutTemporarySupportNodes( spanIdx, tempSupportLocation, pSupport, pNodeLocs );
   // tolerance nodes
   CondenseSupportNodeSections(pNodeLocs, m_LayoutTolerance);
}

void CAnalysisModel::LayoutTemporarySupportNodes( SpanIndexType spanIdx, Float64 tempSupportLocation, ITemporarySupport* pSupport, SubNodeLocs* pNodeLocs)
{
   CHRException hr;
   
   // get connectivity
   BoundaryConditionType boundaryCondition;
   hr = pSupport->get_BoundaryCondition(&boundaryCondition);

   pNodeLocs->m_BC = boundaryCondition;

   // top release
   VARIANT_BOOL bTopRelease;
   hr = pSupport->get_TopRelease(&bTopRelease);

   pNodeLocs->m_TopRelease = bTopRelease;

   SupportIDType tempSupportID;
   hr = pSupport->get_ID(&tempSupportID);

   pNodeLocs->m_LbamTemporarySupportID = tempSupportID;

   // support length
   Float64 support_length;
   hr = pSupport->get_Length(&support_length);

   Float64 support_offset;
   hr = pSupport->get_BottomOffset(&support_offset);

   if ( (0 < support_length && support_length <= fabs(support_offset)) ||
        (support_length == 0 &&  support_offset != 0) )
   {
      CComBSTR msg = ::CreateErrorMsg2L(IDS_E_TEMPSUPPORT_OFFSET_GT_LENGTH, tempSupportID, spanIdx);
      THROW_LBAMA_MSG(TEMPSUPPORT_OFFSET_GT_LENGTH,msg);
   }

   // compute locations of top and bottom nodes
   XyLoc top(tempSupportLocation, 0.0);

   // add top node to the node list. 
   // This is all we need to do for zero-length supports
   pNodeLocs->insert(  SubNodeLoc(top.m_X, top.m_Y, sbnrSupportEnd) );

   if (0.0 < support_length)
   {
      if (support_length <= m_LayoutTolerance)
      {
         CComBSTR msg(::CreateErrorMsg2L(IDS_E_TEMPSUPPORT_LENGTH_MUST_BE_GT_ZERO, tempSupportID, spanIdx));
         THROW_LBAMA_MSG(TEMPSUPPORT_LENGTH_MUST_BE_GT_ZERO,msg);
      }

      Float64 support_height = sqrt( support_length*support_length - support_offset*support_offset);
      XyLoc bottom( top.m_X+support_offset, -support_height );

      // Add bottom node
      pNodeLocs->insert(  SubNodeLoc(bottom.m_X, bottom.m_Y, sbnrSupportEnd) );

      // get segments along support - starts from bottom to top
      CComPtr<IFilteredSegmentCollection> pFilteredSegs;
      hr = pSupport->GetMemberSegments(m_Stage, &pFilteredSegs);

      try
      {
         LayoutSupportSegments(m_Stage, pFilteredSegs, bottom, top, support_length, m_LayoutTolerance, pNodeLocs);
      }
      catch(CComException& re)
      {
         // add some more info to error message
         _bstr_t msg(::CreateErrorMsg2L(IDS_TEMPSUPPORT_INFO, tempSupportID, spanIdx));
         re.AppendToMessage((TCHAR*)msg);
         throw re;
      }
   }
}


void CAnalysisModel::LayoutSupport( SupportIDType supportID, ISupports* pSupports, SubNodeLocs* pNodeLocs)
{
   LayoutSupportNodes( supportID, pSupports, pNodeLocs );
   // tolerance nodes
   CondenseSupportNodeSections(pNodeLocs, m_LayoutTolerance);
}

void CAnalysisModel::LayoutSupportNodes( SupportIDType supportID, ISupports* pSupports, SubNodeLocs* pNodeLocs)
{
   CHRException hr;
   
   CComPtr<ISupport> support;
   hr = pSupports->get_Item(supportID, &support);

   // get BoundaryCondition
   BoundaryConditionType boundaryCondition;
   hr = support->get_BoundaryCondition(&boundaryCondition);

   pNodeLocs->m_BC = boundaryCondition;

   // top release
   VARIANT_BOOL bTopRelease;
   hr = support->get_TopRelease(&bTopRelease);

   pNodeLocs->m_TopRelease = bTopRelease;

   // support length
   Float64 support_length;
   hr = support->get_Length(&support_length);

   if (0.0 < support_length && boundaryCondition == bcRoller && bTopRelease == VARIANT_TRUE)
   {
      // we have roller skates with a pin above - support is not stable
      CComBSTR msg(::CreateErrorMsg1L(IDS_E_SUPPORT_ROLLER_RELEASE, supportID));
      THROW_LBAMA_MSG(SUPPORT_ROLLER_RELEASE,msg);
   }

   // compute locations of top and bottom nodes
   Float64 xtop = 0<supportID ? m_SpanEnds[supportID-1] : 0.0;
   XyLoc top(xtop, 0.0);

   // add top node to the node list. 
   // This is all we need to do for zero-length supports
   pNodeLocs->insert(  SubNodeLoc(top.m_X, top.m_Y, sbnrSupportEnd) );

   if (0.0 < support_length)
   {
      if (support_length <=m_LayoutTolerance)
      {
         CComBSTR msg(::CreateErrorMsg1L(IDS_E_SUPPORT_LENGTH_MUST_BE_GT_ZERO, supportID));
         THROW_LBAMA_MSG(SUPPORT_LENGTH_MUST_BE_GT_ZERO,msg);
      }

      Float64 support_offset;
      hr = support->get_BottomOffset(&support_offset);

      if (support_length <= fabs(support_offset))
      {
         CComBSTR msg = ::CreateErrorMsg1L(IDS_E_SUPPORT_OFFSET_GT_LENGTH, supportID);
         THROW_LBAMA_MSG(SUPPORT_OFFSET_GT_LENGTH,msg);
      }

      Float64 support_height = sqrt( support_length*support_length - support_offset*support_offset);
      XyLoc bottom( xtop+support_offset, -support_height );

      // Add bottom node
      pNodeLocs->insert(  SubNodeLoc(bottom.m_X, bottom.m_Y, sbnrSupportEnd) );

      // get segments along support - starts from bottom to top
      CComPtr<IFilteredSegmentCollection> pFilteredSegs;
      hr = support->GetMemberSegments(m_Stage, &pFilteredSegs);

      try
      {
         LayoutSupportSegments(m_Stage, pFilteredSegs, bottom, top, support_length, m_LayoutTolerance, pNodeLocs);
      }
      catch(CComException& re)
      {
         // add some more info to error message
         _bstr_t msg(::CreateErrorMsg1L(IDS_SUPPORT_INFO, supportID));
         re.AppendToMessage((TCHAR*)msg);
         throw re;
      }
   }
}


void LayoutSupportSegments(BSTR stage, IFilteredSegmentCollection* pFilteredSegs, const XyLoc& bottom, const XyLoc& top, Float64 supportLength, Float64 layoutTolerance, SubNodeLocs* pNodeLocs)
{
   CHRException hr;
   SegmentIndexType segment_cnt;
   Float64 segment_lengths=0;
   hr = pFilteredSegs->get_Count(&segment_cnt);

   if (segment_cnt <= 0)
   {
      CComBSTR msg(::CreateErrorMsg1S(IDS_E_NO_SEGMENT_FOR_SUPPORT, stage));
      THROW_LBAMA_MSG(NO_SEGMENT_FOR_SUPPORT, msg);
   }

   for( SegmentIndexType iseg=0; iseg<segment_cnt; iseg++)
   {
      CComPtr<ISegment> psegment;
      hr = pFilteredSegs->get_Item(iseg, &psegment);

      Float64 segment_length;
      hr = psegment->get_Length(&segment_length);

      // segment length could be fractional
      try
      {
         segment_length = GetFracDistance(segment_length, supportLength, true);
      }
      catch(FracRes&)
      {
         CComBSTR msg =CreateErrorMsg1L(IDS_E_INVALID_SEGMENT_LENGTH, iseg);
         THROW_LBAMA_MSG(INVALID_SEGMENT_LENGTH,msg);
      }

      if (segment_length <=layoutTolerance)
      {
         CComBSTR msg(::CreateErrorMsg1L(IDS_E_SEGMENT_LENGTH_MUST_BE_GT_ZERO, iseg));
         THROW_LBAMA_MSG(SEGMENT_LENGTH_MUST_BE_GT_ZERO,msg);
      }

      CComPtr<ISegmentCrossSection> pcs;
      hr = psegment->get_SegmentCrossSection(&pcs);

      // Check the cross section here, while it's in context for error messaging
      try
      {
         CheckSegmentCrossSection(pcs);
      }
      catch (CComException& re)
      {
         _bstr_t msg1(::CreateErrorMsg1L(IDS_SEGMENT_INFO, iseg));
         re.AppendToMessage( (TCHAR*)msg1);
         throw re;
      }

      segment_lengths += segment_length;

      // compute location of intermediate node
      XyLoc int_loc;
      ComputeSubNodeLocation(bottom, top, segment_lengths, supportLength, &int_loc);

      if (iseg==segment_cnt-1)
         // end of the line - make sure we are at member end
         ATLASSERT( IsEqual(segment_lengths, supportLength) );

      // segments are within this member
      InsertSubSegmentNode(pNodeLocs, int_loc.m_X, int_loc.m_Y, pcs, sbnrSegmentEnd);
   }
}


void InsertSubSegmentNode(SubNodeLocs* node_locs, Float64 xloc, Float64 yloc, ISegmentCrossSection* pcs, SubNodeReason reason)
{
   SubNodeLoc seg_end(xloc,  yloc, reason, pcs);

   std::pair<SubNodeLocIterator, bool> itst( node_locs->insert(seg_end) );

   if (itst.second == false)
   {
      // Insert failed, there must already a node there, 
      // It must be a support end. get it and set its cross section;
      SubNodeLocIterator fnd( node_locs->find(seg_end) );
      if (fnd != node_locs->end())
      {
         ATLASSERT(fnd->IsReason(sbnrSupportEnd));
         fnd->Assimilate(seg_end);
      }
      else
      {
         // this should never happen. An insert in the call stack above failed for an unexpected reason
         THROW_HR(E_FAIL);
      }
   }
}


void CAnalysisModel::SaveModel(IStructuredSave2* pSave)
{
   ATLASSERT(pSave!=NULL);
   ATLASSERT(m_pFem2d!=NULL);

   // get interface for structuredstorage
   CHRException hr;
   CComPtr<IStructuredStorage2> piss;
   hr = m_pFem2d->QueryInterface(&piss);

   // save
   hr = piss->Save( pSave );
}

//////////// Influence Load-related stuff
void CAnalysisModel::ClearInfluenceLoads()
{
   // know that all influence loads have negative ids starting from INFLUENCE_LC and decreasing.
   // first build list of loads to be removed
   std::vector<LoadCaseIDType> remove_list;
   CComPtr<IFem2dLoadingCollection> fem_loadings;
   m_pFem2d->get_Loadings(&fem_loadings);

   CollectionIndexType nLoadings;
   fem_loadings->get_Count(&nLoadings);

   for (CollectionIndexType loadingIdx = 0; loadingIdx < nLoadings; loadingIdx++)
   {
      CComPtr<IFem2dLoading> fem_loading;
      fem_loadings->get_Item(loadingIdx,&fem_loading);

      LoadCaseIDType femLoadCaseID;
      fem_loading->get_ID(&femLoadCaseID);

      if (femLoadCaseID <= INFLUENCE_LC)
      {
         remove_list.push_back(femLoadCaseID);
      }
   }

   // then do removal
   std::vector<LoadCaseIDType>::iterator iter( remove_list.begin() );
   std::vector<LoadCaseIDType>::iterator iterend( remove_list.end() );
   for (; iter != iterend; iter++)
   {
      LoadCaseIDType femLoadCaseID = *iter;
      LoadCaseIDType id;
      fem_loadings->Remove(femLoadCaseID, atID,&id);
      ATLASSERT(id == femLoadCaseID);
   }
}

void CAnalysisModel::GenerateInfluenceLoads()
{
   ATLASSERT(m_pLBAMModel!=NULL);
   ATLASSERT(m_pFem2d!=NULL);

   m_InfluenceLoadSet.clear();

   // first build sorted set of influence locations
   GenerateInfluenceLoadLocations();

   // if there are no influence load locations - there is a problem
   if (m_InfluenceLoadSet.empty())
   {
      THROW_LBAMA(NO_INFLUENCE_LOCATIONS);
   }

   CComPtr<IFem2dLoadingCollection> fem_loadings;
   m_pFem2d->get_Loadings(&fem_loadings);

   // assign fem load case number to each load and,
   // apply unit point load for loading at location
//   ATLTRACE(_T("Influence Load Generation"));
   LoadCaseIDType fem_lc = INFLUENCE_LC;
   InfluenceLoadSetIterator it( m_InfluenceLoadSet.begin() );
   InfluenceLoadSetIterator itend( m_InfluenceLoadSet.end() );
   for (; it!=itend; it++)
   {
      InfluenceLoadLocation& infl_locn = *it;
      infl_locn.m_FemLoadCaseID = fem_lc;

      // create a new loading in the fem model
      CComPtr<IFem2dLoading> fem_loading;
      fem_loadings->Create(fem_lc,&fem_loading);

      // apply joint load
      try
      {
         CComPtr<IFem2dPointLoadCollection> fem_point_loads;
         fem_loading->get_PointLoads(&fem_point_loads);

         CComPtr<IFem2dPointLoad> pointLoad;
         fem_point_loads->Create(fem_lc, infl_locn.m_FemMemberID, infl_locn.m_FemMemberLoc, 0.0, -1.0, 0.0, lotGlobal, &pointLoad);
      }
      catch(_com_error ce)
      {
         THROW_LBAMA(POINT_LOAD_UNKNOWN);
      }

//      ATLTRACE(_T("member %d, mbrLoc = %f, globalLoc=%f, femLc=%d\n"), infl_locn.m_FemMemberId, infl_locn.m_FemMemberLoc, infl_locn.m_GlobalX, infl_locn.m_FemLcId );

      fem_lc--;
   }

//   ATLTRACE(_T("Influence Load Generation - done"));
}

void CAnalysisModel::GenerateInfluenceLoadLocations()
{
//   ATLTRACE(_T("Generate Influence Load Locations"));

   // Get locations of all superstructure pois (internal and external) and add them to the load locations
   PoiIDType poiID;
   try
   {
      PoiMapIterator ipoi(m_PoiMap.begin());
      PoiMapIterator ipoiend(m_PoiMap.end());
      for (; ipoi!=ipoiend; ipoi++)
      {
         PoiMap& info = *(*ipoi);

         poiID                     = info.GetLBAMPoiID();
         MemberType lbamMemberType = info.GetLBAMMemberType();
         MemberIDType lbamMemberID = info.GetLBAMMemberID();
         Float64 lbamPoiLocation   = info.GetLBAMPoiLocation();

         if (lbamMemberType == mtSpan || lbamMemberType == mtSuperstructureMember)
         {
            ComputeInfluenceLoadLocation(lbamMemberType, lbamMemberID, lbamPoiLocation, m_InfluenceLoadSet);
         }
      }
   }
   catch(CComException& re)
   {
      // location not found. add some context and rethrow
      _bstr_t msg =CreateErrorMsg1L(IDS_POI_INFLUENCELOCATION,poiID);
      re.AppendToMessage((TCHAR*)msg);
      throw;
   }

   // finally assign left and rightness to loads at equal locations
   CollectionIndexType nInfluenceLoads = m_InfluenceLoadSet.size();
   if (2 < nInfluenceLoads)
   {
#if defined (_DEBUG)
      Float64 last_loc;
#endif
      bool last_matched=false;
      InfluenceLoadSetIterator it2(m_InfluenceLoadSet.begin());
      InfluenceLoadSetIterator it1(it2++);
      InfluenceLoadSetIterator itend(m_InfluenceLoadSet.end());
      while( it2!=itend)
      {
         if (it1->m_GlobalX == it2->m_GlobalX)
         {
            it1->m_LocationType = iflDualLeft;
            it2->m_LocationType = iflDualRight;
         }

         // some debug code here to check that we don't have three or more of the same location
#if defined (_DEBUG)
         if (it1->m_GlobalX == it2->m_GlobalX)
         {
            if (last_matched)
            {
               ATLASSERT(0); // have three points at the same location - this is bad form and indicates an inefficient influence line
            }
            last_matched = true;
            last_loc = it2->m_GlobalX;
         }
         else
         {
            last_matched = false;
         }
#endif
         // loop
         it1++;
         it2++;
      }
   }

#if defined(_DEBUG_LOGGING)
   for (InfluenceLoadSetIterator it=m_InfluenceLoadSet.begin(); it!=m_InfluenceLoadSet.end(); it++)
   {
      InfluenceLoadLocation& ifl = *it;
      LPCTSTR side[] = {"Single","Left  ","Right "};
      ATLTRACE(_T("Member Location Global %f, %s, ID = %dMbrLoc = %f, Lc = %d\n"), ifl.m_GlobalX, side[ifl.m_LocationType], ifl.m_FemMemberId, ifl.m_FemMemberLoc, ifl.m_FemLcId);
   }
#endif

//   ATLTRACE(_T("Influence Load Locations - done"));
}

void CAnalysisModel::ComputeInfluenceLoadLocation(MemberType lbmbrType, MemberIDType lbamMemberID, Float64 lbmbrLoc, InfluenceLoadSet& influenceLoadSet )
{
   CHRException hr;

   // get location in global coords
   Float64 xloc, yloc;
   hr = m_pLBAMModel->ComputeLocation(lbamMemberID, lbmbrType, lbmbrLoc, &xloc, &yloc);

   ATLASSERT(yloc==0.0); // this should be blocked by IInfluenceLocations - no supports allowed

   // get fem location
   MemberLocationType mbl_type;
   MemberIDType       fem_id;
   Float64            fem_loc;

   if (lbmbrType==mtSpan)
   {
      GetFemMemberLocationAlongSpan(lbamMemberID, lbmbrLoc, &mbl_type, &fem_id, &fem_loc);
   }
   else if (lbmbrType==mtSuperstructureMember)
   {
      GetFemMemberLocationAlongSSM(lbamMemberID, lbmbrLoc, &mbl_type, &fem_id, &fem_loc);
   }
   else
   {
      ATLASSERT(0);
      THROW_HR(E_FAIL);
   }

   ATLASSERT(mbl_type!=mltNotFound);

   influenceLoadSet.insert( InfluenceLoadLocation( xloc, fem_id, fem_loc) );

   if (mbl_type==mltStraddle)
   {
      // add load at both sides of straddle points
      influenceLoadSet.insert( InfluenceLoadLocation( xloc, fem_id+1, 0.0) );
   }
}

void CAnalysisModel::GenerateContraflexureLoads()
{
   // contraflexure load is a unit uniform vertical load applied along entire superstructure
   // create a new loading in the fem model
   CComPtr<IFem2dLoadingCollection> fem_loadings;
   m_pFem2d->get_Loadings(&fem_loadings);

   CComPtr<IFem2dLoading> fem_loading;
   fem_loadings->Create(CONTRAFLEXURE_LC,&fem_loading);

   CComPtr<IFem2dDistributedLoadCollection> fem_distr_loads;
   fem_loading->get_DistributedLoads(&fem_distr_loads);

   // loop over all superstructure member elements and apply unit uniform load
   LoadIDType loadID = 0;
   ElementLayoutGroupIterator its(m_SuperstructureMemberElements.begin());
   ElementLayoutGroupIterator itsend(m_SuperstructureMemberElements.end());
   for (; its!=itsend; its++)
   {
      ElementLayoutVec& vec = *its;

      ElementLayoutVecIterator itv(vec.begin());
      ElementLayoutVecIterator itvend(vec.end());
      for (; itv!=itvend; itv++)
      {
         ElementLayout& lo = *itv;
         MemberIDType mbr_id = lo.m_FemMemberID;

         // finally have the information - create a unit uniform load
         CComPtr<IFem2dDistributedLoad> distLoad;
         fem_distr_loads->Create(loadID,mbr_id, loadDirFy, 0.0, -1.0, -1.0, -1.0,lotGlobal,&distLoad);
         loadID++;
      }
   }
}

void CAnalysisModel::ClearContraflexureLoads()
{
   CComPtr<IFem2dLoadingCollection> fem_loadings;
   m_pFem2d->get_Loadings(&fem_loadings);

   CComPtr<IFem2dLoading> fem_loading;
   fem_loadings->Find(CONTRAFLEXURE_LC,&fem_loading);

   if (fem_loading != NULL)
   {
      LoadCaseIDType id;
      fem_loadings->Remove(CONTRAFLEXURE_LC, atID, &id);
   }

   m_ContraflexureLocations->Clear();
}


void CAnalysisModel::GenerateContraflexurePOIs()
{
   CHRException hr;

   m_ContraflexurePOIs.clear();

   CollectionIndexType cf_size;
   hr = m_ContraflexureLocations->get_Count(&cf_size);
   if ( cf_size < 1 )
      ComputeContraflexureLocations();

   SortedPoiMapTracker poi_tracker(m_PoiMap, true);

   // have cf locations, now generate pois at them
   hr = m_ContraflexureLocations->get_Count(&cf_size);

   if (0 < cf_size)
   {
      for (CollectionIndexType icf=0; icf<cf_size; icf++)
      {
         Float64 xloc;
         hr = m_ContraflexureLocations->get_Item(icf, &xloc);
         CollectionIndexType ssm_idx;
         Float64 ssm_loc;
         if (GetSuperstructureMemberForGlobalX(xloc, &ssm_idx, &ssm_loc))
         {
            PoiIDType id_at_loc;
            if ( !poi_tracker.IsPoiAtLocation(mtSuperstructureMember, ssm_idx, xloc, &id_at_loc) )
            {
               // Need to create an internally-generated poi on the cantilever
               m_LastInternalPoiID--;
               CreateSsmPOI(m_LastInternalPoiID, ssm_idx, ssm_loc);

               m_ContraflexurePOIs.push_back(m_LastInternalPoiID);
            }
            else
            {
               // a poi is already there - add its id
               m_ContraflexurePOIs.push_back(id_at_loc);
            }
         }
         else
         {
            // location not found on superstructure
            ATLASSERT(0);
            THROW_HR(E_FAIL);
         }
      }
   }
}

void CAnalysisModel::GetContraflexureLocations(IDblArray* *locations)
{
   // have locations just copy them into safearray
   CHRException hr;
   hr = m_ContraflexureLocations->Clone(locations);
}


void CAnalysisModel::IsPOIInContraflexureZone(PoiIDType poiID, InZoneType* isInZone)
{
   CHRException hr;

   // first check to see if this poi is on an edge of a cf zone
   CollectionIndexType cfp_size = m_ContraflexurePOIs.size();
   ATLASSERT(cfp_size%2==0);
   for (CollectionIndexType icf=0; icf<cfp_size; icf++)
   {
      PoiIDType id = m_ContraflexurePOIs[icf];
      if (id==poiID)
      {
         // our poi is on the border now figure out which side of the zone it's on
         if (icf%2==0)
         {
            *isInZone = izLeftEdge;
         }
         else
         {
            *isInZone = izRightEdge;
         }

         return;
      }
   }

   // get poi information
   MemberType mtype;
   MemberIDType member_id;
   Float64 mbr_x, glob_x;
   HRESULT hrr = this->GetPoiInfoPrv(poiID, &mtype, &member_id, &mbr_x, &glob_x);
   if (FAILED(hrr))
   {
      ATLASSERT(0);
      CComBSTR msg = ::CreateErrorMsg1L(IDS_E_POI_NOT_FOUND, poiID);
      THROW_LBAMA_MSG(POI_NOT_FOUND,msg);
   }

   // cf locations are only on superstructure
   if (mtype==mtSpan || mtype==mtSuperstructureMember)
   {
      CollectionIndexType cf_size;
      hr = m_ContraflexureLocations->get_Count(&cf_size);
      if( cf_size==0)
      {
         // no zones - no need to look
         *isInZone = izOutside;
      }
      else
      {
         ATLASSERT(cf_size%2==0); // need two sides to define each zone

         // we have zones and we have a poi on the ss. find the zone
         CollectionIndexType cnt = cf_size/2;
         for (CollectionIndexType izone=0; izone<cnt; izone++)
         {
            CollectionIndexType left_idx  = izone*2;
            CollectionIndexType right_idx = left_idx+1;

            Float64 left_edge;
            Float64 right_edge;
            hr = m_ContraflexureLocations->get_Item(left_idx, &left_edge);
            hr = m_ContraflexureLocations->get_Item(right_idx, &right_edge);

            if (IsEqual(glob_x, left_edge))
            {
                *isInZone = izLeftEdge;
                return;
            }
            else if (IsEqual(glob_x, right_edge))
            {
                *isInZone = izRightEdge;
                return;
            }
            else if ( left_edge<glob_x && glob_x<right_edge)
            {
                *isInZone = izInside;
                return;
            }
            else if(left_edge>glob_x)
            {
               // sorted cf zones are now past our location - no sense in looping further. we are out
                break;
            }
         }
      }
   }

   // poi is not in zone
   *isInZone = izOutside;
}


void CAnalysisModel::GetContraflexureForce( ForceEffectType effect, CInfluenceLine* results )
{
   // Sort all pois (including internally generated ones) in superstructure by their global X location
   SortedPoiMapTracker poi_tracker(m_PoiMap, true);

   CollectionIndexType size = poi_tracker.size();
   results->Reserve(size*12/10);    // assume 20% are dual-valued

   // set processing type for influence line so it retains raw values
   results->SetProcessingType(CInfluenceLine::iptRaw);

   SortedPoiMapTracker::iterator it(poi_tracker.begin());
   SortedPoiMapTracker::iterator itend(poi_tracker.end());
   for (; it!=itend; it++)
   {
      PoiMap& info = *(*it);

      Float64 fx_left, fx_right, fy_left, fy_right, mz_left, mz_right;
      info.GetForce(CONTRAFLEXURE_LC, m_pFem2d, roMember, &fx_left, &fy_left, &mz_left, &fx_right, &fy_right, &mz_right);

      Float64 val_left, val_right;
      switch(effect)
      {
      case fetFx:
         val_left  =  fx_left;
         val_right = -fx_right;  // note sign flips
         break;
      case fetFy:
         val_left  =  fy_left;
         val_right = -fy_right;
         break;
      case fetMz:
         val_left  =  mz_left;
         val_right = -mz_right;
         break;
      default:
         ATLASSERT(0);
      };

      results->Add( iflSingle, info.GetLocation(), val_left);

      if (!IsEqual(mz_left, -mz_right ) ) // remember, the whole purpose of contraflexure is to get moment response
      {
         results->Add( iflSingle, info.GetLocation(), val_right);
      }
   }
}


void CAnalysisModel::IsPOIInNegativeLiveLoadMomentZone(PoiIDType poiID, InZoneType* isInZone)
{
   // first check if we are in normal contraflexure zone
   InZoneType lzone;
   this->IsPOIInContraflexureZone(poiID, &lzone);

   // assume that contraflexure zone controls
   *isInZone = lzone;

   // unless POI lies within or on the edge of a zone
   if (lzone!=izOutside)
   {
      // we are in a zone. the only rule that we need to check is if the poi is in the outside
      // half of an exterior span and there is no cantilever on that span

      // get global x of poi
      MemberType mtype;
      MemberIDType member_id;
      Float64 glob_x;
      HRESULT hrr = this->GetSsPoiInfo(poiID, &mtype, &member_id, &glob_x);
      if (FAILED(hrr))
      {
         ATLASSERT(0);
         CComBSTR msg = ::CreateErrorMsg1L(IDS_E_POI_NOT_FOUND, poiID);
         THROW_LBAMA_MSG(POI_NOT_FOUND,msg);
      }

      // check left exterior span
      if (m_LeftOverhang<m_LayoutTolerance)
      {
         Float64 loc = *(m_AllSpanEnds.begin());
         loc /= 2.0; // middle of first span
         if (glob_x==loc)
         {
            // POI is at middle of first span
            *isInZone=izLeftEdge;
            return;
         }
         else if (glob_x<loc)
         {
            // POI is in left end of first span - it's not applicable
            *isInZone=izOutside;
            return;
         }
      }

      // check right exterior span
      if (m_RightOverhang<m_LayoutTolerance)
      {
         std::set<Float64>::iterator it(m_AllSpanEnds.end());
         Float64 end, lst;
         if ( m_AllSpanEnds.size() == 1 )
         {
            end = *(m_AllSpanEnds.begin());
            lst = end;
         }
         else
         {
            end = *(--it);
            lst = *(--it);
         }

         Float64 loc = (end+lst)/2.0;  // middle of last span
         if (glob_x==loc)
         {
            // POI is at middle of last span
            *isInZone=izRightEdge;
            return;
         }
         else if (glob_x>loc)
         {
            // POI is in right end of last span - it's not applicable
            *isInZone=izOutside;
            return;
         }
      }
   }
}

void CAnalysisModel::GetNegativeMomentRegions(IDblArray* *locations)
{
   CHRException hr;

   // start off with our raw contraflexure locations and modify if cf points are in outer spans
   CComPtr<IDblArray> locs;
   hr = m_ContraflexureLocations->Clone(&locs);

   SpanIndexType num_spans = m_AllSpanEnds.size();
   CollectionIndexType num_locs;
   hr = locs->get_Count(&num_locs);
   if (num_locs>0 && num_spans>2)
   {
      // we don't modify cf points if there is an overhang
      // check left exterior span
      if (m_LeftOverhang<m_LayoutTolerance)
      {
         Float64 left_cf;
         hr = locs->get_Item(0, &left_cf);
         Float64 ms = *(m_AllSpanEnds.begin());
         ms /= 2.0; // middle of first span

         if (left_cf<ms)
         {
            // negative moment region cannot extend before middle of first span
            hr = locs->Insert(0, ms);
         }
      }

      // check right exterior span
      if (m_RightOverhang<m_LayoutTolerance)
      {
         Float64 right_cf;
         hr = locs->get_Item(num_locs-1, &right_cf);

         std::set<Float64>::iterator it(m_AllSpanEnds.end());
         Float64 end = *(--it);
         Float64 lst = *(--it);
         Float64 ms = (end+lst)/2.0;  // middle of last span

         if (right_cf>ms)
         {
            // negative moment region cannot extend past middle of last span
            hr = locs->Insert(num_locs-1, ms);
         }
      }
   }

   *locations = locs.Detach();
}


void CAnalysisModel::ComputeContraflexureLocations()
{
   CHRException hr;
   CollectionIndexType cf_size;
   hr = m_ContraflexureLocations->get_Count(&cf_size);

   ATLASSERT( cf_size<1 ); // should never get here if we have results already

   // get moment response for contraflexure load case
   CComObject<CInfluenceLine>* response;
   hr = CComObject<CInfluenceLine>::CreateInstance(&response);
   CComPtr<IInfluenceLine> iholder(response); // ref cnt
   GetContraflexureForce( fetMz,  response );

   CollectionIndexType size;
   hr = response->get_Count(ilsBoth, &size);
   if (size < 2)
   {
      ATLASSERT(0); // should be a lot more pois than this
      return;
   }

   // contraflexure locations are same as negative regions of influence line
   CComPtr<IDblArray> array;
   hr = response->ComputeNonZeroRegions(ilsNegative, &array);

   m_ContraflexureLocations = array;

   hr = m_ContraflexureLocations->get_Count(&cf_size);

   // should always have an even number of locations to define zone
#if defined (_DEBUG_LOGGING)
   if (cf_size<1)
   {
      ATLTRACE(_T("Zero Contraflexure Locations - Stage %S \n"), m_Stage);
   }
   else
   {
      ATLASSERT(cf_size%2 == 0);
      ATLTRACE(_T("Contraflexure Locations - Stage %S \n"), m_Stage);
      for (long idf=0; idf<cf_size; idf++)
      {
         Float64 loc;
         hr = m_ContraflexureLocations->get_Item(idf, &loc);
         ATLTRACE(_T("   %d  - %f \n"),idf, loc);
      }
   }
#endif
}


void CAnalysisModel::GetInfluenceLines(PoiIDType poiID,
                                       ResultsOrientation forceOrientation,  Float64 forceZeroTolerance, Float64 deflZeroTolerance, 
                                       IInfluenceLine** pLeftAxialInfl,  IInfluenceLine** pRightAxialInfl,
                                       IInfluenceLine** pLeftShearInfl,  IInfluenceLine** pRightShearInfl,
                                       IInfluenceLine** pLeftMomentInfl, IInfluenceLine** pRightMomentInfl, 
                                       IInfluenceLine** pLeftDxInfl,     IInfluenceLine** pRightDxInfl,
                                       IInfluenceLine** pLeftDyInfl,     IInfluenceLine** pRightDyInfl, 
                                       IInfluenceLine** pLeftRzInfl,     IInfluenceLine** pRightRzInfl)
{ 
   ATLASSERT(m_pFem2d!=NULL);
   CHRException hr;


   // get poi information
   PoiMapIterator itpoi(m_PoiMap.find( &PoiMap(poiID) ));
   if (itpoi!= m_PoiMap.end() )
   {
      PoiMap& poi_map = *(*itpoi);

      // optimization here - don't need to do coordinate transform for pois in superstructure since we know it is flat
      if (poi_map.GetLBAMMemberType()==mtSpan || poi_map.GetLBAMMemberType()==mtSuperstructureMember)
      {
         forceOrientation = roMember;
      }

      // use the poi map to compute the influence line.
      poi_map.GetInfluenceLines(m_pFem2d, m_InfluenceLoadSet, 
                                forceOrientation, forceZeroTolerance, deflZeroTolerance, 
                                pLeftAxialInfl,  pRightAxialInfl,
                                pLeftShearInfl,  pRightShearInfl,
                                pLeftMomentInfl, pRightMomentInfl,
                                pLeftDxInfl,     pRightDxInfl,
                                pLeftDyInfl,     pRightDyInfl,
                                pLeftRzInfl,     pRightRzInfl);
   }
   else
   {
      CComBSTR msg = ::CreateErrorMsg1L(IDS_E_POI_NOT_FOUND, poiID);
      THROW_LBAMA_MSG(POI_NOT_FOUND,msg);
   }
}

void CAnalysisModel::GetReactionInfluenceLine(SupportIDType supportID, ForceEffectType ReactionEffect, CInfluenceLine* pInfl)
{
   ATLASSERT(m_pFem2d!=NULL);
   CHRException hr;

   CollectionIndexType num_pts = m_InfluenceLoadSet.size();
   if (num_pts == 0)
   {
      ATLASSERT(0);
      THROW_LBAMA(NO_INFLUENCE_LOCATIONS);
   }

   // reserve some space
   pInfl->Reserve(num_pts);

   // first need to find support joint
   JointIDType jointID;
   if (0 <= supportID && supportID < SupportIDType(m_SupportNodes.size()) )
   {
      // permanant support is requested
      jointID = m_SupportNodes[supportID];
   }
   else
   {
      // see if a temporary support is requested
      IdMapIterator itm( m_TemporarySupportNodes.find(supportID) );
      if (itm != m_TemporarySupportNodes.end())
      {
         jointID = itm->second;
      }
      else
      {
         // No joint found for sptId
         CComBSTR msg=CreateErrorMsg1L(IDS_E_SUPPORT_NOT_EXIST, supportID);
         THROW_LBAMA_MSG(SUPPORT_NOT_EXIST,msg);
      }
   }

   // if we made it here, we found the joint
   CComQIPtr<IFem2dModelResults> results(m_pFem2d);

   switch (ReactionEffect)
   {
   case fetFx:
   case fetFy:
   case fetMz:
      {
      // Reactions
      // loop through all influence loads for this poi
         InfluenceLoadSetIterator iter( m_InfluenceLoadSet.begin() );
         InfluenceLoadSetIterator iterend( m_InfluenceLoadSet.end() );
         for (; iter != iterend; iter++)
         {
            const InfluenceLoadLocation& influenceLoadLocation = *iter;

            // get Reaction
            Float64 rx, ry, rz;

            try
            {
               results->ComputeReactions(influenceLoadLocation.m_FemLoadCaseID, jointID, &rx, &ry, &rz);
            }
            catch (...)
            {
               DealWithFem2dExceptions();
            }

            Float64 val;
            if (ReactionEffect==fetFx)
            {
               val = rx;
            }
            else if (ReactionEffect==fetFy)
            {
               val = ry;
            }
            else if (ReactionEffect==fetMz)
            {
               val = rz;
            }
            else
            {
               THROW_HR(E_INVALIDARG);
            }

            // dual-values isn't ugly for Reaction influence
            hr = pInfl->Add(influenceLoadLocation.m_LocationType, influenceLoadLocation.m_GlobalX, val);
         }
      }
   break;

   default:
      THROW_HR(E_INVALIDARG);
   }

}

void CAnalysisModel::GetSupportDeflectionInfluenceLine(SupportIDType supportID, ForceEffectType sdEffect, CInfluenceLine* pInfl)
{
   ATLASSERT(m_pFem2d!=NULL);
   CHRException hr;

   CollectionIndexType num_pts = m_InfluenceLoadSet.size();
   if (num_pts==0)
   {
      ATLASSERT(0);
      THROW_LBAMA(NO_INFLUENCE_LOCATIONS);
   }

   // reserve some space
   pInfl->Reserve(num_pts);

   // first need to find support joint
   JointIDType jointID;
   if (0 <= supportID && supportID < SupportIDType(m_SupportNodes.size()) )
   {
      // permanant support is requested
      jointID = m_SupportNodes[supportID];
   }
   else
   {
      // see if a temporary support is requested
      IdMapIterator itm( m_TemporarySupportNodes.find(supportID) );
      if (itm != m_TemporarySupportNodes.end())
      {
         jointID = itm->second;
      }
      else
      {
         // No joint found for sptId
         CComBSTR msg=CreateErrorMsg1L(IDS_E_SUPPORT_NOT_EXIST, supportID);
         THROW_LBAMA_MSG(SUPPORT_NOT_EXIST,msg);
      }
   }

   // if we made it here, we found the joint
   CComQIPtr<IFem2dModelResults> results(m_pFem2d);

   switch (sdEffect)
   {
   case fetFx:
   case fetFy:
   case fetMz:
      {
      // Reactions
      // loop through all influence loads for this poi
         InfluenceLoadSetIterator iter( m_InfluenceLoadSet.begin() );
         InfluenceLoadSetIterator iterend( m_InfluenceLoadSet.end() );
         for (; iter != iterend; iter++)
         {
            const InfluenceLoadLocation& influenceLoadLocation = *iter;

            // get Reaction
            Float64 rx, ry, rz;

            try
            {
               results->ComputeJointDisplacements(influenceLoadLocation.m_FemLoadCaseID, jointID, &rx, &ry, &rz);
            }
            catch (...)
            {
               DealWithFem2dExceptions();
            }

            Float64 val;
            if (sdEffect==fetFx)
            {
               val = rx;
            }
            else if (sdEffect==fetFy)
            {
               val = ry;
            }
            else if (sdEffect==fetMz)
            {
               val = rz;
            }
            else
            {
               THROW_HR(E_INVALIDARG);
            }

            hr = pInfl->Add(influenceLoadLocation.m_LocationType, influenceLoadLocation.m_GlobalX, val);
         }
      }
   break;

   default:
      THROW_HR(E_INVALIDARG);
   }
}

///////////////////////////////////////////////////////////////
////// IAnalysisPOIs
///////////////////////////////////////////////////////////////

HRESULT CAnalysisModel::get_SpanPoiIncrement( PoiIDType *pVal)
{
   *pVal = m_MinSpanPoiIncrement;
   return S_OK;
}

HRESULT CAnalysisModel::put_SpanPoiIncrement( PoiIDType newVal)
{
   if (newVal<1)
      return E_INVALIDARG;

   m_MinSpanPoiIncrement = newVal;
   return S_OK;
}

HRESULT CAnalysisModel::get_CantileverPoiIncrement(PoiIDType *pVal)
{
   *pVal = m_MinCantileverPoiIncrement;
   return S_OK;
}

HRESULT CAnalysisModel::put_CantileverPoiIncrement( PoiIDType newVal)
{
   if (newVal<1)
      return E_INVALIDARG;

   m_MinCantileverPoiIncrement = newVal;
   return S_OK;
}

HRESULT CAnalysisModel::GetSuperstructurePois(ILongArray* *poiIDs, IDblArray* *poiLocations)
{
   HRESULT hr;
   CollectionIndexType size = m_pPoiTracker->size();

   CComPtr<ILongArray> poi_ids;
   hr = poi_ids.CoCreateInstance(CLSID_LongArray);
   if (FAILED(hr))
      return hr;

   hr = poi_ids->Reserve(size);
   if (FAILED(hr))
      return hr;

   CComPtr<IDblArray> poi_locs;
   hr = poi_locs.CoCreateInstance(CLSID_DblArray);
   if (FAILED(hr))
      return hr;

   hr = poi_locs->Reserve(size);
   if (FAILED(hr))
      return hr;

   Uint32 i=0;
   SortedPoiMapTracker::iterator itp(m_pPoiTracker->begin());
   SortedPoiMapTracker::iterator itpend(m_pPoiTracker->end());
   for (; itp!=itpend; itp++)
   {
      PoiMap& info = *(*itp);
      poi_ids->Add(info.GetLBAMPoiID());
      poi_locs->Add(info.GetLocation());

      i++;
   }

   *poiIDs = poi_ids.Detach();
   *poiLocations = poi_locs.Detach();
   return S_OK;
}

HRESULT CAnalysisModel::GetPoiInfo(PoiIDType poiID, MemberType* lbamMemberType, MemberIDType* memberID, Float64* memberLoc)
{
   Float64 globx;
   return GetPoiInfoPrv(poiID,  lbamMemberType, memberID, memberLoc, &globx);
}

HRESULT CAnalysisModel::GetPoiInfoPrv(PoiIDType poiID, MemberType* lbamMemberType, MemberIDType* memberID, Float64* memberLoc, Float64* globalLoc)
{
   PoiMapIterator itpoi( m_PoiMap.find( &PoiMap(poiID) ));
   if (itpoi!= m_PoiMap.end() )
   {
      PoiMap& info = *(*itpoi);
      ATLASSERT(poiID == info.GetLBAMPoiID());

      *lbamMemberType = info.GetLBAMMemberType();
      *memberID       = info.GetLBAMMemberID();
      *memberLoc      = info.GetLBAMPoiLocation();
      *globalLoc      = info.GetLocation();
      return S_OK;
   }

   return E_INVALIDARG;
}

HRESULT CAnalysisModel::GetSsPoiInfo(PoiIDType poiID, MemberType* lbamMemberType, MemberIDType* memberID, Float64* globalX)
{
   PoiMap findme(poiID);
   SortedPoiMapTracker::iterator itp( std::find_if(m_pPoiTracker->begin(), m_pPoiTracker->end(), PoiMapIdMatch(poiID) ) );

   if (itp!=m_pPoiTracker->end())
   {
      PoiMap& info = *(*itp);
      ATLASSERT(poiID == info.GetLBAMPoiID());

      *lbamMemberType = info.GetLBAMMemberType();
      *memberID       = info.GetLBAMMemberID();
      *globalX = info.GetLocation();
      return S_OK;
   }

   return E_INVALIDARG;
}

void CAnalysisModel::DealWithFem2dExceptions()
{
   // Deal with exceptions thrown from the Fem2D engine
   try
   {
      throw; // throw whatever got thrown last to be caught immediately!
   }
   catch (_com_error& re)
   {
      HRESULT err = re.Error();

      if(err==FEM2D_E_JOINT_EQUILIBRIUM_NOT_SATISFIED ||
         err==FEM2D_E_MEMBER_EQUILIBRIUM_NOT_SATISFIED ||
         err==FEM2D_E_SOLVING_GLOBAL_STIFFNESS ||
         err==FEM2D_E_MATRIX_BACK_SUBSTITUTION ||
         err==FEM2D_E_MATRIX_FACTORING ||
         err==FEM2D_E_JOINT_DISP_TO_FIXED_DOF_ONLY)
      {
         // instability 
         CComBSTR msg = ::CreateErrorMsg1S(IDS_E_INSTABILITY, m_Stage);
         THROW_LBAMA_MSG(INSTABILITY,msg);
      }
   }
   catch(...)
   {
      // don't let exceptions out of here
   }

   // fem crapped and we don't know why
   ATLASSERT(0);
   CComBSTR msg = ::CreateErrorMsg1S(IDS_E_FEM2D, m_Stage);
   THROW_LBAMA_MSG(FEM2D,msg);
}
