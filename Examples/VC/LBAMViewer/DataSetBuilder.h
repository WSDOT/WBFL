#ifndef INCLUDED_DATASETBUILDER_H_
#define INCLUDED_DATASETBUILDER_H_

#include "stdAfx.h"
#include "DataSetUtils.h"


class iDataSetBuilder
{
public:
   virtual ~iDataSetBuilder() {;}

   // build graph data set
   virtual void BuildDataSets(ILongArray* poilist, IDblArray* loclist, BSTR currStg,
                             CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                             COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)=0;

   // tell me how many colors this data set builder requires
   virtual long ColorDemand(BSTR currStg, CLBAMViewerDoc::ResponseType curr_rt)=0;

   virtual CString GetDescription()=0;

   // intialize before use
   virtual void InitializeOnSelect()
   {;}

   // indicate whether a truck placement is assocatiated with data set
   virtual bool HasTruckPlacement()
   {
      return false;
   }

   // get truck data - can only be called if HasTruckPlacement returns true
   virtual void GetTruckInfo(LiveLoadModelType* modelType, VehicleIndexType* vehicleIndex, ILiveLoadConfiguration** config)
   {
      ATLASSERT(0);
   }
};


#endif