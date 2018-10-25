///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2010  Washington State Department of Transportation
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

// BruteForceVehicularResponse2.h : Declaration of the CBruteForceVehicularResponse2

#ifndef __BruteForceVehicularResponse2_H_
#define __BruteForceVehicularResponse2_H_

#include "resource.h"       // main symbols

#include "Truck.h"
#include <algorithm>
#include "LiveLoaderUtils.h"
#include "ComputeInfluenceLineStrategy.h"
#include "DistributionFactorStrategy.h"
#include "LLApplicabilityStrategy.h"

// simple class for performing comparisons and caching current optimized values
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

   iLLCompare(const iLLCompare& other)
   {
      m_FirstCompare = other.m_FirstCompare;
      m_OptimizedVal = other.m_OptimizedVal;
      m_TruckLocation = other.m_TruckLocation;
      m_Direction = other.m_Direction;
      m_AppliedAxles = other.m_AppliedAxles;
      m_VariableSpacing = other.m_VariableSpacing;
      m_PivotAxleIndex = other.m_PivotAxleIndex;
   }

   // virtual function that can be overloaded to customize class
   virtual bool DoCompare(Float64 newVal, Float64 oldVal) = 0;
   virtual iLLCompare* Clone() = 0;

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

   void StoreState(Float64 newMax, Float64 truckLocation, TruckDirectionType direction, AxleIndexType pivotAxleIndex,
                   std::vector<bool>& appliedAxles, Float64 variableSpacing)
   {
      ATLASSERT(!m_FirstCompare);

      m_OptimizedVal    = newMax;
      m_TruckLocation   = truckLocation;
      m_Direction       = direction;
      m_AppliedAxles    = appliedAxles;
      m_VariableSpacing = variableSpacing;
      m_PivotAxleIndex  = pivotAxleIndex;
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
      llConfig->put_PivotAxleIndex(m_PivotAxleIndex);
      llConfig->put_TruckPosition(m_TruckLocation);
      llConfig->put_VariableSpacing(m_VariableSpacing);

      llConfig->put_DoApplyImpact(doApplyImpact);

      // count number of falses and create array of inactive axles
      AxleIndexType count = std::count(m_AppliedAxles.begin(), m_AppliedAxles.end(), false);

      CComPtr<ILongArray> inactive_axles;
      inactive_axles.CoCreateInstance(CLSID_LongArray);

      AxleIndexType axleIdx = 0;
      std::vector<bool>::iterator axleIter;
      for (axleIter = m_AppliedAxles.begin(); axleIter != m_AppliedAxles.end(); axleIter++)
      {
         bool bAxleApplied = *axleIter;
         if (!bAxleApplied)
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
   std::vector<bool>  m_AppliedAxles;
   Float64 m_VariableSpacing;
   AxleIndexType m_PivotAxleIndex;
};

// class for maximizing
class MaxLLCompare : public iLLCompare
{
public:
   MaxLLCompare();
   MaxLLCompare(const MaxLLCompare& other);

   bool DoCompare(Float64 newVal, Float64 oldVal);
   iLLCompare* Clone();
};

// class for minimizing
class MinLLCompare : public iLLCompare
{
public:
   MinLLCompare();
   MinLLCompare(const MinLLCompare& other);

   bool DoCompare(Float64 newVal, Float64 oldVal);
   iLLCompare* Clone();
};

class InflResponseRecord
{
public:
   InflResponseRecord(PoiIDType poiID,LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                        VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                        iLLCompare* pLeftCompare = NULL, iLLCompare* pRightCompare = NULL);

   InflResponseRecord(const InflResponseRecord& other);

   ~InflResponseRecord();

   void Init(PoiIDType poiID,LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
             VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
             iLLCompare* pLeftCompare, iLLCompare* pRightCompare);

   bool operator<(const InflResponseRecord& other) const;
   InflResponseRecord& operator=(const InflResponseRecord& other);

   PoiIDType m_PoiID;
   LiveLoadModelType m_Type;
   VehicleIndexType m_VehicleIndex;
   ForceEffectType m_Effect;
   OptimizationType m_Optimization;
   VehicularLoadConfigurationType m_VehConfiguration;
   VARIANT_BOOL m_doApplyImpact;
   iLLCompare* m_pLeftCompare;
   iLLCompare* m_pRightCompare;
};

/////////////////////////////////////////////////////////////////////////////
// CBruteForceVehicularResponse2
class ATL_NO_VTABLE CBruteForceVehicularResponse2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CBruteForceVehicularResponse2,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CBruteForceVehicularResponse2, &CLSID_BruteForceVehicularResponse2>,
	public ISupportErrorInfo,
	public IEnvelopedVehicularResponse,
	public IDependOnVehicularAnalysisContext,
	public IVehicularAnalysisContextEvents,
   public IObjectSafetyImpl<CBruteForceVehicularResponse2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportProgressMonitor
{
public:
   CBruteForceVehicularResponse2();

DECLARE_REGISTRY_RESOURCEID(IDR_BRUTEFORCEVEHICULARRESPONSE2)
DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBruteForceVehicularResponse2)
	COM_INTERFACE_ENTRY(IEnvelopedVehicularResponse)
	COM_INTERFACE_ENTRY(IDependOnVehicularAnalysisContext)
   COM_INTERFACE_ENTRY(IVehicularAnalysisContextEvents)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(ISupportProgressMonitor)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

   void FinalRelease();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IEnvelopedVehicularResponse
public: 
	STDMETHOD(ComputeForces)(/*[in]*/ILongArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                           /*[in]*/VehicleIndexType vehicleIndex, /*[in]*/ResultsOrientation orientation, 
                           /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization,
                           /*[in]*/VehicularLoadConfigurationType vehConfiguration,
                           /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/DistributionFactorType distributionType,
                           /*[in]*/VARIANT_BOOL computePlacements, /*[out]*/ILiveLoadModelSectionResults** results);

	STDMETHOD(ComputeDeflections)(/*[in]*/ILongArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                                 /*[in]*/VehicleIndexType vehicleIndex, 
                                 /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization,
                                 /*[in]*/VehicularLoadConfigurationType vehConfiguration,
                                 /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/DistributionFactorType distributionType,
                                 /*[in]*/VARIANT_BOOL computePlacements, /*[out]*/ILiveLoadModelSectionResults** results);

	STDMETHOD(ComputeReactions)(/*[in]*/ILongArray* supportIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                               /*[in]*/VehicleIndexType vehicleIndex, 
                               /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization,
                               /*[in]*/VehicularLoadConfigurationType vehConfiguration,
                               /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/DistributionFactorType distributionType,
                               /*[in]*/VARIANT_BOOL computePlacements, /*[out]*/ILiveLoadModelResults** results);

	STDMETHOD(ComputeSupportDeflections)(/*[in]*/ILongArray* supportIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                               /*[in]*/VehicleIndexType vehicleIndex, 
                               /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization,
                               /*[in]*/VehicularLoadConfigurationType vehConfiguration,
                               /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/DistributionFactorType distributionType,
                               /*[in]*/VARIANT_BOOL computePlacements, /*[out]*/ILiveLoadModelResults** results);

	STDMETHOD(ComputeStresses)(/*[in]*/ILongArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                              /*[in]*/VehicleIndexType vehicleIndex, 
                              /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization,
                              /*[in]*/VehicularLoadConfigurationType vehConfiguration,
                              /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/DistributionFactorType distributionType,
                              /*[in]*/VARIANT_BOOL computePlacements, /*[out]*/ILiveLoadModelStressResults** results);

public:
// IDependOnVehicularAnalysisContext
	STDMETHOD(Initialize)(/*[in]*/IUnknown* context);

// IVehicularAnalysisContextEvents
public:
   STDMETHOD(OnLiveLoadChanged)( LiveLoadModelType type);
   STDMETHOD(OnStiffnessResponseChanged)(ChangeScopeType scope, PoiIDType poiID);

// ISupportProgressMonitor
	STDMETHOD(InitializeProgressMonitor)(IProgressMonitor * newVal, LONG cookie);

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


	STDMETHOD(ComputeResponse)(/*[in]*/ILongArray* poiIDs, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                              /*[in]*/VehicleIndexType vehicleIndex, 
                              /*[in]*/ForceEffectType effect,
                              /*[in]*/VehicularLoadConfigurationType vehConfiguration,
                              /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/DistributionFactorType distributionType,
                              /*[in]*/VARIANT_BOOL computePlacements, /*[out]*/ILiveLoadModelSectionResults** results);

   void ComputeInflResponse(PoiIDType poiID,LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                            VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact, VARIANT_BOOL computePlacements,
                            IInfluenceLine* inflLine, 
                            Float64* leftResult, Float64 *rightResult, 
                            ILiveLoadConfiguration* leftConfig, ILiveLoadConfiguration* rightConfig);

   void AssertValid();

   // variables set before call to ComputeResponse to set up strategies
   iComputeInfluenceLineStrategy*     m_pInflStrategy;
   iDistributionFactorStrategy*       m_pDfStrategy;
   iLLApplicabilityStrategy*          m_pApplicabilityStrategy;

   bool                               m_bComputingReaction; // true if we are computing a reaction
   bool                               m_bComputingMaximumInteriorSupportReaction; // true if we are computing a maximum reaction at an interior support
   bool                               m_bComputingMinimumMoment; // true if we are computing a minimum moment

   CComPtr<ILiveLoad>                     m_LiveLoad;
   CComPtr<IInfluenceLineResponse>        m_InfluenceLineResponse;
   CComPtr<ILiveLoadNegativeMomentRegion> m_LiveLoadNegativeMomentRegion;
   CComPtr<IGetDistributionFactors>       m_GetDistributionFactors;
   CComPtr<ISupportLocations>             m_SupportLocations;
   CComPtr<IGetStressPoints>              m_GetStressPoints;
   CComPtr<IUnknown>                      m_Context;
   DWORD                                  m_ContextCookie;

   long                                   m_VariableAxleSpacings;

   // cached values for performance during multiple calls
   void Configure(BSTR stage, LiveLoadModelType type, VehicleIndexType vehicleIndex, VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact);
   void ConfigureAnalysisCache(BSTR stage, LiveLoadModelType type, VehicleIndexType vehicleIndex, VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact);
   void ConfigureAxleSpacings();
   void ConfigureAnalysisPoints(BSTR stage);

   OptimizationType m_RealOptimization; // sometimes we have to play games with the optimization type
                                        // because of sign flips.
                                        // this parameter holds the real optimization we are doing

   // the values we cache
   // ------------------
   CComBSTR                         m_CachedStage;
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

   void EvaluateTruckLoad(LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                          VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                          VARIANT_BOOL computePlacements, IInfluenceLine* inflLine, InfluenceSideType truck_side,
                          iLLCompare* pLeftCompare,iLLCompare* pRightCompare,
                          Float64* pLeftResult, Float64 *pRightResult,
                          ILiveLoadConfiguration* leftConfig, ILiveLoadConfiguration* rightConfig);
   
   void EvaluateForMinMoment(LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                             VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                             VARIANT_BOOL computePlacements, IInfluenceLine* inflLine, InfluenceSideType truck_side,
                             iLLCompare* pLeftCompare,iLLCompare* pRightCompare,
                             Float64* pLeftResult, Float64 *pRightResult,
                             ILiveLoadConfiguration* leftConfig, ILiveLoadConfiguration* rightConfig);
      
   void EvaluateForInteriorSupportReaction(LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                             VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                             VARIANT_BOOL computePlacements, IInfluenceLine* inflLine, InfluenceSideType truck_side,
                             iLLCompare* pLeftCompare,iLLCompare* pRightCompare,
                             Float64* pLeftResult, Float64 *pRightResult,
                             ILiveLoadConfiguration* leftConfig, ILiveLoadConfiguration* rightConfig);

   void Evaluate(LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, OptimizationType optimization, 
                 VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                 VARIANT_BOOL computePlacements, IInfluenceLine* inflLine, InfluenceSideType truck_side,
                 iLLCompare* pLeftCompare,iLLCompare* pRightCompare,
                 Float64* pLeftResult, Float64 *pRightResult,
                 ILiveLoadConfiguration* leftConfig, ILiveLoadConfiguration* rightConfig);

   // variable axle spacing
   typedef std::vector<Float64>            AxleSpacingContainer;
   typedef AxleSpacingContainer::iterator AxleSpacingIterator;
   AxleSpacingContainer m_AxleSpacings;

   // locations of the pois (where we place our axles)
   struct PoiLocation
   {
      long   ID;
      Float64 Location;

      PoiLocation(long id, Float64 location):
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


   // instantiate these at start up so we only have to allocation them once
   MaxLLCompare m_LeftMaxCompare;
   MinLLCompare m_LeftMinCompare;
   MaxLLCompare m_RightMaxCompare;
   MinLLCompare m_RightMinCompare;

 
   void IntializeCompare(OptimizationType optimization, iLLCompare** pleftCompare,  iLLCompare** prightCompare);

   typedef std::set<InflResponseRecord> InflResponse;
   InflResponse m_ForceInflResponse;
   InflResponse m_DeflInflResponse;
   InflResponse m_ReactionInflResponse;
   InflResponse m_SupportDeflInflResponse;

   InflResponse* m_pResultsCache;

   typedef std::set<InflResponseRecord>::iterator InflResponseIterator;
   typedef std::set<InflResponseRecord>::const_iterator ConstInflResponseIterator;

   bool GetInflResponse(long poiID,LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect,
                        VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                        iLLCompare** ppLeftCompare, iLLCompare** ppRightCompare);

   void SaveInflResponse(long poiID,LiveLoadModelType type, VehicleIndexType vehicleIndex, ForceEffectType effect, 
                         VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL doApplyImpact,
                         iLLCompare* pLeftCompare, iLLCompare* pRightCompare);
};

#endif //__BruteForceVehicularResponse2_H_
