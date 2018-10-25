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

// AppUnitSystem.h : Declaration of the CAppUnitSystem

#ifndef __APPUNITSYSTEM_H_
#define __APPUNITSYSTEM_H_

#include "resource.h"       // main symbols
#include "UnitServerImp.h"
#include "DisplayUnitMgr2.h"
#include "WbflUnitServerCP.h"

/////////////////////////////////////////////////////////////////////////////
// CAppUnitSystem
class ATL_NO_VTABLE CAppUnitSystem : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CAppUnitSystem,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CAppUnitSystem, &CLSID_AppUnitSystem>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CAppUnitSystem>,
   public IObjectSafetyImpl<CAppUnitSystem,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IUnitServerEventSink,
	public IDisplayUnitMgrEvents,
	public IAppUnitSystem,
	public CProxyDUnitSystemEvents< CAppUnitSystem >
{
public:
	CAppUnitSystem()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_APPUNITSYSTEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAppUnitSystem)
	COM_INTERFACE_ENTRY(IAppUnitSystem)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IUnitServerEventSink)
   COM_INTERFACE_ENTRY(IDisplayUnitMgrEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CAppUnitSystem)
CONNECTION_POINT_ENTRY(IID_IUnitSystemEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<IUnitServer> m_pUnitServer;
   CComPtr<IDisplayUnitMgr2> m_pDispUnitMgr;

   DWORD m_dwUnitServerCookie;
   DWORD m_dwDispUnitMgrCookie;

   DWORD AdviseSink(IUnknown* pUnk,REFIID riid);
   void UnadviseSink(IUnknown* pUnk,REFIID riid,DWORD dwCookie);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAppUnitSystem
public:
	STDMETHOD(get_DisplayUnitMgr)(/*[out, retval]*/ IDisplayUnitMgr2* *pVal);
	STDMETHOD(get_UnitServer)(/*[out, retval]*/ IUnitServer* *pVal);
   STDMETHOD(ConvertToBaseUnits)(/*[in]*/Float64 value,/*[in]*/VARIANT fromUnit,/*[out,retval]*/Float64* retval);
   STDMETHOD(ConvertFromBaseUnits)(/*[in]*/Float64 value,/*[in]*/VARIANT toUnit,/*[out,retval]*/Float64* retval);

// IUnitServerEventSink
	STDMETHOD(OnUnitAdded)(IUnitType * UnitType, IUnit * unit)
	{
      Fire_OnUnitServerChanged();
      return S_OK;
	}
	STDMETHOD(OnUnitRemoved)(IUnitType * UnitType, BSTR unit)
	{
      Fire_OnUnitServerChanged();
      return S_OK;
	}
	STDMETHOD(OnUnitsCleared)(IUnitType * UnitType)
	{
      Fire_OnUnitServerChanged();
      return S_OK;
	}
	STDMETHOD(OnUnitTypeAdded)(IUnitType * UnitType)
	{
      Fire_OnUnitServerChanged();
      return S_OK;
	}
	STDMETHOD(OnUnitTypeRemoved)(BSTR UnitType)
	{
      Fire_OnUnitServerChanged();
      return S_OK;
	}
	STDMETHOD(OnUnitTypesCleared)()
	{
      Fire_OnUnitServerChanged();
      return S_OK;
	}
// IDisplayUnitMgrEvents
	STDMETHOD(OnFormatChanged)(IDisplayUnitGroup * group, IDisplayUnit * displayUnit)
	{
      Fire_OnUpdateDisplay();
      return S_OK;
	}
	STDMETHOD(OnDisplayUnitCreated)(IDisplayUnitGroup * group, IDisplayUnit * displayUnit)
	{
      // Gobble-up Event
      return S_OK;
	}
	STDMETHOD(OnDisplayUnitRemoved)(IDisplayUnitGroup * group, BSTR displayUnit)
	{
      // Gobble-up Event
      return S_OK;
	}
	STDMETHOD(OnDisplayUnitGroupCleared)(IDisplayUnitGroup * group)
	{
      // Gobble-up Event
      return S_OK;
	}
	STDMETHOD(OnDisplayUnitGroupCreated)(IDisplayUnitGroup * group)
	{
      // Gobble-up Event
      return S_OK;
	}
	STDMETHOD(OnDisplayUnitGroupRemoved)(BSTR group)
	{
      // Gobble-up Event
      return S_OK;
	}
	STDMETHOD(OnDisplayUnitGroupsCleared)()
	{
      // Gobble-up Event
      return S_OK;
	}
};

#endif //__APPUNITSYSTEM_H_
