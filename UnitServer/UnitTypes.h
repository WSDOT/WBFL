///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2019  Washington State Department of Transportation
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

// UnitTypes.h : Declaration of the CUnitTypes

#ifndef __UNITTYPES_H_
#define __UNITTYPES_H_

#include "resource.h"       // main symbols
#include <vector>
#include <map>
#include <string>
#include "WbflUnitServerCP.h"

typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT,VARIANT,_Copy<VARIANT>, std::vector<CComVariant> > UnitTypeEnum;
typedef ICollectionOnSTLImpl<IUnitTypes,std::vector<CComVariant>,VARIANT,_Copy<VARIANT>,UnitTypeEnum> IUnitTypeCollection;

/////////////////////////////////////////////////////////////////////////////
// CUnits
class ATL_NO_VTABLE CUnitTypes : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CUnitTypes,CComObjectRootEx<CComSingleThreadModel> >,
   public IConnectionPointContainerImpl<CUnitTypes>,
	public ISupportErrorInfoImpl<&IID_IUnitTypes>,
   public IObjectSafetyImpl<CUnitTypes,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IUnitTypeEventSink,
	public IUnitTypeCollection,
	public CProxyDUnitTypesEventSink< CUnitTypes >
{
public:
	CUnitTypes()
	{
      m_pUnitServer = 0;
	}

   ~CUnitTypes()
   {
   }

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetUnitServer(IUnitServer* pUnitServer)
   { m_pUnitServer = pUnitServer; }

   HRESULT InitDefaultUnits();

   ULONG OuterAddRef()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::OuterAddRef();
//      ATLTRACE(_T("++++AddRef()  %s::%p refcount=%d\n"),"CUnitTypes",this,m_dwRef);
      if ( ulReturn == 2 )
         AddStrongRef();
      return ulReturn;
   }

   ULONG OuterRelease()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::OuterRelease();
//      ATLTRACE(_T("~~~~Release()  %s::%p refcount=%d\n"),"CUnitTypes",this,m_dwRef);
      if ( ulReturn == 1 )
         ReleaseStrongRef();
      return ulReturn;
   }

   ULONG InternalAddRef()
   { 
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::InternalAddRef();
//      ATLTRACE(_T("++++AddRef()  %s::%p refcount=%d\n"),"CUnitTypes",this,m_dwRef);
      if ( ulReturn == 2 )
         AddStrongRef();
      return ulReturn;
   } 

   ULONG InternalRelease()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::InternalRelease();
//      ATLTRACE(_T("~~~~Release()  %s::%p refcount=%d\n"),"CUnitTypes",this,m_dwRef);
      if ( ulReturn == 1 )
         ReleaseStrongRef();
      return ulReturn;
   } 

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUnitTypes)
	COM_INTERFACE_ENTRY(IUnitTypes)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IUnitTypeEventSink)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CUnitTypes)
CONNECTION_POINT_ENTRY(IID_IUnitTypesEventSink)
END_CONNECTION_POINT_MAP()

// IUnitTypes
public:
	STDMETHOD(get_Count)(CollectionIndexType* retval) override;
	STDMETHOD(get_Item)(VARIANT Index, IUnitType** retval) override;
//	STDMETHOD(get__NewEnum)(IUnknown** retval) override;
   STDMETHOD(Add)(/*[in]*/BSTR bstrLabel,/*[in]*/Float64 Mass,/*[in]*/Float64 Length,/*[in]*/Float64 Time,/*[in]*/Float64 Temperature,/*[in]*/Float64 Angle,/*[out,retval]*/IUnitType** ppUnitType) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(Remove)(VARIANT Index) override;
   STDMETHOD(get__EnumUnitTypes)(/*[out,retval]*/ IEnumUnitTypes** enumUnitTypes) override;

// IUnitTypeEventSink
public:
   STDMETHOD(OnUnitAdded)(IUnitType* unitType,IUnit* unit) override
   {
      Fire_OnUnitAdded(unitType,unit);
      return S_OK;
   }

   STDMETHOD(OnUnitRemoved)(IUnitType* unitType,BSTR unit) override
   {
      Fire_OnUnitRemoved(unitType,unit);
      return S_OK;
   }

   STDMETHOD(OnUnitsCleared)(IUnitType* unitType) override
   {
      Fire_OnUnitsCleared(unitType);
      return S_OK;
   }

private:
   IUnitServer* m_pUnitServer; // Weak reference
   CComPtr<IUnitServer> m_pUnitServerStrong; // Strong reference
   std::map<std::_tstring,DWORD> m_Cookies; // Map of unit type name to connection cookie

   void UnadviseUnitType(IUnitType* pUnitType);
   void UnadviseAll();
   void SaveUnitType(IUnitType* pUnitType);
   HRESULT Remove(IUnitType* pUnitType);
   HRESULT Remove(long idx);
   HRESULT Remove(BSTR bstrName);


   void AddStrongRef()
   {
      ATLASSERT( m_pUnitServerStrong == 0 );
//      ATLTRACE(_T("CUnitTypes Adding Strong Ref to Unit Server\n"));

      m_pUnitServer->QueryInterface(&m_pUnitServerStrong);

      ATLASSERT( m_pUnitServerStrong != 0 );
   }

   void ReleaseStrongRef()
   {
      ATLASSERT( m_pUnitServerStrong != 0 );
//      ATLTRACE(_T("CUnitTypes Releasing Strong Ref to Unit Server\n"));

      m_pUnitServerStrong.Release();

//      ATLASSERT( m_pUnitServerStrong == 0 );
   }
};

#endif //__UNITTYPES_H_
