///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner Test - Test driver for LBAM analysis library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// TestLoadCombiner.cpp: implementation of the TestLoadCombiner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestLoadCombiner.h"

#include <string>
#include <fstream>
#include <MathEx.h>
#include "..\..\LBAMTestUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TEST_MODEL_HOSED() TRY_TEST(pMe->m_csModelHosedFired, true); pMe->InitFired();
#define TEST_COMBO_CHANGED() TRY_TEST(pMe->m_csCombinationChangedFired, true); pMe->InitFired();

static HRESULT CreateSimpleLBAM(ILBAMModel** model);

inline HRESULT CreateDistributedLoad(IDistributedLoads* dls, BSTR stage, BSTR loadGroup, MemberIDType mbrId, MemberType mType, Float64 ldVal)
{
   CComPtr<IDistributedLoad> dl;
   TRY_TEST( dl.CoCreateInstance(CLSID_DistributedLoad), S_OK);
   TRY_TEST( dl->put_Direction(ldFy), S_OK);
   TRY_TEST( dl->put_MemberID(mbrId), S_OK);
   TRY_TEST( dl->put_MemberType(mType), S_OK);
   TRY_TEST( dl->put_StartLocation(0.0), S_OK);
   TRY_TEST( dl->put_EndLocation(-1.0), S_OK);
   TRY_TEST( dl->put_WStart(ldVal), S_OK);
   TRY_TEST( dl->put_WEnd(ldVal), S_OK);
   TRY_TEST( dls->Add(stage, loadGroup,dl,nullptr), S_OK);
   return S_OK;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TestLoadCombiner::TestLoadCombiner():
m_csModelHosedFired(false),
m_csCombinationChangedFired(false),
m_Cookie(0)
{

}

TestLoadCombiner::~TestLoadCombiner()
{

}


void TestLoadCombiner::Test()
{
   // create a listener
   CComObject<TestLoadCombiner>* pMe;
   CComObject<TestLoadCombiner>::CreateInstance(&pMe);
   pMe->AddRef();

   // make an item to test
   CComPtr<ILoadCaseResponse> lc_response;
   TRY_TEST(lc_response.CoCreateInstance( CLSID_LoadCombiner ), S_OK );

   // create our lc context
   CComPtr<ILoadCombinationAnalysisContext> plclc;
   TRY_TEST(plclc.CoCreateInstance( CLSID_LoadCombinationAnalysisContext ), S_OK );
   
   // let's listen to it
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pMe);
   TRY_TEST(AtlAdvise(plclc,punk,IID_ILoadCombinationAnalysisContextEvents,&dwCookie),S_OK);

   // create a simple lbam model to analyze
   CComPtr<ILBAMModel> model;
   TRY_TEST(CreateSimpleLBAM(&model), S_OK);

   // leak testing
   {
      // create an analysis engine
      CComPtr<ILoadGroupResponse> response;
      TRY_TEST(response.CoCreateInstance(CLSID_LoadGroupForceResponse), S_OK);

      CComQIPtr<IDependOnLBAM> resctx(response);
      TRY_TEST(resctx->putref_Model(model), S_OK);

      // get influence and contraflexure interfaces
      CComQIPtr<IInfluenceLineResponse> influence(response);
      TRY_TEST(influence!=nullptr, true);

      CComQIPtr<ILiveLoadNegativeMomentRegion> contraflexure(response);
      TRY_TEST(contraflexure!=nullptr, true);

      CComQIPtr<IAnalysisPOIs> an_pois(response);
      TRY_TEST(an_pois!=nullptr, true);

      CComQIPtr<IGetDistributionFactors> dfs(response);
      TRY_TEST(dfs!=nullptr, true);

      CComQIPtr<IGetStressPoints> css(response);
      TRY_TEST(css!=nullptr, true);

      // need a live load analysis context
      CComPtr<IVehicularAnalysisContext> plvlc;
      TRY_TEST(plvlc.CoCreateInstance( CLSID_VehicularAnalysisContext ), S_OK );
      TRY_TEST(plvlc->Initialize(model, influence, contraflexure, an_pois, dfs, css), S_OK);

      // need a live loader
      CComPtr<ILiveLoadModelResponse> llmr;
      TRY_TEST(llmr.CoCreateInstance(CLSID_LiveLoadModelResponse), S_OK);
      CComQIPtr<IDependOnVehicularAnalysisContext> idvc(llmr);
      TRY_TEST(idvc!=nullptr, true);
      TRY_TEST(idvc->Initialize(plvlc), S_OK);

      CComPtr<IBasicVehicularResponse> bvr;
      TRY_TEST(bvr.CoCreateInstance(CLSID_BasicVehicularResponse), S_OK);
      CComQIPtr<IDependOnVehicularAnalysisContext> idvcb(bvr);
      TRY_TEST(idvcb!=nullptr, true);
      TRY_TEST(idvcb->Initialize(plvlc), S_OK);

      // now can initialize load combination context
      TRY_TEST(plclc->Initialize(model, response, llmr, bvr, an_pois, css), S_OK);
   }

   // initialize our load combiner with the context
   CComQIPtr<IDependOnLoadCombinationAnalysisContext> depctx(lc_response);
   TRY_TEST(depctx!=nullptr, true);
   TRY_TEST(depctx->Initialize(plclc), S_OK);

   // we can now go after some load case results
   CComPtr<IIDArray> poi_ids;
   poi_ids.CoCreateInstance(CLSID_IDArray);
   poi_ids->Add(2);  // middle of each span
   poi_ids->Add(7);

   {
      // Forces
      CComPtr<ISectionResult3Ds> results;
      TRY_TEST(lc_response->ComputeForces(CComBSTR("DC"), poi_ids, CComBSTR("Stage 1"), roGlobal, rsIncremental, &results), S_OK);
      IndexType cnt;
      TRY_TEST(results->get_Count(&cnt), S_OK);
      TRY_TEST(cnt, 2);

      Float64 fxl, fyl, mzl, fxr, fyr, mzr;
      CComPtr<ISectionResult3D> result;
      results->get_Item(0, &result);
      result->GetResult(&fxl, &fyl, &mzl, &fxr, &fyr, &mzr);
      result.Release();
      TRY_TEST(IsEqual(mzl,2562.5),true);
      TRY_TEST(IsEqual(fyl,32.291666666667), true);

      results->get_Item(1, &result);
      result->GetResult(&fxl, &fyl, &mzl, &fxr, &fyr, &mzr);
      TRY_TEST(IsEqual(mzl,1187.5),true);
      TRY_TEST(IsEqual(fyl,-38.75), true);
      result.Release();

      // load case with an empty load group
      results.Release();
      TRY_TEST(lc_response->ComputeForces(CComBSTR("DW"), poi_ids, CComBSTR("Stage 1"), roGlobal, rsIncremental, &results), S_OK);
      TRY_TEST(results->get_Count(&cnt), S_OK);
      TRY_TEST(cnt, 2);

      results->get_Item(0, &result);
      result->GetResult(&fxl, &fyl, &mzl, &fxr, &fyr, &mzr);
      result.Release();
      TRY_TEST(IsEqual(mzl,512.5),true);
      TRY_TEST(IsEqual(fyl,6.4583333333333), true);

      // empty load case
      results.Release();
      TRY_TEST(lc_response->ComputeForces(CComBSTR("Empty"), poi_ids, CComBSTR("Stage 1"), roGlobal, rsIncremental, &results), S_OK);
      TRY_TEST(results->get_Count(&cnt), S_OK);
      TRY_TEST(cnt, 2);

      results->get_Item(0, &result);
      result->GetResult(&fxl, &fyl, &mzl, &fxr, &fyr, &mzr);
      result.Release();
      TRY_TEST(IsEqual(mzl,0.0),true);
      TRY_TEST(IsEqual(fyl,0.0), true);

      // load case that doesn't exist
      results.Release();
      TRY_TEST(lc_response->ComputeForces(CComBSTR("NOGA"), poi_ids, CComBSTR("Stage 1"), roGlobal, rsIncremental, &results), LBAMC_E_LOADCASE_NO_EXIST);

      // stage that doesn't exist
      results.Release();
      TRY_TEST(lc_response->ComputeForces(CComBSTR("DW"), poi_ids, CComBSTR("Stage 2"), roGlobal, rsIncremental, &results), LBAMA_E_STAGE_NOT_FOUND);
   }


   {
      // Deflections
      CComPtr<ISectionResult3Ds> results;
      TRY_TEST(lc_response->ComputeDeflections(CComBSTR("DC"), poi_ids, CComBSTR("Stage 1"), rsIncremental, &results), S_OK);
      IndexType cnt;
      TRY_TEST(results->get_Count(&cnt), S_OK);
      TRY_TEST(cnt, 2);

      Float64 fxl, fyl, mzl, fxr, fyr, mzr;
      CComPtr<ISectionResult3D> result;
      results->get_Item(0, &result);
      result->GetResult(&fxl, &fyl, &mzl, &fxr, &fyr, &mzr);
      result.Release();
      TRY_TEST(IsEqual(mzl, 0.00033405),true);
      TRY_TEST(IsEqual(fyl,-0.05625000), true);

      results->get_Item(1, &result);
      result->GetResult(&fxl, &fyl, &mzl, &fxr, &fyr, &mzr);
      TRY_TEST(IsEqual(mzl,-0.0002783764),true);
      TRY_TEST(IsEqual(fyl,-0.01436781), true);
      result.Release();

      // load case with an empty load group
      results.Release();
      TRY_TEST(lc_response->ComputeDeflections(CComBSTR("DW"), poi_ids, CComBSTR("Stage 1"), rsIncremental, &results), S_OK);
      TRY_TEST(results->get_Count(&cnt), S_OK);
      TRY_TEST(cnt, 2);

      results->get_Item(0, &result);
      result->GetResult(&fxl, &fyl, &mzl, &fxr, &fyr, &mzr);
      result.Release();
      TRY_TEST(IsEqual(mzl,6.6810344827586e-005),true);
      TRY_TEST(IsEqual(fyl,-0.01125000), true);

      // empty load case
      results.Release();
      TRY_TEST(lc_response->ComputeDeflections(CComBSTR("Empty"), poi_ids, CComBSTR("Stage 1"), rsIncremental, &results), S_OK);
      TRY_TEST(results->get_Count(&cnt), S_OK);
      TRY_TEST(cnt, 2);

      results->get_Item(0, &result);
      result->GetResult(&fxl, &fyl, &mzl, &fxr, &fyr, &mzr);
      result.Release();
      TRY_TEST(IsEqual(mzl,0.0),true);
      TRY_TEST(IsEqual(fyl,0.0), true);

      // load case that doesn't exist
      results.Release();
      TRY_TEST(lc_response->ComputeDeflections(CComBSTR("NOGA"), poi_ids, CComBSTR("Stage 1"), rsIncremental, &results), LBAMC_E_LOADCASE_NO_EXIST);

      // stage that doesn't exist
      results.Release();
      TRY_TEST(lc_response->ComputeDeflections(CComBSTR("DW"), poi_ids, CComBSTR("Stage 2"), rsIncremental, &results), LBAMA_E_STAGE_NOT_FOUND);
   }

   {
      // Reactions
      CComPtr<IIDArray> spt_ids;
      spt_ids.CoCreateInstance(CLSID_IDArray);
      spt_ids->Add(0);  // middle of each span
      spt_ids->Add(1);
      spt_ids->Add(2);

      CComPtr<IResult3Ds> results;
      TRY_TEST(lc_response->ComputeReactions(CComBSTR("DC"), spt_ids, CComBSTR("Stage 1"), rsIncremental, &results), S_OK);
      IndexType cnt;
      TRY_TEST(results->get_Count(&cnt), S_OK);
      TRY_TEST(cnt, 3);

      Float64 rx, ry, rz;
      CComPtr<IResult3D> result;
      results->get_Item(0, &result);
      result->GetResult(&rx, &ry, &rz);
      result.Release();
      TRY_TEST(IsEqual(ry, 117.7083333333),true);
      TRY_TEST(IsEqual(rz, 0.00000000), true);

      result.Release();
      results->get_Item(1, &result);
      result->GetResult(&rx, &ry, &rz);
      result.Release();
      TRY_TEST(IsEqual(ry, 346.04166666667),true);
      TRY_TEST(IsEqual(rz, 0.00000000), true);

      // load case with an empty load group
      results.Release();
      TRY_TEST(lc_response->ComputeReactions(CComBSTR("DW"), spt_ids, CComBSTR("Stage 1"), rsIncremental, &results), S_OK);
      TRY_TEST(results->get_Count(&cnt), S_OK);
      TRY_TEST(cnt, 3);

      result.Release();
      results->get_Item(0, &result);
      result->GetResult(&rx, &ry, &rz);
      result.Release();
      TRY_TEST(IsEqual(ry, 23.541666666667),true);
      TRY_TEST(IsEqual(rz, 0.00000000), true);

      // empty load case
      results.Release();
      TRY_TEST(lc_response->ComputeReactions(CComBSTR("Empty"), spt_ids, CComBSTR("Stage 1"), rsIncremental, &results), S_OK);
      TRY_TEST(results->get_Count(&cnt), S_OK);
      TRY_TEST(cnt, 3);

      result.Release();
      results->get_Item(0, &result);
      result->GetResult(&rx, &ry, &rz);
      result.Release();
      TRY_TEST(IsEqual(ry, 0.000),true);
      TRY_TEST(IsEqual(rz, 0.000), true);

      // load case that doesn't exist
      results.Release();
      TRY_TEST(lc_response->ComputeReactions(CComBSTR("NOGA"), spt_ids, CComBSTR("Stage 1"), rsIncremental, &results), LBAMC_E_LOADCASE_NO_EXIST);

      // stage that doesn't exist
      results.Release();
      TRY_TEST(lc_response->ComputeReactions(CComBSTR("DW"), spt_ids, CComBSTR("Stage 2"), rsIncremental, &results), LBAMA_E_STAGE_NOT_FOUND);
   }

   // disconnect our connections
   TRY_TEST(AtlUnadvise(plclc,IID_ILoadCombinationAnalysisContextEvents,dwCookie),S_OK);

   pMe->Release();

}


HRESULT TestLoadCombiner::OnResultsChanged()
{
   m_csModelHosedFired = true;
   return S_OK;
}

HRESULT TestLoadCombiner::OnCombinationChanged(ComboType scope, BSTR combination)
{
   m_csCombinationChangedFired = true;
   return S_OK;
}

void TestLoadCombiner::InitFired()
{
   m_csModelHosedFired=false; 
   m_csCombinationChangedFired=false;
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
   hr = factory->CreateSimpleModel(span_lengths, 29000, 200, 2000, 20, model);
   TRY_TEST(hr, S_OK);

   // add some pois
   PoiIDType last_val;
   TRY_TEST(factory->GeneratePOIsOnSuperstructure(*model, 0, 4, &last_val), S_OK);

   // create some load groups with loads (or not)
   CComPtr<ILoadGroups> lgs;
   TRY_TEST( (*model)->get_LoadGroups(&lgs), S_OK);

   CComPtr<IDistributedLoads> dls;
   TRY_TEST( (*model)->get_DistributedLoads(&dls), S_OK);

   CComBSTR lgn_sw("Girder Self Weight");
   CComPtr<ILoadGroup> lgsw;
   TRY_TEST( lgsw.CoCreateInstance(CLSID_LoadGroup), S_OK);
   TRY_TEST( lgsw->put_Name(lgn_sw), S_OK);
   TRY_TEST( lgs->Add(lgsw), S_OK);
   CreateDistributedLoad(dls, CComBSTR("Stage 1"), lgn_sw, 0, mtSuperstructureMember, -2.0);

   CComBSTR lgn_ol("Overlay");
   CComPtr<ILoadGroup> lgol;
   TRY_TEST( lgol.CoCreateInstance(CLSID_LoadGroup), S_OK);
   TRY_TEST( lgol->put_Name(lgn_ol), S_OK);
   TRY_TEST( lgs->Add(lgol), S_OK);
   CreateDistributedLoad(dls, CComBSTR("Stage 1"), lgn_ol, 0, mtSuperstructureMember, -0.5);

   CComBSTR lgn_br("Barrier");
   CComPtr<ILoadGroup> lgbr;
   TRY_TEST( lgbr.CoCreateInstance(CLSID_LoadGroup), S_OK);
   TRY_TEST( lgbr->put_Name(lgn_br), S_OK);
   TRY_TEST( lgs->Add(lgbr), S_OK);
   CreateDistributedLoad(dls, CComBSTR("Stage 1"), lgn_br, 0, mtSuperstructureMember, -0.5);

   CComBSTR lgn_bg("Bogus");
   CComPtr<ILoadGroup> lgbg;
   TRY_TEST( lgbg.CoCreateInstance(CLSID_LoadGroup), S_OK);
   TRY_TEST( lgbg->put_Name(lgn_bg), S_OK);
   TRY_TEST( lgs->Add(lgbg), S_OK);

   // configure using lrfd table
   ConfigureLrfdLoadCombinations(*model);

   // create some load cases
   CComPtr<ILoadCases> lcs;
   TRY_TEST( (*model)->get_LoadCases(&lcs), S_OK);

   CComPtr<ILoadCase> lcdc;
   TRY_TEST( lcs->Find(CComBSTR("DC"),&lcdc), S_OK);
   lcdc->AddLoadGroup(lgn_sw);
   lcdc->AddLoadGroup(lgn_ol);

   CComPtr<ILoadCase> lcdw;
   TRY_TEST( lcs->Find(CComBSTR("DW"),&lcdw), S_OK);
   lcdw->AddLoadGroup(lgn_br);
   lcdw->AddLoadGroup(lgn_bg);

   // add a bogus empty load case
   CComPtr<ILoadCase> lc_empty;
   TRY_TEST(lc_empty.CoCreateInstance(CLSID_LoadCase), S_OK);
   lc_empty->put_Name(CComBSTR("Empty"));
   TRY_TEST( lcs->Add(lc_empty), S_OK);

   // add some live load action
   ConfigureLrfdLiveLoadModelInKipFeet(*model);

   return S_OK;
}
