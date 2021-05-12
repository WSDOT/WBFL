///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2021  Washington State Department of Transportation
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

// VoidedSlab.cpp : Implementation of CVoidedSlab
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "VoidedSlab.h"
#include "Helper.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////



// CVoidedSlab
HRESULT CVoidedSlab::FinalConstruct()
{
   m_Rotation = 0.00;
   m_H = 0.00;
   m_W = 0.00;
   m_D = 0.00;
   m_S = 0.00;
   m_VoidCount = 0;

   CreatePoint( 0.00, 0.00, nullptr, &m_pHookPoint );
   HRESULT hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   CreateCompositeShape( &m_pShape );

   m_Dirty = true;

   return S_OK;
}

void CVoidedSlab::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CVoidedSlab::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IVoidedSlab,
      &IID_IShape,
      &IID_IXYPosition,
      &IID_IStructuredStorage2
   };
   for (int i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

HRESULT CVoidedSlab::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
{
   ATLASSERT(px != nullptr && py != nullptr);

   HRESULT hr;
   hr = UpdateShape();
   if (FAILED(hr))
      return hr;

   CComPtr<IPoint2d> pPoint;

   if (lp == lpHookPoint)
   {
      pPoint = m_pHookPoint;
   }
   else
   {
      CComQIPtr<IShape> pShape(m_pShape);
      CComPtr<IRect2d> pBox;
      pShape->get_BoundingBox(&pBox);

      switch (lp)
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
         pBox->get_BottomCenter(&pPoint);
         break;

      case lpBottomRight:
         pBox->get_BottomRight(&pPoint);
         break;

      case lpHookPoint:
      default:
         ATLASSERT(false); // Should never get here
      }
   }

   GetCoordinates(pPoint, px, py);

   return S_OK;
}

HRESULT CVoidedSlab::UpdateShape()
{
   if (m_Dirty)
   {
      IndexType nShapes;
      m_pShape->get_Count(&nShapes);

      // Create the main slab rectangle
      CComPtr<IRectangle> slab;
      slab.CoCreateInstance(CLSID_Rect);
      slab->put_Width(m_W);
      slab->put_Height(m_H);

      CComQIPtr<IShape> slabShape(slab);
      if ( nShapes == 0 )
         m_pShape->AddShape(slabShape,VARIANT_FALSE);
      else
         m_pShape->Replace(0,slabShape);

      Float64 y = 0;
      Float64 x = -m_S*(m_VoidCount-1)/2;

      for ( CollectionIndexType i = 0; i < m_VoidCount; i++ )
      {
         CComPtr<ICircle> circle;
         circle.CoCreateInstance(CLSID_Circle);

         circle->put_Radius(m_D/2);

         CComPtr<IPoint2d> center;
         circle->get_Center(&center);
         center->Move(x,y);

         CComQIPtr<IShape> voidShape(circle);

         if ( nShapes == 0 )
            m_pShape->AddShape(voidShape,VARIANT_TRUE);
         else
            m_pShape->Replace(i+1,voidShape);

         x += m_S;
      }

      CComQIPtr<IXYPosition> pPosition(m_pShape);

      // move the shape so that the bottom center is at (0,0)
      // this is the hook point
      pPosition->Offset(0,m_H/2);

      // Rotate the shape
      if (!IsZero(m_Rotation))
      {
         pPosition->Rotate(0.00,0.00,m_Rotation);
      }

      // move the shape to the real hook point
      CComPtr<IPoint2d> origin;
      CreatePoint(0.00,0.00,nullptr,&origin);  // Hook Point at Bottom Center
      pPosition->MoveEx(origin,m_pHookPoint);

      m_Dirty = false;
   }

   return S_OK;
}

STDMETHODIMP CVoidedSlab::get_Width(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W;
   return S_OK;
}

STDMETHODIMP CVoidedSlab::put_Width(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab,GEOMETRY_E_DIMENSION);

   m_W = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_H;
   return S_OK;
}

STDMETHODIMP CVoidedSlab::put_Height(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab,GEOMETRY_E_DIMENSION);

   m_H = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab::get_VoidDiameter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D;
   return S_OK;
}

STDMETHODIMP CVoidedSlab::put_VoidDiameter(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab,GEOMETRY_E_DIMENSION);

   m_D = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab::get_VoidSpacing(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_S;
   return S_OK;
}

STDMETHODIMP CVoidedSlab::put_VoidSpacing(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab,GEOMETRY_E_DIMENSION);

   m_S = newVal;
   return S_OK;
}

STDMETHODIMP CVoidedSlab::get_VoidCount(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_VoidCount;
   return S_OK;
}

STDMETHODIMP CVoidedSlab::put_VoidCount(CollectionIndexType newVal)
{
   MakeDirty();

   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab,GEOMETRY_E_DIMENSION);

   m_VoidCount = newVal;

   return S_OK;
}

STDMETHODIMP CVoidedSlab::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);

   m_pHookPoint.QueryInterface( hookPnt );

   return S_OK;
}

STDMETHODIMP CVoidedSlab::putref_HookPoint(IPoint2d* hookPnt)
{
   MakeDirty();

   HRESULT hr = CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
   return hr;
}

//STDMETHODIMP CVoidedSlab::get_AvgWebWidth(Float64 *pVal)
//{
//   CHECK_RETVAL(pVal);
//
//   *pVal = m_WebCount*(m_T1+m_T2)/2.;
//
//   return S_OK;
//}
//
//STDMETHODIMP CVoidedSlab::get_TopFlangeWidth(Float64 *pVal)
//{
//   CHECK_RETVAL(pVal);
//
//   *pVal = 2*m_W1 + m_WebCount*m_T1 + (m_WebCount-1)*m_W2;
//
//   return S_OK;
//}

STDMETHODIMP CVoidedSlab::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CVoidedSlab::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CVoidedSlab::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_ShapeProperties(pVal);
}

STDMETHODIMP CVoidedSlab::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_BoundingBox(pVal);
}

STDMETHODIMP CVoidedSlab::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CVoidedSlab::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CVoidedSlab::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CVoidedSlab>* pTheClone;
   HRESULT hr = CComObject<CVoidedSlab>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IVoidedSlab> shape(pTheClone); // need at least one reference

   pTheClone->put_Height( m_H );
   pTheClone->put_Width( m_W );
   pTheClone->put_VoidDiameter( m_D );
   pTheClone->put_VoidSpacing( m_S );
   pTheClone->put_VoidCount( m_VoidCount );

   CComPtr<IPoint2d> hookPnt;
   CreatePoint(m_pHookPoint,nullptr,&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);
   pTheClone->Rotate( 0.00, 0.00, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CVoidedSlab::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CVoidedSlab::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CVoidedSlab::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_Perimeter(pVal);
}

STDMETHODIMP CVoidedSlab::FurthestDistance(ILine2d* line,Float64 *pVal)
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
//STDMETHODIMP CVoidedSlab::get_StructuredStorage(IStructuredStorage2* *pStg)
//{
//   return m_pShape->get_StructuredStorage(pStg);
//}
//
//STDMETHODIMP CVoidedSlab::get_XYPosition(IXYPosition* *pVal)
//{
//   return m_pShape->get_XYPosition(pVal);
//}
//
//STDMETHODIMP CVoidedSlab::get_Shape(IShape* *pVal)
//{
//   return m_pShape->get_Shape(pVal);
//}

STDMETHODIMP CVoidedSlab::get_Item(CollectionIndexType idx,ICompositeShapeItem* *pVal)
{
   UpdateShape();
   return m_pShape->get_Item(idx,pVal);
}

STDMETHODIMP CVoidedSlab::get__NewEnum(IUnknown* *pVal)
{
   UpdateShape();
   return m_pShape->get__NewEnum(pVal);
}

STDMETHODIMP CVoidedSlab::get_Count(CollectionIndexType *pVal)
{
   UpdateShape();
   return m_pShape->get_Count(pVal);
}

STDMETHODIMP CVoidedSlab::Remove(CollectionIndexType idx)
{
   return m_pShape->Remove(idx);
}

STDMETHODIMP CVoidedSlab::Clear()
{
   return m_pShape->Clear();
}

STDMETHODIMP CVoidedSlab::ReplaceEx(CollectionIndexType idx,ICompositeShapeItem* pShapeItem)
{
   return m_pShape->ReplaceEx(idx,pShapeItem);
}

STDMETHODIMP CVoidedSlab::Replace(CollectionIndexType idx,IShape* pShape)
{
   return m_pShape->Replace(idx,pShape);
}

STDMETHODIMP CVoidedSlab::AddShapeEx(ICompositeShapeItem* ShapeItem)
{
   return m_pShape->AddShapeEx(ShapeItem);
}

STDMETHODIMP CVoidedSlab::AddShape(IShape* shape,VARIANT_BOOL bVoid)
{
   return m_pShape->AddShape(shape,bVoid);
}

/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CVoidedSlab::Offset(Float64 dx,Float64 dy)
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

STDMETHODIMP CVoidedSlab::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->Dimensions(&dx, &dy);
   return Offset(dx,dy);
}

STDMETHODIMP CVoidedSlab::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   UpdateShape();

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,nullptr,point);
}

STDMETHODIMP CVoidedSlab::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   MakeDirty();

   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CVoidedSlab::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
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

STDMETHODIMP CVoidedSlab::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CVoidedSlab::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   // no need to make dirty since our hook point will call us back
   m_pHookPoint->Rotate(cx,cy,angle);
   
   // Need to keep track of rotation amount when updating polygon
   m_Rotation += angle;

   return S_OK;
}


STDMETHODIMP CVoidedSlab::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CVoidedSlab::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CVoidedSlab::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("VoidedSlab"),1.0);
   pSave->put_Property(CComBSTR("Width"),CComVariant(m_W));
   pSave->put_Property(CComBSTR("Height"),CComVariant(m_H));
   pSave->put_Property(CComBSTR("VoidDiameter"),CComVariant(m_D));
   pSave->put_Property(CComBSTR("VoidSpacing"),CComVariant(m_S));
   pSave->put_Property(CComBSTR("VoidCount"),CComVariant(m_VoidCount));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CVoidedSlab::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("VoidedSlab"));
   
   pLoad->get_Property(CComBSTR("Width"),&var);
   m_W = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Height"),&var);
   m_H = var.dblVal;
   
   pLoad->get_Property(CComBSTR("VoidDiameter"),&var);
   m_D = var.dblVal;
   
   pLoad->get_Property(CComBSTR("VoidSpacing"),&var);
   m_S = var.dblVal;
   
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

STDMETHODIMP CVoidedSlab::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}
