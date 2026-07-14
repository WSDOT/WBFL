// PropertyDataSetBuilder.h: interface for the PropertyDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "DataSetBuilder.h"


class PropertyDataSetBuilder : public iDataSetBuilder
{
public:
   // different properties we can create
   enum PType {ptEAForce, ptEADefl, ptEIForce, ptEIDefl, ptDepth, ptThermal};

	PropertyDataSetBuilder(PType type, IGetSegmentCrossSection* pGcs);
	virtual ~PropertyDataSetBuilder();

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
      CString dsc("Properties");
      return dsc;
   }


private:
 	PropertyDataSetBuilder();
   double GetVal(ISegmentCrossSection* pcs);

   CComPtr<IGetSegmentCrossSection> m_pGetCrossSection;
   PType m_Type;
};

