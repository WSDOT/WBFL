///////////////////////////////////////////////////////////////////////
// ToolsStorage - Test driver for WBFLTools library
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

// PCompositeShape.h : Declaration of the CPCompositeShape

#ifndef __PCOMPOSITESHAPE_H_
#define __PCOMPOSITESHAPE_H_

#include "resource.h"       // main symbols

#include <vector>
#include <WbflAtlExt.h>
#include <WBFLTools.h>

/////////////////////////////////////////////////////////////////////////////
// CPCompositeShape
class ATL_NO_VTABLE CPCompositeShape : 
//	public CComObjectRootEx<CComSingleThreadModel>,
   public CComRefCountTracer<CPCompositeShape,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPCompositeShape, &CLSID_PCompositeShape>,
	public ISupportErrorInfo,
   public IPCompositeShape,
   public IPersist,
   public IStructuredStorage2
{
public:
	CPCompositeShape()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PCOMPOSITESHAPE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPCompositeShape)
	COM_INTERFACE_ENTRY(IPCompositeShape)
	COM_INTERFACE_ENTRY(IPShape)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPCompositeShape
public:
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
			
      *pVal = TRUE;
		return S_OK;
	}
	STDMETHOD(get_Count)(IndexType * pVal)
	{
		if (pVal == nullptr)
			return E_POINTER;
			
      *pVal = m_Shapes.size();

		return S_OK;
	}
	STDMETHOD(get_Item)(IndexType index, IPShape * * pVal)
	{
		if (pVal == nullptr)
			return E_POINTER;

      if (index < 0 || m_Shapes.size() <= index)
         return E_INVALIDARG;

      *pVal = m_Shapes[index];
      (*pVal)->AddRef();
			
		return S_OK;
	}
	STDMETHOD(Add)(IPShape * pVal)
	{
		if (pVal == nullptr)
			return E_POINTER;

      m_Shapes.push_back(ShapePtr(pVal));
		return S_OK;
	}

private:
   Float64 m_X;
   Float64 m_Y;
   using ShapePtr = CComPtr<IPShape>;
   std::vector<ShapePtr> m_Shapes;
// IPersist
	STDMETHOD(GetClassID)(GUID * pClassID)
	{
		if (pClassID == nullptr)
			return E_POINTER;
			
      *pClassID = this->GetObjectCLSID();
		return S_OK;
	}
// IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * pLoad)
	{
      pLoad->BeginUnit(OLESTR("CPCompositeShape"));

      HRESULT hr;
      VARIANT var;
      hr = pLoad->get_Property(OLESTR("X"), &var);
      if (FAILED(hr)) return hr;
      m_X = var.dblVal;

      hr = pLoad->get_Property(OLESTR("Y"), &var);
      if (FAILED(hr)) return hr;
      m_Y = var.dblVal;

      hr = pLoad->get_Property(OLESTR("Count"), &var);
      if (FAILED(hr)) return hr;
      int cnt = var.intVal;

      for (int i = 0; i<cnt; i++)
      {
         hr = pLoad->get_Property(OLESTR("Shape"), &var);
         if (FAILED(hr)) return hr;

         ATLASSERT(var.punkVal!=nullptr);

         IPShape* pis=nullptr;
         hr = var.punkVal->QueryInterface(IID_IPShape, (void**)&pis);
         if (FAILED(hr)) 
            return hr;

         var.punkVal->Release();

         m_Shapes.push_back(pis);
         pis->Release();
      }

      VARIANT_BOOL bl;
      hr = pLoad->EndUnit(&bl);
      if (FAILED(hr)) return hr;

		return S_OK;
	}

	STDMETHOD(Save)(IStructuredSave2 * pSave)
	{
      HRESULT hr;
      hr = pSave->BeginUnit(OLESTR("CPCompositeShape"), 1.0);
      if (FAILED(hr)) return hr;

      hr = pSave->put_Property(OLESTR("X"), CComVariant(m_X));
      if (FAILED(hr)) return hr;

      hr = pSave->put_Property(OLESTR("Y"), CComVariant(m_Y));
      if (FAILED(hr)) return hr;

      IndexType cnt = m_Shapes.size();
      hr = pSave->put_Property(OLESTR("Count"), CComVariant(cnt));
      if (FAILED(hr)) return hr;

      for (IndexType i = 0; i<cnt; i++)
      {
         hr = pSave->put_Property(OLESTR("Shape"), CComVariant(m_Shapes[i]));
         if (FAILED(hr)) return hr;
      }

      hr = pSave->EndUnit();

      return S_OK;
	}
};

#endif //__PCOMPOSITESHAPE_H_
