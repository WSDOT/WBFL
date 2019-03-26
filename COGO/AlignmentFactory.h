///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2019  Washington State Department of Transportation
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

// AlignmentFactory.h : Declaration of the CAlignmentFactory

#ifndef __ALIGNMENTFACTORY_H_
#define __ALIGNMENTFACTORY_H_
#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAlignmentFactory
class ATL_NO_VTABLE CAlignmentFactory : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAlignmentFactory, &CLSID_AlignmentFactory>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CAlignmentFactory,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IAlignmentFactory,
   public IStructuredStorage2,
   public IPersistImpl<CAlignmentFactory>
{
public:
	CAlignmentFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ALIGNMENTFACTORY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAlignmentFactory)
	COM_INTERFACE_ENTRY(IAlignmentFactory)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IAlignmentFactory
public:
	STDMETHOD(CreateAlignment)(/*[out,retval]*/IAlignment* *pVal) override;
	STDMETHOD(IsValidType)(/*[in]*/IAlignment* path,/*[out,retval]*/VARIANT_BOOL* bIsValid) override;
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;
};

#endif //__ALIGNMENTFACTORY_H_
