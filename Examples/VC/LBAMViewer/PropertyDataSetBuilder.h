// PropertyDataSetBuilder.h: interface for the PropertyDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PropertyDATASETBUILDER_H__51063E76_8187_480E_BE44_28EBF2348E5C__INCLUDED_)
#define AFX_PropertyDATASETBUILDER_H__51063E76_8187_480E_BE44_28EBF2348E5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSetBuilder.h"


class PropertyDataSetBuilder : public iDataSetBuilder
{
public:
   // different properties we can create
   enum PType {ptEAForce, ptEADefl, ptEIForce, ptEIDefl, ptDepth, ptThermal};

	PropertyDataSetBuilder(PType type, IGetSegmentCrossSection* pGcs);
	virtual ~PropertyDataSetBuilder();

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
      CString dsc("Properties");
      return dsc;
   }


private:
 	PropertyDataSetBuilder();
   double GetVal(ISegmentCrossSection* pcs);

   CComPtr<IGetSegmentCrossSection> m_pGetCrossSection;
   PType m_Type;
};




#endif
