// DistributionFactorDataSetBuilder.h: interface for the DistributionFactorDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DistributionFactorDATASETBUILDER_H__51063E76_8187_480E_BE44_28EBF2348E5C__INCLUDED_)
#define AFX_DistributionFactorDATASETBUILDER_H__51063E76_8187_480E_BE44_28EBF2348E5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSetBuilder.h"


class DistributionFactorDataSetBuilder : public iDataSetBuilder
{
public:
   // different properties we can create
   enum DfType {dtGPMSgl, dtGPMMul, dtGNMSgl, dtGNMMul, dtGVSgl, dtGVMul, 
                dtGDSgl, dtGDMul, dtGTSgl, dtGTMul, dtGRSgl, dtGRMul, dtGFat};

	DistributionFactorDataSetBuilder(DfType type, IGetDistributionFactors* pDfs);
	virtual ~DistributionFactorDataSetBuilder();

   // iDataSetBuilder
   virtual void BuildDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                             CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                             COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);

   virtual long ColorDemand(BSTR currStg, CLBAMViewerDoc::ResponseType curr_rt)
   {
      return 1;
   }

   virtual CString GetDescription()
   {
      return CString("Distribution Factors");
   }


private:
 	DistributionFactorDataSetBuilder();
   double GetVal(IDistributionFactor* pcs);

   CComPtr<IGetDistributionFactors> m_pDfs;
   DfType m_Type;
};




#endif
