///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// Triangle.cpp : Implementation of CTriangle
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Triangle.h"
#include "Helper.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTriangle
HRESULT CTriangle::FinalConstruct()
{
   HRESULT hr;

   m_Height   = 0.00;
   m_Width    = 0.00;
   m_Offset   = 0.00;
   m_Rotation = 0.00;

   hr = CreatePolyShape( &m_pShape );
   if (FAILED(hr)) return hr;
   hr = CreatePoint(0.00,0.00,nullptr,&m_pHookPoint);
   if (FAILED(hr)) return hr;
   hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr)) return hr;

   m_Dirty = true;

   return S_OK;
}

void CTriangle::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CTriangle::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITriangle,
		&IID_IShape,
		&IID_IXYPosition,
		&IID_IStructuredStorage2,
	};
	for (int i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CTriangle::UpdateShape()
{
   if (m_Dirty)
   {
      Float64 x,y;
      GetCoordinates(m_pHookPoint,&x,&y);

      // create polygon geometry (not rotated)
      m_pShape->Clear();
      m_pShape->AddPoint(x,y);
      m_pShape->AddPoint(x+m_Width,y);
      m_pShape->AddPoint(x+m_Offset,y+m_Height);

      // rotate if needed
      if ( !IsZero(m_Rotation) )
      {
         CComQIPtr<IXYPosition> position(m_pShape);
         position->RotateEx(m_pHookPoint, m_Rotation);
      }

      m_Dirty = false;
   }
}

void CTriangle::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
{
   ATLASSERT(px != nullptr && py != nullptr );

   UpdateShape();

   CComPtr<IRect2d> pRect;

   CComQIPtr<IShape> pShape(m_pShape);
   pShape->get_BoundingBox(&pRect);

   CComPtr<IPoint2d> pPoint;

   switch( lp )
   {
   case lpTopLeft:
      pRect->get_TopLeft(&pPoint);
      break;

   case lpTopCenter:
      pRect->get_TopCenter(&pPoint);
      break;

   case lpTopRight:
      pRect->get_TopRight(&pPoint);
      break;

   case lpCenterLeft:
      pRect->get_CenterLeft(&pPoint);
      break;

   case lpCenterCenter:
      pRect->get_CenterCenter(&pPoint);
      break;

   case lpCenterRight:
      pRect->get_CenterRight(&pPoint);
      break;

   case lpBottomLeft: 
      pRect->get_BottomLeft(&pPoint);
      break;

   case lpBottomCenter:
      pRect->get_BottomCenter(&pPoint);
      break;

   case lpBottomRight:
      pRect->get_BottomRight(&pPoint);
      break;

   case lpHookPoint:
      pPoint = m_pHookPoint;
      break;

   default:
      ATLASSERT( false ); // Should never get here
   }

   pPoint->get_X(px);
   pPoint->get_Y(py);
}

STDMETHODIMP CTriangle::get_Width(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Width;
	return S_OK;
}

STDMETHODIMP CTriangle::put_Width(Float64 newVal)
{
   MakeDirty();

   m_Width = newVal;
   return S_OK;
}

STDMETHODIMP CTriangle::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Height;
	return S_OK;
}

STDMETHODIMP CTriangle::put_Height(Float64 newVal)
{
   MakeDirty();

   m_Height = newVal;
   return S_OK;
}

STDMETHODIMP CTriangle::get_Offset(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Offset;
	return S_OK;
}

STDMETHODIMP CTriangle::put_Offset(Float64 newVal)
{
   MakeDirty();

   m_Offset = newVal;
   return S_OK;
}

STDMETHODIMP CTriangle::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);

   m_pHookPoint.QueryInterface( hookPnt );

   return S_OK;
}

STDMETHODIMP CTriangle::putref_HookPoint(IPoint2d* hookPnt)
{
   CHECK_IN(hookPnt);
   MakeDirty();

   return CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
}

STDMETHODIMP CTriangle::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CTriangle::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTriangle::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_ShapeProperties(pVal);
}

STDMETHODIMP CTriangle::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_BoundingBox(pVal);
}

STDMETHODIMP CTriangle::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CTriangle::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CTriangle::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CTriangle>* pTheClone;
   HRESULT hr = CComObject<CTriangle>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<ITriangle> shape(pTheClone); // need at least one reference

   pTheClone->put_Height(m_Height);
   pTheClone->put_Width(m_Width);
   pTheClone->put_Offset(m_Offset);

   CComPtr<IPoint2d> hookPnt;
   CreatePoint(m_pHookPoint,nullptr,&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);

   return pTheClone->QueryInterface( pClone );
}

STDMETHODIMP CTriangle::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CTriangle::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CTriangle::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_Perimeter(pVal);
}

STDMETHODIMP CTriangle::FurthestDistance(ILine2d* line,Float64 *pVal)
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

STDMETHODIMP CTriangle::Offset(Float64 dx,Float64 dy)
{
   if (m_Dirty)
   {
      // this is going to fire an event that sets m_Dirty to true... since it is already true
      // no need to worry about it
      m_pHookPoint->Offset(dx, dy);
   }
   else
   {
      // We are just offsetting... detach from m_pHookPoint events so we don't invalidate
      // everything about this shape...
      CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
      m_pHookPoint->Offset(dx, dy); // offset the hook point
      CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);

      CComQIPtr<IXYPosition> pos(m_pShape);
      pos->Offset(dx, dy); // offset the shape
   }
   return S_OK;
}

STDMETHODIMP CTriangle::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->Dimensions(&dx, &dy);

   return Offset(dx,dy);
}

STDMETHODIMP CTriangle::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETVAL(point);

   UpdateShape();
   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,nullptr,point);
}

STDMETHODIMP CTriangle::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}
STDMETHODIMP CTriangle::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   CHECK_IN(pFrom);
   CHECK_IN(pTo);

   Float64 x1, y1;
   pFrom->get_X(&x1);
   pFrom->get_Y(&y1);

   Float64 x2, y2;
   pTo->get_X(&x2);
   pTo->get_Y(&y2);

   return Offset( x2-x1, y2-y1 );
}

STDMETHODIMP CTriangle::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   pPoint->get_X(&x);
   pPoint->get_Y(&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CTriangle::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_Rotation += angle;
   m_pHookPoint->Rotate(cx,cy, angle);

   return S_OK;
}

STDMETHODIMP CTriangle::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CTriangle::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CTriangle::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Triangle"),1.0);
   pSave->put_Property(CComBSTR("Height"),CComVariant(m_Height));
   pSave->put_Property(CComBSTR("Width"),CComVariant(m_Width));
   pSave->put_Property(CComBSTR("Offset"),CComVariant(m_Offset));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CTriangle::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Triangle"));

   pLoad->get_Property(CComBSTR("Height"),&var);
   m_Height = var.dblVal;

   pLoad->get_Property(CComBSTR("Width"),&var);
   m_Width = var.dblVal;

   pLoad->get_Property(CComBSTR("Offset"),&var);
   m_Offset = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Rotation"),&var);
   m_Rotation = var.dblVal;

   pLoad->get_Property(CComBSTR("HookPoint"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_pHookPoint,&var)) )
      return STRLOAD_E_INVALIDFORMAT;


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   UpdateShape(); // Rebuild the internal representation

   return S_OK;
}

STDMETHODIMP CTriangle::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}


