// DistributionFactorDataSetBuilder.h: interface for the DistributionFactorDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

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
   virtual void BuildDataSets(IIDArray* poilist, IDblArray* loclist, const CString& currStg,
                             CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                             COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);

   virtual long ColorDemand(const CString& currStg, CLBAMViewerDoc::ResponseType curr_rt)
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

