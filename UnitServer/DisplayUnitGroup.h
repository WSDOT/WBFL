///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// DisplayUnitGroup.h : Declaration of the CDisplayUnitGroup

#ifndef __DISPLAYUNITGROUP_H_
#define __DISPLAYUNITGROUP_H_

#include "resource.h"       // main symbols

#include <vector>
#include <map>
#include <string>
#include "WbflUnitServerCP.h"

typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT,VARIANT,_Copy<VARIANT>, std::vector<CComVariant> > EnumDisplayUnits;
typedef ICollectionOnSTLImpl<IDisplayUnitGroup,std::vector<CComVariant>,VARIANT,_Copy<VARIANT>,EnumDisplayUnits> IDisplayUnitCollection;

/////////////////////////////////////////////////////////////////////////////
// CDisplayUnitGroup
class ATL_NO_VTABLE CDisplayUnitGroup : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CDisplayUnitGroup,CComObjectRootEx<CComSingleThreadModel> >,
   public ISupportErrorInfoImpl<&IID_IDisplayUnitGroup>,
   public IConnectionPointContainerImpl<CDisplayUnitGroup>,
   public IObjectSafetyImpl<CDisplayUnitGroup,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IDisplayUnitEvents,
	public IDisplayUnitCollection,
	public CProxyDDisplayUnitGroupEvents< CDisplayUnitGroup >
{
public:
	CDisplayUnitGroup() 
	{
	}
   
   void FinalRelease();

   void Init(BSTR bstrGroup,IUnitType* pUnitType)
   {
      pUnitType->get_UnitServer(&m_pUnitServer);
      m_pUnitType   = pUnitType;
      m_bstrName    = bstrGroup;

      // Connect to the unit type object that is associated with this group.
      // Otherwise, you would have to connect with the unit server and filter
      // out all the events that aren't related to this unit type (which is all
      // we care about)
      m_pUnitType.Advise( GetUnknown(), IID_IUnitTypeEvents, &m_Cookie );

	  // NOTE: This Advise fails!!!
   }

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDisplayUnitGroup)
	COM_INTERFACE_ENTRY(IDisplayUnitGroup)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IDisplayUnitEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDisplayUnitGroup)
CONNECTION_POINT_ENTRY(IID_IDisplayUnitGroupEvents)
END_CONNECTION_POINT_MAP()

private:
   CComBSTR m_bstrName;
   CComPtr<IUnitServer> m_pUnitServer;
   CComPtr<IUnitType> m_pUnitType;

   DWORD m_Cookie;
   std::map<std::_tstring,DWORD> m_DisplayUnitCookies;

   HRESULT BadUnitTagError(BSTR bstrTag);
   void UnadviseDisplayUnit(IDisplayUnit* pDisplayUnit);
   void UnadviseAll();

// IDisplayUnitGroup
public:
	STDMETHOD(get_Default)(UnitModeType unitMode, /*[out, retval]*/ IDisplayUnit* *pVal) override;
   STDMETHOD(get_Name)(/*[out,retval]*/BSTR* name) override;
   STDMETHOD(get_UnitType)(/*[out,retval]*/BSTR* unitType) override;
   STDMETHOD(get_Item)(/*[in]*/ BSTR unitTag, /*[out, retval]*/ IDisplayUnit** retval) override;
//   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) override;
   STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType* retval) override;
   STDMETHOD(Add)(/*[in]*/BSTR unitTag,/*[in]*/UnitSystemType unitSystem,/*[in]*/ IDisplayUnitFormatter* formatter,/*[in,defaultvalue(VARIANT_FALSE)]*/ VARIANT_BOOL bDefault,/*[out,retval]*/ IDisplayUnit** dispUnit) override;
   STDMETHOD(Clear)() override;
   STDMETHOD(Remove)(/*[in]*/BSTR unitTag) override;
   STDMETHOD(get__EnumDisplayUnits)(/*[out,retval]*/ IEnumDisplayUnits** enumDisplayUnits) override;

// IDisplayUnit2Events
public:
   STDMETHOD(OnFormatChanged)(/*[in]*/IDisplayUnit* displayUnit)
   {
      Fire_OnFormatChanged(this,displayUnit);
      return S_OK;
   }
};

#endif //__DISPLAYUNITGROUP_H_
