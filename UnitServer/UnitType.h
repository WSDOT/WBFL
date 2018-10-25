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

// UnitType.h : Declaration of the CUnitType

#ifndef __UNITTYPE_H_
#define __UNITTYPE_H_

#include "resource.h"       // main symbols
#include <vector>
#include "WbflUnitServerCP.h"

/////////////////////////////////////////////////////////////////////////////
// CUnitType
class ATL_NO_VTABLE CUnitType : 
   public CComObjectRootEx<CComSingleThreadModel>,
   //public CComRefCountTracer<CUnitType,CComObjectRootEx<CComSingleThreadModel> >,
   public IConnectionPointContainerImpl<CUnitType>,
	public ISupportErrorInfoImpl<&IID_IUnitType>,
   public IObjectSafetyImpl<CUnitType,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IUnitsEventSink,
	public IUnitType,
	public CProxyDUnitTypeEventSink< CUnitType >
{
public:
	CUnitType()
	{
      m_pUnitServer = 0;
   }

   ~CUnitType()
   {
   }

   void Init(IUnitServer* pUnitServer, BSTR bstrLabel, Float64 m,Float64 l,Float64 t,Float64 k,Float64 a);
   STDMETHOD(AddUnit)(BSTR bstrTag,Float64 preTerm,Float64 cf,Float64 postTerm,UnitSystemType unitSystem);
   HRESULT FinalConstruct();
   void FinalRelease();

   ULONG OuterAddRef()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::OuterAddRef();
//      ATLTRACE(_T("++++AddRef()  %s::%p refcount=%d\n"),"CUnitType",this,m_dwRef);
      if ( ulReturn == 2 )
         AddStrongRef();
      return ulReturn;
   }

   ULONG OuterRelease()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::OuterRelease();
//      ATLTRACE(_T("~~~~Release()  %s::%p refcount=%d\n"),"CUnitType",this,m_dwRef);
      if ( ulReturn == 1 )
         ReleaseStrongRef();
      return ulReturn;
   }

   ULONG InternalAddRef()
   { 
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::InternalAddRef();
//      ATLTRACE(_T("++++AddRef()  %s::%p refcount=%d\n"),"CUnitType",this,m_dwRef);
      if ( ulReturn == 2 )
         AddStrongRef();
      return ulReturn;
   } 

   ULONG InternalRelease()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::InternalRelease();
//      ATLTRACE(_T("~~~~Release()  %s::%p refcount=%d\n"),"CUnitType",this,m_dwRef);
      if ( ulReturn == 1 )
         ReleaseStrongRef();
      return ulReturn;
   } 

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUnitType)
	COM_INTERFACE_ENTRY(IUnitType)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IUnitsEventSink)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CUnitType)
   CONNECTION_POINT_ENTRY(IID_IUnitTypeEventSink)
END_CONNECTION_POINT_MAP()

// IUnitType
public:
   STDMETHOD(get_UnitServer)(/*[out,retval]*/IUnitServer** unitServer);
   STDMETHOD(get_Mass)(/*[out,retval]*/Float64 *pMass);
   STDMETHOD(get_Length)(/*[out,retval]*/Float64* pLength);
   STDMETHOD(get_Time)(/*[out,retval]*/ Float64* pTime);
   STDMETHOD(get_Temperature)(/*[out,retval]*/ Float64* pTemp);
   STDMETHOD(get_Angle)(/*[out,retval]*/ Float64* pAngle);
   STDMETHOD(get_Label)(/*[out, retval]*/ BSTR *pLabel);
   STDMETHOD(get_Units)(/*[out,retval]*/ IUnits** ppUnits);

// IUnitsEventSink
public:
   STDMETHOD(OnUnitAdded)(IUnit* unit)
   {
      Fire_OnUnitAdded(this,unit);
      return S_OK;
   }

   STDMETHOD(OnUnitRemoved)(BSTR unit)
   {
      Fire_OnUnitRemoved(this,unit);
      return S_OK;
   }

   STDMETHOD(OnUnitsCleared)()
   {
      Fire_OnUnitsCleared(this);
      return S_OK;
   }

private:
   CComPtr<IUnits> m_pUnits;
   IUnitServer* m_pUnitServer; // Weak Reference
   CComPtr<IUnitServer> m_pUnitServerStrong;

   CComBSTR m_bstrLabel;
   Float64 m_Mass;
   Float64 m_Length;
   Float64 m_Time;
   Float64 m_Temp;
   Float64 m_Angle;

   DWORD m_Cookie;

   void AddStrongRef()
   {
      ATLASSERT( m_pUnitServerStrong == 0 );
//      ATLTRACE(_T("CUnitType Adding Strong Ref to Unit Server\n"));

      m_pUnitServer->QueryInterface(&m_pUnitServerStrong);

      ATLASSERT( m_pUnitServerStrong != 0 );
   }

   void ReleaseStrongRef()
   {
      ATLASSERT( m_pUnitServerStrong != 0 );
//      ATLTRACE(_T("CUnitType Releasing Strong Ref to Unit Server\n"));

      m_pUnitServerStrong.Release();

//      ATLASSERT( m_pUnitServerStrong == 0 );
   }
};

#endif //__UNITTYPE_H_
