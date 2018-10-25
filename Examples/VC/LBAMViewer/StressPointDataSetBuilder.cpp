// StressPointDataSetBuilder.cpp: implementation of the StressPointDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "StressPointDataSetBuilder.h"

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

StressPointDataSetBuilder::StressPointDataSetBuilder(SType type, IGetStressPoints* pGsp):
m_Type(type),
m_pStressPoints(pGsp)
{

}

StressPointDataSetBuilder::~StressPointDataSetBuilder()
{

}

void StressPointDataSetBuilder::BuildDataSets(ILongArray* poiList, IDblArray* locList, BSTR currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
{
   HRESULT hr;
   CollectionIndexType size;
   locList->get_Count(&size);

   if (size>0)
   {

      // loop over each stress point
      CollectionIndexType isp=0;
      bool loop=true;
      while(loop)
      {
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
         entry->put_SymbolCharacterCode(115);
         entry->put_DoDrawLine(TRUE);

         CString str;
         if (m_Type == stSa)
         {
            str.Format("Sa at Sp %d", isp);
         }
         else if (m_Type==stSm)
         {
            str.Format("Sm at Sp %d", isp);
         }

         CComBSTR btmp(str);
         entry->put_Name(btmp);

         CComPtr<iDataSet2d> dataset;
         dataset_p->get_DataSet(&dataset);

         for (CollectionIndexType ipoi=0; ipoi<size; ipoi++)
         {
            double loc;
            locList->get_Item(ipoi,&loc);
            PoiIDType poi_id;
            poiList->get_Item(ipoi,&poi_id);

            CComPtr<IStressPoints> left_sps, right_sps;
            hr = m_pStressPoints->GetStressPointsAtPOI(poi_id, currStg, &left_sps, &right_sps);

            // left side
            if (left_sps!=NULL)
            {
               CollectionIndexType cnt;
               hr = left_sps->get_Count(&cnt);
               PROCESS_HR(hr);

               if (isp<cnt)
               {
                  // we have a left stress point
                  is_results = true;

                  CComPtr<IStressPoint> psp;
                  hr = left_sps->get_Item(isp, &psp);

                  double val = GetVal(psp);

                  CComPtr<IPoint2d> pnt;
                  hr = pnt.CoCreateInstance(CLSID_Point2d);
                  ATLASSERT(SUCCEEDED(hr));
                  pnt->put_X(loc);
                  pnt->put_Y(val);
                  dataset->Add(pnt);
               }
            }

            // right side
            if (right_sps!=NULL)
            {
               CollectionIndexType cnt;
               hr = right_sps->get_Count(&cnt);
               PROCESS_HR(hr);

               if (isp<cnt)
               {
                  // we have a right stress point
                  is_results = true;

                  CComPtr<IStressPoint> psp;
                  hr = right_sps->get_Item(isp, &psp);

                  double val = GetVal(psp);

                  CComPtr<IPoint2d> pnt;
                  hr = pnt.CoCreateInstance(CLSID_Point2d);
                  ATLASSERT(SUCCEEDED(hr));
                  pnt->put_X(loc);
                  pnt->put_Y(val);
                  dataset->Add(pnt);
               }
            }
         }

         isp++;
         // for now, limit the number of stress points to the max number of symbol types
         if (!is_results || isp>dpstLastDefault)
         {
            ATLASSERT(isp<dpstLastDefault); // man, that's a  lot of stress points!
            loop=false;
         }
         else
         {
            dataSets->push_back(dataset_p.Detach());
         }
      }
   }
}

double StressPointDataSetBuilder::GetVal(IStressPoint* pcs)
{
   HRESULT hr;
   double val;

   switch (m_Type)
   {
   case stSa:
      hr = pcs->get_Sa(&val);
      break;
   case stSm:
      hr = pcs->get_Sm(&val);
      break;
   default:
      ATLASSERT(0);
      break;
   }

   PROCESS_HR(hr);

   return val;
}


