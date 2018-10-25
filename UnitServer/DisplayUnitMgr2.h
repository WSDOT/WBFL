///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
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

// DisplayUnitMgr2.h : Declaration of the CDisplayUnitMgr2

#ifndef __DISPLAYUNITMGR2_H_
#define __DISPLAYUNITMGR2_H_

#include "resource.h"       // main symbols

#include <vector>
#include <map>
#include <string>
#include "WbflUnitServerCP.h"

typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT,VARIANT,_Copy<VARIANT>, std::vector<CComVariant> > EnumDisplayUnitGroups2;
typedef ICollectionOnSTLImpl<IDisplayUnitMgr2,std::vector<CComVariant>,VARIANT,_Copy<VARIANT>,EnumDisplayUnitGroups2> IDisplayUnitGroup2Collection;

/////////////////////////////////////////////////////////////////////////////
// CDisplayUnitMgr2
class ATL_NO_VTABLE CDisplayUnitMgr2 : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CDisplayUnitMgr2,CComObjectRootEx<CComSingleThreadModel> >,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CDisplayUnitMgr2>,
   public IObjectSafetyImpl<CDisplayUnitMgr2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IDisplayUnitGroupEvents,
	public IDisplayUnitGroup2Collection,
	public CProxyDDisplayUnitMgrEvents< CDisplayUnitMgr2 >
{
public:
	CDisplayUnitMgr2()
	{
	}

   void Init(IUnitServer* pUnitServer);

   void FinalRelease();

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDisplayUnitMgr2)
	COM_INTERFACE_ENTRY(IDisplayUnitMgr2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IDisplayUnitGroupEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDisplayUnitMgr2)
CONNECTION_POINT_ENTRY(IID_IDisplayUnitMgrEvents)
END_CONNECTION_POINT_MAP()

private:
   std::map<std::_tstring,DWORD> m_GroupCookies;
   CComPtr<IUnitServer> m_pUnitServer;

   void UnadviseDisplayUnitGroup(IDisplayUnitGroup* pGroup);
   void UnadviseAll();

   HRESULT BadDisplayUnitGroupError(BSTR name);


// ISupportErrorInfo
public:
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IDisplayUnitMgr2
public:
   STDMETHOD(get_Item)(/*[in]*/ BSTR bstrGroup, /*[out, retval]*/ IDisplayUnitGroup** retval);
   //STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval);
   STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType* retval);
   STDMETHOD(Add)(/*[in]*/BSTR bstrGroup,/*[in]*/ BSTR bstrUnitType,/*[out,retval]*/ IDisplayUnitGroup** newGroup);
   STDMETHOD(Clear)();
   STDMETHOD(Remove)(BSTR bstrGroup);
   STDMETHOD(get__EnumDisplayUnitGroups)(/*[out,retval]*/ IEnumDisplayUnitGroups** enumDisplayUnitGroups);

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

#endif //__DISPLAYUNITMGR2_H_
