// ContraflexureDataSetBuilder.h: interface for the ContraflexureDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "DataSetBuilder.h"

class ContraflexureDataSetBuilder : public iDataSetBuilder  
{
public:
	ContraflexureDataSetBuilder(IContraflexureResponse* response);
	virtual ~ContraflexureDataSetBuilder();

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
      return CString("Contraflexure Response");
   }


private:
	ContraflexureDataSetBuilder();

   CComQIPtr<IContraflexureResponse> m_pContraflexureResponse;

};

