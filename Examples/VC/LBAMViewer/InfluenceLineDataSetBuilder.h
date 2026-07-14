// InfluenceLineDataSetBuilder.h: interface for the InfluenceLineDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "DataSetBuilder.h"

class InfluenceLineDataSetBuilder : public iDataSetBuilder  
{
public:
	InfluenceLineDataSetBuilder(PoiIDType poiID, IInfluenceLineResponse* response);
	virtual ~InfluenceLineDataSetBuilder();

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
      CString tmp;
      tmp.Format(_T("Influence Line Response for POI %d"), m_PoiId);
      return tmp;
   }


private:
	InfluenceLineDataSetBuilder();

   PoiIDType m_PoiId;
   CComQIPtr<IInfluenceLineResponse> m_pInfluenceLineResponse;

};

