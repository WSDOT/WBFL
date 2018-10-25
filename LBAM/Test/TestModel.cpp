///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2016  Washington State Department of Transportation
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

// TestModel.cpp: implementation of the CTestModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestModel.h"
#include <string>
#include <fstream>
#include <MathEx.h>

#define TEST_STIFFNESS_FIRED() TRY_TEST(pMe->m_csStiffnessFired, true); pMe->InitFired(); 
#define TEST_STRESS_FIRED() TRY_TEST(pMe->m_csStressPointsFired, true); pMe->InitFired(); 
#define TEST_COMBO_FIRED() TRY_TEST(pMe->m_csCombinationFired, true); pMe->InitFired();   
#define TEST_STAGE_FIRED() TRY_TEST(pMe->m_csStageFired, true); pMe->InitFired();   
#define TEST_POI_FIRED() TRY_TEST(pMe->m_csPOIFired, true); pMe->InitFired();   
#define TEST_LOAD_FIRED() TRY_TEST(pMe->m_csLoadFired, true); pMe->InitFired();   
#define TEST_DESCRIPTION_FIRED() TRY_TEST(pMe->m_csDescriptionFired, true); pMe->InitFired();   
#define TEST_LIVELOAD_FIRED() TRY_TEST(pMe->m_csLiveLoadFired, true); pMe->InitFired();   
#define TEST_USER_DATA_FIRED() TRY_TEST(pMe->m_csUserDataFired, true); pMe->InitFired();   
#define TEST_DF_FIRED();

#include "TestSeg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// utility struct for computing coarse model statistics
class ModelStats
{
public:
   SpanIndexType NumSpans;
   CollectionIndexType NumSuperstructureMembers;
   SupportIndexType NumSupports;
   Float64 SpanLengths;
   Float64 MemberLengths;
   StageIndexType NumStages;
   CollectionIndexType NumLoadGroups;
   CollectionIndexType NumLoadCases;
   CollectionIndexType NumLoadCombinations;
   CollectionIndexType NumPointLoads;
   CollectionIndexType NumDistributedLoads;
   CollectionIndexType NumTemperatureLoads;
   CollectionIndexType NumStrainLoads;
   CollectionIndexType NumSettlementLoads;

   bool operator==(const ModelStats& rother)
   {
      return NumSpans                 == rother.NumSpans &&
             NumSuperstructureMembers == rother.NumSuperstructureMembers &&
             NumSupports              == rother.NumSupports &&
             SpanLengths              == rother.SpanLengths &&
             MemberLengths            == rother.MemberLengths &&
             NumStages                == rother.NumStages &&
             NumLoadGroups            == rother.NumLoadGroups &&
             NumLoadCases             == rother.NumLoadCases &&
             NumLoadCombinations      == rother.NumLoadCombinations &&
             NumPointLoads            == rother.NumPointLoads &&
             NumDistributedLoads      == rother.NumDistributedLoads &&
             NumTemperatureLoads      == rother.NumTemperatureLoads &&
             NumStrainLoads           == rother.NumStrainLoads &&
             NumSettlementLoads       == rother.NumSettlementLoads;
   }
};

void ComputeModelStatistics(ILBAMModel* pmodel, ModelStats* pstats);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTestModel::CTestModel():
m_CsCookie(0)
{
   InitFired();
}

CTestModel::~CTestModel()
{
}

void CTestModel::Test()
{
   HRESULT hr;

   // create a listener
   CComObject<CTestModel>* pMe;
   CComObject<CTestModel>::CreateInstance(&pMe);
   pMe->AddRef();

   // create
   CComPtr<ILBAMModel> psm;
   TRY_TEST(psm.CoCreateInstance( CLSID_LBAMModel ), S_OK );
   Float64 d;

   // let's listen to pcs
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pMe);
   TRY_TEST(AtlAdvise(psm,punk,IID_ILBAMModelEvents,&dwCookie),S_OK);

   // cause some events to fire
   // add some spans
   // ======================
   CComPtr<ISpan> pspn0, pspn1, pspn2;
   TRY_TEST(pspn0.CoCreateInstance( CLSID_Span ), S_OK );
   TRY_TEST(pspn1.CoCreateInstance( CLSID_Span ), S_OK );
   TRY_TEST(pspn2.CoCreateInstance( CLSID_Span ), S_OK );

   CComPtr<ISpans> pspns;
   TRY_TEST(psm->get_Spans(&pspns), S_OK);

   // add span 0 with a temporary support at mid-span
   TRY_TEST(pspns->Add(pspn0), S_OK);
   TRY_TEST(pspn0->get_Length(&d), S_OK);
   TRY_TEST(d, 0.0);

   // test load modifier on span
   pMe->TestLoadModifier(pMe, pspn0.p);
     
   TRY_TEST(pspn0->put_Length(3.2), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST(pspn0->get_Length(&d), S_OK);
   TRY_TEST(d, 3.2);

   CComPtr<ITemporarySupport> ptmpsp1;
   TRY_TEST(ptmpsp1.CoCreateInstance( CLSID_TemporarySupport ), S_OK );
   TRY_TEST(ptmpsp1->put_ID(21), S_OK );


   CComPtr<ISegment> pseg1, pseg2;
   CComPtr<ISegment> ;
   TRY_TEST( pseg1.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( pseg2.CoCreateInstance( CLSID_Segment ) , S_OK );

   SetupSegment(pseg1);
   SetupSegment(pseg2);

   CComPtr<ITemporarySupports> ptmpsps;
   TRY_TEST(pspn0->get_TemporarySupports(&ptmpsps), S_OK);

   TRY_TEST(ptmpsps->Add(ptmpsp1), S_OK);

   TRY_TEST(ptmpsp1->put_Location(2.0), S_OK);
   TEST_STIFFNESS_FIRED();

   ptmpsp1->AddSegment(CComBSTR("Stage 1"), pseg1);
   TEST_STIFFNESS_FIRED();
   TRY_TEST(ptmpsp1->put_Length(sqrt(2.0)), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST(ptmpsp1->put_BottomOffset(-1.0), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST(ptmpsp1->AddSegment(CComBSTR("Stage 1"), pseg2), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST(pseg1->put_Length(0.4), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST(pseg1->put_Length(1.8), S_OK );
   TEST_STIFFNESS_FIRED();

   // test load modifier on temporary support
   pMe->TestLoadModifier(pMe, ptmpsp1.p);

   // add span 1 - no temporary support
   TRY_TEST(pspns->Add(pspn1), S_OK);
   TRY_TEST(pspn1->put_Length(5.9), S_OK);
   TEST_STIFFNESS_FIRED();

   // add span 2 with a default temporary support at mid-span
   TRY_TEST(pspns->Add(pspn2), S_OK);
   TRY_TEST(pspn2->put_Length(3.2), S_OK);
   TEST_STIFFNESS_FIRED();

   CComPtr<ITemporarySupport> ptmpsp2;
   TRY_TEST(ptmpsp2.CoCreateInstance( CLSID_TemporarySupport ), S_OK );
   TRY_TEST(ptmpsp2->put_ID(22), S_OK );

   CComPtr<ITemporarySupports> ptmpsps2;
   TRY_TEST(pspn2->get_TemporarySupports(&ptmpsps2), S_OK);

   TRY_TEST(ptmpsps2->Add(ptmpsp2), S_OK);
   TEST_STIFFNESS_FIRED();

   TRY_TEST(ptmpsp2->put_Location(-0.5), S_OK );
   TEST_STIFFNESS_FIRED();

   // check the length of our spans
   TRY_TEST(pspns->get_Length(&d), S_OK);
   TRY_TEST(d, 12.3);

   // add our supports
   // ======================
   CComPtr<ISupport> psup0, psup1, psup2, psup3;
   TRY_TEST(psup0.CoCreateInstance( CLSID_Support ), S_OK );
   TRY_TEST(psup1.CoCreateInstance( CLSID_Support ), S_OK );
   TRY_TEST(psup2.CoCreateInstance( CLSID_Support ), S_OK );

   CComPtr<ISupports> psups;
   TRY_TEST(psm->get_Supports(&psups), S_OK);

   // add Support 0 - give it a length and segments the same as temporary support 1
   TRY_TEST(psups->Add(psup0), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST(psup0->put_Length(1.2), S_OK);
   TEST_STIFFNESS_FIRED();

   TRY_TEST(psup0->AddSegment(CComBSTR("Stage 1"), pseg1), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST(psup0->AddSegment(CComBSTR("Stage 1"), pseg2), S_OK );
   TEST_STIFFNESS_FIRED();

   // add support 3 to position 1 - we'll move it soon
   TRY_TEST(psup0->Clone(&psup3), S_OK );
   TRY_TEST(psups->Add(psup3), S_OK);

   // add supports 1 and 2 as default supports
   TRY_TEST(psups->Add(psup1), S_OK);
   TEST_STIFFNESS_FIRED();

   TRY_TEST(psups->Add(psup2), S_OK);
   TEST_STIFFNESS_FIRED();

   // move support 3
   TRY_TEST(psups->MoveTo(1,3), S_OK);
   TEST_STIFFNESS_FIRED();

   CComPtr<ISupport> psupt;
   TRY_TEST(psups->get_Item(3, &psupt), S_OK);
   TRY_TEST(psupt.IsEqualObject(psup3), true);

   TRY_TEST(psup3->put_BottomOffset(0.6), S_OK);

   // test load modifier on support
   pMe->TestLoadModifier(pMe, psup3.p);

   // SuperstructureMembers
//===========================
   CComPtr<ISuperstructureMember> pssm0, pssm1, pssm2, pssm3;
   TRY_TEST(pssm0.CoCreateInstance( CLSID_SuperstructureMember ), S_OK );
   TRY_TEST(pssm1.CoCreateInstance( CLSID_SuperstructureMember ), S_OK );
   TRY_TEST(pssm2.CoCreateInstance( CLSID_SuperstructureMember ), S_OK );

   CComPtr<ISuperstructureMembers> pssms;
   TRY_TEST(psm->get_SuperstructureMembers(&pssms), S_OK);

   // add SuperstructureMember 0
   TRY_TEST(pssms->Add(pssm0), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST(pssm0->put_Length(5.0), S_OK);
   TEST_STIFFNESS_FIRED();

   TRY_TEST(pssm0->AddSegment(CComBSTR("Stage 1"), pseg1), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST(pssm0->AddSegment(CComBSTR("Stage 1"), pseg2), S_OK );
   TEST_STIFFNESS_FIRED();

   // add SuperstructureMember 1
   TRY_TEST(pssms->Add(pssm1), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST(pssm1->put_Length(4.3), S_OK);
   TEST_STIFFNESS_FIRED();

   TRY_TEST(pssm1->AddSegment(CComBSTR("Stage 1"), pseg1), S_OK );
   TEST_STIFFNESS_FIRED();

   // add SuperstructureMember 2
   TRY_TEST(pssms->Add(pssm2), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST(pssm2->put_Length(5.0), S_OK);
   TEST_STIFFNESS_FIRED();

   TRY_TEST(pssm2->AddSegment(CComBSTR("Stage 1"), pseg1), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST(pssm2->AddSegment(CComBSTR("Stage 1"), pseg2), S_OK );
   TEST_STIFFNESS_FIRED();

   // test offset member of ssms
   TRY_TEST(pssms->get_Offset(&d), S_OK);
   TRY_TEST(d, 0.0);
   TRY_TEST(pssms->put_Offset(1.0), S_OK);
   TRY_TEST(pssms->get_Offset(&d), S_OK);
   TRY_TEST(d, 1.0);
   TRY_TEST(pssms->put_Offset(-1.0), E_INVALIDARG);

   // check the length of our ssms
   TRY_TEST(pssms->get_Length(&d), S_OK);
   TRY_TEST(d, 14.3);

   // see if events bubble all the way from stress points
   // superstructuremember
   CComPtr<ISegment> ps1;
   TRY_TEST( pssm1->get_Segment(CComBSTR("Stage 1"), 0, &ps1), S_OK);
   CComPtr<ISegmentCrossSection> pcss;
   TRY_TEST( ps1->get_SegmentCrossSection(&pcss), S_OK);
   TRY_TEST( pcss->put_EADefl(23.3), S_OK);
   TEST_STIFFNESS_FIRED();
   CComPtr<IStressPoints> pspss;
   TRY_TEST( pcss->get_StressPoints(&pspss), S_OK);
   CComPtr<IStressPoint> psp;
   TRY_TEST( pspss->get_Item(0, &psp), S_OK);
   TRY_TEST( psp->put_Sa(3.14), S_OK);
   TEST_STRESS_FIRED();

   // support member
   CComPtr<ISegment> ps2;
   TRY_TEST( psup0->get_Segment(CComBSTR("Stage 1"), 1, &ps2), S_OK);
   CComPtr<ISegmentCrossSection> pcss1;
   TRY_TEST( ps2->get_SegmentCrossSection(&pcss1), S_OK);
   TRY_TEST( pcss1->put_EADefl(23.3), S_OK);
   TEST_STIFFNESS_FIRED();
   CComPtr<IStressPoints> psp1ss1;
   TRY_TEST( pcss1->get_StressPoints(&psp1ss1), S_OK);
   CComPtr<IStressPoint> psp1;
   TRY_TEST( psp1ss1->get_Item(0, &psp1), S_OK);
   TRY_TEST( psp1->put_Sa(3.14), S_OK);
   TEST_STRESS_FIRED();

   // test methods for getting spans and supports
   CComPtr<ISupport> lsup0, lsup2, lsupb;
   TRY_TEST(psm->LeftSupport(0, &lsup0), S_OK);
   TRY_TEST(lsup0.IsEqualObject(psup0), true);
   TRY_TEST(psm->LeftSupport(2, &lsup2), S_OK);
   TRY_TEST(lsup2.IsEqualObject(psup2), true);
   TRY_TEST(psm->LeftSupport(3, &lsupb), S_OK);
   TRY_TEST(!lsupb, true);

   CComPtr<ISupport> rsup1, rsup3, rsupb;
   TRY_TEST(psm->RightSupport(0, &rsup1), S_OK);
   TRY_TEST(rsup1.IsEqualObject(psup1), true);
   TRY_TEST(psm->RightSupport(2, &rsup3), S_OK);
   TRY_TEST(rsup3.IsEqualObject(psup3), true);
   TRY_TEST(psm->RightSupport(3, &rsupb), S_OK);
   TRY_TEST(!rsupb, true);

   CComPtr<ISpan> lspan1, lspan2, lspanb;
   TRY_TEST(psm->LeftSpan(0, &lspanb), S_OK);
   TRY_TEST(!lspanb, true);
   TRY_TEST(psm->LeftSpan(2, &lspan1), S_OK);
   TRY_TEST(lspan1.IsEqualObject(pspn1), true);
   TRY_TEST(psm->LeftSpan(3, &lspan2), S_OK);
   TRY_TEST(lspan2.IsEqualObject(pspn2), true);
   lspanb.Release();
   TRY_TEST(psm->LeftSpan(4, &lspanb), S_OK);
   TRY_TEST(!lspanb, true);

   CComPtr<ISpan> rspan0, rspan2, rspanb;
   TRY_TEST(psm->RightSpan(0, &rspan0), S_OK);
   TRY_TEST(rspan0.IsEqualObject(pspn0), true);
   TRY_TEST(psm->RightSpan(2, &rspan2), S_OK);
   TRY_TEST(rspan2.IsEqualObject(pspn2), true);
   TRY_TEST(psm->RightSpan(3, &rspanb), S_OK);
   TRY_TEST(!rspanb, true);

   // locations of various points in the structure.
   Float64 x, y;
   TRY_TEST(psm->ComputeLocation(0, mtSpan, 0.0, &x, &y), S_OK);
   TRY_TEST(x, 0.0);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(0, mtSpan, 1.0, &x, &y), S_OK);
   TRY_TEST(x, 1.0);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(0, mtSpan, -1.0, &x, &y), S_OK);
   TRY_TEST(x, 3.2);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(0, mtSpan, -0.5, &x, &y), S_OK);
   TRY_TEST(x, 1.6);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(0, mtSpan,  5.0, &x, &y), LBAM_E_LOCATION_OOR);
   TRY_TEST(psm->ComputeLocation(0, mtSpan, -1.1, &x, &y), LBAM_E_LOCATION_OOR);
   TRY_TEST(psm->ComputeLocation(2, mtSpan, 0.0, &x, &y), S_OK);
   TRY_TEST(IsEqual(x, 9.1), true);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(2, mtSpan, 1.0, &x, &y), S_OK);
   TRY_TEST(IsEqual(x, 10.1), true);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(2, mtSpan, -1.0, &x, &y), S_OK);
   TRY_TEST(IsEqual(x, 12.3), true);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(2, mtSpan, -0.5, &x, &y), S_OK);
   TRY_TEST(IsEqual(x, 10.7), true);
   TRY_TEST(y, 0.0);

   TRY_TEST(psm->ComputeLocation(0, mtSuperstructureMember, 0.0, &x, &y), S_OK);
   TRY_TEST(x,-1.0);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(0, mtSuperstructureMember, 1.0, &x, &y), S_OK);
   TRY_TEST(x, 0.0);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(0, mtSuperstructureMember, -1.0, &x, &y), S_OK);
   TRY_TEST(x, 4.0);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(0, mtSuperstructureMember, -0.5, &x, &y), S_OK);
   TRY_TEST(x, 1.5);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(0, mtSuperstructureMember,  6.0, &x, &y), LBAM_E_LOCATION_OOR);
   TRY_TEST(psm->ComputeLocation(0, mtSuperstructureMember, -1.1, &x, &y), LBAM_E_LOCATION_OOR);
   TRY_TEST(psm->ComputeLocation(2, mtSuperstructureMember, 0.0, &x, &y), S_OK);
   TRY_TEST(x, 8.3);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(2, mtSuperstructureMember, 2.0, &x, &y), S_OK);
   TRY_TEST(x,10.3);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(2, mtSuperstructureMember, -1.0, &x, &y), S_OK);
   TRY_TEST(x,13.3);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(2, mtSuperstructureMember, -0.5, &x, &y), S_OK);
   TRY_TEST(x,10.8);
   TRY_TEST(y, 0.0);

   TRY_TEST(psm->ComputeLocation(0, mtSupport, 0.0, &x, &y), S_OK);
   TRY_TEST(x, 0.0);
   TRY_TEST(y, -1.2);
   TRY_TEST(psm->ComputeLocation(0, mtSupport, 1.0, &x, &y), S_OK);
   TRY_TEST(x, 0.0);
   TRY_TEST(IsEqual(y, -0.2), true);
   TRY_TEST(psm->ComputeLocation(0, mtSupport, -1.0, &x, &y), S_OK);
   TRY_TEST(x, 0.0);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(0, mtSupport, -0.5, &x, &y), S_OK);
   TRY_TEST(x, 0.0);
   TRY_TEST(IsEqual(y,-0.6), true);
   TRY_TEST(psm->ComputeLocation(0, mtSupport,  5.0, &x, &y), LBAM_E_LOCATION_OOR);
   TRY_TEST(psm->ComputeLocation(0, mtSupport, -1.1, &x, &y), LBAM_E_LOCATION_OOR);

   TRY_TEST(psm->ComputeLocation(1, mtSupport, 0.0, &x, &y), S_OK);
   TRY_TEST(x, 3.2);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(1, mtSupport,  1.0, &x, &y), LBAM_E_LOCATION_OOR);

   TRY_TEST(psm->ComputeLocation(3, mtSupport, 0.0, &x, &y), S_OK);
   TRY_TEST(x,12.9);
   TRY_TEST(IsEqual(y,-1.0392304845413), true);
   TRY_TEST(psm->ComputeLocation(3, mtSupport, 1.0, &x, &y), S_OK);
   TRY_TEST(x, 12.4);
   TRY_TEST(IsEqual(y, -0.17320508075689), true);
   TRY_TEST(psm->ComputeLocation(3, mtSupport, -1.0, &x, &y), S_OK);
   TRY_TEST(x, 12.3);
   TRY_TEST(y,  0.0);
   TRY_TEST(psm->ComputeLocation(3, mtSupport, -0.5, &x, &y), S_OK);
   TRY_TEST(IsEqual(x, 12.6), true);
   TRY_TEST(IsEqual(y,-0.51961524227066), true);
   TRY_TEST(psm->ComputeLocation(3, mtSupport,  5.0, &x, &y), LBAM_E_LOCATION_OOR);
   TRY_TEST(psm->ComputeLocation(3, mtSupport, -1.1, &x, &y), LBAM_E_LOCATION_OOR);

   // temporary supports
   TRY_TEST(psm->ComputeLocation(21, mtTemporarySupport, 0.0, &x, &y), S_OK);
   TRY_TEST(x,1.0);
   TRY_TEST(IsEqual(y,-1.0), true);
   TRY_TEST(psm->ComputeLocation(21, mtTemporarySupport, 1.0, &x, &y), S_OK);
   TRY_TEST(IsEqual(x, 1.707106), true);
   TRY_TEST(IsEqual(y, -0.2928932188), true);
   TRY_TEST(psm->ComputeLocation(21, mtTemporarySupport, -1.0, &x, &y), S_OK);
   TRY_TEST(x, 2.0);
   TRY_TEST(y, 0.0);
   TRY_TEST(psm->ComputeLocation(21, mtTemporarySupport, -0.5, &x, &y), S_OK);
   TRY_TEST(IsEqual(x, 1.5), true);
   TRY_TEST(IsEqual(y,-0.5), true);
   TRY_TEST(psm->ComputeLocation(21, mtTemporarySupport,  5.0, &x, &y), LBAM_E_LOCATION_OOR);
   TRY_TEST(psm->ComputeLocation(21, mtTemporarySupport, -1.1, &x, &y), LBAM_E_LOCATION_OOR);

   TRY_TEST(psm->ComputeLocation(22, mtTemporarySupport, 0.0, &x, &y), S_OK);
   TRY_TEST(IsEqual(x,10.7), true);
   TRY_TEST(IsEqual(y,0.0), true);
   TRY_TEST(psm->ComputeLocation(22, mtTemporarySupport,  1.0, &x, &y), LBAM_E_LOCATION_OOR);

   TRY_TEST(psm->ComputeLocation(0, mtTemporarySupport, 0.0, &x, &y), LBAM_E_TEMPSUPPORT_NOT_EXIST);
   TRY_TEST(psm->ComputeLocation(0, mtUndefined, 0.0, &x, &y), LBAM_E_INVALID_MEMBERTYPE);

   // stages
   CComPtr<IStages> pStages;
   TRY_TEST(psm->get_Stages(&pStages), S_OK);

   CComPtr<IStage> pStage1, pStage2;
   TRY_TEST(pStage1.CoCreateInstance( CLSID_Stage ), S_OK );
   TRY_TEST(pStage2.CoCreateInstance( CLSID_Stage ), S_OK );
   TRY_TEST( pStage1->put_Name(CComBSTR("Stage 1")), S_OK );
   TRY_TEST( pStage2->put_Name(CComBSTR("Stage 2")), S_OK );

   TRY_TEST(pStages->Add(pStage1), S_OK);
   TEST_STAGE_FIRED();
   TRY_TEST(pStages->Add(pStage2), S_OK);
   TEST_STAGE_FIRED();

   // POIs
   CComPtr<IPOIs> pPOIs;
   TRY_TEST(psm->get_POIs(&pPOIs), S_OK);

   CComPtr<IPOI> pPOI1, pPOI2;
   TRY_TEST(pPOI1.CoCreateInstance( CLSID_POI ), S_OK );
   TRY_TEST(pPOI2.CoCreateInstance( CLSID_POI ), S_OK );
   TRY_TEST( pPOI1->put_ID(101), S_OK );
   TRY_TEST( pPOI1->put_MemberType(mtSpan), S_OK );
   TRY_TEST( pPOI1->put_MemberID(0), S_OK );
   TRY_TEST( pPOI1->put_Location(1.2), S_OK );

   TRY_TEST( pPOI2->put_ID(102), S_OK );

   TRY_TEST(pPOIs->Add(pPOI1), S_OK);
   TEST_POI_FIRED();
   TRY_TEST(pPOIs->Add(pPOI2), S_OK);
   TEST_POI_FIRED();

   TRY_TEST( pPOI2->put_MemberType(mtSupport), S_OK );
   TEST_POI_FIRED();
   TRY_TEST( pPOI2->put_MemberID(1), S_OK );
   TEST_POI_FIRED();
   TRY_TEST( pPOI2->put_Location(3.0), S_OK );
   TEST_POI_FIRED();

   // Load Groups
   CComPtr<ILoadGroups> pLoadGroups;
   TRY_TEST(psm->get_LoadGroups(&pLoadGroups), S_OK);

   CComPtr<ILoadGroup> pLoadGroup1, pLoadGroup2;
   TRY_TEST(pLoadGroup1.CoCreateInstance( CLSID_LoadGroup ), S_OK );
   TRY_TEST(pLoadGroup2.CoCreateInstance( CLSID_LoadGroup ), S_OK );
   TRY_TEST( pLoadGroup1->put_Name(CComBSTR("LoadGroup 1")), S_OK );
   TRY_TEST( pLoadGroup2->put_Name(CComBSTR("LoadGroup 2")), S_OK );

   TRY_TEST(pLoadGroups->Add(pLoadGroup1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pLoadGroups->Add(pLoadGroup2), S_OK);
   TEST_LOAD_FIRED();

   TRY_TEST( pLoadGroup1->put_Description(CComBSTR("Description of LoadGroup 1")), S_OK );
   TEST_DESCRIPTION_FIRED();
   TRY_TEST( pLoadGroup2->put_Description(CComBSTR("Description of LoadGroup 2")), S_OK );
   TEST_DESCRIPTION_FIRED();

   // Point Loads
   CComPtr<IPointLoads> pPointLoads;
   TRY_TEST(psm->get_PointLoads(&pPointLoads), S_OK);

   CComPtr<IPointLoad> pPointLoad1, pPointLoad2;
   TRY_TEST(pPointLoad1.CoCreateInstance( CLSID_PointLoad ), S_OK );
   TRY_TEST(pPointLoad2.CoCreateInstance( CLSID_PointLoad ), S_OK );

   CComPtr<IPointLoadItem> pPLI1, pPLI2;
   TRY_TEST(pPointLoads->Add(CComBSTR("Stage 1"), CComBSTR("LoadGroup 1"), pPointLoad1, &pPLI1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pPointLoads->Add(CComBSTR("Stage 2"), CComBSTR("LoadGroup 2"), pPointLoad2, &pPLI2), S_OK);
   TEST_LOAD_FIRED();

   TRY_TEST(pPointLoad1->put_MemberType(mtSpan), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pPointLoad1->put_MemberID(1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pPointLoad1->put_Location(-.3), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pPointLoad1->SetForce(1,2,3), S_OK);
   TEST_LOAD_FIRED();

   TRY_TEST(pPointLoad2->put_MemberType(mtSupport), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pPointLoad2->put_MemberID(2), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pPointLoad2->put_Fy(-1.1), S_OK);
   TEST_LOAD_FIRED();

   // Distributed Loads
   CComPtr<IDistributedLoads> pDistributedLoads;
   TRY_TEST(psm->get_DistributedLoads(&pDistributedLoads), S_OK);

   CComPtr<IDistributedLoad> pDistributedLoad1, pDistributedLoad2, pDistributedLoad3;
   TRY_TEST(pDistributedLoad1.CoCreateInstance( CLSID_DistributedLoad ), S_OK );
   TRY_TEST(pDistributedLoad2.CoCreateInstance( CLSID_DistributedLoad ), S_OK );
   TRY_TEST(pDistributedLoad3.CoCreateInstance( CLSID_DistributedLoad ), S_OK );

   CComPtr<IDistributedLoadItem> pDLI1, pDLI2, pDLI3;
   TRY_TEST(pDistributedLoads->Add(CComBSTR("Stage 1"), CComBSTR("LoadGroup 1"), pDistributedLoad1, &pDLI1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoads->Add(CComBSTR("Stage 2"), CComBSTR("LoadGroup 1"), pDistributedLoad2, &pDLI2), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoads->Add(CComBSTR("Stage 1"), CComBSTR("LoadGroup 2"), pDistributedLoad3, &pDLI3), S_OK);
   TEST_LOAD_FIRED();

   TRY_TEST(pDistributedLoad1->put_MemberType(mtSpan), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad1->put_MemberID(1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad1->put_Direction(ldFy), S_OK);
// TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad1->put_WStart(-0.1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad1->put_WEnd(-0.3), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad1->put_StartLocation(-0.2), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad1->put_EndLocation(-0.8), S_OK);
   TEST_LOAD_FIRED();

   TRY_TEST(pDistributedLoad2->put_MemberType(mtSuperstructureMember), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad2->put_MemberID(1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad2->put_Direction(ldFx), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad2->put_WStart(-0.3), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad2->put_WEnd(-0.4), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad2->put_StartLocation(-0.0), S_OK);
// TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad2->put_EndLocation(-1.0), S_OK);
   TEST_LOAD_FIRED();

   TRY_TEST(pDistributedLoad3->put_MemberType(mtTemporarySupport), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad3->put_MemberID(1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad3->put_Direction(ldFy), S_OK);
// TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad3->put_WStart(-0.3), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad3->put_WEnd(-0.4), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad3->put_StartLocation(-0.1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pDistributedLoad3->put_EndLocation(-1.0), S_OK);
   TEST_LOAD_FIRED();

   // Strain Loads
   CComPtr<IStrainLoads> pStrainLoads;
   TRY_TEST(psm->get_StrainLoads(&pStrainLoads), S_OK);

   CComPtr<IStrainLoad> pStrainLoad1, pStrainLoad2;
   TRY_TEST(pStrainLoad1.CoCreateInstance( CLSID_StrainLoad ), S_OK );
   TRY_TEST(pStrainLoad2.CoCreateInstance( CLSID_StrainLoad ), S_OK );

   CComPtr<IStrainLoadItem> pSLI1, pSLI2;
   TRY_TEST(pStrainLoads->Add(CComBSTR("Stage 1"), CComBSTR("LoadGroup 1"), pStrainLoad1, &pSLI1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pStrainLoads->Add(CComBSTR("Stage 2"), CComBSTR("LoadGroup 2"), pStrainLoad2, &pSLI2), S_OK);
   TEST_LOAD_FIRED();

   TRY_TEST(pStrainLoad1->put_MemberType(mtSpan), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pStrainLoad1->put_MemberID(1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pStrainLoad1->put_AxialStrain(-0.002), S_OK);
   TEST_LOAD_FIRED();

   TRY_TEST(pStrainLoad2->put_MemberType(mtSupport), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pStrainLoad2->put_MemberID(2), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pStrainLoad2->put_CurvatureStrain(0.0000012), S_OK);
   TEST_LOAD_FIRED();

   // Temperature Loads
   CComPtr<ITemperatureLoads> pTemperatureLoads;
   TRY_TEST(psm->get_TemperatureLoads(&pTemperatureLoads), S_OK);

   CComPtr<ITemperatureLoad> pTemperatureLoad1, pTemperatureLoad2;
   TRY_TEST(pTemperatureLoad1.CoCreateInstance( CLSID_TemperatureLoad ), S_OK );
   TRY_TEST(pTemperatureLoad2.CoCreateInstance( CLSID_TemperatureLoad ), S_OK );

   CComPtr<ITemperatureLoadItem> pTLI1, pTLI2;
   TRY_TEST(pTemperatureLoads->Add(CComBSTR("Stage 1"), CComBSTR("LoadGroup 1"), pTemperatureLoad1, &pTLI1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pTemperatureLoads->Add(CComBSTR("Stage 2"), CComBSTR("LoadGroup 2"), pTemperatureLoad2, &pTLI2), S_OK);
   TEST_LOAD_FIRED();

   TRY_TEST(pTemperatureLoad1->put_MemberType(mtSpan), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pTemperatureLoad1->put_MemberID(1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pTemperatureLoad1->put_TTop(12), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pTemperatureLoad1->put_TBottom(-12), S_OK);
   TEST_LOAD_FIRED();

   TRY_TEST(pTemperatureLoad2->put_MemberType(mtSupport), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pTemperatureLoad2->put_MemberID(2), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pTemperatureLoad2->put_TTop(1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pTemperatureLoad2->put_TBottom(1), S_OK);
   TEST_LOAD_FIRED();

   // Settlement Loads
   CComPtr<ISettlementLoads> pSettlementLoads;
   TRY_TEST(psm->get_SettlementLoads(&pSettlementLoads), S_OK);

   CComPtr<ISettlementLoad> pSettlementLoad1;
   TRY_TEST(pSettlementLoad1.CoCreateInstance( CLSID_SettlementLoad ), S_OK );

   CComPtr<ISettlementLoadItem> pSTI1;
   TRY_TEST(pSettlementLoads->Add(CComBSTR("Stage 1"), CComBSTR("LoadGroup 1"), pSettlementLoad1, &pSTI1), S_OK);
   TEST_LOAD_FIRED();

   TRY_TEST(pSettlementLoad1->put_MemberID(1), S_OK);
   TEST_LOAD_FIRED();
   TRY_TEST(pSettlementLoad1->put_Dy(-0.002), S_OK);
   TEST_LOAD_FIRED();

   // Live Load
   CComPtr<ILiveLoad> pLiveLoad;
   TRY_TEST(psm->get_LiveLoad(&pLiveLoad), S_OK);

   CComPtr<ILiveLoadModel> pDeflectionLLM;
   TRY_TEST(pLiveLoad->get_Deflection(&pDeflectionLLM), S_OK);
   pMe->TestLLM(pDeflectionLLM);

   CComPtr<ILiveLoadModel> pDesignLLM;
   TRY_TEST(pLiveLoad->get_Design(&pDesignLLM), S_OK);
   pMe->TestLLM(pDesignLLM);

   CComPtr<ILiveLoadModel> pFatigueLLM;
   TRY_TEST(pLiveLoad->get_Fatigue(&pFatigueLLM), S_OK);
   pMe->TestLLM(pFatigueLLM);

   CComPtr<ILiveLoadModel> pPedestrianLLM;
   TRY_TEST(pLiveLoad->get_Pedestrian(&pPedestrianLLM), S_OK);
   pMe->TestLLM(pPedestrianLLM);

   CComPtr<ILiveLoadModel> pPermitLLM;
   TRY_TEST(pLiveLoad->get_Permit(&pPermitLLM), S_OK);
   pMe->TestLLM(pPermitLLM);

   CComPtr<ILiveLoadModel> pSpecialLLM;
   TRY_TEST(pLiveLoad->get_Special(&pSpecialLLM), S_OK);
   pMe->TestLLM(pSpecialLLM);

   // Distribution Factors
   CComPtr<IDistributionFactors> pgs;
   TRY_TEST(psm->get_DistributionFactors(&pgs), S_OK);

   CollectionIndexType cnt;
   TRY_TEST(pgs->get_Count(&cnt), S_OK);
   TRY_TEST(cnt,0);

   CComPtr<IDistributionFactorSegment> pgs0;
   TRY_TEST( pgs0.CoCreateInstance( CLSID_DistributionFactorSegment ) , S_OK );

   TRY_TEST(pgs->Add(pgs0), S_OK);
   TEST_DF_FIRED();
   TRY_TEST(pgs->get_Count(&cnt), S_OK);
   TRY_TEST(cnt,1);

   CComPtr<IDistributionFactor> pg0, pg1;
   Float64 g1=2, g2=g1+.1,g3=g2+.1,g4=g3+.1,g5=g4+.1,g6=g5+.1,g7=g6+.1;
   Float64       g8=g7+.1,g9=g8+.1,g10=g9+.1,g11=g10+.1,g12=g11+.1,g13=g12+.1,g14=g13+.1,g15=g14+.1;
   TRY_TEST( pg0.CoCreateInstance( CLSID_DistributionFactor ) , S_OK );
   TRY_TEST( pg0->SetG(g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, g11, g12, g13, g14, g15), S_OK);

   TRY_TEST(pgs0->putref_DistributionFactor(pg0), S_OK);
   TEST_DF_FIRED();
   TRY_TEST(pgs0->put_Length(10.0), S_OK);
   TEST_DF_FIRED();

   TRY_TEST( pg0->put_GPMSgl(1.11), S_OK);
   TEST_DF_FIRED();

   // LoadCases
   CComPtr<ILoadCases> pLoadCases;
   TRY_TEST(psm->get_LoadCases(&pLoadCases), S_OK);

   CComPtr<ILoadCase> pLoadCase1, pLoadCase2;
   TRY_TEST(pLoadCase1.CoCreateInstance( CLSID_LoadCase ), S_OK );
   TRY_TEST(pLoadCase2.CoCreateInstance( CLSID_LoadCase ), S_OK );
   TRY_TEST( pLoadCase1->put_Name(CComBSTR("LoadCase 1")), S_OK );
   TRY_TEST( pLoadCase2->put_Name(CComBSTR("LoadCase 2")), S_OK );

   TRY_TEST(pLoadCases->Add(pLoadCase1), S_OK);
   TEST_COMBO_FIRED();
   TRY_TEST(pLoadCases->Add(pLoadCase2), S_OK);
   TEST_COMBO_FIRED();

   TRY_TEST( pLoadCase1->put_Description(CComBSTR("Description of LoadCase 1")), S_OK );
   TEST_DESCRIPTION_FIRED();
   TRY_TEST( pLoadCase2->put_Description(CComBSTR("Description of LoadCase 2")), S_OK );
   TEST_DESCRIPTION_FIRED();

   TRY_TEST( pLoadCase1->AddLoadGroup(CComBSTR("LoadGroup 1")), S_OK );
   TEST_COMBO_FIRED();
   TRY_TEST( pLoadCase2->AddLoadGroup(CComBSTR("LoadGroup 2")), S_OK );
   TEST_COMBO_FIRED();

   CComVariant ivar=2;
   TRY_TEST( pLoadCase2->put_ItemData(ivar), S_OK );
   TEST_USER_DATA_FIRED();

   // LoadCombinations
   CComPtr<ILoadCombinations> pLoadCombinations;
   TRY_TEST(psm->get_LoadCombinations(&pLoadCombinations), S_OK);

   CComPtr<ILoadCombination> pLoadCombination1, pLoadCombination2;
   TRY_TEST(pLoadCombination1.CoCreateInstance( CLSID_LoadCombination ), S_OK );
   TRY_TEST(pLoadCombination2.CoCreateInstance( CLSID_LoadCombination ), S_OK );
   TRY_TEST( pLoadCombination1->put_Name(CComBSTR("LoadCombination 1")), S_OK );
   TRY_TEST( pLoadCombination2->put_Name(CComBSTR("LoadCombination 2")), S_OK );

   TRY_TEST(pLoadCombinations->Add(pLoadCombination1), S_OK);
   TEST_COMBO_FIRED();
   TRY_TEST(pLoadCombinations->Add(pLoadCombination2), S_OK);
   TEST_COMBO_FIRED();

   TRY_TEST( pLoadCombination1->put_Description(CComBSTR("Description of LoadCombination 1")), S_OK );
   TEST_DESCRIPTION_FIRED();
   TRY_TEST( pLoadCombination2->put_Description(CComBSTR("Description of LoadCombination 2")), S_OK );
   TEST_DESCRIPTION_FIRED();

   TRY_TEST( pLoadCombination1->AddLoadCaseFactor(CComBSTR("LoadCase 1"), 0.8, 1.3), S_OK );
   TEST_COMBO_FIRED();
   TRY_TEST( pLoadCombination2->AddLoadCaseFactor(CComBSTR("LoadCase 2"), 0.9, 1.4), S_OK );
   TEST_COMBO_FIRED();

   TRY_TEST( pLoadCombination2->put_ItemData(ivar), S_OK );
   TEST_USER_DATA_FIRED();


   /////////////////////////////////////////////////////////////////////
   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestModel"), 1.0);

      // get interface pointer to Save our cross section
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( psm.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a new member to work with
      CComPtr<ILBAMModel> psm2;
      TRY_TEST(psm2.CoCreateInstance( CLSID_LBAMModel ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestModel"));

         IStructuredStorage2* piss2=NULL;
         TRY_TEST( psm2.QueryInterface(&piss2), S_OK);

         // Load 
         TRY_TEST( piss2->Load(psl), S_OK );

         piss2->Release();

         VARIANT_BOOL end;
         hr = psl->EndUnit(&end);

         TRY_TEST( psl->Close(), S_OK );

         // now save to a different file so we can compare files
         CComPtr<IStructuredSave2> pss2;
         TRY_TEST( pss2.CoCreateInstance( CLSID_StructuredSave2 ), S_OK );
         TRY_TEST( pss2->Open( CComBSTR("Test2.xml")), S_OK );

         // save our loaded version
         hr = pss2->BeginUnit(CComBSTR("TestModel"), 1.0);
         TRY_TEST( piss2->Save(pss2), S_OK );
         hr = pss2->EndUnit();
         TRY_TEST( pss2->Close(), S_OK );
      }
   }

   // compare two files by comparing strings. note that xml parser based files have only two lines
   // the first line is the xml processing instruction and the second line is all of the data
   // for this simple case we can simply compare the two data strings. For huge files, we
   // might have to resort to less memory intensive methods.
   try
   {
      std::_tstring x1;
      std::_tifstream if1("Test.xml");
      std::getline(if1, x1);
      std::getline(if1, x1); // second line is the data

      std::_tstring x2;
      std::_tifstream if2("Test2.xml");
      std::getline(if2, x2);
      std::getline(if2, x2);

      TRY_TEST( x1, x2 );

   }
   catch(...)
   {
      ATLASSERT(0); // big problems
      TRY_TEST(0,1); 
   }

   // Clone our model
   CComPtr<ILBAMModel> psmc;
   TRY_TEST(psm->Clone(&psmc), S_OK);

   // rough comparison between clone and original
   // they won't be exact since clone is deep
   ModelStats smdl, sclone;
   ComputeModelStatistics(psm,  &smdl);
   ComputeModelStatistics(psmc, &sclone);
   TRY_TEST(smdl, sclone);

   // remove some stage data
   TRY_TEST(psmc->RemoveStage(CComBSTR("Stage 1")), S_OK);
   TRY_TEST(psmc->RemoveStage(CComBSTR("bogus Stage")), LBAM_E_STAGE_NOT_EXISTS);

   // Clear our clone and check for left overs
   TRY_TEST(psmc->Clear(), S_OK);

   ComputeModelStatistics(psmc, &sclone);
   TRY_TEST( sclone.MemberLengths, 0.0);
   TRY_TEST( sclone.NumSpans , 0);
   TRY_TEST( sclone.NumSuperstructureMembers , 0);
   TRY_TEST( sclone.NumSupports, 0);
   TRY_TEST( sclone.SpanLengths , 0.0);

   // disconnect our connections
   TRY_TEST(AtlUnadvise(psm,IID_ILBAMModelEvents,dwCookie),S_OK);
   pMe->Release();
}


HRESULT CTestModel::OnModelChanged(ILBAMModel* Model, ChangeType change)
{
   if (change==cgtStiffness)
      m_csStiffnessFired = true;
   else if (change==cgtStress)
      m_csStressPointsFired = true;
   else if (change==cgtCombination)
      m_csCombinationFired = true;
   else if (change==cgtStage || change==cgtStageOrder)
      m_csStageFired = true;
   else if (change==cgtPOI)
      m_csPOIFired = true;
   else if (change==cgtLoads)
      m_csLoadFired = true;
   else if (change==cgtDescription)
      m_csDescriptionFired = true;
   else if (change==cgtLiveLoad)
      m_csLiveLoadFired = true;
   else if (change==cgtUserItemData)
      m_csUserDataFired = true;
   else if (change==cgtDistributionFactor)
      m_csDfDataFired = true;
   else
      ATLASSERT(0);

   return S_OK;
}

void ComputeModelStatistics(ILBAMModel* pmodel, ModelStats* pstats)
{
   CollectionIndexType cnt=0;
   Float64 len;

   CComPtr<ISuperstructureMembers> pssms;
   pmodel->get_SuperstructureMembers(&pssms);
   pssms->get_Count(&cnt);
   pstats->NumSuperstructureMembers = cnt;
   pssms->get_Length(&len);
   pstats->MemberLengths = len;

   SpanIndexType nSpans;
   CComPtr<ISpans> pspns;
   pmodel->get_Spans(&pspns);
   pspns->get_Count(&nSpans);
   pstats->NumSpans = nSpans;
   pspns->get_Length(&len);
   pstats->SpanLengths = len;


   SupportIndexType nSupports;
   CComPtr<ISupports> psups;
   pmodel->get_Supports(&psups);
   psups->get_Count(&nSupports);
   pstats->NumSupports = nSupports;

   StageIndexType nStages;
   CComPtr<IStages> pStages;
   pmodel->get_Stages(&pStages);
   pStages->get_Count(&nStages);
   pstats->NumStages = nStages;

   CComPtr<ILoadGroups> pLoadGroups;
   pmodel->get_LoadGroups(&pLoadGroups);
   pLoadGroups->get_Count(&cnt);
   pstats->NumLoadGroups = cnt;

   CComPtr<ILoadCases> pLoadCases;
   pmodel->get_LoadCases(&pLoadCases);
   pLoadCases->get_Count(&cnt);
   pstats->NumLoadCases = cnt;

   CComPtr<ILoadCombinations> pLoadCombinations;
   pmodel->get_LoadCombinations(&pLoadCombinations);
   pLoadCombinations->get_Count(&cnt);
   pstats->NumLoadCombinations = cnt;

   CComPtr<IPointLoads> pPointLoads;
   pmodel->get_PointLoads(&pPointLoads);
   pPointLoads->get_Count(&cnt);
   pstats->NumPointLoads = cnt;

   CComPtr<IDistributedLoads> pDistributedLoads;
   pmodel->get_DistributedLoads(&pDistributedLoads);
   pDistributedLoads->get_Count(&cnt);
   pstats->NumDistributedLoads = cnt;

   CComPtr<ITemperatureLoads> pTemperatureLoads;
   pmodel->get_TemperatureLoads(&pTemperatureLoads);
   pTemperatureLoads->get_Count(&cnt);
   pstats->NumTemperatureLoads = cnt;

   CComPtr<ISettlementLoads> pSettlementLoads;
   pmodel->get_SettlementLoads(&pSettlementLoads);
   pSettlementLoads->get_Count(&cnt);
   pstats->NumSettlementLoads = cnt;

   CComPtr<IStrainLoads> pStrainLoads;
   pmodel->get_StrainLoads(&pStrainLoads);
   pStrainLoads->get_Count(&cnt);
   pstats->NumStrainLoads = cnt;
}

void CTestModel::TestLLM(ILiveLoadModel* pllm)
{
   CTestModel* pMe = this;

   CComPtr<IVehicularLoads> ivs;
   TRY_TEST( pllm->get_VehicularLoads(&ivs), S_OK);

   VehicleIndexType cnt;
   TRY_TEST(ivs->get_Count(&cnt), S_OK);
   TRY_TEST(cnt, 0);

   CComPtr<IVehicularLoad> iv;
   TRY_TEST(iv.CoCreateInstance(CLSID_VehicularLoad), S_OK);
   TRY_TEST(iv->put_Name(CComBSTR("My Vehicle")), S_OK);
   TRY_TEST(ivs->Add(iv),S_OK);
   TEST_LIVELOAD_FIRED();

   TRY_TEST(iv->put_IMLane(.33), S_OK);
   TEST_LIVELOAD_FIRED();
   TRY_TEST(iv->put_Applicability(llaContraflexure), S_OK);
   TEST_LIVELOAD_FIRED();

   CComPtr<IAxles> axls;
   TRY_TEST(iv->get_Axles(&axls), S_OK);
   TRY_TEST(axls->get_Count(&cnt), S_OK);
   TRY_TEST(cnt,0);

   CComPtr<IAxle> axl1, axl2;
   TRY_TEST(axl1.CoCreateInstance(CLSID_Axle), S_OK);
   TRY_TEST(axl2.CoCreateInstance(CLSID_Axle), S_OK);

   TRY_TEST(axls->Add(axl1), S_OK);
   TEST_LIVELOAD_FIRED();
   TRY_TEST(axl1->put_Weight(32), S_OK);
   TEST_LIVELOAD_FIRED();
   TRY_TEST(axl1->put_Spacing(14), S_OK);
   TEST_LIVELOAD_FIRED();

   TRY_TEST(axls->Add(axl2), S_OK);
   TEST_LIVELOAD_FIRED();
   TRY_TEST(axl2->put_Weight(32), S_OK);
   TEST_LIVELOAD_FIRED();
}


template <class T>
void CTestModel::TestLoadModifier(CTestModel* pMe, T* thingWithLm)
{
   Float64 dmin, dmax;
   TRY_TEST(thingWithLm->GetLoadModifier(lctStrength,&dmin, &dmax), S_OK);
   TRY_TEST(dmin, 1.0);
   TRY_TEST(dmax, 1.0);
   TRY_TEST(thingWithLm->GetLoadModifier(lctService,&dmin, &dmax), S_OK);
   TRY_TEST(dmin, 1.0);
   TRY_TEST(dmax, 1.0);
   TRY_TEST(thingWithLm->GetLoadModifier(lctExtremeEvent,&dmin, &dmax), S_OK);
   TRY_TEST(dmin, 1.0);
   TRY_TEST(dmax, 1.0);
   TRY_TEST(thingWithLm->GetLoadModifier(lctFatigue,&dmin, &dmax), S_OK);
   TRY_TEST(dmin, 1.0);
   TRY_TEST(dmax, 1.0);
   TRY_TEST(thingWithLm->GetLoadModifier(lctPermit,&dmin, &dmax), S_OK);
   TRY_TEST(dmin, 1.0);
   TRY_TEST(dmax, 1.0);
   TRY_TEST(thingWithLm->GetLoadModifier(lctUserDefined,&dmin, &dmax), S_OK);
   TRY_TEST(dmin, 1.0);
   TRY_TEST(dmax, 1.0);
   TRY_TEST(thingWithLm->SetLoadModifier(lctStrength,1.2, 1.21), S_OK);
   TEST_COMBO_FIRED();
   TRY_TEST(thingWithLm->SetLoadModifier(lctService,1.3, 1.31), S_OK);
   TEST_COMBO_FIRED();
   TRY_TEST(thingWithLm->SetLoadModifier(lctExtremeEvent,1.4, 1.41), S_OK);
   TEST_COMBO_FIRED();
   TRY_TEST(thingWithLm->SetLoadModifier(lctFatigue,1.5, 1.51), S_OK);
   TEST_COMBO_FIRED();
   TRY_TEST(thingWithLm->SetLoadModifier(lctPermit,1.6, 1.61), S_OK);
   TEST_COMBO_FIRED();
   TRY_TEST(thingWithLm->SetLoadModifier(lctUserDefined,1.7, 1.71), S_OK);
   TEST_COMBO_FIRED();
   TRY_TEST(thingWithLm->GetLoadModifier(lctStrength,&dmin, &dmax), S_OK);
   TRY_TEST(dmin, 1.2);
   TRY_TEST(dmax, 1.21);
   TRY_TEST(thingWithLm->GetLoadModifier(lctService,&dmin, &dmax), S_OK);
   TRY_TEST(dmin, 1.3);
   TRY_TEST(dmax, 1.31);
   TRY_TEST(thingWithLm->GetLoadModifier(lctExtremeEvent,&dmin, &dmax), S_OK);
   TRY_TEST(dmin, 1.4);
   TRY_TEST(dmax, 1.41);
   TRY_TEST(thingWithLm->GetLoadModifier(lctFatigue,&dmin, &dmax), S_OK);
   TRY_TEST(dmin, 1.5);
   TRY_TEST(dmax, 1.51);
   TRY_TEST(thingWithLm->GetLoadModifier(lctPermit,&dmin, &dmax), S_OK);
   TRY_TEST(dmin, 1.6);
   TRY_TEST(dmax, 1.61);
   TRY_TEST(thingWithLm->GetLoadModifier(lctUserDefined,&dmin, &dmax), S_OK);
   TRY_TEST(dmin, 1.7);
   TRY_TEST(dmax, 1.71);

   TRY_TEST(thingWithLm->SetLoadModifier(lctStrength,-1.2, 1.0), E_INVALIDARG);
   TRY_TEST(thingWithLm->SetLoadModifier(lctService,1.0, -1.3), E_INVALIDARG);

}

