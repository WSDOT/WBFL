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

// VoidedSlabSection.cpp : Implementation of CVoidedSlabSection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "VoidedSlabSection.h"
#include <math.h>
#include <xutility> // for _cpp_min

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVoidedSlabSection
HRESULT CVoidedSlabSection::FinalConstruct()
{
   m_CompositeShape.CoCreateInstance(CLSID_CompositeShape);
   m_CompositeShape.QueryInterface(&m_Shape);
   m_CompositeShape.QueryInterface(&m_Position);

   m_Beam.CoCreateInstance(CLSID_VoidedSlab);
   CComQIPtr<IShape> shape(m_Beam);
   m_CompositeShape->AddShape(shape,VARIANT_FALSE);

   return S_OK;
}

void CVoidedSlabSection::FinalRelease()
{
}

STDMETHODIMP CVoidedSlabSection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVoidedSlabSection,
      &IID_IGirderSection,
      &IID_IShape,
      &IID_ICompositeShape,
      &IID_IXYPosition,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

bool CVoidedSlabSection::ValidateWebIndex(WebIndexType idx)
{
   WebIndexType nWebs;
   m_Beam->get_VoidCount(&nWebs);
   nWebs++; // there is one more "web" than voids

   return ( 0 <= idx && idx < nWebs );
}

void CVoidedSlabSection::GetWebs(Float64* pIntWeb,Float64* pExtWeb)
{
   Float64 S, D, W;
   CollectionIndexType N;
   m_Beam->get_VoidSpacing(&S);
   m_Beam->get_VoidDiameter(&D);
   m_Beam->get_Width(&W);
   m_Beam->get_VoidCount(&N);

   *pExtWeb = (W - D - (N-1)*S)/2;
   *pIntWeb = S - D;
}


////////////////////////////////////////////////////////////////////////
// IVoidedSlabSection implementation
STDMETHODIMP CVoidedSlabSection::put_Beam(IVoidedSlab* beam)
{
   CHECK_IN(beam);

   CComQIPtr<IShape> shape(beam);
   CHECK_IN(shape);

   CComPtr<IShape> clone;
   HRESULT hr = shape->Clone(&clone);
   ATLASSERT(SUCCEEDED(hr));

   m_Beam.Release();
   clone.QueryInterface(&m_Beam);
   m_Shape = clone;

   m_CompositeShape->Replace(0,m_Shape);

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_Beam(IVoidedSlab** beam)
{
   CHECK_RETOBJ(beam);
   (*beam) = m_Beam;
   (*beam)->AddRef();
   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IPrecastGirderSection implementation
STDMETHODIMP CVoidedSlabSection::get_WebCount(WebIndexType* nWebs)
{
   CHECK_RETVAL(nWebs);

   *nWebs = 0;
   return S_OK;

   // a voided slab doesn't have webs like and I-beam or a U-beam has webs
   // the correct web count is 0.

   //WebIndexType nVoids;
   //m_Beam->get_VoidCount(&nVoids);

   //*nWebs = nVoids + 1;
   //return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_WebLocation(WebIndexType idx,Float64* location)
{
   if ( !ValidateWebIndex(idx) )
      return E_INVALIDARG;

   CHECK_RETVAL(location);

   Float64 S, D, W;
   CollectionIndexType N;
   m_Beam->get_VoidSpacing(&S);
   m_Beam->get_VoidDiameter(&D);
   m_Beam->get_Width(&W);
   m_Beam->get_VoidCount(&N);

   Float64 end_webs, int_webs;
   end_webs = W - D - N*(S-1);
   int_webs = S - D;

   // location measured from left edge
   if ( idx == 0 )
      *location = end_webs/2;
   else if ( 0 < idx && idx < N )
      *location = end_webs + (idx-1)*(D+int_webs) + D + int_webs/2;
   else
      *location = N*S + 1.5*end_webs;

   // location measured from CL of section
   *location -= W/2;

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_WebSpacing(WebIndexType idx,Float64* spacing)
{
   if ( !ValidateWebIndex(idx) )
      return E_INVALIDARG;

   return m_Beam->get_VoidSpacing(spacing);
}

STDMETHODIMP CVoidedSlabSection::get_WebThickness(WebIndexType idx,Float64* tWeb)
{
   if ( !ValidateWebIndex(idx) )
      return E_INVALIDARG;

   CHECK_RETVAL(tWeb);

   CollectionIndexType nVoids;
   m_Beam->get_VoidCount(&nVoids);

   if ( nVoids == 0 )
   {
      m_Beam->get_Width(tWeb);
   }
   else
   {
      Float64 end_webs, int_webs;
      GetWebs(&int_webs,&end_webs);

      if ( idx == 0 || idx == nVoids)
         *tWeb = end_webs;
      else
         *tWeb = int_webs;
   }

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_MinWebThickness(Float64* tWeb)
{
   CHECK_RETVAL(tWeb);

   CollectionIndexType nVoids;
   m_Beam->get_VoidCount(&nVoids);

   if ( nVoids == 0 )
   {
      m_Beam->get_Width(tWeb);
   }
   else
   {
      Float64 end_webs, int_webs;
      GetWebs(&int_webs,&end_webs);

      *tWeb = _cpp_min(int_webs,end_webs);
   }

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_EffectiveWebThickness(Float64* tWeb)
{
   return get_MinWebThickness(tWeb);
}

STDMETHODIMP CVoidedSlabSection::get_WebPlane(WebIndexType idx,IPlane3d** ppPlane)
{
   CHECK_RETOBJ(ppPlane);

   Float64 x;
   HRESULT hr = get_WebLocation(idx,&x);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint3d> p1;
   p1.CoCreateInstance(CLSID_Point3d);
   p1->Move(x,0,0);

   CComPtr<IPoint3d> p2;
   p2.CoCreateInstance(CLSID_Point3d);
   p2->Move(x,100,0);

   CComPtr<IPoint3d> p3;
   p3.CoCreateInstance(CLSID_Point3d);
   p3->Move(x,0,100);

   CComPtr<IPlane3d> plane;
   plane.CoCreateInstance(CLSID_Plane3d);
   plane->ThroughPoints(p1,p2,p3);

   return plane.CopyTo(ppPlane);
}

STDMETHODIMP CVoidedSlabSection::get_MatingSurfaceCount(MatingSurfaceIndexType* nMatingSurfaces)
{
   CHECK_RETVAL(nMatingSurfaces);
   *nMatingSurfaces = 1;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_MatingSurfaceLocation(MatingSurfaceIndexType idx,Float64* location)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   *location = 0;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_MatingSurfaceWidth(MatingSurfaceIndexType idx,Float64* wMatingSurface)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   return get_TopWidth(wMatingSurface);
}

STDMETHODIMP CVoidedSlabSection::get_TopFlangeCount(FlangeIndexType* nTopFlanges)
{
   CHECK_RETVAL(nTopFlanges);
   *nTopFlanges = 0;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_TopFlangeLocation(FlangeIndexType idx,Float64* location)
{
   ATLASSERT(false); // there is no top flange!!!
   return E_INVALIDARG;
   //if ( idx != 0 )
   //   return E_INVALIDARG;

   //*location = 0;
   //return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_TopFlangeWidth(FlangeIndexType idx,Float64* width)
{
   ATLASSERT(false); // there is no top flange!!!
   return E_INVALIDARG;
   //if ( idx != 0 )
   //   return E_INVALIDARG;

   //return get_TopWidth(width);
}

STDMETHODIMP CVoidedSlabSection::get_TopFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   ATLASSERT(false); // there is no top flange!!!
   return E_INVALIDARG;
   //if ( idx != 0 )
   //   return E_INVALIDARG;

   //*tFlange = 0.0;
   //return S_OK;

   //Float64 H, D;
   //m_Beam->get_Height(&H);
   //m_Beam->get_VoidDiameter(&D);
   //*tFlange = (H-D)/2;

   //return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_TopFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   ATLASSERT(false); // there is no top flange!!!
   return E_INVALIDARG;
   //if ( idx != 0 )
   //   return E_INVALIDARG;

   //CHECK_RETVAL(spacing);

   //(*spacing) = 0;
   //
   //return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_BottomFlangeCount(FlangeIndexType* nBottomFlanges)
{
   CHECK_RETVAL(nBottomFlanges);
   *nBottomFlanges = 0;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_BottomFlangeLocation(FlangeIndexType idx,Float64* location)
{
   ATLASSERT(false); // there is no Bottom flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::get_BottomFlangeWidth(FlangeIndexType idx,Float64* width)
{
   ATLASSERT(false); // there is no Bottom flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::get_BottomFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   ATLASSERT(false); // there is no Bottom flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::get_BottomFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   ATLASSERT(false); // there is no Bottom flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::get_GirderHeight(Float64* height)
{
   return m_Beam->get_Height(height);
}

STDMETHODIMP CVoidedSlabSection::get_TopWidth(Float64* width)
{
   return m_Beam->get_Width(width);
}

STDMETHODIMP CVoidedSlabSection::get_BottomWidth(Float64* width)
{
   return m_Beam->get_Width(width);
}

STDMETHODIMP CVoidedSlabSection::get_ShearWidth(Float64* shearwidth)
{
   CHECK_RETVAL(shearwidth);

   CollectionIndexType nVoids;
   m_Beam->get_VoidCount(&nVoids);

   if ( nVoids == 0 )
   {
      m_Beam->get_Width(shearwidth);
   }
   else
   {
      Float64 end_webs, int_webs;
      GetWebs(&int_webs,&end_webs);

      *shearwidth = 2*end_webs + (nVoids-1)*int_webs;
   }

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_MinTopFlangeThickness(Float64* tf)
{
   return get_TopFlangeThickness(0,tf);
}

STDMETHODIMP CVoidedSlabSection::get_MinBottomFlangeThickness(Float64* tf)
{
   CHECK_RETVAL(*tf);
   *tf = 0;
   return S_OK;

   //Float64 H,D;
   //m_Beam->get_Height(&H);
   //m_Beam->get_VoidDiameter(&D);

   //*tf = (H-D)/2;

   //return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_CL2ExteriorWebDistance( DirectionType side, Float64* wd)
{
   HRESULT hr;
   CHECK_RETVAL(*wd);

   WebIndexType nWebs;
   WebIndexType nVoids;
   hr = m_Beam->get_VoidCount(&nVoids);
   if (FAILED(hr))
      return hr;

   nWebs = nVoids + 1;


   if (nWebs == 1)
   {
      *wd = 0.0;
   }
   else
   {
      // multiweb
      Float64 webwid = 0;

      for (WebIndexType is = 0; is < nWebs-1; is++)
      {
         Float64 spacing;

         hr = get_WebSpacing(is, &spacing);
         if (FAILED(hr))
            return hr;

         webwid += spacing;
      }

      *wd = webwid/2.0;
   }

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_SplittingZoneDimension(Float64* pSZD)
{
   CHECK_RETVAL(pSZD);

   Float64 w;
   m_Beam->get_Width(&w);

   *pSZD = w;

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_SplittingDirection(SplittingDirection* pSD)
{
   CHECK_RETVAL(pSD);
   *pSD = sdHorizontal;
   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IShape implementation
STDMETHODIMP CVoidedSlabSection::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   return m_Shape->FurthestDistance(line,pVal);
}

STDMETHODIMP CVoidedSlabSection::get_Perimeter(Float64 *pVal)
{
   return m_Shape->get_Perimeter(pVal);
}

STDMETHODIMP CVoidedSlabSection::get_ShapeProperties(IShapeProperties* *pVal)
{
   return m_Shape->get_ShapeProperties(pVal);
}

STDMETHODIMP CVoidedSlabSection::get_BoundingBox(IRect2d* *pVal)
{
   return m_Shape->get_BoundingBox(pVal);
}

STDMETHODIMP CVoidedSlabSection::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   return m_Shape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CVoidedSlabSection::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   return m_Shape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CVoidedSlabSection::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CVoidedSlabSection>* clone;
   CComObject<CVoidedSlabSection>::CreateInstance(&clone);

   CComPtr<IVoidedSlabSection> voided_slab_section = clone;
   voided_slab_section->put_Beam(m_Beam);

   CComQIPtr<IShape> shape(voided_slab_section);

   (*pClone) = shape;
   (*pClone)->AddRef();

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   return m_Shape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CVoidedSlabSection::ClipIn(IRect2d* pRect,IShape** pShape)
{
   return m_Shape->ClipIn(pRect,pShape);
}

/////////////////////////////////////////////////////////////////////////////
// ICompositeShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CVoidedSlabSection::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   return m_CompositeShape->get_StructuredStorage(pStg);
}

STDMETHODIMP CVoidedSlabSection::get_Shape(IShape* *pVal)
{
   return m_CompositeShape->get_Shape(pVal);
}

STDMETHODIMP CVoidedSlabSection::get_Item(CollectionIndexType idx,ICompositeShapeItem* *pVal)
{
   return m_CompositeShape->get_Item(idx,pVal);
}

STDMETHODIMP CVoidedSlabSection::get__NewEnum(IUnknown* *pVal)
{
   return m_CompositeShape->get__NewEnum(pVal);
}

STDMETHODIMP CVoidedSlabSection::get_Count(CollectionIndexType *pVal)
{
   return m_CompositeShape->get_Count(pVal);
}

STDMETHODIMP CVoidedSlabSection::Remove(CollectionIndexType idx)
{
   return m_CompositeShape->Remove(idx);
}

STDMETHODIMP CVoidedSlabSection::Clear()
{
   return m_CompositeShape->Clear();
}

STDMETHODIMP CVoidedSlabSection::ReplaceEx(CollectionIndexType idx,ICompositeShapeItem* pShapeItem)
{
   return m_CompositeShape->ReplaceEx(idx,pShapeItem);
}

STDMETHODIMP CVoidedSlabSection::Replace(CollectionIndexType idx,IShape* pShape)
{
   return m_CompositeShape->Replace(idx,pShape);
}

STDMETHODIMP CVoidedSlabSection::AddShapeEx(ICompositeShapeItem* ShapeItem)
{
   return m_CompositeShape->AddShapeEx(ShapeItem);
}

STDMETHODIMP CVoidedSlabSection::AddShape(IShape* shape,VARIANT_BOOL bVoid)
{
   return m_CompositeShape->AddShape(shape,bVoid);
}

// XYPosition
STDMETHODIMP CVoidedSlabSection::Offset(Float64 dx,Float64 dy)
{
   return m_Position->Offset(dx,dy);
}

STDMETHODIMP CVoidedSlabSection::OffsetEx(ISize2d* pSize)
{
   return m_Position->OffsetEx(pSize);
}

STDMETHODIMP CVoidedSlabSection::get_LocatorPoint(LocatorPointType lp,IPoint2d** point)
{
   return m_Position->get_LocatorPoint(lp,point);
}

STDMETHODIMP CVoidedSlabSection::put_LocatorPoint(LocatorPointType lp,IPoint2d* point)
{
   return m_Position->put_LocatorPoint(lp,point);
}

STDMETHODIMP CVoidedSlabSection::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   return m_Position->MoveEx(pFrom,pTo);
}

STDMETHODIMP CVoidedSlabSection::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   return m_Position->RotateEx(pPoint,angle);
}

STDMETHODIMP CVoidedSlabSection::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   return m_Position->Rotate(cx,cy,angle);
}
