///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// UnitSystem.h : Declaration of the CUnitSystem

#ifndef __UNITSYSTEM_H_
#define __UNITSYSTEM_H_

#include "resource.h"       // main symbols
#include "WbflUnitServerCP.h"

/////////////////////////////////////////////////////////////////////////////
// CUnitSystem
class ATL_NO_VTABLE CUnitSystem : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CUnitSystem,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CUnitSystem, &CLSID_UnitSystem>,
   public ISupportErrorInfo,
   public IConnectionPointContainerImpl<CUnitSystem>,
   public IObjectSafetyImpl<CUnitSystem,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IUnitServerEvents,
   public IUnitModeControllerEvents,
   public IDisplayUnitMgrEvents,
	public IUnitSystem,
	public CProxyDUnitSystemEvents< CUnitSystem >
{
public:
	CUnitSystem()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_UNITSYSTEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUnitSystem)
	COM_INTERFACE_ENTRY(IUnitSystem)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IUnitServerEvents)
   COM_INTERFACE_ENTRY(IUnitModeControllerEvents)
   COM_INTERFACE_ENTRY(IDisplayUnitMgrEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CUnitSystem)
CONNECTION_POINT_ENTRY(IID_IUnitSystemEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<IUnitServer> m_pUnitServer;
   CComPtr<IDisplayUnitMgr> m_pDisplayUnitMgr;
   CComPtr<IUnitModeController> m_pUnitModeController;

   DWORD m_dwUMCCookie;
   DWORD m_dwDUMCookie;
   DWORD m_dwUSCookie;

   DWORD AdviseSink(IUnknown* pUnk,REFIID riid);
   void UnadviseSink(IUnknown* pUnk,REFIID riid,DWORD dwCookie);

// ISupportErrorInfo
public:
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IUnitSystem
public:
	STDMETHOD(get_UnitModeController)(/*[out, retval]*/ IUnitModeController* *pVal) override;
	STDMETHOD(get_DisplayUnitMgr)(/*[out, retval]*/ IDisplayUnitMgr* *pVal) override;
	STDMETHOD(get_UnitServer)(/*[out, retval]*/ IUnitServer* *pVal) override;

// IUnitServerEvents,
public:
   STDMETHOD(OnUnitAdded)(/*[in]*/IUnitType* unitType,/*[in]*/IUnit* unit) override
   {
      Fire_OnUnitServerChanged();
      return S_OK;
   }

   STDMETHOD(OnUnitRemoved)(/*[in]*/IUnitType* unitType,/*[in]*/BSTR unit) override
   {
      Fire_OnUnitServerChanged();
      return S_OK;
   }

   STDMETHOD(OnUnitsCleared)(/*[in]*/IUnitType* unitType) override
   {
      Fire_OnUnitServerChanged();
      return S_OK;
   }

   STDMETHOD(OnUnitTypeAdded)(/*[in]*/IUnitType* unitType) override
   {
      Fire_OnUnitServerChanged();
      return S_OK;
   }

   STDMETHOD(OnUnitTypeRemoved)(/*[in]*/BSTR unitType) override
   {
      Fire_OnUnitServerChanged();
      return S_OK;
   }

   STDMETHOD(OnUnitTypesCleared)() override
   {
      Fire_OnUnitServerChanged();
      return S_OK;
   }

// IUnitModeControllerEvents,
public:
	STDMETHOD(OnUnitModeChanged)(/*[in]*/UnitModeType newMode) override
   {
      Fire_OnUpdateDisplay();
      return S_OK;
   }

// IDisplayUnitMgrEvents,
public:
   STDMETHOD(OnFormatChanged)(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/IDisplayUnit* displayUnit) override
   {
      Fire_OnUpdateDisplay();
      return S_OK;
   }

   STDMETHOD(OnDisplayUnitCreated)(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/IDisplayUnit* displayUnit) override
   {
      // Gobble-up Event
      return S_OK;
   }

   STDMETHOD(OnDisplayUnitRemoved)(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/BSTR displayUnit) override
   {
      // Gobble-up Event
      return S_OK;
   }

   STDMETHOD(OnDisplayUnitGroupCleared)(/*[in]*/ IDisplayUnitGroup* group) override
   {
      // Gobble-up Event
      return S_OK;
   }

   STDMETHOD(OnDisplayUnitGroupCreated)(/*[in]*/ IDisplayUnitGroup* group) override
   {
      // Gobble-up Event
      return S_OK;
   }

   STDMETHOD(OnDisplayUnitGroupRemoved)(/*[in]*/ BSTR group) override
   {
      // Gobble-up Event
      return S_OK;
   }

   STDMETHOD(OnDisplayUnitGroupsCleared)() override
   {
      // Gobble-up Event
      return S_OK;
   }
};

#endif //__UNITSYSTEM_H_
