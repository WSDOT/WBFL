///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// TrafficBarrier.cpp : Implementation of CTrafficBarrier
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "TrafficBarrier.h"
#include "Helper.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrafficBarrier
STDMETHODIMP CTrafficBarrier::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITrafficBarrier,
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

HRESULT CTrafficBarrier::FinalConstruct()
{
   m_X1 = 0.00;
   m_X2 = 0.00;
   m_X3 = 0.00;
   m_X4 = 0.00;
   m_X5 = 0.00;
   m_Y1 = 0.00;
   m_Y2 = 0.00;
   m_Y3 = 0.00;
   m_Y4 = 0.00;
   m_Orientation = tboLeft;
   m_Rotation = 0.00;

   HRESULT hr;
   hr = CreatePolyShape(&m_pShape);
   if ( FAILED(hr) ) return hr;

   hr = CreatePoint(0,0,NULL,&m_pHookPoint);
   if ( FAILED(hr) ) return hr;

   hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr)) return hr;

   m_Dirty = true;

   return S_OK;
}

void CTrafficBarrier::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}

void CTrafficBarrier::GetLocatorPoint(LocatorPointType lp,Float64* x,Float64* y)
{
   ATLASSERT( x != 0 && y != 0 );

   UpdateShape();

   CComPtr<IRect2d> pBox;
   CComPtr<IPoint2d> pnt;

   get_BoundingBox(&pBox);

   switch(lp)
   {
   case lpTopLeft:
        pBox->get_TopLeft(&pnt);
        break;

   case lpTopCenter:
        pBox->get_TopCenter(&pnt);
        break;

   case lpTopRight:
        pBox->get_TopRight(&pnt);
        break;

   case lpCenterLeft:
        pBox->get_CenterLeft(&pnt);
        break;

   case lpCenterCenter:
        pBox->get_CenterCenter(&pnt);
        break;

   case lpCenterRight:
        pBox->get_CenterRight(&pnt);
        break;

   case lpBottomLeft:
        pBox->get_BottomLeft(&pnt);
        break;

   case lpBottomCenter:
        pBox->get_BottomCenter(&pnt);
        break;

   case lpBottomRight:
        pBox->get_BottomRight(&pnt);
        break;

   case lpHookPoint:
        pnt = m_pHookPoint;
        break;

   default:
      ATLASSERT( false ); // Should never get here!
      break;
   }

   GetCoordinates(pnt,x,y);
}

void CTrafficBarrier::UpdateShape()
{
   if (m_Dirty)
   {

      m_pShape->Clear();

      Float64 sign = (m_Orientation == tboLeft ? 1.00 : -1.00);

      // Hook Point (make it 0,0 for ease of construction)
      CComPtr<IPoint2d> p0;
      Float64 x0,y0;
      x0 = y0 = 0.00;
      CreatePoint(x0,y0,NULL,&p0);

      // Work clockwise around the left oriented shape.
      CComPtr<IPoint2d> p1;
      CreatePoint(sign*(x0 + m_X2), y0, NULL, &p1 );

      CComPtr<IPoint2d> p2;
      CreatePoint( sign*(x0 + m_X2), y0 + m_Y1, NULL, &p2 );

      CComPtr<IPoint2d> p3;
      CreatePoint( sign*(x0 + m_X2 - m_X5), y0 + m_Y1 + m_Y2, NULL, &p3 );

      CComPtr<IPoint2d> p4;
      CreatePoint( sign*(x0 + m_X2 - m_X5 - m_X4), y0 + m_Y3, NULL, &p4 );

      CComPtr<IPoint2d> p5;
      CreatePoint( sign*(x0 + m_X2 - m_X5 - m_X4 - m_X3), y0 + m_Y3, NULL, &p5 );

      CComPtr<IPoint2d> p6;
      CreatePoint( sign*(x0 - m_X1), y0 - m_Y4, NULL, &p6 );

      CComPtr<IPoint2d> p7;
      CreatePoint( x0 , y0 - m_Y4, NULL, &p7 );
   
      m_pShape->AddPointEx(p0);
      m_pShape->AddPointEx(p1);
      m_pShape->AddPointEx(p2);
      m_pShape->AddPointEx(p3);
      m_pShape->AddPointEx(p4);
      m_pShape->AddPointEx(p5);
      m_pShape->AddPointEx(p6);
      m_pShape->AddPointEx(p7);

      CComQIPtr<IXYPosition> pPosition(m_pShape);
      pPosition->MoveEx(p0,m_pHookPoint);

      if (!IsZero(m_Rotation))
      {
         pPosition->Rotate(0.00,0.00,m_Rotation);
      }

      m_Dirty = false;
   }
}

STDMETHODIMP CTrafficBarrier::get_X1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_X1;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_X1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_X1 = newVal;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_X2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   
   *pVal = m_X2;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_X2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_X2 = newVal;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_X3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_X3;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_X3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_X3 = newVal;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_X4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_X4;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_X4(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_X4 = newVal;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_X5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_X5;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_X5(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_X5 = newVal;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_Y1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Y1;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_Y1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_Y1 = newVal;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_Y2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Y2;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_Y2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_Y2 = newVal;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_Y3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Y3;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_Y3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_Y3 = newVal;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_Y4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Y4;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_Y4(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_Y4 = newVal;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_HookPoint(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   m_pHookPoint.QueryInterface( pVal );

   return S_OK;
}

STDMETHODIMP CTrafficBarrier::putref_HookPoint(IPoint2d *hookPnt)
{
   CHECK_IN(hookPnt);
   MakeDirty();

   return CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
}

STDMETHODIMP CTrafficBarrier::get_Orientation(TrafficBarrierOrientation *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Orientation;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_Orientation(TrafficBarrierOrientation newVal)
{
   MakeDirty();

   m_Orientation = newVal;
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CTrafficBarrier::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTrafficBarrier::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);
   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_ShapeProperties(pVal);
}

STDMETHODIMP CTrafficBarrier::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);
   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_BoundingBox(pVal);
}

STDMETHODIMP CTrafficBarrier::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);
   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CTrafficBarrier::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CTrafficBarrier::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CTrafficBarrier>* pTheClone;
   HRESULT hr = CComObject<CTrafficBarrier>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<ITrafficBarrier> shape(pTheClone); // need at least one reference

   pTheClone->put_X1(m_X1);
   pTheClone->put_X2(m_X2);
   pTheClone->put_X3(m_X3);
   pTheClone->put_X4(m_X4);
   pTheClone->put_X5(m_X5);
   pTheClone->put_Y1(m_Y1);
   pTheClone->put_Y2(m_Y2);
   pTheClone->put_Y3(m_Y3);
   pTheClone->put_Y4(m_Y4);
   pTheClone->put_Orientation(m_Orientation);

   CComPtr<IPoint2d> hookPnt;
   CreatePoint(m_pHookPoint,NULL,&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);

   pTheClone->QueryInterface(pClone);

   return S_OK;
}

STDMETHODIMP CTrafficBarrier::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CTrafficBarrier::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CTrafficBarrier::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_Perimeter(pVal);
}

STDMETHODIMP CTrafficBarrier::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->FurthestDistance(line,pVal);
}

/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTrafficBarrier::Offset(Float64 dx,Float64 dy)
{
   // no need to call MakeDirty since our hookpoint will call us back
   m_pHookPoint->Offset(dx,dy);
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   GetSize(pSize,&dx,&dy);
   return Offset(dx,dy);
}

STDMETHODIMP CTrafficBarrier::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   UpdateShape();
   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,NULL,point);
}

STDMETHODIMP CTrafficBarrier::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CTrafficBarrier::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
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

STDMETHODIMP CTrafficBarrier::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CTrafficBarrier::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_pHookPoint->Rotate(cx,cy,angle);
   
   // Need to keep track of rotation amount when updating polygon
   m_Rotation += angle;

   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CTrafficBarrier::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CTrafficBarrier::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("TrafficBarrier"),1.0);
   pSave->put_Property(CComBSTR("X1"),CComVariant(m_X1));
   pSave->put_Property(CComBSTR("X2"),CComVariant(m_X2));
   pSave->put_Property(CComBSTR("X3"),CComVariant(m_X3));
   pSave->put_Property(CComBSTR("X4"),CComVariant(m_X4));
   pSave->put_Property(CComBSTR("X5"),CComVariant(m_X5));
   pSave->put_Property(CComBSTR("Y1"),CComVariant(m_Y1));
   pSave->put_Property(CComBSTR("Y2"),CComVariant(m_Y2));
   pSave->put_Property(CComBSTR("Y3"),CComVariant(m_Y3));
   pSave->put_Property(CComBSTR("Y4"),CComVariant(m_Y4));
   pSave->put_Property(CComBSTR("Orientation"),CComVariant(m_Orientation));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CTrafficBarrier::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("TrafficBarrier"));
   
   pLoad->get_Property(CComBSTR("X1"),&var);
   m_X1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("X2"),&var);
   m_X2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("X3"),&var);
   m_X3 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("X4"),&var);
   m_X4 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("X5"),&var);
   m_X5 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Y1"),&var);
   m_Y1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Y2"),&var);
   m_Y2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Y3"),&var);
   m_Y3 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Y4"),&var);
   m_Y4 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Orientation"),&var);
   m_Orientation = (TrafficBarrierOrientation)var.iVal;
   
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


STDMETHODIMP CTrafficBarrier::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}
