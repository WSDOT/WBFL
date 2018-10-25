///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// MultiWeb.cpp : Implementation of CMultiWeb
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "MultiWeb.h"
#include "Helper.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////



// CMultiWeb
HRESULT CMultiWeb::FinalConstruct()
{
   m_Rotation = 0.00;
   m_D1 = 0.00;
   m_D2 = 0.00;
   m_T1 = 0.00;
   m_T2 = 0.00;
   m_W1 = 0.00;
   m_W2 = 0.00;
   m_WebCount = 0;

   CreatePoint( 0.00, 0.00, NULL, &m_pHookPoint );
   HRESULT hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   CreatePolyShape( &m_pShape );

   m_Dirty = true;

   return S_OK;
}

void CMultiWeb::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CMultiWeb::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IMultiWeb,
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

HRESULT CMultiWeb::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
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

HRESULT CMultiWeb::UpdateShape()
{
   if (m_Dirty)
   {
      // clear the polygon implemenation and recalculate all of the points
      m_pShape->Clear();

      // start at top left and go around clockwise

      // there are 4 points that represent the slab
      Float64 p1_x = 0.;
      Float64 p1_y = 0.;

      Float64 p2_x = 0.;
      Float64 p2_y = -m_D1;

      Float64 p3_x = 2*m_W1 + m_WebCount*m_T1 + (m_WebCount-1)*m_W2;
      Float64 p3_y = -m_D1;

      Float64 p4_x = p3_x;
      Float64 p4_y = 0;

      m_pShape->AddPoint( p1_x, p1_y);  // 1
      m_pShape->AddPoint( p2_x, p2_y);

      for ( WebIndexType i = 0; i < m_WebCount; i++ )
      {
         Float64 web_x1, web_y1;
         Float64 web_x2, web_y2;
         Float64 web_x3, web_y3;
         Float64 web_x4, web_y4;

         web_x1 = m_W1 + i*(m_W2+m_T1);
         web_y1 = -m_D1;

         web_x2 = web_x1 + m_T1/2 - m_T2/2;
         web_y2 = -m_D1 - m_D2;

         web_x3 = web_x2 + m_T2;
         web_y3 = -m_D1 - m_D2;

         web_x4 = web_x1 + m_T1;
         web_y4 = -m_D1;

         m_pShape->AddPoint(web_x1,web_y1);
         m_pShape->AddPoint(web_x2,web_y2);
         m_pShape->AddPoint(web_x3,web_y3);
         m_pShape->AddPoint(web_x4,web_y4);
      }


      m_pShape->AddPoint( p3_x, p3_y);
      m_pShape->AddPoint( p4_x, p4_y);

      CComQIPtr<IXYPosition> pPosition(m_pShape);

      // move the shape so that the top center is at (0,0)
      pPosition->Offset(-p3_x/2,0);

      if (!IsZero(m_Rotation))
      {
         pPosition->Rotate(0.00,0.00,m_Rotation);
      }

      CComPtr<IPoint2d> origin;
      CreatePoint(0.00,0.00,NULL,&origin);  // Hook Point at Bottom Center
      pPosition->MoveEx(origin,m_pHookPoint);

      m_Dirty = false;
   }

   return S_OK;
}

STDMETHODIMP CMultiWeb::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W1;
   return S_OK;
}

STDMETHODIMP CMultiWeb::put_W1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb,GEOMETRY_E_DIMENSION);

   m_W1 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W2;
   return S_OK;
}

STDMETHODIMP CMultiWeb::put_W2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb,GEOMETRY_E_DIMENSION);

   m_W2 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb::get_D1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D1;
   return S_OK;
}

STDMETHODIMP CMultiWeb::put_D1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb,GEOMETRY_E_DIMENSION);

   m_D1 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb::get_D2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D2;
   return S_OK;
}

STDMETHODIMP CMultiWeb::put_D2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb,GEOMETRY_E_DIMENSION);

   m_D2 = newVal;
   return S_OK;
}

STDMETHODIMP CMultiWeb::get_T1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T1;
   return S_OK;
}

STDMETHODIMP CMultiWeb::put_T1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb,GEOMETRY_E_DIMENSION);

   m_T1 = newVal;

   return S_OK;
}

STDMETHODIMP CMultiWeb::get_T2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T2;
   return S_OK;
}

STDMETHODIMP CMultiWeb::put_T2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb,GEOMETRY_E_DIMENSION);

   m_T2 = newVal;

   return S_OK;
}

STDMETHODIMP CMultiWeb::get_WebCount(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_WebCount;
   return S_OK;
}

STDMETHODIMP CMultiWeb::put_WebCount(WebIndexType newVal)
{
   MakeDirty();

   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb,GEOMETRY_E_DIMENSION);

   m_WebCount = newVal;

   return S_OK;
}

STDMETHODIMP CMultiWeb::get_WebLocation(WebIndexType webIdx,Float64* location)
{
   CHECK_RETVAL(location);
   if ( webIdx < 0 || m_WebCount <= webIdx )
      return E_INVALIDARG;

   Float64 W;
   get_TopFlangeWidth(&W);

   (*location) = (m_W1 + webIdx*(m_W2+m_T1) + m_T1/2) - W/2;

   return S_OK;
}

STDMETHODIMP CMultiWeb::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);

   m_pHookPoint.QueryInterface( hookPnt );

   return S_OK;
}

STDMETHODIMP CMultiWeb::putref_HookPoint(IPoint2d* hookPnt)
{
   MakeDirty();

   HRESULT hr = CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
   return hr;
}

STDMETHODIMP CMultiWeb::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D1+m_D2;

   return S_OK;
}

STDMETHODIMP CMultiWeb::get_AvgWebWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_WebCount*(m_T1+m_T2)/2.;

   return S_OK;
}

STDMETHODIMP CMultiWeb::get_TopFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = 2*m_W1 + m_WebCount*m_T1 + (m_WebCount-1)*m_W2;

   return S_OK;
}

STDMETHODIMP CMultiWeb::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CMultiWeb::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMultiWeb::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_ShapeProperties(pVal);
}

STDMETHODIMP CMultiWeb::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_BoundingBox(pVal);
}

STDMETHODIMP CMultiWeb::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CMultiWeb::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CMultiWeb::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CMultiWeb>* pTheClone;
   HRESULT hr = CComObject<CMultiWeb>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IMultiWeb> shape(pTheClone); // need at least one reference

   pTheClone->put_D1( m_D1 );
   pTheClone->put_D2( m_D2 );
   pTheClone->put_T1( m_T1 );
   pTheClone->put_T2( m_T2 );
   pTheClone->put_W1( m_W1 );
   pTheClone->put_W2( m_W2 );
   pTheClone->put_WebCount( m_WebCount );

   CComPtr<IPoint2d> hookPnt;
   CreatePoint(m_pHookPoint,NULL,&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);
   pTheClone->Rotate( 0.00, 0.00, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CMultiWeb::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CMultiWeb::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CMultiWeb::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_Perimeter(pVal);
}

STDMETHODIMP CMultiWeb::FurthestDistance(ILine2d* line,Float64 *pVal)
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

STDMETHODIMP CMultiWeb::Offset(Float64 dx,Float64 dy)
{
   // no need to call MakeDirty since our hookpoint will call us back

   m_pHookPoint->Offset(dx,dy);
   return S_OK;
}

STDMETHODIMP CMultiWeb::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->get_Dx(&dx);
   pSize->get_Dy(&dy);

   return Offset(dx,dy);
}

STDMETHODIMP CMultiWeb::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   UpdateShape();

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,NULL,point);
}

STDMETHODIMP CMultiWeb::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   MakeDirty();

   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CMultiWeb::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
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

STDMETHODIMP CMultiWeb::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CMultiWeb::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   // no need to make dirty since our hook point will call us back
   m_pHookPoint->Rotate(cx,cy,angle);
   
   // Need to keep track of rotation amount when updating polygon
   m_Rotation += angle;

   return S_OK;
}


STDMETHODIMP CMultiWeb::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CMultiWeb::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CMultiWeb::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("MultiWeb"),1.0);
   pSave->put_Property(CComBSTR("D1"),CComVariant(m_D1));
   pSave->put_Property(CComBSTR("D2"),CComVariant(m_D2));
   pSave->put_Property(CComBSTR("T1"),CComVariant(m_T1));
   pSave->put_Property(CComBSTR("T2"),CComVariant(m_T2));
   pSave->put_Property(CComBSTR("W1"),CComVariant(m_W1));
   pSave->put_Property(CComBSTR("W2"),CComVariant(m_W2));
   pSave->put_Property(CComBSTR("WebCount"),CComVariant(m_WebCount));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CMultiWeb::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("MultiWeb"));
   
   pLoad->get_Property(CComBSTR("D1"),&var);
   m_D1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D2"),&var);
   m_D2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("T1"),&var);
   m_T1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("T2"),&var);
   m_T2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W1"),&var);
   m_W1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W2"),&var);
   m_W2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("WebCount"),&var);
   m_WebCount = var.iVal;
   
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

STDMETHODIMP CMultiWeb::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}
