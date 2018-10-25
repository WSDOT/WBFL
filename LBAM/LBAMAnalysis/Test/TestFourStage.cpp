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

// TestFourStage.cpp: implementation of the CTestFourStage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestFourStage.h"
#include "..\AnalysisUtils.h"
#include <fstream>

#include "TestUtils.h"
#include "..\..\LBAMTestUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static void SetupSegment(ISegment* pseg, Float64 Length, Float64 E, Float64 A, Float64 I, Float64 Depth);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestFourStage::CTestFourStage()
{

}

CTestFourStage::~CTestFourStage()
{

}

HRESULT CTestFourStage::Test()
{
   // dump results to a file
   std::_tofstream os("FourStage.txt");

   // build a model and attach it to our load group response object

   CComPtr<ILBAMModel> psm;
   psm.Attach( CreateModel() );

   HRESULT hr;
   CComPtr<ILoadGroupResponse> plgr;
   TRY_TEST( plgr.CoCreateInstance(CLSID_LoadGroupForceResponse), S_OK );

   CComQIPtr<IDependOnLBAM> pctx(plgr);
   TRY_TEST( pctx->putref_Model(psm), S_OK );

   CComPtr<ILBAMFactory> poiu;
   TRY_TEST( poiu.CoCreateInstance(CLSID_LRFDFactory), S_OK );

   // get pois for superstructure to request results
   CComPtr<ILongArray> poilist;
   CComPtr<IDblArray> loclist;
   hr = poiu->GetSuperstructurePOIs(psm, &poilist, &loclist);

   // save input file off
   /////////////////////////////////////////////////////////////////////
   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("TestFourStage.xml")), S_OK );

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

   // determine which load groups are active
   CComPtr<IBstrArray> algs;
   CComQIPtr<IGetActiveLoadGroups> active_groups(plgr);
   active_groups->GetActiveLoadGroups(&algs);
   algs->get_Count(&cnt);
   TRY_TEST(cnt, 1);
   CComBSTR sw_nm;
   algs->get_Item(0,&sw_nm);
   TRY_TEST(sw_nm, "Self Weight");

   // compute forces for stage 1 Point Loads and print results to file

   CComPtr<ISectionResult3Ds> pres;
   hr = plgr->ComputeForces(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 1"), roGlobal, rsCumulative, &pres);
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

   pres = NULL;
   hr = plgr->ComputeForces(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 4"), roGlobal, rsCumulative, &pres);
   ATLASSERT(SUCCEEDED(hr));

   DumpSectionForceResults( os, poilist, pres, poi_locs);

   CComPtr<ISectionResult3Ds> pdefls;
   hr = plgr->ComputeDeflections(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 1"), rsCumulative, &pdefls);
   ATLASSERT(SUCCEEDED(hr));

   DumpDeflectionResults( os, poilist, pdefls, poi_locs);

   pdefls = NULL;
   hr = plgr->ComputeDeflections(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 2"), rsCumulative, &pdefls);
   ATLASSERT(SUCCEEDED(hr));

   DumpDeflectionResults( os, poilist, pdefls, poi_locs);

   pdefls = NULL;
   hr = plgr->ComputeDeflections(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 3"), rsCumulative, &pdefls);
   ATLASSERT(SUCCEEDED(hr));

   DumpDeflectionResults( os, poilist, pdefls, poi_locs);

   pdefls = NULL;
   hr = plgr->ComputeDeflections(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 4"), rsCumulative, &pdefls);
   ATLASSERT(SUCCEEDED(hr));

   DumpDeflectionResults( os, poilist, pdefls, poi_locs);

   // stresses
   CComPtr<ISectionStressResults> pstresses;
   hr = plgr->ComputeStresses(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 1"), rsCumulative, &pstresses);
   ATLASSERT(SUCCEEDED(hr));

   DumpStressResults( os, poilist, pstresses);

   pstresses = NULL;
   hr = plgr->ComputeStresses(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 2"), rsCumulative, &pstresses);
   ATLASSERT(SUCCEEDED(hr));

   DumpStressResults( os, poilist, pstresses);

   pstresses = NULL;
   hr = plgr->ComputeStresses(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 3"), rsCumulative, &pstresses);
   ATLASSERT(SUCCEEDED(hr));

   DumpStressResults( os, poilist, pstresses);

   pstresses = NULL;
   hr = plgr->ComputeStresses(_bstr_t("Self Weight"), poilist ,_bstr_t("Stage 4"), rsCumulative, &pstresses);
   ATLASSERT(SUCCEEDED(hr));

   DumpStressResults( os, poilist, pstresses);

   // get contraflexure locations
   CComQIPtr<IContraflexureResponse> pcontrf(plgr);

   {
      CComPtr<IDblArray> locs;
      hr =pcontrf->ComputeContraflexureLocations(_bstr_t("Stage 1"), &locs);
      ATLASSERT(SUCCEEDED(hr));

      CollectionIndexType size;
      locs->get_Count(&size);
      TRY_TEST(size==0,true);
   }

   {
      CComPtr<IDblArray> alocs;
      hr =pcontrf->ComputeContraflexureLocations(_bstr_t("Stage 2"), &alocs);
      ATLASSERT(SUCCEEDED(hr));

      TIArrayHelper<Float64, IDblArray,CollectionIndexType> locs(alocs);

      CollectionIndexType size = locs.Size();
      TRY_TEST(size,4);

      TRY_TEST( IsEqual(locs[0], 37.58181, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[1], 62.44067, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[2], 137.5593, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[3], 162.4181, 1.0e-4), true);
   }

   InZoneType zt;
   hr =pcontrf->get_IsPOIInContraflexureZone(104, _bstr_t("Stage 2"), &zt);
   ATLASSERT(SUCCEEDED(hr));
   TRY_TEST(zt, izOutside);

   hr =pcontrf->get_IsPOIInContraflexureZone(108, _bstr_t("Stage 2"), &zt);
   ATLASSERT(SUCCEEDED(hr));
   TRY_TEST(zt, izInside);

   {
      CComPtr<IDblArray> alocs;
      hr =pcontrf->ComputeContraflexureLocations(_bstr_t("Stage 3"), &alocs);
      ATLASSERT(SUCCEEDED(hr));

      TIArrayHelper<Float64, IDblArray,CollectionIndexType> locs(alocs);
      CollectionIndexType size = locs.Size();
      TRY_TEST(size,2);
      TRY_TEST( IsEqual(locs[0], 75.10389, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[1], 124.8961, 1.0e-4), true);
   }

   {
      CComPtr<IDblArray> alocs;

      hr =pcontrf->ComputeContraflexureLocations(_bstr_t("Stage 4"), &alocs);
      ATLASSERT(SUCCEEDED(hr));

      TIArrayHelper<Float64, IDblArray,CollectionIndexType> locs(alocs);
      CollectionIndexType size = locs.Size();
      TRY_TEST(size,2);
      TRY_TEST( IsEqual(locs[0], 75.10389, 1.0e-4), true);
      TRY_TEST( IsEqual(locs[1], 124.8961, 1.0e-4), true);
   }

   return S_OK;
}


void CTestFourStage::GetSSPoiLocs(ILongArray* pPoilist, ILBAMModel* pModel, std::vector<Float64>* poiLocs)
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

   TIArrayHelper<PoiIDType, ILongArray, CollectionIndexType> ppoilist(pPoilist);

   CollectionIndexType cnt = ppoilist.Size();
   for (CollectionIndexType i=0; i<cnt; i++)
   {
      PoiIDType poi_id = ppoilist[i];

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
         ATLASSERT(0); // we can only handle superstructure
   }
}


ILBAMModel* CTestFourStage::CreateModel()
{
   CComPtr<ILBAMModel> psm;
   TRY_TEST(psm.CoCreateInstance( CLSID_LBAMModel ), S_OK );
   Float64 d;

   // stages
   CComPtr<IStages> pStages;
   TRY_TEST(psm->get_Stages(&pStages), S_OK);

   CComPtr<IStage> pStage1, pStage2, pStage3, pStage4;
   TRY_TEST(pStage1.CoCreateInstance( CLSID_Stage ), S_OK );
   TRY_TEST(pStage2.CoCreateInstance( CLSID_Stage ), S_OK );
   TRY_TEST(pStage3.CoCreateInstance( CLSID_Stage ), S_OK );
   TRY_TEST(pStage4.CoCreateInstance( CLSID_Stage ), S_OK );
   TRY_TEST(pStage1->put_Name(_bstr_t("Stage 1")), S_OK );
   TRY_TEST(pStage2->put_Name(_bstr_t("Stage 2")), S_OK );
   TRY_TEST(pStage3->put_Name(_bstr_t("Stage 3")), S_OK );
   TRY_TEST(pStage4->put_Name(_bstr_t("Stage 4")), S_OK );
   TRY_TEST(pStages->Add(pStage1), S_OK);
   TRY_TEST(pStages->Add(pStage2), S_OK);
   TRY_TEST(pStages->Add(pStage3), S_OK);
   TRY_TEST(pStages->Add(pStage4), S_OK);

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
   // add SuperstructureMembers - four identical 50 long members in each stage
   // cannot use the same instance though because hinging is different for each
   CComPtr<ISuperstructureMember> pss_super0;
   TRY_TEST(pss_super0.CoCreateInstance( CLSID_SuperstructureMember ), S_OK );

   TRY_TEST(pss_super0->put_Length(50.0), S_OK);

   // segments are different for each stage
   CComPtr<ISegment> psegs1, psegs2, psegs3, psegs4;
   TRY_TEST( psegs1.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( psegs2.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( psegs3.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( psegs4.CoCreateInstance( CLSID_Segment ) , S_OK );
   Float64 E=1.0;
   SetupSegment(psegs1, 50.0, E, 1000.0, 10000.0, 5.0);
   TRY_TEST(pss_super0->AddSegment(_bstr_t("Stage 1"), psegs1), S_OK );
   SetupSegment(psegs2, 50.0, E, 1000.0, 10000.0, 5.0);
   TRY_TEST(pss_super0->AddSegment(_bstr_t("Stage 2"), psegs2), S_OK );
   SetupSegment(psegs3, 50.0, E, 1500.0, 20000.0, 5.0);
   TRY_TEST(pss_super0->AddSegment(_bstr_t("Stage 3"), psegs3), S_OK );
   SetupSegment(psegs4, 50.0, E, 1500.0, 20000.0, 5.0);
   TRY_TEST(pss_super0->AddSegment(_bstr_t("Stage 4"), psegs4), S_OK );

   // now we have one ssm that suits our needs - clone it, set hinges, and add it
   CComPtr<ISuperstructureMember> pss_super1,pss_super2,pss_super3;
   pss_super0->Clone(&pss_super1);
   pss_super0->Clone(&pss_super2);
   pss_super0->Clone(&pss_super3);

   pss_super0->SetEndRelease(ssRight,_bstr_t("Stage 2"),mrtPinned);
   pss_super1->SetEndRelease(ssLeft, _bstr_t("Stage 2"),mrtPinned);
   pss_super1->SetEndRelease(ssRight,_bstr_t("Stage 3"),mrtPinned);
   pss_super2->SetEndRelease(ssLeft, _bstr_t("Stage 3"),mrtPinned);
   pss_super2->SetEndRelease(ssRight,_bstr_t("Stage 2"),mrtPinned);
   pss_super3->SetEndRelease(ssLeft, _bstr_t("Stage 2"),mrtPinned);

   CComPtr<ISuperstructureMembers> pssms;
   TRY_TEST(psm->get_SuperstructureMembers(&pssms), S_OK);

   pssms->Add(pss_super0);
   pssms->Add(pss_super1);
   pssms->Add(pss_super2);
   pssms->Add(pss_super3);

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
   TRY_TEST(psup0->put_BoundaryCondition(bcRoller), S_OK);
   TRY_TEST(psups->Add(psup0), S_OK);

   // support 1
   TRY_TEST(psups->Add(psup1), S_OK);
   TRY_TEST(psup1->put_BoundaryCondition(bcFixed), S_OK);
   TRY_TEST(psup1->put_Length(15.0), S_OK);
 
   CComPtr<ISegment> psseg1;
   TRY_TEST( psseg1.CoCreateInstance( CLSID_Segment ) , S_OK );
   SetupSegment(psseg1, 15.0, E, 2000.0, 1000.0, 2.0);

   TRY_TEST(psup1->AddSegment(_bstr_t("Stage 1"), psseg1), S_OK );
   TRY_TEST(psup1->AddSegment(_bstr_t("Stage 2"), psseg1), S_OK );
   TRY_TEST(psup1->AddSegment(_bstr_t("Stage 3"), psseg1), S_OK );
   TRY_TEST(psup1->AddSegment(_bstr_t("Stage 4"), psseg1), S_OK );

   // support 2
   TRY_TEST(psup2->put_BoundaryCondition(bcRoller), S_OK);
   TRY_TEST(psups->Add(psup2), S_OK);

   // temporary supports
   // ======================
   CComPtr<ITemporarySupport> ptsup0;
   TRY_TEST(ptsup0.CoCreateInstance( CLSID_TemporarySupport ), S_OK );
   TRY_TEST(ptsup0->put_Length(10.0), S_OK);
   TRY_TEST(ptsup0->put_ID(10), S_OK);
   TRY_TEST(ptsup0->put_Location(-0.5), S_OK);
   TRY_TEST(ptsup0->put_BoundaryCondition(bcFixed), S_OK);
   TRY_TEST(ptsup0->put_StageRemoved(_bstr_t("Stage 3")), S_OK);
   TRY_TEST(ptsup0->AddSegment(_bstr_t("Stage 1"), psseg1), S_OK ); // use same properties as support 1
   TRY_TEST(ptsup0->AddSegment(_bstr_t("Stage 2"), psseg1), S_OK );
   TRY_TEST(ptsup0->AddSegment(_bstr_t("Stage 3"), psseg1), S_OK );
   TRY_TEST(ptsup0->AddSegment(_bstr_t("Stage 4"), psseg1), S_OK );

   // midway in span 0
   CComPtr<ITemporarySupports> ptsups0;
   TRY_TEST(pspn0->get_TemporarySupports(&ptsups0), S_OK);
   TRY_TEST(ptsups0->Add(ptsup0), S_OK);

   // midway in span 1
   CComPtr<ITemporarySupport> ptsup1;
   TRY_TEST(ptsup0->Clone(&ptsup1), S_OK);
   TRY_TEST(ptsup0->put_ID(11), S_OK);

   CComPtr<ITemporarySupports> ptsups1;
   TRY_TEST(pspn1->get_TemporarySupports(&ptsups1), S_OK);
   TRY_TEST(ptsups1->Add(ptsup1), S_OK);

   // POIs
   // ======================
   CComPtr<IPOIs> pPOIs;
   TRY_TEST(psm->get_POIs(&pPOIs), S_OK);

   // span 0
   long numincs = 16;
   Float64 loc = 0.0;
   long startval=101;
   for (int i=startval; i<=startval+numincs; i++) 
   {
      CComPtr<IPOI> pPOI;
      TRY_TEST(pPOI.CoCreateInstance( CLSID_POI ), S_OK );
      TRY_TEST( pPOI->put_ID(i), S_OK );
      TRY_TEST( pPOI->put_MemberType(mtSpan), S_OK );
      TRY_TEST( pPOI->put_MemberID(0), S_OK );
      TRY_TEST( pPOI->put_Location(loc), S_OK );
      TRY_TEST(pPOIs->Add(pPOI), S_OK);
      loc -= 1.0/(Float64)numincs;
   }

   // just to the right of ts in span 0
   CComPtr<IPOI> pPOIts0;
   TRY_TEST(pPOIts0.CoCreateInstance( CLSID_POI ), S_OK );
   TRY_TEST( pPOIts0->put_ID(10007), S_OK );
   TRY_TEST( pPOIts0->put_MemberType(mtSpan), S_OK );
   TRY_TEST( pPOIts0->put_MemberID(0), S_OK );
   TRY_TEST( pPOIts0->put_Location(-0.50001), S_OK );
   TRY_TEST(pPOIs->Add(pPOIts0), S_OK);


   // span 1
   loc = 0.0;
   startval=201;
   for (int i=startval; i<=startval+numincs; i++) 
   {
      CComPtr<IPOI> pPOI;
      TRY_TEST(pPOI.CoCreateInstance( CLSID_POI ), S_OK );
      TRY_TEST( pPOI->put_ID(i), S_OK );
      TRY_TEST( pPOI->put_MemberType(mtSpan), S_OK );
      TRY_TEST( pPOI->put_MemberID(1), S_OK );
      TRY_TEST( pPOI->put_Location(loc), S_OK );
      TRY_TEST(pPOIs->Add(pPOI), S_OK);
      loc -= 1.0/(Float64)numincs;
   }

   // just to the right of ts in span 1
   CComPtr<IPOI> pPOIts1;
   TRY_TEST(pPOIts1.CoCreateInstance( CLSID_POI ), S_OK );
   TRY_TEST( pPOIts1->put_ID(10017), S_OK );
   TRY_TEST( pPOIts1->put_MemberType(mtSpan), S_OK );
   TRY_TEST( pPOIts1->put_MemberID(1), S_OK );
   TRY_TEST( pPOIts1->put_Location(-0.50001), S_OK );
   TRY_TEST(pPOIs->Add(pPOIts1), S_OK);


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

   // temporary support 10
   loc = 0.0;
   for (int i=3001; i<3012; i++)
   {
      CComPtr<IPOI> pPOI;
      TRY_TEST(pPOI.CoCreateInstance( CLSID_POI ), S_OK );
      TRY_TEST( pPOI->put_ID(i), S_OK );
      TRY_TEST( pPOI->put_MemberType(mtTemporarySupport), S_OK );
      TRY_TEST( pPOI->put_MemberID(10), S_OK );
      TRY_TEST( pPOI->put_Location(loc), S_OK );
      TRY_TEST(pPOIs->Add(pPOI), S_OK);
      loc -= 0.1;
   }

   // temporary support 11
   loc = 0.0;
   for (int i=4001; i<4012; i++)
   {
      CComPtr<IPOI> pPOI;
      TRY_TEST(pPOI.CoCreateInstance( CLSID_POI ), S_OK );
      TRY_TEST( pPOI->put_ID(i), S_OK );
      TRY_TEST( pPOI->put_MemberType(mtTemporarySupport), S_OK );
      TRY_TEST( pPOI->put_MemberID(11), S_OK );
      TRY_TEST( pPOI->put_Location(loc), S_OK );
      TRY_TEST(pPOIs->Add(pPOI), S_OK);
      loc -= 0.1;
   }

   // muck with stress points at some pois
   CComPtr<IStressPoints> new_sps;
   TRY_TEST(new_sps.CoCreateInstance(CLSID_StressPoints), S_OK);
   CComPtr<IStressPoint> new_sp0,new_sp1;
   TRY_TEST(new_sp0.CoCreateInstance(CLSID_StressPoint), S_OK);
   TRY_TEST(new_sp1.CoCreateInstance(CLSID_StressPoint), S_OK);
   TRY_TEST(new_sp0->put_Sa( 0.001), S_OK);
   TRY_TEST(new_sp0->put_Sm( 0.0015), S_OK);
   TRY_TEST(new_sp1->put_Sa( 0.001), S_OK);
   TRY_TEST(new_sp1->put_Sm(-0.0015), S_OK);
   TRY_TEST(new_sps->Add(new_sp0), S_OK);
   TRY_TEST(new_sps->Add(new_sp1), S_OK);

   CComPtr<IPOI> poi_103;  
   TRY_TEST(pPOIs->Find(103, &poi_103), S_OK);
   CComPtr<IPOIStressPoints> poisps_103;
   TRY_TEST(poi_103->get_POIStressPoints(&poisps_103), S_OK);
   TRY_TEST(poisps_103->Insert(CComBSTR("Stage 4"), new_sps, new_sps), S_OK);

   CComPtr<IPOI> poi_104;  
   TRY_TEST(pPOIs->Find(104, &poi_104), S_OK);
   CComPtr<IPOIStressPoints> poisps_104;
   TRY_TEST(poi_104->get_POIStressPoints(&poisps_104), S_OK);
   TRY_TEST(poisps_104->Insert(CComBSTR("Stage 4"), new_sps, new_sps), S_OK);

   CComPtr<IPOI> poi_105;  
   TRY_TEST(pPOIs->Find(105, &poi_105), S_OK);
   CComPtr<IPOIStressPoints> poisps_105;
   TRY_TEST(poi_105->get_POIStressPoints(&poisps_105), S_OK);
   TRY_TEST(poisps_105->Insert(CComBSTR("Stage 4"), new_sps, new_sps), S_OK);

   // Load Groups
   CComPtr<ILoadGroups> pLoadGroups;
   TRY_TEST(psm->get_LoadGroups(&pLoadGroups), S_OK);

   // create an empty bogus load group
   CComPtr<ILoadGroup> pLoadGroupb;
   TRY_TEST(pLoadGroupb.CoCreateInstance( CLSID_LoadGroup ), S_OK );
   TRY_TEST( pLoadGroupb->put_Name( CComBSTR("Empty Bogus") ), S_OK );
   TRY_TEST(pLoadGroups->Add(pLoadGroupb), S_OK);

   CComPtr<ILoadGroup> pLoadGroup;
   TRY_TEST(pLoadGroup.CoCreateInstance( CLSID_LoadGroup ), S_OK );
   TRY_TEST( pLoadGroup->put_Name( CComBSTR("Self Weight") ), S_OK );
   TRY_TEST(pLoadGroups->Add(pLoadGroup), S_OK);

   // Distributed Self weight loads in stages 1, 2, 4
   CComPtr<IDistributedLoads> pDistributedLoads;
   TRY_TEST(psm->get_DistributedLoads(&pDistributedLoads), S_OK);

   // create first for span 0 and then clone for span 1
   CComPtr<IDistributedLoadItem> pDLI01, pDLI02, pDLI04,pDLI11, pDLI12, pDLI14;
   CComPtr<IDistributedLoad> pDistributedLoad01, pDistributedLoad02, pDistributedLoad04;
   CComPtr<IDistributedLoad> pDistributedLoad11, pDistributedLoad12, pDistributedLoad14;
   TRY_TEST(pDistributedLoad01.CoCreateInstance( CLSID_DistributedLoad ), S_OK );
   TRY_TEST(pDistributedLoad02.CoCreateInstance( CLSID_DistributedLoad ), S_OK );
   TRY_TEST(pDistributedLoad04.CoCreateInstance( CLSID_DistributedLoad ), S_OK );

   // span 0, stage 1
   TRY_TEST(pDistributedLoad01->put_MemberType(mtSpan), S_OK);
   TRY_TEST(pDistributedLoad01->put_MemberID(0), S_OK);
   TRY_TEST(pDistributedLoad01->put_Direction(ldFy), S_OK);
   TRY_TEST(pDistributedLoad01->put_WStart(-1.), S_OK);
   TRY_TEST(pDistributedLoad01->put_WEnd(-1.), S_OK);
   TRY_TEST(pDistributedLoad01->put_StartLocation(0.0), S_OK);
   TRY_TEST(pDistributedLoad01->put_EndLocation(-1.0), S_OK);

   TRY_TEST(pDistributedLoads->Add(_bstr_t("Stage 1"), _bstr_t("Self Weight"), pDistributedLoad01, &pDLI01), S_OK);
   // span 1
   pDistributedLoad01->Clone(&pDistributedLoad11);
   TRY_TEST(pDistributedLoad11->put_MemberID(1), S_OK);
   TRY_TEST(pDistributedLoads->Add(_bstr_t("Stage 1"), _bstr_t("Self Weight"), pDistributedLoad11, &pDLI11), S_OK);

   // span 0, stage 2
   TRY_TEST(pDistributedLoad02->put_MemberType(mtSpan), S_OK);
   TRY_TEST(pDistributedLoad02->put_MemberID(0), S_OK);
   TRY_TEST(pDistributedLoad02->put_Direction(ldFy), S_OK);
   TRY_TEST(pDistributedLoad02->put_WStart(-0.5), S_OK);
   TRY_TEST(pDistributedLoad02->put_WEnd(-0.5), S_OK);
   TRY_TEST(pDistributedLoad02->put_StartLocation(0.0), S_OK);
   TRY_TEST(pDistributedLoad02->put_EndLocation(-1.0), S_OK);

   TRY_TEST(pDistributedLoads->Add(_bstr_t("Stage 2"), _bstr_t("Self Weight"), pDistributedLoad02, &pDLI02), S_OK);
   // span 1
   pDistributedLoad02->Clone(&pDistributedLoad12);
   TRY_TEST(pDistributedLoad12->put_MemberID(1), S_OK);
   TRY_TEST(pDistributedLoads->Add(_bstr_t("Stage 2"), _bstr_t("Self Weight"), pDistributedLoad12, &pDLI12), S_OK);

   // span 0, stage 4
   TRY_TEST(pDistributedLoad04->put_MemberType(mtSpan), S_OK);
   TRY_TEST(pDistributedLoad04->put_MemberID(0), S_OK);
   TRY_TEST(pDistributedLoad04->put_Direction(ldFy), S_OK);
   TRY_TEST(pDistributedLoad04->put_WStart(-0.1), S_OK);
   TRY_TEST(pDistributedLoad04->put_WEnd(-0.1), S_OK);
   TRY_TEST(pDistributedLoad04->put_StartLocation(0.0), S_OK);
   TRY_TEST(pDistributedLoad04->put_EndLocation(-1.0), S_OK);

   TRY_TEST(pDistributedLoads->Add(_bstr_t("Stage 4"), _bstr_t("Self Weight"), pDistributedLoad04, &pDLI04), S_OK);
   // span 1
   pDistributedLoad04->Clone(&pDistributedLoad14);
   TRY_TEST(pDistributedLoad14->put_MemberID(1), S_OK);
   TRY_TEST(pDistributedLoads->Add(_bstr_t("Stage 4"), _bstr_t("Self Weight"), pDistributedLoad14, &pDLI14), S_OK);

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

void SetupSegment(ISegment* pseg, Float64 Length, Float64 E, Float64 A, Float64 I, Float64 Depth)
{
   CComPtr<ISegmentCrossSection> pcs;
   TRY_TEST(pcs.CoCreateInstance( CLSID_SegmentCrossSection ), S_OK );

   Float64 ea, ei;
   Float64 sm, sa;
   ea = E*A;
   ei = E*I;
   sm = Depth/I;
   sa = 1/A;

   TRY_TEST( pcs->put_EAForce(ea), S_OK );
   TRY_TEST( pcs->put_EIForce(ei), S_OK );
   TRY_TEST( pcs->put_EADefl(ea), S_OK );
   TRY_TEST( pcs->put_EIDefl(ei), S_OK );
   TRY_TEST( pcs->put_ThermalCoeff(1.0), S_OK );
   TRY_TEST( pcs->put_Depth(Depth), S_OK );

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
   TRY_TEST( pseg->put_Length(Length), S_OK);
}
