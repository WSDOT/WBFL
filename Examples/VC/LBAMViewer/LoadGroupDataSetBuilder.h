// LoadGroupDataSetBuilder.h: interface for the LoadGroupDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADGROUPDATASETBUILDER_H__51063E76_8187_480E_BE44_28EBF2348E5C__INCLUDED_)
#define AFX_LOADGROUPDATASETBUILDER_H__51063E76_8187_480E_BE44_28EBF2348E5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSetBuilder.h"
#include "ReactionReportBuilder.h"

class LoadGroupDataSetBuilder : public iDataSetBuilder, public iReactionReportBuilder
{
public:
	LoadGroupDataSetBuilder(BSTR loadGroup, ILoadGroupResponse* reponse);
	virtual ~LoadGroupDataSetBuilder();

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
      CString dsc(m_LoadGroup);
      dsc = CString("Load Group Response for ") + dsc;
      return dsc;
   }

   // iReactionReportBuilder
   void BuildReactionReport(IIDArray* supportlist, BSTR currStg,
                            CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                            std::_tostream& pos);


private:
 	LoadGroupDataSetBuilder();
   void BuildForceDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);

   void BuildStressDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);

   CComBSTR m_LoadGroup;
   CComPtr<ILoadGroupResponse> m_pLoadGroupResponse;

};

#endif // !defined(AFX_LOADGROUPDATASETBUILDER_H__51063E76_8187_480E_BE44_28EBF2348E5C__INCLUDED_)
