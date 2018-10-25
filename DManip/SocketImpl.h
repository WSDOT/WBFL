///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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

// SocketImpl.h: interface for the CSocketImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETIMPL_H__D88A0192_DCD4_11D4_8B74_006097C68A9C__INCLUDED_)
#define AFX_SOCKETIMPL_H__D88A0192_DCD4_11D4_8B74_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include <map>

class ATL_NO_VTABLE CSocketImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSocketImpl,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSocketImpl, &CLSID_Socket>,
   public iSocket
{
public:
	CSocketImpl();
	virtual ~CSocketImpl();
   HRESULT FinalConstruct();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_SOCKET)

BEGIN_COM_MAP(CSocketImpl)
   COM_INTERFACE_ENTRY(iSocket)
END_COM_MAP()

   // iSocket
   STDMETHOD_(void,SetID)(IDType id);
   STDMETHOD_(IDType,GetID)();
   STDMETHOD_(void,SetPosition)(IPoint2d* pos);
   STDMETHOD_(void,GetPosition)(IPoint2d* *pos);
   STDMETHOD_(void,Move)(ISize2d* offset);

   STDMETHOD_(void,Connect)(iPlug* plug,DWORD* pdwCookie);
   STDMETHOD_(void,Disconnect)(DWORD dwCookie);
   STDMETHOD_(void,DisconnectAll)();

   STDMETHOD_(void,Draw)(CDC* pDC,iCoordinateMap* pMap);

   STDMETHOD_(void,SetConnectable)(iConnectable* pConnectable);
   STDMETHOD_(void,GetConnectable)(iConnectable** connectable);

private:
   IDType m_ID;
   CComPtr<IPoint2d> m_Position;
   static DWORD ms_dwCookies;
   typedef std::map<DWORD,CComPtr<iPlug> > PlugContainer;
   PlugContainer m_Plugs;

   // weak reference
   iConnectable* m_pConnectable;
};

#endif // !defined(AFX_SOCKETIMPL_H__D88A0192_DCD4_11D4_8B74_006097C68A9C__INCLUDED_)
