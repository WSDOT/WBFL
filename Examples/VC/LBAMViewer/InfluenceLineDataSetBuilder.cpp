// InfluenceLineDataSetBuilder.cpp: implementation of the InfluenceLineDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "InfluenceLineDataSetBuilder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

InfluenceLineDataSetBuilder::InfluenceLineDataSetBuilder(long poiID, IInfluenceLineResponse* response):
m_PoiId(poiID),
m_pInfluenceLineResponse(response)
{

}

InfluenceLineDataSetBuilder::~InfluenceLineDataSetBuilder()
{
}

void InfluenceLineDataSetBuilder::BuildDataSets(ILongArray* poiList, IDblArray* locList, BSTR currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
{
   HRESULT hr;

   ForceEffectType fet;
   if (currRt==CLBAMViewerDoc::rtFx || currRt==CLBAMViewerDoc::rtDx)
      fet = fetFx;
   else if( currRt==CLBAMViewerDoc::rtFy || currRt==CLBAMViewerDoc::rtDy)
      fet = fetFy;
   else if ( currRt==CLBAMViewerDoc::rtMz || currRt==CLBAMViewerDoc::rtRz)
      fet = fetMz;
   else if ( currRt==CLBAMViewerDoc::rtStress)
   {
      ::AfxMessageBox("Stress Results Not Available for Influence Lines");
      return;
   }
   else
   {
      ATLASSERT(0);
      return;
   }

   CComPtr<IInfluenceLine> lft_infl, rgt_infl;

   if (currRt==CLBAMViewerDoc::rtFx || currRt==CLBAMViewerDoc::rtFy || currRt==CLBAMViewerDoc::rtMz)
   {
      // forces
      hr = m_pInfluenceLineResponse->ComputeForceInfluenceLine(m_PoiId, currStg, fet, roGlobal, &lft_infl, &rgt_infl);
   }
   else  if (currRt==CLBAMViewerDoc::rtDx || currRt==CLBAMViewerDoc::rtDy || currRt==CLBAMViewerDoc::rtRz)
   {
      // deflections
      hr = m_pInfluenceLineResponse->ComputeDeflectionInfluenceLine(m_PoiId, currStg, fet, &lft_infl, &rgt_infl);
   }
   PROCESS_HR(hr);

   bool do_symbols = rgt_infl!=NULL;

   if (lft_infl!=NULL)
   {
      // create dataset 
      CComPtr<iGraphXyDataProvider> dataset_p;
      hr = dataset_p.CoCreateInstance(CLSID_GraphXyDataProvider);
      ATLASSERT(SUCCEEDED(hr));

      // deal with legend
      CComPtr<iDataPointFactory> fac;
      dataset_p->get_DataPointFactory(&fac);
      CComQIPtr<iSymbolLegendEntry> entry(fac);

      entry->put_Color(color);
      entry->put_SymbolCharacterCode(233);
      entry->put_DoDrawLine(TRUE);

      CComBSTR btmp("Influence - Rgt");
      entry->put_Name(btmp);

      CComPtr<iDataSet2d> dataset;
      dataset_p->get_DataSet(&dataset);

      // fill up data set
      CollectionIndexType cnt;
      InfluenceSideType side = ilsBoth;

      hr = lft_infl->get_Count(side, &cnt);
      PROCESS_HR(hr);
      for (CollectionIndexType ii=0; ii<cnt; ii++)
      {
         double value, location;
         InfluenceLocationType itype;
         hr = lft_infl->Item(ii, side, &value, &itype, &location);
         PROCESS_HR(hr);

         if (currRt==CLBAMViewerDoc::rtFy)
         {
            // Convert shear forces to beam diagram coordinates
            value *= -1;
         }

         CComPtr<IPoint2d> pnt;
         hr = pnt.CoCreateInstance(CLSID_Point2d);
         PROCESS_HR(hr);

         pnt->put_X(location);
         pnt->put_Y(value);

         dataset->Add(pnt);
      }

      dataSets->push_back( dataset_p.Detach());
   }
   else
   {
      ATLASSERT(0);
      return;
   }


   if (rgt_infl!=NULL)
   {
      // create dataset 
      CComPtr<iGraphXyDataProvider> dataset_p;
      hr = dataset_p.CoCreateInstance(CLSID_GraphXyDataProvider);
      ATLASSERT(SUCCEEDED(hr));

      // deal with legend
      CComPtr<iDataPointFactory> fac;
      dataset_p->get_DataPointFactory(&fac);
      CComQIPtr<iSymbolLegendEntry> entry(fac);

      entry->put_Color(color);
      entry->put_SymbolCharacterCode(249);
      entry->put_DoDrawLine(TRUE);

      CComBSTR btmp("Influence - Lft");
      entry->put_Name(btmp);

      CComPtr<iDataSet2d> dataset;
      dataset_p->get_DataSet(&dataset);

      // fill up data set
      CollectionIndexType cnt;
      InfluenceSideType side = ilsBoth;

      hr = rgt_infl->get_Count(side, &cnt);
      PROCESS_HR(hr);
      for (CollectionIndexType ii=0; ii<cnt; ii++)
      {
         double value, location;
         InfluenceLocationType itype;
         hr = rgt_infl->Item(ii, side, &value, &itype, &location);
         PROCESS_HR(hr);

         if (currRt==CLBAMViewerDoc::rtFx || currRt==CLBAMViewerDoc::rtMz)
         {
            // convert to beam coordinates
            value *= -1;
         }

         CComPtr<IPoint2d> pnt;
         hr = pnt.CoCreateInstance(CLSID_Point2d);
         PROCESS_HR(hr);

         pnt->put_X(location);
         pnt->put_Y(value);

         dataset->Add(pnt);
      }

      dataSets->push_back( dataset_p.Detach());
   }

}
