// LiveLoadModelDataSetBuilder.cpp: implementation of the LiveLoadModelDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "LiveLoadModelDataSetBuilder.h"
#include <iomanip>
#include "LBAMViewerUtils.h"

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


void LiveLoadModelDataSetBuilder::BuildDataSets(ILongArray* poiList, IDblArray* locList, BSTR currStg,
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

CString LiveLoadModelDataSetBuilder::GetDescription()
{
   CString tmp;
   tmp.Format("Enveloped Live Load Model Response For %s ", LL_NAMES[m_LlmType]);

   return tmp;
}


void LiveLoadModelDataSetBuilder::BuildForceDataSets(ILongArray* poiList, IDblArray* locList, BSTR currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
{

   HRESULT hr;

   // deal with vehicle type
   std::string strvlc;
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

   CollectionIndexType poi_cnt;
   poiList->get_Count(&poi_cnt);

   double flip = is_force ? -1.0 : 1.0;

   for (Uint32 iopt=0; iopt<2; iopt++)
   {
      CString str;
      // first maximize
      OptimizationType optimization;
      if (iopt==0)
      {
         optimization = optMaximize;
         str.Format("LL Env %s Max", LL_NAMES[m_LlmType]);
      }
      else
      {
         optimization = optMinimize;
         str.Format("LL Env %s Min", LL_NAMES[m_LlmType]);
      }

      // create dataset 
      CComPtr<iGraphXyDataProvider> dataset_p;
      hr = dataset_p.CoCreateInstance(CLSID_GraphXyDataProvider);
      ATLASSERT(SUCCEEDED(hr));

      // deal with legend
      CComPtr<iDataPointFactory> fac;
      dataset_p->get_DataPointFactory(&fac);
      CComQIPtr<iSymbolLegendEntry> entry(fac);

      entry->put_Color(color);
      entry->put_SymbolFontFace("Webdings");
      entry->put_SymbolCharacterCode(104);
      entry->put_DoDrawLine(TRUE);

      CComBSTR btmp(str);
      entry->put_Name(btmp);

      CComPtr<iDataSet2d> dataset;
      dataset_p->get_DataSet(&dataset);

      CComPtr<ILiveLoadModelSectionResults> results;

      // get results
      if (is_force)
      {
		   hr = m_pLiveLoadModelResponse->ComputeForces(poiList, currStg, m_LlmType, roGlobal,
										                   fet, optimization, config_type, VARIANT_TRUE, VARIANT_FALSE,
                                                 VARIANT_FALSE, &results);
      }
      else
      {
		   hr = m_pLiveLoadModelResponse->ComputeDeflections(poiList, currStg, m_LlmType,
										                   fet, optimization, config_type, VARIANT_TRUE, VARIANT_FALSE,
                                                 VARIANT_FALSE, &results);
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

         if (currRt==CLBAMViewerDoc::rtFy )
         {
            // convert shear force values to beam diagram coordinates
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

         right_result*=flip;
         if (right_result!= left_result)
         {
            CComPtr<IPoint2d> rpnt;
            hr = rpnt.CoCreateInstance(CLSID_Point2d);
            ATLASSERT(SUCCEEDED(hr));
            rpnt->put_X(loc);
            rpnt->put_Y(right_result);
            dataset->Add(rpnt);
         }
      }

      dataSets->push_back( dataset_p.Detach());
   }
}

void LiveLoadModelDataSetBuilder::BuildStressDataSets(ILongArray* poiList, IDblArray* locList, BSTR currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
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

   CollectionIndexType poi_cnt;
   poiList->get_Count(&poi_cnt);

   CComPtr<ILiveLoadModelStressResults> results;

   // get results
#pragma Reminder("Stresses are only computed for maximized Moment. Need to come up with GUI to change this")
	hr = m_pLiveLoadModelResponse->ComputeStresses(poiList, currStg, m_LlmType, 
										                fetMz, optMaximize, config_type, VARIANT_TRUE, dftNone, VARIANT_FALSE,
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
      entry->put_SymbolFontFace("Wingdings");
      entry->put_SymbolCharacterCode(128+isp);
      entry->put_DoDrawLine(TRUE);

      CString str;
      str.Format("LL Env %s SP %d", LL_NAMES[m_LlmType],isp);
      CComBSTR btmp(str);
      entry->put_Name(btmp);

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

void LiveLoadModelDataSetBuilder::BuildReactionReport(ILongArray* supportlist, BSTR currStg,
                                  CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                  std::ostream& os)
{
   HRESULT hr;
   os<<C_R<<"------------------------------------------"<<C_R;

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


   os<<(is_force?"Reactions":"Support Deflections")<<" for Live Load Model: ";
   switch (m_LlmType)
   {
   case lltNone:
      os <<"No Truck";
      break;
   case lltDeflection:
      os <<"Deflection Truck";
      break;
   case lltDesign:
      os <<"Design Truck";
      break;
   case lltPedestrian:
      os <<"Pedestrian Truck";
      break;
   case lltFatigue:
      os <<"Fatigue Truck";
      break;
   case lltPermit:
      os <<"Permit Truck";
      break;
   case lltSpecial:
      os <<"Special Truck";
      break;
   default:
      _ASSERT(0);
   }

   // deal with vehicle type
   std::string strvlc;
   VehicularLoadConfigurationType config_type = GetConfigType(m_RespType, strvlc);

   os<<" - "<<strvlc<< C_R;

   os<<" Results for Stage: "<<(const char*)CString(currStg)<<C_R<<C_R;

   if (is_force)
      os<<"Support        Rx         Ry           Mz"<<C_R;
   else
      os<<"Support        Dx         Dy           Rz"<<C_R;
   os<<"------- ------------ ------------ ------------"<<C_R;

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

      long spt;
      supportlist->get_Item(i, &spt);
      os<<(i==0?"Min":"   ")<<std::setw(4)<<spt<<std::fixed<<std::setprecision(2)<<std::setw(13)<<rx<<std::setw(13)<<ry<<std::setw(13)<<rz<<C_R;
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

   for (CollectionIndexType i=0; i<size; i++)
   {
      double rx, ry, rz;
      hr = fx_max->GetResult(i, &rx, &null_config);
      PROCESS_HR(hr);
      hr = fy_max->GetResult(i, &ry, &null_config);
      PROCESS_HR(hr);
      hr = fz_max->GetResult(i, &rz, &null_config);
      PROCESS_HR(hr);

      long spt;
      supportlist->get_Item(i, &spt);
      os<<(i==0?"Max":"   ")<<std::setw(4)<<spt<<std::fixed<<std::setprecision(2)<<std::setw(13)<<rx<<std::setw(13)<<ry<<std::setw(13)<<rz<<C_R;
   }
}

