///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright (C) 2008  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// SocketFactoryImpl.h: interface for the CSocketFactoryImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETFACTORYIMPL_H__D88A0193_DCD4_11D4_8B74_006097C68A9C__INCLUDED_)
#define AFX_SOCKETFACTORYIMPL_H__D88A0193_DCD4_11D4_8B74_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class ATL_NO_VTABLE CSocketFactoryImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSocketFactoryImpl, &CLSID_SocketFactory>,
   public iSocketFactory
{
public:
	CSocketFactoryImpl();
	virtual ~CSocketFactoryImpl();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_SOCKETFACTORY)

BEGIN_COM_MAP(CSocketFactoryImpl)
   COM_INTERFACE_ENTRY(iSocketFactory)
END_COM_MAP()

   // iSocketFactory
   STDMETHOD_(void,CreateSocket)(long id,IPoint2d* pos,iSocket** socket);
};


#endif // !defined(AFX_SOCKETFACTORYIMPL_H__D88A0193_DCD4_11D4_8B74_006097C68A9C__INCLUDED_)
