///////////////////////////////////////////////////////////////////////
// LBAM Analysis Test - Test driver for LBAM analysis library
// Copyright © 1999-2018  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestStressPoints.cpp: implementation of the TestStressPoints class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestStressPoints.h"

#include "..\AnalysisUtils.h"
#include <fstream>
#include "TestUtils.h"
#include "..\..\LBAMTestUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static void SetupSegment(ISegment* pseg, Float64 factor, bool IsColumn);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TestStressPoints::TestStressPoints()
{

}

TestStressPoints::~TestStressPoints()
{

}

inline void TestStressPoint(IStressPoint* sp, Float64 Sa, Float64 Sm)
{
   Float64 sa, sm;
   TRY_TEST(sp->get_Sa(&sa), S_OK);
   TRY_TEST(sa, Sa);
   TRY_TEST(sp->get_Sm(&sm), S_OK);
   TRY_TEST(sm, Sm);
}

inline void TestSpsAtPoi(IGetStressPoints* pigsp, CComBSTR Stage, PoiIDType poiID, 
                        Float64 Sa0, Float64 Sm0, Float64 Sa1, Float64 Sm1, Float64 Sa2, Float64 Sm2)
{
   CComQIPtr<IStressPoints> left_sps, right_sps;
   pigsp->GetStressPointsAtPOI(poiID, Stage, &left_sps, &right_sps);
   CollectionIndexType cnt;
   TRY_TEST(left_sps->get_Count(&cnt), S_OK);
   TRY_TEST(cnt, 3);
   CComQIPtr<IStressPoint> sp0, sp1, sp2;
   TRY_TEST(left_sps->get_Item(0, &sp0), S_OK);
   TestStressPoint(sp0, Sa0, Sm0);

   TRY_TEST(left_sps->get_Item(1, &sp1), S_OK);
   TestStressPoint(sp1, Sa1, Sm1);

   TRY_TEST(left_sps->get_Item(2, &sp2), S_OK);
   TestStressPoint(sp2, Sa2, Sm2);
}

HRESULT TestStressPoints::Test()
{
   // build a model and attach it to our load group response object
   CComPtr<ILoadGroupResponse> plgr;
   plgr.CoCreateInstance(CLSID_LoadGroupForceResponse);
//   plgr.CoCreateInstance(CLSID_LoadGroupDeflectionResponse);

   CComPtr<ILBAMModel> psm;
   psm.Attach( CreateModel(true) );

   HRESULT hr;
   CComQIPtr<IDependOnLBAM> pctx(plgr);
   hr = pctx->putref_Model(psm);

   CComQIPtr<IGetStressPoints> pigsp(plgr);
   TRY_TEST(pigsp!=nullptr, true);

   TestSpsAtPoi(pigsp, CComBSTR("Stage 1"), 1, 2.0, 2.0, 2.0, 0.0, 2.0,-2.0);
   TestSpsAtPoi(pigsp, CComBSTR("Stage 2"), 1, 2.0, 2.0, 2.0, 0.0, 2.0,-2.0);
   TestSpsAtPoi(pigsp, CComBSTR("Stage 1"), 5, 5.1, 5.2, 5.3, 5.4, 5.5, 5.6);
   TestSpsAtPoi(pigsp, CComBSTR("Stage 2"), 5, 2.0, 2.0, 2.0, 0.0, 2.0,-2.0);
   TestSpsAtPoi(pigsp, CComBSTR("Stage 1"), 7, 2.0, 2.0, 2.0, 0.0, 2.0,-2.0);
   TestSpsAtPoi(pigsp, CComBSTR("Stage 2"), 7, 5.1, 5.2, 2.0, 0.0, 2.0,-2.0);
   TestSpsAtPoi(pigsp, CComBSTR("Stage 1"), 6, 2.0, 2.0, 2.0, 0.0, 2.0,-2.0);
   TestSpsAtPoi(pigsp, CComBSTR("Stage 2"), 6, 2.0, 2.0, 2.0, 0.0, 2.0,-2.0);

   return S_OK;
}


ILBAMModel* TestStressPoints::CreateModel(bool doPois)
{
   CComPtr<ILBAMModel> psm;
   TRY_TEST(psm.CoCreateInstance( CLSID_LBAMModel ), S_OK );
   Float64 d;

   // stages
   CComPtr<IStages> pStages;
   TRY_TEST(psm->get_Stages(&pStages), S_OK);

   CComPtr<IStage> pStage1, pStage2;
   TRY_TEST(pStage1.CoCreateInstance( CLSID_Stage ), S_OK );
   TRY_TEST(pStage2.CoCreateInstance( CLSID_Stage ), S_OK );
   TRY_TEST(pStage1->put_Name(_bstr_t("Stage 1")), S_OK );
   TRY_TEST(pStage2->put_Name(_bstr_t("Stage 2")), S_OK );
   TRY_TEST(pStages->Add(pStage1), S_OK);
   TRY_TEST(pStages->Add(pStage2), S_OK);

   // add spans
   // ======================
   CComPtr<ISpan> pspn0;
   TRY_TEST(pspn0.CoCreateInstance( CLSID_Span ), S_OK );

   CComPtr<ISpans> pspns;
   TRY_TEST(psm->get_Spans(&pspns), S_OK);

   TRY_TEST(pspns->Add(pspn0), S_OK);
   TRY_TEST(pspn0->put_Length(100.0), S_OK);

   // check the length of our spans
   TRY_TEST(pspns->get_Length(&d), S_OK);
   TRY_TEST(d, 100.0);

// SuperstructureMembers
//===========================
   CComPtr<ISuperstructureMember> pssm0;
   TRY_TEST(pssm0.CoCreateInstance( CLSID_SuperstructureMember ), S_OK );

   CComPtr<ISuperstructureMembers> pssms;
   TRY_TEST(psm->get_SuperstructureMembers(&pssms), S_OK);

   // add SuperstructureMember 0
   TRY_TEST(pssms->Add(pssm0), S_OK);
   TRY_TEST(pssm0->put_Length(100.0), S_OK);

   CComPtr<ISegment> pseg1s1, pseg1s2;
   TRY_TEST( pseg1s1.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( pseg1s2.CoCreateInstance( CLSID_Segment ) , S_OK );
   SetupSegment(pseg1s1, 0.8, false);
   TRY_TEST( pseg1s1->put_Length(100.0) , S_OK );
   SetupSegment(pseg1s2, 1.0, false);
   TRY_TEST( pseg1s2->put_Length(100.0) , S_OK );

   TRY_TEST(pssm0->AddSegment(_bstr_t("Stage 1"), pseg1s1), S_OK );
   TRY_TEST(pssm0->AddSegment(_bstr_t("Stage 2"), pseg1s2), S_OK );

   // check the length of our ssms
   TRY_TEST(pssms->get_Length(&d), S_OK);
   TRY_TEST(d, 100);

   // add our supports
   // ======================
   CComPtr<ISupport> psup0, psup1;
   TRY_TEST(psup0.CoCreateInstance( CLSID_Support ), S_OK );
   TRY_TEST(psup1.CoCreateInstance( CLSID_Support ), S_OK );

   CComPtr<ISupports> psups;
   TRY_TEST(psm->get_Supports(&psups), S_OK);

   TRY_TEST(psups->Add(psup0), S_OK);
   TRY_TEST(psups->Add(psup1), S_OK);

   // POIs
   // ======================
   CComPtr<IPOIs> pPOIs;
   TRY_TEST(psm->get_POIs(&pPOIs), S_OK);

   // span 0
   Float64 loc = 0.0;
   for (PoiIDType i=1; i<11; i++)
   {
      CComPtr<IPOI> pPOI;
      TRY_TEST(pPOI.CoCreateInstance( CLSID_POI ), S_OK );
      TRY_TEST( pPOI->put_ID(i), S_OK );
      TRY_TEST( pPOI->put_MemberType(mtSpan), S_OK );
      TRY_TEST( pPOI->put_MemberID(0), S_OK );
      TRY_TEST( pPOI->put_Location(loc), S_OK );
      TRY_TEST(pPOIs->Add(pPOI), S_OK);
      loc -= 0.1;
   }

   // muck with stress points at some pois
   CComPtr<IPOI> poi_5;  // stress point 5 - replace all stress coeff's
   TRY_TEST(pPOIs->Find(5, &poi_5), S_OK);
   CComPtr<IStressPoints> new_sps_5;
   TRY_TEST(new_sps_5.CoCreateInstance(CLSID_StressPoints), S_OK);
   CComPtr<IStressPoint> new_sp0_5,new_sp1_5,new_sp2_5;
   TRY_TEST(new_sp0_5.CoCreateInstance(CLSID_StressPoint), S_OK);
   TRY_TEST(new_sp1_5.CoCreateInstance(CLSID_StressPoint), S_OK);
   TRY_TEST(new_sp2_5.CoCreateInstance(CLSID_StressPoint), S_OK);
   TRY_TEST(new_sp0_5->put_Sa(5.1), S_OK);
   TRY_TEST(new_sp0_5->put_Sm(5.2), S_OK);
   TRY_TEST(new_sp1_5->put_Sa(5.3), S_OK);
   TRY_TEST(new_sp1_5->put_Sm(5.4), S_OK);
   TRY_TEST(new_sp2_5->put_Sa(5.5), S_OK);
   TRY_TEST(new_sp2_5->put_Sm(5.6), S_OK);
   TRY_TEST(new_sps_5->Add(new_sp0_5), S_OK);
   TRY_TEST(new_sps_5->Add(new_sp1_5), S_OK);
   TRY_TEST(new_sps_5->Add(new_sp2_5), S_OK);

   CComPtr<IPOIStressPoints> poisps_5;
   TRY_TEST(poi_5->get_POIStressPoints(&poisps_5), S_OK);
   TRY_TEST(poisps_5->Insert(CComBSTR("Stage 1"), new_sps_5, new_sps_5), S_OK);

   CComPtr<IPOI> poi_7;  // stress point 7 - only replace 1 stress point
   TRY_TEST(pPOIs->Find(7, &poi_7), S_OK);
   CComPtr<IStressPoints> new_sps_7;
   TRY_TEST(new_sps_7.CoCreateInstance(CLSID_StressPoints), S_OK);
   CComPtr<IStressPoint> new_sp0_7;
   TRY_TEST(new_sp0_7.CoCreateInstance(CLSID_StressPoint), S_OK);
   TRY_TEST(new_sp0_7->put_Sa(5.1), S_OK);
   TRY_TEST(new_sp0_7->put_Sm(5.2), S_OK);
   TRY_TEST(new_sps_7->Add(new_sp0_7), S_OK);

   CComPtr<IPOIStressPoints> poisps_7;
   TRY_TEST(poi_7->get_POIStressPoints(&poisps_7), S_OK);
   TRY_TEST(poisps_7->Insert(CComBSTR("Stage 2"), new_sps_7, new_sps_7), S_OK);

   // Load Groups
   CComPtr<ILoadGroups> pLoadGroups;
   TRY_TEST(psm->get_LoadGroups(&pLoadGroups), S_OK);

   TCHAR* lgns[]={_T("Point Loads"),_T("Distributed Loads")};
   for (int i = 0; i<2; i++)
   {
      CComPtr<ILoadGroup> pLoadGroup;
      TRY_TEST(pLoadGroup.CoCreateInstance( CLSID_LoadGroup ), S_OK );
      TRY_TEST( pLoadGroup->put_Name( CComBSTR(lgns[i]) ), S_OK );
      TRY_TEST(pLoadGroups->Add(pLoadGroup), S_OK);
   }

   // Point Loads
   CComPtr<IPointLoads> pPointLoads;
   TRY_TEST(psm->get_PointLoads(&pPointLoads), S_OK);

   CComPtr<IPointLoad> pPointLoad1, pPointLoad2;
   TRY_TEST(pPointLoad1.CoCreateInstance( CLSID_PointLoad ), S_OK );
   TRY_TEST(pPointLoad2.CoCreateInstance( CLSID_PointLoad ), S_OK );

   CComPtr<IPointLoadItem> pPLI1, pPLI2;
   TRY_TEST(pPointLoads->Add(_bstr_t("Stage 1"), _bstr_t("Point Loads"), pPointLoad1, &pPLI1), S_OK);
   TRY_TEST(pPointLoads->Add(_bstr_t("Stage 2"), _bstr_t("Point Loads"), pPointLoad2, &pPLI2), S_OK);

   TRY_TEST(pPointLoad1->put_MemberType(mtSuperstructureMember), S_OK);
   TRY_TEST(pPointLoad1->put_MemberID(0), S_OK);
   TRY_TEST(pPointLoad1->put_Location(10), S_OK);
   TRY_TEST(pPointLoad1->SetForce(0,-1000,0), S_OK);

   TRY_TEST(pPointLoad2->put_MemberType(mtSuperstructureMember), S_OK);
   TRY_TEST(pPointLoad2->put_MemberID(0), S_OK);
   TRY_TEST(pPointLoad2->put_Location(-0.5), S_OK);
   TRY_TEST(pPointLoad2->SetForce(0,-1000,0), S_OK);

   // Distributed Loads
   CComPtr<IDistributedLoads> pDistributedLoads;
   TRY_TEST(psm->get_DistributedLoads(&pDistributedLoads), S_OK);

   CComPtr<IDistributedLoad> pDistributedLoad1, pDistributedLoad2;
   TRY_TEST(pDistributedLoad1.CoCreateInstance( CLSID_DistributedLoad ), S_OK );
   TRY_TEST(pDistributedLoad2.CoCreateInstance( CLSID_DistributedLoad ), S_OK );

   CComPtr<IDistributedLoadItem> pDLI1, pDLI2;
   TRY_TEST(pDistributedLoads->Add(_bstr_t("Stage 1"), _bstr_t("Distributed Loads"), pDistributedLoad1, &pDLI1), S_OK);
   TRY_TEST(pDistributedLoads->Add(_bstr_t("Stage 2"), _bstr_t("Distributed Loads"), pDistributedLoad2, &pDLI2), S_OK);

   TRY_TEST(pDistributedLoad1->put_MemberType(mtSuperstructureMember), S_OK);
   TRY_TEST(pDistributedLoad1->put_MemberID(0), S_OK);
   TRY_TEST(pDistributedLoad1->put_Direction(ldFy), S_OK);
   TRY_TEST(pDistributedLoad1->put_WStart(-100.), S_OK);
   TRY_TEST(pDistributedLoad1->put_WEnd(-100.), S_OK);
   TRY_TEST(pDistributedLoad1->put_StartLocation(0.0), S_OK);
   TRY_TEST(pDistributedLoad1->put_EndLocation(-1.0), S_OK);

   TRY_TEST(pDistributedLoad2->put_MemberType(mtSuperstructureMember), S_OK);
   TRY_TEST(pDistributedLoad2->put_MemberID(0), S_OK);
   TRY_TEST(pDistributedLoad2->put_Direction(ldFy), S_OK);
   TRY_TEST(pDistributedLoad2->put_WStart(-100), S_OK);
   TRY_TEST(pDistributedLoad2->put_WEnd(-100), S_OK);
   TRY_TEST(pDistributedLoad2->put_StartLocation(-1.0), S_OK);
   TRY_TEST(pDistributedLoad2->put_EndLocation(-0.9), S_OK);

   // add lrfd live loads
   ConfigureLrfdLiveLoadModelInKipFeet(psm);

   // configure using lrfd table
   ConfigureLrfdLoadCombinations(psm);

   CComPtr<ILoadCases> lcs;
   TRY_TEST( (psm)->get_LoadCases(&lcs), S_OK);

   CComPtr<ILoadCase> lcdc;
   TRY_TEST( lcs->Find(CComBSTR("DC"),&lcdc), S_OK);
   lcdc->AddLoadGroup(_bstr_t(lgns[0]));

   CComPtr<ILoadCase> lcdw;
   TRY_TEST( lcs->Find(CComBSTR("DW"),&lcdw), S_OK);
   lcdw->AddLoadGroup(_bstr_t(lgns[1]));

   return psm.Detach();
}

void SetupSegment(ISegment* pseg, Float64 factor, bool IsColumn)
{
   CComPtr<ISegmentCrossSection> pcs;
   TRY_TEST(pcs.CoCreateInstance( CLSID_SegmentCrossSection ), S_OK );

   // fake in some numbers
   Float64 e = 28; // approx 4ksi concrete
   Float64 ea, ei, d;
   Float64 sm, sa;
   if (IsColumn)
   {
      // 3' sq column
      ea = 9.0   * e *factor;
      ei = 6.75  * e * factor;
      d  = 3.0;
      sm = 2.0;
      sa = 2.0;
   }
   else
   {
      // 6' deep x 1' wide rect
      ea = 6.0  * e * factor;
      ei = 18.0 * e * factor;
      d  = 6.0;
      sm = 2.0;
      sa = 2.0;
   }

   TRY_TEST( pcs->put_EAForce(ea), S_OK );
   TRY_TEST( pcs->put_EIForce(ei), S_OK );
   TRY_TEST( pcs->put_EADefl(ea/2.), S_OK ); // deflection has 1/2 props
   TRY_TEST( pcs->put_EIDefl(ei/2.), S_OK );
   TRY_TEST( pcs->put_ThermalCoeff(1.5), S_OK );
   TRY_TEST( pcs->put_Depth(d), S_OK );

   CComPtr<IStressPoints> psps;
   TRY_TEST( pcs->get_StressPoints(&psps), S_OK );

   CComPtr<IStressPoint> pss1, pss2, pss3;
   TRY_TEST( pss1.CoCreateInstance( CLSID_StressPoint ) , S_OK );
   TRY_TEST( pss2.CoCreateInstance( CLSID_StressPoint ) , S_OK );
   TRY_TEST( pss3.CoCreateInstance( CLSID_StressPoint ) , S_OK );

   TRY_TEST( pss1->put_Sm(sm), S_OK );
   TRY_TEST( pss1->put_Sa(sa), S_OK );
   TRY_TEST( psps->Add(pss1), S_OK);

   TRY_TEST( psps->Add(pss2), S_OK);
   TRY_TEST( pss2->put_Sm(0.0), S_OK );
   TRY_TEST( pss2->put_Sa(sa), S_OK );

   TRY_TEST( psps->Add(pss3), S_OK);
   TRY_TEST( pss3->put_Sm(-sm), S_OK );
   TRY_TEST( pss3->put_Sa(sa), S_OK );

   TRY_TEST( pseg->putref_SegmentCrossSection(pcs), S_OK);
}

