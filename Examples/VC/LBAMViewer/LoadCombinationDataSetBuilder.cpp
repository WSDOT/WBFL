// LoadCombinationDataSetBuilder.cpp: implementation of the LoadCombinationDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "LoadCombinationDataSetBuilder.h"

#include "DataSetUtils.h"
#include <iomanip>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// free function to fill dataset from combo result
void FillComboDataSet(ILoadCombinationSectionResults* results, IDblArray* locList, iDataSet2d* dataset, bool isShearForce, bool doFlip)
{
   HRESULT hr;
   CollectionIndexType res_size;
   hr = results->get_Count(&res_size);
   PROCESS_HR(hr);

   double flip = (doFlip? -1 : 1);

   CollectionIndexType locsiz;
   locList->get_Count(&locsiz);
   ATLASSERT(res_size==locsiz);
   for (CollectionIndexType ipoi=0; ipoi<res_size; ipoi++)
   {
      double left_result, right_result;
      ILoadCombinationResultConfiguration** ppDummy=NULL;
      hr = results->GetResult(ipoi, &left_result, ppDummy, &right_result, ppDummy);
      PROCESS_HR(hr);

      if (isShearForce)
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

      if (right_result!= flip * left_result)
      {
         CComPtr<IPoint2d> rpnt;
         hr = rpnt.CoCreateInstance(CLSID_Point2d);
         ATLASSERT(SUCCEEDED(hr));
         rpnt->put_X(loc);
         rpnt->put_Y(flip* right_result);
         dataset->Add(rpnt);
      }
   }
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LoadCombinationDataSetBuilder::LoadCombinationDataSetBuilder(BSTR loadCombination, ILoadCombinationResponse* response):
m_LoadCombination(loadCombination),
m_pLoadCombinationResponse(response),
m_IncludeLiveLoad(VARIANT_TRUE)
{

}

LoadCombinationDataSetBuilder::~LoadCombinationDataSetBuilder()
{

}

void LoadCombinationDataSetBuilder::BuildDataSets(IIDArray* poiList, IDblArray* locList, BSTR currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
{
   if (m_LoadCombination.Length()<=0)
      ATLASSERT(0);

   // check to see if cumulative results are requested. If so, we have to filter out internally generated
   // pois
   CComPtr<IIDArray> cumm_poi_list;
   CComPtr<IDblArray> cumm_loc_list;
   CComPtr<IIDArray> arr;
   CComPtr<IDblArray> ploc_list;
   if (summType==rsCumulative)
   {
      CollectionIndexType size;
      poiList->get_Count(&size);
      cumm_poi_list.CoCreateInstance(CLSID_IDArray);
      cumm_loc_list.CoCreateInstance(CLSID_DblArray);
      long new_size=0;
      for (CollectionIndexType ip=0; ip<size; ip++)
      {
         PoiIDType id;
         poiList->get_Item(ip,&id);
         if (id>=0)
         {
            cumm_poi_list->Add(id);
            double loc;
            locList->get_Item(ip, &loc);
            cumm_loc_list->Add(loc);
            new_size++;
         }
      }

      arr       = cumm_poi_list;
      ploc_list = cumm_loc_list;
   }
   else
   {
      arr       = poiList;
      ploc_list = locList;
   }

   if (currRt!=CLBAMViewerDoc::rtStress)
   {
      BuildForceDataSets(arr, ploc_list, currStg, currRt, summType,
                         color, dataSets);
   }
   else
   {
      BuildStressDataSets(arr, ploc_list, currStg, currRt, summType,
                          color, dataSets);
   }
}

void LoadCombinationDataSetBuilder::BuildForceDataSets(IIDArray* arr, IDblArray* locList, BSTR currStg,
                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
{
   HRESULT hr;


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

   for (long iopt=0; iopt<2; iopt++)
   {
      // first maximize
      CString str(m_LoadCombination);
      OptimizationType optimization;
      if (iopt==0)
      {
         optimization = optMaximize;
         str += " Max";
      }
      else
      {
         optimization = optMinimize;
         str += " Max";
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
      entry->put_SymbolCharacterCode(229);
      entry->put_DoDrawLine(TRUE);

      CComBSTR btmp(str);
      entry->put_Name(btmp);

      CComPtr<iDataSet2d> dataset;
      dataset_p->get_DataSet(&dataset);

      CComPtr<ILoadCombinationSectionResults> srs;

      bool do_flip;
      if (is_force)
      {
         do_flip = true;

         hr = m_pLoadCombinationResponse->ComputeForces(m_LoadCombination, arr, currStg, roGlobal, summType, 
                                                        fet, optimization, m_IncludeLiveLoad, VARIANT_TRUE, VARIANT_FALSE, 
                                                        &srs);
         PROCESS_HR(hr);
      }
      else
      {
         do_flip = false; // no sign change needed

         hr = m_pLoadCombinationResponse->ComputeDeflections(m_LoadCombination, arr, currStg, summType, 
                                                             fet, optimization, m_IncludeLiveLoad, 
                                                             VARIANT_TRUE, VARIANT_FALSE, &srs);
         PROCESS_HR(hr);
      }

      FillComboDataSet(srs, locList, dataset, currRt==CLBAMViewerDoc::rtFy, do_flip);

      dataSets->push_back(dataset_p.Detach());
   }
}

void LoadCombinationDataSetBuilder::BuildStressDataSets(IIDArray* arr, IDblArray* locList, BSTR currStg,
                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
{
   HRESULT hr;

   CollectionIndexType size;
   locList->get_Count(&size);

   if (m_LoadCombination.Length()>0)
   {
      ForceEffectType fet = fetMz;

      CComPtr<ILoadCombinationStressResults> srs;
      hr = m_pLoadCombinationResponse->ComputeStresses(m_LoadCombination, arr, currStg, 
                                                       summType, fet, optMaximize, VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &srs);
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
         entry->put_SymbolFontFace(_T("Wingdings2"));
         entry->put_SymbolCharacterCode(DWORD(116+isp));
         entry->put_DoDrawLine(TRUE);

         CString str;
         str.Format(_T("%s SP %d"), m_LoadCombination ,isp);
         CComBSTR btmp(str);
         entry->put_Name(btmp);

         CComPtr<iDataSet2d> dataset;
         dataset_p->get_DataSet(&dataset);

         for (CollectionIndexType ipoi=0; ipoi<size; ipoi++)
         {
            double loc;
            locList->get_Item(ipoi,&loc);

            CComPtr<IStressResult> left_res, right_res;
            hr = srs->GetResult(ipoi, &left_res, NULL, &right_res, NULL);
            PROCESS_HR(hr);

            double val;

            // left side
            CollectionIndexType cnt;
            hr = left_res->get_Count(&cnt);
            PROCESS_HR(hr);

            if (isp<cnt)
            {
               // we have a left stress point
               is_results = true;

               hr = left_res->GetResult(isp, &val);

               CComPtr<IPoint2d> pnt;
               hr = pnt.CoCreateInstance(CLSID_Point2d);
               ATLASSERT(SUCCEEDED(hr));
               pnt->put_X(loc);
               pnt->put_Y(val);
               dataset->Add(pnt);
            }

            // right side
            hr = right_res->get_Count(&cnt);
            PROCESS_HR(hr);

            if (isp<cnt)
            {
               // we have a left stress point
               is_results = true;

               hr = right_res->GetResult(isp, &val);

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
}


void LoadCombinationDataSetBuilder::BuildReactionReport(IIDArray* supportlist, BSTR currStg,
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
   
   os<<(is_force?_T("Reactions"):_T("Support Deflections"))<<_T(" for Load Combination ")<<(const TCHAR*)CString(m_LoadCombination)<<C_R;

   CString st;
   if (summType==rsCumulative)
      st = _T(" Cumulative");
   else
      st = _T(" Incremental");

   os<<(const TCHAR*)st<<_T(" results for Stage: ")<<(const TCHAR*)CString(currStg)<<C_R<<C_R;

   if (is_force)
      os<<_T("Support        Rx         Ry           Mz")<<C_R;
   else
      os<<_T("Support        Dx         Dy           Rz")<<C_R;
   os<<_T("------- ------------ ------------ ------------")<<C_R;

   // get results
   // Min
   CComPtr<ILoadCombinationResults> fx_min, fy_min, fz_min;
   if (is_force)
   {
      hr = m_pLoadCombinationResponse->ComputeReactions(m_LoadCombination, supportlist, currStg, summType, 
                                                        fetFx, optMinimize, VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fx_min);
      PROCESS_HR(hr);
      hr = m_pLoadCombinationResponse->ComputeReactions(m_LoadCombination, supportlist, currStg, summType, 
                                                        fetFy, optMinimize, VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fy_min);
      PROCESS_HR(hr);
      hr = m_pLoadCombinationResponse->ComputeReactions(m_LoadCombination, supportlist, currStg, summType, 
                                                        fetMz, optMinimize, VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fz_min);
      PROCESS_HR(hr);
   }
   else
   {
      hr = m_pLoadCombinationResponse->ComputeSupportDeflections(m_LoadCombination, supportlist, currStg, summType, 
                                                        fetFx, optMinimize, VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fx_min);
      PROCESS_HR(hr);
      hr = m_pLoadCombinationResponse->ComputeSupportDeflections(m_LoadCombination, supportlist, currStg, summType, 
                                                        fetFy, optMinimize, VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fy_min);
      PROCESS_HR(hr);
      hr = m_pLoadCombinationResponse->ComputeSupportDeflections(m_LoadCombination, supportlist, currStg, summType, 
                                                        fetMz, optMinimize, VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fz_min);
      PROCESS_HR(hr);
   }

   ILoadCombinationResultConfiguration* null_config=NULL;

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

   // Max
   CComPtr<ILoadCombinationResults> fx_max, fy_max, fz_max;
   if (is_force)
   {
      hr = m_pLoadCombinationResponse->ComputeReactions(m_LoadCombination, supportlist, currStg, summType, 
                                                        fetFx, optMaximize, VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fx_max);
      PROCESS_HR(hr);
      hr = m_pLoadCombinationResponse->ComputeReactions(m_LoadCombination, supportlist, currStg, summType, 
                                                        fetFy, optMaximize, VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fy_max);
      PROCESS_HR(hr);
      hr = m_pLoadCombinationResponse->ComputeReactions(m_LoadCombination, supportlist, currStg, summType, 
                                                        fetMz, optMaximize, VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fz_max);
      PROCESS_HR(hr);
   }
   else
   {
      hr = m_pLoadCombinationResponse->ComputeSupportDeflections(m_LoadCombination, supportlist, currStg, summType, 
                                                        fetFx, optMaximize, VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fx_max);
      PROCESS_HR(hr);
      hr = m_pLoadCombinationResponse->ComputeSupportDeflections(m_LoadCombination, supportlist, currStg, summType, 
                                                        fetFy, optMaximize, VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fy_max);
      PROCESS_HR(hr);
      hr = m_pLoadCombinationResponse->ComputeSupportDeflections(m_LoadCombination, supportlist, currStg, summType, 
                                                        fetMz, optMaximize, VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, &fz_max);
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

