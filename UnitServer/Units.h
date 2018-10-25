///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2014  Washington State Department of Transportation
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

// Units.h : Declaration of the CUnits

#ifndef __UNITS_H_
#define __UNITS_H_

#include "resource.h"       // main symbols
#include <vector>
#include "UnitType.h"
#include "WbflUnitServerCP.h"

typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT,VARIANT,_Copy<VARIANT>, std::vector<CComVariant> > UnitEnum;
typedef ICollectionOnSTLImpl<IUnits,std::vector<CComVariant>,VARIANT,_Copy<VARIANT>,UnitEnum> IUnitCollection;

/////////////////////////////////////////////////////////////////////////////
// CUnits
class ATL_NO_VTABLE CUnits : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CUnits,CComObjectRootEx<CComSingleThreadModel> >,
   public IConnectionPointContainerImpl<CUnits>,
	public ISupportErrorInfoImpl<&IID_IUnits>,
   public IObjectSafetyImpl<CUnits,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IUnitCollection,
	public CProxyDUnitsEventSink< CUnits >
{
public:
	CUnits()
	{
      m_UnitSystem = unitsSI + unitsUS;
      m_pUnitType = 0;
      m_pUnitServer = 0;
	}

   void Init(IUnitServer* pUnitServer, IUnitType* pUnitType)
   {
      ATLASSERT(  pUnitServer != 0 && pUnitType != 0 );

      m_pUnitType   = pUnitType;
      m_pUnitServer = pUnitServer;
   }

   ULONG OuterAddRef()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::OuterAddRef();
//      ATLTRACE(_T("++++AddRef()  %s::%p refcount=%d\n"),"CUnits",this,m_dwRef);
      if ( ulReturn == 2 )
         AddStrongRef();
      return ulReturn;
   }

   ULONG OuterRelease()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::OuterRelease();
//      ATLTRACE(_T("~~~~Release()  %s::%p refcount=%d\n"),"CUnits",this,m_dwRef);
      if ( ulReturn == 1 )
         ReleaseStrongRef();
      return ulReturn;
   }

   ULONG InternalAddRef()
   { 
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::InternalAddRef();
//      ATLTRACE(_T("++++AddRef()  %s::%p refcount=%d\n"),"CUnits",this,m_dwRef);
      if ( ulReturn == 2 )
         AddStrongRef();
      return ulReturn;
   } 

   ULONG InternalRelease()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::InternalRelease();
//      ATLTRACE(_T("~~~~Release()  %s::%p refcount=%d\n"),"CUnits",this,m_dwRef);
      if ( ulReturn == 1 )
         ReleaseStrongRef();
      return ulReturn;
   } 

BEGIN_COM_MAP(CUnits)
	COM_INTERFACE_ENTRY(IUnits)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CUnits)
CONNECTION_POINT_ENTRY(IID_IUnitsEventSink)
END_CONNECTION_POINT_MAP()

// IUnits
public:
	STDMETHOD(Remove)(/*[in]*/VARIANT Index);
	STDMETHOD(get_Count)(CollectionIndexType* retval);
	STDMETHOD(get_Item)(VARIANT Index, IUnit** retval);
//	STDMETHOD(get__NewEnum)(IUnknown** retval);
	STDMETHOD(Add)(/*[in]*/BSTR tag,/*[in]*/Float64 preTerm,/*[in]*/Float64 cf,/*[in]*/Float64 postTerm,/*[in]*/UnitSystemType unitSystem,/*[out,retval]*/IUnit** ppUnit);
   STDMETHOD(Clear)();
   STDMETHOD(get__EnumUnits)(/*[out,retval]*/ IEnumUnits** enumUnits);

private:
   // Store variants because it makes creating the enumerators easier
   IUnitType* m_pUnitType; // Weak reference
   IUnitServer* m_pUnitServer; // Weak reference
   CComPtr<IUnitType> m_pUnitTypeStrong; // Strong reference
   CComPtr<IUnitServer> m_pUnitServerStrong; // Strong reference

   long m_UnitSystem;

   std::vector<CComVariant>::iterator GetUnit(VARIANT Index);
   std::vector<CComVariant>::iterator GetUnitByIndex(long idx);
   std::vector<CComVariant>::iterator GetUnitByTag(BSTR bstrName);


   void AddStrongRef()
   {
      ATLASSERT( m_pUnitTypeStrong == 0 );
      ATLASSERT( m_pUnitServerStrong == 0 );

//      ATLTRACE(_T("CUnits Adding Strong Ref to Unit Server\n"));
      m_pUnitServer->QueryInterface(&m_pUnitServerStrong);

//      ATLTRACE(_T("CUnits Adding Strong Ref to Unit Type\n"));
      m_pUnitType->QueryInterface(&m_pUnitTypeStrong);

      ATLASSERT( m_pUnitTypeStrong != 0 );
      ATLASSERT( m_pUnitServerStrong != 0 );
   }

   void ReleaseStrongRef()
   {
      ATLASSERT( m_pUnitTypeStrong != 0 );
      ATLASSERT( m_pUnitServerStrong != 0 );

//      ATLTRACE(_T("CUnits Releasing Strong Ref to Unit Server\n"));
      m_pUnitServerStrong.Release();

//      ATLTRACE(_T("CUnits Releasing Strong Ref to Unit Type\n"));
      m_pUnitTypeStrong.Release();

//      ATLASSERT( m_pUnitTypeStrong == 0 );
//      ATLASSERT( m_pUnitServerStrong == 0 );
   }
};

#endif //__UNITS_H_
