///////////////////////////////////////////////////////////////////////
// LBAM Analysis Test - Test driver for LBAM analysis library
// Copyright © 1999-2020  Washington State Department of Transportation
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

// TestOverhang.cpp: implementation of the CTestOverhang class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestOverhang.h"
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
static const long TS_ID=12;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestOverhang::CTestOverhang()
{

}

CTestOverhang::~CTestOverhang()
{

}

HRESULT CTestOverhang::Test()
{
   // dump results to a file
   std::_tofstream os("Overhang.txt");

   // build a model and attach it to our load group response object
   CComPtr<ILoadGroupResponse> plgr;
   plgr.CoCreateInstance(CLSID_LoadGroupForceResponse);
//   plgr.CoCreateInstance(CLSID_LoadGroupDeflectionResponse);

   CComPtr<ILBAMModel> psm;
   psm.Attach( CreateModel(true) );

   HRESULT hr;
   CComQIPtr<IDependOnLBAM> pctx(plgr);
   hr = pctx->putref_Model(psm);

   // request results for tenth points in spans 0 and 1
   CComPtr<IIDArray> poilist;
   poilist.CoCreateInstance(CLSID_IDArray);
   for (PoiIDType i = 0; i<11; i++)
   {
      poilist->Add(i+101);
   }
   for (PoiIDType i = 0; i<11; i++)
   {
      poilist->Add(i+201);
   }

   // save input file off
   /////////////////////////////////////////////////////////////////////
   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("TestOverhang.xml")), S_OK );

      // get interface pointer to Save our cross section
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

   // compute forces for stage 1 Point Loads and print results to file

   CComPtr<ISectionResult3Ds> pres;
   hr = plgr->ComputeForces(_bstr_t("Point Loads"), poilist ,_bstr_t("Stage 1"), roGlobal, rsCumulative, &pres);
   ATLASSERT(SUCCEEDED(hr));

   DumpSectionForceResults( os, poilist, pres, poi_locs);

   pres = nullptr;
   hr = plgr->ComputeForces(_bstr_t("Point Loads"), poilist ,_bstr_t("Stage 2"), roGlobal, rsIncremental, &pres);
   ATLASSERT(SUCCEEDED(hr));

   DumpSectionForceResults( os, poilist, pres, poi_locs);

   pres = nullptr;
   hr = plgr->ComputeForces(_bstr_t("Point Loads"), poilist ,_bstr_t("Stage 2"), roGlobal, rsCumulative, &pres);
   ATLASSERT(SUCCEEDED(hr));

   DumpSectionForceResults( os, poilist, pres, poi_locs);

   CComPtr<ISectionResult3Ds> pdefls;
   hr = plgr->ComputeDeflections(_bstr_t("Point Loads"), poilist ,_bstr_t("Stage 1"), rsCumulative, &pdefls);
   ATLASSERT(SUCCEEDED(hr));

   DumpDeflectionResults( os, poilist, pdefls, poi_locs);

   pdefls = nullptr;
   hr = plgr->ComputeDeflections(_bstr_t("Point Loads"), poilist ,_bstr_t("Stage 2"), rsIncremental, &pdefls);
   ATLASSERT(SUCCEEDED(hr));

   DumpDeflectionResults( os, poilist, pdefls, poi_locs);

   // stresses
   os <<"Stresses"<<std::endl;
   CComPtr<ISectionStressResults> pStresss;
   hr = plgr->ComputeStresses(_bstr_t("Point Loads"), poilist, _bstr_t("Stage 1"), rsIncremental, &pStresss);
   ATLASSERT(SUCCEEDED(hr));

   DumpStressResults( os, poilist, pStresss);

   pStresss = nullptr;
   hr = plgr->ComputeStresses(_bstr_t("Point Loads"), poilist, _bstr_t("Stage 2"), rsIncremental, &pStresss);
   ATLASSERT(SUCCEEDED(hr));

   DumpStressResults( os, poilist, pStresss);

   pStresss = nullptr;
   hr = plgr->ComputeStresses(_bstr_t("Point Loads"), poilist, _bstr_t("Stage 1"), rsCumulative, &pStresss);
   ATLASSERT(SUCCEEDED(hr));

   DumpStressResults( os, poilist, pStresss);

   pStresss = nullptr;
   hr = plgr->ComputeStresses(_bstr_t("Point Loads"), poilist, _bstr_t("Stage 2"), rsCumulative, &pStresss);
   ATLASSERT(SUCCEEDED(hr));

   DumpStressResults( os, poilist, pStresss);

   // get reactions and deflections at supports
   os <<std::endl<<"Supports"<<std::endl;

   // lists of supports for stage 1 and 2 are different since temp support is gone in stage 2
   CComPtr<IIDArray> sptlist_stg1;
   sptlist_stg1.CoCreateInstance(CLSID_IDArray);
   sptlist_stg1->Add(0);
   sptlist_stg1->Add(1);
   sptlist_stg1->Add(2);
   sptlist_stg1->Add(TS_ID);

   CComPtr<IIDArray> sptlist_stg2;
   sptlist_stg2.CoCreateInstance(CLSID_IDArray);
   sptlist_stg2->Add(0);
   sptlist_stg2->Add(1);
   sptlist_stg2->Add(2);

   os <<"Deflections"<<std::endl;
   CComPtr<IResult3Ds> prdefls;
   hr = plgr->ComputeSupportDeflections(_bstr_t("Point Loads"), sptlist_stg1, _bstr_t("Stage 1"), rsIncremental, &prdefls);
   ATLASSERT(SUCCEEDED(hr));

   DumpSupportDeflectionResults( os, sptlist_stg1, prdefls);

   prdefls = nullptr;
   hr = plgr->ComputeSupportDeflections(_bstr_t("Point Loads"), sptlist_stg2, _bstr_t("Stage 2"), rsIncremental, &prdefls);
   ATLASSERT(SUCCEEDED(hr));

   DumpSupportDeflectionResults( os, sptlist_stg2, prdefls);

   prdefls=nullptr;
   hr = plgr->ComputeSupportDeflections(_bstr_t("Point Loads"), sptlist_stg1, _bstr_t("Stage 1"), rsCumulative, &prdefls);
   ATLASSERT(SUCCEEDED(hr));

   DumpSupportDeflectionResults( os, sptlist_stg1, prdefls);

   prdefls = nullptr;
   hr = plgr->ComputeSupportDeflections(_bstr_t("Point Loads"), sptlist_stg2, _bstr_t("Stage 2"), rsCumulative, &prdefls);
   ATLASSERT(SUCCEEDED(hr));

   DumpSupportDeflectionResults( os, sptlist_stg2, prdefls);

   os <<"Reactions"<<std::endl;
   CComPtr<IResult3Ds> pforces;
   hr = plgr->ComputeReactions(_bstr_t("Point Loads"), sptlist_stg1, _bstr_t("Stage 1"), rsIncremental, &pforces);
   ATLASSERT(SUCCEEDED(hr));

   DumpReactionResults( os, sptlist_stg1, pforces);

   pforces = nullptr;
   hr = plgr->ComputeReactions(_bstr_t("Point Loads"), sptlist_stg2, _bstr_t("Stage 2"), rsIncremental, &pforces);
   ATLASSERT(SUCCEEDED(hr));

   DumpReactionResults( os, sptlist_stg2, pforces);

   pforces = nullptr;
   hr = plgr->ComputeReactions(_bstr_t("Point Loads"), sptlist_stg1, _bstr_t("Stage 1"), rsCumulative, &pforces);
   ATLASSERT(SUCCEEDED(hr));

   DumpReactionResults( os, sptlist_stg1, pforces);

   pforces = nullptr;
   hr = plgr->ComputeReactions(_bstr_t("Point Loads"), sptlist_stg2, _bstr_t("Stage 2"), rsCumulative, &pforces);
   ATLASSERT(SUCCEEDED(hr));

   DumpReactionResults( os, sptlist_stg2, pforces);


   CComPtr<IIDArray> suplist;
   suplist.CoCreateInstance(CLSID_IDArray);
   suplist->Add(20005);
   pStresss = nullptr;
   hr = plgr->ComputeStresses(_bstr_t("Distributed Loads"), suplist, _bstr_t("Stage 1"), rsIncremental, &pStresss);
   ATLASSERT(SUCCEEDED(hr));
   os<< "Stress Dump"<<std::endl;
   DumpStressResults( os, suplist, pStresss);
   os<< "Stress Dump Done"<<std::endl;



// do some testing of change management - make a change to a load case and see if loading is updated correctly
// (most of testing must be done through debugger
   os << "After Loading Change"<<std::endl;

   CComPtr<IPointLoads> pPointLoads;
   TRY_TEST(psm->get_PointLoads(&pPointLoads), S_OK);

   CComPtr<IPointLoad> pPointLoad1;
   TRY_TEST(pPointLoad1.CoCreateInstance( CLSID_PointLoad ), S_OK );

   TRY_TEST(pPointLoad1->put_MemberType(mtSpan), S_OK);
   TRY_TEST(pPointLoad1->put_MemberID(1), S_OK);
   TRY_TEST(pPointLoad1->put_Location(-.5), S_OK);
   TRY_TEST(pPointLoad1->SetForce(0,-1000,0), S_OK);

   CComPtr<IPointLoadItem> pPLI1;
   TRY_TEST(pPointLoads->Add(_bstr_t("Stage 1"), _bstr_t("Point Loads"), pPointLoad1, &pPLI1), S_OK);

   pres = nullptr;
   hr = plgr->ComputeForces(_bstr_t("Point Loads"), poilist ,_bstr_t("Stage 1"), roGlobal, rsIncremental, &pres);
   ATLASSERT(SUCCEEDED(hr));

   DumpSectionForceResults( os, poilist, pres, poi_locs);

   // add a poi and see how system deals with change
   os << "After POI Change"<<std::endl;
   CComPtr<IPOIs> pPOIs;
   TRY_TEST(psm->get_POIs(&pPOIs), S_OK);

   CComPtr<IPOI> pPOI;
   TRY_TEST(pPOI.CoCreateInstance( CLSID_POI ), S_OK );
   TRY_TEST( pPOI->put_ID(10001), S_OK );
   TRY_TEST( pPOI->put_MemberType(mtSpan), S_OK );
   TRY_TEST( pPOI->put_MemberID(0), S_OK );
   TRY_TEST( pPOI->put_Location(-0.5), S_OK );
   TRY_TEST(pPOIs->Add(pPOI), S_OK);

   pres = nullptr;
   hr = plgr->ComputeForces(_bstr_t("Point Loads"), poilist ,_bstr_t("Stage 1"), roGlobal, rsIncremental, &pres);
   ATLASSERT(SUCCEEDED(hr));

   DumpSectionForceResults( os, poilist, pres, poi_locs);

   // test influence line computation
   CComQIPtr<IInfluenceLineResponse> pinfl(plgr);
   ATLASSERT(pinfl!=nullptr);

   CComPtr<IInfluenceLine> lft_ifl_f1, rgt_ifl_f1;
   TRY_TEST(pinfl->ComputeForceInfluenceLine(106,CComBSTR("Stage 2"),fetFy, roGlobal, &lft_ifl_f1, &rgt_ifl_f1), S_OK );

   CComPtr<IInfluenceLine> lft_ifl_d1, rgt_ifl_d1;
   TRY_TEST(pinfl->ComputeDeflectionInfluenceLine(106,CComBSTR("Stage 2"),fetFy, &lft_ifl_d1, &rgt_ifl_d1), S_OK );

   CComPtr<IInfluenceLine> ifl_r0, ifl_r1, ifl_r2;
   TRY_TEST(pinfl->ComputeReactionInfluenceLine(0,CComBSTR("Stage 2"),fetFy, &ifl_r0), S_OK );
   TRY_TEST(pinfl->ComputeReactionInfluenceLine(1,CComBSTR("Stage 2"),fetFy, &ifl_r1), S_OK );
   TRY_TEST(pinfl->ComputeReactionInfluenceLine(2,CComBSTR("Stage 2"),fetFy, &ifl_r2), S_OK );

   CComPtr<IInfluenceLine> ifl_rts,ifl_rts1;
   TRY_TEST(pinfl->ComputeReactionInfluenceLine(TS_ID,CComBSTR("Stage 1"),fetFy, &ifl_rts),S_OK );
   TRY_TEST(pinfl->ComputeReactionInfluenceLine(TS_ID,CComBSTR("Stage 2"),fetFy, &ifl_rts1),LBAMA_E_SUPPORT_NOT_EXIST );

   // get contraflexure locations
   CComQIPtr<IContraflexureResponse> pcontrf(plgr);

   {
      CComPtr<IDblArray> vlocs;
      hr =pcontrf->ComputeContraflexureLocations(_bstr_t("Stage 1"), &vlocs);
      ATLASSERT(SUCCEEDED(hr));

      TIArrayHelper<Float64, IDblArray, CollectionIndexType> locs(vlocs);
      CollectionIndexType size = locs.Size();
      TRY_TEST(size,6);
      TRY_TEST( IsEqual(locs[0],-10.00000, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[1],  1.43582, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[2], 78.17671, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[3],143.81020, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[4],197.93342, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[5],210.00000, 1.0e-4), true);
   }

   {
      CComPtr<IDblArray> vlocs;
      hr =pcontrf->ComputeContraflexureLocations(_bstr_t("Stage 2"), &vlocs);
      ATLASSERT(SUCCEEDED(hr));
      TIArrayHelper<Float64, IDblArray, CollectionIndexType> locs(vlocs);

      CollectionIndexType size = locs.Size();
      TRY_TEST(size,6);
      TRY_TEST( IsEqual(locs[0],-10.00000, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[1],  1.50335, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[2], 74.84803, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[3],125.15196, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[4],198.49664, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[5],210.00000, 1.0e-4), true);
   }

   // lastly, create a model with no pois so we can view it later
   CreateWithNoPOis();

   return S_OK;
}


void CTestOverhang::GetSSPoiLocs(IIDArray* ppoilist, ILBAMModel* pModel, std::vector<Float64>* poiLocs)
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

   for(SpanIndexType ispan = 0; ispan<span_cnt; ispan++)
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
   for(CollectionIndexType issm = 0; issm<ssm_cnt; issm++)
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
   for (CollectionIndexType i = 0; i<cnt; i++)
   {
      PoiIDType poi_id;
      ppoilist->get_Item(i, &poi_id);

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
         ATLASSERT(mbr_id < MemberIDType(ssm_ends.size()) );
         Float64 mbr_length = ssm_ends[mbr_id+1] - ssm_ends[mbr_id];
         Float64 mbr_loc = GetFracDistance(location, mbr_length);
         mbr_loc += ssm_ends[mbr_id];
         poiLocs->push_back(mbr_loc);
      }
      else
         ATLASSERT(false); // we can only handle superstructure
   }
}


ILBAMModel* CTestOverhang::CreateModel(bool doPois)
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

   // 10 overhang on both ends
   TRY_TEST(pssms->put_Offset(10.0), S_OK);

   // add SuperstructureMember 0
   TRY_TEST(pssms->Add(pssm0), S_OK);
   TRY_TEST(pssm0->put_Length(75.0), S_OK);

   CComPtr<ISegment> pseg1s1, pseg1s2;
   TRY_TEST( pseg1s1.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( pseg1s2.CoCreateInstance( CLSID_Segment ) , S_OK );
   SetupSegment(pseg1s1, 0.8, false);
   TRY_TEST( pseg1s1->put_Length(75.0) , S_OK );
   SetupSegment(pseg1s2, 1.0, false);
   TRY_TEST( pseg1s2->put_Length(75.0) , S_OK );

   TRY_TEST(pssm0->AddSegment(_bstr_t("Stage 1"), pseg1s1), S_OK );
   TRY_TEST(pssm0->AddSegment(_bstr_t("Stage 2"), pseg1s2), S_OK );

   // add SuperstructureMember 1
   TRY_TEST(pssms->Add(pssm1), S_OK);
   TRY_TEST(pssm1->put_Length(70.0), S_OK);

   CComPtr<ISegment> pseg2s1, pseg2s2;
   TRY_TEST( pseg2s1.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( pseg2s2.CoCreateInstance( CLSID_Segment ) , S_OK );
   SetupSegment(pseg2s1, 0.8, false);
   TRY_TEST( pseg2s1->put_Length(75.0) , S_OK );
   SetupSegment(pseg2s2, 1.0, false);
   TRY_TEST( pseg2s2->put_Length(75.0) , S_OK );

   TRY_TEST(pssm1->AddSegment(_bstr_t("Stage 1"), pseg2s1), S_OK );
   TRY_TEST(pssm1->AddSegment(_bstr_t("Stage 2"), pseg2s2), S_OK );

   // add SuperstructureMember 2
   TRY_TEST(pssms->Add(pssm2), S_OK);
   TRY_TEST(pssm2->put_Length(75.0), S_OK);

   TRY_TEST(pssm2->AddSegment(_bstr_t("Stage 1"), pseg1s1), S_OK );
   TRY_TEST(pssm2->AddSegment(_bstr_t("Stage 2"), pseg1s2), S_OK );

   // check the length of our ssms
   TRY_TEST(pssms->get_Length(&d), S_OK);
   TRY_TEST(d, 220);

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

   // support 1
   TRY_TEST(psups->Add(psup1), S_OK);
   TRY_TEST(psup1->put_Length(12.0), S_OK);
   TRY_TEST(psup1->put_BoundaryCondition(bcFixed), S_OK);

   CComPtr<ISegment> psseg1;
   TRY_TEST( psseg1.CoCreateInstance( CLSID_Segment ) , S_OK );
   SetupSegment(psseg1, 1.0, true);
   TRY_TEST( psseg1->put_Length(12.0) , S_OK );

   TRY_TEST(psup1->AddSegment(_bstr_t("Stage 1"), psseg1), S_OK );
   TRY_TEST(psup1->AddSegment(_bstr_t("Stage 2"), psseg1), S_OK );

   // support 2
   TRY_TEST(psups->Add(psup2), S_OK);

   // put a temporary support in span 1 for stage 1 only
   // ======================
   CComPtr<ITemporarySupports> ptsups;
   TRY_TEST(pspn1->get_TemporarySupports(&ptsups), S_OK);

   CComPtr<ITemporarySupport> ptsup;
   TRY_TEST(ptsup.CoCreateInstance( CLSID_TemporarySupport ), S_OK );

   TRY_TEST(ptsups->Add(ptsup), S_OK);
   TRY_TEST(ptsup->put_Length(12.0), S_OK);
   TRY_TEST(ptsup->put_ID(TS_ID), S_OK);
   TRY_TEST(ptsup->put_Location(-1./3.), S_OK);
   TRY_TEST(ptsup->put_BoundaryCondition(bcFixed), S_OK);
   TRY_TEST(ptsup->put_StageRemoved(_bstr_t("Stage 2")), S_OK);
   TRY_TEST(ptsup->put_TopRelease(VARIANT_TRUE), S_OK);
   TRY_TEST(psseg1->put_Length(8.0) , S_OK );
   TRY_TEST(ptsup->AddSegment(_bstr_t("Stage 1"), psseg1), S_OK ); // use same properties as support 1

   if (doPois)
   {
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

      // put a poi at our temporary support location
      CComPtr<IPOI> ptsPOI;
      TRY_TEST(ptsPOI.CoCreateInstance( CLSID_POI ), S_OK );
      TRY_TEST( ptsPOI->put_ID(213), S_OK );
      TRY_TEST( ptsPOI->put_MemberType(mtSpan), S_OK );
      TRY_TEST( ptsPOI->put_MemberID(1), S_OK );
      TRY_TEST( ptsPOI->put_Location(-1./3.), S_OK );
      TRY_TEST(pPOIs->Add(ptsPOI), S_OK);

      // superstructuremember 0 - only on cantilever
      loc = 0.0;
      for (int i=1001; i<1006; i++)
      {
         CComPtr<IPOI> pPOI;
         TRY_TEST(pPOI.CoCreateInstance( CLSID_POI ), S_OK );
         TRY_TEST( pPOI->put_ID(i), S_OK );
         TRY_TEST( pPOI->put_MemberType(mtSuperstructureMember), S_OK );
         TRY_TEST( pPOI->put_MemberID(0), S_OK );
         // special ssm poi at start of span so we pick up shear jump
         TRY_TEST( pPOI->put_Location(loc), S_OK );

         TRY_TEST(pPOIs->Add(pPOI), S_OK);
         loc += 2.5;
      }

      // superstructuremember 2
      loc = 65.0;
      for (int i=1101; i<1106; i++)
      {
         CComPtr<IPOI> pPOI;
         TRY_TEST(pPOI.CoCreateInstance( CLSID_POI ), S_OK );
         TRY_TEST( pPOI->put_ID(i), S_OK );
         TRY_TEST( pPOI->put_MemberType(mtSuperstructureMember), S_OK );
         TRY_TEST( pPOI->put_MemberID(2), S_OK );

         TRY_TEST( pPOI->put_Location(loc), S_OK );

         TRY_TEST(pPOIs->Add(pPOI), S_OK);
         loc += 2.5;
      }

      // support 1
      loc = 0.0;
      for (int i=20001; i<20012; i++)
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

      // temporary support 1
      loc = 0.0;
      for (int i=30001; i<30012; i++)
      {
         CComPtr<IPOI> pPOI;
         TRY_TEST(pPOI.CoCreateInstance( CLSID_POI ), S_OK );
         TRY_TEST( pPOI->put_ID(i), S_OK );
         TRY_TEST( pPOI->put_MemberType(mtTemporarySupport), S_OK );
         TRY_TEST( pPOI->put_MemberID(TS_ID), S_OK );
         TRY_TEST( pPOI->put_Location(loc), S_OK );
         TRY_TEST(pPOIs->Add(pPOI), S_OK);
         loc -= 0.1;
      }
   }

   // Load Groups
   CComPtr<ILoadGroups> pLoadGroups;
   TRY_TEST(psm->get_LoadGroups(&pLoadGroups), S_OK);

   TCHAR* lgns[]={_T("Point Loads"),_T("Distributed Loads")};
   for (long i = 0; i<2; i++)
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
   TRY_TEST(pPointLoad1->put_Location(0), S_OK);
   TRY_TEST(pPointLoad1->SetForce(0,-1000,0), S_OK);

   TRY_TEST(pPointLoad2->put_MemberType(mtSuperstructureMember), S_OK);
   TRY_TEST(pPointLoad2->put_MemberID(2), S_OK);
   TRY_TEST(pPointLoad2->put_Location(-1.0), S_OK);
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
   TRY_TEST(pDistributedLoad2->put_MemberID(2), S_OK);
   TRY_TEST(pDistributedLoad2->put_Direction(ldFy), S_OK);
   TRY_TEST(pDistributedLoad2->put_WStart(-100), S_OK);
   TRY_TEST(pDistributedLoad2->put_WEnd(-100), S_OK);
   TRY_TEST(pDistributedLoad2->put_StartLocation(-0.0), S_OK);
   TRY_TEST(pDistributedLoad2->put_EndLocation(-1.0), S_OK);

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
      sm = 1.5/6.75;
      sa = 1/9.0;
   }
   else
   {
      // 6' deep x 1' wide rect
      ea = 6.0  * e * factor;
      ei = 18.0 * e * factor;
      d  = 6.0;
      sm = 3.0/18.0;
      sa = 1/6.0;
   }

   TRY_TEST( pcs->put_EAForce(ea), S_OK );
   TRY_TEST( pcs->put_EIForce(ei), S_OK );
   TRY_TEST( pcs->put_EADefl(ea/2.), S_OK ); // deflection has 1/2 props
   TRY_TEST( pcs->put_EIDefl(ei/2.), S_OK );
   TRY_TEST( pcs->put_ThermalCoeff(1.5), S_OK );
   TRY_TEST( pcs->put_Depth(d), S_OK );

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

void CTestOverhang::CreateWithNoPOis()
{
   CComPtr<ILBAMModel> psm;
   psm.Attach( CreateModel(false) );

   // save input file off
   /////////////////////////////////////////////////////////////////////
   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("TestOverhangNoPois.xml")), S_OK );

      // get interface pointer to Save our cross section
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( psm.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );
      TRY_TEST( pss->Close(), S_OK );
   }
}