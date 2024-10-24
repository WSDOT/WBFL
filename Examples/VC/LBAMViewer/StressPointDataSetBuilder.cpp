// StressPointDataSetBuilder.cpp: implementation of the StressPointDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "StressPointDataSetBuilder.h"

#include "DataSetUtils.h"
#include <iomanip>

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

StressPointDataSetBuilder::StressPointDataSetBuilder(SType type, IGetStressPoints* pGsp):
m_Type(type),
m_pStressPoints(pGsp)
{

}

StressPointDataSetBuilder::~StressPointDataSetBuilder()
{

}

void StressPointDataSetBuilder::BuildDataSets(IIDArray* poiList, IDblArray* locList, const CString& currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets)
{
   HRESULT hr;
   IndexType size;
   locList->get_Count(&size);

   if (size>0)
   {

      // loop over each stress point
      IndexType isp=0;
      bool loop=true;
      while(loop)
      {
         bool is_results = false;

         // create dataset 
         auto dataset_p = std::make_shared<CGraphXyDataProvider>();

         // deal with legend
         auto fac = dataset_p->GetDataPointFactory();
         auto entry = std::dynamic_pointer_cast<iSymbolLegendEntry>(fac);

         entry->SetColor(color);
         entry->SetSymbolCharacterCode(115);
         entry->DoDrawLine(TRUE);

         CString str;
         if (m_Type == stSa)
         {
            str.Format(_T("Sa at Sp %d"), isp);
         }
         else if (m_Type==stSm)
         {
            str.Format(_T("Sm at Sp %d"), isp);
         }

         entry->SetName(str.LockBuffer());

         auto dataset = dataset_p->GetDataSet();

         for (IndexType ipoi=0; ipoi<size; ipoi++)
         {
            double loc;
            locList->get_Item(ipoi,&loc);
            PoiIDType poi_id;
            poiList->get_Item(ipoi,&poi_id);

            CComPtr<IStressPoints> left_sps, right_sps;
            hr = m_pStressPoints->GetStressPointsAtPOI(poi_id, CComBSTR(currStg), &left_sps, &right_sps);

            // left side
            if (left_sps!=NULL)
            {
               IndexType cnt;
               hr = left_sps->get_Count(&cnt);
               PROCESS_HR(hr);

               if (isp<cnt)
               {
                  // we have a left stress point
                  is_results = true;

                  CComPtr<IStressPoint> psp;
                  hr = left_sps->get_Item(isp, &psp);

                  double val = GetVal(psp);

                  WBFL::Geometry::Point2d pnt(loc, val);
                  dataset->Add(pnt);
               }
            }

            // right side
            if (right_sps!=NULL)
            {
               IndexType cnt;
               hr = right_sps->get_Count(&cnt);
               PROCESS_HR(hr);

               if (isp<cnt)
               {
                  // we have a right stress point
                  is_results = true;

                  CComPtr<IStressPoint> psp;
                  hr = right_sps->get_Item(isp, &psp);

                  double val = GetVal(psp);

                  WBFL::Geometry::Point2d pnt(loc, val);
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
            dataSets->push_back(dataset_p);
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


