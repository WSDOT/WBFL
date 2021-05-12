///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2021  Washington State Department of Transportation
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

// UnitServerImp.h : Declaration of the CUnitServerImp

#ifndef __UNITSERVERIMP_H_
#define __UNITSERVERIMP_H_

#include "resource.h"       // main symbols
#include "UnitTypes.h"
#include "Unit.h"
#include <vector>
#include "WbflUnitServerCP.h"

interface IUnitType;

#pragma warning ( disable : 4786 )

/////////////////////////////////////////////////////////////////////////////
// CUnitSystem
class ATL_NO_VTABLE CUnitServerImp : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CUnitServerImp,CComObjectRootEx<CComSingleThreadModel> >,
   public CComCoClass<CUnitServerImp, &CLSID_UnitServer>,
   public IConnectionPointContainerImpl<CUnitServerImp>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CUnitServerImp,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IUnitTypesEvents,
   public IUnitServer,
   public IUnitConvert,
   public IUnitConvert2,
   public CProxyDUnitServerEvents< CUnitServerImp >
{
public:
   CUnitServerImp()
	{
      m_bIsLocked = false;

      m_pMass   = 0;
      m_pLength = 0;
      m_pTime   = 0;
      m_pTemp   = 0;
      m_pAngle  = 0;
   }

   ~CUnitServerImp()
   {
   }

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_UNITSERVER)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUnitServerImp)
	COM_INTERFACE_ENTRY(IUnitServer)
	COM_INTERFACE_ENTRY(IUnitConvert)
	COM_INTERFACE_ENTRY(IUnitConvert2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IUnitTypesEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CUnitServerImp)
CONNECTION_POINT_ENTRY(IID_IUnitServerEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IUnitServer
public:
	STDMETHOD(SetBaseUnits)(/*[in]*/ BSTR bstrMass, /*[in]*/ BSTR bstrLength, /*[in]*/ BSTR bstrTime, /*[in]*/ BSTR bstrTemp, /*[in]*/ BSTR bstrAngle) override;
	STDMETHOD(get_Mass)(/*[out,retval]*/ BSTR* pMass) override;
	STDMETHOD(get_Length)(/*[out,retval]*/ BSTR* pLength) override;
	STDMETHOD(get_Time)(/*[out,retval]*/ BSTR* pTime) override;
	STDMETHOD(get_Temperature)(/*[out,retval]*/ BSTR* pTemperature) override;
	STDMETHOD(get_Angle)(/*[out,retval]*/ BSTR* pAngle) override;
	STDMETHOD(get_UnitTypes)(/*[out,retval]*/ IUnitTypes** ppUnitTypes) override;
	STDMETHOD(get_UnitConvert)(/*[out,retval]*/ IUnitConvert** convert) override;
	STDMETHOD(get_UnitConvert2)(/*[out,retval]*/ IUnitConvert2** convert) override;

// IUnitConvert
public:
	STDMETHOD(Convert)(/*[in]*/ Float64 from, /*[in]*/ BSTR fromUnit, /*[in]*/ BSTR toUnit, /*[out,retval]*/ Float64* pTo) override;
	STDMETHOD(ConvertToBaseUnits)(/*[in]*/ Float64 val,/*[in]*/ BSTR fromUnit, /*[out,retval]*/ Float64* pConvVal) override;
	STDMETHOD(ConvertFromBaseUnits)(/*[in]*/ Float64 val,/*[in]*/ BSTR toUnit, /*[out,retval]*/ Float64* pConvVal) override;

// IUnitConvert2
public:
	STDMETHOD(Convert)(/*[in]*/ Float64 from, /*[in]*/ IUnit* pFromUnit, /*[in]*/ IUnit* pToUnit, /*[out,retval]*/ Float64* pTo) override;
	STDMETHOD(ConvertToBaseUnits)(/*[in]*/ Float64 val,/*[in]*/ IUnit* pFromUnit, /*[out,retval]*/ Float64* pConvVal) override;
	STDMETHOD(ConvertFromBaseUnits)(/*[in]*/ Float64 val, /*[in]*/ IUnit* pToUnit, /*[out,retval]*/ Float64* pConvVal) override;

// IUnitTypesEvents
public:
   STDMETHOD(OnUnitAdded)(/*[in]*/ IUnitType* unitType,/*[in]*/ IUnit* unit)
   {
      Fire_OnUnitAdded(unitType,unit);
      return S_OK;
   }

	STDMETHOD(OnUnitRemoved)(/*[in]*/ IUnitType* unitType,/*[in]*/ BSTR unit)
   {
      Fire_OnUnitRemoved(unitType,unit);
      return S_OK;
   }

	STDMETHOD(OnUnitsCleared)(/*[in]*/ IUnitType* unitType)
   {
      Fire_OnUnitsCleared(unitType);
      return S_OK;
   }

	STDMETHOD(OnUnitTypeAdded)(/*[in]*/ IUnitType* unitType)
   {
      Fire_OnUnitTypeAdded(unitType);
      return S_OK;
   }

	STDMETHOD(OnUnitTypeRemoved)(/*[in]*/ BSTR unitType)
   {
      Fire_OnUnitTypeRemoved(unitType);
      return S_OK;
   }

	STDMETHOD(OnUnitTypesCleared)()
   {
      Fire_OnUnitTypesCleared();
      return S_OK;
   }

private:
   bool m_bIsLocked;

   // Used in ConvertFromBaseUnits and ConvertToBaseUnits
   // Caching pointers here so that they don't have to be allocated for every conversion (which are many)
   CComObject<CUnit>* m_pFromUnit;
   CComObject<CUnit>* m_pToUnit; // same object as pFromUnit, just a different name so it makes more sense in context
   CComObject<CUnit>* m_pConvUnit;


   // Weak references
   IUnit* m_pMass;
   IUnit* m_pLength;
   IUnit* m_pTime;
   IUnit* m_pTemp;
   IUnit* m_pAngle;

   CComPtr<IUnitTypes> m_pUnitTypes;
   DWORD m_Cookie;

   HRESULT GetUnitType(BSTR bstrLabel,IUnitType** ppUnitType);
   HRESULT GetUnit(BSTR bstrType,BSTR bstrTag,IUnit** ppUnit);
   HRESULT GetUnit(BSTR bstrTag,IUnit** ppUnit);

   HRESULT BadUnitTagError(BSTR name);

};

#endif //__UNITSERVERIMP_H_
