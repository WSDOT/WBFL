///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner Test - Test driver for LBAM analysis library
// Copyright © 1999-2015  Washington State Department of Transportation
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

// Solleks.cpp: implementation of the Solleks class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Solleks.h"

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
   TRY_TEST( dls->Add(stage, loadGroup,dl,NULL), S_OK);
   return S_OK;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

inline void CompareCmbForceResults(BSTR loadCombination, BSTR Stage, OptimizationType optmization, 
                             ForceEffectType forceType, ResultsSummationType summ, VARIANT_BOOL includeLiveLoad,
                             ILoadCombinationResponse* lcResponse, IConcurrentLoadCombinationResponse* concResponse,
                             std::_tofstream& os)
{
   // This function compares the enveloped result computed by the enveloping engine and then stuffs
   // the optimal configuration into the basic engine. The result should be the same if both engines are
   // working correctly. 
   // Of course, both engines could be computing the wrong answer....
   os<<"---------------------------------------------------"<< std::endl;
   os<<"Results for "<<(TCHAR*)_bstr_t(loadCombination)<< " for stage "<<(TCHAR*)_bstr_t(Stage)<<std::endl;
   os<< (optmization==optMaximize ? "Maximized Positive ":"Maximized Negative ")<<
      (forceType==fetMz? "Moment " : "Shear ")<<std::endl;

   os << " POI     Left Value     Right Value"<<std::endl;
   os << "-----  -------------   -------------"<<std::endl;

   const CollectionIndexType NUMPOIS=10;
   CComPtr<IIDArray> apois;
   apois.CoCreateInstance(CLSID_IDArray);
   for (CollectionIndexType i=0; i<NUMPOIS; i++)
   {
      apois->Add((PoiIDType)i);
   }

   // compute enveloped results for all pois
   CComPtr<ILoadCombinationSectionResults> results;
   TRY_TEST(lcResponse->ComputeForces(loadCombination, apois, Stage, roGlobal, summ, forceType, optmization,
                                       includeLiveLoad, VARIANT_TRUE, VARIANT_TRUE, &results), S_OK);

   // have to compute basic result for a single poi for each configuration optimized at that poi
   CComPtr<IIDArray> apoi;
   apoi.CoCreateInstance(CLSID_IDArray);
   apoi->ReDim(1);

   for (CollectionIndexType j=0; j<NUMPOIS; j++)
   {
      apoi->put_Item(0,(PoiIDType)j);

      // get enveloped value - with optimal configuration
      Float64 left_val, right_val;
      CComPtr<ILoadCombinationResultConfiguration> left_config, right_config;
      TRY_TEST(results->GetResult(j, &left_val, &left_config, &right_val, &right_config), S_OK);

      // compute result using config and basic engine
      // left config first,
      CComPtr<ISectionResult3Ds> res3Ds;
      CComPtr<ISectionResult3D> res3D;
      Float64 vleft, vright;
      TRY_TEST(concResponse->ComputeForces(apoi, Stage, roGlobal, left_config, &res3Ds), S_OK);

      // basic value
      TRY_TEST(res3Ds->get_Item(0, &res3D), S_OK);
      TRY_TEST(res3D->GetSingleResult(forceType, &vleft, &vright), S_OK);

      // compare response
//      TRY_TEST(IsEqual(vleft,  left_val), true);

      os <<"L"<<std::setw(3) << j
         <<std::setw(16)<< left_val
         <<std::setw(16)<< right_val<<std::endl;

      // then right config if there was one
      if (right_config!=NULL)
      {
         res3Ds.Release();
         TRY_TEST(concResponse->ComputeForces(apoi, Stage, roGlobal, right_config, &res3Ds), S_OK);

         // basic value
         res3D.Release();
         TRY_TEST(res3Ds->get_Item(0, &res3D), S_OK);
         TRY_TEST(res3D->GetSingleResult(forceType, &vleft, &vright), S_OK);

         // compare response
//         TRY_TEST(IsEqual(vright, right_val), true);

         os <<"R"<<std::setw(3) << j
            <<std::setw(16)<< left_val
            <<std::setw(16)<< right_val<<std::endl;
      }
   }
}

inline void CompareCmbDeflectionResults(BSTR loadCombination, BSTR Stage, OptimizationType optmization, 
                             ForceEffectType forceType, ResultsSummationType summ, VARIANT_BOOL includeLiveLoad,
                             ILoadCombinationResponse* lcResponse, IConcurrentLoadCombinationResponse* concResponse,
                             std::_tofstream& os)
{
   // This function compares the enveloped result computed by the enveloping engine and then stuffs
   // the optimal configuration into the basic engine. The result should be the same if both engines are
   // working correctly. 
   // Of course, both engines could be computing the wrong answer....
   os<<"---------------------------------------------------"<< std::endl;
   os<<"Deflection Results for "<<(TCHAR*)_bstr_t(loadCombination)<< " for stage "<<(TCHAR*)_bstr_t(Stage)<<std::endl;
   os<< (optmization==optMaximize ? "Maximized Positive ":"Maximized Negative ");
   if (forceType==fetFx)
      os<<"Horizontal Deflection"<<std::endl;
   else if (forceType==fetFy)
      os<<"Vertical Deflection"<<std::endl;
   else if (forceType==fetMz)
      os<<"Rotation"<<std::endl;

   os << " POI     Left Value     Right Value"<<std::endl;
   os << "-----  -------------   -------------"<<std::endl;

   const CollectionIndexType NUMPOIS=10;
   CComPtr<IIDArray> apois;
   apois.CoCreateInstance(CLSID_IDArray);
   for (CollectionIndexType i=0; i<NUMPOIS; i++)
   {
      apois->Add((PoiIDType)i);
   }

   // compute enveloped results for all pois
   CComPtr<ILoadCombinationSectionResults> results;
   TRY_TEST(lcResponse->ComputeDeflections(loadCombination, apois, Stage, summ, forceType, optmization,
                                       includeLiveLoad, VARIANT_TRUE, VARIANT_TRUE, &results), S_OK);

   // have to compute basic result for a single poi for each configuration optimized at that poi
   CComPtr<IIDArray> apoi;
   apoi.CoCreateInstance(CLSID_IDArray);
   apoi->ReDim(1);

   for (CollectionIndexType j=0; j<NUMPOIS; j++)
   {
      apoi->put_Item(0,(PoiIDType)j);

      // get enveloped value - with optimal configuration
      Float64 left_val, right_val;
      CComPtr<ILoadCombinationResultConfiguration> left_config, right_config;
      TRY_TEST(results->GetResult(j, &left_val, &left_config, &right_val, &right_config), S_OK);

      // compute result using config and basic engine
      // left config first,
      CComPtr<ISectionResult3Ds> res3Ds;
      CComPtr<ISectionResult3D> res3D;
      Float64 vleft, vright;
      TRY_TEST(concResponse->ComputeDeflections(apoi, Stage, left_config, &res3Ds), S_OK);

      // basic value
      TRY_TEST(res3Ds->get_Item(0, &res3D), S_OK);
      TRY_TEST(res3D->GetSingleResult(forceType, &vleft, &vright), S_OK);

      // compare response
      TRY_TEST(IsEqual(vleft,  left_val), true);

      os <<"L"<<std::setw(3) << j
         <<std::setw(16)<< left_val
         <<std::setw(16)<< right_val<<std::endl;

      // then right config if there was one
      if (right_config!=NULL)
      {
         res3Ds.Release();
         TRY_TEST(concResponse->ComputeDeflections(apoi, Stage, right_config, &res3Ds), S_OK);

         // basic value
         res3D.Release();
         TRY_TEST(res3Ds->get_Item(0, &res3D), S_OK);
         TRY_TEST(res3D->GetSingleResult(forceType, &vleft, &vright), S_OK);

         // compare response
         TRY_TEST(IsEqual(vright, right_val), true);

         os <<"R"<<std::setw(3) << j
            <<std::setw(16)<< left_val
            <<std::setw(16)<< right_val<<std::endl;
      }
   }
}


inline void CompareCmbReactionResults(ILBAMModel* Model, BSTR loadCombination, BSTR Stage, 
                                   OptimizationType optmization, ForceEffectType forceType, 
                                   ResultsSummationType summ, VARIANT_BOOL includeLiveLoad,
                                   ILoadCombinationResponse* lcResponse, IConcurrentLoadCombinationResponse* concResponse,
                                   std::_tofstream& os)
{
   HRESULT hr;
   // This function compares the enveloped result computed by the enveloping engine and then stuffs
   // the optimal configuration into the basic engine. The result should be the same if both engines are
   // working correctly. 
   // Of course, both engines could be computing the wrong answer....
   os<<"---------------------------------------------------"<< std::endl;
   os<<"Reactions for "<<(TCHAR*)_bstr_t(loadCombination)<< " for stage "<<(TCHAR*)_bstr_t(Stage)<<std::endl;
   os<< (optmization==optMaximize ? "Maximized Positive ":"Maximized Negative ");

   if (forceType==fetFx)
      os<<"Horizontal Reaction "<<std::endl;
   else if (forceType==fetFy)
      os<<"Vertical Reaction "<<std::endl;
   if (forceType==fetMz)
      os<<"Moment Reaction "<<std::endl;

   os << " Spt      Value    "<<std::endl;
   os << "-----  -------------   "<<std::endl;

   // get list of supports for this stage
   CComPtr<IIDArray> support_ids;
   CComPtr<ILBAMFactory> gen_util;
   hr = gen_util.CoCreateInstance(CLSID_LRFDFactory);
   ATLASSERT(SUCCEEDED(hr));
   hr = gen_util->GetSupportIDsForStage(Model, Stage, &support_ids);
   ATLASSERT(SUCCEEDED(hr));

   CollectionIndexType num_supports;
   support_ids->get_Count(&num_supports);

   // compute enveloped results for all pois
   CComPtr<ILoadCombinationResults> results;
   TRY_TEST(lcResponse->ComputeReactions(loadCombination, support_ids, Stage, summ, forceType, optmization,
                                         VARIANT_TRUE, VARIANT_TRUE, VARIANT_TRUE, &results), S_OK);

   // have to compute basic result for a single poi for each configuration optimized at that poi
   CComPtr<IIDArray> asup;
   asup.CoCreateInstance(CLSID_IDArray);
   asup->ReDim(1);

   for (CollectionIndexType j=0; j<num_supports; j++)
   {
      asup->put_Item(0,(SupportIDType)j);

      // get enveloped value - with optimal configuration
      Float64 llmval;
      CComPtr<ILoadCombinationResultConfiguration> config;
      TRY_TEST(results->GetResult(j, &llmval, &config), S_OK);

      // compute result using config and basic engine
      // left config first,
      CComPtr<IResult3Ds> res3Ds;
      CComPtr<IResult3D> res3D;
      TRY_TEST(concResponse->ComputeReactions(asup, Stage, config, &res3Ds), S_OK);

      // basic value
      Float64 bval;
      TRY_TEST(res3Ds->get_Item(0, &res3D), S_OK);
      TRY_TEST(res3D->GetSingleResult(forceType, &bval), S_OK);

      // compare response
      TRY_TEST(IsEqual(llmval,  bval), true);

      os <<"L"<<std::setw(3) << j <<std::setw(16)<< llmval<<std::endl;
   }
}

inline void CompareCmbSupportDeflectionResults(ILBAMModel* Model, BSTR loadCombination, BSTR Stage, 
                                   OptimizationType optmization, ForceEffectType forceType, 
                                   ResultsSummationType summ, VARIANT_BOOL includeLiveLoad,
                                   ILoadCombinationResponse* lcResponse, IConcurrentLoadCombinationResponse* concResponse,
                                   std::_tofstream& os)
{
   HRESULT hr;
   // This function compares the enveloped result computed by the enveloping engine and then stuffs
   // the optimal configuration into the basic engine. The result should be the same if both engines are
   // working correctly. 
   // Of course, both engines could be computing the wrong answer....
   os<<"---------------------------------------------------"<< std::endl;
   os<<"Support Deflections for "<<(TCHAR*)_bstr_t(loadCombination)<< " for stage "<<(TCHAR*)_bstr_t(Stage)<<std::endl;
   os<< (optmization==optMaximize ? "Maximized Positive ":"Maximized Negative ");

   if (forceType==fetFx)
      os<<"Horizontal Support Deflection "<<std::endl;
   else if (forceType==fetFy)
      os<<"Vertical Support Deflection "<<std::endl;
   if (forceType==fetMz)
      os<<"Moment Support Deflection "<<std::endl;

   os << " Spt      Value    "<<std::endl;
   os << "-----  -------------   "<<std::endl;

   // get list of supports for this stage
   CComPtr<IIDArray> support_ids;
   CComPtr<ILBAMFactory> gen_util;
   hr = gen_util.CoCreateInstance(CLSID_LRFDFactory);
   ATLASSERT(SUCCEEDED(hr));
   hr = gen_util->GetSupportIDsForStage(Model, Stage, &support_ids);
   ATLASSERT(SUCCEEDED(hr));

   CollectionIndexType num_supports;
   support_ids->get_Count(&num_supports);

   // compute enveloped results for all pois
   CComPtr<ILoadCombinationResults> results;
   TRY_TEST(lcResponse->ComputeSupportDeflections(loadCombination, support_ids, Stage, summ, forceType, optmization,
                                         VARIANT_TRUE, VARIANT_TRUE, VARIANT_TRUE, &results), S_OK);

   // have to compute basic result for a single poi for each configuration optimized at that poi
   CComPtr<IIDArray> asup;
   asup.CoCreateInstance(CLSID_IDArray);
   asup->ReDim(1);

   for (CollectionIndexType j=0; j<num_supports; j++)
   {
      asup->put_Item(0,(SupportIDType)j);

      // get enveloped value - with optimal configuration
      Float64 llmval;
      CComPtr<ILoadCombinationResultConfiguration> config;
      TRY_TEST(results->GetResult(j, &llmval, &config), S_OK);

      // compute result using config and basic engine
      // left config first,
      CComPtr<IResult3Ds> res3Ds;
      CComPtr<IResult3D> res3D;
      TRY_TEST(concResponse->ComputeSupportDeflections(asup, Stage, config, &res3Ds), S_OK);

      // basic value
      Float64 bval;
      TRY_TEST(res3Ds->get_Item(0, &res3D), S_OK);
      TRY_TEST(res3D->GetSingleResult(forceType, &bval), S_OK);

      // compare response
      TRY_TEST(IsEqual(llmval,  bval), true);

      os <<"L"<<std::setw(3) << j <<std::setw(16)<< llmval<<std::endl;
   }
}

Solleks::Solleks()
{
}

Solleks::~Solleks()
{
}

void Solleks::Test()
{
   // create a simple lbam model to analyze
   CComPtr<ILBAMModel> model;
   TRY_TEST(CreateASimpleLBAM(&model), S_OK);

   // set up response engine 
   CComPtr<ILBAMAnalysisEngine> pengine;
   TRY_TEST(pengine.CoCreateInstance( CLSID_LBAMAnalysisEngine ), S_OK );

   TRY_TEST(pengine->Initialize(model, atForce), S_OK);

   CComPtr<ILoadCombinationResponse> lc_response;
   TRY_TEST(pengine->get_LoadCombinationResponse(&lc_response), S_OK);

   CComPtr<IConcurrentLoadCombinationResponse> clc_response;
   TRY_TEST(pengine->get_ConcurrentLoadCombinationResponse(&clc_response), S_OK);

   // dump results to a file
   std::_tofstream os("Solleks.txt");

   for (long is=0; is<1; is++)
   {
      CComBSTR stage;
      if (is==0)
         stage = "Stage 1";
      else
         stage = "Stage 2";

      for (long ic=0; ic<1; ic++)
      {
         CComBSTR cmb;
         if (ic==0)
            cmb = "SERVICE-I";
         else
            cmb = "STRENGTH-I";

         // ready to compute something
         // Mz
         CompareCmbForceResults(cmb, stage, optMaximize, fetMz, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbForceResults(cmb, stage, optMinimize, fetMz, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbForceResults(cmb, stage, optMaximize, fetMz, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbForceResults(cmb, stage, optMinimize, fetMz, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbForceResults(cmb, stage, optMaximize, fetMz, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbForceResults(cmb, stage, optMinimize, fetMz, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);

         CompareCmbForceResults(cmb, stage, optMaximize, fetMz, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbForceResults(cmb, stage, optMinimize, fetMz, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);

         // Fy
         CompareCmbForceResults(cmb, stage, optMaximize, fetFy, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbForceResults(cmb, stage, optMinimize, fetFy, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbForceResults(cmb, stage, optMaximize, fetFy, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbForceResults(cmb, stage, optMinimize, fetFy, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbForceResults(cmb, stage, optMaximize, fetFy, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbForceResults(cmb, stage, optMinimize, fetFy, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);

         CompareCmbForceResults(cmb, stage, optMaximize, fetFy, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbForceResults(cmb, stage, optMinimize, fetFy, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);

         //---------------------
         // Deflections
         // Rz
         CompareCmbDeflectionResults(cmb, stage, optMaximize, fetMz, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbDeflectionResults(cmb, stage, optMinimize, fetMz, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbDeflectionResults(cmb, stage, optMaximize, fetMz, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbDeflectionResults(cmb, stage, optMinimize, fetMz, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbDeflectionResults(cmb, stage, optMaximize, fetMz, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbDeflectionResults(cmb, stage, optMinimize, fetMz, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);

         CompareCmbDeflectionResults(cmb, stage, optMaximize, fetMz, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbDeflectionResults(cmb, stage, optMinimize, fetMz, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);

         // Dy
         CompareCmbDeflectionResults(cmb, stage, optMaximize, fetFy, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbDeflectionResults(cmb, stage, optMinimize, fetFy, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbDeflectionResults(cmb, stage, optMaximize, fetFy, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbDeflectionResults(cmb, stage, optMinimize, fetFy, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbDeflectionResults(cmb, stage, optMaximize, fetFy, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbDeflectionResults(cmb, stage, optMinimize, fetFy, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);

         CompareCmbDeflectionResults(cmb, stage, optMaximize, fetFy, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbDeflectionResults(cmb, stage, optMinimize, fetFy, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);

         // Dx
         CompareCmbDeflectionResults(cmb, stage, optMaximize, fetFx, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbDeflectionResults(cmb, stage, optMinimize, fetFx, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbDeflectionResults(cmb, stage, optMaximize, fetFx, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbDeflectionResults(cmb, stage, optMinimize, fetFx, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbDeflectionResults(cmb, stage, optMaximize, fetFx, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbDeflectionResults(cmb, stage, optMinimize, fetFx, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);

         CompareCmbDeflectionResults(cmb, stage, optMaximize, fetFx, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbDeflectionResults(cmb, stage, optMinimize, fetFx, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);

         //---------------------
         // Reactions
         // Rz
         CompareCmbReactionResults(model, cmb, stage, optMaximize, fetMz, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbReactionResults(model, cmb, stage, optMinimize, fetMz, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbReactionResults(model, cmb, stage, optMaximize, fetMz, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbReactionResults(model, cmb, stage, optMinimize, fetMz, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbReactionResults(model, cmb, stage, optMaximize, fetMz, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbReactionResults(model, cmb, stage, optMinimize, fetMz, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);

         CompareCmbReactionResults(model, cmb, stage, optMaximize, fetMz, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbReactionResults(model, cmb, stage, optMinimize, fetMz, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);

         // Dy
         CompareCmbReactionResults(model, cmb, stage, optMaximize, fetFy, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbReactionResults(model, cmb, stage, optMinimize, fetFy, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbReactionResults(model, cmb, stage, optMaximize, fetFy, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbReactionResults(model, cmb, stage, optMinimize, fetFy, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbReactionResults(model, cmb, stage, optMaximize, fetFy, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbReactionResults(model, cmb, stage, optMinimize, fetFy, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);

         CompareCmbReactionResults(model, cmb, stage, optMaximize, fetFy, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbReactionResults(model, cmb, stage, optMinimize, fetFy, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);

         // Dx
         CompareCmbReactionResults(model, cmb, stage, optMaximize, fetFx, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbReactionResults(model, cmb, stage, optMinimize, fetFx, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbReactionResults(model, cmb, stage, optMaximize, fetFx, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbReactionResults(model, cmb, stage, optMinimize, fetFx, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbReactionResults(model, cmb, stage, optMaximize, fetFx, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbReactionResults(model, cmb, stage, optMinimize, fetFx, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);

         CompareCmbReactionResults(model, cmb, stage, optMaximize, fetFx, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbReactionResults(model, cmb, stage, optMinimize, fetFx, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);

         //---------------------
         // SupportDeflections
         // Rz
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMaximize, fetMz, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMinimize, fetMz, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbSupportDeflectionResults(model, cmb, stage, optMaximize, fetMz, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMinimize, fetMz, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbSupportDeflectionResults(model, cmb, stage, optMaximize, fetMz, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMinimize, fetMz, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);


         CompareCmbSupportDeflectionResults(model, cmb, stage, optMaximize, fetMz, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMinimize, fetMz, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);

         // Dy
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMaximize, fetFy, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMinimize, fetFy, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbSupportDeflectionResults(model, cmb, stage, optMaximize, fetFy, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMinimize, fetFy, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbSupportDeflectionResults(model, cmb, stage, optMaximize, fetFy, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMinimize, fetFy, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);

         CompareCmbSupportDeflectionResults(model, cmb, stage, optMaximize, fetFy, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMinimize, fetFy, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);

         // Dx
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMaximize, fetFx, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMinimize, fetFx, rsIncremental,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbSupportDeflectionResults(model, cmb, stage, optMaximize, fetFx, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMinimize, fetFx, rsCumulative,  VARIANT_FALSE, lc_response, clc_response, os);

         CompareCmbSupportDeflectionResults(model, cmb, stage, optMaximize, fetFx, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMinimize, fetFx, rsIncremental,  VARIANT_TRUE,  lc_response, clc_response, os);

         CompareCmbSupportDeflectionResults(model, cmb, stage, optMaximize, fetFx, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);
         CompareCmbSupportDeflectionResults(model, cmb, stage, optMinimize, fetFx, rsCumulative,  VARIANT_TRUE,  lc_response, clc_response, os);

      }
   }
}

#define RETURN_ON_FAIL(_hr_) if (FAILED(_hr_)) return _hr_

HRESULT CreateASegment(ISegment** Segment, Float64 E, Float64 A, Float64 I, Float64 Depth, Float64 Length)
{
   // set up cross section
   HRESULT hr;
   CComPtr<ISegmentCrossSection> pcs;
   hr = pcs.CoCreateInstance( CLSID_SegmentCrossSection );
   RETURN_ON_FAIL(hr);

   Float64 ea = E*A;
   Float64 ei = E*I;
   hr = pcs->put_EAForce(ea);
   RETURN_ON_FAIL(hr);
   hr = pcs->put_EIForce(ei);
   RETURN_ON_FAIL(hr);
   hr = pcs->put_EADefl(ea);
   RETURN_ON_FAIL(hr);
   hr = pcs->put_EIDefl(ei);
   RETURN_ON_FAIL(hr);
   hr = pcs->put_ThermalCoeff(0.0);
   RETURN_ON_FAIL(hr);
   hr = pcs->put_Depth(Depth);
   RETURN_ON_FAIL(hr);

   // put one stress point on the top and bottom and middle of the section
   Float64 sa = 1.0/A;
   Float64 sm = (Depth/2.0)/I;

   CComPtr<IStressPoints> psps;
   hr = pcs->get_StressPoints(&psps);

   CComPtr<IStressPoint> psst, pssb, pssm;
   hr = psst.CoCreateInstance( CLSID_StressPoint ) ;
   RETURN_ON_FAIL(hr);
   hr = pssb.CoCreateInstance( CLSID_StressPoint ) ;
   RETURN_ON_FAIL(hr);
   hr = pssm.CoCreateInstance( CLSID_StressPoint ) ;
   RETURN_ON_FAIL(hr);

   hr = psst->put_Sm(-sm);
   RETURN_ON_FAIL(hr);
   hr = psst->put_Sa(sa);
   RETURN_ON_FAIL(hr);
   hr = psps->Add(psst);
   RETURN_ON_FAIL(hr);

   hr = pssb->put_Sm(sm);
   RETURN_ON_FAIL(hr);
   hr = pssb->put_Sa(sa);
   RETURN_ON_FAIL(hr);
   hr = psps->Add(pssb);
   RETURN_ON_FAIL(hr);

   hr = pssm->put_Sm(0.0);
   RETURN_ON_FAIL(hr);
   hr = pssm->put_Sa(sa);
   RETURN_ON_FAIL(hr);
   hr = psps->Add(pssm);
   RETURN_ON_FAIL(hr);

   // segment
   CComPtr<ISegment> pseg;
   hr = pseg.CoCreateInstance( CLSID_Segment );
   RETURN_ON_FAIL(hr);

   hr = pseg->put_Length(Length);
   RETURN_ON_FAIL(hr);

   hr = pseg->putref_SegmentCrossSection(pcs);
   RETURN_ON_FAIL(hr);

   return pseg.CopyTo(Segment);
}


HRESULT CreateASimpleLBAM(ILBAMModel** model)
{
   HRESULT hr;
   // create a simple two span model
   CComPtr<ILBAMFactory> factory;
   TRY_TEST(factory.CoCreateInstance(CLSID_LRFDFactory), S_OK);
   CComPtr<IDblArray> span_lengths;
   span_lengths.CoCreateInstance(CLSID_DblArray);
   span_lengths->Add( 70.0);
   span_lengths->Add( 90.0);
   span_lengths->Add( 70.0);
   hr = factory->CreateSimpleModel(span_lengths, 1, 1, 1, 1, model);
   TRY_TEST(hr, S_OK);

   // make the model have two stages
   CComPtr<IStages> stages;
   TRY_TEST( (*model)->get_Stages(&stages), S_OK);
   CComPtr<IStage> stage2;
   TRY_TEST(stage2.CoCreateInstance(CLSID_Stage), S_OK);
   TRY_TEST(stage2->put_Name(CComBSTR("Stage 2")), S_OK);
   TRY_TEST(stages->Add(stage2), S_OK);

   // modify supports so they slant
   CComPtr<ISegment> segment;
   TRY_TEST(CreateASegment(&segment, 1.0, 1.0, 1.0, 1.0, 64.5),S_OK);

   CComPtr<ISupports> supports;
   TRY_TEST( (*model)->get_Supports(&supports), S_OK);

   CComPtr<ISupport> s0, s1, s2, s3;
   TRY_TEST( supports->get_Item(0, &s0), S_OK);
   TRY_TEST( s0->put_BoundaryCondition(bcRoller), S_OK);

   TRY_TEST( supports->get_Item(1, &s1), S_OK);
   TRY_TEST( s1->put_Length(64.5), S_OK);
   TRY_TEST( s1->put_BottomOffset(-39.26), S_OK);
   TRY_TEST( s1->put_BoundaryCondition(bcFixed), S_OK);
   TRY_TEST( s1->put_TopRelease(VARIANT_TRUE), S_OK);
   TRY_TEST( s1->AddSegment(CComBSTR("Stage 1"), segment), S_OK);
   TRY_TEST( s1->AddSegment(CComBSTR("Stage 2"), segment), S_OK);

   TRY_TEST( supports->get_Item(2, &s2), S_OK);
   TRY_TEST( s2->put_Length(64.5), S_OK);
   TRY_TEST( s2->put_BottomOffset( 39.26), S_OK);
   TRY_TEST( s2->put_BoundaryCondition(bcFixed), S_OK);
   TRY_TEST( s2->put_TopRelease(VARIANT_TRUE), S_OK);
   TRY_TEST( s2->AddSegment(CComBSTR("Stage 1"), segment), S_OK);
   TRY_TEST( s2->AddSegment(CComBSTR("Stage 2"), segment), S_OK);

   TRY_TEST( supports->get_Item(3, &s3), S_OK);
   TRY_TEST( s3->put_BoundaryCondition(bcRoller), S_OK);

   // add superstructure members so we can have hinges
   CComPtr<ISuperstructureMembers> ssms;
   TRY_TEST( (*model)->get_SuperstructureMembers(&ssms), S_OK);
   CComPtr<ISuperstructureMember> ssm1, ssm2, ssm3;
   TRY_TEST( ssms->get_Item(0,&ssm1), S_OK);
   TRY_TEST( ssm1->put_Length(77.5), S_OK);
   CComPtr<ISegment> ssegment;
   TRY_TEST( ssm1->get_Segment(CComBSTR("Stage 1"),0,&ssegment), S_OK);
   TRY_TEST( ssm1->AddSegment(CComBSTR("Stage 2"), ssegment), S_OK);

   TRY_TEST( ssm1->Clone(&ssm2), S_OK);
   TRY_TEST( ssm2->put_Length(75.0), S_OK);
   TRY_TEST( ssms->Add(ssm2), S_OK);
   TRY_TEST( ssm1->Clone(&ssm3), S_OK);
   TRY_TEST( ssms->Add(ssm3), S_OK);
   // hinges become continuous in stage 2
   TRY_TEST( ssm1->SetEndReleaseRemovalStage(ssRight,CComBSTR("Stage 2")),S_OK);
   TRY_TEST( ssm1->SetEndRelease(ssRight, mrtMz), S_OK);

   TRY_TEST( ssm3->SetEndReleaseRemovalStage(ssLeft,CComBSTR("Stage 2")),S_OK);
   TRY_TEST( ssm3->SetEndRelease(ssLeft,  mrtMz), S_OK);

   // configure LRFD live loads and combinations
   ConfigureLrfdLiveLoadModelInKipFeet(*model);
   ConfigureLrfdLoadCombinations(*model);

   // create a barrier load group and add it to the dc load case
   // create some load groups with loads (or not)
   CComPtr<ILoadGroups> lgs;
   TRY_TEST( (*model)->get_LoadGroups(&lgs), S_OK);

   CComPtr<IDistributedLoads> dls;
   TRY_TEST( (*model)->get_DistributedLoads(&dls), S_OK);

   CComBSTR lgn_sw("Self Weight");
   CComPtr<ILoadGroup> lgsw;
   TRY_TEST( lgsw.CoCreateInstance(CLSID_LoadGroup), S_OK);
   TRY_TEST( lgsw->put_Name(lgn_sw), S_OK);
   TRY_TEST( lgs->Add(lgsw), S_OK);
   CreateDistributedLoad(dls, CComBSTR("Stage 1"), lgn_sw, 0, mtSuperstructureMember, -1.0);
   CreateDistributedLoad(dls, CComBSTR("Stage 1"), lgn_sw, 1, mtSuperstructureMember, -1.0);
   CreateDistributedLoad(dls, CComBSTR("Stage 1"), lgn_sw, 2, mtSuperstructureMember, -1.0);
   CreateDistributedLoad(dls, CComBSTR("Stage 2"), lgn_sw, 0, mtSuperstructureMember, -0.3);
   CreateDistributedLoad(dls, CComBSTR("Stage 2"), lgn_sw, 1, mtSuperstructureMember, -0.3);
   CreateDistributedLoad(dls, CComBSTR("Stage 2"), lgn_sw, 2, mtSuperstructureMember, -0.3);

   CComBSTR lgn_br("Barrier");
   CComPtr<ILoadGroup> lgbr;
   TRY_TEST( lgbr.CoCreateInstance(CLSID_LoadGroup), S_OK);
   TRY_TEST( lgbr->put_Name(lgn_br), S_OK);
   TRY_TEST( lgs->Add(lgbr), S_OK);
   CreateDistributedLoad(dls, CComBSTR("Stage 2"), lgn_br, 0, mtSuperstructureMember, -0.25);
   CreateDistributedLoad(dls, CComBSTR("Stage 2"), lgn_br, 1, mtSuperstructureMember, -0.25);
   CreateDistributedLoad(dls, CComBSTR("Stage 2"), lgn_br, 2, mtSuperstructureMember, -0.25);

   CComPtr<ILoadCases> lcs;
   TRY_TEST( (*model)->get_LoadCases(&lcs), S_OK);
   CComPtr<ILoadCase> lcdc;
   TRY_TEST( lcs->Find(CComBSTR("DC"),&lcdc), S_OK);
   lcdc->AddLoadGroup(lgn_br);
   lcdc->AddLoadGroup(lgn_sw);

   CComBSTR lgn_ws("Wearing Surface");
   CComPtr<ILoadGroup> lgws;
   TRY_TEST( lgws.CoCreateInstance(CLSID_LoadGroup), S_OK);
   TRY_TEST( lgws->put_Name(lgn_ws), S_OK);
   TRY_TEST( lgs->Add(lgws), S_OK);
   CreateDistributedLoad(dls, CComBSTR("Stage 2"), lgn_ws, 0, mtSuperstructureMember, -0.15);
   CreateDistributedLoad(dls, CComBSTR("Stage 2"), lgn_ws, 1, mtSuperstructureMember, -0.15);
   CreateDistributedLoad(dls, CComBSTR("Stage 2"), lgn_ws, 2, mtSuperstructureMember, -0.15);

   CComPtr<ILoadCase> lcdw;
   TRY_TEST( lcs->Find(CComBSTR("DW"),&lcdw), S_OK);
   lcdw->AddLoadGroup(lgn_ws);

   // add some pois
   PoiIDType last_val;
   TRY_TEST(factory->GeneratePOIsOnSuperstructure(*model, 0, 4, &last_val), S_OK);

   // Save off to file for later inspection
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Solleks.xml")), S_OK );

      // get interface pointer 
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( (*model)->QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );
      TRY_TEST( pss->Close(), S_OK );
   }

   return S_OK;
}
