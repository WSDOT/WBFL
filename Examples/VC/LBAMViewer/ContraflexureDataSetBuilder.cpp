// ContraflexureDataSetBuilder.cpp: implementation of the ContraflexureDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "ContraflexureDataSetBuilder.h"

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

void ContraflexureDataSetBuilder::BuildDataSets(IIDArray* poiList, IDblArray* locList, BSTR currStg,
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
   entry->put_SymbolCharacterCode(64);
   entry->put_DoDrawLine(TRUE);

   CComBSTR btmp("Contraflexure");
   entry->put_Name(btmp);

   CComPtr<iDataSet2d> dataset;
   dataset_p->get_DataSet(&dataset);

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
      hr = m_pContraflexureResponse->ComputeContraflexureResponse(currStg, fet, &influence);
      PROCESS_HR(hr);
   }

   if (influence==NULL)
   {
      ATLASSERT(0);
      return;
   }

   // fill up data set
   CollectionIndexType cnt;
   InfluenceSideType side = ilsBoth;

   hr = influence->get_Count(side, &cnt);
   ATLASSERT(SUCCEEDED(hr));
   for (CollectionIndexType ii=0; ii<cnt; ii++)
   {
      double value, location;
      InfluenceLocationType itype;
      hr = influence->Item(ii, side, &value, &itype, &location);
      ATLASSERT(SUCCEEDED(hr));

      CComPtr<IPoint2d> pnt;
      hr = pnt.CoCreateInstance(CLSID_Point2d);
      ATLASSERT(SUCCEEDED(hr));

      if (currRt==CLBAMViewerDoc::rtFy)
         value *= -1;  // beam diagram coordinates

      pnt->put_X(location);
      pnt->put_Y(value);

      dataset->Add(pnt);
   }

   dataSets->push_back( dataset_p.Detach());
}
