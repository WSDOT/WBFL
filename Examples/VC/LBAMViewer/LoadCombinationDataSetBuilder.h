// LoadCombinationDataSetBuilder.h: interface for the LoadCombinationDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "DataSetBuilder.h"
#include "ReactionReportBuilder.h"


class LoadCombinationDataSetBuilder : public iDataSetBuilder, public iReactionReportBuilder
{
public:
	LoadCombinationDataSetBuilder(BSTR LoadCombination, ILoadCombinationResponse* reponse);
	virtual ~LoadCombinationDataSetBuilder();

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
      CString dsc(m_LoadCombination);
      dsc = CString("Combined Load Response for ") + dsc;
      return dsc;
   }


   // iReactionReportBuilder
   void BuildReactionReport(IIDArray* supportlist, BSTR currStg,
                            CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                            std::_tostream& pos);

private:
 	LoadCombinationDataSetBuilder();

   void BuildForceDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);

   void BuildStressDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);


   CComBSTR m_LoadCombination;
   CComPtr<ILoadCombinationResponse> m_pLoadCombinationResponse;

   VARIANT_BOOL m_IncludeLiveLoad;
};

