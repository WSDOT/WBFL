///////////////////////////////////////////////////////////////////////
// LBAM Utility - Longitindal Bridge Analysis Model
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

// LBAMFactory.h : Declaration of the CLBAMFactory

#ifndef __LBAMFACTORY_H_
#define __LBAMFACTORY_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLBAMFactory
class ATL_NO_VTABLE CLBAMFactory : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLBAMFactory, &CLSID_LRFDFactory>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CLBAMFactory,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ILBAMLRFDFactory3
{
public:
	CLBAMFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LBAMFACTORY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLBAMFactory)
	COM_INTERFACE_ENTRY(ILBAMLRFDFactory3)
	COM_INTERFACE_ENTRY(ILBAMLRFDFactory2)
	COM_INTERFACE_ENTRY(ILBAMLRFDFactory)
	COM_INTERFACE_ENTRY(ILBAMFactory)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILBAMFactory
public:
	STDMETHOD(CreateSimpleModel)(/*[in]*/IDblArray* SpanLengths, /*[in]*/Float64 E, /*[in]*/Float64 A, /*[in]*/Float64 I, /*[in]*/Float64 Depth, /*[out,retval]*/ILBAMModel** newModel) override;
	STDMETHOD(GetSupportIDsForStage)(/*[in]*/ILBAMModel* pModel, /*[in]*/BSTR stage, /*[out]*/IIDArray* *supportIDs) override;
   STDMETHOD(MapLoadGroupToLoadCase)(/*[in]*/ILBAMModel* pModel,/*[in]*/ BSTR lgName,/*[in]*/ BSTR lgDesc,/*[in]*/ BSTR lcName) override;
   STDMETHOD(CreateSelfWeightDeadLoad)(/*[in]*/ILBAMModel* pModel,/*[in]*/BSTR stage,/*[in]*/BSTR lgName,/*[in]*/Float64 unitWgt,/*[in]*/Float64 E) override;
	STDMETHOD(GetSuperstructurePOIs)(/*[in]*/ILBAMModel* Model, /*[out,retval]*/IIDArray* *PoiIDs, /*[out]*/IDblArray* *PoiLocations) override;
	STDMETHOD(GeneratePOIsOnSuperstructure)(/*[in]*/ILBAMModel* Model, /*[in]*/PoiIDType startID, /*[in]*/PoiIDType Increment,/*[out,retval]*/PoiIDType* lastVal) override;

// ILBAMLRFDFactory
public:
	STDMETHOD(ConfigureLiveLoad)(/*[in]*/ILBAMModel* pModel,/*[in]*/VARIANT_BOOL includeLowBoy, /*[in]*/SpecUnitType units,/*[in]*/IUnitServer* pUnitServer) override;
   STDMETHOD(ConfigureLoadCombinations)(/*[in]*/ILBAMModel* pModel) override;

// ILBAMLRFDFactory2
public:
   STDMETHOD(ConfigureDesignLiveLoad)(/*[in]*/ILBAMModel* pModel, /*[in]*/ LiveLoadModelType llmt, /*[in]*/ Float64 imTruck,/*[in]*/Float64 imLane, /*[in]*/VARIANT_BOOL includeDualTrucks, /*[in]*/VARIANT_BOOL includeLowBoy, /*[in]*/SpecUnitType units,/*[in]*/IUnitServer* pUnitServer) override;
   STDMETHOD(ConfigureFatigueLiveLoad)(/*[in]*/ILBAMModel* pModel, /*[in]*/ LiveLoadModelType llmt,/*[in]*/ Float64 imTruck,/*[in]*/Float64 imLane,/*[in]*/SpecUnitType units,/*[in]*/IUnitServer* pUnitServer) override;
   STDMETHOD(ConfigureDeflectionLiveLoad)(/*[in]*/ILBAMModel* pModel, /*[in]*/ LiveLoadModelType llmt,/*[in]*/Float64 imTruck,/*[in]*/Float64 imLane,/*[in]*/SpecUnitType units,/*[in]*/IUnitServer* pUnitServer) override;

// ILBAMLRFDFactory3
public:
   STDMETHOD(ConfigureLegalLiveLoad)(/*[in]*/ILBAMModel* pModel, /*[in]*/ LiveLoadModelType llmt,
                                     /*[in]*/ Float64 imTruck,
                                     /*[in]*/Float64 imLane, 
                                     /*[in]*/VARIANT_BOOL includeType33, // 0.75Type3-3 + Lane
                                     /*[in]*/VARIANT_BOOL includeDualType33, // 2@0.75Type3-3 + Lane
                                     /*[in]*/VARIANT_BOOL removeLaneLoad, // removes lane from Type33 and Dual Type 33 and uses a factor of 1.0
                                     /*[in]*/IUnitServer* pUnitServer) override;

   STDMETHOD(ConfigureNotionalRatingLoad)(/*[in]*/ILBAMModel* pModel, /*[in]*/LiveLoadModelType llmt,
                                     /*[in]*/Float64 imTruck,
                                     /*[in]*/Float64 imLane, 
                                     /*[in]*/IUnitServer* pUnitServer) override;

   STDMETHOD(ConfigureEmergencyRatingLoad)(/*[in]*/ILBAMModel* pModel, /*[in]*/LiveLoadModelType llmt,
      /*[in]*/Float64 imTruck,
      /*[in]*/Float64 imLane,
      /*[in]*/VARIANT_BOOL bIncludeLiveLoad,
      /*[in]*/IUnitServer* pUnitServer) override;

   STDMETHOD(ConfigureSpecializedHaulingUnits)(/*[in]*/ILBAMModel* pModel, /*[in]*/LiveLoadModelType llmt,
                                     /*[in]*/Float64 imTruck,
                                     /*[in]*/Float64 imLane, 
                                     /*[in]*/IUnitServer* pUnitServer) override;

private:
	HRESULT CreatePOI(/*[in]*/PoiIDType ID, /*[in]*/MemberType Type, /*[in]*/MemberIDType memberID, /*[in]*/Float64 Location,/*[out,retval]*/IPOI** newPOI);
   HRESULT GetLiveLoadModel(ILBAMModel* pModel,LiveLoadModelType llmt,ILiveLoadModel** ppLiveLoadModel);

   void AddLoadCase(ILoadCases* loadCases, BSTR name, BSTR description);
   void ApplyTypicalLoadFactors(ILoadCombination* loadCombo, bool Strength4);
   void ApplyTypicalServiceLoadFactors(ILoadCombination* loadCombo);
   void ApplyTypicalLiveLoadFactors(ILoadCombination* loadCombo, Float64 factor);
   void ApplyTUCRSHLoadFactors(ILoadCombination* loadCombo, Float64 gradientFactor);
   void CreateSegmentLoad(MemberIDType mbrID,MemberType mbrType,IEnumSegmentItem* enum_segments,IDistributedLoads* loads,BSTR stage,BSTR lgName,Float64 unitWgt,Float64 E);
   void CreatePoiAlongSuperstructure(Float64 location, PoiIDType id, ISuperstructureMembers* pSsms, IPOI** pPoi);
   
   
   };

#endif //__LBAMFACTORY_H_
