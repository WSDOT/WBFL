///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2018  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_CORE_MFCDUAL_H_
#define INCLUDED_CORE_MFCDUAL_H_
#pragma once

// mfcdual.h: Helpful macros for adding dual interface support to
//			  MFC applications

// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

/////////////////////////////////////////////////////////////////////
// BEGIN_DUAL_INTERFACE_PART is just like BEGIN_INTERFACE_PART,
// except that it also adds the IDispatch methods to your class
// declaration.
#define BEGIN_DUAL_INTERFACE_PART(localClass, baseClass) \
	BEGIN_INTERFACE_PART(localClass, baseClass) \
       STDMETHOD(GetTypeInfoCount)(UINT FAR* pctinfo) override; \
       STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo FAR* FAR* pptinfo) override; \
       STDMETHOD(GetIDsOfNames)(REFIID riid, OLECHAR FAR* FAR* rgszNames, UINT cNames, LCID lcid, DISPID FAR* rgdispid) override; \
       STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pdispparams, VARIANT FAR* pvarResult, EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr) override; \

/////////////////////////////////////////////////////////////////////
// END_DUAL_INTERFACE_PART is just like END_INTERFACE_PART. It
// is only added for symmetry...
#define END_DUAL_INTERFACE_PART(localClass) \
	END_INTERFACE_PART(localClass) \



/////////////////////////////////////////////////////////////////////
// DELEGATE_DUAL_INTERFACE expands to define the standard IDispatch
// methods for a dual interface, delegating back to the default
// MFC implementation
#define DELEGATE_DUAL_INTERFACE(objectClass, dualClass) \
    STDMETHODIMP_(ULONG) objectClass::X##dualClass::AddRef() \
    { \
		METHOD_PROLOGUE(objectClass, dualClass) \
		return pThis->ExternalAddRef(); \
	} \
	STDMETHODIMP_(ULONG) objectClass::X##dualClass::Release() \
	{ \
		METHOD_PROLOGUE(objectClass, dualClass) \
		return pThis->ExternalRelease(); \
	} \
	STDMETHODIMP objectClass::X##dualClass::QueryInterface( \
		REFIID iid, LPVOID* ppvObj) \
	{ \
		METHOD_PROLOGUE(objectClass, dualClass) \
		return pThis->ExternalQueryInterface(&iid, ppvObj); \
	} \
	STDMETHODIMP objectClass::X##dualClass::GetTypeInfoCount( \
		UINT FAR* pctinfo) \
	{ \
		METHOD_PROLOGUE(objectClass, dualClass) \
		LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE); \
		ASSERT(lpDispatch != nullptr); \
		return lpDispatch->GetTypeInfoCount(pctinfo); \
	} \
	STDMETHODIMP objectClass::X##dualClass::GetTypeInfo( \
		UINT itinfo, LCID lcid, ITypeInfo FAR* FAR* pptinfo) \
	{ \
		METHOD_PROLOGUE(objectClass, dualClass) \
		LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE); \
		ASSERT(lpDispatch != nullptr); \
		return lpDispatch->GetTypeInfo(itinfo, lcid, pptinfo); \
	} \
	STDMETHODIMP objectClass::X##dualClass::GetIDsOfNames( \
		REFIID riid, OLECHAR FAR* FAR* rgszNames, UINT cNames, \
		LCID lcid, DISPID FAR* rgdispid) \
	{ \
		METHOD_PROLOGUE(objectClass, dualClass) \
		LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE); \
		ASSERT(lpDispatch != nullptr); \
		return lpDispatch->GetIDsOfNames(riid, rgszNames, cNames, \
								         lcid, rgdispid); \
	} \
	STDMETHODIMP objectClass::X##dualClass::Invoke( \
		DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, \
		DISPPARAMS FAR* pdispparams, VARIANT FAR* pvarResult, \
		EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr) \
	{ \
		METHOD_PROLOGUE(objectClass, dualClass) \
		LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE); \
		ASSERT(lpDispatch != nullptr); \
		return lpDispatch->Invoke(dispidMember, riid, lcid, \
								  wFlags, pdispparams, pvarResult, \
								  pexcepinfo, puArgErr); \
	} \



/////////////////////////////////////////////////////////////////////
// TRY_DUAL and CATCH_ALL_DUAL are used to provide exception handling
// for your dual interface methods. CATCH_ALL_DUAL takes care of 
// returning the appropriate error code.

#define TRY_DUAL(iidSource) \
	HRESULT _hr = S_OK; \
    REFIID  _riidSource = iidSource; \
	TRY \

#define CATCH_ALL_DUAL \
	CATCH(COleException, e) \
	{ \
		_hr = e->m_sc; \
	} \
	AND_CATCH_ALL(e) \
	{ \
		AFX_MANAGE_STATE(pThis->m_pModuleState); \
		_hr = DualHandleException(_riidSource, e); \
	} \
	END_CATCH_ALL \
	return _hr; \

/////////////////////////////////////////////////////////////////////
// DualHandleException is a helper function used to set the system's 
// error object, so that container applications that call through 
// VTBLs can retrieve rich error information		
extern "C"
{
HRESULT DualHandleException(REFIID riidSource, const CException* pAnyException);
}

/////////////////////////////////////////////////////////////////////
// DECLARE_DUAL_ERRORINFO expands to declare the ISupportErrorInfo
// support class. It works together with DUAL_ERRORINFO_PART and
// IMPLEMENT_DUAL_ERRORINFO defined below.
#define DECLARE_DUAL_ERRORINFO() \
    BEGIN_INTERFACE_PART(SupportErrorInfo, ISupportErrorInfo) \
        STDMETHOD(InterfaceSupportsErrorInfo)(THIS_ REFIID riid) override; \
    END_INTERFACE_PART(SupportErrorInfo) \

/////////////////////////////////////////////////////////////////////
// DUAL_ERRORINFO_PART adds the appropriate entry to the interface map
// for ISupportErrorInfo, if you used DECLARE_DUAL_ERRORINFO.
#define DUAL_ERRORINFO_PART(objectClass) \
    INTERFACE_PART(objectClass, IID_ISupportErrorInfo, SupportErrorInfo) \

/////////////////////////////////////////////////////////////////////
// IMPLEMENT_DUAL_ERRORINFO expands to an implementation of 
// ISupportErrorInfo which matches the declaration in 
// DECLARE_DUAL_ERRORINFO.
#define IMPLEMENT_DUAL_ERRORINFO(objectClass, riidSource) \
    STDMETHODIMP_(ULONG) objectClass::XSupportErrorInfo::AddRef() \
    { \
        METHOD_PROLOGUE(objectClass, SupportErrorInfo) \
	    return pThis->ExternalAddRef(); \
    } \
    STDMETHODIMP_(ULONG) objectClass::XSupportErrorInfo::Release() \
    { \
	    METHOD_PROLOGUE(objectClass, SupportErrorInfo) \
	    return pThis->ExternalRelease(); \
    } \
    STDMETHODIMP objectClass::XSupportErrorInfo::QueryInterface( \
	    REFIID iid, LPVOID* ppvObj) \
    { \
	    METHOD_PROLOGUE(objectClass, SupportErrorInfo) \
	    return pThis->ExternalQueryInterface(&iid, ppvObj); \
    } \
    STDMETHODIMP objectClass::XSupportErrorInfo::InterfaceSupportsErrorInfo( \
        REFIID iid) \
    { \
        METHOD_PROLOGUE(objectClass, SupportErrorInfo) \
        return (iid == riidSource) ? S_OK : S_FALSE; \
    }



/////////////////////////////////////////////////////////////////////
// DELEGATE_CUSTOM_INTERFACE expands to define the standard IUnknown
// methods, delegating back to the default MFC implementation
#define DELEGATE_CUSTOM_INTERFACE(objectClass, customClass) \
STDMETHODIMP_(ULONG) objectClass::X##customClass::AddRef() \
{ \
   METHOD_PROLOGUE(objectClass, customClass) \
   return pThis->ExternalAddRef(); \
} \
STDMETHODIMP_(ULONG) objectClass::X##customClass::Release() \
{ \
   METHOD_PROLOGUE(objectClass, customClass) \
   return pThis->ExternalRelease(); \
} \
STDMETHODIMP objectClass::X##customClass::QueryInterface( \
   REFIID iid, LPVOID* ppvObj) \
{ \
   METHOD_PROLOGUE(objectClass, customClass) \
   return pThis->ExternalQueryInterface( &iid, ppvObj ); \
}


#endif //  INCLUDED_CORE_MFCDUAL_H_