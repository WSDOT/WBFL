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
                                           CLBAMViewerDoc::ResponseType responseType, ResultsSummationType summType,
                                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
{
   HRESULT hr;

   ForceEffectType fet;
   if (responseType==CLBAMViewerDoc::rtFx || responseType==CLBAMViewerDoc::rtDx)
      fet = fetFx;
   else if( responseType==CLBAMViewerDoc::rtFy || responseType==CLBAMViewerDoc::rtDy)
      fet = fetFy;
   else if ( responseType==CLBAMViewerDoc::rtMz || responseType==CLBAMViewerDoc::rtRz)
      fet = fetMz;
   else if ( responseType==CLBAMViewerDoc::rtStress)
   {
      ::AfxMessageBox("Stress Results Not Available for Influence Lines");
      return;
   }
   else
   {
      ATLASSERT(0);
      return;
   }

   CComPtr<IInfluenceLine> left_face_influence_line, right_face_influence_line;

   if (responseType==CLBAMViewerDoc::rtFx || responseType==CLBAMViewerDoc::rtFy || responseType==CLBAMViewerDoc::rtMz)
   {
      // forces
      hr = m_pInfluenceLineResponse->ComputeForceInfluenceLine(m_PoiId, currStg, fet, roGlobal, &left_face_influence_line, &right_face_influence_line);
   }
   else  if (responseType==CLBAMViewerDoc::rtDx || responseType==CLBAMViewerDoc::rtDy || responseType==CLBAMViewerDoc::rtRz)
   {
      // deflections
      hr = m_pInfluenceLineResponse->ComputeDeflectionInfluenceLine(m_PoiId, currStg, fet, &left_face_influence_line, &right_face_influence_line);
   }
   PROCESS_HR(hr);

   bool do_symbols = right_face_influence_line!=NULL;

   if ( left_face_influence_line )
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

      CComBSTR btmp("Influence - Left Face");
      entry->put_Name(btmp);

      CComPtr<iDataSet2d> dataset;
      dataset_p->get_DataSet(&dataset);

      // fill up data set
      CollectionIndexType cnt;
      InfluenceSideType side = ilsBoth;

      hr = left_face_influence_line->get_Count(side, &cnt);
      PROCESS_HR(hr);
      for (CollectionIndexType ii=0; ii<cnt; ii++)
      {
         double value, location;
         InfluenceLocationType itype;
         hr = left_face_influence_line->Item(ii, side, &value, &itype, &location);
         PROCESS_HR(hr);

         //if (responseType==CLBAMViewerDoc::rtFy)
         //{
         //   // Convert shear forces to beam diagram coordinates
         //   value *= -1;
         //}

         CComPtr<IPoint2d> pnt;
         hr = pnt.CoCreateInstance(CLSID_Point2d);
         PROCESS_HR(hr);

         pnt->put_X(location);
         pnt->put_Y(value);

         dataset->Add(pnt);
      }

      dataSets->push_back( dataset_p.Detach());
   }
   //else
   //{
   //   ATLASSERT(0);
   //   return;
   //}


   if ( right_face_influence_line )
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

      CComBSTR btmp("Influence - Right Face");
      entry->put_Name(btmp);

      CComPtr<iDataSet2d> dataset;
      dataset_p->get_DataSet(&dataset);

      // fill up data set
      CollectionIndexType cnt;
      InfluenceSideType side = ilsBoth;

      hr = right_face_influence_line->get_Count(side, &cnt);
      PROCESS_HR(hr);
      for (CollectionIndexType ii=0; ii<cnt; ii++)
      {
         double value, location;
         InfluenceLocationType itype;
         hr = right_face_influence_line->Item(ii, side, &value, &itype, &location);
         PROCESS_HR(hr);

         //if (responseType==CLBAMViewerDoc::rtFx || responseType==CLBAMViewerDoc::rtMz)
         //{
         //   // convert to beam coordinates
         //   value *= -1;
         //}

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
