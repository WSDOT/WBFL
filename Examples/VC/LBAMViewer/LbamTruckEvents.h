#ifndef INCLUDED_LBAMTRUCKEVENTS_H_
#define INCLUDED_LBAMTRUCKEVENTS_H_


interface iLBAMTruckEvents : public IUnknown
{
   STDMETHOD_(void,Init)(iPointDisplayObject* pDO, ILBAMModel* model, LiveLoadModelType modelType, VehicleIndexType vehicleIndex,ILiveLoadConfiguration* placement) PURE;
   STDMETHOD_(void,GetLiveLoadConfiguration)(ILiveLoadConfiguration** dispObj) PURE;
	STDMETHOD_(void,GetRoadwayElevation)(double *pVal) PURE;
	STDMETHOD_(void,SetRoadwayElevation)(iPointDisplayObject* pDO, double newVal) PURE;
};

#endif // INCLUDED_LBAMTruckEVENTS_H_