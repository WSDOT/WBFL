// EnvelopedVehicularDataSetBuilder.h: interface for the EnvelopedVehicularDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "DataSetBuilder.h"
#include "ReactionReportBuilder.h"

class EnvelopedVehicularDataSetBuilder : public iDataSetBuilder, public iReactionReportBuilder
{
public:
	EnvelopedVehicularDataSetBuilder(LiveLoadModelType llmType, VehicleIndexType vehicleIndex, 
                                    llResponseType respType, IEnvelopedVehicularResponse* response);
	virtual ~EnvelopedVehicularDataSetBuilder();

   // iDataSetBuilder
   virtual void BuildDataSets(IIDArray* poilist, IDblArray* loclist, const CString& currStg,
                             CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                             COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);

   virtual long ColorDemand(const CString& currStg, CLBAMViewerDoc::ResponseType curr_rt)
   {
      return 1;
   }

   virtual CString GetDescription();

   // iReactionReportBuilder
   virtual void BuildReactionReport(IIDArray* supportlist, BSTR currStg,
                                    CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                                    std::_tostream& pos);

private:
   void BuildForceDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);

   void BuildStressDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                            CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                            COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);

	EnvelopedVehicularDataSetBuilder();

   CComQIPtr<IEnvelopedVehicularResponse> m_pVehicularResponse;
   LiveLoadModelType                      m_LlmType;
   VehicleIndexType                                   m_VehicleIndex;
   llResponseType                         m_RespType;
};

