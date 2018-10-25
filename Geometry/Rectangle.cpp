///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2012  Washington State Department of Transportation
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

// Rectangle.cpp : Implementation of CRectangle
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Rectangle.h"
#include "Helper.h"
#include <MathEx.h>
#include <WBFLTools.h> // IMohrCircle

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRectangle
STDMETHODIMP CRectangle::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IRectangle,
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

void CRectangle::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
{
   ATLASSERT( px != 0 && py != 0 );

   UpdateBoundingRect();

   Float64 cx, cy;
   m_pHookPoint->get_X(&cx);
   m_pHookPoint->get_Y(&cy);

   switch( lp )
   {
   case lpTopLeft:
      *px = m_BoundingRect.Left;
      *py = m_BoundingRect.Top;
      break;

   case lpTopCenter:
      *px = cx;
      *py = m_BoundingRect.Top;
      break;

   case lpTopRight:
      *px = m_BoundingRect.Right;
      *py = m_BoundingRect.Top;
      break;

   case lpCenterLeft:
      *px = m_BoundingRect.Left;
      *py = cy;
      break;

   case lpCenterCenter:
   case lpHookPoint:
      *px = cx;
      *py = cy;
      break;

   case lpCenterRight:
      *px = m_BoundingRect.Right;
      *py = cy;
      break;

   case lpBottomLeft: 
      *px = m_BoundingRect.Left;
      *py = m_BoundingRect.Bottom;
      break;

   case lpBottomCenter:
      *px = cx;
      *py = m_BoundingRect.Bottom;
      break;

   case lpBottomRight:
      *px = m_BoundingRect.Right;
      *py = m_BoundingRect.Bottom;
      break;

   default:
      ATLASSERT( false ); // Should never get here
   }
}

HRESULT CRectangle::FinalConstruct()
{
   m_Height = 0.00;
   m_Width  = 0.00;
   m_Rotation = 0.00;
   HRESULT hr = CreatePoint(0.00,0.00,NULL,&m_pHookPoint);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   CComPtr<IPolyShape> pshape;
   hr = CreatePolyShape(&pshape);
   if (FAILED(hr))
      return hr;

   hr = pshape.QueryInterface(&m_pPolyShape);
   if (FAILED(hr))
      return hr;

   MakeDirty();

   return S_OK;
}

void CRectangle::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CRectangle::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Height;
	return S_OK;
}

STDMETHODIMP CRectangle::put_Height(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_IRectangle,GEOMETRY_E_DIMENSION);

   m_Height = newVal;
   MakeDirty();
	return S_OK;
}

STDMETHODIMP CRectangle::get_Width(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Width;
	return S_OK;
}

STDMETHODIMP CRectangle::put_Width(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_IRectangle,GEOMETRY_E_DIMENSION);

   m_Width = newVal;
   MakeDirty();
	return S_OK;
}

STDMETHODIMP CRectangle::get_HookPoint(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   m_pHookPoint->QueryInterface( pVal );

   return S_OK;
}

STDMETHODIMP CRectangle::putref_HookPoint(IPoint2d *hookPnt)
{
   MakeDirty();

   HRESULT hr = CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
   return hr;
}

STDMETHODIMP CRectangle::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CRectangle::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CRectangle::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);
   UpdateShapeProperties();

   return m_ShapeProps.CreateIShapeProperties(pVal);
}

void CRectangle::UpdateShapeProperties()
{
   if (m_DirtyProperties)
   {
      // get non-rotated properties
      Float64 area = m_Height * m_Width;
      Float64 l_ixx = (m_Width * pow(m_Height,3))/ 12.;
      Float64 l_iyy = (m_Height * pow(m_Width,3))/ 12.;

      // rotate properties into correct orientation.
      CComPtr<IMohrCircle> pMohrCircle;
      pMohrCircle.CoCreateInstance( CLSID_MohrCircle );
      pMohrCircle->put_Sii( l_ixx );
      pMohrCircle->put_Sjj( l_iyy );
      pMohrCircle->put_Sij( 0.00 );
   
      Float64 ixx, ixy, iyy;
      pMohrCircle->ComputeState( m_Rotation, &ixx, &iyy, &ixy );

      // bounding box in centroidal coords
      Float64 cx,cy;
      m_pHookPoint->get_X(&cx);
      m_pHookPoint->get_Y(&cy);

      Float64 left, right, top, bottom;
      left   = m_Width/2;
      right  = m_Width/2;
      top    = m_Height/2;
      bottom = m_Height/2;

      m_ShapeProps.Area = area;
      m_ShapeProps.Ixx = ixx;
      m_ShapeProps.Iyy = iyy;
      m_ShapeProps.Ixy = ixy;
      m_ShapeProps.Xleft = left;
      m_ShapeProps.Xright = right;
      m_ShapeProps.Ytop = top;
      m_ShapeProps.Ybottom = bottom;
      m_ShapeProps.Cx = cx;
      m_ShapeProps.Cy = cy;

      m_DirtyProperties = false;
   }
}

STDMETHODIMP CRectangle::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateBoundingRect();
   return CreateRect(m_BoundingRect.Left,m_BoundingRect.Top,m_BoundingRect.Right,m_BoundingRect.Bottom,pVal);
}

void CRectangle::UpdateBoundingRect()
{
   if (m_DirtyBoundingBox)
   {
      // use a point to determine box height and width
      Float64 w2 = m_Width/2.;
      Float64 h2 = m_Height/2.;

      CComPtr<IPoint2d> tl;
      CreatePoint( w2, h2, NULL, &tl );

      CComPtr<IPoint2d> tr;
      CreatePoint( -w2, h2, NULL, &tr );

      tl->Rotate(0.00,0.00, m_Rotation);
      tr->Rotate(0.00,0.00, m_Rotation);

      Float64 tl_x, tl_y;
      tl->get_X(&tl_x);
      tl->get_Y(&tl_y);

      Float64 tr_x, tr_y;
      tr->get_X(&tr_x);
      tr->get_Y(&tr_y);

      Float64 cx,cy;
      m_pHookPoint->get_X(&cx);
      m_pHookPoint->get_Y(&cy);

      Float64 rr = max(fabs(tl_x),fabs(tr_x));
      Float64 rt = max(fabs(tl_y),fabs(tr_y));
      m_BoundingRect.Top    = cy + rt;
      m_BoundingRect.Right  = cx + rr;
      m_BoundingRect.Bottom = cy - rt;
      m_BoundingRect.Left   = cx - rr;

      m_DirtyBoundingBox = false;
   }
}

STDMETHODIMP CRectangle::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   UpdatePolyShape();
   return m_pPolyShape->get_PolyPoints(ppPolyPoints);
}

void CRectangle::UpdatePolyShape()
{
   if (m_DirtyPolyShape)
   {
      CComQIPtr<IPolyShape> pshape(m_pPolyShape);

      pshape->Clear();

      // create polygon geometry
      Float64 w2 = m_Width/2.;
      Float64 h2 = m_Height/2.;
      Float64 cx;
      Float64 cy;
      m_pHookPoint->get_X(&cx);
      m_pHookPoint->get_Y(&cy);

      CComPtr<IPoint2d> bl;
      CreatePoint(cx-w2,cy-h2,NULL,&bl);

      CComPtr<IPoint2d> br;
      CreatePoint(cx+w2,cy-h2,NULL,&br);

      CComPtr<IPoint2d> tr;
      CreatePoint(cx+w2, cy+h2,NULL,&tr);

      CComPtr<IPoint2d> tl;
      CreatePoint(cx-w2, cy+h2,NULL,&tl);

      // rotate points if needed
      if ( !IsZero(m_Rotation) )
      {
         br->RotateEx(m_pHookPoint,m_Rotation);
         bl->RotateEx(m_pHookPoint,m_Rotation);
         tr->RotateEx(m_pHookPoint,m_Rotation);
         tl->RotateEx(m_pHookPoint,m_Rotation);
      }

      pshape->AddPointEx( bl );
      pshape->AddPointEx( br );
      pshape->AddPointEx( tr );
      pshape->AddPointEx( tl );
      pshape->AddPointEx( bl ); // repeat first point to close the shape

      m_DirtyPolyShape = false;
   }

}

STDMETHODIMP CRectangle::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   Float64 cx,cy;
   m_pHookPoint->get_X(&cx);
   m_pHookPoint->get_Y(&cy);

   Float64 left    = cx - m_Width/2;
   Float64 right   = cx + m_Width/2;
   Float64 top     = cy + m_Height/2;
   Float64 bottom  = cy - m_Height/2;

   Float64 x,y;
   pPoint->get_X(&x);
   pPoint->get_Y(&y);

   bool bContained;
   if ( (left < x && x < right)  &&
        (bottom < y && y < top) )
   
   {
      bContained = true;
   }
   else
   {
      bContained = false;
   }

   *pbResult = MakeBool( bContained );
   return S_OK;
}

STDMETHODIMP CRectangle::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CRectangle>* pTheClone;
   HRESULT hr = CComObject<CRectangle>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IRectangle> pRect(pTheClone); // hang on to a reference

   pTheClone->put_Height( m_Height );
   pTheClone->put_Width( m_Width );
   CComPtr<IPoint2d> hookPnt;
   hr = CreatePoint(m_pHookPoint,NULL,&hookPnt);
   pTheClone->putref_HookPoint( hookPnt );
   pTheClone->RotateEx( m_pHookPoint, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CRectangle::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   UpdatePolyShape();
   return m_pPolyShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CRectangle::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   UpdatePolyShape();
   return m_pPolyShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CRectangle::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = 2.0*(m_Width + m_Height);
	return S_OK;
}

STDMETHODIMP CRectangle::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);

   UpdatePolyShape();
   return m_pPolyShape->FurthestDistance(line,pVal);
}
/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CRectangle::Offset(Float64 dx,Float64 dy)
{
   return m_pHookPoint->Offset(dx,dy);
}

STDMETHODIMP CRectangle::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);
   return m_pHookPoint->OffsetEx(pSize);
}

STDMETHODIMP CRectangle::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   if ( lp == lpHookPoint )
   {
      return m_pHookPoint->QueryInterface( point );
   }
   else
   {
      Float64 lx,ly;
      GetLocatorPoint(lp,&lx,&ly);
      return CreatePoint(lx,ly,NULL,point);
   }
}

STDMETHODIMP CRectangle::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CRectangle::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   CHECK_IN(pFrom);
   CHECK_IN(pTo);

   Float64 x1,y1;
   Float64 x2,y2;

   pFrom->get_X(&x1);
   pFrom->get_Y(&y1);

   pTo->get_X(&x2);
   pTo->get_Y(&y2);

   m_pHookPoint->Offset( x2-x1, y2-y1 );

   return S_OK;
}

STDMETHODIMP CRectangle::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   pPoint->get_X(&x);
   pPoint->get_Y(&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CRectangle::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_pHookPoint->Rotate(cx,cy,angle);
   m_Rotation += angle;
   return S_OK;
}


STDMETHODIMP CRectangle::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CRectangle::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CRectangle::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Rectangle"),1.0);
   pSave->put_Property(CComBSTR("Height"),CComVariant(m_Height));
   pSave->put_Property(CComBSTR("Width"),CComVariant(m_Width));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CRectangle::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Rectangle"));

   pLoad->get_Property(CComBSTR("Height"),&var);
   m_Height = var.dblVal;

   pLoad->get_Property(CComBSTR("Width"),&var);
   m_Width = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Rotation"),&var);
   m_Rotation = var.dblVal;

   pLoad->get_Property(CComBSTR("HookPoint"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_pHookPoint,&var)) )
      return STRLOAD_E_INVALIDFORMAT;


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

STDMETHODIMP CRectangle::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}

void CRectangle::ShapeProps::Init()
{
   Area = 0.0;
   Ixx = 0.0;
   Iyy = 0.0;
   Ixy = 0.0;
   Xleft = 0.0;
   Xright = 0.0;
   Ytop = 0.0;
   Ybottom = 0.0;
   Cx = 0.0;
   Cy = 0.0;
}

HRESULT CRectangle::ShapeProps::CreateIShapeProperties(IShapeProperties ** props)
{
   HRESULT hr = CreateShapeProperties(props);
   if (FAILED(hr))
      return hr;

   (*props)->put_Area( Area );
   (*props)->put_Ixx( Ixx );
   (*props)->put_Iyy( Iyy );
   (*props)->put_Ixy( Ixy );
   (*props)->put_Xleft( Xleft );
   (*props)->put_Xright( Xright );
   (*props)->put_Ytop( Ytop );
   (*props)->put_Ybottom( Ybottom );

   CComPtr<IPoint2d> centroid;
   centroid.CoCreateInstance(CLSID_Point2d);
   centroid->put_X(Cx);
   centroid->put_Y(Cy);
   (*props)->put_Centroid( centroid );

   (*props)->put_CoordinateSystem( csCentroidal );

   return S_OK;
}

HRESULT CRectangle::BoundRect::CreateIRect(IRect2d** rect)
{
   return ::CreateRect(Left, Top, Right, Bottom, rect);
}
