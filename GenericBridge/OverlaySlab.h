///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// OverlaySlab.h : Declaration of the COverlaySlab

#ifndef __OVERLAYSLAB_H_
#define __OVERLAYSLAB_H_

#include "resource.h"       // main symbols
#include "BridgeDeckImpl.h"

/////////////////////////////////////////////////////////////////////////////
// COverlaySlab
class ATL_NO_VTABLE COverlaySlab : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<COverlaySlab,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<COverlaySlab, &CLSID_OverlaySlab>,
	public ISupportErrorInfo,
	public IStructuredStorage2,
	public IConnectionPointContainerImpl<COverlaySlab>,
   public IObjectSafetyImpl<COverlaySlab,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IOverlaySlab,
   public IBridgeDeckImpl<COverlaySlab>,
   public IOverhangPathStrategyEvents
{
public:
   COverlaySlab()
	{
      m_GrossDepth = 0;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

private:
   Float64 m_GrossDepth;

   CComPtr<IOverhangPathStrategy> m_LeftPathStrategy;
   CComPtr<IOverhangPathStrategy> m_RightPathStrategy;
   DWORD m_dwLeftPathStrategyCookie;
   DWORD m_dwRightPathStrategyCookie;

public:
DECLARE_REGISTRY_RESOURCEID(IDR_OVERLAYSLAB)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(COverlaySlab)
	COM_INTERFACE_ENTRY(IOverlaySlab)
	COM_INTERFACE_ENTRY(IBridgeDeck)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IOverhangPathStrategyEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(COverlaySlab)
   CONNECTION_POINT_ENTRY(IID_IBridgeDeckEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IBridgeDeck
public:
   STDMETHOD(get_StructuralDepth)(/*[out,retval]*/Float64* depth);
   STDMETHOD(get_GrossDepth)(/*[out,retval]*/Float64* depth);

// IOverlaySlab
public:
	STDMETHOD(put_GrossDepth)(/*[in]*/Float64 depth);

	STDMETHOD(get_LeftOverhangPathStrategy)(/*[out,retval]*/IOverhangPathStrategy** strategy);
	STDMETHOD(putref_LeftOverhangPathStrategy)(/*[in]*/IOverhangPathStrategy* strategy);
	STDMETHOD(get_RightOverhangPathStrategy)(/*[out,retval]*/IOverhangPathStrategy** strategy);
	STDMETHOD(putref_RightOverhangPathStrategy)(/*[in]*/IOverhangPathStrategy* strategy);

	STDMETHOD(get_LeftOverhangPath)(/*[out,retval]*/IPath** Path);
	STDMETHOD(get_RightOverhangPath)(/*[out,retval]*/IPath** Path);

   STDMETHOD(Clone)(/*[out,retval]*/IBridgeDeck** clone);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);


// IOverhangPathStrategyEvents
public:
   STDMETHOD(OnStrategyChanged)()
   {
      Fire_OnBridgeDeckChanged(this);
      return S_OK;
   }
};

#endif //__OVERLAYSLAB_H_
