///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2012  Washington State Department of Transportation
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

// EdgePathStrategy.h : Declaration of the CEdgePathStrategy

#ifndef __EDGEPATHSTRATEGY_H_
#define __EDGEPATHSTRATEGY_H_

#include "resource.h"       // main symbols
#include "GenericBridgeCP.h"

/////////////////////////////////////////////////////////////////////////////
// CEdgePathStrategy
class ATL_NO_VTABLE CEdgePathStrategy : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CEdgePathStrategy,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CEdgePathStrategy, &CLSID_EdgePathStrategy>,
	public ISupportErrorInfo,
   public IEdgePathStrategy,
   public IStructuredStorage2,
   public IOverhangPathStrategy,
   public CProxyDOverhangPathStrategyEvents<CEdgePathStrategy>,
   public IObjectSafetyImpl<CEdgePathStrategy,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IConnectionPointContainerImpl<CEdgePathStrategy>,
   public IPathEvents
{
public:
   CEdgePathStrategy()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

private:
   CComPtr<IPath> m_Path;
   DWORD m_dwPathCookie;

   void Advise(IPath* path,DWORD* pdwCookie);
   void Unadvise(IPath* path,DWORD dwCookie);

public:
DECLARE_REGISTRY_RESOURCEID(IDR_EDGEPATHSTRATEGY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEdgePathStrategy)
	COM_INTERFACE_ENTRY(IEdgePathStrategy)
	COM_INTERFACE_ENTRY(IOverhangPathStrategy)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPathEvents)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CEdgePathStrategy)
	CONNECTION_POINT_ENTRY(IID_IOverhangPathStrategyEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IOverhangPathStrategy
public:
   STDMETHOD(get_Path)(/*[out,retval]*/IPath** path);

// IEdgePathStrategy
public:
   STDMETHOD(putref_Path)(/*[in]*/IPath* path);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);

// IPathEvents
public:
   STDMETHOD(OnPathChanged)(/*[in]*/ IPath* path)
   {
      Fire_OnStrategyChanged();
      return S_OK;
   }

	STDMETHOD(OnProfileChanged)(/*[in]*/ IProfile* profile)
   {
      // do nothing... it doesn't matter if the profile changes
      return S_OK;
   }
};

#endif //__EDGEPATHSTRATEGY_H_
