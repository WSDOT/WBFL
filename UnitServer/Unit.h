///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2011  Washington State Department of Transportation
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

// Unit.h : Declaration of the CUnit

#ifndef __UNIT_H_
#define __UNIT_H_

#include "resource.h"       // main symbols
#include "UnitType.h"


/////////////////////////////////////////////////////////////////////////////
// CUnitOfMeasure
class ATL_NO_VTABLE CUnit : 
   public CComObjectRootEx<CComSingleThreadModel>,
   //public CComRefCountTracer<CUnit,CComObjectRootEx<CComSingleThreadModel> >,
   public IObjectSafetyImpl<CUnit,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportErrorInfoImpl<&IID_IUnit>,
	public IUnit
{
public:
	CUnit()
	{
      m_pUnitServer = 0;
      m_pUnitType = 0;
	}
   
   ~CUnit()
   {
   }

   void Init( IUnitServer* pUnitServer,IUnitType* pUnitType,Float64 pre,Float64 cf,Float64 post,BSTR tag,UnitSystemType unitSystem);

   ULONG OuterAddRef()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::OuterAddRef();
      //ATLTRACE(_T("++++AddRef()  %s::%p refcount=%d\n"),"CUnit",this,m_dwRef);
      if ( ulReturn == 2 )
         AddStrongRef();
      return ulReturn;
   }

   ULONG OuterRelease()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::OuterRelease();
      //ATLTRACE(_T("~~~~Release()  %s::%p refcount=%d\n"),"CUnit",this,m_dwRef);
      if ( ulReturn == 1 )
         ReleaseStrongRef();
      return ulReturn;
   }

   ULONG InternalAddRef()
   { 
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::InternalAddRef();
      //ATLTRACE(_T("++++AddRef()  %s::%p refcount=%d\n"),"CUnit",this,m_dwRef);
      if ( ulReturn == 2 )
         AddStrongRef();
      return ulReturn;
   } 

   ULONG InternalRelease()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::InternalRelease();
      //ATLTRACE(_T("~~~~Release()  %s::%p refcount=%d\n"),"CUnit",this,m_dwRef);
      if ( ulReturn == 1 )
         ReleaseStrongRef();
      return ulReturn;
   } 

BEGIN_COM_MAP(CUnit)
	COM_INTERFACE_ENTRY(IUnit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// IUnit
public:
   STDMETHOD(get_UnitServer)(/*[out,retval]*/IUnitServer** unitServer);
	STDMETHOD(get_Tag)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_PreTerm)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_ConvFactor)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_PostTerm)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(get_UnitSystem)(/*[out, retval]*/ UnitSystemType *pVal);
	STDMETHOD(get_UnitType)(/*[out,retval]*/ IUnitType** ppUnitType);

private:
   Float64 m_PreTerm;
   Float64 m_ConvFactor;
   Float64 m_PostTerm;
   CComBSTR m_Tag;

   UnitSystemType m_UnitSystem;

   IUnitType* m_pUnitType; // Weak reference
   IUnitServer* m_pUnitServer; // Weak reference
   CComPtr<IUnitType> m_pUnitTypeStrong; // Strong reference
   CComPtr<IUnitServer> m_pUnitServerStrong; // Strong reference

   void AddStrongRef()
   {
      ATLASSERT( m_pUnitTypeStrong == 0 );
      ATLASSERT( m_pUnitServerStrong == 0 );

      m_pUnitServer->QueryInterface(&m_pUnitServerStrong);
      m_pUnitType->QueryInterface(&m_pUnitTypeStrong);

//      ATLTRACE(_T("CUnit Adding Strong Ref to Unit Type\n"));
      ATLASSERT( m_pUnitTypeStrong != 0 );

//      ATLTRACE(_T("CUnit Adding Strong Ref to Unit Server\n"));
      ATLASSERT( m_pUnitServerStrong != 0 );
   }

   void ReleaseStrongRef()
   {
      ATLASSERT( m_pUnitTypeStrong != 0 );
      ATLASSERT( m_pUnitServerStrong != 0 );

//      ATLTRACE(_T("CUnit Releasing Strong Ref to Unit Server\n"));
      m_pUnitServerStrong.Release();

//      ATLTRACE(_T("CUnit Releasing Strong Ref to Unit Type\n"));
      m_pUnitTypeStrong.Release();

//      ATLASSERT( m_pUnitTypeStrong == 0 );
//      ATLASSERT( m_pUnitServerStrong == 0 );
   }
};

#endif //__UNIT_H_
