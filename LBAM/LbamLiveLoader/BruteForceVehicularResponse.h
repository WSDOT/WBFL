///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2019  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// BruteForceVehicularResponse.h : Declaration of the CBruteForceVehicularResponse

#ifndef __BruteForceVehicularResponse_H_
#define __BruteForceVehicularResponse_H_

#include "resource.h"       // main symbols

#include "Truck.h"
#include <algorithm>
#include "LiveLoaderUtils.h"
#include "ComputeInfluenceLineStrategy.h"
#include "DistributionFactorStrategy.h"
#include "LLApplicabilityStrategy.h"

/////////////////////////////////////////////////////////////////////////////
// CBruteForceVehicularResponse
class ATL_NO_VTABLE CBruteForceVehicularResponse : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CBruteForceVehicularResponse,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CBruteForceVehicularResponse, &CLSID_BruteForceVehicularResponse>,
	public ISupportErrorInfo,
	public IEnvelopedVehicularResponse,
	public IDependOnVehicularAnalysisContext,
	public IVehicularAnalysisContextEvents,
   public IObjectSafetyImpl<CBruteForceVehicularResponse,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportProgressMonitor
{
public:
   CBruteForceVehicularResponse();

DECLARE_REGISTRY_RESOURCEID(IDR_BRUTEFORCEVEHICULARRESPONSE)
DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBruteForceVehicularResponse)
	COM_INTERFACE_ENTRY(IEnvelopedVehicularResponse)
	COM_INTERFACE_ENTRY(IDependOnVehicularAnalysisContext)
   COM_INTERFACE_ENTRY(IVehicularAnalysisContextEvents)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(ISupportProgressMonitor)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

   void FinalRelease();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IEnvelopedVehicularResponse
public: 
	STDMETHOD(ComputeForces)(/*[in]*/IIDArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                           /*[in]*/VehicleIndexType vehicleIndex, /*[in]*/ResultsOrientation orientation, 
                           /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization,
                           /*[in]*/VehicularLoadConfigurationType vehConfiguration,
                           /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/DistributionFactorType distributionType,
                           /*[in]*/VARIANT_BOOL computePlacements, /*[out]*/ILiveLoadModelSectionResults** results) override;

	STDMETHOD(ComputeDeflections)(/*[in]*/IIDArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                                 /*[in]*/VehicleIndexType vehicleIndex, 
                                 /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization,
                                 /*[in]*/VehicularLoadConfigurationType vehConfiguration,
                                 /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/DistributionFactorType distributionType,
                                 /*[in]*/VARIANT_BOOL computePlacements, /*[out]*/ILiveLoadModelSectionResults** results) override;

	STDMETHOD(ComputeReactions)(/*[in]*/IIDArray* supportIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                               /*[in]*/VehicleIndexType vehicleIndex, 
                               /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization,
                               /*[in]*/VehicularLoadConfigurationType vehConfiguration,
                               /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/DistributionFactorType distributionType,
                               /*[in]*/VARIANT_BOOL computePlacements, /*[out]*/ILiveLoadModelResults** results) override;

	STDMETHOD(ComputeSupportDeflections)(/*[in]*/IIDArray* supportIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                               /*[in]*/VehicleIndexType vehicleIndex, 
                               /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization,
                               /*[in]*/VehicularLoadConfigurationType vehConfiguration,
                               /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/DistributionFactorType distributionType,
                               /*[in]*/VARIANT_BOOL computePlacements, /*[out]*/ILiveLoadModelResults** results) override;

	STDMETHOD(ComputeStresses)(/*[in]*/IIDArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                              /*[in]*/VehicleIndexType vehicleIndex, 
                              /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization,
                              /*[in]*/VehicularLoadConfigurationType vehConfiguration,
                              /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/DistributionFactorType distributionType,
                              /*[in]*/VARIANT_BOOL computePlacements, /*[out]*/ILiveLoadModelStressResults** results) override;

public:
// IDependOnVehicularAnalysisContext
	STDMETHOD(Initialize)(/*[in]*/IUnknown* context) override;

// IVehicularAnalysisContextEvents
public:
   STDMETHOD(OnLiveLoadChanged)( LiveLoadModelType type) override;
   STDMETHOD(OnStiffnessResponseChanged)(ChangeScopeType scope, PoiIDType poiID) override;

// ISupportProgressMonitor
	STDMETHOD(InitializeProgressMonitor)(IProgressMonitor * newVal, LONG cookie) override;

private:
   // progress monitoring
   bool CheckForCancel()
   {
      if (m_pProgressMonitor)
      {
         VARIANT_BOOL cncl = VARIANT_FALSE;
         HRESULT hr = m_pProgressMonitor->get_WasCancelled(&cncl);
         ATLASSERT(SUCCEEDED(hr));
         return cncl!=VARIANT_FALSE;
      }
      else
         return false;
   }

   CComPtr<IProgressMonitor>                m_pProgressMonitor;
   long                                     m_ProgressCookie;


	HRESULT ComputeResponse(/*[in]*/IIDArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                              /*[in]*/VehicleIndexType vehicleIndex, 
                              /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization,
                              /*[in]*/VehicularLoadConfigurationType vehConfiguration,
                              /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/DistributionFactorType distributionType,
                              /*[in]*/VARIANT_BOOL computePlacements, /*[out]*/ILiveLoadModelSectionResults** results);

   void ComputeInflResponse(LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                            VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact, VARIANT_BOOL computePlacements,
                            IInfluenceLine* inflLine, 
                            Float64* leftResult, Float64 *rightResult, 
                            ILiveLoadConfiguration* leftConfig, ILiveLoadConfiguration* rightConfig);

   void AssertValid();

   // variables set before call to ComputeResponse to set up strategies
   iComputeInfluenceLineStrategy*     m_InflStrategy;
   iDistributionFactorStrategy*       m_DfStrategy;
   iLLApplicabilityStrategy*          m_ApplicabilityStrategy;

   bool                               m_CaptureJumps;

   CComPtr<ILiveLoad>                     m_LiveLoad;
   CComPtr<IInfluenceLineResponse>        m_InfluenceLineResponse;
   CComPtr<ILiveLoadNegativeMomentRegion> m_LiveLoadNegativeMomentRegion;
   CComPtr<IGetDistributionFactors>       m_GetDistributionFactors;
   CComPtr<ISupportLocations>             m_SupportLocations;
   CComPtr<IGetStressPoints>              m_GetStressPoints;
   CComPtr<IUnknown>                      m_Context;
   DWORD                                  m_ContextCookie;

   Float64 m_MinVariableAxleIncrement; // minimum step size of variable axle spacing

   // cached values for performance during multiple calls
   void Compute(BSTR stage, LiveLoadModelType type, VehicleIndexType vehicleIndex, VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact);

   // the values we cache
   // ------------------
   _bstr_t                          m_CachedStage;
   LiveLoadModelType                m_CachedLiveLoadModel;
   VehicleIndexType                 m_CachedVehicleIndex;
   VehicularLoadConfigurationType   m_CachedVehConfiguration;
   VARIANT_BOOL                     m_CachedDoApplyImpact;

   FixedTruck m_Truck;
   bool m_IsTruck;
   bool m_IsLane;
   bool m_IsSidewalk;
   bool m_IsNotional;
   Float64 m_LaneLoad;
   Float64 m_SidewalkLoad;
   LiveLoadApplicabilityType m_LiveLoadApplicability;

   // variable axle spacing
   typedef std::vector<Float64>            AxleSpacingContainer;
   typedef AxleSpacingContainer::iterator AxleSpacingIterator;
   AxleSpacingContainer m_AxleSpacings;

   // locations of the pois (where we place our axles)
   struct PoiLocation
   {
      PoiIDType ID;
      Float64 Location;

      PoiLocation(PoiIDType id, Float64 location):
      ID(id),
      Location(location)
      {;}
   };

   typedef std::vector<PoiLocation>       PoiLocationContainer;
   typedef PoiLocationContainer::iterator PoiLocationIterator;
   PoiLocationContainer m_PoiLocations;

   // a tolerance for truck placment - used only for shear reponse calc to capture jumps in 
   // shear due to axle loads
   Float64  m_TruckPlacementTolerance;

   // dirty flags
   bool m_ModelDirty;
   bool m_LiveLoadDirty;

   // simple class for performing comparisons and caching current optimized values
// simple class for performing comparisons and caching current optimized value
   class iLLCompare
   {
   public:
      iLLCompare():
      m_FirstCompare(true)
      {;}

      void Init()
      {
         m_FirstCompare=true;
         m_OptimizedVal=0.0;
      }

      // virtual function that can be overloaded to customize class
      virtual bool DoCompare(Float64 newVal, Float64 oldVal) = 0;

      bool CompareResults(Float64 newVal)
      {
         // always return true for first value
         if (m_FirstCompare)
         {
            m_FirstCompare=false;
            return true;
         }
         else
            return DoCompare(newVal, m_OptimizedVal);
      }

      void StoreState(Float64 newMax, Float64 truckLocation, TruckDirectionType direction,
                      std::vector<AxleState>& appliedAxles, Float64 variableSpacing)
      {
         ATLASSERT(!m_FirstCompare);

         m_OptimizedVal    = newMax;
         m_TruckLocation   = truckLocation;
         m_Direction       = direction;
         m_AppliedAxles    = appliedAxles;
         m_VariableSpacing = variableSpacing;
      }

      Float64 GetResult()
      {
         ATLASSERT(!m_FirstCompare);
         return m_OptimizedVal;
      }

       void ConfigureTruckPlacement(ILiveLoadConfiguration* llConfig, LiveLoadModelType liveLoadModel, VehicleIndexType vehicleIndex, VehicularLoadConfigurationType Config, 
                                              ForceEffectType forceEffect, OptimizationType optimization,
                                              VARIANT_BOOL doApplyImpact)
      {
         ATLASSERT(!m_FirstCompare);

         llConfig->put_IsApplicable(VARIANT_TRUE);
         llConfig->put_LiveLoadModel(liveLoadModel);
         llConfig->put_VehicleIndex(vehicleIndex);
         llConfig->put_VehicularLoadConfiguration(Config);
         llConfig->put_ForceEffect(forceEffect);
         llConfig->put_Optimization(optimization);

         llConfig->put_TruckDirection(m_Direction);
         llConfig->put_TruckPosition(m_TruckLocation);
         llConfig->put_VariableSpacing(m_VariableSpacing);

         llConfig->put_DoApplyImpact(doApplyImpact);

         // count number of falses and create array of inactive axles
         AxleIndexType nInactiveAxles = std::count(m_AppliedAxles.begin(), m_AppliedAxles.end(), AxleOff);

         CComPtr<IIndexArray> inactive_axles;
         inactive_axles.CoCreateInstance(CLSID_IndexArray);

         if (nInactiveAxles>0)
            inactive_axles->Reserve(nInactiveAxles);

         AxleIndexType axleIdx = 0;
         std::vector<AxleState>::iterator  axleIter;
         for (axleIter = m_AppliedAxles.begin(); axleIter != m_AppliedAxles.end(); axleIter++)
         {
            int bAxleApplied = *axleIter;
            if (0==bAxleApplied)
            {
               inactive_axles->Add(axleIdx);
            }

            axleIdx++;
         }

         llConfig->put_AxleConfig(inactive_axles);
      }

   protected:
      bool   m_FirstCompare;
      Float64 m_OptimizedVal;
      Float64 m_TruckLocation;
      TruckDirectionType m_Direction;
      std::vector<AxleState>  m_AppliedAxles;
      Float64 m_VariableSpacing;
   };

   // class for maximizing
   class MaxLLCompare : public iLLCompare
   {
      bool DoCompare(Float64 newVal, Float64 oldVal)
      {
         return newVal>oldVal;
      }
   };

   // class for minimizing
   class MinLLCompare : public iLLCompare
   {
      bool DoCompare(Float64 newVal, Float64 oldVal)
      {
         return newVal<oldVal;
      }
   };

   // instantiate these at start up so we only have to allocation them once
   MaxLLCompare m_LeftMaxCompare;
   MinLLCompare m_LeftMinCompare;
   MaxLLCompare m_RightMaxCompare;
   MinLLCompare m_RightMinCompare;

 
   void IntializeCompare(OptimizationType optimization, iLLCompare** pleftCompare,  iLLCompare** prightCompare);
};

#endif //__BruteForceVehicularResponse_H_
