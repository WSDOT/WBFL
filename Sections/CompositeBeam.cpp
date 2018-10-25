///////////////////////////////////////////////////////////////////////
// Sections - Model bridge member cross sections
// Copyright © 1999-2016  Washington State Department of Transportation
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

// CompositeBeam.cpp : Implementation of CCompositeBeam
#include "stdafx.h"
#include "WBFLSections.h"
#include "CompositeBeam.h"
#include "CompositeSection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Index of composite section items
#define BEAM       0
#define HAUNCH     1
#define SLAB       2
#define TRIB_LEFT  3
#define TRIB_RIGHT 4
#define WS         5

/////////////////////////////////////////////////////////////////////////////
// CCompositeBeam
HRESULT CCompositeBeam::FinalConstruct()
{
   CComObject<CCompositeSection>* pCompSect;
   CComObject<CCompositeSection>::CreateInstance(&pCompSect);
   m_Section = pCompSect;

   // Add a section for the beam.
   // Use a dummy shape to keep everybody happy
   CComPtr<IRectangle> beam;
   beam.CoCreateInstance(CLSID_Rect);
   CComQIPtr<IShape> beamShape(beam);
   m_Section->AddSection(beamShape,1.0,1.0,VARIANT_FALSE,VARIANT_TRUE);

   // Add the slab haunch
   // Initial dimensions = 0x0
   CComPtr<IShape> haunchShape;
   haunchShape.CoCreateInstance(CLSID_Rect);
   m_Section->AddSection(haunchShape,1.0,1.0,VARIANT_FALSE,VARIANT_TRUE);

   // Add the main slab
   CComPtr<IShape> slabShape;
   slabShape.CoCreateInstance(CLSID_Rect);
   m_Section->AddSection(slabShape,1.0,1.0,VARIANT_FALSE,VARIANT_TRUE);

   // Add the left tributary slab area
   CComPtr<IShape> leftShape;
   leftShape.CoCreateInstance(CLSID_Rect);
   m_Section->AddSection(leftShape,1.0,1.0,VARIANT_FALSE,VARIANT_FALSE);

   // Add the right tributary slab area
   CComPtr<IShape> rightShape;
   rightShape.CoCreateInstance(CLSID_Rect);
   m_Section->AddSection(rightShape,1.0,1.0,VARIANT_FALSE,VARIANT_FALSE);

   // Add the wearing surface (non-structural)
   CComPtr<IShape> wsShape;
   wsShape.CoCreateInstance(CLSID_Rect);
   m_Section->AddSection(wsShape,1.0,1.0,VARIANT_FALSE,VARIANT_FALSE);

   UpdateShapeLocations();

   return S_OK;
}

void CCompositeBeam::UpdateShapeLocations()
{
   // Get IXYPosition interface for all of the shapes
   CComPtr<ICompositeSectionItem> beamItem;
   m_Section->get_Item(BEAM,&beamItem);

   CComPtr<IShape> beamShape;
   beamItem->get_Shape(&beamShape);

   CComQIPtr<IXYPosition> beamPosition(beamShape);
   //
   CComPtr<ICompositeSectionItem> haunchItem;
   m_Section->get_Item(HAUNCH,&haunchItem);
   
   CComPtr<IShape> haunchShape;
   haunchItem->get_Shape(&haunchShape);

   CComQIPtr<IXYPosition> haunchPosition(haunchShape);
   //
   CComPtr<ICompositeSectionItem> slabItem;
   m_Section->get_Item(SLAB,&slabItem);
   
   CComPtr<IShape> slabShape;
   slabItem->get_Shape(&slabShape);

   CComQIPtr<IXYPosition> slabPosition(slabShape);
   //
   CComPtr<ICompositeSectionItem> leftItem;
   m_Section->get_Item(TRIB_LEFT,&leftItem);

   CComPtr<IShape> leftShape;
   leftItem->get_Shape(&leftShape);

   CComQIPtr<IXYPosition> leftPosition(leftShape);
   //
   CComPtr<ICompositeSectionItem> rightItem;
   m_Section->get_Item(TRIB_RIGHT,&rightItem);

   CComPtr<IShape> rightShape;
   rightItem->get_Shape(&rightShape);

   CComQIPtr<IXYPosition> rightPosition(rightShape);
   //
   CComPtr<ICompositeSectionItem> wsItem;
   m_Section->get_Item(WS,&wsItem);
   
   CComPtr<IShape> wsShape;
   wsItem->get_Shape(&wsShape);

   CComQIPtr<IXYPosition> wsPosition(wsShape);

   // Align bottom center of haunch on top center of beam
   CComPtr<IPoint2d> beamTopCenter;
   beamPosition->get_LocatorPoint(lpTopCenter,&beamTopCenter);
   haunchPosition->put_LocatorPoint(lpBottomCenter,beamTopCenter);

   // Align bottom center of slab with top center of haunch
   CComPtr<IPoint2d> haunchTopCenter;
   haunchPosition->get_LocatorPoint(lpTopCenter,&haunchTopCenter);
   slabPosition->put_LocatorPoint(lpBottomCenter,haunchTopCenter);

   // Align bottom center of wearing surface with top center of slab
   CComPtr<IPoint2d> slabTopCenter;
   slabPosition->get_LocatorPoint(lpTopCenter,&slabTopCenter);
   wsPosition->put_LocatorPoint(lpBottomCenter,slabTopCenter);

   // Align the bottom right of the left tributary area with the 
   // bottom left of the main slab
   CComPtr<IPoint2d> slabBottomLeft;
   slabPosition->get_LocatorPoint(lpBottomLeft,&slabBottomLeft);
   leftPosition->put_LocatorPoint(lpBottomRight,slabBottomLeft);

   // Align the bottom left of the right tributary area with the
   // bottom right of the main slab
   CComPtr<IPoint2d> slabBottomRight;
   slabPosition->get_LocatorPoint(lpBottomRight,&slabBottomRight);
   rightPosition->put_LocatorPoint(lpBottomLeft,slabBottomRight);
}

STDMETHODIMP CCompositeBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICompositeBeam,
      &IID_ISection,
      &IID_IXYPosition,
		&IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCompositeBeam::get_Beam(IShape **pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<ICompositeSectionItem> item;
   m_Section->get_Item(0,&item);
   item->get_Shape(pVal);

	return S_OK;
}

STDMETHODIMP CCompositeBeam::putref_Beam(IShape *newVal)
{
   CHECK_IN(newVal);

   CComPtr<ICompositeSectionItem> item;
   m_Section->get_Item(BEAM,&item);
   item->putref_Shape(newVal);

   UpdateShapeLocations();

	return S_OK;
}

STDMETHODIMP CCompositeBeam::put_SacrificialDepth(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   CComPtr<ICompositeSectionItem> slabItem;
   CComPtr<IShape> slabShape;

   m_Section->get_Item(SLAB,&slabItem);
   slabItem->get_Shape(&slabShape);
   CComQIPtr<IRectangle> slab(slabShape);

   CComPtr<ICompositeSectionItem> wsItem;
   CComPtr<IShape> wsShape;
   m_Section->get_Item(WS,&wsItem);
   wsItem->get_Shape(&wsShape);
   CComQIPtr<IRectangle> ws(wsShape);

   Float64 slabDepth;
   Float64 wsDepth;
   Float64 grossSlabDepth;

   slab->get_Height(&slabDepth);
   ws->get_Height(&wsDepth);

   grossSlabDepth = slabDepth + wsDepth;

   slabDepth = grossSlabDepth - newVal;
   wsDepth = newVal;

   slab->put_Height(slabDepth);
   ws->put_Height(wsDepth);

   UpdateShapeLocations();

	return S_OK;
}

STDMETHODIMP CCompositeBeam::get_SacrificialDepth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<ICompositeSectionItem> wsItem;
   CComPtr<IShape> wsShape;
   m_Section->get_Item(WS,&wsItem);
   wsItem->get_Shape(&wsShape);
   CComQIPtr<IRectangle> ws(wsShape);
   ws->get_Height(pVal);

	return S_OK;
}

STDMETHODIMP CCompositeBeam::put_GrossSlabDepth(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   CComPtr<ICompositeSectionItem> slabItem;
   CComPtr<IShape> slabShape;

   m_Section->get_Item(SLAB,&slabItem);
   slabItem->get_Shape(&slabShape);
   CComQIPtr<IRectangle> slab(slabShape);

   CComPtr<ICompositeSectionItem> wsItem;
   CComPtr<IShape> wsShape;
   m_Section->get_Item(WS,&wsItem);
   wsItem->get_Shape(&wsShape);
   CComQIPtr<IRectangle> ws(wsShape);

   CComPtr<ICompositeSectionItem> leftItem;
   CComPtr<IShape> leftShape;
   m_Section->get_Item(TRIB_LEFT,&leftItem);
   leftItem->get_Shape(&leftShape);
   CComQIPtr<IRectangle> left(leftShape);

   CComPtr<ICompositeSectionItem> rightItem;
   CComPtr<IShape> rightShape;
   m_Section->get_Item(TRIB_RIGHT,&rightItem);
   rightItem->get_Shape(&rightShape);
   CComQIPtr<IRectangle> right(rightShape);

   Float64 slabDepth;
   Float64 wsDepth;
   Float64 grossSlabDepth;

   ws->get_Height(&wsDepth);

   grossSlabDepth = newVal;
   slabDepth = grossSlabDepth - wsDepth;

   slab->put_Height(slabDepth);
   ws->put_Height(wsDepth);

   left->put_Height(grossSlabDepth);
   right->put_Height(grossSlabDepth);

   UpdateShapeLocations();

	return S_OK;
}

STDMETHODIMP CCompositeBeam::get_GrossSlabDepth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<ICompositeSectionItem> wsItem;
   CComPtr<IShape> wsShape;
   m_Section->get_Item(WS,&wsItem);
   wsItem->get_Shape(&wsShape);
   CComQIPtr<IRectangle> ws(wsShape);
   Float64 wsDepth;
   ws->get_Height(&wsDepth);

   CComPtr<ICompositeSectionItem> slabItem;
   CComPtr<IShape> slabShape;
   m_Section->get_Item(SLAB,&slabItem);
   slabItem->get_Shape(&slabShape);
   CComQIPtr<IRectangle> slab(slabShape);
   Float64 slabDepth;
   slab->get_Height(&slabDepth);

   *pVal = slabDepth + wsDepth;

	return S_OK;
}

STDMETHODIMP CCompositeBeam::put_EffectiveSlabWidth(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   Float64 tribWidth;
   get_TributarySlabWidth(&tribWidth);
   
   CComPtr<ICompositeSectionItem> slabItem;
   CComPtr<IShape> slabShape;
   m_Section->get_Item(SLAB,&slabItem);
   slabItem->get_Shape(&slabShape);
   CComQIPtr<IRectangle> slab(slabShape);
   slab->put_Width(newVal);

   CComPtr<ICompositeSectionItem> wsItem;
   CComPtr<IShape> wsShape;
   m_Section->get_Item(WS,&wsItem);
   wsItem->get_Shape(&wsShape);
   CComQIPtr<IRectangle> ws(wsShape);
   ws->put_Width(newVal);

   CComPtr<ICompositeSectionItem> leftItem;
   CComPtr<IShape> leftShape;
   m_Section->get_Item(TRIB_LEFT,&leftItem);
   leftItem->get_Shape(&leftShape);
   CComQIPtr<IRectangle> left(leftShape);

   CComPtr<ICompositeSectionItem> rightItem;
   CComPtr<IShape> rightShape;
   m_Section->get_Item(TRIB_RIGHT,&rightItem);
   rightItem->get_Shape(&rightShape);
   CComQIPtr<IRectangle> right(rightShape);

   Float64 overhang = (tribWidth - newVal) / 2;
   if ( overhang < 0 )
      overhang = 0;

   left->put_Width(overhang);
   right->put_Width(overhang);

   return S_OK;
}

STDMETHODIMP CCompositeBeam::get_EffectiveSlabWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<ICompositeSectionItem> slabItem;
   CComPtr<IShape> slabShape;
   m_Section->get_Item(SLAB,&slabItem);
   slabItem->get_Shape(&slabShape);
   CComQIPtr<IRectangle> slab(slabShape);
   slab->get_Width(pVal);

   return S_OK;
}

STDMETHODIMP CCompositeBeam::put_TributarySlabWidth(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   Float64 effWidth;
   get_EffectiveSlabWidth(&effWidth);

   if (newVal < effWidth)
      effWidth = newVal;

   CComPtr<ICompositeSectionItem> slabItem;
   CComPtr<IShape> slabShape;
   m_Section->get_Item(SLAB,&slabItem);
   slabItem->get_Shape(&slabShape);
   CComQIPtr<IRectangle> slab(slabShape);
   slab->put_Width(effWidth);

   CComPtr<ICompositeSectionItem> wsItem;
   CComPtr<IShape> wsShape;
   m_Section->get_Item(WS,&wsItem);
   wsItem->get_Shape(&wsShape);
   CComQIPtr<IRectangle> ws(wsShape);
   ws->put_Width(effWidth);

   CComPtr<ICompositeSectionItem> leftItem;
   CComPtr<IShape> leftShape;
   m_Section->get_Item(TRIB_LEFT,&leftItem);
   leftItem->get_Shape(&leftShape);
   CComQIPtr<IRectangle> left(leftShape);

   CComPtr<ICompositeSectionItem> rightItem;
   CComPtr<IShape> rightShape;
   m_Section->get_Item(TRIB_RIGHT,&rightItem);
   rightItem->get_Shape(&rightShape);
   CComQIPtr<IRectangle> right(rightShape);


   Float64 overhang = (newVal - effWidth) / 2;
   if ( overhang < 0 )
      overhang = 0;

   left->put_Width(overhang);
   right->put_Width(overhang);


   return S_OK;
}

STDMETHODIMP CCompositeBeam::get_TributarySlabWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 effWidth,leftOverhang,rightOverhang;

   CComPtr<ICompositeSectionItem> slabItem;
   CComPtr<IShape> slabShape;
   m_Section->get_Item(SLAB,&slabItem);
   slabItem->get_Shape(&slabShape);
   CComQIPtr<IRectangle> slab(slabShape);
   slab->get_Width(&effWidth);

   CComPtr<ICompositeSectionItem> leftItem;
   CComPtr<IShape> leftShape;
   m_Section->get_Item(TRIB_LEFT,&leftItem);
   leftItem->get_Shape(&leftShape);
   CComQIPtr<IRectangle> left(leftShape);
   left->get_Width(&leftOverhang);

   CComPtr<ICompositeSectionItem> rightItem;
   CComPtr<IShape> rightShape;
   m_Section->get_Item(TRIB_RIGHT,&rightItem);
   rightItem->get_Shape(&rightShape);
   CComQIPtr<IRectangle> right(rightShape);
   right->get_Width(&rightOverhang);

   *pVal = leftOverhang + effWidth + rightOverhang;

   return S_OK;
}

STDMETHODIMP CCompositeBeam::get_SlabE(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<ICompositeSectionItem> slabItem;
   m_Section->get_Item(SLAB,&slabItem);
   slabItem->get_E(pVal);

   return S_OK;
}

STDMETHODIMP CCompositeBeam::put_SlabE(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   CComPtr<ICompositeSectionItem> slabItem;
   m_Section->get_Item(SLAB,&slabItem);
   slabItem->put_E(newVal);

   CComPtr<ICompositeSectionItem> wsItem;
   m_Section->get_Item(WS,&wsItem);
   wsItem->put_E(newVal);

   CComPtr<ICompositeSectionItem> haunchItem;
   m_Section->get_Item(HAUNCH,&haunchItem);
   haunchItem->put_E(newVal);

   CComPtr<ICompositeSectionItem> leftItem;
   m_Section->get_Item(TRIB_LEFT,&leftItem);
   leftItem->put_E(newVal);

   CComPtr<ICompositeSectionItem> rightItem;
   m_Section->get_Item(TRIB_RIGHT,&rightItem);
   rightItem->put_E(newVal);

   return S_OK;
}

STDMETHODIMP CCompositeBeam::get_SlabDensity(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<ICompositeSectionItem> slabItem;
   m_Section->get_Item(SLAB,&slabItem);
   slabItem->get_Density(pVal);

   return S_OK;
}

STDMETHODIMP CCompositeBeam::put_SlabDensity(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   CComPtr<ICompositeSectionItem> slabItem;
   m_Section->get_Item(SLAB,&slabItem);
   slabItem->put_Density(newVal);

   CComPtr<ICompositeSectionItem> wsItem;
   m_Section->get_Item(WS,&wsItem);
   wsItem->put_Density(newVal);

   CComPtr<ICompositeSectionItem> haunchItem;
   m_Section->get_Item(HAUNCH,&haunchItem);
   haunchItem->put_Density(newVal);

   CComPtr<ICompositeSectionItem> leftItem;
   m_Section->get_Item(TRIB_LEFT,&leftItem);
   leftItem->put_Density(newVal);

   CComPtr<ICompositeSectionItem> rightItem;
   m_Section->get_Item(TRIB_RIGHT,&rightItem);
   rightItem->put_Density(newVal);

   return S_OK;
}

STDMETHODIMP CCompositeBeam::get_HaunchWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<ICompositeSectionItem> haunchItem;
   CComPtr<IShape> haunchShape;
   m_Section->get_Item(HAUNCH,&haunchItem);
   haunchItem->get_Shape(&haunchShape);
   CComQIPtr<IRectangle> haunch(haunchShape);
   haunch->get_Width(pVal);

   return S_OK;
}

STDMETHODIMP CCompositeBeam::put_HaunchWidth(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   CComPtr<ICompositeSectionItem> haunchItem;
   CComPtr<IShape> haunchShape;
   m_Section->get_Item(HAUNCH,&haunchItem);
   haunchItem->get_Shape(&haunchShape);
   CComQIPtr<IRectangle> haunch(haunchShape);
   haunch->put_Width(newVal);

	return S_OK;
}

STDMETHODIMP CCompositeBeam::get_HaunchDepth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<ICompositeSectionItem> haunchItem;
   CComPtr<IShape> haunchShape;
   m_Section->get_Item(HAUNCH,&haunchItem);
   haunchItem->get_Shape(&haunchShape);
   CComQIPtr<IRectangle> haunch(haunchShape);
   haunch->get_Height(pVal);

   return S_OK;
}

STDMETHODIMP CCompositeBeam::put_HaunchDepth(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   CComPtr<ICompositeSectionItem> haunchItem;
   CComPtr<IShape> haunchShape;
   m_Section->get_Item(HAUNCH,&haunchItem);
   haunchItem->get_Shape(&haunchShape);
   CComQIPtr<IRectangle> haunch(haunchShape);
   haunch->put_Height(newVal);

   UpdateShapeLocations();

	return S_OK;
}

STDMETHODIMP CCompositeBeam::get_Section(ISection **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_ISection, (void**)pVal );
}

STDMETHODIMP CCompositeBeam::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

STDMETHODIMP CCompositeBeam::get_BeamE(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<ICompositeSectionItem> beamItem;
   m_Section->get_Item(BEAM,&beamItem);
   beamItem->get_E(pVal);

   return S_OK;
}

STDMETHODIMP CCompositeBeam::put_BeamE(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   CComPtr<ICompositeSectionItem> beamItem;
   m_Section->get_Item(BEAM,&beamItem);
   return beamItem->put_E(newVal);
}

STDMETHODIMP CCompositeBeam::get_BeamDensity(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<ICompositeSectionItem> beamItem;
   m_Section->get_Item(BEAM,&beamItem);
   beamItem->get_Density(pVal);

   return S_OK;
}

STDMETHODIMP CCompositeBeam::put_BeamDensity(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   CComPtr<ICompositeSectionItem> beamItem;
   m_Section->get_Item(BEAM,&beamItem);
   return beamItem->put_Density(newVal);
}

STDMETHODIMP CCompositeBeam::get_QSlab(Float64 *pVal)
{
   // Need to determine height of beam
   CComPtr<ICompositeSectionItem> item;
   m_Section->get_Item(BEAM,&item);

   CComPtr<IShape> shape;
   item->get_Shape(&shape);

   CComPtr<IShapeProperties> props;
   shape->get_ShapeProperties(&props);

   Float64 ytop, ybot;
   props->get_Ytop(&ytop);
   props->get_Ybottom(&ybot);

   Float64 location = ytop + ybot;

   return get_Q(location,pVal);
}

STDMETHODIMP CCompositeBeam::get_Q(Float64 location, Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   if ( location < 0 )
      return E_INVALIDARG;

   CComPtr<IPoint2d> p1;
   CComPtr<IPoint2d> p2;
   p1.CoCreateInstance(CLSID_Point2d);
   p2.CoCreateInstance(CLSID_Point2d);

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);

   CComPtr<IElasticProperties> props;
   get_ElasticProperties(&props);

   CComPtr<IPoint2d> cg;
   props->get_Centroid(&cg);
   Float64 cx,cy;
   cg->get_X(&cx);
   cg->get_Y(&cy);

   Float64 xleft, xright, ybottom;
   props->get_Xleft(&xleft);
   props->get_Xright(&xright);
   props->get_Ybottom(&ybottom);

   Float64 y = cy - ybottom + location;

   p1->Move(cx + 2*xleft,y);
   p2->Move(cx - 2*xleft,y);
   line->ThroughPoints(p1,p2);

   CComPtr<ISection> section;
   ClipWithLine(line,&section); // Removes all portions of the section left of the line

   if ( section == NULL )
   {
      *pVal = 0;
      return S_OK;
   }
   else
   {
      CComPtr<IElasticProperties> clipEProps;
      section->get_ElasticProperties(&clipEProps);

      // Transform into beam material
      CComPtr<ICompositeSectionItem> item;
      m_Section->get_Item(BEAM,&item);
      Float64 beamE;
      item->get_E(&beamE);

      CComPtr<IShapeProperties> clipProps;
      clipEProps->TransformProperties(beamE,&clipProps);

      // Get area above/below the clipping line
      Float64 area;
      clipProps->get_Area(&area);

      // get the centroid of the clipped shape
      CComPtr<IPoint2d> clipCG;
      clipProps->get_Centroid(&clipCG);
      Float64 cgy;
      clipCG->get_Y(&cgy);

      // compute the first moment of area
      *pVal = area*(cgy - cy);

      return S_OK;
   }
}


STDMETHODIMP CCompositeBeam::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

/////////////////////////////////////////////////
// ISection
STDMETHODIMP CCompositeBeam::get_BoundingBox(IRect2d* *pVal)
{
   CComQIPtr<ISection> section(m_Section);
   return section->get_BoundingBox(pVal);
}

STDMETHODIMP CCompositeBeam::get_ElasticProperties(IElasticProperties* *pVal)
{
   CComQIPtr<ISection> section(m_Section);
   return section->get_ElasticProperties(pVal);
}

STDMETHODIMP CCompositeBeam::get_MassProperties(IMassProperties* *pVal)
{
   CComQIPtr<ISection> section(m_Section);
   return section->get_MassProperties(pVal);
}

STDMETHODIMP CCompositeBeam::ClipIn(IRect2d* rect, ISection** section)
{
   CComQIPtr<ISection> s(m_Section);
   return s->ClipIn(rect,section);
}

STDMETHODIMP CCompositeBeam::ClipWithLine(ILine2d* line,ISection** section)
{
   CComQIPtr<ISection> s(m_Section);
   return s->ClipWithLine(line,section);
}

STDMETHODIMP CCompositeBeam::Clone(ISection** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CCompositeBeam>* theClone;
   CComObject<CCompositeBeam>::CreateInstance(&theClone);

   CComPtr<ISection> clone_of_sections;
   CComQIPtr<ISection> mySection(m_Section);
   mySection->Clone(&clone_of_sections);

   CComQIPtr<ICompositeSection> compSection(clone_of_sections);
   theClone->m_Section = compSection;

   (*clone) = theClone;
   (*clone)->AddRef();

	return S_OK;
}

/////////////////////////////////////////////////
// IXYPosition
STDMETHODIMP CCompositeBeam::Offset(Float64 dx,Float64 dy)
{
   CComQIPtr<IXYPosition> position(m_Section);
   return position->Offset(dx,dy);
}

STDMETHODIMP CCompositeBeam::OffsetEx(ISize2d* pSize)
{
   CComQIPtr<IXYPosition> position(m_Section);
   return position->OffsetEx(pSize);
}

STDMETHODIMP CCompositeBeam::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CComQIPtr<IXYPosition> position(m_Section);
   return position->get_LocatorPoint(lp,point);
}

STDMETHODIMP CCompositeBeam::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CComQIPtr<IXYPosition> position(m_Section);
   return position->put_LocatorPoint(lp,point);
}

STDMETHODIMP CCompositeBeam::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   CComQIPtr<IXYPosition> position(m_Section);
   return position->MoveEx(pFrom,pTo);
}

STDMETHODIMP CCompositeBeam::RotateEx( IPoint2d* pPoint, Float64 angle)
{
   CComQIPtr<IXYPosition> position(m_Section);
   return position->RotateEx(pPoint,angle);
}

STDMETHODIMP CCompositeBeam::Rotate( Float64 cx, Float64 cy, Float64 angle)
{
   CComQIPtr<IXYPosition> position(m_Section);
   return position->Rotate(cx,cy,angle);
}

// IStructuredStorage2
STDMETHODIMP CCompositeBeam::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("CompositeBeam"),1.0);
   pSave->put_Property(CComBSTR("Section"),CComVariant(m_Section));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CCompositeBeam::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("CompositeBeam"));

   pLoad->get_Property(CComBSTR("Section"),&var);
   if ( FAILED( _CopyVariantToInterface<ICompositeSection>::copy(&m_Section,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
