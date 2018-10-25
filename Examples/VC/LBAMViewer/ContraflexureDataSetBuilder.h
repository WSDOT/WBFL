// ContraflexureDataSetBuilder.h: interface for the ContraflexureDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ContraflexureDATASETBUILDER_H__FC05FEE7_8D7C_4091_AA21_77E74AD51426__INCLUDED_)
#define AFX_ContraflexureDATASETBUILDER_H__FC05FEE7_8D7C_4091_AA21_77E74AD51426__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSetBuilder.h"

class ContraflexureDataSetBuilder : public iDataSetBuilder  
{
public:
	ContraflexureDataSetBuilder(IContraflexureResponse* response);
	virtual ~ContraflexureDataSetBuilder();

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
      return CString("Contraflexure Response");
   }


private:
	ContraflexureDataSetBuilder();

   CComQIPtr<IContraflexureResponse> m_pContraflexureResponse;

};

#endif // !defined(AFX_ContraflexureDATASETBUILDER_H__FC05FEE7_8D7C_4091_AA21_77E74AD51426__INCLUDED_)
