#ifndef INCLUDED_LBAMVIEWERUTILS_H_
#define INCLUDED_LBAMVIEWERUTILS_H_

inline void GetVehicularLoad(ILBAMModel* model, LiveLoadModelType modelType, long vehicleIndex, IVehicularLoad** vehicularLoad)
{
   HRESULT hr;
   CComPtr<ILiveLoad> liveload;
   hr = model->get_LiveLoad(&liveload);
   ATLASSERT(SUCCEEDED(hr));

   // get our vehicular load
   CComPtr<ILiveLoadModel> llm;
   switch (modelType)
   {
   case lltDeflection:
      hr = liveload->get_Deflection(&llm);
      break;
   case lltDesign:
      hr = liveload->get_Design(&llm);
      break;
   case lltPedestrian:
      hr = liveload->get_Pedestrian(&llm);
      break;
   case lltFatigue:
      hr = liveload->get_Fatigue(&llm);
      break;
   case lltPermit:
      hr = liveload->get_Permit(&llm);
      break;
   case lltSpecial:
      hr = liveload->get_Special(&llm);
      break;
   default:
      llm = NULL;
      ATLASSERT(0);
   };

   ATLASSERT(SUCCEEDED(hr));

   CComPtr<IVehicularLoads> vls;
   hr = llm->get_VehicularLoads(&vls);
   ATLASSERT(SUCCEEDED(hr));

   hr = vls->get_Item(vehicleIndex, vehicularLoad);
   ATLASSERT(SUCCEEDED(hr));
}

static const int NUM_LLM=6;
static const char* LL_NAMES[]={"Deflection","Design","Pedestrian","Fatigue","Permit","Special"};


#endif