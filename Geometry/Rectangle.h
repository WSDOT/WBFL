///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// Rectangle.h : Declaration of the CRectangle

#ifndef __RECTANGLE_H_
#define __RECTANGLE_H_

#include "resource.h"       // main symbols
#include <GeomModel/Rectangle.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CRectangle
class ATL_NO_VTABLE CRectangle : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRectangle, &CLSID_Rect>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CRectangle,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IRectangle,
   public IShapeXYPositionImpl<CRectangle,WBFL::Geometry::Rectangle>
{
public:
	CRectangle()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetShape(const WBFL::Geometry::Rectangle& shape);
   virtual WBFL::Geometry::Rectangle& GetShape() override { return m_Rectangle; }

DECLARE_REGISTRY_RESOURCEID(IDR_RECTANGLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRectangle)
	COM_INTERFACE_ENTRY(IRectangle)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   WBFL::Geometry::Rectangle m_Rectangle;
   CComPtr<IPoint2d> m_HookPoint;

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IRectangle
public:
	STDMETHOD(get_HookPoint)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_Width)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Width)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Height)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
};

#endif //__RECTANGLE_H_
