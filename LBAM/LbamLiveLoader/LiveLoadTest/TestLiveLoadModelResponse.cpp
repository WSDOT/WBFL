///////////////////////////////////////////////////////////////////////
// LBAM Live Load Test - Test driver for LBAM analysis library
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

// TestLiveLoadModelResponse.cpp: implementation of the TestLiveLoadModelResponse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestLiveLoadModelResponse.h"

#include <string>
#include <fstream>
#include <iomanip>

#include <MathEx.h>
#include "..\..\LBAMTestUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static HRESULT CreateASimpleLBAM(ILBAMModel** model);

inline HRESULT CreateDistributedLoad(IDistributedLoads* dls, BSTR stage, BSTR loadGroup, long mbrId, MemberType mType, Float64 ldVal)
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
   TRY_TEST( dls->Add(stage, loadGroup,dl,NULL), S_OK);
   return S_OK;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

inline void CompareLLResults(OptimizationType optmization, ForceEffectType forceType, 
                             VehicularLoadConfigurationType vlcType, VARIANT_BOOL doApplyImpact,
                             VARIANT_BOOL doApplyDistribution,
                             ILiveLoadModelResponse* llmResponse, IBasicVehicularResponse* basicResponse,
                             std::_tofstream& os)
{
   // This function compares the enveloped result computed by the enveloping engine and then stuffs
   // the optimal configuration into the basic engine. The result should be the same if both engines are
   // working correctly. 
   // Of course, both engines could be computing the wrong answer....
   os<<"---------------------------------------------------"<< std::endl;
   os<< (optmization==optMaximize ? "Maximized Positive ":"Maximized Negative ")<<
      (forceType==fetMz? "Moment " : "Shear ")<<std::endl;

   switch (vlcType)
   {
   case vlcDefault:
      os <<"Truck Type: vlcDefault"<<std::endl;
      break;
   case vlcTruckOnly:
      os <<"Truck Type: vlcTruckOnly"<<std::endl;
      break;
   case vlcLaneOnly:
      os <<"Truck Type: vlcLaneOnly"<<std::endl;
      break;
   case vlcTruckPlusLane:
      os <<"Truck Type: vlcTruckPlusLane"<<std::endl;
      break;
   case vlcTruckLaneEnvelope:
      os <<"Truck Type: vlcTruckLaneEnvelope"<<std::endl;
      break;
   case vlcSidewalkOnly:
      os <<"Truck Type: vlcSidewalkOnly"<<std::endl;
      break;
   default:
      _ASSERT(0);
   }

   os << (doApplyImpact==VARIANT_FALSE? "No Impact": "Impact Applied")<<std::endl;
   os << (doApplyDistribution==VARIANT_FALSE? "No Distribution": "Distribution Applied")<<std::endl<<std::endl;

   os << " POI     Left Value     Right Value"<<std::endl;
   os << "-----  -------------   -------------"<<std::endl;

   const PoiIDType NUMPOIS=10;
   CComPtr<ILongArray> poiIDs;
   poiIDs.CoCreateInstance(CLSID_LongArray);
   for (PoiIDType poiID = 0; poiID < NUMPOIS; poiID++)
   {
      poiIDs->Add(poiID);
   }

   // compute enveloped results for all pois
   CComPtr<ILiveLoadModelSectionResults> results;
   TRY_TEST(llmResponse->ComputeForces(poiIDs, CComBSTR("Stage 1"),lltDesign, roGlobal, forceType, optmization,
                                       vlcType, doApplyImpact, doApplyDistribution, VARIANT_TRUE, &results), S_OK);

   // have to compute basic result for a single poi for each configuration optimized at that poi
   CComPtr<ILongArray> singlePOI;
   singlePOI.CoCreateInstance(CLSID_LongArray);
   singlePOI->ReDim(1);

   for (PoiIDType poiID = 0; poiID < NUMPOIS; poiID++)
   {
      singlePOI->put_Item(0,poiID);

      // get enveloped value - with optimal configuration
      Float64 left_val, right_val;
      CComPtr<ILiveLoadConfiguration> left_config, right_config;
      TRY_TEST(results->GetResult(poiID, &left_val, &left_config, &right_val, &right_config), S_OK);

      // compute result using config and basic engine
      // left config first,
      CComPtr<ISectionResult3Ds> res3Ds;
      CComPtr<ISectionResult3D> res3D;
      Float64 vleft, vright;
      TRY_TEST(basicResponse->ComputeForces(singlePOI, CComBSTR("Stage 1"), roGlobal, left_config, &res3Ds), S_OK);

      // basic value
      TRY_TEST(res3Ds->get_Item(0, &res3D), S_OK);
      TRY_TEST(res3D->GetSingleResult(forceType, &vleft, &vright), S_OK);

      // compare response
//      TRY_TEST(IsEqual(vleft,  left_val), true);

      os <<"L"<<std::setw(5) << poiID
         <<std::setw(16)<< left_val
         <<std::setw(16)<< right_val<<std::endl;

      // then right config if there was one
      if (right_config!=NULL)
      {
         res3Ds.Release();
         TRY_TEST(basicResponse->ComputeForces(singlePOI, CComBSTR("Stage 1"), roGlobal, right_config, &res3Ds), S_OK);

         // basic value
         res3D.Release();
         TRY_TEST(res3Ds->get_Item(0, &res3D), S_OK);
         TRY_TEST(res3D->GetSingleResult(forceType, &vleft, &vright), S_OK);

         // compare response
//         TRY_TEST(IsEqual(vright, right_val), true);

         os <<"R"<<std::setw(5) << poiID
            <<std::setw(16)<< left_val
            <<std::setw(16)<< right_val<<std::endl;
      }
   }
}


TestLiveLoadModelResponse::TestLiveLoadModelResponse()
{
}

TestLiveLoadModelResponse::~TestLiveLoadModelResponse()
{
}

void TestLiveLoadModelResponse::Test()
{
   // create a simple lbam model to analyze
   CComPtr<ILBAMModel> model;
   TRY_TEST(CreateASimpleLBAM(&model), S_OK);

   // set up response engine 
   CComPtr<ILBAMAnalysisEngine> pengine;
   TRY_TEST(pengine.CoCreateInstance( CLSID_LBAMAnalysisEngine ), S_OK );

   TRY_TEST(pengine->Initialize(model, atForce), S_OK);

   CComPtr<ILiveLoadModelResponse> llm_response;
   TRY_TEST(pengine->get_LiveLoadModelResponse(&llm_response), S_OK);

   CComPtr<IBasicVehicularResponse> basic_response;
   TRY_TEST(pengine->get_BasicVehicularResponse(&basic_response), S_OK);

   // dump results to a file
   std::_tofstream os("LiveLoadModelResponse.txt");

   // ready to compute something
   // Mz
   CompareLLResults(optMaximize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
// -----
   CompareLLResults(optMaximize, fetMz, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetMz, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
//-------
   CompareLLResults(optMaximize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

   // Fy
   CompareLLResults(optMaximize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
// -----
   CompareLLResults(optMaximize, fetFy, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetFy, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
//-------
   CompareLLResults(optMaximize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

   CompareLLResults(optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
   CompareLLResults(optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
}


HRESULT CreateASimpleLBAM(ILBAMModel** model)
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

   // configure LRFD live loads and combinations
   ConfigureLrfdLiveLoadModelInKipFeet(*model);
   ConfigureLrfdLoadCombinations(*model);

   // create a barrier load group and add it to the dc load case
   // create some load groups with loads (or not)
   CComPtr<ILoadGroups> lgs;
   TRY_TEST( (*model)->get_LoadGroups(&lgs), S_OK);

   CComPtr<IDistributedLoads> dls;
   TRY_TEST( (*model)->get_DistributedLoads(&dls), S_OK);

   CComBSTR lgn_br("Barrier");
   CComPtr<ILoadGroup> lgbr;
   TRY_TEST( lgbr.CoCreateInstance(CLSID_LoadGroup), S_OK);
   TRY_TEST( lgbr->put_Name(lgn_br), S_OK);
   TRY_TEST( lgs->Add(lgbr), S_OK);
   CreateDistributedLoad(dls, CComBSTR("Stage 1"), lgn_br, 0, mtSuperstructureMember, -2.5);

   CComPtr<ILoadCases> lcs;
   TRY_TEST( (*model)->get_LoadCases(&lcs), S_OK);

   CComPtr<ILoadCase> lcdc;
   TRY_TEST( lcs->Find(CComBSTR("DC"),&lcdc), S_OK);
   lcdc->AddLoadGroup(lgn_br);

   // add some pois
   long last_val;
   TRY_TEST(factory->GeneratePOIsOnSuperstructure(*model, 0, 4, &last_val), S_OK);


   // Save off to file for later inspection
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("TestLiveLoadModelResponse.xml")), S_OK );

      // get interface pointer 
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( (*model)->QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );
      TRY_TEST( pss->Close(), S_OK );
   }

   return S_OK;
}
