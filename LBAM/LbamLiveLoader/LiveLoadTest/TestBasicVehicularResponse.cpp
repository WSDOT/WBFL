///////////////////////////////////////////////////////////////////////
// LBAM Live Load Test - Test driver for LBAM analysis library
// Copyright © 1999-2021  Washington State Department of Transportation
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

// TestBasicVehicularResponse.cpp: implementation of the TestBasicVehicularResponse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestBasicVehicularResponse.h"

#include <string>
#include <fstream>
#include <MathEx.h>
#include "..\..\LBAMTestUtils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static HRESULT CreateASimpleLBAM(ILBAMModel** model);
void GenerateLoadGroups(ILBAMModel* model, Float64 overhang);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TestBasicVehicularResponse::TestBasicVehicularResponse()
{

}

TestBasicVehicularResponse::~TestBasicVehicularResponse()
{

}

void TestBasicVehicularResponse::Test()
{
   HRESULT hr;
   CComObject<TestBasicVehicularResponse>* pMe;
   CComObject<TestBasicVehicularResponse>::CreateInstance(&pMe);
   pMe->AddRef();

   // lots of initializing to do.
   // set up response engine context
   CComPtr<IVehicularAnalysisContext> pllc;
   TRY_TEST(pllc.CoCreateInstance( CLSID_VehicularAnalysisContext ), S_OK );

   // create a simple lbam model to analyze
   CComPtr<ILBAMModel> model;
   TRY_TEST(CreateASimpleLBAM(&model), S_OK);

   // set it up with an lrfd live load model
   ConfigureLrfdLiveLoadModelInKipFeet(model);

   // create some load groups
   Float64 overhang = 10;
   GenerateLoadGroups(model, overhang);

   // create an analysis engine
   CComPtr<ILoadGroupResponse> response;
   TRY_TEST(response.CoCreateInstance(CLSID_LoadGroupForceResponse), S_OK);

   CComQIPtr<IDependOnLBAM> respctx(response);
   TRY_TEST(respctx->putref_Model(model), S_OK);

   // get influence and contraflexure interfaces
   CComQIPtr<IInfluenceLineResponse> influence(response);
   TRY_TEST(influence!=nullptr, true);

   CComQIPtr<IContraflexureResponse> contraflexure(response);
   TRY_TEST(contraflexure!=nullptr, true);

   CComQIPtr<ILiveLoadNegativeMomentRegion> llnmr(response);
   TRY_TEST(contraflexure!=nullptr, true);

   CComQIPtr<IAnalysisPOIs> an_pois(response);
   TRY_TEST(an_pois!=nullptr, true);

   CComQIPtr<IGetDistributionFactors> igdf(response);
   TRY_TEST(igdf!=nullptr, true);

   CComQIPtr<IGetStressPoints> igcs(response);
   TRY_TEST(igcs!=nullptr, true);

   TRY_TEST(pllc->Initialize(model, influence, llnmr, an_pois, igdf, igcs), S_OK);

   CComPtr<IBasicVehicularResponse> bvresponse;
   TRY_TEST(bvresponse.CoCreateInstance( CLSID_BasicVehicularResponse ), S_OK );

   CComQIPtr<IDependOnVehicularAnalysisContext> depcontxt(bvresponse);
   ATLASSERT(depcontxt!=nullptr);

   TRY_TEST(depcontxt->Initialize(pllc), S_OK);

   // get contraflexure locations and add pois at those locations
   CComPtr<IDblArray> cflocs;
   hr = contraflexure->ComputeContraflexureLocations(CComBSTR("Stage 1"), &cflocs);

   CComPtr<IPOIs> pois;
   hr = model->get_POIs(&pois);
/*
   long numcfs = cflocs.Size();
   long id=500;
   for (long icf = 0; icf<numcfs; icf++)
   {
      Float64 loc = cflocs[icf];

      CComPtr<IPOI> poi;
      poi.CoCreateInstance(CLSID_POI);

      poi->put_ID(id++);
      poi->put_MemberType(mtSuperstructureMember);
      poi->put_MemberID(0);
      poi->put_Location(loc+overhang);

      pois->Add(poi);
   }
*/

   // finally have model built and analysis engines set up - now let's prepare to request some results
   CComPtr<ILiveLoadConfiguration> placemt;
   TRY_TEST(placemt.CoCreateInstance( CLSID_LiveLoadConfiguration), S_OK );

   TRY_TEST(placemt->put_LiveLoadModel(lltDesign), S_OK);
   TRY_TEST(placemt->put_VehicleIndex(0), S_OK);
   TRY_TEST(placemt->put_ForceEffect(fetFy), S_OK);
   TRY_TEST(placemt->put_Optimization(optMaximize), S_OK);

   TRY_TEST(placemt->put_TruckDirection(ltdForward), S_OK);
   TRY_TEST(placemt->put_VehicularLoadConfiguration(vlcTruckOnly), S_OK);
   TRY_TEST(placemt->put_VariableSpacing(20.), S_OK);
   TRY_TEST(placemt->put_TruckPosition(110.), S_OK);
   TRY_TEST(placemt->put_DistributionFactorType(dftMultipleLane), S_OK);
  

   // ready to compute something
   CComPtr<IIDArray> apois;
   apois.CoCreateInstance(CLSID_IDArray);
   apois->Add( 3);  // midspan of both spans
   apois->Add(17);

   CComPtr<ISectionResult3Ds> results;
   TRY_TEST(bvresponse->ComputeForces(apois, CComBSTR("Stage 1"),roGlobal,placemt, &results), S_OK);

   TRY_TEST(placemt->put_Optimization(optMinimize), S_OK);
   CComPtr<ISectionResult3Ds> results2;
   TRY_TEST(bvresponse->ComputeForces(apois, CComBSTR("Stage 1"),roGlobal,placemt, &results2), S_OK);

   CComPtr<IDblArray> cflocs2;
   hr = contraflexure->ComputeContraflexureLocations(CComBSTR("Stage 1"), &cflocs2);
/*
   numcfs = cflocs2.Size();
   for (icf = 0; icf<numcfs; icf++)
   {
      Float64 loc = cflocs2[icf];
   }
*/

/*
   CComPtr<ISectionResult3D> result6, result17;
   results->get_Item(0, &result6);
   Float64 fx, fy, mz;
   result6->get_ZLeft(&mz);
   TRY_TEST(IsEqual(mz, 32.75, 0.1), true);
   result6->get_YLeft(&fy);
   TRY_TEST(IsEqual(fy, -2.72, 0.01), true);
   result6->get_XLeft(&fx);
   TRY_TEST(fx, 0.0);

   results->get_Item(1, &result17);
   result17->get_ZLeft(&mz);
//   TRY_TEST(mz, 0.0);
   result17->get_YLeft(&fy);
//   TRY_TEST(fy, 0.0);
   result17->get_XLeft(&fx);
   TRY_TEST(fx, 0.0);
*/
   // save model off to a file so we can load it in other applications for comparisons
   CComQIPtr<IStructuredStorage2> piss(model);
   ATLASSERT(piss!=nullptr);

   CComPtr<IStructuredSave2> pss;
   TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
   TRY_TEST( pss->Open( CComBSTR("TestVehicular.xml")), S_OK );

   piss->Save( pss );
   TRY_TEST( pss->Close(), S_OK );

   // release ourself
   pMe->Release();
}


static HRESULT CreateASimpleLBAM(ILBAMModel** model)
{
   HRESULT hr;
   CComPtr<IDblArray> span_lengths;
   span_lengths.CoCreateInstance(CLSID_DblArray);
   span_lengths->Add(70);
   span_lengths->Add(70);
   CComPtr<ILBAMFactory> factory;
   hr = factory.CoCreateInstance(CLSID_LRFDFactory);
   TRY_TEST(hr, S_OK);
   hr = factory->CreateSimpleModel(span_lengths, 29000, 200, 2000, 20, model);
   TRY_TEST(hr, S_OK);

   // give it some overhangs
   CComPtr<ISuperstructureMembers> ssms;
   TRY_TEST( (*model)->get_SuperstructureMembers(&ssms), S_OK);
   TRY_TEST(ssms->put_Offset(10.), S_OK);
   CComPtr<ISuperstructureMember> ssm1;
   TRY_TEST(ssms->get_Item(0, &ssm1), S_OK);
   TRY_TEST(ssm1->put_Length(160.0), S_OK);

   // add some pois
   PoiIDType last_val;
   TRY_TEST(factory->GeneratePOIsOnSuperstructure(*model, 0, 10, &last_val), S_OK);

   return S_OK;
}


void GenerateLoadGroups(ILBAMModel* model, Float64 overhang)
{
   // create some load groups that look like trucks
   CComPtr<ILoadGroups> loadgroups;
   model->get_LoadGroups(&loadgroups);

   CComPtr<IPointLoads> pointloads;
   model->get_PointLoads(&pointloads);

   CComBSTR stage_nm("Stage 1");

   {
      CComBSTR design_at_50_nm("Design Truck at 56 Forward");
      CComPtr<ILoadGroup> design_at_50_lg;
      design_at_50_lg.CoCreateInstance(CLSID_LoadGroup);
      design_at_50_lg->put_Name(design_at_50_nm);
      loadgroups->Add(design_at_50_lg);

      CComPtr<IPointLoad> pl1, pl2, pl3;
      pl1.CoCreateInstance(CLSID_PointLoad);
      pl1->put_MemberID(0);
      pl1->put_MemberType(mtSuperstructureMember);
      pl1->put_Fy(-8);

      Float64 front_loc = 56.0 + overhang;
      pl1->put_Location(front_loc);

      pl1->Clone(&pl2);
      pl2->put_Fy(-32);
      pl2->put_Location(front_loc-14);

      pl2->Clone(&pl3);
      pl3->put_Location(front_loc-28);

      CComPtr<IPointLoadItem> pli1, pli2, pli3;
      pointloads->Add(stage_nm, design_at_50_nm, pl1, &pli1);
      pointloads->Add(stage_nm, design_at_50_nm, pl2, &pli2);
      pointloads->Add(stage_nm, design_at_50_nm, pl3, &pli3);
   }

   {
      CComBSTR design_at_50_nm("Design Truck at 56 Reverse");
      CComPtr<ILoadGroup> design_at_50_lg;
      design_at_50_lg.CoCreateInstance(CLSID_LoadGroup);
      design_at_50_lg->put_Name(design_at_50_nm);
      loadgroups->Add(design_at_50_lg);

      CComPtr<IPointLoad> pl1, pl2, pl3;
      pl1.CoCreateInstance(CLSID_PointLoad);
      pl1->put_MemberID(0);
      pl1->put_MemberType(mtSuperstructureMember);
      pl1->put_Fy(-8);

      Float64 front_loc = 56.0 + overhang;
      pl1->put_Location(front_loc);

      pl1->Clone(&pl2);
      pl2->put_Fy(-32);
      pl2->put_Location(front_loc+14);

      pl2->Clone(&pl3);
      pl3->put_Location(front_loc+28);

      CComPtr<IPointLoadItem> pli1, pli2, pli3;
      pointloads->Add(stage_nm, design_at_50_nm, pl1, &pli1);
      pointloads->Add(stage_nm, design_at_50_nm, pl2, &pli2);
      pointloads->Add(stage_nm, design_at_50_nm, pl3, &pli3);
   }

   CComPtr<IDistributedLoads> distributedloads;
   model->get_DistributedLoads(&distributedloads);

   {
      CComBSTR name("Uniform Load of 1.0");
      CComPtr<ILoadGroup> unif_lg;
      unif_lg.CoCreateInstance(CLSID_LoadGroup);
      unif_lg->put_Name(name);
      loadgroups->Add(unif_lg);

      CComPtr<IDistributedLoad> u1;
      u1.CoCreateInstance(CLSID_DistributedLoad);
      u1->put_MemberID(0);
      u1->put_MemberType(mtSuperstructureMember);
      u1->put_Direction(ldFy);
      u1->put_WStart(-1.0);
      u1->put_WEnd(-1.0);
      u1->put_StartLocation(0.0);
      u1->put_EndLocation(-1.0);

      distributedloads->Add(stage_nm, name, u1, nullptr);
   }
}



