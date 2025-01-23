///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2025  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#if !defined INCLUDED_LOADCOMBUTILS_H_
#define INCLUDED_LOADCOMBUTILS_H_
#include "WBFLLBam.h"
#include "WBFLLBamAnalysis.h"


inline HRESULT CombSectionToStressResults(IIDArray* POIs, BSTR stage, ILoadCombinationSectionResults* forceRes, 
                                          IConcurrentLoadCombinationResponse* basicResponse,
                                          ILoadCombinationStressResults**pResults)
{
   HRESULT hr;
   IndexType num_pois;
   hr = forceRes->get_Count(&num_pois);
   if (FAILED(hr))
      return hr;

   // Create our results object
   CComPtr<ILoadCombinationStressResults> results;
   hr = results.CoCreateInstance(CLSID_LoadCombinationStressResults);
   if (FAILED(hr))
      return hr;

   hr = results->Reserve(num_pois);
   if (FAILED(hr))
      return hr;

   CComPtr<IIDArray> single_poi;
   hr = single_poi.CoCreateInstance(CLSID_IDArray);
   if (FAILED(hr))
      return hr;

   hr = single_poi->ReDim(1);
   if (FAILED(hr))
      return hr;


   // loop over all pois and compute stresses due to optimization at that poi
   for (IndexType ipoi = 0; ipoi<num_pois; ipoi++)
   {
      // use configuration object from force results to compute stresses
      // get left and right config objects
      Float64 left_force, right_force;
      CComPtr<ILoadCombinationResultConfiguration> left_config, right_config;
      hr = forceRes->GetResult(ipoi, &left_force, &left_config, &right_force, &right_config);
      if (FAILED(hr))
         return hr;

      // compute results one poi at a time
      PoiIDType poi_id;
      POIs->get_Item(ipoi, &poi_id);
      single_poi->put_Item(0, poi_id);

      CComPtr<ISectionStressResults> left_stresses, right_stresses;
      hr = basicResponse->ComputeStresses(single_poi, stage, left_config, &left_stresses);
      if (FAILED(hr))
         return hr;

      hr = basicResponse->ComputeStresses(single_poi, stage, right_config, &right_stresses);
      if (FAILED(hr))
         return hr;

      CComPtr<ISectionStressResult> left_sec_stress, right_sec_stress;
      hr = left_stresses->get_Item(0, &left_sec_stress);
      if (FAILED(hr))
         return hr;

      hr = right_stresses->get_Item(0, &right_sec_stress);
      if (FAILED(hr))
         return hr;

      // extract out results from left and right sections
      CComPtr<IStressResult> left_stress, right_stress;
      hr = left_sec_stress->CreateLeftStressResult(&left_stress);
      if (FAILED(hr))
         return hr;

      hr = right_sec_stress->CreateRightStressResult(&right_stress);
      if (FAILED(hr))
         return hr;

      hr = results->Add(left_stress, left_config, right_stress, right_config);
      if (FAILED(hr))
         return hr;
   }

   return results.CopyTo(pResults);
}


#endif 