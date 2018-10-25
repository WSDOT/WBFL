///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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
   public IObjectSafetyImpl<CEdgePathStrategy,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CEdgePathStrategy()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

private:
   CComPtr<IPath> m_Path;

public:
DECLARE_REGISTRY_RESOURCEID(IDR_EDGEPATHSTRATEGY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEdgePathStrategy)
	COM_INTERFACE_ENTRY(IEdgePathStrategy)
	COM_INTERFACE_ENTRY(IOverhangPathStrategy)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

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
};

#endif //__EDGEPATHSTRATEGY_H_
