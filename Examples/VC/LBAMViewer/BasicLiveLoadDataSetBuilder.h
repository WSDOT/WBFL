// BasicLiveLoadDataSetBuilder.h: interface for the BasicLiveLoadDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "DataSetBuilder.h"
#include "ReactionReportBuilder.h"
#include "DataSetUtils.h"

class BasicLiveLoadDataSetBuilder : public iDataSetBuilder, public iReactionReportBuilder
{
public:
	BasicLiveLoadDataSetBuilder(LiveLoadModelType llmType, VehicleIndexType llIndex, 
                               llResponseType respType, ILBAMModel* model, 
                               IBasicVehicularResponse* pResponse);

	virtual ~BasicLiveLoadDataSetBuilder();

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


   // indicate whether a truck placement is associated with data set
   virtual bool HasTruckPlacement();
   virtual void GetTruckInfo(LiveLoadModelType* modelType, VehicleIndexType* vehicleIndex, ILiveLoadConfiguration** placement);

private:
   void BuildForceDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);

   void BuildStressDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                            CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                            COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets);


	BasicLiveLoadDataSetBuilder();

   void InitializePlacement();

   LiveLoadModelType                m_LlmType;
   VehicleIndexType                 m_LlIndex;
   CComPtr<ILBAMModel>              m_Model;
   CComPtr<IBasicVehicularResponse> m_Response;
   CComPtr<ILiveLoadConfiguration>  m_Placement;
   llResponseType                   m_RespType;
   bool                             m_IsTruck;
};

