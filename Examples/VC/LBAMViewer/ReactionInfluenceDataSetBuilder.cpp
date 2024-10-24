// ReactionInfluenceDataSetBuilder.cpp: implementation of the ReactionInfluenceDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "ReactionInfluenceDataSetBuilder.h"

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

ReactionInfluenceDataSetBuilder::ReactionInfluenceDataSetBuilder(SupportIDType supportId, IInfluenceLineResponse* response):
m_SupportId(supportId),
m_pInfluenceLineResponse(response)
{
}

ReactionInfluenceDataSetBuilder::~ReactionInfluenceDataSetBuilder()
{
}

void ReactionInfluenceDataSetBuilder::BuildDataSets(IIDArray* poiList, IDblArray* locList, const CString& currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets)
{
   HRESULT hr;
   // create dataset 
   auto dataset_p = std::make_shared<CGraphXyDataProvider>();

   // deal with legend
   auto fac = dataset_p->GetDataPointFactory();
   auto entry = std::dynamic_pointer_cast<iSymbolLegendEntry>(fac);

   entry->SetColor(color);
   entry->SetSymbolCharacterCode(213);
   entry->DoDrawLine(TRUE);

   CString str;
   str.Format(_T("React Infl %d"),m_SupportId);
   entry->SetName(str.LockBuffer());

   auto dataset = dataset_p->GetDataSet();

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

   CComBSTR bcurrStg(currStg);

   if (currRt==CLBAMViewerDoc::rtFx || currRt==CLBAMViewerDoc::rtFy || currRt==CLBAMViewerDoc::rtMz)
   {
      // forces
      hr = m_pInfluenceLineResponse->ComputeReactionInfluenceLine(m_SupportId, bcurrStg, fet, &influence);
   }
   else  if (currRt==CLBAMViewerDoc::rtDx || currRt==CLBAMViewerDoc::rtDy || currRt==CLBAMViewerDoc::rtRz)
   {
      // deflections
      hr = m_pInfluenceLineResponse->ComputeSupportDeflectionInfluenceLine(m_SupportId, bcurrStg, fet, &influence);
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

      WBFL::Geometry::Point2d pnt(location, value);
      dataset->Add(pnt);
   }

   dataSets->push_back( dataset_p);
}
