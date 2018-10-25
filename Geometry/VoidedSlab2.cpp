///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2011  Washington State Department of Transportation
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

// VoidedSlab2.cpp : Implementation of CVoidedSlab2
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "VoidedSlab2.h"
#include "Helper.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////



// CVoidedSlab2
HRESULT CVoidedSlab2::FinalConstruct()
{
   m_Rotation = 0.00;
   m_H    = 0.00;
   m_W    = 0.00;
   m_C1   = 0.00;
   m_C2   = 0.00;
   m_C3   = 0.00;
   m_Hext   = 0.00;
   m_Hint = 0.00;
   m_Dext = 0.00;
   m_Dint = 0.00;
   m_Sext = 0.00;
   m_Sint = 0.00;
   m_VoidCount = 0;

   m_bLeftBlockOut = VARIANT_TRUE;
   m_bRightBlockOut = VARIANT_TRUE;

   CreatePoint( 0.00, 0.00, NULL, &m_pHookPoint );
   HRESULT hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   CreateCompositeShape( &m_pShape );

   m_Dirty = true;

   return S_OK;
}

void CVoidedSlab2::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CVoidedSlab2::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IVoidedSlab2,
      &IID_IShape,
      &IID_IXYPosition,
      &IID_IStructuredStorage2
   };
   for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

HRESULT CVoidedSlab2::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
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

HRESULT CVoidedSlab2::UpdateShape()
{
   if (m_Dirty)
   {
      // create a new shape
      m_pShape.Release();
      CreateCompositeShape(&m_pShape);

      // Create the main slab rectangle
      CComPtr<IPolyShape> slab;
      slab.CoCreateInstance(CLSID_PolyShape);

      // bottom right corner
      slab->AddPoint( m_W/2-m_C3, 0);
      slab->AddPoint( m_W/2,      m_C3);  

      if ( m_bRightBlockOut == VARIANT_TRUE )
      {
         slab->AddPoint( m_W/2,        m_H - m_C1 - m_C2);
         slab->AddPoint( m_W/2 - m_C1, m_H - m_C2);
         slab->AddPoint( m_W/2 - m_C1, m_H);
      }
      else
      {
         slab->AddPoint( m_W/2,m_H);
      }

      if ( m_bLeftBlockOut == VARIANT_TRUE )
      {
         slab->AddPoint(-m_W/2 + m_C1, m_H);
         slab->AddPoint(-m_W/2 + m_C1, m_H - m_C2);
         slab->AddPoint(-m_W/2,        m_H - m_C1 - m_C2);
      }
      else
      {
         slab->AddPoint(-m_W/2,m_H);
      }

      // bottom left corner
      slab->AddPoint(-m_W/2,       m_C3);
      slab->AddPoint(-m_W/2 + m_C3,0); 

      CComQIPtr<IShape> slabShape(slab);
      m_pShape->AddShape(slabShape,VARIANT_FALSE);

      if ( m_VoidCount == 0 )
      {
         // do nothing
      }
      else if ( m_VoidCount == 1 )
      {
         // put an exterior void in the center of the beam
         CComPtr<ICircle> circle;
         circle.CoCreateInstance(CLSID_Circle);

         circle->put_Radius(m_Dext/2);

         CComPtr<IPoint2d> center;
         circle->get_Center(&center);
         center->Move(0,m_Hext);

         CComQIPtr<IShape> voidShape(circle);
         m_pShape->AddShape(voidShape,VARIANT_TRUE);
      }
      else if ( m_VoidCount == 2 )
      {
         // left exterior void
         CComPtr<ICircle> circle;
         circle.CoCreateInstance(CLSID_Circle);

         circle->put_Radius(m_Dext/2);

         CComPtr<IPoint2d> center;
         circle->get_Center(&center);
         Float64 x = m_Sext/2;
         center->Move(-x,m_Hext);

         CComQIPtr<IShape> voidShape(circle);
         m_pShape->AddShape(voidShape,VARIANT_TRUE);

         // right exterior void
         circle.Release();
         voidShape.Release();
         center.Release();
         circle.CoCreateInstance(CLSID_Circle);
         circle->put_Radius(m_Dext/2);
         circle->get_Center(&center);
         center->Move(x,m_Hext);
         circle->QueryInterface(&voidShape);
         m_pShape->AddShape(voidShape,VARIANT_TRUE);
      }
      else
      {
         // center the two exterior voids
         Uint32 nIntVoids;
         if ( m_VoidCount == 0 || m_VoidCount == 1 )
            nIntVoids = 0;
         else
            nIntVoids = m_VoidCount - 2;

         // left exterior void
         CComPtr<ICircle> circle;
         circle.CoCreateInstance(CLSID_Circle);

         circle->put_Radius(m_Dext/2);

         CComPtr<IPoint2d> center;
         circle->get_Center(&center);
         Float64 x = m_Sext + m_Sint*(nIntVoids-1)/2;
         center->Move(-x,m_Hext);

         CComQIPtr<IShape> voidShape(circle);
         m_pShape->AddShape(voidShape,VARIANT_TRUE);

         // right exterior void
         circle.Release();
         voidShape.Release();
         center.Release();
         circle.CoCreateInstance(CLSID_Circle);
         circle->put_Radius(m_Dext/2);
         circle->get_Center(&center);
         center->Move(x,m_Hext);
         circle->QueryInterface(&voidShape);
         m_pShape->AddShape(voidShape,VARIANT_TRUE);

         // interior voids
         x = -m_Sint*(nIntVoids-1)/2;
         for ( Uint32 voidIdx = 0; voidIdx < nIntVoids; voidIdx++ )
         {
            CComPtr<ICircle> intVoid;
            intVoid.CoCreateInstance(CLSID_Circle);

            intVoid->put_Radius(m_Dint/2);

            CComPtr<IPoint2d> center;
            intVoid->get_Center(&center);
            center->Move(x,m_Hint);

            CComQIPtr<IShape> voidShape(intVoid);
            m_pShape->AddShape(voidShape,VARIANT_TRUE);

            x += m_Sint;
         }
      }

      CComQIPtr<IXYPosition> pPosition(m_pShape);

      // Rotate the shape
      if (!IsZero(m_Rotation))
      {
         pPosition->Rotate(0.00,0.00,m_Rotation);
      }

      // move the shape to the real hook point
      CComPtr<IPoint2d> origin;
      CreatePoint(0.00,0.00,NULL,&origin);  // Hook Point at Bottom Center
      pPosition->MoveEx(origin,m_pHookPoint);

      m_Dirty = false;
   }

   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_Width(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_Width(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_W = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_H;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_Height(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_H = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_C1;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_C1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_C1 = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_C2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_C2;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_C2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_C2 = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_C3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_C3;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_C3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_C3 = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_LeftBlockOut(VARIANT_BOOL bLeftBlockOut)
{
   MakeDirty();
   m_bLeftBlockOut = bLeftBlockOut;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_LeftBlockOut(VARIANT_BOOL* pbLeftBlockOut)
{
   CHECK_RETVAL(pbLeftBlockOut);
   *pbLeftBlockOut = m_bLeftBlockOut;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_RightBlockOut(VARIANT_BOOL bRightBlockOut)
{
   MakeDirty();
   m_bRightBlockOut = bRightBlockOut;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_RightBlockOut(VARIANT_BOOL* pbRightBlockOut)
{
   CHECK_RETVAL(pbRightBlockOut);
   *pbRightBlockOut = m_bRightBlockOut;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_ExteriorVoidDiameter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Dext;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_ExteriorVoidDiameter(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Dext = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_InteriorVoidDiameter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Dint;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_InteriorVoidDiameter(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Dint = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_ExteriorVoidSpacing(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Sext;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_ExteriorVoidSpacing(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Sext = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_InteriorVoidSpacing(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Sint;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_InteriorVoidSpacing(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Sint = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_ExteriorVoidElevation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Hext;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_ExteriorVoidElevation(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Hext = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_InteriorVoidElevation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Hint;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_InteriorVoidElevation(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Hint = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_VoidCount(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_VoidCount;
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_VoidCount(CollectionIndexType newVal)
{
   MakeDirty();

   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_VoidCount = newVal;

   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);

   m_pHookPoint.QueryInterface( hookPnt );

   return S_OK;
}

STDMETHODIMP CVoidedSlab2::putref_HookPoint(IPoint2d* hookPnt)
{
   MakeDirty();

   HRESULT hr = CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
   return hr;
}

//STDMETHODIMP CVoidedSlab2::get_AvgWebWidth(Float64 *pVal)
//{
//   CHECK_RETVAL(pVal);
//
//   *pVal = m_WebCount*(m_T1+m_T2)/2.;
//
//   return S_OK;
//}
//
//STDMETHODIMP CVoidedSlab2::get_TopFlangeWidth(Float64 *pVal)
//{
//   CHECK_RETVAL(pVal);
//
//   *pVal = 2*m_W1 + m_WebCount*m_T1 + (m_WebCount-1)*m_W2;
//
//   return S_OK;
//}

STDMETHODIMP CVoidedSlab2::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CVoidedSlab2::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CVoidedSlab2::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_ShapeProperties(pVal);
}

STDMETHODIMP CVoidedSlab2::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_BoundingBox(pVal);
}

STDMETHODIMP CVoidedSlab2::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CVoidedSlab2::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CVoidedSlab2::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CVoidedSlab2>* pTheClone;
   HRESULT hr = CComObject<CVoidedSlab2>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IVoidedSlab2> shape(pTheClone); // need at least one reference

   pTheClone->put_Height( m_H );
   pTheClone->put_Width( m_W );
   pTheClone->put_C1( m_C1 );
   pTheClone->put_C2( m_C2 );
   pTheClone->put_C3( m_C3 );
   pTheClone->put_ExteriorVoidDiameter( m_Dext );
   pTheClone->put_InteriorVoidDiameter( m_Dint );
   pTheClone->put_ExteriorVoidSpacing( m_Sext );
   pTheClone->put_InteriorVoidSpacing( m_Sint );
   pTheClone->put_ExteriorVoidElevation( m_Hext );
   pTheClone->put_InteriorVoidElevation( m_Hint );
   pTheClone->put_VoidCount( m_VoidCount );
   pTheClone->put_LeftBlockOut(m_bLeftBlockOut);
   pTheClone->put_RightBlockOut(m_bRightBlockOut);

   CComPtr<IPoint2d> hookPnt;
   CreatePoint(m_pHookPoint,NULL,&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);
   pTheClone->Rotate( 0.00, 0.00, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CVoidedSlab2::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CVoidedSlab2::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CVoidedSlab2::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_Perimeter(pVal);
}

STDMETHODIMP CVoidedSlab2::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->FurthestDistance(line,pVal);
}

/////////////////////////////////////////////////////////////////////////////
// ICompositeShape
/////////////////////////////////////////////////////////////////////////////
//STDMETHODIMP CVoidedSlab2::get_StructuredStorage(IStructuredStorage2* *pStg)
//{
//   return m_pShape->get_StructuredStorage(pStg);
//}
//
//STDMETHODIMP CVoidedSlab2::get_XYPosition(IXYPosition* *pVal)
//{
//   return m_pShape->get_XYPosition(pVal);
//}
//
//STDMETHODIMP CVoidedSlab2::get_Shape(IShape* *pVal)
//{
//   return m_pShape->get_Shape(pVal);
//}

STDMETHODIMP CVoidedSlab2::get_Item(CollectionIndexType idx,ICompositeShapeItem* *pVal)
{
   UpdateShape();
   return m_pShape->get_Item(idx,pVal);
}

STDMETHODIMP CVoidedSlab2::get__NewEnum(IUnknown* *pVal)
{
   UpdateShape();
   return m_pShape->get__NewEnum(pVal);
}

STDMETHODIMP CVoidedSlab2::get_Count(CollectionIndexType *pVal)
{
   UpdateShape();
   return m_pShape->get_Count(pVal);
}

STDMETHODIMP CVoidedSlab2::Remove(CollectionIndexType idx)
{
   return m_pShape->Remove(idx);
}

STDMETHODIMP CVoidedSlab2::Clear()
{
   return m_pShape->Clear();
}

STDMETHODIMP CVoidedSlab2::AddShapeEx(ICompositeShapeItem* ShapeItem)
{
   return m_pShape->AddShapeEx(ShapeItem);
}

STDMETHODIMP CVoidedSlab2::AddShape(IShape* shape,VARIANT_BOOL bVoid)
{
   return m_pShape->AddShape(shape,bVoid);
}

/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CVoidedSlab2::Offset(Float64 dx,Float64 dy)
{
   // no need to call MakeDirty since our hookpoint will call us back

   m_pHookPoint->Offset(dx,dy);
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->get_Dx(&dx);
   pSize->get_Dy(&dy);

   return Offset(dx,dy);
}

STDMETHODIMP CVoidedSlab2::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   UpdateShape();

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,NULL,point);
}

STDMETHODIMP CVoidedSlab2::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   MakeDirty();

   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CVoidedSlab2::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
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

STDMETHODIMP CVoidedSlab2::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CVoidedSlab2::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   // no need to make dirty since our hook point will call us back
   m_pHookPoint->Rotate(cx,cy,angle);
   
   // Need to keep track of rotation amount when updating polygon
   m_Rotation += angle;

   return S_OK;
}


STDMETHODIMP CVoidedSlab2::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CVoidedSlab2::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CVoidedSlab2::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("VoidedSlab2"),2.0);
   pSave->put_Property(CComBSTR("Width"),CComVariant(m_W));
   pSave->put_Property(CComBSTR("Height"),CComVariant(m_H));
   pSave->put_Property(CComBSTR("C1"),CComVariant(m_C1));
   pSave->put_Property(CComBSTR("C2"),CComVariant(m_C2));
   pSave->put_Property(CComBSTR("C3"),CComVariant(m_C3));
   pSave->put_Property(CComBSTR("LeftBlockOut"),CComVariant(m_bLeftBlockOut));
   pSave->put_Property(CComBSTR("RightBlockOut"),CComVariant(m_bRightBlockOut));
   pSave->put_Property(CComBSTR("ExteriorVoidDiameter"),CComVariant(m_Dext));
   pSave->put_Property(CComBSTR("InteriorVoidDiameter"),CComVariant(m_Dint));
   pSave->put_Property(CComBSTR("ExteriorVoidSpacing"),CComVariant(m_Sext));
   pSave->put_Property(CComBSTR("InteriorVoidSpacing"),CComVariant(m_Sint));
   pSave->put_Property(CComBSTR("ExteriorVoidElevation"),CComVariant(m_Hext));
   pSave->put_Property(CComBSTR("InteriorVoidElevation"),CComVariant(m_Hint));
   pSave->put_Property(CComBSTR("VoidCount"),CComVariant(m_VoidCount));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CVoidedSlab2::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("VoidedSlab2"));
   
   Float64 version;
   pLoad->get_Version(&version);

   pLoad->get_Property(CComBSTR("Width"),&var);
   m_W = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Height"),&var);
   m_H = var.dblVal;
   
   pLoad->get_Property(CComBSTR("C1"),&var);
   m_C1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("C2"),&var);
   m_C2 = var.dblVal;

   if ( version < 1 )
   {
      pLoad->get_Property(CComBSTR("C3"),&var);
      m_C3 = var.dblVal;
   }
   else
   {
      m_C3 = 0;
   }

   pLoad->get_Property(CComBSTR("LeftBlockOut"),&var);
   m_bLeftBlockOut = var.boolVal;

   pLoad->get_Property(CComBSTR("RightBlockOut"),&var);
   m_bRightBlockOut = var.boolVal;
   
   pLoad->get_Property(CComBSTR("ExteriorVoidDiameter"),&var);
   m_Dext = var.dblVal;
   
   pLoad->get_Property(CComBSTR("InteriorVoidDiameter"),&var);
   m_Dint = var.dblVal;
   
   pLoad->get_Property(CComBSTR("ExteriorVoidSpacing"),&var);
   m_Sext = var.dblVal;
   
   pLoad->get_Property(CComBSTR("InteriorVoidSpacing"),&var);
   m_Sint = var.dblVal;
   
   pLoad->get_Property(CComBSTR("ExteriorVoidElevation"),&var);
   m_Hext = var.dblVal;
   
   pLoad->get_Property(CComBSTR("InteriorVoidElevation"),&var);
   m_Hint = var.dblVal;
   
   pLoad->get_Property(CComBSTR("VoidCount"),&var);
   m_VoidCount = var.iVal;
   
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

STDMETHODIMP CVoidedSlab2::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}
