// LoadCombinationDataSetBuilder.h: interface for the LoadCombinationDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADCOMBINATIONDATASETBUILDER_H__51063E76_8187_480E_BE44_28EBF2348E5C__INCLUDED_)
#define AFX_LOADCOMBINATIONDATASETBUILDER_H__51063E76_8187_480E_BE44_28EBF2348E5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSetBuilder.h"
#include "ReactionReportBuilder.h"


class LoadCombinationDataSetBuilder : public iDataSetBuilder, public iReactionReportBuilder
{
public:
	LoadCombinationDataSetBuilder(BSTR LoadCombination, ILoadCombinationResponse* reponse);
	virtual ~LoadCombinationDataSetBuilder();

   // iDataSetBuilder
   virtual void BuildDataSets(ILongArray* poilist, IDblArray* loclist, BSTR currStg,
                             CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                             COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);

   virtual long ColorDemand(BSTR currStg, CLBAMViewerDoc::ResponseType curr_rt)
   {
      return 1;
   }

   virtual CString GetDescription()
   {
      CString dsc(m_LoadCombination);
      dsc = CString("Combined Load Response for ") + dsc;
      return dsc;
   }


   // iReactionReportBuilder
   void BuildReactionReport(ILongArray* supportlist, BSTR currStg,
                            CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                            std::_tostream& pos);

private:
 	LoadCombinationDataSetBuilder();

   void BuildForceDataSets(ILongArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);

   void BuildStressDataSets(ILongArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);


   CComBSTR m_LoadCombination;
   CComPtr<ILoadCombinationResponse> m_pLoadCombinationResponse;

   VARIANT_BOOL m_IncludeLiveLoad;
};




#endif
