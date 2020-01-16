///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner Test - Test driver for LBAM analysis library
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

// TestUsingBogusContext.cpp: implementation of the CTestUsingBogusContext class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestUsingBogusContext.h"
#include "BogusCombinationContext/BogusComboContext.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTestUsingBogusContext::CTestUsingBogusContext()
{

}

CTestUsingBogusContext::~CTestUsingBogusContext()
{

}


void CTestUsingBogusContext::Test()
{
   HRESULT hr;

   // make an item to test
   CComPtr<ILoadCaseResponse> lc_response;
   TRY_TEST(lc_response.CoCreateInstance( CLSID_LoadCombiner ), S_OK );

   // create our bogus context
   CComPtr<ILoadCombinationAnalysisContext> plclc;
   plclc.CoCreateInstance(CLSID_BogusComboContext);

   CComQIPtr<ICompareBogusResults> compare(plclc);
   ATLASSERT(compare);
//   CBogusComboContext* pcontext = dynamic_cast<CBogusComboContext*>(plclc.p);

   // initialize our load combiner with the context
   CComQIPtr<IDependOnLoadCombinationAnalysisContext> depctx(lc_response);
   TRY_TEST(depctx!=nullptr, true);
   TRY_TEST(depctx->Initialize(plclc), S_OK);

   // get list of pois from context
   CComQIPtr<IAnalysisPOIs> anpois(plclc);
   CComPtr<IIDArray> pois;
   CComPtr<IDblArray> bogus;
   anpois->GetSuperstructurePois(CComBSTR("Stage 1"), &pois, &bogus);

   CollectionIndexType num_pois;
   pois->get_Count(&num_pois);
   PoiIDType id;
   pois->get_Item(0,&id);

   //////////////////////////////////////////////////////////////
   // NOTE: See FinalConstruct Method in BogusComboContext for calculations of numbers
   //       that are compared by this test
   ///////////////////////////////////////////////////////////////

   // test load case results
   CComQIPtr<IStages> stages(plclc);
   CComQIPtr<ILoadCases> loadcases(plclc);
   CollectionIndexType num_loadcases;
   StageIndexType num_stages;
   stages->get_Count(&num_stages);
   loadcases->get_Count(&num_loadcases);

   for (StageIndexType istg = 0; istg<num_stages; istg++)
   {
      CComPtr<IStage> ostg;
      stages->get_Item(istg, &ostg);
      CComBSTR stage;
      ostg->get_Name(&stage);

      for (CollectionIndexType ilc = 0; ilc<num_loadcases; ilc++)
      {
         CComPtr<ILoadCase> olc;
         loadcases->get_Item(ilc, &olc);
         CComBSTR load_case;
         olc->get_Name(&load_case);

         for (long isumm = 0; isumm<2; isumm++)
         {
            // need both incremental and cumulative results
            ResultsSummationType summ = (isumm==0)? rsIncremental:rsCumulative;

            // forces
            CComPtr<ISectionResult3Ds> secres3ds;
            hr = lc_response->ComputeForces(load_case, pois, stage, roGlobal, 
                                            summ, &secres3ds);
            TRY_TEST(hr, S_OK);

            hr = compare->CompareLoadCaseSectionResults(load_case, stage, summ, VARIANT_TRUE, secres3ds);
            TRY_TEST(hr, S_OK);

            // deflections
            secres3ds.Release();
            hr = lc_response->ComputeDeflections(load_case, pois, stage,
                                            summ, &secres3ds);
            TRY_TEST(hr, S_OK);

            hr = compare->CompareLoadCaseSectionResults(load_case, stage, summ, VARIANT_FALSE, secres3ds);
            TRY_TEST(hr, S_OK);

            // reactions
            CComPtr<IResult3Ds> res3ds;
            hr = lc_response->ComputeReactions(load_case, pois, stage, summ, &res3ds);
            TRY_TEST(hr, S_OK);

            hr = compare->CompareLoadCaseResults(load_case, stage, summ, res3ds);
            TRY_TEST(hr, S_OK);

            // support deflections
            res3ds.Release();
            hr = lc_response->ComputeSupportDeflections(load_case, pois, stage, summ, &res3ds);
            TRY_TEST(hr, S_OK);

            hr = compare->CompareLoadCaseResults(load_case, stage, summ, res3ds);
            TRY_TEST(hr, S_OK);

            // stresses
            CComPtr<ISectionStressResults> stresses;
            hr = lc_response->ComputeStresses(load_case, pois, stage, summ, &stresses);
            TRY_TEST(hr, S_OK);

            hr = compare->CompareLoadCaseStressResults(load_case, stage, summ, stresses);
            TRY_TEST(hr, S_OK);

         }
      }
   }

   // LoadCombinations
   CComQIPtr<ILoadCombinationResponse> lcmb_response(lc_response);
   CComQIPtr<IConcurrentLoadCombinationResponse> conc_response(lc_response);

   CComQIPtr<ILoadCombinations> loadcombos(plclc);
   CollectionIndexType num_loadcombos;
   loadcombos->get_Count(&num_loadcombos);

   for (StageIndexType istg = 0; istg<num_stages; istg++)
   {
      CComPtr<IStage> ostg;
      stages->get_Item(istg, &ostg);
      CComBSTR stage;
      ostg->get_Name(&stage);

      VARIANT_BOOL compute_ll = istg==num_stages-1 ? VARIANT_TRUE : VARIANT_FALSE;

      for (CollectionIndexType ilc = 0; ilc<num_loadcombos; ilc++)
      {
         CComPtr<ILoadCombination> olc;
         loadcombos->get_Item(ilc, &olc);
         CComBSTR load_combo;
         olc->get_Name(&load_combo);

         // need both incremental and cumulative results
         for (long isumm = 0; isumm<2; isumm++)
         {
            ResultsSummationType summ = (isumm==0)? rsIncremental:rsCumulative;

            // need all dof's
            for (long idof = 0; idof<3; idof++)
            {
               ForceEffectType feff;
               if (idof==0)
                  feff = fetFx;
               else if (idof==1)
                  feff = fetFy;
               else
                  feff = fetMz;

               // maximize and minimize
               for (long iopt = 0; iopt<2; iopt++)
               {
                  OptimizationType opt = iopt==0 ? optMinimize : optMaximize;

                  // Forces
                  CComPtr<ILoadCombinationSectionResults> secress;
                  hr = lcmb_response->ComputeForces(load_combo, pois, stage, roGlobal, 
                                                    summ, feff, opt, compute_ll, VARIANT_TRUE, VARIANT_TRUE, &secress);
                  TRY_TEST(hr, S_OK);

                  hr = compare->CompareLoadCombinationSectionResults(load_combo, stage, summ, feff, opt, VARIANT_TRUE, secress);
                  TRY_TEST(hr, S_OK);

                  // loop over all pois to get concurrent results
                  for (CollectionIndexType ipoi = 0; ipoi<num_pois; ipoi++)
                  {
                     CComPtr<ILoadCombinationResultConfiguration> left_config, right_config;
                     Float64 left_val, right_val;
                     secress->GetResult(ipoi, &left_val, &left_config, &right_val, &right_config);

                     CComPtr<ISectionResult3Ds> left_secres, right_secres;
                     hr = conc_response->ComputeForces(pois, stage, roGlobal, left_config, &left_secres);
                     compare->CompareLoadCombinationSectionRes(load_combo, stage, summ, opt, VARIANT_TRUE, left_secres);

                     hr = conc_response->ComputeForces(pois, stage, roGlobal, right_config, &right_secres);
                     compare->CompareLoadCombinationSectionRes(load_combo, stage, summ, opt, VARIANT_TRUE, right_secres);
                  }

                  // Deflections
                  secress.Release();
                  hr = lcmb_response->ComputeDeflections(load_combo, pois, stage,
                                                    summ, feff, opt, compute_ll, VARIANT_TRUE, VARIANT_TRUE, &secress);
                  TRY_TEST(hr, S_OK);

                  hr = compare->CompareLoadCombinationSectionResults(load_combo, stage, summ, feff, opt, VARIANT_FALSE, secress);
                  TRY_TEST(hr, S_OK);

                  // loop over all pois to get concurrent results
                  for (CollectionIndexType ipoi = 0; ipoi<num_pois; ipoi++)
                  {
                     CComPtr<ILoadCombinationResultConfiguration> left_config, right_config;
                     Float64 left_val, right_val;
                     secress->GetResult(ipoi, &left_val, &left_config, &right_val, &right_config);

                     CComPtr<ISectionResult3Ds> left_secres, right_secres;
                     hr = conc_response->ComputeDeflections(pois, stage, left_config, &left_secres);
                     compare->CompareLoadCombinationSectionRes(load_combo, stage, summ, opt, VARIANT_FALSE, left_secres);

                     hr = conc_response->ComputeDeflections(pois, stage, right_config, &right_secres);
                     compare->CompareLoadCombinationSectionRes(load_combo, stage, summ, opt, VARIANT_FALSE, right_secres);
                  }

                  // reactions
                  CComPtr<ILoadCombinationResults> ress;
                  hr = lcmb_response->ComputeReactions(load_combo, pois, stage,
                                                       summ, feff, opt, compute_ll, VARIANT_TRUE, VARIANT_TRUE, &ress);
                  TRY_TEST(hr, S_OK);

                  hr = compare->CompareLoadCombinationResults(load_combo, stage, summ, feff, opt, ress);
                  TRY_TEST(hr, S_OK);

                  // loop over all pois to get concurrent results
                  for (CollectionIndexType ipoi = 0; ipoi<num_pois; ipoi++)
                  {
                     CComPtr<ILoadCombinationResultConfiguration> config;
                     Float64 val;
                     ress->GetResult(ipoi, &val, &config);

                     CComPtr<IResult3Ds> res;
                     hr = conc_response->ComputeReactions(pois, stage, config, &res);
                     compare->CompareLoadCombinationRes(load_combo, stage, summ, opt, res);
                  }

                  // support deflections
                  ress.Release();
                  hr = lcmb_response->ComputeSupportDeflections(load_combo, pois, stage,
                                                       summ, feff, opt, compute_ll, VARIANT_TRUE, VARIANT_TRUE, &ress);
                  TRY_TEST(hr, S_OK);

                  hr = compare->CompareLoadCombinationResults(load_combo, stage, summ, feff, opt, ress);
                  TRY_TEST(hr, S_OK);

                  // loop over all pois to get concurrent results
                  for (CollectionIndexType ipoi = 0; ipoi<num_pois; ipoi++)
                  {
                     CComPtr<ILoadCombinationResultConfiguration> config;
                     Float64 val;
                     ress->GetResult(ipoi, &val, &config);

                     CComPtr<IResult3Ds> res;
                     hr = conc_response->ComputeSupportDeflections(pois, stage, config, &res);
                     compare->CompareLoadCombinationRes(load_combo, stage, summ, opt, res);
                  }

                  // stresses
                  CComPtr<ILoadCombinationStressResults> stressress;
                  hr = lcmb_response->ComputeStresses(load_combo, pois, stage,
                                                       summ, feff, opt, compute_ll, VARIANT_TRUE, VARIANT_TRUE, &stressress);
                  TRY_TEST(hr, S_OK);

                  hr = compare->CompareLoadCombinationStressResults(load_combo, stage, summ, feff, opt, stressress);
                  TRY_TEST(hr, S_OK);

                  // loop over all pois to get concurrent results
                  for (CollectionIndexType ipoi = 0; ipoi<num_pois; ipoi++)
                  {
                     CComPtr<ILoadCombinationResultConfiguration> leftconfig, rightconfig;
                     CComPtr<IStressResult> leftval, rightval;
                     stressress->GetResult(ipoi, &leftval, &leftconfig, &rightval, &rightconfig);

                     CComPtr<ISectionStressResults> leftres, rightres;
                     hr = conc_response->ComputeStresses(pois, stage, leftconfig, &leftres);
                     compare->CompareLoadCombinationStressRes(load_combo, stage, summ, opt, leftres);

                     hr = conc_response->ComputeStresses(pois, stage, rightconfig, &rightres);
                     compare->CompareLoadCombinationStressRes(load_combo, stage, summ, opt, rightres);
                  }
               }
            }
         }
      }
   }
}