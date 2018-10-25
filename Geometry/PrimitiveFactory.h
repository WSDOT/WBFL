///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// PrimitiveFactory.h : Declaration of the CPrimitiveFactory

#ifndef __PRIMITIVEFACTORY_H_
#define __PRIMITIVEFACTORY_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPrimitiveFactory
class ATL_NO_VTABLE CPrimitiveFactory : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPrimitiveFactory, &CLSID_PrimitiveFactory>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPrimitiveFactory,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IPoint2dFactory,
   public IPoint3dFactory,
   public ILine2dFactory,
   public ILineSegment2dFactory,
   public IStructuredStorage2,
   public IPersistImpl<CPrimitiveFactory>
{
public:
	CPrimitiveFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PRIMITIVEFACTORY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPrimitiveFactory)
	COM_INTERFACE_ENTRY(IPoint2dFactory)
	COM_INTERFACE_ENTRY(IPoint3dFactory)
   COM_INTERFACE_ENTRY(ILine2dFactory)
   COM_INTERFACE_ENTRY(ILineSegment2dFactory)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPoint2dFactory
public:
	STDMETHOD(CreatePoint)(/*[out,retval]*/IPoint2d** ppPoint);
   STDMETHOD(get_StructuredStorage)(/*[out, retval]*/ IStructuredStorage2* *pStrStg);

// IPoint3dFactory
public:
	STDMETHOD(CreatePoint)(/*[out,retval]*/IPoint3d** ppPoint);

// ILine2dFactory
public:
	STDMETHOD(CreateLine)(/*[out,retval]*/ILine2d** ppLine);

// ILineSegment2dFactory
public:
	STDMETHOD(CreateLineSegment)(/*[out,retval]*/ILineSegment2d** ppLineSeg);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);
};

#endif //__PRIMITIVEFACTORY_H_
