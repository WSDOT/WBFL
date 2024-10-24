// InfluenceLineDataSetBuilder.cpp: implementation of the InfluenceLineDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "InfluenceLineDataSetBuilder.h"

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

InfluenceLineDataSetBuilder::InfluenceLineDataSetBuilder(PoiIDType poiID, IInfluenceLineResponse* response):
m_PoiId(poiID),
m_pInfluenceLineResponse(response)
{

}

InfluenceLineDataSetBuilder::~InfluenceLineDataSetBuilder()
{
}

void InfluenceLineDataSetBuilder::BuildDataSets(IIDArray* poiList, IDblArray* locList, const CString& currStg,
                                           CLBAMViewerDoc::ResponseType responseType, ResultsSummationType summType,
                                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets)
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
      ::AfxMessageBox(_T("Stress Results Not Available for Influence Lines"));
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
      hr = m_pInfluenceLineResponse->ComputeForceInfluenceLine(m_PoiId, CComBSTR(currStg), fet, roGlobal, &left_face_influence_line, &right_face_influence_line);
   }
   else  if (responseType==CLBAMViewerDoc::rtDx || responseType==CLBAMViewerDoc::rtDy || responseType==CLBAMViewerDoc::rtRz)
   {
      // deflections
      hr = m_pInfluenceLineResponse->ComputeDeflectionInfluenceLine(m_PoiId, CComBSTR(currStg), fet, &left_face_influence_line, &right_face_influence_line);
   }
   PROCESS_HR(hr);

   bool do_symbols = right_face_influence_line!=NULL;

   if ( left_face_influence_line )
   {
      // create dataset 
      auto dataset_p = std::make_shared<CGraphXyDataProvider>();

      // deal with legend
      auto fac = dataset_p->GetDataPointFactory();
      auto entry = std::dynamic_pointer_cast<iSymbolLegendEntry>(fac);

      entry->SetColor(color);
      entry->SetSymbolCharacterCode(249);
      entry->DoDrawLine(TRUE);

      entry->SetName(_T("Influence - Left Face"));

      auto dataset = dataset_p->GetDataSet();

      // fill up data set
      IndexType cnt;
      InfluenceSideType side = ilsBoth;

      hr = left_face_influence_line->get_Count(side, &cnt);
      PROCESS_HR(hr);
      for (IndexType ii=0; ii<cnt; ii++)
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

         WBFL::Geometry::Point2d pnt(location, value);

         dataset->Add(pnt);
      }

      dataSets->push_back( dataset_p );
   }
   //else
   //{
   //   ATLASSERT(0);
   //   return;
   //}


   if ( right_face_influence_line )
   {
      // create dataset 
      auto dataset_p = std::make_shared<CGraphXyDataProvider>();

      // deal with legend
      auto fac = dataset_p->GetDataPointFactory();
      auto entry = std::dynamic_pointer_cast<iSymbolLegendEntry>(fac);

      entry->SetColor(color);
      entry->SetSymbolCharacterCode(233);
      entry->DoDrawLine(TRUE);

      entry->SetName(_T("Influence - Right Face"));

      auto dataset = dataset_p->GetDataSet();

      // fill up data set
      IndexType cnt;
      InfluenceSideType side = ilsBoth;

      hr = right_face_influence_line->get_Count(side, &cnt);
      PROCESS_HR(hr);
      for (IndexType ii=0; ii<cnt; ii++)
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
         WBFL::Geometry::Point2d pnt(location, value);
         dataset->Add(pnt);
      }

      dataSets->push_back(dataset_p);
   }

}
