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
   virtual void BuildDataSets(ILongArray* poilist, IDblArray* loclist, BSTR currStg,
                             CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                             COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);

   virtual long ColorDemand(BSTR currStg, CLBAMViewerDoc::ResponseType curr_rt)
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
   void BuildReactionReport(ILongArray* supportlist, BSTR currStg,
                            CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                            std::ostream& pos);


private:
 	LoadGroupDataSetBuilder();
   void BuildForceDataSets(ILongArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);

   void BuildStressDataSets(ILongArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);

   CComBSTR m_LoadGroup;
   CComPtr<ILoadGroupResponse> m_pLoadGroupResponse;

};

#endif // !defined(AFX_LOADGROUPDATASETBUILDER_H__51063E76_8187_480E_BE44_28EBF2348E5C__INCLUDED_)
