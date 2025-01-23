///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// PlateGirder.h : Declaration of the CPlateGirder

#ifndef __PLATEGIRDER_H_
#define __PLATEGIRDER_H_

#include "resource.h"       // main symbols
#include <GeomModel/PlateGirder.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CPlateGirder
class ATL_NO_VTABLE CPlateGirder : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPlateGirder, &CLSID_PlateGirder>,
   public IObjectSafetyImpl<CPlateGirder,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportErrorInfo,
   public IPlateGirder,
	public IShapeXYPositionImpl<CPlateGirder, WBFL::Geometry::PlateGirder>
{
public:
	CPlateGirder()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

	void SetShape(const WBFL::Geometry::PlateGirder& shape);
	virtual WBFL::Geometry::PlateGirder& GetShape() override { return m_Beam; }

DECLARE_REGISTRY_RESOURCEID(IDR_PLATEGIRDER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPlateGirder)
	COM_INTERFACE_ENTRY(IPlateGirder)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   WBFL::Geometry::PlateGirder m_Beam;
   CComPtr<IPoint2d> m_HookPoint;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPlateGirder
public:
	STDMETHOD(get_HookPoint)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
	STDMETHOD(get_QBottomFlange)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_QTopFlange)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_WebWidth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_WebWidth)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_WebHeight)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_WebHeight)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_BottomFlangeThickness)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_BottomFlangeThickness)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_BottomFlangeWidth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_BottomFlangeWidth)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_TopFlangeThickness)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_TopFlangeThickness)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_TopFlangeWidth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_TopFlangeWidth)(/*[in]*/ Float64 newVal) override;
};

#endif //__PLATEGIRDER_H_
