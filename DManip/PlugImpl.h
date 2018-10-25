///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2016  Washington State Department of Transportation
//                        Bridge and Structures Office
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

// PlugImpl.h: interface for the CPlugImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLUGIMPL_H__D88A0195_DCD4_11D4_8B74_006097C68A9C__INCLUDED_)
#define AFX_PLUGIMPL_H__D88A0195_DCD4_11D4_8B74_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include <vector>

class ATL_NO_VTABLE CPlugImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPlugImpl, &CLSID_Plug>,
   public iPlug
{
public:
	CPlugImpl();
	virtual ~CPlugImpl();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_PLUG)

BEGIN_COM_MAP(CPlugImpl)
   COM_INTERFACE_ENTRY(iPlug)
END_COM_MAP()

   // iPlug
   STDMETHOD_(void,Notify)(iSocket* socket);
   STDMETHOD_(void,OnRemove)(iSocket* socket);
   STDMETHOD_(void,SetSocket)(iSocket* pSocket);
   STDMETHOD_(void,GetSocket)(iSocket** socket);
   STDMETHOD_(void,Register)(iPlugEvents* pEventSink);

protected:
   DWORD m_dwCookie;
   CComPtr<iSocket> m_pSocket;

   std::vector<iPlugEvents* > m_EventSinks;
};

#endif // !defined(AFX_PLUGIMPL_H__D88A0195_DCD4_11D4_8B74_006097C68A9C__INCLUDED_)
