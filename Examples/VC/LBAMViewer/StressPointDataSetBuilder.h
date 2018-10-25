// StressPointDataSetBuilder.h: interface for the StressPointDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_StressPointDATASETBUILDER_H__51063E76_8187_480E_BE44_28EBF2348E5C__INCLUDED_)
#define AFX_StressPointDATASETBUILDER_H__51063E76_8187_480E_BE44_28EBF2348E5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSetBuilder.h"


class StressPointDataSetBuilder : public iDataSetBuilder
{
public:
   // different properties we can create
   enum SType {stSa, stSm};

	StressPointDataSetBuilder(SType type, IGetStressPoints* pGsp);
	virtual ~StressPointDataSetBuilder();

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
      CString dsc("Stress Points");
      return dsc;
   }

private:
 	StressPointDataSetBuilder();
   double GetVal(IStressPoint* pcs);

   CComPtr<IGetStressPoints> m_pStressPoints;
   SType m_Type;
};




#endif
