// StressPointDataSetBuilder.h: interface for the StressPointDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "DataSetBuilder.h"


class StressPointDataSetBuilder : public iDataSetBuilder
{
public:
   // different properties we can create
   enum SType {stSa, stSm};

	StressPointDataSetBuilder(SType type, IGetStressPoints* pGsp);
	virtual ~StressPointDataSetBuilder();

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
      CString dsc("Stress Points");
      return dsc;
   }

private:
 	StressPointDataSetBuilder();
   double GetVal(IStressPoint* pcs);

   CComPtr<IGetStressPoints> m_pStressPoints;
   SType m_Type;
};

