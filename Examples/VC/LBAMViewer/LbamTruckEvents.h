#pragma once


interface iLBAMTruckEvents
{
   virtual void Init(std::shared_ptr<WBFL::DManip::iPointDisplayObject> pDO, ILBAMModel* model, LiveLoadModelType modelType, VehicleIndexType vehicleIndex,ILiveLoadConfiguration* placement) = 0;
   virtual void GetLiveLoadConfiguration(ILiveLoadConfiguration** dispObj) = 0;
	virtual void GetRoadwayElevation(double *pVal) = 0;
	virtual void SetRoadwayElevation(std::shared_ptr<WBFL::DManip::iPointDisplayObject> pDO, double newVal) = 0;
};

