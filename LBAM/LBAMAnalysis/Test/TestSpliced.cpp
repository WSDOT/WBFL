///////////////////////////////////////////////////////////////////////
// LBAM Analysis Test - Test driver for LBAM analysis library
// Copyright © 1999-2012  Washington State Department of Transportation
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

// TestSpliced.cpp: implementation of the CTestSpliced class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSpliced.h"
#include "..\AnalysisUtils.h"
#include <fstream>

#include "TestUtils.h"
#include "..\..\LBAMTestUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void SetupSegment(ISegment* pseg, Float64 A, Float64 I, Float64 E, Float64 depth);
static const long TS_ID=12;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestSpliced::CTestSpliced()
{

}

CTestSpliced::~CTestSpliced()
{

}

HRESULT CTestSpliced::Test()
{
   // dump results to a file
   std::_tofstream os("Spliced.txt");

   // build a model and attach it to our load group response object
   CComPtr<ILoadGroupResponse> plgr;
   plgr.CoCreateInstance(CLSID_LoadGroupForceResponse);
//   plgr.CoCreateInstance(CLSID_LoadGroupDeflectionResponse);

   // most of the work building the model happens here
   CComPtr<ILBAMModel> psm;
   psm.Attach( CreateModel() );

   HRESULT hr;
   CComQIPtr<IDependOnLBAM> pctx(plgr);
   hr = pctx->putref_Model(psm);

   // request results for tenth points in spans 0 and 1
   CComPtr<IIDArray> poilist;
   poilist.CoCreateInstance(CLSID_IDArray);
   for (PoiIDType i=0; i<11; i++)
   {
      poilist->Add(i+101);
   }
   for (PoiIDType i=0; i<11; i++)
   {
      poilist->Add(i+201);
   }

   // save input file off
   /////////////////////////////////////////////////////////////////////
   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("TestSpliced.xml")), S_OK );

      // get interface pointer to Save
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( psm.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );
      TRY_TEST( pss->Close(), S_OK );
   }

   // compute location of all pois
   CollectionIndexType cnt;
   poilist->get_Count(&cnt);
   std::vector<Float64> poi_locs;
   poi_locs.reserve(cnt);
   GetSSPoiLocs(poilist, psm, &poi_locs);

   // compute forces for stage 1 Self Weight and print results to file
   CComPtr<ISectionResult3Ds> pres;
   hr = plgr->ComputeForces(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 1"), roGlobal, rsCumulative, &pres);
   ATLASSERT(SUCCEEDED(hr));

   DumpSectionForceResults( os, poilist, pres, poi_locs);

   pres = NULL;
   hr = plgr->ComputeForces(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 2"), roGlobal, rsIncremental, &pres);
   ATLASSERT(SUCCEEDED(hr));

   DumpSectionForceResults( os, poilist, pres, poi_locs);

   pres = NULL;
   hr = plgr->ComputeForces(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 2"), roGlobal, rsCumulative, &pres);
   ATLASSERT(SUCCEEDED(hr));

   DumpSectionForceResults( os, poilist, pres, poi_locs);

   pres = NULL;
   hr = plgr->ComputeForces(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 3"), roGlobal, rsCumulative, &pres);
   ATLASSERT(SUCCEEDED(hr));

   DumpSectionForceResults( os, poilist, pres, poi_locs);

   CComPtr<ISectionResult3Ds> pdefls;
   hr = plgr->ComputeDeflections(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 1"), rsCumulative, &pdefls);
   ATLASSERT(SUCCEEDED(hr));

   DumpDeflectionResults( os, poilist, pdefls, poi_locs);

   pdefls = NULL;
   hr = plgr->ComputeDeflections(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 2"), rsIncremental, &pdefls);
   ATLASSERT(SUCCEEDED(hr));

   DumpDeflectionResults( os, poilist, pdefls, poi_locs);

   pdefls = NULL;
   hr = plgr->ComputeDeflections(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 3"), rsIncremental, &pdefls);
   ATLASSERT(SUCCEEDED(hr));

   DumpDeflectionResults( os, poilist, pdefls, poi_locs);

   // stresses
   os <<"Stresses"<<std::endl;
   CComPtr<ISectionStressResults> pStresss;
   hr = plgr->ComputeStresses(_bstr_t("Self Weight"), poilist, _bstr_t("Stage 1"), rsIncremental, &pStresss);
   ATLASSERT(SUCCEEDED(hr));

   DumpStressResults( os, poilist, pStresss);

   pStresss = NULL;
   hr = plgr->ComputeStresses(_bstr_t("Self Weight"), poilist, _bstr_t("Stage 2"), rsIncremental, &pStresss);
   ATLASSERT(SUCCEEDED(hr));

   DumpStressResults( os, poilist, pStresss);

   pStresss = NULL;
   hr = plgr->ComputeStresses(_bstr_t("Self Weight"), poilist, _bstr_t("Stage 3"), rsIncremental, &pStresss);
   ATLASSERT(SUCCEEDED(hr));

   DumpStressResults( os, poilist, pStresss);

   pStresss = NULL;
   hr = plgr->ComputeStresses(_bstr_t("Self Weight"), poilist, _bstr_t("Stage 1"), rsCumulative, &pStresss);
   ATLASSERT(SUCCEEDED(hr));

   DumpStressResults( os, poilist, pStresss);

   pStresss = NULL;
   hr = plgr->ComputeStresses(_bstr_t("Self Weight"), poilist, _bstr_t("Stage 2"), rsCumulative, &pStresss);
   ATLASSERT(SUCCEEDED(hr));

   DumpStressResults( os, poilist, pStresss);

   pStresss = NULL;
   hr = plgr->ComputeStresses(_bstr_t("Self Weight"), poilist, _bstr_t("Stage 3"), rsCumulative, &pStresss);
   ATLASSERT(SUCCEEDED(hr));

   DumpStressResults( os, poilist, pStresss);

   // get contraflexure locations
   CComQIPtr<IContraflexureResponse> pcontrf(plgr);

   {
      CComPtr<IDblArray> vlocs;
      hr = pcontrf->ComputeContraflexureLocations(_bstr_t("Stage 1"), &vlocs);
      ATLASSERT(SUCCEEDED(hr));
      TIArrayHelper<Float64, IDblArray, CollectionIndexType> locs(vlocs);

      CollectionIndexType size = locs.Size();
      TRY_TEST(size,2);
      TRY_TEST( IsEqual(locs[0], 80.00000, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[1],120.00000, 1.0e-4), true);
   }

   {
      CComPtr<IDblArray> vlocs;
      hr =pcontrf->ComputeContraflexureLocations(_bstr_t("Stage 2"), &vlocs);
      ATLASSERT(SUCCEEDED(hr));

      TIArrayHelper<Float64, IDblArray, CollectionIndexType> locs(vlocs);
      CollectionIndexType size = locs.Size();
      TRY_TEST(size,2);
      TRY_TEST( IsEqual(locs[0], 80.00000, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[1],120.00000, 1.0e-4), true);
   }

   {
      CComPtr<IDblArray> vlocs;
      hr =pcontrf->ComputeContraflexureLocations(_bstr_t("Stage 3"), &vlocs);
      ATLASSERT(SUCCEEDED(hr));

      TIArrayHelper<Float64, IDblArray, CollectionIndexType> locs(vlocs);

      CollectionIndexType size = locs.Size();
      TRY_TEST(size,2);
      TRY_TEST( IsEqual(locs[0], 72.79669, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[1],127.20330, 1.0e-4), true);
   }

   return S_OK;
}


void CTestSpliced::GetSSPoiLocs(IIDArray* ppoilist, ILBAMModel* pModel, std::vector<Float64>* poiLocs)
{
   HRESULT hr;
   // first determine locations of span and superstructuremember ends
   std::vector<Float64> span_ends;
   CComPtr<ISpans> spans;
   pModel->get_Spans(&spans);
   SpanIndexType span_cnt;
   spans->get_Count(&span_cnt);
   Float64 loc = 0.0;
   span_ends.push_back(loc);  // spans start at 0.0

   for(SpanIndexType ispan=0; ispan<span_cnt; ispan++)
   {
      CComPtr<ISpan> span;
      spans->get_Item(ispan, &span);
      Float64 len;
      span->get_Length(&len);
      loc += len;
      span_ends.push_back(loc);
   }

   // ssm's
   std::vector<Float64> ssm_ends;
   CComPtr<ISuperstructureMembers> ssms;
   pModel->get_SuperstructureMembers(&ssms);

   Float64 left_overhang;
   ssms->get_Offset(&left_overhang);

   CollectionIndexType ssm_cnt;
   ssms->get_Count(&ssm_cnt);
   loc = -left_overhang;
   ssm_ends.push_back(loc);
   for(CollectionIndexType issm=0; issm<ssm_cnt; issm++)
   {
      CComPtr<ISuperstructureMember> ssm;
      ssms->get_Item(issm, &ssm);
      Float64 len;
      ssm->get_Length(&len);
      loc += len;
      ssm_ends.push_back(loc);
   }

   // determine locations of pois along x
   CComPtr<IPOIs> pois;
   pModel->get_POIs(&pois);

   CollectionIndexType cnt;
   ppoilist->get_Count(&cnt);
   for (CollectionIndexType i=0; i<cnt; i++)
   {
      PoiIDType poi_id;
      ppoilist->get_Item(i,&poi_id);

      CComPtr<IPOI> poi;
      hr = pois->Find(poi_id, &poi);
      ATLASSERT(SUCCEEDED(hr));

      MemberIDType mbr_id;
      poi->get_MemberID(&mbr_id);

      MemberType mbr_type;
      poi->get_MemberType(&mbr_type);

      Float64 location;
      poi->get_Location(&location);

      if (mbr_type==mtSpan)
      {
         ATLASSERT(mbr_id < MemberIDType(span_ends.size()) );
         Float64 mbr_length = span_ends[mbr_id+1] - span_ends[mbr_id];
         Float64 mbr_loc = GetFracDistance(location, mbr_length);
         mbr_loc += span_ends[mbr_id];
         poiLocs->push_back(mbr_loc);
      }
      else if (mbr_type==mtSuperstructureMember)
      {
         ATLASSERT( mbr_id < MemberIDType(ssm_ends.size()) );
         Float64 mbr_length = ssm_ends[mbr_id+1] - ssm_ends[mbr_id];
         Float64 mbr_loc = GetFracDistance(location, mbr_length);
         mbr_loc += ssm_ends[mbr_id];
         poiLocs->push_back(mbr_loc);
      }
      else
         ATLASSERT(0); // we can only handle superstructure
   }
}


ILBAMModel* CTestSpliced::CreateModel()
{
   CComPtr<ILBAMModel> psm;
   TRY_TEST(psm.CoCreateInstance( CLSID_LBAMModel ), S_OK );
   Float64 d;

   // stages
   CComPtr<IStages> pStages;
   TRY_TEST(psm->get_Stages(&pStages), S_OK);

   CComPtr<IStage> pStage1, pStage2, pStage3;
   TRY_TEST(pStage1.CoCreateInstance( CLSID_Stage ), S_OK );
   TRY_TEST(pStage2.CoCreateInstance( CLSID_Stage ), S_OK );
   TRY_TEST(pStage3.CoCreateInstance( CLSID_Stage ), S_OK );
   TRY_TEST(pStage1->put_Name(_bstr_t("Stage 1")), S_OK );
   TRY_TEST(pStage2->put_Name(_bstr_t("Stage 2")), S_OK );
   TRY_TEST(pStage3->put_Name(_bstr_t("Stage 3")), S_OK );
   TRY_TEST(pStages->Add(pStage1), S_OK);
   TRY_TEST(pStages->Add(pStage2), S_OK);
   TRY_TEST(pStages->Add(pStage3), S_OK);

   // add some spans
   // ======================
   CComPtr<ISpan> pspn0, pspn1;
   TRY_TEST(pspn0.CoCreateInstance( CLSID_Span ), S_OK );
   TRY_TEST(pspn1.CoCreateInstance( CLSID_Span ), S_OK );

   CComPtr<ISpans> pspns;
   TRY_TEST(psm->get_Spans(&pspns), S_OK);

   // add spans
   TRY_TEST(pspns->Add(pspn0), S_OK);
   TRY_TEST(pspn0->put_Length(100.0), S_OK);
   TRY_TEST(pspns->Add(pspn1), S_OK);
   TRY_TEST(pspn1->put_Length(100.0), S_OK);

   // check the length of our spans
   TRY_TEST(pspns->get_Length(&d), S_OK);
   TRY_TEST(d, 200.0);

// SuperstructureMembers
//===========================
   CComPtr<ISuperstructureMember> pssm0, pssm1, pssm2;
   TRY_TEST(pssm0.CoCreateInstance( CLSID_SuperstructureMember ), S_OK );
   TRY_TEST(pssm1.CoCreateInstance( CLSID_SuperstructureMember ), S_OK );
   TRY_TEST(pssm2.CoCreateInstance( CLSID_SuperstructureMember ), S_OK );

   CComPtr<ISuperstructureMembers> pssms;
   TRY_TEST(psm->get_SuperstructureMembers(&pssms), S_OK);

   // add SuperstructureMember's 0 and 2
   TRY_TEST(pssms->Add(pssm0), S_OK);
   TRY_TEST(pssms->Add(pssm1), S_OK);
   TRY_TEST(pssms->Add(pssm2), S_OK);
   TRY_TEST(pssm0->put_Length(80.0), S_OK);
   TRY_TEST(pssm1->put_Length(40.0), S_OK);
   TRY_TEST(pssm2->put_Length(80.0), S_OK);

   // segments for ssms 0, 2
   CComPtr<ISegment> pseg1s2, pseg1s3;
   TRY_TEST( pseg1s2.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( pseg1s3.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( pseg1s2->put_Length(80.0) , S_OK );
   TRY_TEST( pseg1s3->put_Length(80.0) , S_OK );
   SetupSegment(pseg1s2, 5, 20, 1.0e4, 6);
   SetupSegment(pseg1s3, 6, 30, 1.0e4, 6);

   TRY_TEST(pssm0->AddSegment(_bstr_t("Stage 1"), pseg1s2), S_OK ); // not active in analysis
   TRY_TEST(pssm0->AddSegment(_bstr_t("Stage 2"), pseg1s2), S_OK );
   TRY_TEST(pssm0->AddSegment(_bstr_t("Stage 3"), pseg1s3), S_OK );
   TRY_TEST(pssm2->AddSegment(_bstr_t("Stage 1"), pseg1s2), S_OK ); // not active in analysis
   TRY_TEST(pssm2->AddSegment(_bstr_t("Stage 2"), pseg1s2), S_OK );
   TRY_TEST(pssm2->AddSegment(_bstr_t("Stage 3"), pseg1s3), S_OK );

   // SuperstructureMember 1
   CComPtr<ISegment> pseg2s1, pseg2s2, pseg2s3;
   TRY_TEST( pseg2s1.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( pseg2s2.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( pseg2s3.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( pseg2s1->put_Length(40.0) , S_OK );
   TRY_TEST( pseg2s2->put_Length(40.0) , S_OK );
   TRY_TEST( pseg2s3->put_Length(40.0) , S_OK );
   SetupSegment(pseg2s1, 6, 30, 1.0e4, 6);
   SetupSegment(pseg2s2, 6, 30, 1.0e4, 6);
   SetupSegment(pseg2s3, 7, 40, 1.0e4, 6);

   TRY_TEST(pssm1->AddSegment(_bstr_t("Stage 1"), pseg2s1), S_OK );
   TRY_TEST(pssm1->AddSegment(_bstr_t("Stage 2"), pseg2s2), S_OK );
   TRY_TEST(pssm1->AddSegment(_bstr_t("Stage 3"), pseg2s3), S_OK );

   TRY_TEST(pssm1->SetEndRelease(ssLeft,  _bstr_t("Stage 3"), mrtPinned), S_OK );
   TRY_TEST(pssm1->SetEndRelease(ssRight, _bstr_t("Stage 3"), mrtPinned), S_OK );

   // check the length of our ssms
   TRY_TEST(pssms->get_Length(&d), S_OK);
   TRY_TEST(d, 200);

   // add our supports
   // ======================
   CComPtr<ISupport> psup0, psup1, psup2;
   TRY_TEST(psup0.CoCreateInstance( CLSID_Support ), S_OK );
   TRY_TEST(psup1.CoCreateInstance( CLSID_Support ), S_OK );
   TRY_TEST(psup2.CoCreateInstance( CLSID_Support ), S_OK );

   CComPtr<ISupports> psups;
   TRY_TEST(psm->get_Supports(&psups), S_OK);

   // Supports 0 and 2 are zero length
   TRY_TEST(psups->Add(psup0), S_OK);
   TRY_TEST(psups->Add(psup1), S_OK);
   TRY_TEST(psups->Add(psup2), S_OK);

   TRY_TEST(psup0->put_BoundaryCondition(bcRoller), S_OK);
   TRY_TEST(psup2->put_BoundaryCondition(bcRoller), S_OK);

   // support 1
   TRY_TEST(psup1->put_Length(20.0), S_OK);
   TRY_TEST(psup1->put_BoundaryCondition(bcPinned), S_OK);

   CComPtr<ISegment> psseg1;
   TRY_TEST( psseg1.CoCreateInstance( CLSID_Segment ) , S_OK );
   SetupSegment(psseg1, 2, 10, 1.0e4, 2);
   TRY_TEST( psseg1->put_Length(20.0) , S_OK );

   TRY_TEST(psup1->AddSegment(_bstr_t("Stage 1"), psseg1), S_OK );
   TRY_TEST(psup1->AddSegment(_bstr_t("Stage 2"), psseg1), S_OK );
   TRY_TEST(psup1->AddSegment(_bstr_t("Stage 3"), psseg1), S_OK );

   // put a temporary support in span 0 for stages 1,2   
   // ======================
   CComPtr<ITemporarySupports> ptsups;
   TRY_TEST(pspn0->get_TemporarySupports(&ptsups), S_OK);

   CComPtr<ITemporarySupport> ptsup;
   TRY_TEST(ptsup.CoCreateInstance( CLSID_TemporarySupport ), S_OK );

   TRY_TEST(ptsups->Add(ptsup), S_OK);
   TRY_TEST(ptsup->put_ID(TS_ID), S_OK);
   TRY_TEST(ptsup->put_Location(80.0), S_OK);
   TRY_TEST(ptsup->put_BoundaryCondition(bcPinned), S_OK);
   TRY_TEST(ptsup->put_StageRemoved(_bstr_t("Stage 3")), S_OK);

   // POIs
   // ======================
   CComPtr<IPOIs> pPOIs;
   TRY_TEST(psm->get_POIs(&pPOIs), S_OK);

   // span 0
   Float64 loc = 0.0;
   for (int i=101; i<112; i++)
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

   // span 1
   loc = 0.0;
   for (int i=201; i<212; i++)
   {
      CComPtr<IPOI> pPOI;
      TRY_TEST(pPOI.CoCreateInstance( CLSID_POI ), S_OK );
      TRY_TEST( pPOI->put_ID(i), S_OK );
      TRY_TEST( pPOI->put_MemberType(mtSpan), S_OK );
      TRY_TEST( pPOI->put_MemberID(1), S_OK );
      TRY_TEST( pPOI->put_Location(loc), S_OK );
      TRY_TEST(pPOIs->Add(pPOI), S_OK);
      loc -= 0.1;
   }

   // ssms
   loc = 0.0;
   for (MemberIDType i=0; i<=2; i++)
   {
      PoiIDType poi_id = PoiIDType(300+i*2);
      CComPtr<IPOI> pPOI0, pPOI1;
      TRY_TEST(pPOI0.CoCreateInstance( CLSID_POI ), S_OK );
      TRY_TEST( pPOI0->put_ID(poi_id), S_OK );
      TRY_TEST( pPOI0->put_MemberType(mtSuperstructureMember), S_OK );
      TRY_TEST( pPOI0->put_MemberID(i), S_OK );
      TRY_TEST( pPOI0->put_Location(0.0), S_OK );
      TRY_TEST(pPOIs->Add(pPOI0), S_OK);

      poi_id += 1;
      TRY_TEST(pPOI1.CoCreateInstance( CLSID_POI ), S_OK );
      TRY_TEST( pPOI1->put_ID(poi_id), S_OK );
      TRY_TEST( pPOI1->put_MemberType(mtSuperstructureMember), S_OK );
      TRY_TEST( pPOI1->put_MemberID(i), S_OK );
      TRY_TEST( pPOI1->put_Location(-1.0), S_OK );
      TRY_TEST(pPOIs->Add(pPOI1), S_OK);
   }

   // support 1
   loc = 0.0;
   for (int i=2001; i<2012; i++)
   {
      CComPtr<IPOI> pPOI;
      TRY_TEST(pPOI.CoCreateInstance( CLSID_POI ), S_OK );
      TRY_TEST( pPOI->put_ID(i), S_OK );
      TRY_TEST( pPOI->put_MemberType(mtSupport), S_OK );
      TRY_TEST( pPOI->put_MemberID(1), S_OK );
      TRY_TEST( pPOI->put_Location(loc), S_OK );
      TRY_TEST(pPOIs->Add(pPOI), S_OK);
      loc -= 0.1;
   }

   // Load Groups
   CComPtr<ILoadGroups> pLoadGroups;
   TRY_TEST(psm->get_LoadGroups(&pLoadGroups), S_OK);

   TCHAR* lgns[]={_T("Self Weight")};
   for (int i=0; i<1; i++)
   {
      CComPtr<ILoadGroup> pLoadGroup;
      TRY_TEST(pLoadGroup.CoCreateInstance( CLSID_LoadGroup ), S_OK );
      TRY_TEST( pLoadGroup->put_Name( CComBSTR(lgns[i]) ), S_OK );
      TRY_TEST(pLoadGroups->Add(pLoadGroup), S_OK);
   }

   // Self Weight - stage 1
   CComPtr<IDistributedLoads> pDistributedLoads;
   TRY_TEST(psm->get_DistributedLoads(&pDistributedLoads), S_OK);

   CComPtr<IDistributedLoad> pDistributedLoad1s1;
   TRY_TEST(pDistributedLoad1s1.CoCreateInstance( CLSID_DistributedLoad ), S_OK );

   CComPtr<IDistributedLoadItem> pDLtmp;
   TRY_TEST(pDistributedLoads->Add(_bstr_t("Stage 1"), _bstr_t("Self Weight"), pDistributedLoad1s1, &pDLtmp), S_OK);

   TRY_TEST(pDistributedLoad1s1->put_MemberType(mtSuperstructureMember), S_OK);
   TRY_TEST(pDistributedLoad1s1->put_MemberID(1), S_OK);
   TRY_TEST(pDistributedLoad1s1->put_Direction(ldFy), S_OK);
   TRY_TEST(pDistributedLoad1s1->put_WStart(-20), S_OK);
   TRY_TEST(pDistributedLoad1s1->put_WEnd(-20), S_OK);
   TRY_TEST(pDistributedLoad1s1->put_StartLocation(-0.0), S_OK);
   TRY_TEST(pDistributedLoad1s1->put_EndLocation(-1.0), S_OK);

   // Self Weight - stage 2 - use cloning to reduce # of calls
   CComPtr<IDistributedLoad> pDistributedLoad0s2;
   CComPtr<IDistributedLoad> pDistributedLoad2s2;

   pDistributedLoad1s1->Clone(&pDistributedLoad0s2);
   TRY_TEST(pDistributedLoad0s2->put_MemberID(0), S_OK);
   TRY_TEST(pDistributedLoad0s2->put_WStart(-15), S_OK);
   TRY_TEST(pDistributedLoad0s2->put_WEnd(-15), S_OK);
   pDistributedLoad1s1->Clone(&pDistributedLoad2s2);
   TRY_TEST(pDistributedLoad2s2->put_MemberID(2), S_OK);
   TRY_TEST(pDistributedLoad2s2->put_WStart(-15), S_OK);
   TRY_TEST(pDistributedLoad2s2->put_WEnd(-15), S_OK);

   pDLtmp= NULL;
   TRY_TEST(pDistributedLoads->Add(_bstr_t("Stage 2"), _bstr_t("Self Weight"), pDistributedLoad0s2, &pDLtmp), S_OK);
   pDLtmp= NULL;
   TRY_TEST(pDistributedLoads->Add(_bstr_t("Stage 2"), _bstr_t("Self Weight"), pDistributedLoad2s2, &pDLtmp), S_OK);

   // Self Weight - stage 2 - use cloning to reduce # of calls
   CComPtr<IDistributedLoad> pDistributedLoad0s3;
   CComPtr<IDistributedLoad> pDistributedLoad1s3;
   CComPtr<IDistributedLoad> pDistributedLoad2s3;

   pDistributedLoad1s1->Clone(&pDistributedLoad0s3);
   TRY_TEST(pDistributedLoad0s3->put_MemberID(0), S_OK);
   TRY_TEST(pDistributedLoad0s3->put_WStart(-5), S_OK);
   TRY_TEST(pDistributedLoad0s3->put_WEnd(-5), S_OK);
   pDistributedLoad1s1->Clone(&pDistributedLoad1s3);
   TRY_TEST(pDistributedLoad1s3->put_MemberID(1), S_OK);
   TRY_TEST(pDistributedLoad1s3->put_WStart(-5), S_OK);
   TRY_TEST(pDistributedLoad1s3->put_WEnd(-5), S_OK);
   pDistributedLoad1s1->Clone(&pDistributedLoad2s3);
   TRY_TEST(pDistributedLoad2s3->put_MemberID(2), S_OK);
   TRY_TEST(pDistributedLoad2s3->put_WStart(-5), S_OK);
   TRY_TEST(pDistributedLoad2s3->put_WEnd(-5), S_OK);

   pDLtmp= NULL;
   TRY_TEST(pDistributedLoads->Add(_bstr_t("Stage 3"), _bstr_t("Self Weight"), pDistributedLoad0s3, &pDLtmp), S_OK);
   pDLtmp= NULL;
   TRY_TEST(pDistributedLoads->Add(_bstr_t("Stage 3"), _bstr_t("Self Weight"), pDistributedLoad1s3, &pDLtmp), S_OK);
   pDLtmp= NULL;
   TRY_TEST(pDistributedLoads->Add(_bstr_t("Stage 3"), _bstr_t("Self Weight"), pDistributedLoad2s3, &pDLtmp), S_OK);

   // add lrfd live loads
   ConfigureLrfdLiveLoadModelInKipFeet(psm);

   // configure using lrfd table
   ConfigureLrfdLoadCombinations(psm);

   CComPtr<ILoadCases> lcs;
   TRY_TEST( (psm)->get_LoadCases(&lcs), S_OK);

   CComPtr<ILoadCase> lcdc;
   TRY_TEST( lcs->Find(CComBSTR("DC"),&lcdc), S_OK);
   lcdc->AddLoadGroup(_bstr_t("Self Weight"));


   return psm.Detach();
}

void SetupSegment(ISegment* pseg, Float64 A, Float64 I, Float64 E, Float64 depth)
{
   CComPtr<ISegmentCrossSection> pcs;
   TRY_TEST(pcs.CoCreateInstance( CLSID_SegmentCrossSection ), S_OK );

   // fake in some numbers
   Float64 ei = E*I;
   Float64 ea = E*A;
   Float64 sm = depth/(2*I);
   Float64 sa = 1/A;

   TRY_TEST( pcs->put_EAForce(ea), S_OK );
   TRY_TEST( pcs->put_EIForce(ei), S_OK );
   TRY_TEST( pcs->put_EADefl(ea/2.), S_OK ); // deflection has 1/2 props
   TRY_TEST( pcs->put_EIDefl(ei/2.), S_OK );
   TRY_TEST( pcs->put_ThermalCoeff(1.5), S_OK );
   TRY_TEST( pcs->put_Depth(depth), S_OK );

   CComPtr<IStressPoints> psps;
   TRY_TEST( pcs->get_StressPoints(&psps), S_OK );

   CComPtr<IStressPoint> pss1, pss2;
   TRY_TEST( pss1.CoCreateInstance( CLSID_StressPoint ) , S_OK );
   TRY_TEST( pss2.CoCreateInstance( CLSID_StressPoint ) , S_OK );

   TRY_TEST( pss1->put_Sm(sm), S_OK );
   TRY_TEST( pss1->put_Sa(sa), S_OK );
   TRY_TEST( psps->Add(pss1), S_OK);

   TRY_TEST( psps->Add(pss2), S_OK);
   TRY_TEST( pss2->put_Sm(-sm), S_OK );
   TRY_TEST( pss2->put_Sa(sa), S_OK );

   TRY_TEST( pseg->putref_SegmentCrossSection(pcs), S_OK);
}
