///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright � 1999-2025  Washington State Department of Transportation
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

// VehicularAnalysisContext.h : Declaration of the CVehicularAnalysisContext

#ifndef __VEHICULARANALYSISCONTEXT_H_
#define __VEHICULARANALYSISCONTEXT_H_

#include "resource.h"       // main symbols

#include <vector>
#include "LBAMLiveLoaderCP.h"

/////////////////////////////////////////////////////////////////////////////
// CVehicularAnalysisContext
class ATL_NO_VTABLE CVehicularAnalysisContext : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CVehicularAnalysisContext,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CVehicularAnalysisContext, &CLSID_VehicularAnalysisContext>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CVehicularAnalysisContext>,
	public IVehicularAnalysisContext,
	public ISupportLocations, 
	public IInfluenceLineResponse,
	public ILiveLoadNegativeMomentRegion, 
	public IAnalysisPOIs, 
	public IGetDistributionFactors,
	public IGetStressPoints, 
   public ILiveLoad, 
	public ILBAMModelEvents,
	public ILiveLoadEvents, 
   public IObjectSafetyImpl<CVehicularAnalysisContext,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDVehicularAnalysisContextEvents< CVehicularAnalysisContext >
{
public:
	CVehicularAnalysisContext();

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_VEHICULARANALYSISCONTEXT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVehicularAnalysisContext)
	COM_INTERFACE_ENTRY(IVehicularAnalysisContext)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISupportLocations)
	COM_INTERFACE_ENTRY(IInfluenceLineResponse)
	COM_INTERFACE_ENTRY(ILiveLoadNegativeMomentRegion)
	COM_INTERFACE_ENTRY(IAnalysisPOIs)
	COM_INTERFACE_ENTRY(IGetDistributionFactors)
	COM_INTERFACE_ENTRY(IGetStressPoints)
	COM_INTERFACE_ENTRY(ILiveLoad)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ILBAMModelEvents)
   COM_INTERFACE_ENTRY(ILiveLoadEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CVehicularAnalysisContext)
CONNECTION_POINT_ENTRY(IID_IVehicularAnalysisContextEvents)
END_CONNECTION_POINT_MAP()

DECLARE_GET_CONTROLLING_UNKNOWN()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IVehicularAnalysisContext
public:
	STDMETHOD(Initialize)(/*[in]*/ILBAMModel* model, /*[in]*/IInfluenceLineResponse* influence, 
                         /*[in]*/ILiveLoadNegativeMomentRegion* llnmr, /*[in]*/IAnalysisPOIs* pois,
                         /*[in]*/IGetDistributionFactors* dfs, /*[in]*/IGetStressPoints* gcs);

   STDMETHOD(get_Model)(/*[out,retval]*/ILBAMModel** ppModel) override;

// ISupportLocations
public:
	STDMETHOD(get_LeftOverhang)(/*[out,retval]*/Float64* overhang) override;
	STDMETHOD(get_RightOverhang)(/*[out,retval]*/Float64* overhang) override;
	STDMETHOD(get_SupportLocations)(/*[out,retval]*/IDblArray* *suppLocs) override;
	STDMETHOD(get_TotalLength)(/*[out,retval]*/Float64* length) override;

// IInfluenceLineResponse
   STDMETHOD(ComputeForceInfluenceLine)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[in]*/ForceEffectType forceEffect, /*[in]*/ ResultsOrientation orientation, /*[out]*/ IInfluenceLine** lftVal, /*[out]*/ IInfluenceLine** rgtVal) override;
   STDMETHOD(ComputeDeflectionInfluenceLine)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[in]*/ForceEffectType deflectionEffect, /*[out]*/ IInfluenceLine** lftVal, /*[out]*/ IInfluenceLine** rgtVal) override;
   STDMETHOD(ComputeReactionInfluenceLine)(/*[in]*/SupportIDType supportID, /*[in]*/BSTR stage, /*[in]*/ForceEffectType deflectionEffect, /*[out,retval]*/ IInfluenceLine** newVal) override;
   STDMETHOD(ComputeSupportDeflectionInfluenceLine)(/*[in]*/SupportIDType supportID, /*[in]*/BSTR stage, /*[in]*/ForceEffectType deflectionEffect, /*[out,retval]*/ IInfluenceLine** newVal) override;
	STDMETHOD(GetZeroTolerance)(/*[out]*/Float64* forceTolerance, /*[out]*/Float64* deflectionTolerance) override;
	STDMETHOD(SetZeroTolerance)(/*[in]*/Float64 forceTolerance, /*[in]*/Float64 deflectionTolerance) override;

// ILiveLoadNegativeMomentRegion
   STDMETHOD(get_IsPOIInNegativeLiveLoadMomentZone)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[out,retval]*/InZoneType* isInZone) override;
   STDMETHOD(ComputeNegativeMomentRegions)(/*[in]*/BSTR stage, /*[out,retval]*/IDblArray* *locations) override;

// IAnalysisPOIs
   STDMETHOD(get_SpanPoiIncrement)( PoiIDType *pVal) override;
   STDMETHOD(put_SpanPoiIncrement)( PoiIDType newVal) override;
   STDMETHOD(get_CantileverPoiIncrement)(PoiIDType *pVal) override;
   STDMETHOD(put_CantileverPoiIncrement)( PoiIDType newVal) override;
   STDMETHOD(GetSuperstructurePois)(BSTR stage, IIDArray* *poiIDs, IDblArray* *poiLocations) override;
   STDMETHOD(GetPoiInfo)(BSTR stage, PoiIDType poiID, MemberType* lbamMemberType, MemberIDType* memberID, Float64* memberLocation) override;

// IGetDistributionFactors
   STDMETHOD(GetPOIDistributionFactor)(/*[in]*/PoiIDType POI, /*[in]*/BSTR stage, /*[out]*/IDistributionFactor* *leftFactor, /*[out]*/IDistributionFactor* *rightFactor) override;
	STDMETHOD(GetSupportDistributionFactor)(/*[in]*/SupportIDType supportID, /*[in]*/BSTR Stage, /*[out,retval]*/IDistributionFactor* *Factor) override;

// IGetStressPoints
   STDMETHOD(GetStressPointsAtPOI)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[out]*/IStressPoints* *leftSps,  /*[out]*/IStressPoints* *rightSPs) override;

// ILiveLoad
public:
	STDMETHOD(IsInteriorSupport)(/*[in]*/SupportIDType supportID, /*[out,retval]*/VARIANT_BOOL* isInterior) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(Clone)(/*[out,retval]*/ILiveLoad** clone) override;
   STDMETHOD(get_LegalRoutineRating)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
   STDMETHOD(putref_LegalRoutineRating)(/*[in]*/ ILiveLoadModel* newVal) override;
   STDMETHOD(get_LegalSpecialRating)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
   STDMETHOD(putref_LegalSpecialRating)(/*[in]*/ ILiveLoadModel* newVal) override;
   STDMETHOD(get_LegalEmergencyRating)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
   STDMETHOD(putref_LegalEmergencyRating)(/*[in]*/ ILiveLoadModel* newVal) override;
   STDMETHOD(get_PermitRoutineRating)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
   STDMETHOD(putref_PermitRoutineRating)(/*[in]*/ ILiveLoadModel* newVal) override;
   STDMETHOD(get_PermitSpecialRating)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
   STDMETHOD(putref_PermitSpecialRating)(/*[in]*/ ILiveLoadModel* newVal) override;
	STDMETHOD(get_Pedestrian)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
	STDMETHOD(putref_Pedestrian)(/*[in]*/ ILiveLoadModel* newVal) override;
	STDMETHOD(get_Special)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
	STDMETHOD(putref_Special)(/*[in]*/ ILiveLoadModel* newVal) override;
	STDMETHOD(get_Permit)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
	STDMETHOD(putref_Permit)(/*[in]*/ ILiveLoadModel* newVal) override;
	STDMETHOD(get_Fatigue)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
	STDMETHOD(putref_Fatigue)(/*[in]*/ ILiveLoadModel* newVal) override;
	STDMETHOD(get_Deflection)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
	STDMETHOD(putref_Deflection)(/*[in]*/ ILiveLoadModel* newVal) override;
	STDMETHOD(get_Design)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
	STDMETHOD(putref_Design)(/*[in]*/ ILiveLoadModel* newVal) override;

// ILBAMModelEvents
   STDMETHOD(OnModelChanged)(/*[in]*/ILBAMModel* Model, ChangeType change) override;

// ILiveLoadEvents
   STDMETHOD(OnLiveLoadChanged)(ILiveLoad* load, LiveLoadModelType lltype) override;

private:
   void Compute();
   void ComputeSupportLocations();
   bool m_IsComputed;
   void Invalidate();

   CComPtr<ILBAMModel> m_pModel;
   CComPtr<ILiveLoad> m_pLiveLoad;

   CComPtr<IInfluenceLineResponse>         m_pInfluenceResponse;
   CComPtr<ILiveLoadNegativeMomentRegion>  m_pLiveLoadNegativeMomentRegion;
   CComPtr<IAnalysisPOIs>                  m_pAnalysisPOIs;
   CComPtr<IGetDistributionFactors>        m_pGetDistributionFactors;
   CComPtr<IGetStressPoints>               m_pGetStressPoints;

   DWORD m_ModelEventsCookie;
   DWORD m_LiveLoadEventsCookie;

   // support locations
   Float64 m_LeftOverhang;
   Float64 m_RightOverhang;
   Float64 m_SuperstructureLength;
   SupportIDType  m_NumSupports; // number of supports - not including temporaries
   CComPtr<IDblArray>  m_SupportLocations;


};

#endif //__VEHICULARANALYSISCONTEXT_H_
