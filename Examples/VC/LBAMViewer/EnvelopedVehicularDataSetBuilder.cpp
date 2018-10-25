// EnvelopedVehicularDataSetBuilder.cpp: implementation of the EnvelopedVehicularDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "EnvelopedVehicularDataSetBuilder.h"
#include <iomanip>
#include <WbflAtlExt.h> // WBFL ATL Extensions and helpers
#include "LBAMViewerUtils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnvelopedVehicularDataSetBuilder::EnvelopedVehicularDataSetBuilder(LiveLoadModelType llmType, 
                                                                   VehicleIndexType vehicleIndex, llResponseType respType,
                                                                   IEnvelopedVehicularResponse* response):
m_pVehicularResponse(response),
m_LlmType(llmType),
m_VehicleIndex(vehicleIndex),
m_RespType(respType)
{
}

EnvelopedVehicularDataSetBuilder::~EnvelopedVehicularDataSetBuilder()
{

}

void EnvelopedVehicularDataSetBuilder::BuildDataSets(IIDArray* poiList, IDblArray* locList, BSTR currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
{
   if (currRt!=CLBAMViewerDoc::rtStress)
   {
      BuildForceDataSets(poiList, locList, currStg, currRt, summType,
                         color, dataSets);
   }
   else
   {
      BuildStressDataSets(poiList, locList, currStg, currRt, summType,
                          color, dataSets);
   }
}

CString EnvelopedVehicularDataSetBuilder::GetDescription()
{
   CString tmp;
   tmp.Format(_T("Enveloped Live Load Response For %s %d"), LL_NAMES[m_LlmType], m_VehicleIndex);

   return tmp;
}


void EnvelopedVehicularDataSetBuilder::BuildForceDataSets(IIDArray* poiList, IDblArray* locList, BSTR currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
{
   HRESULT hr;
   // deal with vehicle type
   VehicularLoadConfigurationType config_type;
   DWORD symbol_code;
   switch (m_RespType)
   {
   case llrTruckLaneCombo:
      config_type = vlcDefault;
      symbol_code = 224;
      break;
   case llrTruckOnly:
      config_type = vlcTruckOnly;
      symbol_code = 217;
      break;
   case llrLaneOnly:
   case llrSidewalkOnly:
   default:
      ATLASSERT(0);
   }

   bool is_force=false;
   ForceEffectType fet;
   if (currRt==CLBAMViewerDoc::rtFx || currRt==CLBAMViewerDoc::rtDx)
   {
      fet = fetFx;
      is_force = currRt==CLBAMViewerDoc::rtFx;
   }
   else if( currRt==CLBAMViewerDoc::rtFy || currRt==CLBAMViewerDoc::rtDy)
   {
      fet = fetFy;
      is_force = currRt==CLBAMViewerDoc::rtFy;
   }
   else if ( currRt==CLBAMViewerDoc::rtMz || currRt==CLBAMViewerDoc::rtRz)
   {
      fet = fetMz;
      is_force = currRt==CLBAMViewerDoc::rtMz;
   }
   else
   {
      ATLASSERT(0);
      return;
   }

   double flip = is_force ? -1.0 : 1.0;

   CollectionIndexType poi_cnt;
   poiList->get_Count(&poi_cnt);

   for (CollectionIndexType iopt=0; iopt<2; iopt++)
   {
      // first maximize
      // For shear, BEAM max = -FE min
      //            BEAM min = -FE max
      CString str;
      OptimizationType optimization;
      if (iopt == 0)
      {
         optimization = ( currRt==CLBAMViewerDoc::rtFy ? optMinimize : optMaximize);
         str.Format(_T("Env. %s %d - Max"), LL_NAMES[m_LlmType], m_VehicleIndex);
      }
      else
      {
         optimization = ( currRt==CLBAMViewerDoc::rtFy ? optMaximize : optMinimize);
         str.Format(_T("Env. %s %d - Min"), LL_NAMES[m_LlmType], m_VehicleIndex);
      }

      // create dataset 
      CComPtr<iGraphXyDataProvider> dataset_p;
      hr = dataset_p.CoCreateInstance(CLSID_GraphXyDataProvider);
      ATLASSERT(SUCCEEDED(hr));

      // deal with legend
      CComPtr<iDataPointFactory> fac;
      dataset_p->get_DataPointFactory(&fac);
      CComQIPtr<iSymbolLegendEntry> entry(fac);

      entry->put_Color(iopt == 0 ? color : ~color);
      entry->put_SymbolCharacterCode(symbol_code);
      entry->put_DoDrawLine(TRUE);

      CComBSTR bstr(str);
      entry->put_Name(bstr);

      CComPtr<iDataSet2d> dataset;
      dataset_p->get_DataSet(&dataset);

      CComPtr<ILiveLoadModelSectionResults> results;

      // get results
      VARIANT_BOOL bApplyImpact = VARIANT_FALSE; // individual truck responses don't have impact so we need to be consistent with the envelopes
      VARIANT_BOOL bComputePlacement = VARIANT_FALSE; // don't need the truck placements
#pragma Reminder("Make distribution factor an option")
      if (is_force)
      {
		   hr = m_pVehicularResponse->ComputeForces(poiList, currStg, m_LlmType, m_VehicleIndex, roGlobal,
										                    fet, optimization, config_type, bApplyImpact, dftNone, bComputePlacement,
                                                  &results);
      }
      else
      {
		   hr = m_pVehicularResponse->ComputeDeflections(poiList, currStg, m_LlmType, m_VehicleIndex, 
										                    fet, optimization, config_type, bApplyImpact, dftNone, bComputePlacement,
                                                  &results);
      }
      PROCESS_HR(hr);

      CollectionIndexType res_size;
      hr = results->get_Count(&res_size);
      PROCESS_HR(hr);

      ATLASSERT(res_size==poi_cnt);
      for (CollectionIndexType ipoi=0; ipoi<res_size; ipoi++)
      {
         double left_result, right_result;
         ILiveLoadConfiguration** ppDummy=NULL;
         hr = results->GetResult(ipoi, &left_result, ppDummy, &right_result, ppDummy);
         PROCESS_HR(hr);

         // For shear, BEAM max = -FE min
         //            BEAM min = -FE max
         if (currRt==CLBAMViewerDoc::rtFy)
         {
            left_result  *= -1;
            right_result *= -1;
         }

         // fill up data set
         CComPtr<IPoint2d> pnt;
         hr = pnt.CoCreateInstance(CLSID_Point2d);
         ATLASSERT(SUCCEEDED(hr));
         double loc;
         locList->get_Item(ipoi, &loc);
         pnt->put_X(loc);
         pnt->put_Y(left_result);
         dataset->Add(pnt);

         CComPtr<IPoint2d> rpnt;
         hr = rpnt.CoCreateInstance(CLSID_Point2d);
         ATLASSERT(SUCCEEDED(hr));
         rpnt->put_X(loc);
         rpnt->put_Y(flip*right_result);
         dataset->Add(rpnt);
      }

      dataSets->push_back( dataset_p.Detach());
   }
}

void EnvelopedVehicularDataSetBuilder::BuildStressDataSets(IIDArray* poiList, IDblArray* locList, BSTR currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
{
   HRESULT hr;
   // deal with vehicle type
   VehicularLoadConfigurationType config_type;
   DWORD symbol_code;
   switch (m_RespType)
   {
   case llrTruckLaneCombo:
      config_type = vlcDefault;
      symbol_code = 224;
      break;
   case llrTruckOnly:
      config_type = vlcTruckOnly;
      symbol_code = 217;
      break;
   case llrLaneOnly:
   case llrSidewalkOnly:
   default:
      ATLASSERT(0);
   }

   CollectionIndexType poi_cnt;
   poiList->get_Count(&poi_cnt);

   CComPtr<ILiveLoadModelStressResults> results;

   // get results
#pragma Reminder("Stresses are only computed for maximized Moment. Need to come up with GUI to change this")
   VARIANT_BOOL bApplyImpact = VARIANT_FALSE; // individual truck responses don't have impact so we need to be consistent with the envelopes
   VARIANT_BOOL bComputePlacement = VARIANT_FALSE; // don't need the truck placements
	hr = m_pVehicularResponse->ComputeStresses(poiList, currStg, m_LlmType, m_VehicleIndex,
										                fetMz, optMaximize, config_type, bApplyImpact, dftNone, bComputePlacement,
                                              &results);
   PROCESS_HR(hr);

   CollectionIndexType res_size;
   hr = results->get_Count(&res_size);
   PROCESS_HR(hr);

   // loop over each stress point
   CollectionIndexType isp=0;
   bool loop=true;
   while(loop)
   {
      HRESULT hr;
      bool is_results = false;

      // create dataset 
      CComPtr<iGraphXyDataProvider> dataset_p;
      hr = dataset_p.CoCreateInstance(CLSID_GraphXyDataProvider);
      ATLASSERT(SUCCEEDED(hr));

      // deal with legend
      CComPtr<iDataPointFactory> fac;
      dataset_p->get_DataPointFactory(&fac);
      CComQIPtr<iSymbolLegendEntry> entry(fac);

      entry->put_Color(color);
      entry->put_SymbolCharacterCode(DWORD(47+isp));
      entry->put_DoDrawLine(TRUE);

      CString str;
      str.Format(_T("Env. %s %d"), LL_NAMES[m_LlmType], m_VehicleIndex);
      CComBSTR bstr(str);
      entry->put_Name(bstr);

      CComPtr<iDataSet2d> dataset;
      dataset_p->get_DataSet(&dataset);

      for (CollectionIndexType ipoi=0; ipoi<res_size; ipoi++)
      {
         double loc;
         locList->get_Item(ipoi,&loc);

         CComPtr<IStressResult> left_sr, right_sr;
         CComPtr<ILiveLoadConfiguration> left_config, right_config;
         hr = results->GetResult(ipoi, &left_sr, &left_config, &right_sr, &right_config);
         PROCESS_HR(hr);

         double val;

         // left side
         CollectionIndexType cnt;
         hr = left_sr->get_Count(&cnt);
         PROCESS_HR(hr);

         if (isp<cnt)
         {
            // we have a left stress point
            is_results = true;

            hr = left_sr->GetResult(isp, &val);

            CComPtr<IPoint2d> pnt;
            hr = pnt.CoCreateInstance(CLSID_Point2d);
            ATLASSERT(SUCCEEDED(hr));
            pnt->put_X(loc);
            pnt->put_Y(val);
            dataset->Add(pnt);
         }

         // right side
         hr = right_sr->get_Count(&cnt);
         PROCESS_HR(hr);

         if (isp<cnt)
         {
            // we have a left stress point
            is_results = true;

            hr = right_sr->GetResult(isp, &val);

            CComPtr<IPoint2d> pnt;
            hr = pnt.CoCreateInstance(CLSID_Point2d);
            ATLASSERT(SUCCEEDED(hr));
            pnt->put_X(loc);
            pnt->put_Y(val);
            dataset->Add(pnt);
         }
      }

      isp++;
      // for now, limit the number of stress points to the max number of symbol types
      if (!is_results || isp>dpstLastDefault)
      {
         loop=false;
      }
      else
      {
         dataSets->push_back(dataset_p.Detach());
      }
   }
}


void EnvelopedVehicularDataSetBuilder::BuildReactionReport(IIDArray* supportlist, BSTR currStg,
                                       CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                       std::_tostream& os)
{
   HRESULT hr;
   bool is_force; // force or deflection
   switch(currRt)
   {
      case CLBAMViewerDoc::rtFx:
      case CLBAMViewerDoc::rtFy:
      case CLBAMViewerDoc::rtMz:
         is_force = true;
         break;
      case CLBAMViewerDoc::rtDx:
      case CLBAMViewerDoc::rtDy:
      case CLBAMViewerDoc::rtRz:
         is_force = false;
         break;
      default:
         ATLASSERT(0);
   }

   os<<C_R<<_T("------------------------------------------")<<C_R;

   os<<(is_force?_T("Reactions"):_T("Support Deflections"))<<_T(" for Enveloped Vehicular Live Load: ");
   switch (m_LlmType)
   {
   case lltNone:
      os <<_T("No Truck");
      break;
   case lltDeflection:
      os <<_T("Deflection Truck");
      break;
   case lltDesign:
      os <<_T("Design Truck");
      break;
   case lltPedestrian:
      os <<_T("Pedestrian Truck");
      break;
   case lltFatigue:
      os <<_T("Fatigue Truck");
      break;
   case lltPermit:
      os <<_T("Permit Truck");
      break;
   case lltSpecial:
      os <<_T("Special Truck");
      break;
   default:
      _ASSERT(0);
   }

   os <<C_R<<_T(" Vehicle Index = ")<<m_VehicleIndex;

   // deal with vehicle type
   std::_tstring strvlc;
   VehicularLoadConfigurationType config_type = GetConfigType(m_RespType, strvlc);

   os<<_T(" Config = ")<<strvlc<<_T(" - Enveloped")<< C_R;

   os<<_T(" Results for Stage: ")<<(const TCHAR*)CString(currStg)<<C_R<<C_R;

   if (is_force)
      os<<_T("Support        Rx         Ry           Mz")<<C_R;
   else
      os<<_T("Support        Dx         Dy           Rz")<<C_R;

   os<<_T("------- ------------ ------------ ------------")<<C_R;

   // get results
   CComPtr<ILiveLoadModelResults> fx_min, fy_min, fz_min;
   VARIANT_BOOL bApplyImpact = VARIANT_FALSE; // individual truck responses don't have impact so we need to be consistent with the envelopes
   VARIANT_BOOL bComputePlacement = VARIANT_FALSE; // don't need the truck placements
   if (is_force)
   {
      hr = m_pVehicularResponse->ComputeReactions(supportlist, currStg, m_LlmType, m_VehicleIndex, fetFx, optMinimize,
                                                  config_type,bApplyImpact, dftNone, bComputePlacement, &fx_min);
      PROCESS_HR(hr);
      hr = m_pVehicularResponse->ComputeReactions(supportlist, currStg, m_LlmType, m_VehicleIndex, fetFy, optMinimize,
                                                      config_type,bApplyImpact, dftNone, bComputePlacement, &fy_min);
      PROCESS_HR(hr);
      hr = m_pVehicularResponse->ComputeReactions(supportlist, currStg, m_LlmType, m_VehicleIndex, fetMz, optMinimize,
                                                      config_type,bApplyImpact, dftNone, bComputePlacement, &fz_min);
      PROCESS_HR(hr);
   }
   else
   {
      hr = m_pVehicularResponse->ComputeSupportDeflections(supportlist, currStg, m_LlmType, m_VehicleIndex, fetFx, optMinimize,
                                                  config_type,bApplyImpact, dftNone, bComputePlacement, &fx_min);
      PROCESS_HR(hr);
      hr = m_pVehicularResponse->ComputeSupportDeflections(supportlist, currStg, m_LlmType, m_VehicleIndex, fetFy, optMinimize,
                                                      config_type,bApplyImpact, dftNone, bComputePlacement, &fy_min);
      PROCESS_HR(hr);
      hr = m_pVehicularResponse->ComputeSupportDeflections(supportlist, currStg, m_LlmType, m_VehicleIndex, fetMz, optMinimize,
                                                      config_type,bApplyImpact, dftNone, bComputePlacement, &fz_min);
      PROCESS_HR(hr);
   }

   ILiveLoadConfiguration* null_config=NULL;

   CollectionIndexType size;
   supportlist->get_Count(&size);
   for (CollectionIndexType i=0; i<size; i++)
   {
      double rx, ry, rz;
      hr = fx_min->GetResult(i, &rx, &null_config);
      PROCESS_HR(hr);
      hr = fy_min->GetResult(i, &ry, &null_config);
      PROCESS_HR(hr);
      hr = fz_min->GetResult(i, &rz, &null_config);
      PROCESS_HR(hr);

      IDType spt;
      supportlist->get_Item(i,&spt);
      os<<(i==0?_T("Min"):_T("   "))<<std::setw(4)<<spt<<std::fixed<<std::setprecision(2)<<std::setw(13)<<rx<<std::setw(13)<<ry<<std::setw(13)<<rz<<C_R;
   }

   CComPtr<ILiveLoadModelResults> fx_max, fy_max, fz_max;
   if (is_force)
   {
      hr = m_pVehicularResponse->ComputeReactions(supportlist, currStg, m_LlmType, m_VehicleIndex, fetFx, optMaximize,
                                                      config_type,bApplyImpact, dftNone, bComputePlacement, &fx_max);
      PROCESS_HR(hr);
      hr = m_pVehicularResponse->ComputeReactions(supportlist, currStg, m_LlmType, m_VehicleIndex, fetFy, optMaximize,
                                                      config_type,bApplyImpact, dftNone, bComputePlacement, &fy_max);
      PROCESS_HR(hr);
      hr = m_pVehicularResponse->ComputeReactions(supportlist, currStg, m_LlmType, m_VehicleIndex, fetMz, optMaximize,
                                                      config_type,bApplyImpact, dftNone, bComputePlacement, &fz_max);
      PROCESS_HR(hr);
   }
   else
   {
      hr = m_pVehicularResponse->ComputeSupportDeflections(supportlist, currStg, m_LlmType, m_VehicleIndex, fetFx, optMaximize,
                                                      config_type,bApplyImpact, dftNone, bComputePlacement, &fx_max);
      PROCESS_HR(hr);
      hr = m_pVehicularResponse->ComputeSupportDeflections(supportlist, currStg, m_LlmType, m_VehicleIndex, fetFy, optMaximize,
                                                      config_type,bApplyImpact, dftNone, bComputePlacement, &fy_max);
      PROCESS_HR(hr);
      hr = m_pVehicularResponse->ComputeSupportDeflections(supportlist, currStg, m_LlmType, m_VehicleIndex, fetMz, optMaximize,
                                                      config_type,bApplyImpact, dftNone, bComputePlacement, &fz_max);
      PROCESS_HR(hr);
   }

   for (CollectionIndexType i=0; i<size; i++)
   {
      double rx, ry, rz;
      hr = fx_max->GetResult(i, &rx, &null_config);
      PROCESS_HR(hr);
      hr = fy_max->GetResult(i, &ry, &null_config);
      PROCESS_HR(hr);
      hr = fz_max->GetResult(i, &rz, &null_config);
      PROCESS_HR(hr);

      IDType spt;
      supportlist->get_Item(i,&spt);
      os<<(i==0?_T("Max"):_T("   "))<<std::setw(4)<<spt<<std::fixed<<std::setprecision(2)<<std::setw(13)<<rx<<std::setw(13)<<ry<<std::setw(13)<<rz<<C_R;
   }

}

