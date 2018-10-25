///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2014  Washington State Department of Transportation
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

// ProfilePointFactory.h : Declaration of the CProfilePointFactory

#ifndef __PROFILEPOINTFACTORY_H_
#define __PROFILEPOINTFACTORY_H_
#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CProfilePointFactory
class ATL_NO_VTABLE CProfilePointFactory : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProfilePointFactory, &CLSID_ProfilePointFactory>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CProfilePointFactory,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IProfilePointFactory,
   public IStructuredStorage2,
   public IPersistImpl<CProfilePointFactory>
{
public:
	CProfilePointFactory()
	{
      m_pProfile = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PROFILEPOINTFACTORY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProfilePointFactory)
	COM_INTERFACE_ENTRY(IProfilePointFactory)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IProfilePointFactory
public:
   STDMETHOD(get_Profile)(IProfile* *pVal);
   STDMETHOD(putref_Profile)(IProfile* newVal);
	STDMETHOD(CreateProfilePoint)(/*[out,retval]*/IProfilePoint* *pVal);
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

private:
   IProfile* m_pProfile; // weak reference
};

#endif //__PROFILEPOINTFACTORY_H_
