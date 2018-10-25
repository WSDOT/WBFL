// ReactionInfluenceDataSetBuilder.h: interface for the ReactionInfluenceDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ReactionInfluenceDataSetBuilder_H__FC05FEE7_8D7C_4091_AA21_77E74AD51426__INCLUDED_)
#define AFX_ReactionInfluenceDataSetBuilder_H__FC05FEE7_8D7C_4091_AA21_77E74AD51426__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSetBuilder.h"

class ReactionInfluenceDataSetBuilder : public iDataSetBuilder  
{
public:
	ReactionInfluenceDataSetBuilder(SupportIDType supportId, IInfluenceLineResponse* response);
	virtual ~ReactionInfluenceDataSetBuilder();

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
      CString dsc;
      dsc.Format(_T("Reaction Influence for Support %d"), m_SupportId);
      return dsc;
   }


private:
	ReactionInfluenceDataSetBuilder();

   SupportIDType m_SupportId;
   CComQIPtr<IInfluenceLineResponse> m_pInfluenceLineResponse;

};

#endif // !defined(AFX_ReactionInfluenceDataSetBuilder_H__FC05FEE7_8D7C_4091_AA21_77E74AD51426__INCLUDED_)
