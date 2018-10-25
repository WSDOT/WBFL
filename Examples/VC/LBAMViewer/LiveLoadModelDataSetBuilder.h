// LiveLoadModelDataSetBuilder.h: interface for the LiveLoadModelDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIVELOADMODELDATASETBUILDER_H__3BE3848A_55B5_4AFF_85AE_17393BB1F515__INCLUDED_)
#define AFX_LIVELOADMODELDATASETBUILDER_H__3BE3848A_55B5_4AFF_85AE_17393BB1F515__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSetBuilder.h"
#include "ReactionReportBuilder.h"

class LiveLoadModelDataSetBuilder : public iDataSetBuilder, public iReactionReportBuilder
{
public:
	LiveLoadModelDataSetBuilder(LiveLoadModelType llmType, llResponseType respType, ILiveLoadModelResponse* response);
	virtual ~LiveLoadModelDataSetBuilder();

   // iDataSetBuilder
   virtual void BuildDataSets(ILongArray* poilist, IDblArray* loclist, BSTR currStg,
                             CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                             COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);

   virtual long ColorDemand(BSTR currStg, CLBAMViewerDoc::ResponseType curr_rt)
   {
      return 1;
   }

   virtual CString GetDescription();

   // iReactionReportBuilder
   void BuildReactionReport(ILongArray* supportlist, BSTR currStg,
                            CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                            std::ostream& pos);

private:
   void BuildForceDataSets(ILongArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);

   void BuildStressDataSets(ILongArray* poilist, IDblArray* loclist, BSTR currStg,
                            CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                            COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);

	LiveLoadModelDataSetBuilder();

   CComQIPtr<ILiveLoadModelResponse> m_pLiveLoadModelResponse;
   LiveLoadModelType                 m_LlmType;
   llResponseType                    m_RespType;

};

#endif // !defined(AFX_LIVELOADMODELDATASETBUILDER_H__3BE3848A_55B5_4AFF_85AE_17393BB1F515__INCLUDED_)
