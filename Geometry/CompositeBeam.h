///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// CompositeBeam.h : Declaration of the CCompositeBeam

#ifndef __COMPOSITEBEAM_H_
#define __COMPOSITEBEAM_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCompositeBeam
class ATL_NO_VTABLE CCompositeBeam : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCompositeBeam, &CLSID_CompositeBeam>,
   public IObjectSafetyImpl<CCompositeBeam,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportErrorInfo,
	public ISection,
	public IXYPosition,
	public ICompositeBeam
{
public:
	CCompositeBeam()
	{
	}

   HRESULT FinalConstruct();

DECLARE_REGISTRY_RESOURCEID(IDR_COMPOSITEBEAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCompositeBeam)
	COM_INTERFACE_ENTRY(ICompositeBeam)
   COM_INTERFACE_ENTRY(ISection)
	COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICompositeBeam
public:
	STDMETHOD(get_Q)(/*[in]*/ Float64 location, /*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_QSlab)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_BeamDensity)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_BeamDensity)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_BeamE)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_BeamE)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Section)(/*[out, retval]*/ ISection* *pVal) override;
	STDMETHOD(get_HaunchDepth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_HaunchDepth)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_HaunchWidth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_HaunchWidth)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_SlabDensity)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_SlabDensity)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_SlabE)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_SlabE)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_EffectiveSlabWidth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EffectiveSlabWidth)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_TributarySlabWidth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_TributarySlabWidth)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_GrossSlabDepth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_GrossSlabDepth)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_SacrificialDepth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_SacrificialDepth)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Beam)(/*[out, retval]*/ IShape* *pVal) override;
	STDMETHOD(putref_Beam)(/*[in]*/ IShape* newVal) override;

// ISection
public:
   STDMETHOD(get_BoundingBox)(/*[out, retval]*/ IRect2d* *pVal) override;
	STDMETHOD(get_ElasticProperties)(/*[out, retval]*/ IElasticProperties* *pVal) override;
	STDMETHOD(get_MassProperties)(/*[out, retval]*/ IMassProperties* *pVal) override;
	STDMETHOD(ClipIn)(/*[in]*/ IRect2d* rect,/*[out,retval]*/ ISection** section) override;
	STDMETHOD(ClipWithLine)(/*[in]*/ ILine2d* line,/*[out,retval]*/ ISection** section) override;
	STDMETHOD(Clone)(ISection** clone) override;

// IXYPosition
public:
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy) override;
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize) override;
	STDMETHOD(get_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[out,retval]*/ IPoint2d** point) override;
	STDMETHOD(put_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[in]*/ IPoint2d* point) override;
	STDMETHOD(MoveEx)(/*[in]*/ IPoint2d* pFrom,/*[in]*/ IPoint2d* pTo) override;
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pPoint,/*[in]*/ Float64 angle) override;
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx,/*[in]*/ Float64 cy,/*[in]*/ Float64 angle) override;

protected:
   CComPtr<ICompositeSectionEx> m_Section;

private:
   void UpdateShapeLocations();
};

#endif //__COMPOSITEBEAM_H_
