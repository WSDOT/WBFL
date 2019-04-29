///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2019  Washington State Department of Transportation
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

// DeckedSlabBeam.cpp : Implementation of CDeckedSlabBeam
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "DeckedSlabBeam.h"
#include "Helper.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////



// CDeckedSlabBeam
HRESULT CDeckedSlabBeam::FinalConstruct()
{
   m_Rotation = 0.00;
   m_A    = 0.00;
   m_B    = 0.00;
   m_C   = 0.00;
   m_W   = 0.00;
   m_Tt   = 0.00;
   m_Tb = 0.00;
   m_F = 0.00;

   m_VoidCount = 1;

   m_bLeftBlockOut = VARIANT_TRUE;
   m_bRightBlockOut = VARIANT_TRUE;

   CreatePoint( 0.00, 0.00, nullptr, &m_pHookPoint );
   HRESULT hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   CreateCompositeShape( &m_pShape );

   m_Dirty = true;

   return S_OK;
}

void CDeckedSlabBeam::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CDeckedSlabBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IDeckedSlabBeam,
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

HRESULT CDeckedSlabBeam::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
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

HRESULT CDeckedSlabBeam::UpdateShape()
{

   if (m_Dirty)
   {
      // create a new shape
      m_pShape.Release();
      CreateCompositeShape(&m_pShape);

      // Create the outer poly
      CComPtr<IPolyShape> slab;
      slab.CoCreateInstance(CLSID_PolyShape);
      Float64 Wb = m_A-2*m_B;
      slab->AddPoint( Wb/2,      0.0);  // bottom right corner
      slab->AddPoint( Wb/2,      m_C);
      slab->AddPoint(m_A/2,      m_C);

      if ( m_bRightBlockOut == VARIANT_TRUE )
      {
         slab->AddPoint(m_A/2-m_F,    m_C+m_Tt);
      }
      else
      {
         slab->AddPoint(m_A/2,        m_C+m_Tt);
      }

      // top left corner
      if ( m_bLeftBlockOut == VARIANT_TRUE )
      {
         slab->AddPoint(-(m_A/2-m_F),    m_C+m_Tt);
      }
      else
      {
         slab->AddPoint(-m_A/2,          m_C+m_Tt);
      }

      slab->AddPoint(-m_A/2,     m_C);
      slab->AddPoint(-Wb/2,      m_C);
      slab->AddPoint(-Wb/2,      0.0);

      CComQIPtr<IShape> slabShape(slab);
      m_pShape->AddShape(slabShape,VARIANT_FALSE);

      // put an exterior void in the center of the beam
      if (m_VoidCount >0)
      {
         CComPtr<IPolyShape> rvoid;
         rvoid.CoCreateInstance(CLSID_PolyShape);
         Float64 Wv2 = (Wb - 2*m_W)/2.0; // half width of void
         rvoid->AddPoint( Wv2,      m_Tb);
         rvoid->AddPoint( Wv2,      m_C);
         rvoid->AddPoint(-Wv2,      m_C);
         rvoid->AddPoint(-Wv2,      m_Tb);
         CComQIPtr<IShape> voidShape(rvoid);
         m_pShape->AddShape(voidShape,VARIANT_TRUE);
      }

      CComQIPtr<IXYPosition> pPosition(m_pShape);

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

STDMETHODIMP CDeckedSlabBeam::get_A(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_A;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_A(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IDeckedSlabBeam,GEOMETRY_E_DIMENSION);

   m_A = newVal;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_B(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_B;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_B(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IDeckedSlabBeam,GEOMETRY_E_DIMENSION);

   m_B = newVal;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_C(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_C;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_C(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IDeckedSlabBeam,GEOMETRY_E_DIMENSION);

   m_C = newVal;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_W(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_W;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_W(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IDeckedSlabBeam,GEOMETRY_E_DIMENSION);

   m_W = newVal;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_F(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_F;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_F(Float64 neFVal)
{
   MakeDirty();

   if ( neFVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IDeckedSlabBeam,GEOMETRY_E_DIMENSION);

   m_F = neFVal;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_Tt(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Tt;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_Tt(Float64 neTtVal)
{
   MakeDirty();

   if ( neTtVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IDeckedSlabBeam,GEOMETRY_E_DIMENSION);

   m_Tt = neTtVal;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_Tb(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Tb;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_Tb(Float64 neTbVal)
{
   MakeDirty();

   if ( neTbVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IDeckedSlabBeam,GEOMETRY_E_DIMENSION);

   m_Tb = neTbVal;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_LeftBlockOut(VARIANT_BOOL bLeftBlockOut)
{
   MakeDirty();
   m_bLeftBlockOut = bLeftBlockOut;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_LeftBlockOut(VARIANT_BOOL* pbLeftBlockOut)
{
   CHECK_RETVAL(pbLeftBlockOut);
   *pbLeftBlockOut = m_bLeftBlockOut;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_RightBlockOut(VARIANT_BOOL bRightBlockOut)
{
   MakeDirty();
   m_bRightBlockOut = bRightBlockOut;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_RightBlockOut(VARIANT_BOOL* pbRightBlockOut)
{
   CHECK_RETVAL(pbRightBlockOut);
   *pbRightBlockOut = m_bRightBlockOut;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_VoidCount(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_VoidCount;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_VoidCount(CollectionIndexType newVal)
{
   MakeDirty();

   // Void count can be 0 or 1
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab,GEOMETRY_E_DIMENSION);
   if ( newVal > 1 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab,GEOMETRY_E_DIMENSION);

   m_VoidCount = newVal;

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_Height(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Tt + m_C;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);

   m_pHookPoint.QueryInterface( hookPnt );

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::putref_HookPoint(IPoint2d* hookPnt)
{
   MakeDirty();

   HRESULT hr = CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
   return hr;
}

STDMETHODIMP CDeckedSlabBeam::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CDeckedSlabBeam::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CDeckedSlabBeam::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_ShapeProperties(pVal);
}

STDMETHODIMP CDeckedSlabBeam::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_BoundingBox(pVal);
}

STDMETHODIMP CDeckedSlabBeam::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CDeckedSlabBeam::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CDeckedSlabBeam::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CDeckedSlabBeam>* pTheClone;
   HRESULT hr = CComObject<CDeckedSlabBeam>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IDeckedSlabBeam> shape(pTheClone); // need at least one reference

   pTheClone->put_A( m_A );
   pTheClone->put_B( m_B );
   pTheClone->put_C( m_C );
   pTheClone->put_W( m_W );
   pTheClone->put_F( m_F );
   pTheClone->put_Tt( m_Tt );
   pTheClone->put_Tb( m_Tb );
   pTheClone->put_LeftBlockOut(m_bLeftBlockOut);
   pTheClone->put_RightBlockOut(m_bRightBlockOut);
   pTheClone->put_VoidCount(m_VoidCount);

   CComPtr<IPoint2d> hookPnt;
   CreatePoint(m_pHookPoint,nullptr,&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);
   pTheClone->Rotate( 0.00, 0.00, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CDeckedSlabBeam::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CDeckedSlabBeam::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_Perimeter(pVal);
}

STDMETHODIMP CDeckedSlabBeam::FurthestDistance(ILine2d* line,Float64 *pVal)
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

STDMETHODIMP CDeckedSlabBeam::get_Item(CollectionIndexType idx,ICompositeShapeItem* *pVal)
{
   UpdateShape();
   return m_pShape->get_Item(idx,pVal);
}

STDMETHODIMP CDeckedSlabBeam::get__NewEnum(IUnknown* *pVal)
{
   UpdateShape();
   return m_pShape->get__NewEnum(pVal);
}

STDMETHODIMP CDeckedSlabBeam::get_Count(CollectionIndexType *pVal)
{
   UpdateShape();
   return m_pShape->get_Count(pVal);
}

STDMETHODIMP CDeckedSlabBeam::Remove(CollectionIndexType idx)
{
   return m_pShape->Remove(idx);
}

STDMETHODIMP CDeckedSlabBeam::Clear()
{
   return m_pShape->Clear();
}

STDMETHODIMP CDeckedSlabBeam::ReplaceEx(CollectionIndexType idx,ICompositeShapeItem* pShapeItem)
{
   return m_pShape->ReplaceEx(idx,pShapeItem);
}

STDMETHODIMP CDeckedSlabBeam::Replace(CollectionIndexType idx,IShape* pShape)
{
   return m_pShape->Replace(idx,pShape);
}

STDMETHODIMP CDeckedSlabBeam::AddShapeEx(ICompositeShapeItem* ShapeItem)
{
   return m_pShape->AddShapeEx(ShapeItem);
}

STDMETHODIMP CDeckedSlabBeam::AddShape(IShape* shape,VARIANT_BOOL bVoid)
{
   return m_pShape->AddShape(shape,bVoid);
}

/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CDeckedSlabBeam::Offset(Float64 dx,Float64 dy)
{
   // no need to call MakeDirty since our hookpoint will call us back

   m_pHookPoint->Offset(dx,dy);
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->get_Dx(&dx);
   pSize->get_Dy(&dy);

   return Offset(dx,dy);
}

STDMETHODIMP CDeckedSlabBeam::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   UpdateShape();

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,nullptr,point);
}

STDMETHODIMP CDeckedSlabBeam::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   MakeDirty();

   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CDeckedSlabBeam::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
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

STDMETHODIMP CDeckedSlabBeam::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CDeckedSlabBeam::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   // no need to make dirty since our hook point will call us back
   m_pHookPoint->Rotate(cx,cy,angle);
   
   // Need to keep track of rotation amount when updating polygon
   m_Rotation += angle;

   return S_OK;
}


STDMETHODIMP CDeckedSlabBeam::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CDeckedSlabBeam::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CDeckedSlabBeam::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("DeckedSlabBeam"),1.0);
   pSave->put_Property(CComBSTR("A"),CComVariant(m_A));
   pSave->put_Property(CComBSTR("B"),CComVariant(m_B));
   pSave->put_Property(CComBSTR("C"),CComVariant(m_C));
   pSave->put_Property(CComBSTR("W"),CComVariant(m_W));
   pSave->put_Property(CComBSTR("F"),CComVariant(m_F));
   pSave->put_Property(CComBSTR("Tt"),CComVariant(m_Tt));
   pSave->put_Property(CComBSTR("Tb"),CComVariant(m_Tb));
   pSave->put_Property(CComBSTR("LeftBlockOut"),CComVariant(m_bLeftBlockOut));
   pSave->put_Property(CComBSTR("RightBlockOut"),CComVariant(m_bRightBlockOut));
   pSave->put_Property(CComBSTR("VoidCount"),CComVariant(m_VoidCount));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("DeckedSlabBeam"));
   
   pLoad->get_Property(CComBSTR("A"),&var);
   m_A = var.dblVal;
   
   pLoad->get_Property(CComBSTR("B"),&var);
   m_B = var.dblVal;
   
   pLoad->get_Property(CComBSTR("C"),&var);
   m_C = var.dblVal;
   
   pLoad->get_Property(CComBSTR("W"),&var);
   m_W = var.dblVal;

   pLoad->get_Property(CComBSTR("F"),&var);
   m_F = var.dblVal;

   pLoad->get_Property(CComBSTR("Tt"),&var);
   m_Tt = var.dblVal;

   pLoad->get_Property(CComBSTR("Tb"),&var);
   m_Tb = var.dblVal;

   pLoad->get_Property(CComBSTR("LeftBlockOut"),&var);
   m_bLeftBlockOut = var.boolVal;

   pLoad->get_Property(CComBSTR("RightBlockOut"),&var);
   m_bRightBlockOut = var.boolVal;
   
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

STDMETHODIMP CDeckedSlabBeam::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}
