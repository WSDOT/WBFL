///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright � 1999-2025  Washington State Department of Transportation
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

// BoxBeamSection.h : Declaration of the CBoxBeamSection

#ifndef __BoxBeamSection_H_
#define __BoxBeamSection_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBoxBeamSection
class ATL_NO_VTABLE CBoxBeamSection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CBoxBeamSection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CBoxBeamSection, &CLSID_BoxBeamSection>,
	public ISupportErrorInfo,
   public IBoxBeamSection,
   public IPrestressedGirderSection,
   public IShape,
   public ICompositeShape,
   public IXYPosition,
   public IAsymmetricSection
{
public:
   CBoxBeamSection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_BOXBEAMSECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBoxBeamSection)
	COM_INTERFACE_ENTRY(IBoxBeamSection)
	COM_INTERFACE_ENTRY(IGirderSection)
	COM_INTERFACE_ENTRY(IPrestressedGirderSection)
	COM_INTERFACE_ENTRY(IShape)
	COM_INTERFACE_ENTRY(ICompositeShape)
	COM_INTERFACE_ENTRY(IXYPosition)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IAsymmetricSection)
END_COM_MAP()

private:
   CComPtr<IBoxBeam> m_Beam;
   Float64 m_Rotation{ 0.0 }; // we need to keep track of rotation for the work point

   bool ValidateWebIndex(WebIndexType idx);
   void GetSplittingZone(Float64* pH,SplittingDirection* pSD);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IBoxBeamSection
public:
   STDMETHOD(put_Beam)(/*[in]*/IBoxBeam* beam) override;
   STDMETHOD(get_Beam)(/*[out,retval]*/IBoxBeam** beam) override;

// IGirderSection
public:
   STDMETHOD(get_GirderShape)(/*[out, retval]*/IShape** ppShape) override;
   STDMETHOD(get_VoidCount)(/*[out, retval]*/IndexType* pnVoids) override;
   STDMETHOD(get_VoidShape)(/*[in]*/IndexType voidIdx, /*[out, retval]*/IShape** ppShape) override;
   STDMETHOD(get_WorkPoint)(/*[out, retval]*/IPoint2d** ppWorkPoint) override;
   STDMETHOD(get_WebCount)(/*[out,retval]*/WebIndexType* nWebs) override;
	STDMETHOD(get_WebLocation)(/*[in]*/WebIndexType idx,/*[out,retval]*/Float64* location) override;
	STDMETHOD(get_WebSpacing)(/*[in]*/WebIndexType idx,/*[out,retval]*/Float64* spacing) override;
	STDMETHOD(get_WebThickness)(/*[in]*/WebIndexType idx,/*[out,retval]*/Float64* tWeb) override;
   STDMETHOD(get_WebPlane)(/*[in]*/WebIndexType idx,/*[out,retval]*/IPlane3d** ppPlane) override;
   STDMETHOD(get_MinWebThickness)(/*[out,retval]*/Float64* tWeb) override;
   STDMETHOD(get_EffectiveWebThickness)(/*[out,retval]*/Float64* tWeb) override;
   STDMETHOD(get_MatingSurfaceCount)(/*[out,retval]*/MatingSurfaceIndexType* nMatingSurfaces) override;
	STDMETHOD(get_MatingSurfaceLocation)(/*[in]*/MatingSurfaceIndexType idx, /*[in]*/ VARIANT_BOOL bGirderOnly,/*[out,retval]*/Float64* location) override;
	STDMETHOD(get_MatingSurfaceWidth)(/*[in]*/MatingSurfaceIndexType idx, /*[in]*/ VARIANT_BOOL bGirderOnly, /*[out,retval]*/Float64* wMatingSurface) override;
   STDMETHOD(get_MatingSurfaceProfile)(/*[in]*/MatingSurfaceIndexType idx, /*[in]*/ VARIANT_BOOL bGirderOnly, /*[out, retval]*/IPoint2dCollection** ppProfile) override;
   STDMETHOD(get_TopFlangeCount)(/*[out,retval]*/FlangeIndexType* nTopFlanges) override;
	STDMETHOD(get_TopFlangeLocation)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* location) override;
	STDMETHOD(get_TopFlangeWidth)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* width) override;
   STDMETHOD(get_TopFlangeThickness)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* tFlange) override;
   STDMETHOD(get_TopFlangeSpacing)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* spacing) override;
   STDMETHOD(get_BottomFlangeCount)(/*[out,retval]*/FlangeIndexType* nBottomFlanges) override;
	STDMETHOD(get_BottomFlangeLocation)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* location) override;
	STDMETHOD(get_BottomFlangeWidth)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* width) override;
   STDMETHOD(get_BottomFlangeThickness)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* tFlange) override;
   STDMETHOD(get_BottomFlangeSpacing)(/*[in]*/FlangeIndexType idx,/*[out,retval]*/Float64* spacing) override;
   STDMETHOD(get_OverallHeight)(/*[out,retval]*/Float64* height) override;
   STDMETHOD(get_NominalHeight)(/*[out,retval]*/Float64* height) override;
   STDMETHOD(get_TopWidth)(/*[out]*/Float64* wLeft,/*[out]*/Float64* wRight) override;
	STDMETHOD(get_BottomWidth)(/*[out]*/Float64* wLeft,/*[out]*/Float64* wRight) override;
	STDMETHOD(get_ShearWidth)(/*[out,retval]*/Float64* shearwidth) override;
   STDMETHOD(get_MinTopFlangeThickness)(/*[out,retval]*/Float64* tf) override;
	STDMETHOD(get_MinBottomFlangeThickness)(/*[out,retval]*/Float64* tf) override;
	STDMETHOD(get_CL2ExteriorWebDistance)(/*[in]*/ DirectionType side, /*[out,retval]*/Float64* ww) override;

// IPrestressedGirderSection
public:
   STDMETHOD(RemoveSacrificalDepth)(/*[in]*/Float64 sacDepth);
   STDMETHOD(get_SplittingZoneDimension)(/*[out,retval]*/Float64* pSZD) override;
   STDMETHOD(get_SplittingDirection)(/*[out,retval]*/SplittingDirection* pSD) override;
   STDMETHOD(GetWebSections)(/*[out]*/IDblArray** ppY, /*[out]*/IDblArray** ppW,/*[out]*/IBstrArray** ppDesc) override;
   STDMETHOD(GetWebWidthProjectionsForDebonding)(/*[out]*/IUnkArray** ppArray) override;

// IShape
public:
   STDMETHOD(FurthestPoint)(/*[in]*/ILine2d* line, /*[out]*/ IPoint2d** ppPoint, /*[out]*/Float64* dist) override;
   STDMETHOD(FurthestDistance)(/*[in]*/ILine2d* line,/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Perimeter)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_ShapeProperties)(/*[out,retval]*/ IShapeProperties* *pVal) override;
	STDMETHOD(get_BoundingBox)(/*[out, retval]*/ IRect2d* *pVal) override;
	STDMETHOD(get_PolyPoints)(/*[out,retval]*/ IPoint2dCollection** ppPolyPoints) override;
	STDMETHOD(PointInShape)(/*[in]*/ IPoint2d* pPoint,/*[out,retval]*/ VARIANT_BOOL* pbResult) override;
	STDMETHOD(Clone)(/*[out,retval]*/ IShape** pClone) override;
	STDMETHOD(ClipWithLine)(/*[in]*/ ILine2d* pLine,/*[out,retval]*/ IShape** pShape) override;
	STDMETHOD(ClipIn)(/*[in]*/ IRect2d* pRect,/*[out,retval]*/ IShape** pShape) override;

// ICompositeShape
public:
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
   STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
   STDMETHOD(get_Item)(/*[in]*/ IndexType idx, /*[out, retval]*/ ICompositeShapeItem* *pVal) override;
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown* *pVal) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ IndexType *pVal) override;
	STDMETHOD(Remove)(/*[in]*/ IndexType idx) override;
	STDMETHOD(Clear)() override;
   STDMETHOD(ReplaceEx)(IndexType idx,ICompositeShapeItem* pShapeItem) override;
   STDMETHOD(Replace)(IndexType idx,IShape* pShape) override;
	STDMETHOD(AddShapeEx)(/*[in]*/ ICompositeShapeItem* ShapeItem) override;
   STDMETHOD(AddShape)(/*[in]*/ IShape* shape,/*[in]*/ VARIANT_BOOL bVoid) override;

// IXYPosition
public:
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy) override;
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize) override;
	STDMETHOD(get_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[out,retval]*/ IPoint2d** point) override;
	STDMETHOD(put_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[in]*/ IPoint2d* point) override;
	STDMETHOD(MoveEx)(/*[in]*/ IPoint2d* pFrom,/*[in]*/ IPoint2d* pTo) override;
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pPoint,/*[in]*/ Float64 angle) override;
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx,/*[in]*/ Float64 cy,/*[in]*/ Float64 angle) override;

// IAsymmetricSection
public:
   STDMETHOD(GetTopWidth)(Float64* pLeft, Float64* pRight) override;
   STDMETHOD(GetHeight)(Float64* pHmin, Float64* pHcl, Float64* pHmax) override;
   STDMETHOD(GetStressPoints)(StressPointType spType, IPoint2dCollection** ppPoints) override;
   STDMETHOD(IgnoreBiaxialBending)(BOOL* pIgnore) override { *pIgnore = FALSE; return S_OK; }
};

#endif //__BoxBeamSection_H_
