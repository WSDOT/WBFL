///////////////////////////////////////////////////////////////////////
// ToolsStorage - Test driver for WBFLTools library
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

// PCircle.h : Declaration of the CPCircle

#ifndef __PCIRCLE_H_
#define __PCIRCLE_H_

#include "resource.h"       // main symbols
#include <Private\WbflPackage.h>
#include <WbflAtlExt.h>
#include <WBFLTools.h>

/////////////////////////////////////////////////////////////////////////////
// CPCircle
class ATL_NO_VTABLE CPCircle : 
	// public CComObjectRootEx<CComSingleThreadModel>,
   public CComRefCountTracer<CPCircle,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPCircle, &CLSID_PCircle>,
   public IPCircle,
   public IStructuredStorage2,
	public IPersist
{
public:
	CPCircle()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PCIRCLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPCircle)
	COM_INTERFACE_ENTRY(IPCircle)
 	COM_INTERFACE_ENTRY(IPShape)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

// IPCircle
public:
	STDMETHOD(get_Diameter)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Diameter)(/*[in]*/ Float64 newVal);
// IPShape
	STDMETHOD(get_X)(Float64 * pVal)
	{
		if (pVal == nullptr)
			return E_POINTER;
			
      *pVal = m_X;

		return S_OK;
	}
	STDMETHOD(put_X)(Float64 pVal)
	{
      m_X = pVal;
		return S_OK;
	}
	STDMETHOD(get_Y)(Float64 * pVal)
	{
		if (pVal == nullptr)
			return E_POINTER;
			
      *pVal = m_Y;
		return S_OK;
	}
	STDMETHOD(put_Y)(Float64 pVal)
	{
      m_Y = pVal;
		return S_OK;
	}
	STDMETHOD(get_IsComposite)(BOOL * pVal)
	{
		if (pVal == nullptr)
			return E_POINTER;
			
      *pVal = FALSE;

		return S_OK;
	}
	STDMETHOD(get_Count)(CollectionIndexType * pVal)
	{
		if (pVal == nullptr)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(get_Item)(CollectionIndexType index, IPShape * * pVal)
	{
		if (pVal == nullptr)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(Add)(IPShape * __MIDL_0015)
	{
		return E_NOTIMPL;
	}
// IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * pLoad)
	{
      HRESULT hr = pLoad->BeginUnit(OLESTR("CPCircle"));
      
      CComVariant var;
      hr = pLoad->get_Property(OLESTR("X"), &var);
      if (FAILED(hr)) return hr;
      m_X = var.dblVal;

      hr = pLoad->get_Property(OLESTR("Y"), &var);
      if (FAILED(hr)) return hr;
      m_Y = var.dblVal;

      hr = pLoad->get_Property(OLESTR("Diameter"), &var);
      if (FAILED(hr)) return hr;
      m_Diameter = var.dblVal;

      VARIANT_BOOL bl;
      hr = pLoad->EndUnit(&bl);
      if (FAILED(hr)) return hr;

		return S_OK;
	}
	STDMETHOD(Save)(IStructuredSave2 * pSave)
	{
      pSave->BeginUnit(L"CPCircle", 1.0);

      pSave->put_Property(L"X", CComVariant(m_X));
      pSave->put_Property(L"Y", CComVariant(m_Y));
      pSave->put_Property(L"Diameter", CComVariant(m_Diameter));

      Float64 ver;
      TRY_TEST( pSave->get_Version(&ver), S_OK); 
      TRY_TEST(ver, 1.0);
      TRY_TEST( pSave->get_TopVersion(&ver), S_OK); 
      TRY_TEST(ver, 2.0);


      pSave->EndUnit();
		return S_OK;
	}

private:
   Float64 m_X;
   Float64 m_Y;
   Float64 m_Diameter;

// IPersist
	STDMETHOD(GetClassID)(GUID * pClassID)
	{
		if (pClassID == nullptr)
			return E_POINTER;
			
      *pClassID = this->GetObjectCLSID();
		return S_OK;
	}
};

#endif //__PCIRCLE_H_
