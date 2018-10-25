///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2015  Washington State Department of Transportation
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

// CrossBeamRebarPattern.h : Declaration of the CCrossBeamRebarPattern

#pragma once

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CRebarRowPattern
class ATL_NO_VTABLE CCrossBeamRebarPattern : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CCrossBeamRebarPattern,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CCrossBeamRebarPattern, &CLSID_CrossBeamRebarPattern>,
	public ISupportErrorInfo,
	public ICrossBeamRebarPattern,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CCrossBeamRebarPattern,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CCrossBeamRebarPattern()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_CROSSBEAMREBARPATTERN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCrossBeamRebarPattern)
	COM_INTERFACE_ENTRY(ICrossBeamRebarPattern)
	COM_INTERFACE_ENTRY(IRebarPattern)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   CComPtr<IRebar> m_Rebar;
   CollectionIndexType m_Count;
   Float64 m_Spacing;
   Float64 m_Cover;
   CrossBeamRebarDatum m_Datum;
   HookType m_HookType[2];

   ICrossBeam* m_pCrossBeam; // weak reference
   IRebarLayoutItem* m_pRebarLayoutItem; // weak reference

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IRebarPattern
public:
	STDMETHOD(putref_Rebar)(/*[in]*/IRebar* rebar);
	STDMETHOD(get_Rebar)(/*[out,retval]*/IRebar** rebar);
   STDMETHOD(putref_RebarLayoutItem)(/*[in]*/IRebarLayoutItem* rebarLayoutItem);
   STDMETHOD(put_Hook)(/*[in]*/DirectionType side,/*[in]*/HookType hook);
   STDMETHOD(get_Hook)(/*[in]*/DirectionType side,/*[out,retval]*/HookType* hook);
	STDMETHOD(get_Count)(/*[out,retval]*/CollectionIndexType* count);
	STDMETHOD(get_Location)(/*[in]*/Float64 distFromStartOfPattern,/*[in]*/CollectionIndexType barIdx,/*[out,retval]*/IPoint2d** location);
   STDMETHOD(get_Profile)(/*[in]*/IndexType barIdx,/*[out,retval]*/IPoint2dCollection** ppProfile);

// ICrossBeamRebarPattern
public:
   STDMETHOD(putref_CrossBeam)(/*[in]*/ICrossBeam* pXBeam);
   STDMETHOD(get_CrossBeam)(/*[out,retval]*/ICrossBeam** ppXBeam);
   STDMETHOD(put_Datum)(/*[in]*/CrossBeamRebarDatum datum);
   STDMETHOD(get_Datum)(/*[out,retval]*/CrossBeamRebarDatum* pDatum);
   STDMETHOD(put_Cover)(/*[in]*/Float64 cover);
   STDMETHOD(get_Cover)(/*[out,retval]*/Float64* pCover);
	STDMETHOD(put_Count)(/*[in]*/RowIndexType count);
	STDMETHOD(put_Spacing)(/*[in]*/Float64 spacing);
	STDMETHOD(get_Spacing)(/*[out,retval]*/Float64* spacing);
   STDMETHOD(get_DisplayProfile)(/*[in]*/IndexType barIdx,/*[out,retval]*/IPoint2dCollection** ppProfile);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);
};
