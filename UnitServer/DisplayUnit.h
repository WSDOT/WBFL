///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 2000  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// DisplayUnit.h : Declaration of the CDisplayUnit

#ifndef __DISPLAYUNIT_H_
#define __DISPLAYUNIT_H_

#include "resource.h"       // main symbols
#include "WbflUnitServerCP.h"

/////////////////////////////////////////////////////////////////////////////
// CDisplayUnit
class ATL_NO_VTABLE CDisplayUnit : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CDisplayUnit,CComObjectRootEx<CComSingleThreadModel> >,
   public ISupportErrorInfoImpl<&IID_IDisplayUnit>,
   public IConnectionPointContainerImpl<CDisplayUnit>,
   public IObjectSafetyImpl<CDisplayUnit,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IDisplayUnitFormatterEvents,
	public IDisplayUnit,
	public CProxyDDisplayUnitEvents< CDisplayUnit >
{
public:
	CDisplayUnit()
	{
	}

   void Init(IUnitServer* pUnitServer,IUnit* pUnit,IDisplayUnitFormatter* pFormatter,UnitSystemType unitSystem,VARIANT_BOOL bIsDefault)
   {
      ATLASSERT(pUnitServer != 0 && pUnit != 0 && pFormatter != 0);

      pUnitServer->QueryInterface( &m_pConverter );
      m_pUnit = pUnit;
      m_pFormatter = pFormatter;
      m_UnitSystem = unitSystem;
      m_bIsDefault = bIsDefault;

      AdviseFormatter();
   }

   void FinalRelease();

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDisplayUnit)
	COM_INTERFACE_ENTRY(IDisplayUnit)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IDisplayUnitFormatterEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDisplayUnit)
CONNECTION_POINT_ENTRY(IID_IDisplayUnitEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<IUnit> m_pUnit;
   CComPtr<IUnitConvert2> m_pConverter;
   CComPtr<IDisplayUnitFormatter> m_pFormatter;
   UnitSystemType m_UnitSystem;
   VARIANT_BOOL m_bIsDefault;
   DWORD m_Cookie;

   void AdviseFormatter();
   void UnadviseFormatter();

// IDisplayUnit
public:
	STDMETHOD(get_Formatter)(/*[out,retval]*/IDisplayUnitFormatter** formatter);
	STDMETHOD(putref_Formatter)(/*[in]*/IDisplayUnitFormatter* formatter);
   STDMETHOD(get_Unit)(/*[out,retval]*/ IUnit** unit);
	STDMETHOD(get_UnitTag)(/*[out,retval]*/ BSTR* unitTag);
   STDMETHOD(get_UnitSystem)(/*[out,retval]*/ UnitSystemType* unitSystem);
   STDMETHOD(IsDefault)(/*[out,retval]*/ VARIANT_BOOL* bIsDefault);
   STDMETHOD(Format)(/*[in]*/ Float64 val,/*[in]*/ VARIANT_BOOL bShowUnitTag,/*[out,retval]*/ BSTR* fmtString);

// IDisplayUnitFormatterEvents
public:
   STDMETHOD(OnFormatChanged)()
   {
      Fire_OnFormatChanged(this);
      return S_OK;
   }
};

#endif //__DISPLAYUNIT_H_
