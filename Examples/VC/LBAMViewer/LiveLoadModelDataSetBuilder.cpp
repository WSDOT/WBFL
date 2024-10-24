// LiveLoadModelDataSetBuilder.cpp: implementation of the LiveLoadModelDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "LiveLoadModelDataSetBuilder.h"
#include <iomanip>
#include "LBAMViewerUtils.h"
#include "GraphXYDisplayObjectImpl.h"
#include "Legend.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
LiveLoadModelDataSetBuilder::LiveLoadModelDataSetBuilder(LiveLoadModelType llmType, llResponseType respType,
                                                         ILiveLoadModelResponse* response):
m_pLiveLoadModelResponse(response),
m_LlmType(llmType),
m_RespType(respType)
{
}

LiveLoadModelDataSetBuilder::~LiveLoadModelDataSetBuilder()
{

}


void LiveLoadModelDataSetBuilder::BuildDataSets(IIDArray* poiList, IDblArray* locList, const CString& currStg,
                                  CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                  COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets)
{
   if (currRt!=CLBAMViewerDoc::rtStress)
   {
      BuildForceDataSets(poiList, locList, CComBSTR(currStg), currRt, summType,
                         color, dataSets);
   }
   else
   {
      BuildStressDataSets(poiList, locList, CComBSTR(currStg), currRt, summType,
                          color, dataSets);
   }
}

CString LiveLoadModelDataSetBuilder::GetDescription()
{
   CString tmp;
   tmp.Format(_T("Enveloped Live Load Model Response For %s "), LL_NAMES[m_LlmType]);

   return tmp;
}


void LiveLoadModelDataSetBuilder::BuildForceDataSets(IIDArray* poiList, IDblArray* locList, BSTR currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets)
{

   HRESULT hr;

   // deal with vehicle type
   std::_tstring strvlc;
   VehicularLoadConfigurationType config_type = GetConfigType(m_RespType, strvlc);

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

   IndexType poi_cnt;
   poiList->get_Count(&poi_cnt);

   for (Uint32 iopt=0; iopt<2; iopt++)
   {
      CString str;
      // first maximize
      OptimizationType optimization;
      if (iopt==0)
      {
         optimization = optMaximize;
         str.Format(_T("LL Env %s Max"), LL_NAMES[m_LlmType]);
      }
      else
      {
         optimization = optMinimize;
         str.Format(_T("LL Env %s Min"), LL_NAMES[m_LlmType]);
      }

      // create dataset 
      auto dataset_p = std::make_shared<CGraphXyDataProvider>();

      // deal with legend
      auto fac = dataset_p->GetDataPointFactory();
      auto entry = std::dynamic_pointer_cast<iSymbolLegendEntry>(fac);

      entry->SetColor(color);
      entry->SetSymbolFontFace(_T("Webdings"));
      entry->SetSymbolCharacterCode(104);
      entry->DoDrawLine(TRUE);

      entry->SetName(str.LockBuffer());

      auto dataset = dataset_p->GetDataSet();

      CComPtr<ILiveLoadModelSectionResults> results;

      VARIANT_BOOL bApplyImpact = VARIANT_FALSE;
      // get results
      if (is_force)
      {
		   hr = m_pLiveLoadModelResponse->ComputeForces(poiList, currStg, m_LlmType, roGlobal,
										                   fet, optimization, config_type, bApplyImpact, VARIANT_FALSE,
                                                 VARIANT_FALSE, &results);
      }
      else
      {
		   hr = m_pLiveLoadModelResponse->ComputeDeflections(poiList, currStg, m_LlmType,
										                   fet, optimization, config_type, bApplyImpact, VARIANT_FALSE,
                                                 VARIANT_FALSE, &results);
      }
      PROCESS_HR(hr);

      IndexType res_size;
      hr = results->get_Count(&res_size);
      PROCESS_HR(hr);

      ATLASSERT(res_size==poi_cnt);
      for (IndexType ipoi=0; ipoi<res_size; ipoi++)
      {
         double left_result, right_result;
         ILiveLoadConfiguration** ppDummy=NULL;
         hr = results->GetResult(ipoi, &left_result, ppDummy, &right_result, ppDummy);
         PROCESS_HR(hr);

         if (currRt==CLBAMViewerDoc::rtFy )
         {
            // convert shear force values to beam diagram coordinates
            left_result  *= -1;
            right_result *= -1;
         }

         // fill up data set
         double loc;
         locList->get_Item(ipoi, &loc);
         WBFL::Geometry::Point2d pnt(loc, left_result);
         dataset->Add(pnt);

         if (right_result!= left_result)
         {
            WBFL::Geometry::Point2d rpnt(loc, -right_result);
            dataset->Add(rpnt);
         }
      }

      dataSets->push_back( dataset_p );
   }
}

void LiveLoadModelDataSetBuilder::BuildStressDataSets(IIDArray* poiList, IDblArray* locList, BSTR currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets)
{
   HRESULT hr;
   // deal with vehicle type
   VehicularLoadConfigurationType config_type;
   switch (m_RespType)
   {
   case llrTruckLaneCombo:
      config_type = vlcDefault;
      break;
   case llrTruckOnly:
      config_type = vlcTruckOnly;
      break;
   case llrLaneOnly:
   case llrSidewalkOnly:
   default:
      ATLASSERT(0);
   }

   IndexType poi_cnt;
   poiList->get_Count(&poi_cnt);

   CComPtr<ILiveLoadModelStressResults> results;

   // get results
#pragma Reminder("Stresses are only computed for maximized Moment. Need to come up with GUI to change this")
	hr = m_pLiveLoadModelResponse->ComputeStresses(poiList, currStg, m_LlmType, 
										                fetMz, optMaximize, config_type, VARIANT_TRUE, dftNone, VARIANT_FALSE,
                                              &results);
   PROCESS_HR(hr);

   IndexType res_size;
   hr = results->get_Count(&res_size);
   PROCESS_HR(hr);

   // loop over each stress point
   IndexType isp=0;
   bool loop=true;
   while(loop)
   {
      HRESULT hr;
      bool is_results = false;

      // create dataset 
      auto dataset_p = std::make_shared<CGraphXyDataProvider>();

      // deal with legend
      auto fac = dataset_p->GetDataPointFactory();
      auto entry = std::dynamic_pointer_cast<iSymbolLegendEntry>(fac);

      entry->SetColor(color);
      entry->SetSymbolFontFace(_T("Wingdings"));
      entry->SetSymbolCharacterCode(DWORD(128+isp));
      entry->DoDrawLine(TRUE);

      CString str;
      str.Format(_T("LL Env %s SP %d"), LL_NAMES[m_LlmType],isp);
      entry->SetName(str.LockBuffer());

      auto dataset = dataset_p->GetDataSet();

      for (IndexType ipoi=0; ipoi<res_size; ipoi++)
      {
         double loc;
         locList->get_Item(ipoi,&loc);

         CComPtr<IStressResult> left_sr, right_sr;
         CComPtr<ILiveLoadConfiguration> left_config, right_config;
         hr = results->GetResult(ipoi, &left_sr, &left_config, &right_sr, &right_config);
         PROCESS_HR(hr);

         double val;

         // left side
         IndexType cnt;
         hr = left_sr->get_Count(&cnt);
         PROCESS_HR(hr);

         if (isp<cnt)
         {
            // we have a left stress point
            is_results = true;

            hr = left_sr->GetResult(isp, &val);

            WBFL::Geometry::Point2d pnt(loc, val);
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

            WBFL::Geometry::Point2d pnt(loc, val);
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
         dataSets->push_back(dataset_p);
      }
   }
}

void LiveLoadModelDataSetBuilder::BuildReactionReport(IIDArray* supportlist, BSTR currStg,
                                  CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                  std::_tostream& os)
{
   HRESULT hr;
   os<<C_R<<_T("------------------------------------------")<<C_R;

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


   os<<(is_force?_T("Reactions"):_T("Support Deflections"))<<_T(" for Live Load Model: ");
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

   // deal with vehicle type
   std::_tstring strvlc;
   VehicularLoadConfigurationType config_type = GetConfigType(m_RespType, strvlc);

   os<<_T(" - ")<<strvlc<< C_R;

   os<<_T(" Results for Stage: ")<<(const TCHAR*)CString(currStg)<<C_R<<C_R;

   if (is_force)
      os<<_T("Support        Rx         Ry           Mz")<<C_R;
   else
      os<<_T("Support        Dx         Dy           Rz")<<C_R;
   os<<_T("------- ------------ ------------ ------------")<<C_R;

   // get results
   CComPtr<ILiveLoadModelResults> fx_min, fy_min, fz_min;
   if (is_force)
   {
      hr = m_pLiveLoadModelResponse->ComputeReactions(supportlist, currStg, m_LlmType, fetFx, optMinimize,
                                                      config_type,VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fx_min);
      PROCESS_HR(hr);
      hr = m_pLiveLoadModelResponse->ComputeReactions(supportlist, currStg, m_LlmType, fetFy, optMinimize,
                                                      config_type,VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fy_min);
      PROCESS_HR(hr);
      hr = m_pLiveLoadModelResponse->ComputeReactions(supportlist, currStg, m_LlmType, fetMz, optMinimize,
                                                      config_type,VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fz_min);
      PROCESS_HR(hr);
   }
   else
   {
      hr = m_pLiveLoadModelResponse->ComputeSupportDeflections(supportlist, currStg, m_LlmType, fetFx, optMinimize,
                                                      config_type,VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fx_min);
      PROCESS_HR(hr);
      hr = m_pLiveLoadModelResponse->ComputeSupportDeflections(supportlist, currStg, m_LlmType, fetFy, optMinimize,
                                                      config_type,VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fy_min);
      PROCESS_HR(hr);
      hr = m_pLiveLoadModelResponse->ComputeSupportDeflections(supportlist, currStg, m_LlmType, fetMz, optMinimize,
                                                      config_type,VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fz_min);
      PROCESS_HR(hr);
   }

   ILiveLoadConfiguration* null_config=NULL;

   IndexType size;
   supportlist->get_Count(&size);
   for (IndexType i=0; i<size; i++)
   {
      double rx, ry, rz;
      hr = fx_min->GetResult(i, &rx, &null_config);
      PROCESS_HR(hr);
      hr = fy_min->GetResult(i, &ry, &null_config);
      PROCESS_HR(hr);
      hr = fz_min->GetResult(i, &rz, &null_config);
      PROCESS_HR(hr);

      IDType spt;
      supportlist->get_Item(i, &spt);
      os<<(i==0?_T("Min"):_T("   "))<<std::setw(4)<<spt<<std::fixed<<std::setprecision(2)<<std::setw(13)<<rx<<std::setw(13)<<ry<<std::setw(13)<<rz<<C_R;
   }

   CComPtr<ILiveLoadModelResults> fx_max, fy_max, fz_max;
   if (is_force)
   {
      hr = m_pLiveLoadModelResponse->ComputeReactions(supportlist, currStg, m_LlmType, fetFx, optMaximize,
                                                      config_type,VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fx_max);
      PROCESS_HR(hr);
      hr = m_pLiveLoadModelResponse->ComputeReactions(supportlist, currStg, m_LlmType, fetFy, optMaximize,
                                                      config_type,VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fy_max);
      PROCESS_HR(hr);
      hr = m_pLiveLoadModelResponse->ComputeReactions(supportlist, currStg, m_LlmType, fetMz, optMaximize,
                                                      config_type,VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fz_max);
      PROCESS_HR(hr);
   }
   else
   {
      hr = m_pLiveLoadModelResponse->ComputeSupportDeflections(supportlist, currStg, m_LlmType, fetFx, optMaximize,
                                                      config_type,VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fx_max);
      PROCESS_HR(hr);
      hr = m_pLiveLoadModelResponse->ComputeSupportDeflections(supportlist, currStg, m_LlmType, fetFy, optMaximize,
                                                      config_type,VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fy_max);
      PROCESS_HR(hr);
      hr = m_pLiveLoadModelResponse->ComputeSupportDeflections(supportlist, currStg, m_LlmType, fetMz, optMaximize,
                                                      config_type,VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fz_max);
      PROCESS_HR(hr);
   }

   for (IndexType i=0; i<size; i++)
   {
      double rx, ry, rz;
      hr = fx_max->GetResult(i, &rx, &null_config);
      PROCESS_HR(hr);
      hr = fy_max->GetResult(i, &ry, &null_config);
      PROCESS_HR(hr);
      hr = fz_max->GetResult(i, &rz, &null_config);
      PROCESS_HR(hr);

      IDType spt;
      supportlist->get_Item(i, &spt);
      os<<(i==0?_T("Max"):_T("   "))<<std::setw(4)<<spt<<std::fixed<<std::setprecision(2)<<std::setw(13)<<rx<<std::setw(13)<<ry<<std::setw(13)<<rz<<C_R;
   }
}

