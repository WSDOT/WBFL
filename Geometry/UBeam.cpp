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

// UBeam.cpp : Implementation of CUBeam 
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "UBeam.h"
#include "Helper.h"
#include <MathEx.h>
#include <float.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUBeam
HRESULT CUBeam::FinalConstruct()
{
   m_Rotation = 0.00;
   m_D1 = 0.00;
   m_D2 = 0.00;
   m_D3 = 0.00;
   m_D4 = 0.00;
   m_D5 = 0.00;
   m_D6 = 0.00;
   m_D7 = 0.00;
   m_T  = 0.00;
   m_W1 = 0.00;
   m_W2 = 0.00;
   m_W3 = 0.00;
   m_W4 = 0.00;
   m_W5 = 0.00;

   CreatePoint( 0.00, 0.00, NULL, &m_pHookPoint );
   HRESULT hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   CreatePolyShape( &m_pShape );

   m_Dirty = true;

   return S_OK;
}

void CUBeam::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}


STDMETHODIMP CUBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUBeam,
      &IID_IShape,
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

HRESULT CUBeam::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
{
   ATLASSERT(px != NULL && py != NULL);

   UpdateShape();

   CComPtr<IPoint2d> pPoint;

   CComQIPtr<IShape> pShape(m_pShape);
   CComPtr<IRect2d> pBox;
   pShape->get_BoundingBox(&pBox);

   switch(lp)
   {
   case lpTopLeft:
      pBox->get_TopLeft(&pPoint);
      break;

   case lpTopCenter:
      pBox->get_TopCenter(&pPoint);
      break;

   case lpTopRight:
      pBox->get_TopRight(&pPoint);
      break;

   case lpCenterLeft:
      pBox->get_CenterLeft(&pPoint);
      break;

   case lpCenterCenter:
      pBox->get_CenterCenter(&pPoint);
      break;

   case lpCenterRight:
      pBox->get_CenterRight(&pPoint);
      break;

   case lpBottomLeft: 
      pBox->get_BottomLeft(&pPoint);
      break;

   case lpBottomCenter: 
   case lpHookPoint:
      pBox->get_BottomCenter(&pPoint);
      break;

   case lpBottomRight:
      pBox->get_BottomRight(&pPoint);
      break;

   default:
      ATLASSERT(false); // Should never get here
   }

   GetCoordinates(pPoint,px,py);

   return S_OK;
}

HRESULT CUBeam::UpdateShape()
{
   if (m_Dirty)
   {
      // clear the polygon implemenation and recalculate all of the points
      m_pShape->Clear();

      // compute wall slope
      Float64 rise = m_D1 - m_D4 - m_D5;
      Float64 run = (m_W2 - m_W1)/2 - m_W5;

      Float64 slope;
      if ( IsZero(run) )
         slope = DBL_MAX;
      else
         slope = rise/run;

      Float64 T = m_T;
      if ( !IsZero(slope) )
         T = m_T*sqrt(slope*slope+1)/slope;

      // start at the bottom center and go around clockwise
      // Hook point is at bottom center (0,0)
      // Compute left side points, mirror for right side
      Float64 p1_x =  0.;
      Float64 p1_y =  0.;

      Float64 p2_x = -m_W1/2;
      Float64 p2_y =  0.;

      Float64 p3_x =  p2_x - (IsZero(slope) ? 0: (m_D1 - m_D4 - m_D5)/slope);
      Float64 p3_y =  m_D1 - m_D4 - m_D5;

      Float64 p4_x =  -m_W2/2;
      Float64 p4_y =  m_D1 - m_D4;

      Float64 p5_x =  -m_W2/2;
      Float64 p5_y =  m_D1;

      Float64 p6_x =  -m_W2/2 + m_W4 + m_W5 + T;
      Float64 p6_y =  m_D1;

      Float64 p7_x =  p6_x;
      Float64 p7_y =  m_D1 - m_D6;

      Float64 p8_x =  p7_x - m_W4;
      Float64 p8_y =  m_D1 - m_D6 - m_D7;

      Float64 p9_x =  p8_x + (IsZero(slope) ? 0 : (m_D1 - m_D2 - m_D3 - m_D6 - m_D7)/slope);
      Float64 p9_y =  m_D2 + m_D3;

      Float64 p10_x = p9_x + m_W3;
      Float64 p10_y = m_D2;

      m_pShape->AddPoint( p1_x, p1_y);  // 1
      m_pShape->AddPoint( p2_x, p2_y);
      m_pShape->AddPoint( p3_x, p3_y);
      m_pShape->AddPoint( p4_x, p4_y);
      m_pShape->AddPoint( p5_x, p5_y);
      m_pShape->AddPoint( p6_x, p6_y);
      m_pShape->AddPoint( p7_x, p7_y);
      m_pShape->AddPoint( p8_x, p8_y);
      m_pShape->AddPoint( p9_x, p9_y);
      m_pShape->AddPoint( p10_x, p10_y);

      // mirror points
      m_pShape->AddPoint(-p10_x, p10_y);
      m_pShape->AddPoint(-p9_x, p9_y);
      m_pShape->AddPoint(-p8_x, p8_y);
      m_pShape->AddPoint(-p7_x, p7_y);
      m_pShape->AddPoint(-p6_x, p6_y); 
      m_pShape->AddPoint(-p5_x, p5_y);
      m_pShape->AddPoint(-p4_x, p4_y);
      m_pShape->AddPoint(-p3_x, p3_y);
      m_pShape->AddPoint(-p2_x, p2_y);

      CComQIPtr<IXYPosition> pPosition(m_pShape);

      if (!IsZero(m_Rotation))
      {
         pPosition->Rotate(0.00,0.00,m_Rotation);
      }

      CComPtr<IPoint2d> origin;
      CreatePoint(0.00,0.00,NULL,&origin);  // Hook Point at Bottom Center
      pPosition->MoveEx(origin,m_pHookPoint);

//#ifdef _DEBUG
//      CComPtr<IPoint2dCollection> points;
//      m_pShape->get_Points(&points);
//      long npts;
//      points->get_Count(&npts);
//      ATLTRACE("Trace of Points for UBeam - count = %d \n", npts);
//      ATLTRACE("  pt         X         Y\n");
//      ATLTRACE("---------------------------------\n");
//      for (long ip=0; ip<npts; ip++)
//      {
//         CComPtr<IPoint2d> pnt;
//         points->get_Item(ip, &pnt);
//         Float64 x, y;
//         pnt->get_X(&x);
//         pnt->get_Y(&y);
//         ATLTRACE(" %4d  %10f %10f \n", ip, x, y);
//      }
//      ATLTRACE("---------------------------\n");
//#endif

      m_Dirty = false;
   }

   return S_OK;
}



STDMETHODIMP CUBeam::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W1;
   return S_OK;
}

STDMETHODIMP CUBeam::put_W1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam,GEOMETRY_E_DIMENSION);

   m_W1 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W2;
   return S_OK;
}

STDMETHODIMP CUBeam::put_W2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam,GEOMETRY_E_DIMENSION);

   m_W2 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam::get_W3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W3;
   return S_OK;
}

STDMETHODIMP CUBeam::put_W3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam,GEOMETRY_E_DIMENSION);

   m_W3 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam::get_W4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W4;
   return S_OK;
}

STDMETHODIMP CUBeam::put_W4(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam,GEOMETRY_E_DIMENSION);

   m_W4 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam::get_W5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W5;
   return S_OK;
}

STDMETHODIMP CUBeam::put_W5(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam,GEOMETRY_E_DIMENSION);

   m_W5 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam::get_D1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D1;
   return S_OK;
}

STDMETHODIMP CUBeam::put_D1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam,GEOMETRY_E_DIMENSION);

   m_D1 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam::get_D2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D2;
   return S_OK;
}

STDMETHODIMP CUBeam::put_D2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam,GEOMETRY_E_DIMENSION);

   m_D2 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam::get_D3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D3;
   return S_OK;
}

STDMETHODIMP CUBeam::put_D3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam,GEOMETRY_E_DIMENSION);

   m_D3 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam::get_D4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D4;
   return S_OK;
}

STDMETHODIMP CUBeam::put_D4(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam,GEOMETRY_E_DIMENSION);

   m_D4 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam::get_D5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D5;
   return S_OK;
}

STDMETHODIMP CUBeam::put_D5(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam,GEOMETRY_E_DIMENSION);

   m_D5 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam::get_D6(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D6;
   return S_OK;
}

STDMETHODIMP CUBeam::put_D6(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam,GEOMETRY_E_DIMENSION);

   m_D6 = newVal;
   return S_OK;
}

STDMETHODIMP CUBeam::get_D7(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D7;
   return S_OK;
}

STDMETHODIMP CUBeam::put_D7(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam,GEOMETRY_E_DIMENSION);

   m_D7 = newVal;
   return S_OK;
}


STDMETHODIMP CUBeam::get_T(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T;
   return S_OK;
}

STDMETHODIMP CUBeam::put_T(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam,GEOMETRY_E_DIMENSION);

   m_T = newVal;

   return S_OK;
}

STDMETHODIMP CUBeam::get_Slope(WebIndexType webIdx,Float64* slope)
{
   CHECK_RETVAL(slope);
   if ( webIdx < 0 || 2 <= webIdx )
      return E_INVALIDARG;

   Float64 rise = m_D1 - m_D4 - m_D5;
   Float64 run = (m_W2 - m_W1)/2 - m_W5;

   if ( IsZero(run) )
      *slope = DBL_MAX;
   else
      *slope = rise/run;

   if ( webIdx == 0 )
      (*slope) *= -1;

   return S_OK;
}

STDMETHODIMP CUBeam::get_TopWidth(Float64* width)
{
   CHECK_RETVAL(width);
   *width = m_W2;
   return S_OK;
}

STDMETHODIMP CUBeam::get_TopFlangeWidth(Float64* width)
{
   CHECK_RETVAL(width);

   Float64 slope;
   get_Slope(1,&slope);
   Float64 t = m_T*sqrt(slope*slope + 1)/slope;

   (*width) = m_W4 + m_W5 + t;
   return S_OK;
}

STDMETHODIMP CUBeam::get_WebLocation(WebIndexType webIdx,Float64* location)
{
   CHECK_RETVAL(location);
   if ( webIdx < 0 || 2 <= webIdx )
      return E_INVALIDARG;

   Float64 sign = (webIdx == 0) ? -1 : 1;
   Float64 top_width;
   Float64 slope;

   get_TopWidth(&top_width);
   get_Slope(webIdx,&slope);
   slope = fabs(slope);
   (*location) = sign*(m_D1/slope - 0.5*m_T*sqrt(slope*slope+1)/slope + m_W1/2);

   return S_OK;
}

STDMETHODIMP CUBeam::get_WebSpacing(Float64* spacing)
{
   CHECK_RETVAL(spacing);

   Float64 top_width;
   Float64 slope;

   get_TopWidth(&top_width);
   get_Slope(0,&slope);
   slope = fabs(slope);
   (*spacing) = m_W1 - m_T*sqrt(slope*slope+1)/slope + 2*m_D1/slope;

   return S_OK;
}

STDMETHODIMP CUBeam::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);

   m_pHookPoint.CopyTo( hookPnt );

   return S_OK;
}

STDMETHODIMP CUBeam::putref_HookPoint(IPoint2d* hookPnt)
{
   MakeDirty();

   HRESULT hr = CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
   return hr;
}

STDMETHODIMP CUBeam::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D1;

	return S_OK;
}

STDMETHODIMP CUBeam::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CUBeam::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CUBeam::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_ShapeProperties(pVal);
}

STDMETHODIMP CUBeam::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_BoundingBox(pVal);
}

STDMETHODIMP CUBeam::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CUBeam::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CUBeam::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CUBeam>* pTheClone;
   HRESULT hr = CComObject<CUBeam>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IUBeam> shape(pTheClone); // need at least one reference

   pTheClone->put_D1( m_D1 );
   pTheClone->put_D2( m_D2 );
   pTheClone->put_D3( m_D3 );
   pTheClone->put_D4( m_D4 );
   pTheClone->put_D5( m_D5 );
   pTheClone->put_D6( m_D6 );
   pTheClone->put_D7( m_D7 );
   pTheClone->put_T(  m_T  );
   pTheClone->put_W1( m_W1 );
   pTheClone->put_W2( m_W2 );
   pTheClone->put_W3( m_W3 );
   pTheClone->put_W4( m_W4 );
   pTheClone->put_W5( m_W5 );

   CComPtr<IPoint2d> hookPnt;
   CreatePoint(m_pHookPoint,NULL,&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);
   pTheClone->Rotate( 0.00, 0.00, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CUBeam::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CUBeam::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CUBeam::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_Perimeter(pVal);
}

STDMETHODIMP CUBeam::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->FurthestDistance(line,pVal);
}

STDMETHODIMP CUBeam::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}
/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CUBeam::Offset(Float64 dx,Float64 dy)
{
   // no need to call MakeDirty since our hookpoint will call us back

   m_pHookPoint->Offset(dx,dy);
   return S_OK;
}

STDMETHODIMP CUBeam::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->get_Dx(&dx);
   pSize->get_Dy(&dy);

   return Offset(dx,dy);
}

STDMETHODIMP CUBeam::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   UpdateShape();

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,NULL,point);
}

STDMETHODIMP CUBeam::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{

   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CUBeam::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   CHECK_IN(pFrom);
   CHECK_IN(pTo);

   Float64 x1,y1;
   Float64 x2,y2;

   GetCoordinates(pFrom,&x1,&y1);
   GetCoordinates(pTo,&x2,&y2);

   Float64 dx = x2 - x1;
   Float64 dy = y2 - y1;

   return Offset(dx,dy);
}

STDMETHODIMP CUBeam::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CUBeam::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   // no need to call MakeDirty since our hookpoint will call us back

   m_pHookPoint->Rotate(cx,cy,angle);
   
   // Need to keep track of rotation amount when updating polygon
   m_Rotation += angle;

   return S_OK;
}


// IPersist
STDMETHODIMP CUBeam::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CUBeam::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("UBeam"),1.0);
   pSave->put_Property(CComBSTR("D1"),CComVariant(m_D1));
   pSave->put_Property(CComBSTR("D2"),CComVariant(m_D2));
   pSave->put_Property(CComBSTR("D3"),CComVariant(m_D3));
   pSave->put_Property(CComBSTR("D4"),CComVariant(m_D4));
   pSave->put_Property(CComBSTR("D5"),CComVariant(m_D5));
   pSave->put_Property(CComBSTR("D6"),CComVariant(m_D6));
   pSave->put_Property(CComBSTR("D7"),CComVariant(m_D7));
   pSave->put_Property(CComBSTR("T"),CComVariant(m_T));
   pSave->put_Property(CComBSTR("W1"),CComVariant(m_W1));
   pSave->put_Property(CComBSTR("W2"),CComVariant(m_W2));
   pSave->put_Property(CComBSTR("W3"),CComVariant(m_W3));
   pSave->put_Property(CComBSTR("W4"),CComVariant(m_W4));
   pSave->put_Property(CComBSTR("W5"),CComVariant(m_W5));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CUBeam::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("UBeam"));
   
   pLoad->get_Property(CComBSTR("D1"),&var);
   m_D1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D2"),&var);
   m_D2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D3"),&var);
   m_D3 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D4"),&var);
   m_D4 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D5"),&var);
   m_D5 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D6"),&var);
   m_D6 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D7"),&var);
   m_D7 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("T"),&var);
   m_T = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W1"),&var);
   m_W1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W2"),&var);
   m_W2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W3"),&var);
   m_W3 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W4"),&var);
   m_W4 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W5"),&var);
   m_W5 = var.dblVal;

   pLoad->get_Property(CComBSTR("Rotation"),&var);
   m_Rotation = var.dblVal;

   pLoad->get_Property(CComBSTR("HookPoint"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_pHookPoint,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   UpdateShape();

   return S_OK;
}


STDMETHODIMP CUBeam::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}
