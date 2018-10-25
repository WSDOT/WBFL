///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

// MultiWebSection.h : Declaration of the CMultiWebSection

#ifndef __MultiWebSection_H_
#define __MultiWebSection_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMultiWebSection
class ATL_NO_VTABLE CMultiWebSection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CMultiWebSection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CMultiWebSection, &CLSID_MultiWebSection>,
	public ISupportErrorInfo,
   public IMultiWebSection,
   public IPrestressedGirderSection,
   public IShape,
   public ICompositeShape,
   public IXYPosition
{
public:
   CMultiWebSection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_MULTIWEBSECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMultiWebSection)
	COM_INTERFACE_ENTRY(IMultiWebSection)
	COM_INTERFACE_ENTRY(IGirderSection)
	COM_INTERFACE_ENTRY(IPrestressedGirderSection)
	COM_INTERFACE_ENTRY(IShape)
	COM_INTERFACE_ENTRY(ICompositeShape)
	COM_INTERFACE_ENTRY(IXYPosition)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   CComPtr<IMultiWeb> m_Beam;
   CComPtr<IShape> m_Shape;
   CComPtr<IXYPosition> m_Position;
   CComPtr<ICompositeShape> m_CompositeShape;

   bool ValidateWebIndex(CollectionIndexType idx);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMultiWebSection
public:
   STDMETHOD(put_Beam)(/*[in]*/IMultiWeb* beam);
   STDMETHOD(get_Beam)(/*[out,retval]*/IMultiWeb** beam);

// IGirderSection
public:
	STDMETHOD(get_WebCount)(/*[out,retval]*/WebIndexType* nWebs);
	STDMETHOD(get_WebLocation)(/*[in]*/WebIndexType idx,/*[out,retval]*/Float64* location);
	STDMETHOD(get_WebSpacing)(/*[in]*/WebIndexType idx,/*[out,retval]*/Float64* spacing);
	STDMETHOD(get_WebThickness)(/*[in]*/WebIndexType idx,/*[out,retval]*/Float64* tWeb);
   STDMETHOD(get_MinWebThickness)(/*[out,retval]*/Float64* tWeb);
   STDMETHOD(get_WebPlane)(/*[in]*/WebIndexType idx,/*[out,retval]*/IPlane3d** ppPlane);
   STDMETHOD(get_EffectiveWebThickness)(/*[out,retval]*/Float64* tWeb);
   STDMETHOD(get_MatingSurfaceCount)(/*[out,retval]*/MatingSurfaceIndexType* nMatingSurfaces);
	STDMETHOD(get_MatingSurfaceLocation)(/*[in]*/MatingSurfaceIndexType idx,/*[out,retval]*/Float64* location);
	STDMETHOD(get_MatingSurfaceWidth)(/*[in]*/MatingSurfaceIndexType idx,/*[out,retval]*/Float64* wMatingSurface);
   STDMETHOD(get_TopFlangeCount)(/*[out,retval]*/FlangeIndexType* nTopFlanges);
	STDMETHOD(get_TopFlangeLocation)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* location);
	STDMETHOD(get_TopFlangeWidth)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* width);
   STDMETHOD(get_TopFlangeThickness)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* tFlange);
   STDMETHOD(get_TopFlangeSpacing)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* spacing);
   STDMETHOD(get_BottomFlangeCount)(/*[out,retval]*/FlangeIndexType* nBottomFlanges);
	STDMETHOD(get_BottomFlangeLocation)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* location);
	STDMETHOD(get_BottomFlangeWidth)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* width);
   STDMETHOD(get_BottomFlangeThickness)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* tFlange);
   STDMETHOD(get_BottomFlangeSpacing)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* spacing);
   STDMETHOD(get_GirderHeight)(/*[out,retval]*/Float64* height);
	STDMETHOD(get_TopWidth)(/*[out,retval]*/Float64* width);
	STDMETHOD(get_BottomWidth)(/*[out,retval]*/Float64* width);
	STDMETHOD(get_ShearWidth)(/*[out,retval]*/Float64* shearwidth);
	STDMETHOD(get_MinTopFlangeThickness)(/*[out,retval]*/Float64* tf);
	STDMETHOD(get_MinBottomFlangeThickness)(/*[out,retval]*/Float64* tf);
	STDMETHOD(get_CL2ExteriorWebDistance)(/*[in]*/ DirectionType side, /*[out,retval]*/Float64* ww);
   STDMETHOD(get_SplittingZoneDimension)(/*[out,retval]*/Float64* pSZD);
   STDMETHOD(get_SplittingDirection)(/*[out,retval]*/SplittingDirection* pSD);

// IShape
public:
	STDMETHOD(FurthestDistance)(/*[in]*/ILine2d* line,/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_Perimeter)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(get_ShapeProperties)(/*[out,retval]*/ IShapeProperties* *pVal);
	STDMETHOD(get_BoundingBox)(/*[out, retval]*/ IRect2d* *pVal);
	STDMETHOD(get_PolyPoints)(/*[out,retval]*/ IPoint2dCollection** ppPolyPoints);
	STDMETHOD(PointInShape)(/*[in]*/ IPoint2d* pPoint,/*[out,retval]*/ VARIANT_BOOL* pbResult);
	STDMETHOD(Clone)(/*[out,retval]*/ IShape** pClone);
	STDMETHOD(ClipWithLine)(/*[in]*/ ILine2d* pLine,/*[out,retval]*/ IShape** pShape);
	STDMETHOD(ClipIn)(/*[in]*/ IRect2d* pRect,/*[out,retval]*/ IShape** pShape);

// IXYPosition
public:
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy);
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize);
	STDMETHOD(get_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[out,retval]*/ IPoint2d** point);
	STDMETHOD(put_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[in]*/ IPoint2d* point);
	STDMETHOD(MoveEx)(/*[in]*/ IPoint2d* pFrom,/*[in]*/ IPoint2d* pTo);
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pPoint,/*[in]*/ Float64 angle);
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx,/*[in]*/ Float64 cy,/*[in]*/ Float64 angle);

// ICompositeShape
public:
   STDMETHOD(get_StructuredStorage)(/*[out, retval]*/ IStructuredStorage2* *pStg);
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal);
	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx, /*[out, retval]*/ ICompositeShapeItem* *pVal);
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(Remove)(/*[in]*/ CollectionIndexType idx);
	STDMETHOD(Clear)();
   STDMETHOD(ReplaceEx)(CollectionIndexType idx,ICompositeShapeItem* pShapeItem);
   STDMETHOD(Replace)(CollectionIndexType idx,IShape* pShape);
	STDMETHOD(AddShapeEx)(/*[in]*/ ICompositeShapeItem* ShapeItem);
   STDMETHOD(AddShape)(/*[in]*/ IShape* shape,/*[in]*/ VARIANT_BOOL bVoid);
};

#endif //__MultiWebSection_H_
