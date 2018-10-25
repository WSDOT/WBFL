// InfluenceLineDataSetBuilder.h: interface for the InfluenceLineDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFLUENCELINEDATASETBUILDER_H__FC05FEE7_8D7C_4091_AA21_77E74AD51426__INCLUDED_)
#define AFX_INFLUENCELINEDATASETBUILDER_H__FC05FEE7_8D7C_4091_AA21_77E74AD51426__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSetBuilder.h"

class InfluenceLineDataSetBuilder : public iDataSetBuilder  
{
public:
	InfluenceLineDataSetBuilder(long poiID, IInfluenceLineResponse* response);
	virtual ~InfluenceLineDataSetBuilder();

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
      CString tmp;
      tmp.Format("Influence Line Response for POI %d", m_PoiId);
      return tmp;
   }


private:
	InfluenceLineDataSetBuilder();

   long m_PoiId;
   CComQIPtr<IInfluenceLineResponse> m_pInfluenceLineResponse;

};

#endif // !defined(AFX_INFLUENCELINEDATASETBUILDER_H__FC05FEE7_8D7C_4091_AA21_77E74AD51426__INCLUDED_)
