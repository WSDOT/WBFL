// ReactionInfluenceDataSetBuilder.h: interface for the ReactionInfluenceDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "DataSetBuilder.h"

class ReactionInfluenceDataSetBuilder : public iDataSetBuilder  
{
public:
	ReactionInfluenceDataSetBuilder(SupportIDType supportId, IInfluenceLineResponse* response);
	virtual ~ReactionInfluenceDataSetBuilder();

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
      CString dsc;
      dsc.Format(_T("Reaction Influence for Support %d"), m_SupportId);
      return dsc;
   }


private:
	ReactionInfluenceDataSetBuilder();

   SupportIDType m_SupportId;
   CComQIPtr<IInfluenceLineResponse> m_pInfluenceLineResponse;

};

