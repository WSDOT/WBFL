///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// CastingRegion.h : Declaration of the CCastingRegion

#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCastingRegion
class ATL_NO_VTABLE CCastingRegion :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCastingRegion, &CLSID_CastingRegion>,
	public ISupportErrorInfo,
	public ICastingRegion,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CCastingRegion,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CCastingRegion()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void Init(ICastingRegions* pParent, PierIDType startPierID, Float64 Xstart, PierIDType endPierID, Float64 Xend, IMaterial* pMaterial);

DECLARE_REGISTRY_RESOURCEID(IDR_CASTING_REGION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCastingRegion)
	COM_INTERFACE_ENTRY(ICastingRegion)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   ICastingRegions* m_pParent; // weak reference
   PierIDType m_StartPierID; // ID of pier anchoring start of region
   Float64 m_Xstart; // distance from start pier to starting region boundary
   PierIDType m_EndPierID; // ID of pier anchoring end of region
   Float64 m_Xend; // distance from end pier to ending region boundary
   CComPtr<IMaterial> m_Material;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICastingRegion
public:
   STDMETHOD(GetRange)(/*[out]*/Float64* pXbStart, /*[out]*/Float64* pXbEnd) override;
   STDMETHOD(ContainsPoint)(/*[in]*/ Float64 Xb, /*[out, retval]*/VARIANT_BOOL* pvbContainsPoint) override;
   STDMETHOD(Perimeter)(/*[in]*/CollectionIndexType nMinPointsPerSide,/*[out]*/IPoint2dCollection** ppPoints) override;
   STDMETHOD(putref_Material)(/*[in]*/IMaterial* pMaterial) override;
   STDMETHOD(get_Material)(/*[out, retval]*/IMaterial** ppMaterial) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};
