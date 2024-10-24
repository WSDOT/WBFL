// BasicLiveLoadDataSetBuilder.cpp: implementation of the BasicLiveLoadDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "BasicLiveLoadDataSetBuilder.h"

#include "DataSetUtils.h"
#include "GraphXYDisplayObjectImpl.h"
#include "Legend.h"

#include "LBAMViewerUtils.h"
#include <iomanip>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BasicLiveLoadDataSetBuilder::	BasicLiveLoadDataSetBuilder(LiveLoadModelType llmType, VehicleIndexType llIndex, 
                                                          llResponseType respType,
                                                          ILBAMModel* model, IBasicVehicularResponse* response):
m_LlmType(llmType),
m_LlIndex(llIndex),
m_Model(model),
m_Response(response),
m_RespType(respType)
{
   // set up initial vehicle placement
	HRESULT hr = m_Placement.CoCreateInstance(CLSID_LiveLoadConfiguration);
   ATLASSERT(SUCCEEDED(hr));

   InitializePlacement();
}

BasicLiveLoadDataSetBuilder::~BasicLiveLoadDataSetBuilder()
{
}

bool BasicLiveLoadDataSetBuilder::HasTruckPlacement()
{
   return m_IsTruck;
}

void BasicLiveLoadDataSetBuilder::GetTruckInfo(LiveLoadModelType* modelType, VehicleIndexType* vehicleIndex, ILiveLoadConfiguration** placement)
{
   ATLASSERT(m_IsTruck);

   *modelType = m_LlmType;
   *vehicleIndex = m_LlIndex;
   m_Placement.CopyTo(placement);
}

void BasicLiveLoadDataSetBuilder::BuildDataSets(IIDArray* poiList, IDblArray* locList, const CString& currStg,
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

CString BasicLiveLoadDataSetBuilder::GetDescription()
{
   CString tmp;
   tmp.Format(_T("Basic Live Load Response For %s %d"), LL_NAMES[m_LlmType], m_LlIndex);

   return tmp;
}

void BasicLiveLoadDataSetBuilder::BuildForceDataSets(IIDArray* poiList, IDblArray* locList, BSTR currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets)
{
   // create dataset
   auto dataset_p = std::make_shared<CGraphXyDataProvider>();

   // deal with legend
   auto fac = dataset_p->GetDataPointFactory();
   auto entry = std::dynamic_pointer_cast<iSymbolLegendEntry>(fac);

   entry->SetColor(color);
   entry->SetSymbolCharacterCode(198);
   entry->DoDrawLine(TRUE);

   CString tmp;
   tmp.Format(_T("%s %d"), LL_NAMES[m_LlmType], m_LlIndex);
   entry->SetName(tmp.LockBuffer());

   auto dataset = dataset_p->GetDataSet();

   CComPtr<ISectionResult3Ds> srs;

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

   m_Placement->put_ForceEffect(fet);

   HRESULT hr;
   if (is_force)
   {
      hr = m_Response->ComputeForces(poiList, currStg, roGlobal, m_Placement, &srs);
   }
   else
   {
      hr = m_Response->ComputeDeflections(poiList, currStg, m_Placement, &srs);
   }
   PROCESS_HR(hr);


   FillDataSet(locList, dataset, srs, currRt);
   dataSets->push_back( dataset_p );
}

void BasicLiveLoadDataSetBuilder::BuildStressDataSets(IIDArray* poiList, IDblArray* locList, BSTR currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets)
{
   HRESULT hr;
   IndexType poi_cnt;
   poiList->get_Count(&poi_cnt);

   CComPtr<ISectionStressResults> srs;

   // get results
	hr = m_Response->ComputeStresses(poiList, currStg, m_Placement, &srs);
   PROCESS_HR(hr);

   // loop over each stress point
   IndexType isp=0;
   bool loop=true;
   while(loop)
   {
      HRESULT hr;
      bool is_results = false;

      // create datasets for min and max responses
      auto dataset_p = std::make_shared<CGraphXyDataProvider>();

      // deal with legend
      auto fac = dataset_p->GetDataPointFactory();
      auto entry = std::dynamic_pointer_cast<iSymbolLegendEntry>(fac);

      entry->SetColor(color);
      entry->SetSymbolCharacterCode(DWORD(47+isp));
      entry->DoDrawLine(TRUE);

      CString tmp;
      tmp.Format(_T("%s %d - SP %d"), LL_NAMES[m_LlmType], m_LlIndex, isp);
      entry->SetName(tmp.LockBuffer());

      auto dataset = dataset_p->GetDataSet();

      for (IndexType ipoi=0; ipoi<poi_cnt; ipoi++)
      {
         double loc;
         locList->get_Item(ipoi, &loc);

         CComPtr<ISectionStressResult> sr;
         hr = srs->get_Item(ipoi, &sr);
         PROCESS_HR(hr);

         double val;

         // left side
         IndexType cnt;
         hr = sr->get_LeftCount(&cnt);
         PROCESS_HR(hr);

         if (isp<cnt)
         {
            // we have a left stress point
            is_results = true;

            hr = sr->GetLeftResult(isp, &val);

            dataset->Add(WBFL::Geometry::Point2d(loc,val));
         }

         // right side
         hr = sr->get_RightCount(&cnt);
         PROCESS_HR(hr);

         if (isp<cnt)
         {
            // we have a left stress point
            is_results = true;

            hr = sr->GetRightResult(isp, &val);

            dataset->Add(WBFL::Geometry::Point2d(loc,val));
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



void BasicLiveLoadDataSetBuilder::BuildReactionReport(IIDArray* supportlist, BSTR currStg,
                                       CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                       std::_tostream& os)
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

   os <<C_R<<" Vehicle Index = "<<m_LlIndex;

   // deal with vehicle type
   std::_tstring strvlc;
   VehicularLoadConfigurationType config_type = GetConfigType(m_RespType, strvlc);

   os<<" Config = "<<strvlc<< C_R;

   ForceEffectType fet;
   if (currRt==CLBAMViewerDoc::rtFx || currRt==CLBAMViewerDoc::rtDx)
   {
      fet = fetFx;
      if (is_force)
         os<<" Optimized for Axial Response"<< C_R;
      else
         os<<" Optimized for Horizontal Movement"<< C_R;
   }
   else if( currRt==CLBAMViewerDoc::rtFy || currRt==CLBAMViewerDoc::rtDy)
   {
      fet = fetFy;
      if (is_force)
         os<<" Optimized for Shear Response"<< C_R;
      else
         os<<" Optimized for Vertical Movement"<< C_R;
   }
   else if ( currRt==CLBAMViewerDoc::rtMz || currRt==CLBAMViewerDoc::rtRz)
   {
      fet = fetMz;
      if (is_force)
         os<<" Optimized for Moment Response"<< C_R;
      else
         os<<" Optimized for Rotational Movement"<< C_R;
   }
   else
   {
      ATLASSERT(0);
      return;
   }

   os<<_T(" Results for Stage: ")<<(const TCHAR*)CString(currStg)<<C_R<<C_R;

   if (is_force)
      os<<_T("Support        Rx         Ry           Mz")<<C_R;
   else
      os<<_T("Support        Dx         Dy           Rz")<<C_R;

   os<<_T("------- ------------ ------------ ------------")<<C_R;

   // clone current placement so we don't fire events when changing values
   CComPtr<ILiveLoadConfiguration> config;
   m_Placement->Clone(&config);

   config->put_ForceEffect(fet);

   // minimize
   config->put_Optimization(optMinimize);

   // get results
   CComPtr<IResult3Ds> results;
   if (is_force)
   {
      hr = m_Response->ComputeReactions(supportlist, currStg, config, &results);
   }
   else
   {
      hr = m_Response->ComputeSupportDeflections(supportlist, currStg, config, &results);
   }
   PROCESS_HR(hr);

   IndexType size;
   supportlist->get_Count(&size);
   for (IndexType i=0; i<size; i++)
   {
      double rx, ry, rz;
      CComPtr<IResult3D> result;

      hr = results->get_Item(i, &result);
      PROCESS_HR(hr);

      hr = result->GetResult(&rx, &ry, &rz);
      PROCESS_HR(hr);

      IDType spt;
      supportlist->get_Item(i, &spt);
      os<<(i==0?"Min":"   ")<<std::setw(4)<<spt<<std::fixed<<std::setprecision(2)<<std::setw(13)<<rx<<std::setw(13)<<ry<<std::setw(13)<<rz<<C_R;
   }

   // maximize
   config->put_Optimization(optMaximize);

   // get results
   results.Detach();
   if (is_force)
   {
      hr = m_Response->ComputeReactions(supportlist, currStg, config, &results);
   }
   else
   {
      hr = m_Response->ComputeSupportDeflections(supportlist, currStg, config, &results);
   }
   PROCESS_HR(hr);

   for (IndexType i=0; i<size; i++)
   {
      double rx, ry, rz;
      CComPtr<IResult3D> result;

      hr = results->get_Item(i, &result);
      PROCESS_HR(hr);

      hr = result->GetResult(&rx, &ry, &rz);
      PROCESS_HR(hr);

      IDType spt;
      supportlist->get_Item(i,&spt);
      os<<(i==0?"Max":"   ")<<std::setw(4)<<spt<<std::fixed<<std::setprecision(2)<<std::setw(13)<<rx<<std::setw(13)<<ry<<std::setw(13)<<rz<<C_R;
   }
}


void BasicLiveLoadDataSetBuilder::InitializePlacement()
{
   HRESULT hr;
   // assume we have a truck to view
   m_IsTruck = true;

   m_Placement->put_LiveLoadModel(m_LlmType);
   m_Placement->put_VehicleIndex(m_LlIndex);
   m_Placement->put_IsApplicable(VARIANT_TRUE);

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
      config_type = vlcLaneOnly;
      m_IsTruck = false;
      break;

   case llrSidewalkOnly:
      config_type = vlcSidewalkOnly;
      m_IsTruck = false;
      break;
   default:
      ATLASSERT(0);
   }

   m_Placement->put_VehicularLoadConfiguration(config_type);

   // get vehicular load
   CComPtr<IVehicularLoad> vehicular_load;
   GetVehicularLoad(m_Model, m_LlmType, m_LlIndex,  &vehicular_load);

   CComPtr<IAxles> axles;
   vehicular_load->get_Axles(&axles);
   AxleIndexType num_axles;
   axles->get_Count(&num_axles);

   if (num_axles<1)
   {
      m_IsTruck = false;
   }
   else
   {
      // put truck initially at middle of lbam
      CComPtr<ISpans> spans;
      hr = m_Model->get_Spans(&spans);
      ATLASSERT(SUCCEEDED(hr));

      double spans_length;
      hr = spans->get_Length(&spans_length);
      ATLASSERT(SUCCEEDED(hr));

      double location = spans_length/2.0;
      m_Placement->put_TruckPosition(location);
      m_Placement->put_TruckDirection(ltdForward);

      // set up initial variable axle spacing
      AxleIndexType var_spc_idx;
      vehicular_load->get_VariableAxle(&var_spc_idx);
      if ( var_spc_idx != FIXED_AXLE_TRUCK )
      {
         // truck has variable axle spacing - initialize spacing to minimum
         double min_var_spc;
         CComPtr<IAxle> var_axle;
         axles->get_Item(var_spc_idx, &var_axle);
         var_axle->get_Spacing(&min_var_spc);
         m_Placement->put_VariableSpacing(min_var_spc);
      }
   }
} 
