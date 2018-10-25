// EnvelopedVehicularDataSetBuilder.h: interface for the EnvelopedVehicularDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENVELOPEDVEHICULARDATASETBUILDER_H__10C2652A_DE47_4FF9_9BA9_FC05801AA726__INCLUDED_)
#define AFX_ENVELOPEDVEHICULARDATASETBUILDER_H__10C2652A_DE47_4FF9_9BA9_FC05801AA726__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSetBuilder.h"
#include "ReactionReportBuilder.h"

class EnvelopedVehicularDataSetBuilder : public iDataSetBuilder, public iReactionReportBuilder
{
public:
	EnvelopedVehicularDataSetBuilder(LiveLoadModelType llmType, VehicleIndexType vehicleIndex, 
                                    llResponseType respType, IEnvelopedVehicularResponse* response);
	virtual ~EnvelopedVehicularDataSetBuilder();

   // iDataSetBuilder
   virtual void BuildDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                             CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                             COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);

   virtual long ColorDemand(BSTR currStg, CLBAMViewerDoc::ResponseType curr_rt)
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
                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);

   void BuildStressDataSets(IIDArray* poilist, IDblArray* loclist, BSTR currStg,
                            CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                            COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);

	EnvelopedVehicularDataSetBuilder();

   CComQIPtr<IEnvelopedVehicularResponse> m_pVehicularResponse;
   LiveLoadModelType                      m_LlmType;
   VehicleIndexType                                   m_VehicleIndex;
   llResponseType                         m_RespType;
};

#endif // !defined(AFX_ENVELOPEDVEHICULARDATASETBUILDER_H__10C2652A_DE47_4FF9_9BA9_FC05801AA726__INCLUDED_)
