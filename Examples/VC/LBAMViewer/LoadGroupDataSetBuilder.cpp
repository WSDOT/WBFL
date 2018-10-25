// LoadGroupDataSetBuilder.cpp: implementation of the LoadGroupDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "LoadGroupDataSetBuilder.h"

#include "DataSetUtils.h"
#include <iomanip>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LoadGroupDataSetBuilder::LoadGroupDataSetBuilder(BSTR loadGroup, ILoadGroupResponse* response):
m_LoadGroup(loadGroup),
m_pLoadGroupResponse(response)
{

}

LoadGroupDataSetBuilder::~LoadGroupDataSetBuilder()
{

}

void LoadGroupDataSetBuilder::BuildDataSets(ILongArray* poiList, IDblArray* locList, BSTR currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
{
   // check to see if cumulative results are requested. If so, we have to filter out internally generated
   // pois
   CComPtr<ILongArray> cumm_poi_list;
   CComPtr<IDblArray> cumm_loc_list;
   CComPtr<IDblArray> ploc_list;
   CComPtr<ILongArray> arr;
   if (summType==rsCumulative)
   {
      CollectionIndexType size;
      poiList->get_Count(&size);
      cumm_poi_list.CoCreateInstance(CLSID_LongArray);
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
            locList->get_Item(ip,&loc);
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


void LoadGroupDataSetBuilder::BuildForceDataSets(ILongArray* arr, IDblArray* locList, BSTR currStg,
                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
{
   HRESULT hr;
   // create dataset 
   CComPtr<iGraphXyDataProvider> dataset_p;
   hr = dataset_p.CoCreateInstance(CLSID_GraphXyDataProvider);
   ATLASSERT(SUCCEEDED(hr));

   // deal with legend
   CComPtr<iDataPointFactory> fac;
   dataset_p->get_DataPointFactory(&fac);
   CComQIPtr<iSymbolLegendEntry> entry(fac);

   entry->put_Color(color);
   entry->put_SymbolCharacterCode(204);
   entry->put_DoDrawLine(TRUE);

   entry->put_Name(m_LoadGroup);

   CComPtr<iDataSet2d> dataset;
   dataset_p->get_DataSet(&dataset);

   CComPtr<ISectionResult3Ds> srs;

   if (m_LoadGroup.Length()>0)
   {
      if (currRt==CLBAMViewerDoc::rtFx || currRt==CLBAMViewerDoc::rtFy || currRt==CLBAMViewerDoc::rtMz)
      {
         hr = m_pLoadGroupResponse->ComputeForces(m_LoadGroup, arr, currStg, roGlobal, summType, &srs);
         PROCESS_HR(hr);
      }
      else
      {
         hr = m_pLoadGroupResponse->ComputeDeflections(m_LoadGroup, arr, currStg, summType,&srs);
         PROCESS_HR(hr);
      }

      FillDataSet(locList, dataset, srs, currRt);

      dataSets->push_back(dataset_p.Detach());
   }
   else
      ATLASSERT(0); 
}

void LoadGroupDataSetBuilder::BuildStressDataSets(ILongArray* arr, IDblArray* locList, BSTR currStg,
                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
{
   HRESULT hr;

   CollectionIndexType size;
   locList->get_Count(&size);

   if (m_LoadGroup.Length()>0)
   {
      CComPtr<ISectionStressResults> srs;
      hr = m_pLoadGroupResponse->ComputeStresses(m_LoadGroup, arr, currStg, summType, &srs);
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
         entry->put_SymbolCharacterCode(49+isp);
         entry->put_DoDrawLine(TRUE);

         entry->put_Name(m_LoadGroup);

         CComPtr<iDataSet2d> dataset;
         dataset_p->get_DataSet(&dataset);

         for (CollectionIndexType ipoi=0; ipoi<size; ipoi++)
         {
            double loc;
            locList->get_Item(ipoi,&loc);

            CComPtr<ISectionStressResult> sr;
            hr = srs->get_Item(ipoi, &sr);
            PROCESS_HR(hr);

            double val;

            // left side
            CollectionIndexType cnt;
            hr = sr->get_LeftCount(&cnt);
            PROCESS_HR(hr);

            if (isp<cnt)
            {
               // we have a left stress point
               is_results = true;

               hr = sr->GetLeftResult(isp, &val);

               CComPtr<IPoint2d> pnt;
               hr = pnt.CoCreateInstance(CLSID_Point2d);
               ATLASSERT(SUCCEEDED(hr));
               pnt->put_X(loc);
               pnt->put_Y(val);
               dataset->Add(pnt);
            }

            // right side
            hr = sr->get_RightCount(&cnt);
            PROCESS_HR(hr);

            if (isp<cnt)
            {
               // we have a left stress point
               is_results = true;

               hr = sr->GetRightResult(isp, &val);

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


void LoadGroupDataSetBuilder::BuildReactionReport(ILongArray* supportlist, BSTR currStg,
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
      case CLBAMViewerDoc::rtStress:
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

   os<<(is_force?"Reactions":"Support Deflections")<<" for Load Group "<<(const char*)CString(m_LoadGroup)<<C_R;

   CString st;
   if (summType==rsCumulative)
      st = " Cumulative";
   else
      st = " Incremental";

   os<<(const char*)st<<" results for Stage: "<<(const char*)CString(currStg)<<C_R<<C_R;

   if (is_force)
      os<<"Support        Rx         Ry           Mz"<<C_R;
   else
      os<<"Support        Dx         Dy           Rz"<<C_R;

   os<<"------- ------------ ------------ ------------"<<C_R;

   // get results
   CComPtr<IResult3Ds> srs;
   if (is_force)
   {
      hr = m_pLoadGroupResponse->ComputeReactions(m_LoadGroup, supportlist, currStg, summType, &srs);
   }
   else
   {
      hr = m_pLoadGroupResponse->ComputeSupportDeflections(m_LoadGroup, supportlist, currStg, summType, &srs);
   }

   PROCESS_HR(hr);

   CollectionIndexType size;
   supportlist->get_Count(&size);
   for (CollectionIndexType i=0; i<size; i++)
   {
      CComPtr<IResult3D> sr;
      hr = srs->get_Item(i, &sr);
      PROCESS_HR(hr);
      double fx, fy, fz;
      hr = sr->GetResult(&fx, &fy, &fz);
      PROCESS_HR(hr);

      long sup;
      supportlist->get_Item(i,&sup);
      os<<std::setw(7)<<sup<<std::fixed<<std::setprecision(2)<<std::setw(13)<<fx<<std::setw(13)<<fy<<std::setw(13)<<fz<<C_R;

   }

}
