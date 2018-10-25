///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// NUBeam.cpp : Implementation of CNUBeam
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "NUBeam.h"
#include "Helper.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNUBeam
HRESULT CNUBeam::FinalConstruct()
{
   m_Rotation = 0.00;
   m_D1 = 0.00;
   m_D2 = 0.00;
   m_D3 = 0.00;
   m_D4 = 0.00;
   m_D5 = 0.00;
   m_T  = 0.00;
   m_W1 = 0.00;
   m_W2 = 0.00;
   m_R1 = 0.00;
   m_R2 = 0.00;
   m_R3 = 0.00;
   m_R4 = 0.00;
   m_C1 = 0.00;

   CreatePoint( 0.00, 0.00, NULL, &m_pHookPoint );
   HRESULT hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   CreatePolyShape( &m_pShape );

   m_Dirty = true;

   return S_OK;
}

void CNUBeam::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CNUBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_INUBeam,
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

HRESULT CNUBeam::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
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

HRESULT CNUBeam::UpdateShape()
{

   if (m_Dirty)
   {
      // clear the polygon implemenation and recalculate all of the points
      m_pShape->Clear();

      const long nSpaces = 20; // number of spaces used to approximate the curved fillets
      Float64 cx, cy;           // center of arc
      Float64 delta;            // sweep angle of arc
      Float64 startAngle;       // start angle for generating points along arc

      // Start at the lower left corner of the shape
      if  ( IsZero(m_C1) )
      {
         m_pShape->AddPoint(-m_W2/2,0.0);
      }
      else
      {
         m_pShape->AddPoint(-m_W2/2+m_C1,0.0);
         m_pShape->AddPoint(-m_W2/2,m_C1);
      }

      // compute angle of bottom flange (measured from vertical)
      delta = atan2( (m_W2-m_T)/2, m_D4 );

      // generate lower left fillet
      cx = -m_W2/2 + m_R4;
      cy = m_D5 - m_R4*tan(delta/2);
      startAngle = M_PI;
      GenerateFillet(m_pShape,cx,cy,m_R4,startAngle,-delta,nSpaces);

      // generate bottom left flange-web fillet
      cx = -m_T/2 - m_R2;
      cy = m_D5 + m_D4 + m_R2*tan(delta/2);
      startAngle = TWO_PI - delta;
      GenerateFillet(m_pShape,cx,cy,m_R2,startAngle,delta,nSpaces);

      // compute angle of top flange (measured from vertical)
      delta = atan2( (m_W1-m_T)/2, m_D2 );

      // generate top left flange-web fillet
      cx = -m_T/2 - m_R1;
      cy = m_D5 + m_D4 + m_D3 - m_R1*tan(delta/2);
      startAngle = 0.0;
      GenerateFillet(m_pShape,cx,cy,m_R1,startAngle,delta,nSpaces);

      // generate top flange left fillet
      cx = -m_W1/2 + m_R3;
      cy = m_D5 + m_D4 + m_D3 + m_D2 + m_R3*tan(delta/2);
      startAngle = M_PI + delta;
      GenerateFillet(m_pShape,cx,cy,m_R3,startAngle,-delta,nSpaces);

      // extreme points on top flange
      m_pShape->AddPoint(-m_W1/2,m_D5 + m_D4 + m_D3 + m_D2 + m_D1);
      m_pShape->AddPoint( m_W1/2,m_D5 + m_D4 + m_D3 + m_D2 + m_D1);

      // generate top flange right fillet
      cx = m_W1/2 - m_R3;
      cy = m_D5 + m_D4 + m_D3 + m_D2 + m_R3*tan(delta/2);
      startAngle = 0;
      GenerateFillet(m_pShape,cx,cy,m_R3,startAngle,-delta,nSpaces);

      // generate top right flange-web fillet
      cx = m_T/2 + m_R1;
      cy = m_D5 + m_D4 + m_D3 - m_R1*tan(delta/2);
      startAngle = M_PI - delta;
      GenerateFillet(m_pShape,cx,cy,m_R1,startAngle,delta,nSpaces);

      // compute angle of bottom flange (measured from vertical)
      delta = atan2( (m_W2-m_T)/2, m_D4 );

      // generate bottom right flange-web fillet
      cx = m_T/2 + m_R2;
      cy = m_D5 + m_D4 + m_R2*tan(delta/2);
      startAngle = M_PI;
      GenerateFillet(m_pShape,cx,cy,m_R2,startAngle,delta,nSpaces);

      // generate bottom flange right fillet
      cx = m_W2/2 - m_R4;
      cy = m_D5 - m_R4*tan(delta/2);
      startAngle = delta;
      GenerateFillet(m_pShape,cx,cy,m_R4,startAngle,-delta,nSpaces);

      // bottom right point
      if ( IsZero(m_C1) )
      {
         m_pShape->AddPoint(m_W2/2,0.0);
      }
      else
      {
         m_pShape->AddPoint(m_W2/2,m_C1);
         m_pShape->AddPoint(m_W2/2-m_C1,0.0);
      }

      // rotate if necessary
      CComQIPtr<IXYPosition> pPosition(m_pShape);
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

STDMETHODIMP CNUBeam::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W1;
   return S_OK;
}

STDMETHODIMP CNUBeam::put_W1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_W1 = newVal;
   return S_OK;
}

STDMETHODIMP CNUBeam::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W2;
   return S_OK;
}

STDMETHODIMP CNUBeam::put_W2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_W2 = newVal;
   return S_OK;
}

STDMETHODIMP CNUBeam::get_D1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D1;
   return S_OK;
}

STDMETHODIMP CNUBeam::put_D1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_D1 = newVal;
   return S_OK;
}

STDMETHODIMP CNUBeam::get_D2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D2;
   return S_OK;
}

STDMETHODIMP CNUBeam::put_D2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_D2 = newVal;
   return S_OK;
}

STDMETHODIMP CNUBeam::get_D3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D3;
   return S_OK;
}

STDMETHODIMP CNUBeam::put_D3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_D3 = newVal;
   return S_OK;
}

STDMETHODIMP CNUBeam::get_D4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D4;
   return S_OK;
}

STDMETHODIMP CNUBeam::put_D4(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_D4 = newVal;
   return S_OK;
}

STDMETHODIMP CNUBeam::get_D5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D5;
   return S_OK;
}

STDMETHODIMP CNUBeam::put_D5(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_D5 = newVal;
   return S_OK;
}

STDMETHODIMP CNUBeam::get_T(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T;
   return S_OK;
}

STDMETHODIMP CNUBeam::put_T(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_T = newVal;

   return S_OK;
}

STDMETHODIMP CNUBeam::get_R1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_R1;
   return S_OK;
}

STDMETHODIMP CNUBeam::put_R1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_R1 = newVal;
   return S_OK;
}

STDMETHODIMP CNUBeam::get_R2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_R2;
   return S_OK;
}

STDMETHODIMP CNUBeam::put_R2(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_R2 = newVal;
   return S_OK;
}

STDMETHODIMP CNUBeam::get_R3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_R3;
   return S_OK;
}

STDMETHODIMP CNUBeam::put_R3(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_R3 = newVal;
   return S_OK;
}

STDMETHODIMP CNUBeam::get_R4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_R4;
   return S_OK;
}

STDMETHODIMP CNUBeam::put_R4(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_R4 = newVal;
   return S_OK;
}

STDMETHODIMP CNUBeam::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_C1;
   return S_OK;
}

STDMETHODIMP CNUBeam::put_C1(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_C1 = newVal;

   return S_OK;
}

STDMETHODIMP CNUBeam::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);

   m_pHookPoint.QueryInterface( hookPnt );

   return S_OK;
}

STDMETHODIMP CNUBeam::putref_HookPoint(IPoint2d* hookPnt)
{
   MakeDirty();

   HRESULT hr = CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
   return hr;
}

STDMETHODIMP CNUBeam::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_D1+m_D2+m_D3+m_D4+m_D5;

   return S_OK;
}

STDMETHODIMP CNUBeam::get_AvgWebWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_T;

   return S_OK;
}

STDMETHODIMP CNUBeam::get_BottomFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W2;

   return S_OK;
}

STDMETHODIMP CNUBeam::get_TopFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W1;

   return S_OK;
}

STDMETHODIMP CNUBeam::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CNUBeam::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CNUBeam::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_ShapeProperties(pVal);
}

STDMETHODIMP CNUBeam::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_BoundingBox(pVal);
}

STDMETHODIMP CNUBeam::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CNUBeam::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CNUBeam::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CNUBeam>* pTheClone;
   HRESULT hr = CComObject<CNUBeam>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<INUBeam> shape(pTheClone); // need at least one reference

   pTheClone->put_D1( m_D1 );
   pTheClone->put_D2( m_D2 );
   pTheClone->put_D3( m_D3 );
   pTheClone->put_D4( m_D4 );
   pTheClone->put_D5( m_D5 );
   pTheClone->put_T( m_T );
   pTheClone->put_W1( m_W1 );
   pTheClone->put_W2( m_W2 );
   pTheClone->put_R1( m_R1 );
   pTheClone->put_R2( m_R2 );
   pTheClone->put_R3( m_R3 );
   pTheClone->put_R4( m_R4 );
   pTheClone->put_C1( m_C1 );

   CComPtr<IPoint2d> hookPnt;
   CreatePoint(m_pHookPoint,NULL,&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);
   pTheClone->Rotate( 0.00, 0.00, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CNUBeam::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CNUBeam::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CNUBeam::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_Perimeter(pVal);
}

STDMETHODIMP CNUBeam::FurthestDistance(ILine2d* line,Float64 *pVal)
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

STDMETHODIMP CNUBeam::Offset(Float64 dx,Float64 dy)
{
   // no need to call MakeDirty since our hookpoint will call us back
   m_pHookPoint->Offset(dx,dy);
   return S_OK;
}

STDMETHODIMP CNUBeam::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->get_Dx(&dx);
   pSize->get_Dy(&dy);

   return Offset(dx,dy);
}

STDMETHODIMP CNUBeam::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   UpdateShape();

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,NULL,point);
}

STDMETHODIMP CNUBeam::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CNUBeam::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
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

STDMETHODIMP CNUBeam::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CNUBeam::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   // no need to call MakeDirty since our hookpoint will call us back
   m_pHookPoint->Rotate(cx,cy,angle);
   
   // Need to keep track of rotation amount when updating polygon
   m_Rotation += angle;

   return S_OK;
}


STDMETHODIMP CNUBeam::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CNUBeam::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CNUBeam::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("NUBeam"),2.0);
   pSave->put_Property(CComBSTR("D1"),CComVariant(m_D1));
   pSave->put_Property(CComBSTR("D2"),CComVariant(m_D2));
   pSave->put_Property(CComBSTR("D3"),CComVariant(m_D3));
   pSave->put_Property(CComBSTR("D4"),CComVariant(m_D4));
   pSave->put_Property(CComBSTR("D5"),CComVariant(m_D5));
   pSave->put_Property(CComBSTR("T"),CComVariant(m_T));
   pSave->put_Property(CComBSTR("W1"),CComVariant(m_W1));
   pSave->put_Property(CComBSTR("W2"),CComVariant(m_W2));
   pSave->put_Property(CComBSTR("R1"),CComVariant(m_R1));
   pSave->put_Property(CComBSTR("R2"),CComVariant(m_R2));
   pSave->put_Property(CComBSTR("R3"),CComVariant(m_R3));
   pSave->put_Property(CComBSTR("R4"),CComVariant(m_R4));
   pSave->put_Property(CComBSTR("C1"),CComVariant(m_C1)); // added in version 2.0
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CNUBeam::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("NUBeam"));
   
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
   
   pLoad->get_Property(CComBSTR("T"),&var);
   m_T = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W1"),&var);
   m_W1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W2"),&var);
   m_W2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("R1"),&var);
   m_R1 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("R2"),&var);
   m_R2 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("R3"),&var);
   m_R3 = var.dblVal;
   
   pLoad->get_Property(CComBSTR("R4"),&var);
   m_R4 = var.dblVal;

   Float64 version;
   pLoad->get_Version(&version);
   if ( 1.0 < version )
   {
      pLoad->get_Property(CComBSTR("C1"),&var);
      m_C1 = var.dblVal;
   }
   
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

void CNUBeam::GenerateFillet(IPolyShape* pShape,Float64 cx,Float64 cy,Float64 r,Float64 startAngle,Float64 delta,long nSpaces)
{
   if (!IsZero(r))
   {
   Float64 dAngle = delta/nSpaces;
   for ( long i = 0; i <= nSpaces; i++ )
   {
      Float64 x = cx + r*cos(startAngle + i*dAngle);
      Float64 y = cy + r*sin(startAngle + i*dAngle);

         pShape->AddPoint(x,y);
      }
   }
   else
   {
      // No radius 
      Float64 x = cx;
      Float64 y = cy;
      pShape->AddPoint(x,y);
   }
}

STDMETHODIMP CNUBeam::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}
