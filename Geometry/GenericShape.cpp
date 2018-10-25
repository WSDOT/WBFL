///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2013  Washington State Department of Transportation
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

// GenericShape.cpp : Implementation of CGenericShape
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "GenericShape.h"
#include "Helper.h"
#include <MathEx.h>
#include <WBFLTools.h> // IMohrCircle

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenericShape
STDMETHODIMP CGenericShape::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IGenericShape,
		&IID_IShape,
		&IID_IXYPosition,
		&IID_IStructuredStorage2,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CGenericShape::FinalConstruct()
{
   m_Area      = 0.0;
   m_Ixx       = 0.0;
   m_Iyy       = 0.0;
   m_Ixy       = 0.0;
   m_Perimeter = 0.0;
   m_Rotation  = 0.0;

   HRESULT hr = CreatePoint(0.00,0.00,NULL,&m_pCG);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_pCG, this, IID_IPoint2dEvents, &m_cgCookie);
   if (FAILED(hr))
      return hr;

   hr = m_MohrCircle.CoCreateInstance( CLSID_MohrCircle );
   if (FAILED(hr))
      return hr;

   hr = m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

void CGenericShape::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pCG, this, IID_IPoint2dEvents, m_cgCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CGenericShape::get_Area(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Area;
   return S_OK;
}

STDMETHODIMP CGenericShape::put_Area(Float64 newVal)
{
   m_Area = newVal;
   return S_OK;
}

STDMETHODIMP CGenericShape::put_Perimeter(Float64 newVal)
{
   m_Perimeter = newVal;
   return S_OK;
}

STDMETHODIMP CGenericShape::get_Centroid(IPoint2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   m_pCG->QueryInterface( pVal );

   return S_OK;
}

STDMETHODIMP CGenericShape::putref_Centroid(IPoint2d* newVal)
{
   CHECK_IN(newVal);
   HRESULT hr = CrAssignPointer(m_pCG, newVal, this, IID_IPoint2dEvents, &m_cgCookie);
   return hr;
}

STDMETHODIMP CGenericShape::get_Ixx(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Ixx;
   return S_OK;
}

STDMETHODIMP CGenericShape::put_Ixx(Float64 newVal)
{
   m_Ixx = newVal;
   return S_OK;
}

STDMETHODIMP CGenericShape::get_Iyy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Iyy;
   return S_OK;
}

STDMETHODIMP CGenericShape::put_Iyy(Float64 newVal)
{
   m_Iyy = newVal;
   return S_OK;
}

STDMETHODIMP CGenericShape::get_Ixy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Ixy;
   return S_OK;
}

STDMETHODIMP CGenericShape::put_Ixy(Float64 newVal)
{
   m_Ixy = newVal;
   return S_OK;
}

STDMETHODIMP CGenericShape::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CGenericShape::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CGenericShape::get_ShapeProperties(IShapeProperties* *props)
{
   CHECK_RETOBJ(props);

   // rotate properties into correct orientation.
   m_MohrCircle->put_Sii( m_Ixx );
   m_MohrCircle->put_Sjj( m_Iyy );
   m_MohrCircle->put_Sij( m_Ixy );

   Float64 ixx, ixy, iyy;
   m_MohrCircle->ComputeState( m_Rotation, &ixx, &iyy, &ixy );

   HRESULT hr = CreateShapeProperties(props);
   if (FAILED(hr))
      return hr;

   Float64 cx,cy;
   m_pCG->Location(&cx,&cy);

   (*props)->put_Area(    m_Area );
   (*props)->put_Ixx(     ixx    );
   (*props)->put_Iyy(     iyy    );
   (*props)->put_Ixy(     ixy    );
   (*props)->put_Xleft(   0.0    );
   (*props)->put_Xright(  0.0    );
   (*props)->put_Ytop(    0.0    );
   (*props)->put_Ybottom( 0.0    );

   CComPtr<IPoint2d> centroid;
   centroid.CoCreateInstance(CLSID_Point2d);
   centroid->put_X(cx);
   centroid->put_Y(cy);
   (*props)->put_Centroid( centroid );

   (*props)->put_CoordinateSystem( csCentroidal );

   return S_OK;
}

STDMETHODIMP CGenericShape::get_BoundingBox(IRect2d* *rect)
{
   CHECK_RETOBJ(rect);

   Float64 cx,cy;
   m_pCG->Location(&cx,&cy);

   return ::CreateRect(cx, cy, cx, cy, rect);
}

STDMETHODIMP CGenericShape::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   CComPtr<IPoint2d> cg;
   m_pCG->Clone(&cg);

   HRESULT hr = CreatePointCollection(ppPolyPoints);
   if ( FAILED(hr) )
      return hr;

   (*ppPolyPoints)->Add(cg);

   return S_OK;
}

STDMETHODIMP CGenericShape::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   *pbResult = (m_pCG->SameLocation(pPoint) == S_OK ? VARIANT_TRUE : VARIANT_FALSE);
   return S_OK;
}

STDMETHODIMP CGenericShape::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CGenericShape>* pTheClone;
   HRESULT hr = CComObject<CGenericShape>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IGenericShape> pGenericShape(pTheClone); // hang on to a reference

   pTheClone->put_Area(m_Area);
   pTheClone->put_Perimeter(m_Perimeter);
   pTheClone->put_Ixx(m_Ixx);
   pTheClone->put_Iyy(m_Iyy);
   pTheClone->put_Ixy(m_Ixy);

   CComPtr<IPoint2d> cg;
   hr = CreatePoint(m_pCG,NULL,&cg);
   pTheClone->putref_Centroid( cg );
   pTheClone->RotateEx( m_pCG, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CGenericShape::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   // if CG is on the right of the line, create a clone, otherwise
   // consider the shape to be clipped away

   Float64 d;
   m_GeomUtil->ShortestDistanceToPoint(pLine,m_pCG,&d);
   if ( d < 0 )
   {
      // CG is on the left side of the line
      *pShape = NULL;
   }
   else
   {
      // CG is on the right side of the line
      Clone(pShape);
   }

   return S_OK;
}

STDMETHODIMP CGenericShape::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   VARIANT_BOOL vbContainsPoint;
   pRect->ContainsPoint(m_pCG,&vbContainsPoint);
   if ( vbContainsPoint == VARIANT_TRUE )
   {
      // shape is inside of clipping rect
      Clone(pShape);
   }
   else
   {
      // shape is outside of clipping rect
      *pShape = NULL;
   }

   return S_OK;
}

STDMETHODIMP CGenericShape::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Perimeter;
   return S_OK;
}

STDMETHODIMP CGenericShape::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);

   m_GeomUtil->ShortestDistanceToPoint(line,m_pCG,pVal);
   
   return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CGenericShape::Offset(Float64 dx,Float64 dy)
{
   return m_pCG->Offset(dx,dy);
}

STDMETHODIMP CGenericShape::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);
   return m_pCG->OffsetEx(pSize);
}

STDMETHODIMP CGenericShape::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);
   // this shape doesn't have any "size" so all points on the bounding box
   // are at the CG
   return m_pCG->QueryInterface( point );
}

STDMETHODIMP CGenericShape::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CHECK_IN(point);
   return m_pCG->MoveEx(point);
}

STDMETHODIMP CGenericShape::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   CHECK_IN(pFrom);
   CHECK_IN(pTo);

   Float64 x1,y1;
   Float64 x2,y2;

   pFrom->Location(&x1,&y1);
   pTo->Location(&x2,&y2);

   m_pCG->Offset( x2-x1, y2-y1 );

   return S_OK;
}

STDMETHODIMP CGenericShape::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   pPoint->Location(&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CGenericShape::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_pCG->Rotate(cx,cy,angle);
   m_Rotation += angle;
   return S_OK;
}


STDMETHODIMP CGenericShape::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CGenericShape::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CGenericShape::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("GenericShape"),1.0);
   pSave->put_Property(CComBSTR("Area"),CComVariant(m_Area));
   pSave->put_Property(CComBSTR("Perimeter"),CComVariant(m_Perimeter));
   pSave->put_Property(CComBSTR("Ixx"),CComVariant(m_Ixx));
   pSave->put_Property(CComBSTR("Iyy"),CComVariant(m_Iyy));
   pSave->put_Property(CComBSTR("Ixy"),CComVariant(m_Ixy));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("Centroid"),CComVariant(m_pCG));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CGenericShape::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("GenericShape"));

   pLoad->get_Property(CComBSTR("Area"),&var);
   m_Area = var.dblVal;

   pLoad->get_Property(CComBSTR("Perimeter"),&var);
   m_Perimeter = var.dblVal;

   pLoad->get_Property(CComBSTR("Ixx"),&var);
   m_Ixx = var.dblVal;

   pLoad->get_Property(CComBSTR("Iyy"),&var);
   m_Iyy = var.dblVal;

   pLoad->get_Property(CComBSTR("Ixy"),&var);
   m_Ixy = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Rotation"),&var);
   m_Rotation = var.dblVal;

   pLoad->get_Property(CComBSTR("Centroid"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_pCG,&var)) )
      return STRLOAD_E_INVALIDFORMAT;


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

STDMETHODIMP CGenericShape::OnPointChanged(IPoint2d* point)
{
   return S_OK;
}
