///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
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

// UnitSystem.cpp : Implementation of CUnitSystem
#include "stdafx.h"
#include "WBFLUnitServer.h"
#include "UnitSystem.h"
#include "UnitServerImp.h"
#include "DisplayUnitMgr.h"
#include "UnitModeController.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CUnitSystem
HRESULT CUnitSystem::FinalConstruct()
{
   HRESULT hr;
   //
   // Create instances of these three objects
   //
   CComObject<CUnitServerImp>* pUnitServer;
   hr = CComObject<CUnitServerImp>::CreateInstance( &pUnitServer );
   if (FAILED(hr) )
      return E_FAIL;

   m_pUnitServer = pUnitServer;

   CComObject<CUnitModeController>* pUnitModeController;
   hr = CComObject<CUnitModeController>::CreateInstance( &pUnitModeController );
   if (FAILED(hr) )
      return E_FAIL;

   m_pUnitModeController = pUnitModeController; // Calls AddRef()

   // DispUnitMgr has-a unit server and is an even sink for
   // unit mode controller
   CComObject<CDisplayUnitMgr>* pDisplayUnitMgr;
   hr = CComObject<CDisplayUnitMgr>::CreateInstance( &pDisplayUnitMgr );
   if ( FAILED(hr) )
      return E_FAIL;

   m_pDisplayUnitMgr = pDisplayUnitMgr; // Calls AddRef()
   pDisplayUnitMgr->Init(m_pUnitModeController,m_pUnitServer);

   // Setup Connection Points
   m_dwUMCCookie = AdviseSink(m_pUnitModeController,IID_IUnitModeControllerEvents);
   m_dwDUMCookie = AdviseSink(m_pDisplayUnitMgr,    IID_IDisplayUnitMgrEvents);
   m_dwUSCookie  = AdviseSink(m_pUnitServer,        IID_IUnitServerEventSink);

   return S_OK;
}

void CUnitSystem::FinalRelease()
{
   // Disconnect from connection points
   UnadviseSink(m_pUnitModeController,IID_IUnitModeControllerEvents, m_dwUMCCookie);
   UnadviseSink(m_pDisplayUnitMgr,    IID_IDisplayUnitMgrEvents,     m_dwDUMCookie);
   UnadviseSink(m_pUnitServer,        IID_IUnitServerEventSink,      m_dwUSCookie);
}

DWORD CUnitSystem::AdviseSink(IUnknown* pUnk,REFIID riid)
{
   DWORD dwCookie;
   CComPtr<IUnknown> p(pUnk);
   p.Advise(GetUnknown(),riid,&dwCookie);
   InternalRelease(); // Break circular reference
   return dwCookie;
}

void CUnitSystem::UnadviseSink(IUnknown* pUnk,REFIID riid,DWORD dwCookie)
{
   CComQIPtr<IConnectionPointContainer> pCPC(pUnk);
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( riid, &pCP );
   InternalAddRef(); // Counteract call to InternalRelease() in AdviseSink
   pCP->Unadvise( dwCookie );
}

STDMETHODIMP CUnitSystem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IUnitSystem,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CUnitSystem::get_UnitServer(IUnitServer **pVal)
{
   CHECK_RETOBJ(pVal);
   m_pUnitServer.QueryInterface(pVal);
	return S_OK;
}

STDMETHODIMP CUnitSystem::get_DisplayUnitMgr(IDisplayUnitMgr **pVal)
{
   CHECK_RETOBJ(pVal);
   m_pDisplayUnitMgr.QueryInterface(pVal);
	return S_OK;
}

STDMETHODIMP CUnitSystem::get_UnitModeController(IUnitModeController **pVal)
{
   CHECK_RETOBJ(pVal);
   m_pUnitModeController.QueryInterface(pVal);
	return S_OK;
}
