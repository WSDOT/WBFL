///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2016  Washington State Department of Transportation
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

// HorzCurveFactory.h : Declaration of the CHorzCurveFactory

#ifndef __HORZCURVEFACTORY_H_
#define __HORZCURVEFACTORY_H_
#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHorzCurveFactory
class ATL_NO_VTABLE CHorzCurveFactory : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHorzCurveFactory, &CLSID_HorzCurveFactory>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CHorzCurveFactory,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IHorzCurveFactory,
   public IStructuredStorage2,
   public IPersistImpl<CHorzCurveFactory>
{
public:
	CHorzCurveFactory()
	{
	}


DECLARE_REGISTRY_RESOURCEID(IDR_HORZCURVEFACTORY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHorzCurveFactory)
	COM_INTERFACE_ENTRY(IHorzCurveFactory)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IHorzCurveFactory
public:
	STDMETHOD(CreateHorzCurve)(/*[out,retval]*/ IHorzCurve* *pVal);
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);
};

#endif //__HORZCURVEFACTORY_H_
