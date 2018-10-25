///////////////////////////////////////////////////////////////////////
// LBAM Live Load Test - Test driver for LBAM analysis library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// TestVehicularLoadContext.cpp: implementation of the TestVehicularLoadContext class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestVehicularLoadContext.h"

#include <string>
#include <fstream>
#include <MathEx.h>
#include "..\..\LBAMTestUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TEST_MODEL_HOSED() TRY_TEST(pMe->m_csModelHosedFired, true); pMe->m_csModelHosedFired=false; pMe->m_csLiveLoadChangedFired=false;
#define TEST_LL_CHANGED() TRY_TEST(pMe->m_csLiveLoadChangedFired, true); pMe->m_csModelHosedFired=false; pMe->m_csLiveLoadChangedFired=false;

HRESULT CreateSimpleLBAM(ILBAMModel** model);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TestVehicularLoadContext::TestVehicularLoadContext():
m_csModelHosedFired(false),
m_csLiveLoadChangedFired(false),
m_Cookie(0)
{

}

TestVehicularLoadContext::~TestVehicularLoadContext()
{

}

void TestVehicularLoadContext::Test()
{
   // create a listener
   CComObject<TestVehicularLoadContext>* pMe;
   CComObject<TestVehicularLoadContext>::CreateInstance(&pMe);
   pMe->AddRef();

   // make an item to test
   CComPtr<IVehicularAnalysisContext> pllc;
   TRY_TEST(pllc.CoCreateInstance( CLSID_VehicularAnalysisContext ), S_OK );

   // let's listen to it
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pMe);
   TRY_TEST(AtlAdvise(pllc,punk,IID_IVehicularAnalysisContextEvents,&dwCookie),S_OK);

   // create a simple lbam model to analyze
   CComPtr<ILBAMModel> model;
   TRY_TEST(CreateSimpleLBAM(&model), S_OK);

   // leak testing
   {
      // create an analysis engine
      CComPtr<ILoadGroupResponse> response;
      TRY_TEST(response.CoCreateInstance(CLSID_LoadGroupForceResponse), S_OK);

      CComQIPtr<IDependOnLBAM> respctx(response);
      TRY_TEST(respctx->putref_Model(model), S_OK);

      // get influence and contraflexure interfaces
      CComQIPtr<IInfluenceLineResponse> influence(response);
      TRY_TEST(influence!=NULL, true);

      CComQIPtr<ILiveLoadNegativeMomentRegion> contraflexure(response);
      TRY_TEST(contraflexure!=NULL, true);

      CComQIPtr<IAnalysisPOIs> an_pois(response);
      TRY_TEST(an_pois!=NULL, true);

      CComQIPtr<IGetDistributionFactors> igdf(response);
      TRY_TEST(igdf!=NULL, true);

      CComQIPtr<IGetStressPoints> igcs(response);
      TRY_TEST(igcs!=NULL, true);

      TRY_TEST(pllc->Initialize(model, influence, contraflexure, an_pois, igdf, igcs), S_OK);
   }

   // ISupportLocations
   CComQIPtr<ISupportLocations> support_locs(pllc);
   TRY_TEST(!support_locs, false);
   Float64 val;
   TRY_TEST(support_locs->get_LeftOverhang(&val), S_OK);
   TRY_TEST(val, 10.0);
   TRY_TEST(support_locs->get_RightOverhang(&val), S_OK);
   TRY_TEST(val, 5.0);
   CComPtr<IDblArray> alocs;
   TRY_TEST(support_locs->get_SupportLocations(&alocs), S_OK);

   TIArrayHelper<Float64, IDblArray, SupportIDType> locs(alocs);
   TRY_TEST(locs.Size(), 3);
   TRY_TEST(locs[0], 0.0);
   TRY_TEST(locs[1], 120.0);
   TRY_TEST(locs[2], 220.0);

   // IGetDistributionFactors
   CComBSTR bs_stage1("Stage 1");
   CComQIPtr<IGetDistributionFactors> poi_dfs(pllc);
   Float64 df;
   CComQIPtr<IDistributionFactor> df1, df2;
   TRY_TEST(!poi_dfs, false);
   TRY_TEST(poi_dfs->GetPOIDistributionFactor(0, bs_stage1, &df1, &df2), S_OK);
   TRY_TEST(df1->get_GPMMul(&df), S_OK);
   TRY_TEST(df, 2);
   TRY_TEST(df2, NULL);
   df1.Release(); df2.Release();
   TRY_TEST(poi_dfs->GetPOIDistributionFactor(1, bs_stage1, &df1, &df2), S_OK);
   TRY_TEST(df1->get_GPMMul(&df), S_OK);
   TRY_TEST(df, 2);
   TRY_TEST(df2, NULL);
   df1.Release(); df2.Release();
   TRY_TEST(poi_dfs->GetPOIDistributionFactor(6, bs_stage1, &df1, &df2), S_OK);
   TRY_TEST(df1->get_GPMMul(&df), S_OK);
   TRY_TEST(df, 2);
   TRY_TEST(df2->get_GPMMul(&df), S_OK);
   TRY_TEST(df, 3);
   df1.Release(); df2.Release();
   TRY_TEST(poi_dfs->GetPOIDistributionFactor(7, bs_stage1, &df1, &df2), S_OK);
   TRY_TEST(df1->get_GPMMul(&df), S_OK);
   TRY_TEST(df, 2);
   TRY_TEST(df2->get_GPMMul(&df), S_OK);
   TRY_TEST(df, 3);
   df1.Release(); df2.Release();
   TRY_TEST(poi_dfs->GetPOIDistributionFactor(10,bs_stage1, &df1, &df2), S_OK);
   TRY_TEST(df1->get_GPMMul(&df), S_OK);
   TRY_TEST(df, 3);
   TRY_TEST(df2, NULL);
   df1.Release(); df2.Release();
   TRY_TEST(poi_dfs->GetPOIDistributionFactor(13,bs_stage1, &df1, &df2), S_OK);
   TRY_TEST(df1->get_GPMMul(&df), S_OK);
   TRY_TEST(df, 3);
   TRY_TEST(df2, NULL);
   df1.Release(); df2.Release();

   // test some event firing
   // give it some overhangs
   CComPtr<ISuperstructureMembers> ssms;
   TRY_TEST( model->get_SuperstructureMembers(&ssms), S_OK);
   TRY_TEST(ssms->put_Offset(15.), S_OK);
   TEST_MODEL_HOSED()

   TRY_TEST(support_locs->get_RightOverhang(&val), S_OK);
   TRY_TEST(val, 0.0);

   CComPtr<ISpans> spans;
   TRY_TEST( model->get_Spans(&spans), S_OK);
   CComPtr<ISpan> span;
   TRY_TEST( spans->get_Item(0,&span), S_OK);
   TRY_TEST(span->put_Length(100.), S_OK);
   TEST_MODEL_HOSED()

   CComQIPtr<ILiveLoad> liveload(pllc);
   TRY_TEST(!liveload, false);
   CComPtr<ILiveLoadModel> dllm;
   TRY_TEST( liveload->get_Design(&dllm), S_OK);
   TRY_TEST(dllm->put_Name(CComBSTR("Design Truck")), S_OK);
   TEST_LL_CHANGED()

   CComQIPtr<IInfluenceLineResponse> infres(pllc);
   TRY_TEST(!infres, false);
   CComPtr<IInfluenceLine> lft_infline, rgt_infline;
   TRY_TEST(infres->ComputeForceInfluenceLine(1,CComBSTR("Stage 1"), fetMz, roGlobal, &lft_infline, &rgt_infline), S_OK);

   CComQIPtr<ILiveLoadNegativeMomentRegion> contrf(pllc);
   TRY_TEST(!contrf, false);
   CComPtr<IDblArray> cfpnts;
   TRY_TEST(contrf->ComputeNegativeMomentRegions(CComBSTR("Stage 1"), &cfpnts), S_OK);
   CollectionIndexType lsz;
   cfpnts->get_Count(&lsz);
   TRY_TEST(lsz, 6); 

   // disconnect our connections
   TRY_TEST(AtlUnadvise(pllc,IID_IVehicularAnalysisContextEvents,dwCookie),S_OK);
   pMe->Release();
}

HRESULT TestVehicularLoadContext::OnLiveLoadChanged( LiveLoadModelType type)
{
   m_csLiveLoadChangedFired = true;

   return S_OK;
}

HRESULT TestVehicularLoadContext::OnStiffnessResponseChanged(ChangeScopeType scope, PoiIDType poiID)
{
   m_csModelHosedFired = true;

   return S_OK;
}

HRESULT CreateSimpleLBAM(ILBAMModel** model)
{
   HRESULT hr;
   // create a simple two span model
   CComPtr<ILBAMFactory> factory;
   TRY_TEST(factory.CoCreateInstance(CLSID_LRFDFactory), S_OK);
   CComPtr<IDblArray> span_lengths;
   span_lengths.CoCreateInstance(CLSID_DblArray);
   span_lengths->Add(120);
   span_lengths->Add(100);
   hr = factory->CreateSimpleModel(span_lengths, 1, 1, 1, 1, model);
   TRY_TEST(hr, S_OK);

   // give it some overhangs
   CComPtr<ISuperstructureMembers> ssms;
   TRY_TEST( (*model)->get_SuperstructureMembers(&ssms), S_OK);
   TRY_TEST(ssms->put_Offset(10.), S_OK);
   CComPtr<ISuperstructureMember> ssm1;
   TRY_TEST(ssms->get_Item(0, &ssm1), S_OK);
   TRY_TEST(ssm1->put_Length(235.0), S_OK);

   // set up some distribution factors
   CComPtr<IDistributionFactors> dfs;
   TRY_TEST((*model)->get_DistributionFactors(&dfs), S_OK);
   CComPtr<IDistributionFactor> df1, df2;
   TRY_TEST(df1.CoCreateInstance(CLSID_DistributionFactor), S_OK);
   TRY_TEST(df2.CoCreateInstance(CLSID_DistributionFactor), S_OK);
   TRY_TEST(df1->SetG(2,2,2,2,2,2,2,2,2,2,2,2,2,2,2), S_OK);
   TRY_TEST(df2->SetG(3,3,3,3,3,3,3,3,3,3,3,3,2,2,2), S_OK);
   CComPtr<IDistributionFactorSegment> dfs1, dfs2;
   TRY_TEST(dfs1.CoCreateInstance(CLSID_DistributionFactorSegment), S_OK);
   TRY_TEST(dfs2.CoCreateInstance(CLSID_DistributionFactorSegment), S_OK);
   TRY_TEST(dfs1->putref_DistributionFactor(df1), S_OK);
   TRY_TEST(dfs1->put_Length(130.0), S_OK);
   TRY_TEST(dfs2->putref_DistributionFactor(df2), S_OK);
   TRY_TEST(dfs2->put_Length(100.0), S_OK);
   TRY_TEST(dfs->Add(dfs1), S_OK);
   TRY_TEST(dfs->Add(dfs2), S_OK);

   // add some pois
   PoiIDType last_val;
   TRY_TEST(factory->GeneratePOIsOnSuperstructure(*model, 0, 4, &last_val), S_OK);

   ConfigureLrfdLiveLoadModelInKipFeet(*model);
   ConfigureLrfdLoadCombinations(*model);

   // Save off to file for later inspection
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Combo.xml")), S_OK );

      // get interface pointer 
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( (*model)->QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );
      TRY_TEST( pss->Close(), S_OK );
   }

   return S_OK;
}
