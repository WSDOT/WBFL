///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2017  Washington State Department of Transportation
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


#if !defined INCLUDED_LIVELOADUTILS_H_
#define INCLUDED_LIVELOADUTILS_H_
#include "WBFLLBam.h"
#include "WBFLLBamAnalysis.h"
#include "WBFLLBamAnalysis.h"

#include "LBAMLiveLoader.hh"

// macros to help error processing
// short-hand version if consistent naming conventions are used
#define THROW_LBAMLL(errNam) { ATLASSERT(false); THROW_LBAMLL_NOA(errNam);}
#define THROW_LBAMLL_NOA(errNam) { throw CComException(_T(__FILE__),__LINE__, IDS_E_##errNam, LBAMLL_E_##errNam, IDH_E_##errNam);}
#define THROW_LBAMLL_MSG(errNam, msg) { ATLASSERT(false); throw CComException(_T(__FILE__),__LINE__, msg, LBAMLL_E_##errNam, IDH_E_##errNam);}

#define PROCESS_HR(hr) if (FAILED(hr)){ THROW_HR(hr) }

// get the vehicular load from a model
inline void GetLiveLoadModel(LiveLoadModelType type, ILiveLoad* pll, ILiveLoadModel** ppLlm)
{
   HRESULT hr;

   switch(type)
   {
   case lltDeflection:
      hr = pll->get_Deflection(ppLlm);
      break;
   case lltDesign:  
      hr = pll->get_Design(ppLlm);
      break;
   case lltPedestrian:
      hr = pll->get_Pedestrian(ppLlm);
      break;
   case lltFatigue:  
      hr = pll->get_Fatigue(ppLlm);
      break;
   case lltPermit:
      hr = pll->get_Permit(ppLlm);
      break;
   case lltSpecial:
      hr = pll->get_Special(ppLlm);
      break;
   case lltLegalRoutineRating:
      hr = pll->get_LegalRoutineRating(ppLlm);
      break;
   case lltLegalSpecialRating:
      hr = pll->get_LegalSpecialRating(ppLlm);
      break;
   case lltPermitRoutineRating:
      hr = pll->get_PermitRoutineRating(ppLlm);
      break;
   case lltPermitSpecialRating:
      hr = pll->get_PermitSpecialRating(ppLlm);
      break;
   default:
      ATLASSERT(false);
      THROW_HR(E_FAIL);
   };
   PROCESS_HR(hr);
}


inline void GetVehicularLoad(LiveLoadModelType type, VehicleIndexType vehicleIndex, ILiveLoad* pll, IVehicularLoad** ppVl)
{
   HRESULT hr;

   CComPtr<ILiveLoadModel> pllm;
   GetLiveLoadModel(type, pll, &pllm);

   CComPtr<IVehicularLoads> pvls;
   hr = pllm->get_VehicularLoads(&pvls);
   PROCESS_HR(hr);

   hr = pvls->get_Item(vehicleIndex, ppVl);
   if (FAILED(hr))
   {
      THROW_LBAMLL(VEHICULARLOAD_NOT_FOUND);
   }
}


inline bool VehicularLoadConfigurationHasTruck(VehicularLoadConfigurationType vlc)
{
   if ( vlc == vlcTruckOnly || vlc == vlcTruckPlusLane || vlc == vlcTruckLaneEnvelope )
      return true;

   return false;
}

inline bool VehicularLoadConfigurationHasLane(VehicularLoadConfigurationType vlc)
{
   if ( vlc == vlcLaneOnly || vlc == vlcTruckPlusLane || vlc == vlcTruckLaneEnvelope || vlc == vlcSidewalkOnly )
      return true;

   return false;
}

inline VehicularLoadConfigurationType GetSelectedVehicularConfiguration(VehicularLoadConfigurationType requestedConfig, IVehicularLoad* pVl)
{
   // Determine the vehicular configuration based on the client request and 
   // the vehicularload information
   HRESULT hr;
   VehicularLoadConfigurationType veh_config;
   hr = pVl->get_Configuration(&veh_config);
   PROCESS_HR(hr);
   if (requestedConfig == vlcDefault)
   {
      // requested default - use application type from vehicularload
      if (veh_config == vlcDefault)
         return vlcTruckPlusLane; // this is the global default
      else
         return veh_config;
   }
   else
   {
      if ( 
         (VehicularLoadConfigurationHasTruck(requestedConfig) && VehicularLoadConfigurationHasTruck(veh_config) ) ||
         (VehicularLoadConfigurationHasLane(requestedConfig)  && VehicularLoadConfigurationHasLane(veh_config) ) 
         )
      {
         // compatible
         return requestedConfig;
      }
      else
      {
         return veh_config;
      }
   }
}

inline HRESULT LLSectionToStressResults(IIDArray* POIs, BSTR stage, ILiveLoadModelSectionResults* forceRes, 
                                        IBasicVehicularResponse* basicResponse,
                                        ILiveLoadModelStressResults**pResults)
{
   HRESULT hr;
   CollectionIndexType num_pois;
   hr = forceRes->get_Count(&num_pois);
   if (FAILED(hr))
      return hr;

   // Create our results object
   CComPtr<ILiveLoadModelStressResults> results;
   hr = results.CoCreateInstance(CLSID_LiveLoadModelStressResults);
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
   for (CollectionIndexType ipoi=0; ipoi<num_pois; ipoi++)
   {
      // use configuration object from force results to compute stresses
      // get left and right config objects
      Float64 left_force, right_force;
      CComPtr<ILiveLoadConfiguration> left_config, right_config;
      hr = forceRes->GetResult(ipoi, &left_force, &left_config, &right_force, &right_config);
      if (FAILED(hr))
         return hr;

      // compute results one poi at a time
      PoiIDType poi_id;
      POIs->get_Item(ipoi,&poi_id);
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