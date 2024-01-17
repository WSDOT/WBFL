///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner Test - Test driver for LBAM analysis library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// TestLoadCombinationContext.cpp: implementation of the TestLoadCombinationContext class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestLoadCombinationContext.h"

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

static HRESULT CreatePOI(PoiIDType ID, MemberType Type, MemberIDType memberID, Float64 Location, IPOI** newPOI)
{
   CHECK_RETOBJ(newPOI);

   CHRException hr;

	CComPtr<IPOI> ppoi;
   hr = ppoi.CoCreateInstance(CLSID_POI);
   hr = ppoi->put_ID(ID);
   hr = ppoi->put_MemberType(Type);
   hr = ppoi->put_MemberID(memberID);
   hr = ppoi->put_Location(Location);

   return ppoi.CopyTo(newPOI);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TestLoadCombinationContext::TestLoadCombinationContext():
m_csModelHosedFired(false),
m_csCombinationChangedFired(false),
m_Cookie(0)
{

}

TestLoadCombinationContext::~TestLoadCombinationContext()
{

}


void TestLoadCombinationContext::Test()
{

   HRESULT hr;
   // create a listener
   CComObject<TestLoadCombinationContext>* pMe;
   CComObject<TestLoadCombinationContext>::CreateInstance(&pMe);
   pMe->AddRef();

   // make an item to test
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

      // now can initilize load combination context
      TRY_TEST(plclc->Initialize(model, response, llmr, bvr, an_pois, css), S_OK);
   }

   // test some event firing
   // ILoadCases
   CComQIPtr<ILoadCases> load_cases(plclc);
   TRY_TEST(!load_cases, false);
   IndexType cnt;
   TRY_TEST(load_cases->get_Count(&cnt), S_OK);
   TRY_TEST(cnt, 0);
   CComPtr<ILoadCase> load_case;
   load_case.CoCreateInstance(CLSID_LoadCase);
   TRY_TEST(load_case->put_Name(CComBSTR("DC")), S_OK);
   TRY_TEST(load_cases->Add(load_case), S_OK);
   TEST_COMBO_CHANGED()

   // ILoadCombinations
   CComQIPtr<ILoadCombinations> load_combos(plclc);
   TRY_TEST(!load_combos, false);
   TRY_TEST(load_combos->get_Count(&cnt), S_OK);
   TRY_TEST(cnt, 0);
   CComPtr<ILoadCombination> load_combo;
   load_combo.CoCreateInstance(CLSID_LoadCombination);
   TRY_TEST(load_combo->put_Name(CComBSTR("Service I")), S_OK);
   TRY_TEST(load_combos->Add(load_combo), S_OK);
   TEST_COMBO_CHANGED()

   // give it some overhangs
   CComPtr<ISuperstructureMembers> ssms;
   TRY_TEST( model->get_SuperstructureMembers(&ssms), S_OK);
   TRY_TEST(ssms->put_Offset(15.), S_OK);
   TEST_MODEL_HOSED()

   CComPtr<ISpans> spans;
   TRY_TEST( model->get_Spans(&spans), S_OK);
   CComPtr<ISpan> span;
   TRY_TEST( spans->get_Item(0,&span), S_OK);
   TRY_TEST(span->put_Length(100.), S_OK);
   TEST_MODEL_HOSED()

   // combination factors
   CComQIPtr<IGetCombinationFactors> poi_factors(plclc);
   TRY_TEST(!poi_factors, false);
   Float64 min_factor, max_factor;
   TRY_TEST(poi_factors->GetPOICombinationFactors(0, CComBSTR("Stage 1"), lctService, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.011);
   TRY_TEST(max_factor,11.011);
   TRY_TEST(poi_factors->GetPOICombinationFactors(2, CComBSTR("Stage 1"), lctService, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.011);
   TRY_TEST(max_factor,11.011);
   TRY_TEST(poi_factors->GetPOICombinationFactors(7, CComBSTR("Stage 1"), lctService, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.021);
   TRY_TEST(max_factor,11.021);
   TRY_TEST(poi_factors->GetPOICombinationFactors(10, CComBSTR("Stage 1"), lctService, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.021);
   TRY_TEST(max_factor,11.021);

   TRY_TEST(poi_factors->GetPOICombinationFactors(100, CComBSTR("Stage 1"), lctService, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.011);
   TRY_TEST(max_factor,11.011);
   TRY_TEST(poi_factors->GetPOICombinationFactors(101, CComBSTR("Stage 1"), lctService, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.011);
   TRY_TEST(max_factor,11.011);
   TRY_TEST(poi_factors->GetPOICombinationFactors(102, CComBSTR("Stage 1"), lctService, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.021);
   TRY_TEST(max_factor,11.021);
   TRY_TEST(poi_factors->GetPOICombinationFactors(103, CComBSTR("Stage 1"), lctService, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.021);
   TRY_TEST(max_factor,11.021);

   TRY_TEST(poi_factors->GetPOICombinationFactors(0, CComBSTR("Stage 1"), lctStrength, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.012);
   TRY_TEST(max_factor,11.012);
   TRY_TEST(poi_factors->GetPOICombinationFactors(2, CComBSTR("Stage 1"), lctStrength, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.012);
   TRY_TEST(max_factor,11.012);
   TRY_TEST(poi_factors->GetPOICombinationFactors(7, CComBSTR("Stage 1"), lctStrength, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.022);
   TRY_TEST(max_factor,11.022);
   TRY_TEST(poi_factors->GetPOICombinationFactors(10, CComBSTR("Stage 1"), lctStrength, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.022);
   TRY_TEST(max_factor,11.022);

   TRY_TEST(poi_factors->GetPOICombinationFactors(100, CComBSTR("Stage 1"), lctStrength, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.012);
   TRY_TEST(max_factor,11.012);
   TRY_TEST(poi_factors->GetPOICombinationFactors(101, CComBSTR("Stage 1"), lctStrength, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.012);
   TRY_TEST(max_factor,11.012);
   TRY_TEST(poi_factors->GetPOICombinationFactors(102, CComBSTR("Stage 1"), lctStrength, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.022);
   TRY_TEST(max_factor,11.022);
   TRY_TEST(poi_factors->GetPOICombinationFactors(103, CComBSTR("Stage 1"), lctStrength, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.022);
   TRY_TEST(max_factor,11.022);

   TRY_TEST(poi_factors->GetPOICombinationFactors(0, CComBSTR("Stage 1"), lctService, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.011);
   TRY_TEST(max_factor,11.011);
   TRY_TEST(poi_factors->GetPOICombinationFactors(2, CComBSTR("Stage 1"), lctService, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.011);
   TRY_TEST(max_factor,11.011);
   TRY_TEST(poi_factors->GetPOICombinationFactors(7, CComBSTR("Stage 1"), lctService, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.021);
   TRY_TEST(max_factor,11.021);
   TRY_TEST(poi_factors->GetPOICombinationFactors(10, CComBSTR("Stage 1"), lctService, &min_factor, &max_factor), S_OK);
   TRY_TEST(min_factor, 1.021);
   TRY_TEST(max_factor,11.021);

   // see if we can get a response for load group results
   CComQIPtr<ILoadGroupResponse> lgres(plclc);
   TRY_TEST(!lgres, false);
   CComPtr<IIDArray> poi_ids;
   poi_ids.CoCreateInstance(CLSID_IDArray);
   poi_ids->Add(3);
   poi_ids->Add(7);
   CComPtr<ISectionResult3Ds> pres;
   TRY_TEST( lgres->ComputeForces(_bstr_t("Self Weight"), poi_ids ,_bstr_t("Stage 1"), roGlobal, rsCumulative, &pres), S_OK);
   pres->get_Count(&cnt);
   TRY_TEST(cnt, 2);

   // get a live load response
   CComQIPtr<ILiveLoadModelResponse> vehres(plclc);
   TRY_TEST(!vehres, false);
   CComPtr<ILiveLoadModelSectionResults> veh_results;
   hr = vehres->ComputeForces(poi_ids, _bstr_t("Stage 1"), lltDesign, roGlobal,
								     fetMz, optMaximize, vlcTruckPlusLane, VARIANT_TRUE, VARIANT_TRUE, 
                             VARIANT_FALSE, &veh_results);
   veh_results->get_Count(&cnt);
   TRY_TEST(cnt, 2);

   // get list of active load groups
   CComPtr<IBstrArray> lgs;
   CComQIPtr<IGetActiveLoadGroups> igalg(plclc);
   TRY_TEST(!igalg, false);
   TRY_TEST(igalg->GetActiveLoadGroups(&lgs), S_OK);
   lgs->get_Count(&cnt);
   TRY_TEST(cnt,1);
   CComBSTR swn;
   lgs->get_Item(0, &swn);
   TRY_TEST(swn, "Self Weight");

   // disconnect our connections
   TRY_TEST(AtlUnadvise(plclc,IID_ILoadCombinationAnalysisContextEvents,dwCookie),S_OK);

   pMe->Release();

}


HRESULT TestLoadCombinationContext::OnResultsChanged()
{
   m_csModelHosedFired = true;
   return S_OK;
}

HRESULT TestLoadCombinationContext::OnCombinationChanged(ComboType scope, BSTR combination)
{
   m_csCombinationChangedFired = true;
   return S_OK;
}

void TestLoadCombinationContext::InitFired()
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

   // give it some overhangs
   CComPtr<ISuperstructureMembers> ssms;
   TRY_TEST( (*model)->get_SuperstructureMembers(&ssms), S_OK);
   TRY_TEST(ssms->put_Offset(10.), S_OK);
   CComPtr<ISuperstructureMember> ssm1;
   TRY_TEST(ssms->get_Item(0, &ssm1), S_OK);
   TRY_TEST(ssm1->put_Length(235.0), S_OK);

   // change loadmodifiers on spans and supports so we can test
   CComPtr<ISpans> spans;
   TRY_TEST( (*model)->get_Spans(&spans), S_OK);
   CComPtr<ISpan> span0, span1;
   TRY_TEST( spans->get_Item(0,&span0), S_OK);
   TRY_TEST( span0->SetLoadModifier(lctService,  1.011, 11.011), S_OK);
   TRY_TEST( span0->SetLoadModifier(lctStrength, 1.012, 11.012), S_OK);
   TRY_TEST( spans->get_Item(1,&span1), S_OK);
   TRY_TEST( span1->SetLoadModifier(lctService,  1.021, 11.021), S_OK);
   TRY_TEST( span1->SetLoadModifier(lctStrength, 1.022, 11.022), S_OK);

   CComPtr<ISupports> supports;
   TRY_TEST( (*model)->get_Supports(&supports), S_OK);
   CComPtr<ISupport> support0, support1;
   TRY_TEST( supports->get_Item(0,&support0), S_OK);
   TRY_TEST( support0->SetLoadModifier(lctService,  2.011, 12.011), S_OK);
   TRY_TEST( support0->SetLoadModifier(lctStrength, 2.012, 12.012), S_OK);
   TRY_TEST( supports->get_Item(1,&support1), S_OK);
   TRY_TEST( support1->SetLoadModifier(lctService,  2.021, 12.021), S_OK);
   TRY_TEST( support1->SetLoadModifier(lctStrength, 2.022, 12.022), S_OK);

   // add some pois
   PoiIDType last_val;
   TRY_TEST(factory->GeneratePOIsOnSuperstructure(*model, 0, 4, &last_val), S_OK);

   CComPtr<IPOIs> pois;
   (*model)->get_POIs(&pois);
   CComPtr<IPOI> poi;
   TRY_TEST( CreatePOI(100, mtSuperstructureMember, 0, 2.0, &poi), S_OK);
   TRY_TEST(pois->Add(poi), S_OK);
   poi.Release();
   TRY_TEST( CreatePOI(101, mtSuperstructureMember, 0, 52.0, &poi), S_OK);
   TRY_TEST(pois->Add(poi), S_OK);
   poi.Release();
   TRY_TEST( CreatePOI(102, mtSuperstructureMember, 0, 152.0, &poi), S_OK);
   TRY_TEST(pois->Add(poi), S_OK);
   poi.Release();
   TRY_TEST( CreatePOI(103, mtSuperstructureMember, 0, 232.0, &poi), S_OK);
   TRY_TEST(pois->Add(poi), S_OK);
   poi.Release();

   // put a uniform load across the entire superstructure
   CComPtr<ILoadGroups> lgs;
   TRY_TEST( (*model)->get_LoadGroups(&lgs), S_OK);
   CComPtr<ILoadGroup> lg;
   TRY_TEST( lg.CoCreateInstance(CLSID_LoadGroup), S_OK);
   TRY_TEST( lg->put_Name(CComBSTR("Self Weight")), S_OK);
   TRY_TEST( lgs->Add(lg), S_OK);

   CComPtr<IDistributedLoads> dls;
   TRY_TEST( (*model)->get_DistributedLoads(&dls), S_OK);
   CComPtr<IDistributedLoad> dl;
   TRY_TEST( dl.CoCreateInstance(CLSID_DistributedLoad), S_OK);
   TRY_TEST( dl->put_Direction(ldFy), S_OK);
   TRY_TEST( dl->put_MemberID(0), S_OK);
   TRY_TEST( dl->put_MemberType(mtSuperstructureMember), S_OK);
   TRY_TEST( dl->put_StartLocation(0.0), S_OK);
   TRY_TEST( dl->put_EndLocation(-1.0), S_OK);
   TRY_TEST( dl->put_WStart(-2.0), S_OK);
   TRY_TEST( dl->put_WEnd(-2.0), S_OK);
   TRY_TEST(  dls->Add(CComBSTR("Stage 1"), CComBSTR("Self Weight"),dl,nullptr), S_OK);

   // add some live load action
   ConfigureLrfdLiveLoadModelInKipFeet(*model);

   return S_OK;
}
