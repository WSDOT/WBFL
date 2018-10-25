///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// CompositeShapeItem.h : Declaration of the CCompositeShapeItem

#ifndef __COMPOSITESHAPEITEM_H_
#define __COMPOSITESHAPEITEM_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCompositeShapeItem
class ATL_NO_VTABLE CCompositeShapeItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCompositeShapeItem, &CLSID_CompositeShapeItem>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CCompositeShapeItem,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ICompositeShapeItem,
   public IStructuredStorage2,
   public IPersistImpl<CCompositeShapeItem>
{
public:
	CCompositeShapeItem()
	{
      m_bVoid = VARIANT_FALSE;
	}


DECLARE_REGISTRY_RESOURCEID(IDR_COMPOSITESHAPEITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCompositeShapeItem)
	COM_INTERFACE_ENTRY(ICompositeShapeItem)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICompositeShapeItem
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
	STDMETHOD(get_Void)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Void)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal);
	STDMETHOD(putref_Shape)(/*[in]*/ IShape* newVal);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

private:
   VARIANT_BOOL m_bVoid;
   CComPtr<IShape> m_Shape;
};

#endif //__COMPOSITESHAPEITEM_H_
