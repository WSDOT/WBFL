// LiveLoadModelDataSetBuilder.h: interface for the LiveLoadModelDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "DataSetBuilder.h"
#include "ReactionReportBuilder.h"

class LiveLoadModelDataSetBuilder : public iDataSetBuilder, public iReactionReportBuilder
{
public:
	LiveLoadModelDataSetBuilder(LiveLoadModelType llmType, llResponseType respType, ILiveLoadModelResponse* response);
	virtual ~LiveLoadModelDataSetBuilder();

   // iDataSetBuilder
   virtual void BuildDataSets(IIDArray* poilist, IDblArray* loclist, const CString& currStg,
                             CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                             COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);

   virtual long ColorDemand(const CString& currStg, CLBAMViewerDoc::ResponseType curr_rt)
   {
      return 1;
   }

   virtual CString GetDescription();

   // iReactionReportBuilder
   void BuildReactionReport(IIDArray* supportlist, BSTR currStg,
                            CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                            std::_tostream& pos);

private:
   void BuildForceDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);

   void BuildStressDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                            CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                            COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);

	LiveLoadModelDataSetBuilder();

   CComQIPtr<ILiveLoadModelResponse> m_pLiveLoadModelResponse;
   LiveLoadModelType                 m_LlmType;
   llResponseType                    m_RespType;

};

