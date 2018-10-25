///////////////////////////////////////////////////////////////////////
// Sections - Model bridge member cross sections
// Copyright © 1999-2011  Washington State Department of Transportation
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
	public ICompositeBeamEx,
   public IStructuredStorage2,
   public IPersistImpl<CCompositeBeam>
{
public:
	CCompositeBeam()
	{
	}

   HRESULT FinalConstruct();

DECLARE_REGISTRY_RESOURCEID(IDR_COMPOSITEBEAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCompositeBeam)
	COM_INTERFACE_ENTRY(ICompositeBeamEx)
	COM_INTERFACE_ENTRY(ICompositeBeam)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISection)
	COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICompositeBeam
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
	STDMETHOD(get_Q)(/*[in]*/ Float64 location, /*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_QSlab)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_BeamDensity)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_BeamDensity)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_BeamE)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_BeamE)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal);
	STDMETHOD(get_Section)(/*[out, retval]*/ ISection* *pVal);
	STDMETHOD(get_HaunchDepth)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_HaunchDepth)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_HaunchWidth)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_HaunchWidth)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_SlabDensity)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_SlabDensity)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_SlabE)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_SlabE)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_EffectiveSlabWidth)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_EffectiveSlabWidth)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_TributarySlabWidth)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_TributarySlabWidth)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_GrossSlabDepth)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_GrossSlabDepth)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_SacrificialDepth)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_SacrificialDepth)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Beam)(/*[out, retval]*/ IShape* *pVal);
	STDMETHOD(putref_Beam)(/*[in]*/ IShape* newVal);

// ISection
public:
   STDMETHOD(get_BoundingBox)(/*[out, retval]*/ IRect2d* *pVal);
	STDMETHOD(get_ElasticProperties)(/*[out, retval]*/ IElasticProperties* *pVal);
	STDMETHOD(get_MassProperties)(/*[out, retval]*/ IMassProperties* *pVal);
	STDMETHOD(ClipIn)(/*[in]*/ IRect2d* rect,/*[out,retval]*/ ISection** section);
	STDMETHOD(ClipWithLine)(/*[in]*/ ILine2d* line,/*[out,retval]*/ ISection** section);
	STDMETHOD(Clone)(ISection** clone);

// IXYPosition
public:
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy);
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize);
	STDMETHOD(get_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[out,retval]*/ IPoint2d** point);
	STDMETHOD(put_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[in]*/ IPoint2d* point);
	STDMETHOD(MoveEx)(/*[in]*/ IPoint2d* pFrom,/*[in]*/ IPoint2d* pTo);
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pPoint,/*[in]*/ Float64 angle);
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx,/*[in]*/ Float64 cy,/*[in]*/ Float64 angle);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

protected:
   CComPtr<ICompositeSection> m_Section;

private:
   void UpdateShapeLocations();
};

#endif //__COMPOSITEBEAM_H_
