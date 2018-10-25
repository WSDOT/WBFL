// ReactionInfluenceDataSetBuilder.cpp: implementation of the ReactionInfluenceDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "ReactionInfluenceDataSetBuilder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ReactionInfluenceDataSetBuilder::ReactionInfluenceDataSetBuilder(SupportIDType supportId, IInfluenceLineResponse* response):
m_SupportId(supportId),
m_pInfluenceLineResponse(response)
{
}

ReactionInfluenceDataSetBuilder::~ReactionInfluenceDataSetBuilder()
{
}

void ReactionInfluenceDataSetBuilder::BuildDataSets(ILongArray* poiList, IDblArray* locList, BSTR currStg,
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
   entry->put_SymbolCharacterCode(213);
   entry->put_DoDrawLine(TRUE);

   CString str;
   str.Format(_T("React Infl %d"),m_SupportId);
   CComBSTR btmp(str);
   entry->put_Name(btmp);

   CComPtr<iDataSet2d> dataset;
   dataset_p->get_DataSet(&dataset);

   ForceEffectType fet;
   if (currRt==CLBAMViewerDoc::rtFx || currRt==CLBAMViewerDoc::rtDx)
      fet = fetFx;
   else if( currRt==CLBAMViewerDoc::rtFy || currRt==CLBAMViewerDoc::rtDy)
      fet = fetFy;
   else if ( currRt==CLBAMViewerDoc::rtMz || currRt==CLBAMViewerDoc::rtRz)
      fet = fetMz;
   else
   {
      ATLASSERT(0);
      return;
   }

   CComPtr<IInfluenceLine> influence;

   if (currRt==CLBAMViewerDoc::rtFx || currRt==CLBAMViewerDoc::rtFy || currRt==CLBAMViewerDoc::rtMz)
   {
      // forces
      hr = m_pInfluenceLineResponse->ComputeReactionInfluenceLine(m_SupportId, currStg, fet, &influence);
   }
   else  if (currRt==CLBAMViewerDoc::rtDx || currRt==CLBAMViewerDoc::rtDy || currRt==CLBAMViewerDoc::rtRz)
   {
      // deflections
      hr = m_pInfluenceLineResponse->ComputeSupportDeflectionInfluenceLine(m_SupportId, currStg, fet, &influence);
   }

   if (hr==LBAMA_E_SUPPORT_NOT_EXIST)
   {
      ::AfxMessageBox(_T("Temporary Support Does not Exist in this stage"));
      throw hr;
   }

   PROCESS_HR(hr);

   if (influence==NULL)
   {
      ATLASSERT(0);
      throw E_FAIL;
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

      pnt->put_X(location);
      pnt->put_Y(value);

      dataset->Add(pnt);
   }

   dataSets->push_back( dataset_p.Detach());
}
