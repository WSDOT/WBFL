///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// ProfileElement.h : Declaration of the CProfileElement

#ifndef __PROFILEELEMENT_H_
#define __PROFILEELEMENT_H_
#pragma once

#include "resource.h"       // main symbols
#include "COGOCP.h"

/////////////////////////////////////////////////////////////////////////////
// CProfileElement
class ATL_NO_VTABLE CProfileElement : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProfileElement, &CLSID_ProfileElement>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CProfileElement,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CProfileElement>,
	public CProxyDProfileElementEvents< CProfileElement >,
	public IProfilePointEvents,
	public IVertCurveEvents,
   public IProfileElement,
   public IStructuredStorage2,
   public IPersistImpl<CProfileElement>
{
public:
	CProfileElement()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PROFILEELEMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProfileElement)
	COM_INTERFACE_ENTRY(IProfileElement)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IProfilePointEvents)
 
   COM_INTERFACE_ENTRY(IVertCurveEvents)

   COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)

   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CProfileElement)
CONNECTION_POINT_ENTRY(IID_IProfileElementEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IProfileElement
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
   STDMETHOD(Clone)(/*[out,retval]*/ IProfileElement* *clone) override;
	STDMETHOD(get_Value)(/*[out, retval]*/ IUnknown** pdispVal) override;
	STDMETHOD(putref_Value)(/*[in]*/ IUnknown* pdispVal) override;
	STDMETHOD(get_Type)(/*[out, retval]*/ ProfileElementType *pVal) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

   // IProfilePointEvents
public:
	STDMETHOD(OnProfilePointChanged)(IProfilePoint * pp)
	{
      ATLASSERT(m_Value.IsEqualObject(pp));
      Fire_OnProfileElementChanged(this);
		return S_OK;
	}

// IVertCurveEvents
public:
	STDMETHOD(OnVertCurveChanged)(IVertCurve * vc)
	{
      ATLASSERT(m_Value.IsEqualObject(vc));
      Fire_OnProfileElementChanged(this);
		return S_OK;
	}

private:
	ProfileElementType m_Type;
   CComPtr<IUnknown> m_Value;
   DWORD m_dwCookie;

   void Advise();
   void Unadvise();
};

#endif //__PROFILEELEMENT_H_
