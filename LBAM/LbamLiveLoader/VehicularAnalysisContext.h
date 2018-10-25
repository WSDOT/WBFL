///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2015  Washington State Department of Transportation
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
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IVehicularAnalysisContext
public:
	STDMETHOD(Initialize)(/*[in]*/ILBAMModel* model, /*[in]*/IInfluenceLineResponse* influence, 
                         /*[in]*/ILiveLoadNegativeMomentRegion* llnmr, /*[in]*/IAnalysisPOIs* pois,
                         /*[in]*/IGetDistributionFactors* dfs, /*[in]*/IGetStressPoints* gcs);

// ISupportLocations
public:
	STDMETHOD(get_LeftOverhang)(/*[out,retval]*/Float64* overhang);
	STDMETHOD(get_RightOverhang)(/*[out,retval]*/Float64* overhang);
	STDMETHOD(get_SupportLocations)(/*[out,retval]*/IDblArray* *suppLocs);
	STDMETHOD(get_TotalLength)(/*[out,retval]*/Float64* length);

// IInfluenceLineResponse
   STDMETHOD(ComputeForceInfluenceLine)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[in]*/ForceEffectType forceEffect, /*[in]*/ ResultsOrientation orientation, /*[out]*/ IInfluenceLine** lftVal, /*[out]*/ IInfluenceLine** rgtVal);
   STDMETHOD(ComputeDeflectionInfluenceLine)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[in]*/ForceEffectType deflectionEffect, /*[out]*/ IInfluenceLine** lftVal, /*[out]*/ IInfluenceLine** rgtVal);
   STDMETHOD(ComputeReactionInfluenceLine)(/*[in]*/SupportIDType supportID, /*[in]*/BSTR stage, /*[in]*/ForceEffectType deflectionEffect, /*[out,retval]*/ IInfluenceLine** newVal);
   STDMETHOD(ComputeSupportDeflectionInfluenceLine)(/*[in]*/SupportIDType supportID, /*[in]*/BSTR stage, /*[in]*/ForceEffectType deflectionEffect, /*[out,retval]*/ IInfluenceLine** newVal);
	STDMETHOD(GetZeroTolerance)(/*[out]*/Float64* forceTolerance, /*[out]*/Float64* deflectionTolerance);
	STDMETHOD(SetZeroTolerance)(/*[in]*/Float64 forceTolerance, /*[in]*/Float64 deflectionTolerance);

// ILiveLoadNegativeMomentRegion
   STDMETHOD(get_IsPOIInNegativeLiveLoadMomentZone)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[out,retval]*/InZoneType* isInZone);
   STDMETHOD(ComputeNegativeMomentRegions)(/*[in]*/BSTR stage, /*[out,retval]*/IDblArray* *locations);

// IAnalysisPOIs
   STDMETHOD(get_SpanPoiIncrement)( PoiIDType *pVal);
   STDMETHOD(put_SpanPoiIncrement)( PoiIDType newVal);
   STDMETHOD(get_CantileverPoiIncrement)(PoiIDType *pVal);
   STDMETHOD(put_CantileverPoiIncrement)( PoiIDType newVal);
   STDMETHOD(GetSuperstructurePois)(BSTR stage, IIDArray* *poiIDs, IDblArray* *poiLocations);
   STDMETHOD(GetPoiInfo)(BSTR stage, PoiIDType poiID, MemberType* lbamMemberType, MemberIDType* memberID, Float64* memberLocation);

// IGetDistributionFactors
   STDMETHOD(GetPOIDistributionFactor)(/*[in]*/PoiIDType POI, /*[in]*/BSTR stage, /*[out]*/IDistributionFactor* *leftFactor, /*[out]*/IDistributionFactor* *rightFactor);
	STDMETHOD(GetSupportDistributionFactor)(/*[in]*/SupportIDType supportID, /*[in]*/BSTR Stage, /*[out,retval]*/IDistributionFactor* *Factor);

// IGetStressPoints
   STDMETHOD(GetStressPointsAtPOI)(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[out]*/IStressPoints* *leftSps,  /*[out]*/IStressPoints* *rightSPs);

// ILiveLoad
public:
	STDMETHOD(IsInteriorSupport)(/*[in]*/SupportIDType supportID, /*[out,retval]*/VARIANT_BOOL* isInterior);
	STDMETHOD(Clear)();
	STDMETHOD(Clone)(/*[out,retval]*/ILiveLoad** clone);
   STDMETHOD(get_LegalRoutineRating)(/*[out, retval]*/ ILiveLoadModel* *pVal);
   STDMETHOD(putref_LegalRoutineRating)(/*[in]*/ ILiveLoadModel* newVal);
   STDMETHOD(get_LegalSpecialRating)(/*[out, retval]*/ ILiveLoadModel* *pVal);
   STDMETHOD(putref_LegalSpecialRating)(/*[in]*/ ILiveLoadModel* newVal);
   STDMETHOD(get_PermitRoutineRating)(/*[out, retval]*/ ILiveLoadModel* *pVal);
   STDMETHOD(putref_PermitRoutineRating)(/*[in]*/ ILiveLoadModel* newVal);
   STDMETHOD(get_PermitSpecialRating)(/*[out, retval]*/ ILiveLoadModel* *pVal);
   STDMETHOD(putref_PermitSpecialRating)(/*[in]*/ ILiveLoadModel* newVal);
	STDMETHOD(get_Pedestrian)(/*[out, retval]*/ ILiveLoadModel* *pVal);
	STDMETHOD(putref_Pedestrian)(/*[in]*/ ILiveLoadModel* newVal);
	STDMETHOD(get_Special)(/*[out, retval]*/ ILiveLoadModel* *pVal);
	STDMETHOD(putref_Special)(/*[in]*/ ILiveLoadModel* newVal);
	STDMETHOD(get_Permit)(/*[out, retval]*/ ILiveLoadModel* *pVal);
	STDMETHOD(putref_Permit)(/*[in]*/ ILiveLoadModel* newVal);
	STDMETHOD(get_Fatigue)(/*[out, retval]*/ ILiveLoadModel* *pVal);
	STDMETHOD(putref_Fatigue)(/*[in]*/ ILiveLoadModel* newVal);
	STDMETHOD(get_Deflection)(/*[out, retval]*/ ILiveLoadModel* *pVal);
	STDMETHOD(putref_Deflection)(/*[in]*/ ILiveLoadModel* newVal);
	STDMETHOD(get_Design)(/*[out, retval]*/ ILiveLoadModel* *pVal);
	STDMETHOD(putref_Design)(/*[in]*/ ILiveLoadModel* newVal);

// ILBAMModelEvents
   STDMETHOD(OnModelChanged)(/*[in]*/ILBAMModel* Model, ChangeType change);

// ILiveLoadEvents
   STDMETHOD(OnLiveLoadChanged)(ILiveLoad* load, LiveLoadModelType lltype);

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
