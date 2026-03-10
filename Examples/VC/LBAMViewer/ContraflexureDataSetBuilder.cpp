// ContraflexureDataSetBuilder.cpp: implementation of the ContraflexureDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "ContraflexureDataSetBuilder.h"
#include "GraphXYDisplayObjectImpl.h"
#include "LegendDisplayObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ContraflexureDataSetBuilder::ContraflexureDataSetBuilder(IContraflexureResponse* response):
m_pContraflexureResponse(response)
{

}

ContraflexureDataSetBuilder::~ContraflexureDataSetBuilder()
{
}

void ContraflexureDataSetBuilder::BuildDataSets(IIDArray* poiList, IDblArray* locList, const CString& currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets)
{
   HRESULT hr;
   // create dataset 
   auto dataset_p = std::make_shared<CGraphXyDataProvider>();

   // deal with legend
   auto fac = dataset_p->GetDataPointFactory();
   auto entry = std::dynamic_pointer_cast<iLegendEntry>(fac);

   entry->SetColor(color);
   entry->SetSymbolCharacterCode(64);
   entry->DrawLine(TRUE);

   entry->SetName(_T("Contraflexure"));

   auto dataset = dataset_p->GetDataSet();

   ForceEffectType fet;
   if (currRt==CLBAMViewerDoc::rtFx )
      fet = fetFx;
   else if( currRt==CLBAMViewerDoc::rtFy)
      fet = fetFy;
   else if ( currRt==CLBAMViewerDoc::rtMz )
      fet = fetMz;
   else if (currRt==CLBAMViewerDoc::rtDx || currRt==CLBAMViewerDoc::rtDy|| currRt==CLBAMViewerDoc::rtRz)
   {
      AfxMessageBox(_T("Deflection data not available for Contraflexure response"));
      return;
   }
   else if (currRt==CLBAMViewerDoc::rtStress)
   {
      AfxMessageBox(_T("Stress data not available for Contraflexure response"));
      return;
   }
   else
   {
      ATLASSERT(0);
      return;
   }

   CComPtr<IInfluenceLine> influence;

   if (currRt==CLBAMViewerDoc::rtFx || currRt==CLBAMViewerDoc::rtFy || currRt==CLBAMViewerDoc::rtMz)
   {
      // forces
      hr = m_pContraflexureResponse->ComputeContraflexureResponse(CComBSTR(currStg), fet, &influence);
      PROCESS_HR(hr);
   }

   if (influence==NULL)
   {
      ATLASSERT(0);
      return;
   }

   // fill up data set
   IndexType cnt;
   InfluenceSideType side = ilsBoth;

   hr = influence->get_Count(side, &cnt);
   ATLASSERT(SUCCEEDED(hr));
   for (IndexType ii=0; ii<cnt; ii++)
   {
      double value, location;
      InfluenceLocationType itype;
      hr = influence->Item(ii, side, &value, &itype, &location);
      ATLASSERT(SUCCEEDED(hr));

      if (currRt==CLBAMViewerDoc::rtFy)
         value *= -1;  // beam diagram coordinates

      WBFL::Geometry::Point2d pnt(location, value);

      dataset->Add(pnt);
   }

   dataSets->push_back(dataset_p);
}
