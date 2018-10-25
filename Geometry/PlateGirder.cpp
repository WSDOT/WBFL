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

// PlateGirder.cpp : Implementation of CPlateGirder
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "PlateGirder.h"
#include "Helper.h"

#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlateGirder
HRESULT CPlateGirder::FinalConstruct()
{
   m_Rotation  = 0.00;
	m_webThick  = 0.00;
	m_webHeight = 0.00;
	m_bfThick   = 0.00;
	m_bfWidth   = 0.00;
	m_tfThick   = 0.00;
	m_tfWidth   = 0.00;

   CreatePoint( 0.00, 0.00, NULL, &m_pHookPoint );
   HRESULT hr = CrAdvise(m_pHookPoint, this, IID_IPoint2dEvents, &m_HookPointCookie);
   if (FAILED(hr))
      return hr;

   CreatePolyShape( &m_pShape );

   m_Dirty = true;

   return S_OK;
}

void CPlateGirder::FinalRelease()
{
   HRESULT hr = CrUnadvise(m_pHookPoint, this, IID_IPoint2dEvents, m_HookPointCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CPlateGirder::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPlateGirder,
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

HRESULT CPlateGirder::UpdateShape()
{
   if (m_Dirty)
   {

      // clear the polygon implemenation and recalculate all of the points
      m_pShape->Clear();

      // start at bottom center and go around counter-clockwise
      // there are 13 points total. point 1 is bottom left, point 6 is the
      // top left corner.
      Float64 p1_x = -m_bfWidth/2;
      Float64 p1_y =  0.;
      Float64 p2_x = -m_bfWidth/2;
      Float64 p2_y =  m_bfThick;
      Float64 p3_x = -m_webThick/2;
      Float64 p3_y =  m_bfThick;
      Float64 p4_x = -m_webThick/2;
      Float64 p4_y =  m_bfThick + m_webHeight;
      Float64 p5_x = -m_tfWidth/2;
      Float64 p5_y =  m_bfThick + m_webHeight;
      Float64 p6_x = -m_tfWidth/2;
      Float64 p6_y =  m_bfThick + m_webHeight + m_tfThick;

      m_pShape->AddPoint( p1_x, p1_y); // 1
      m_pShape->AddPoint( p2_x, p2_y);
      m_pShape->AddPoint( p3_x, p3_y);
      m_pShape->AddPoint( p4_x, p4_y);  
      m_pShape->AddPoint( p5_x, p5_y);
      m_pShape->AddPoint( p6_x, p6_y);  // 6
      m_pShape->AddPoint( -p6_x, p6_y);
      m_pShape->AddPoint( -p5_x, p5_y);
      m_pShape->AddPoint( -p4_x, p4_y);  
      m_pShape->AddPoint( -p3_x, p3_y);
      m_pShape->AddPoint( -p2_x, p2_y);
      m_pShape->AddPoint( -p1_x, p1_y); // 13 = 1

      CComQIPtr<IXYPosition> pPosition(m_pShape);

      // Rotate the shape to the proper rotation angle
      if (!IsZero(m_Rotation))
      {
         pPosition->Rotate(0.00,0.00,m_Rotation);
      }

      // Translate the shape to the proper position
      CComPtr<IPoint2d> origin;
      CreatePoint(0.00,0.00,NULL,&origin);  // Hook Point at Bottom Center
      pPosition->MoveEx(origin,m_pHookPoint);

      m_Dirty = false;
   }

   return S_OK;
}

HRESULT CPlateGirder::GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py)
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


STDMETHODIMP CPlateGirder::get_TopFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_tfWidth;
	return S_OK;
}

STDMETHODIMP CPlateGirder::put_TopFlangeWidth(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPlateGirder,GEOMETRY_E_DIMENSION);

   m_tfWidth = newVal;

	return S_OK;
}

STDMETHODIMP CPlateGirder::get_TopFlangeThick(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_tfThick;
	return S_OK;
}

STDMETHODIMP CPlateGirder::put_TopFlangeThick(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPlateGirder,GEOMETRY_E_DIMENSION);

   m_tfThick = newVal;

	return S_OK;
}

STDMETHODIMP CPlateGirder::get_BottomFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_bfWidth;
	return S_OK;
}

STDMETHODIMP CPlateGirder::put_BottomFlangeWidth(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPlateGirder,GEOMETRY_E_DIMENSION);

   m_bfWidth = newVal;

	return S_OK;
}

STDMETHODIMP CPlateGirder::get_BottomFlangeThick(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_bfThick;
	return S_OK;
}

STDMETHODIMP CPlateGirder::put_BottomFlangeThick(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPlateGirder,GEOMETRY_E_DIMENSION);

   m_bfThick = newVal;

	return S_OK;
}

STDMETHODIMP CPlateGirder::get_WebHeight(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_webHeight;
	return S_OK;
}

STDMETHODIMP CPlateGirder::put_WebHeight(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPlateGirder,GEOMETRY_E_DIMENSION);

   m_webHeight = newVal;

	return S_OK;
}

STDMETHODIMP CPlateGirder::get_WebThick(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_webThick;
	return S_OK;
}

STDMETHODIMP CPlateGirder::put_WebThick(Float64 newVal)
{
   MakeDirty();

   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPlateGirder,GEOMETRY_E_DIMENSION);

   m_webThick = newVal;

	return S_OK;
}

STDMETHODIMP CPlateGirder::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_bfThick + m_webHeight + m_tfThick;
	return S_OK;
}

STDMETHODIMP CPlateGirder::get_QTopFlange(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 Aflange = m_tfWidth * m_tfThick;
   Float64 cgFlange = m_bfThick + m_webHeight + m_tfThick/2;

   CComPtr<IShapeProperties> props;
   get_ShapeProperties(&props);

   Float64 Ybot;
   props->get_Ybottom(&Ybot);

   Float64 Q = Aflange*(cgFlange - Ybot);

   *pVal = Q;
	return S_OK;
}

STDMETHODIMP CPlateGirder::get_QBottomFlange(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 Aflange = m_bfWidth * m_bfThick;
   Float64 cgFlange = m_bfThick/2;


   CComPtr<IShapeProperties> props;
   get_ShapeProperties(&props);

   Float64 Ybot;
   props->get_Ybottom(&Ybot);

   Float64 Q = Aflange*(Ybot - cgFlange);

   *pVal = Q;
	return S_OK;
}

STDMETHODIMP CPlateGirder::get_HookPoint(IPoint2d **hookPnt)
{
   CHECK_RETOBJ(hookPnt);

   m_pHookPoint.QueryInterface( hookPnt );

   return S_OK;
}

STDMETHODIMP CPlateGirder::putref_HookPoint(IPoint2d *hookPnt)
{
   MakeDirty();

   HRESULT hr = CrAssignPointer(m_pHookPoint, hookPnt, this, IID_IPoint2dEvents, &m_HookPointCookie);
   return hr;
}

STDMETHODIMP CPlateGirder::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CPlateGirder::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CPlateGirder::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_ShapeProperties(pVal);
}

STDMETHODIMP CPlateGirder::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_BoundingBox(pVal);
}

STDMETHODIMP CPlateGirder::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CPlateGirder::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CPlateGirder::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CPlateGirder>* pTheClone;
   HRESULT hr = CComObject<CPlateGirder>::CreateInstance( &pTheClone );
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPlateGirder> shape(pTheClone); // need at least one reference

   pTheClone->put_BottomFlangeThick(m_bfThick);
   pTheClone->put_BottomFlangeWidth(m_bfWidth);
   pTheClone->put_TopFlangeThick(m_tfThick);
   pTheClone->put_TopFlangeWidth(m_tfWidth);
   pTheClone->put_WebHeight(m_webHeight);
   pTheClone->put_WebThick(m_webThick);

   CComPtr<IPoint2d> hookPnt;
   CreatePoint(m_pHookPoint,NULL,&hookPnt);
   pTheClone->putref_HookPoint(hookPnt);
   pTheClone->Rotate( 0.00, 0.00, m_Rotation );

   pTheClone->QueryInterface( pClone );

   return S_OK;
}

STDMETHODIMP CPlateGirder::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CPlateGirder::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);

   UpdateShape();
   CComQIPtr<IShape> pIShape(m_pShape);
   return pIShape->ClipIn(pRect,pShape);
}

STDMETHODIMP CPlateGirder::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   UpdateShape();
   CComQIPtr<IShape> pShape(m_pShape);
   return pShape->get_Perimeter(pVal);
}

STDMETHODIMP CPlateGirder::FurthestDistance(ILine2d* line,Float64 *pVal)
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

STDMETHODIMP CPlateGirder::Offset(Float64 dx,Float64 dy)
{
   // no need to call MakeDirty since our hookpoint will call us back
   m_pHookPoint->Offset(dx,dy);
   return S_OK;
}

STDMETHODIMP CPlateGirder::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->get_Dx(&dx);
   pSize->get_Dy(&dy);

   return Offset(dx,dy);
}

STDMETHODIMP CPlateGirder::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   UpdateShape();

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);
   return CreatePoint(lx,ly,NULL,point);
}

STDMETHODIMP CPlateGirder::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CHECK_IN(point);

   Float64 lx,ly;
   GetLocatorPoint(lp,&lx,&ly);

   Float64 cx,cy;
   GetCoordinates(point,&cx,&cy);

   return Offset(cx-lx,cy-ly);
}

STDMETHODIMP CPlateGirder::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
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

STDMETHODIMP CPlateGirder::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CPlateGirder::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_pHookPoint->Rotate(cx,cy,angle);
   
   // Need to keep track of rotation amount when updating polygon
   m_Rotation += angle;

   return S_OK;
}


STDMETHODIMP CPlateGirder::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CPlateGirder::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CPlateGirder::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("PlateGirder"),1.0);
   pSave->put_Property(CComBSTR("bfThick"),CComVariant(m_bfThick));
   pSave->put_Property(CComBSTR("bfWidth"),CComVariant(m_bfWidth));
   pSave->put_Property(CComBSTR("tfThick"),CComVariant(m_tfThick));
   pSave->put_Property(CComBSTR("tfWidth"),CComVariant(m_tfWidth));
   pSave->put_Property(CComBSTR("webHeight"),CComVariant(m_webHeight));
   pSave->put_Property(CComBSTR("webThick"),CComVariant(m_webThick));
   pSave->put_Property(CComBSTR("Rotation"),CComVariant(m_Rotation));
   pSave->put_Property(CComBSTR("HookPoint"),CComVariant(m_pHookPoint));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CPlateGirder::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("PlateGirder"));

   pLoad->get_Property(CComBSTR("bfThick"),&var);
   m_bfThick = var.dblVal;

   pLoad->get_Property(CComBSTR("bfWidth"),&var);
   m_bfWidth = var.dblVal;

   pLoad->get_Property(CComBSTR("tfThick"),&var);
   m_tfThick = var.dblVal;

   pLoad->get_Property(CComBSTR("tfWidth"),&var);
   m_tfWidth = var.dblVal;
   
   pLoad->get_Property(CComBSTR("webHeight"),&var);
   m_webHeight = var.dblVal;

   pLoad->get_Property(CComBSTR("webThick"),&var);
   m_webThick = var.dblVal;

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

STDMETHODIMP CPlateGirder::OnPointChanged(IPoint2d* point)
{
   // our hook point got changed
   MakeDirty();

   return S_OK;
}
