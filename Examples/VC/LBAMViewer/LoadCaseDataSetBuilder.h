// LoadCaseDataSetBuilder.h: interface for the LoadCaseDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "DataSetBuilder.h"
#include "ReactionReportBuilder.h"


class LoadCaseDataSetBuilder : public iDataSetBuilder, public iReactionReportBuilder
{
public:
	LoadCaseDataSetBuilder(BSTR loadCase, ILoadCaseResponse* reponse);
	virtual ~LoadCaseDataSetBuilder();

   // iDataSetBuilder
   virtual void BuildDataSets(IIDArray* poilist, IDblArray* loclist, const CString& currStg,
                             CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                             COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);

   virtual long ColorDemand(const CString& currStg, CLBAMViewerDoc::ResponseType curr_rt)
   {
      return 1;
   }

   virtual CString GetDescription()
   {
      CString dsc(m_LoadCase);
      dsc = CString("Load Case Response for ") + dsc;
      return dsc;
   }


   // iReactionReportBuilder
   void BuildReactionReport(IIDArray* supportlist, BSTR currStg,
                            CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                            std::_tostream& pos);

private:
 	LoadCaseDataSetBuilder();
   void BuildForceDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);

   void BuildStressDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);

   CComBSTR m_LoadCase;
   CComPtr<ILoadCaseResponse> m_pLoadCaseResponse;
};

