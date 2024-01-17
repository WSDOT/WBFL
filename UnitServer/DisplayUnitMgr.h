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

// DisplayUnitMgr.h : Declaration of the CDisplayUnitMgr

#ifndef __DISPLAYUNITMGR_H_
#define __DISPLAYUNITMGR_H_

#include "resource.h"       // main symbols

#include <vector>
#include <map>
#include <string>
#include "WbflUnitServerCP.h"

using EnumDisplayUnitGroups = CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT>, std::vector<CComVariant> >;
using IDisplayUnitGroupCollection = ICollectionOnSTLImpl<IDisplayUnitMgr,std::vector<CComVariant>,VARIANT,_Copy<VARIANT>,EnumDisplayUnitGroups>;

/////////////////////////////////////////////////////////////////////////////
// CDisplayUnitMgr
class ATL_NO_VTABLE CDisplayUnitMgr : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CDisplayUnitMgr,CComObjectRootEx<CComSingleThreadModel> >,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CDisplayUnitMgr>,
   public IObjectSafetyImpl<CDisplayUnitMgr,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IDisplayUnitGroupEvents,
	public IDisplayUnitGroupCollection,
	public CProxyDDisplayUnitMgrEvents< CDisplayUnitMgr >
{
public:
	CDisplayUnitMgr()
	{
	}

  void FinalRelease();

  void Init(IUnitModeController* pUMC,IUnitServer* pUnitServer)
  {
      ATLASSERT( pUMC != 0 );
      ATLASSERT( pUnitServer != 0);

      m_pUMC = pUMC;
      m_pUnitServer = pUnitServer;
   }

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDisplayUnitMgr)
	COM_INTERFACE_ENTRY(IDisplayUnitMgr)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IDisplayUnitGroupEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDisplayUnitMgr)
CONNECTION_POINT_ENTRY(IID_IDisplayUnitMgrEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<IUnitServer> m_pUnitServer;
   CComPtr<IUnitModeController> m_pUMC;

   std::map<std::_tstring,DWORD> m_GroupCookies;

   void UnadviseDisplayUnitGroup(IDisplayUnitGroup* pGroup);
   void UnadviseAll();

   HRESULT BadDisplayUnitGroupError(BSTR name);


// ISupportErrorInfo
public:
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IDisplayUnitMgr
public:
   STDMETHOD(get_Item)(/*[in]*/ BSTR bstrGroup, /*[out, retval]*/ IDisplayUnitGroup** retval) override;
   //STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) override;
   STDMETHOD(get_Count)(/*[out, retval]*/ IndexType* retval) override;
   STDMETHOD(Add)(/*[in]*/BSTR bstrGroup,/*[in]*/ BSTR bstrUnitType,/*[out,retval]*/ IDisplayUnitGroup** newGroup) override;
   STDMETHOD(Clear)() override;
   STDMETHOD(Remove)(BSTR bstrGroup) override;
	STDMETHOD(Format)(/*[in]*/ Float64 val,/*[in]*/ BSTR group,/*[in]*/ VARIANT_BOOL bShowUnitTag,/*[out,retval]*/BSTR* fmtString) override;
   STDMETHOD(get__EnumDisplayUnitGroups)(/*[out,retval]*/ IEnumDisplayUnitGroups** enumDisplayUnitGroups) override;
	STDMETHOD(get_Tag)(/*[in]*/ BSTR group,/*[out,retval]*/BSTR* tag) override;
	STDMETHOD(ConvertToDisplayUnits)(/*[in]*/ Float64 value,/*[in]*/ BSTR group,/*[out,retval]*/Float64* result) override;
	STDMETHOD(ConvertFromDisplayUnits)(/*[in]*/ Float64 value,/*[in]*/ BSTR group,/*[out,retval]*/Float64* result) override;

// IDisplayUnitGroupEvents
public:
   STDMETHOD(OnFormatChanged)(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/IDisplayUnit* displayUnit)
   {
      Fire_OnFormatChanged(group,displayUnit);
      return S_OK;
   }

   STDMETHOD(OnDisplayUnitCreated)(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/IDisplayUnit* displayUnit)
   {
      Fire_OnDisplayUnitCreated(group,displayUnit);
      return S_OK;
   }

   STDMETHOD(OnDisplayUnitRemoved)(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/BSTR displayUnit)
   {
      Fire_OnDisplayUnitRemoved(group,displayUnit);
      return S_OK;
   }

   STDMETHOD(OnDisplayUnitGroupCleared)(/*[in]*/ IDisplayUnitGroup* group)
   {
      Fire_OnDisplayUnitGroupCleared(group);
      return S_OK;
   }
};

#endif //__DISPLAYUNITMGR_H_
