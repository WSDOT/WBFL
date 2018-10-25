///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

// SidewalkBarrier.cpp : Implementation of CSidewalkBarrier
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "SidewalkBarrier.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSidewalkBarrier
HRESULT CSidewalkBarrier::FinalConstruct()
{
   m_CompShape.CoCreateInstance(CLSID_CompositeShape);
   m_Material.CoCreateInstance(CLSID_Material);

   return S_OK;
}

void CSidewalkBarrier::FinalRelease()
{
}

STDMETHODIMP CSidewalkBarrier::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISidewalkBarrier,
      &IID_IBarrier,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CSidewalkBarrier::Clone(IBarrier** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CSidewalkBarrier>* pClone;
   CComObject<CSidewalkBarrier>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   if ( m_Configuration == 1 )
   {
      pClone->put_Barrier1(m_ExtBarrier,m_ConnectionWidth);
   }
   else if ( m_Configuration == 2 )
   {
      pClone->put_Barrier2(m_ExtBarrier,m_H1,m_H2,m_W,m_Orientation,m_SidewalkPosition,m_ConnectionWidth);
   }
   else if ( m_Configuration == 3 )
   {
      pClone->put_Barrier3(m_ExtBarrier,m_H1,m_H2,m_W,m_IntBarrier,m_Orientation,m_SidewalkPosition,m_ConnectionWidth);
   }

   pClone->put_IsExteriorStructurallyContinuous(m_bExteriorStructurallyContinuous);
   pClone->put_IsSidewalkStructurallyContinuous(m_bSidewalkStructurallyContinuous);
   pClone->put_IsInteriorStructurallyContinuous(m_bInteriorStructurallyContinuous);
 
   (*clone)->putref_Material(m_Material);
   (*clone)->put_Path(m_Path);

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_Shape(IShape** shape)
{
   CHECK_RETOBJ(shape);

   CComQIPtr<IShape> s(m_CompShape);
   s->Clone(shape);

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_StructuralShape(IShape** shape)
{
   if ( m_bExteriorStructurallyContinuous == VARIANT_FALSE && 
        m_bSidewalkStructurallyContinuous == VARIANT_FALSE &&
        m_bInteriorStructurallyContinuous == VARIANT_FALSE )
   {
      (*shape) = NULL;
      return S_OK;
   }


   CComPtr<ICompositeShape> compShape;
   compShape.CoCreateInstance(CLSID_CompositeShape);

   if ( m_bExteriorStructurallyContinuous == VARIANT_TRUE )
   {
      CComPtr<ICompositeShapeItem> shapeItem;
      m_CompShape->get_Item(m_idxExteriorBarrier, &shapeItem);
      compShape->AddShapeEx(shapeItem);
   }

   if ( m_bSidewalkStructurallyContinuous == VARIANT_TRUE )
   {
      CComPtr<ICompositeShapeItem> shapeItem;
      m_CompShape->get_Item(m_idxSidewalk, &shapeItem);
      compShape->AddShapeEx(shapeItem);
   }

   if ( m_bInteriorStructurallyContinuous == VARIANT_TRUE )
   {
      CComPtr<ICompositeShapeItem> shapeItem;
      m_CompShape->get_Item(m_idxInteriorBarrier, &shapeItem);
      compShape->AddShapeEx(shapeItem);
   }

   compShape.QueryInterface(shape);
   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::put_Barrier1(IShape* shape,Float64 connectionWidth)
{
   // single barrier configuration
   CHECK_IN(shape);

   m_ConnectionWidth = connectionWidth;

   m_CompShape->Clear();
   m_CompShape->AddShape(shape,VARIANT_FALSE);

   m_ExtBarrier = shape;
   m_W = 0;
   m_Configuration = 1;

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::put_Barrier2(IShape* shape,Float64 h1,Float64 h2,Float64 w,TrafficBarrierOrientation orientation,SidewalkPositionType swPosition,Float64 connectionWidth)
{
   // single barrier and sidewalk configuration
   CHECK_IN(shape);

   m_ConnectionWidth = connectionWidth;

   m_SidewalkPosition = swPosition;

   m_Orientation = orientation;

   m_CompShape->Clear();

   Float64 xStart;
   Float64 sign;
   if ( m_SidewalkPosition == swpBetweenBarriers )
   {
      // get the bounding box of the exterior barrier
      // the sidewalk starts at its right/left most point
      CComPtr<IRect2d> bbox;
      shape->get_BoundingBox(&bbox);

      if ( orientation == tboLeft )
      {
         bbox->get_Right(&xStart);
         sign = 1;
      }
      else
      {
         bbox->get_Left(&xStart);
         sign = -1;
      }
   }
   else
   {
      m_idxExteriorBarrier = 1;
      m_idxSidewalk = 0;
      // sidewalk starts at the deck's edge
      xStart = 0;

      if ( orientation == tboLeft )
      {
         sign = 1;
      }
      else
      {
         sign = -1;
      }

      // move the barrier so it is above the sidewalk
      CComQIPtr<IXYPosition> position(shape);
      CComPtr<IPoint2d> hp;
      position->get_LocatorPoint(lpHookPoint,&hp);
      hp->Move(0,h1);
      position->put_LocatorPoint(lpHookPoint,hp);
   }


   // sidewalk coordinates
   Float64 x[4], y[4];
   x[0] = xStart;
   y[0] = 0;

   x[1] = xStart;
   y[1] = h1;

   x[2] = xStart + sign*w;
   y[2] = h2;

   x[3] = xStart + sign*w;
   y[3] = 0;

   // create the sidewalk shape
   CComPtr<IPolyShape> sidewalk;
   sidewalk.CoCreateInstance(CLSID_PolyShape);

   sidewalk->AddPoint(x[0],y[0]);
   sidewalk->AddPoint(x[1],y[1]);
   sidewalk->AddPoint(x[2],y[2]);
   sidewalk->AddPoint(x[3],y[3]);

   CComQIPtr<IShape> shapeSidewalk(sidewalk);

   if ( m_SidewalkPosition == swpBetweenBarriers )
   {
      m_CompShape->AddShape(shape,VARIANT_FALSE);
      m_CompShape->AddShape(shapeSidewalk,VARIANT_FALSE);
   }
   else
   {
      m_CompShape->AddShape(shapeSidewalk,VARIANT_FALSE);
      m_CompShape->AddShape(shape,VARIANT_FALSE);
   }

   m_ExtBarrier = shape;
   m_H1 = h1;
   m_H2 = h2;
   m_W  = w;
   m_Configuration = 2;

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::put_Barrier3(IShape* extShape,Float64 h1,Float64 h2,Float64 w,IShape* intShape,TrafficBarrierOrientation orientation,SidewalkPositionType swPosition,Float64 connectionWidth)
{
   // Float64 barrier and sidewalk configuration
   CHECK_IN(extShape);
   CHECK_IN(intShape);

   m_Orientation = orientation;
   m_ConnectionWidth = connectionWidth;
   m_SidewalkPosition = swPosition;

   m_CompShape->Clear();

   Float64 xStart;
   Float64 sign;
   if ( m_SidewalkPosition == swpBetweenBarriers )
   {
      m_idxExteriorBarrier = 0;
      m_idxSidewalk = 1;

      // get the bounding box of the exterior barrier
      // the sidewalk starts at its right/left most point
      CComPtr<IRect2d> bbox;
      extShape->get_BoundingBox(&bbox);

      if ( orientation == tboLeft )
      {
         bbox->get_Right(&xStart);
         sign = 1;
      }
      else
      {
         bbox->get_Left(&xStart);
         sign = -1;
      }
   }
   else
   {
      m_idxExteriorBarrier = 1;
      m_idxSidewalk = 0;

      // sidewalk starts at the deck's edge
      xStart = 0;

      if ( orientation == tboLeft )
      {
         sign = 1;
      }
      else
      {
         sign = -1;
      }

      // move the barrier so it is above the sidewalk
      CComQIPtr<IXYPosition> position(extShape);
      CComPtr<IPoint2d> hp;
      position->get_LocatorPoint(lpHookPoint,&hp);
      hp->Move(0,h1);
      position->put_LocatorPoint(lpHookPoint,hp);
   }


   // sidewalk coordinates
   Float64 x[4], y[4];
   x[0] = xStart;
   y[0] = 0;

   x[1] = xStart;
   y[1] = h1;

   x[2] = xStart + sign*w;
   y[2] = h2;

   x[3] = xStart + sign*w;
   y[3] = 0;
   
   // create the sidewalk shape
   CComPtr<IPolyShape> sidewalk;
   sidewalk.CoCreateInstance(CLSID_PolyShape);

   sidewalk->AddPoint(x[0],y[0]);
   sidewalk->AddPoint(x[1],y[1]);
   sidewalk->AddPoint(x[2],y[2]);
   sidewalk->AddPoint(x[3],y[3]);

   CComQIPtr<IShape> shapeSidewalk(sidewalk);

   // move the interior barrier
   CComQIPtr<IXYPosition> position(intShape);
   CComPtr<IPoint2d> point;
   LocatorPointType lp;
   if (m_SidewalkPosition == swpBetweenBarriers)
      lp = orientation == tboLeft ? lpBottomLeft : lpBottomRight;
   else
      lp = orientation == tboLeft ? lpBottomRight : lpBottomLeft;

   position->get_LocatorPoint(lp,&point);
   Float64 dx,dy;
   if ( m_SidewalkPosition == swpBetweenBarriers )
   {
      dx = x[3];
      dy = 0;
   }
   else
   {
      dx = x[3];
      dy = h2;
   }
   point->Move(dx,dy);
   position->put_LocatorPoint(lp,point);

   if ( m_SidewalkPosition == swpBetweenBarriers )
   {
      m_CompShape->AddShape(extShape,VARIANT_FALSE);
      m_CompShape->AddShape(shapeSidewalk,VARIANT_FALSE);
   }
   else
   {
      m_CompShape->AddShape(shapeSidewalk,VARIANT_FALSE);
      m_CompShape->AddShape(extShape,VARIANT_FALSE);
   }
   m_CompShape->AddShape(intShape,VARIANT_FALSE);

   m_ExtBarrier = extShape;
   m_H1 = h1;
   m_H2 = h2;
   m_W  = w;
   m_IntBarrier = intShape;
   m_Configuration = 3;

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_SidewalkWidth(Float64* width)
{
   CHECK_RETVAL(width);
   *width = m_W;
   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_Material(IMaterial** material)
{
   CHECK_RETOBJ(material);
   (*material) = m_Material;
   (*material)->AddRef();
   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::putref_Material(IMaterial* material)
{
   if ( m_Material.IsEqualObject(material) )
      return S_OK;

   m_Material = material;

#pragma Reminder("UPDATE: Fire Event")

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_Path(IPath** path)
{
   CHECK_RETOBJ(path);

   m_Path->Clone(path);

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::put_Path(IPath* path)
{
   if ( m_Path.IsEqualObject(path) )
      return S_OK;

   m_Path.Release();
   path->Clone(&m_Path);

#pragma Reminder("UPDATE: Fire Event")

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_ConnectionWidth(Float64 location,Float64* width)
{
   CHECK_RETVAL(width);

   *width = m_ConnectionWidth;
   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_IsStructurallyContinuous(VARIANT_BOOL* pbContinuous)
{
   CHECK_RETVAL(pbContinuous);
   (*pbContinuous) = (m_bExteriorStructurallyContinuous == VARIANT_TRUE) || 
                     (m_bSidewalkStructurallyContinuous == VARIANT_TRUE) || 
                     (m_bInteriorStructurallyContinuous == VARIANT_TRUE) ? VARIANT_TRUE : VARIANT_FALSE;
   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::put_IsStructurallyContinuous(VARIANT_BOOL bContinuous)
{
   m_bInteriorStructurallyContinuous = bContinuous;
   m_bSidewalkStructurallyContinuous = bContinuous;
   m_bExteriorStructurallyContinuous = bContinuous;
   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_ExteriorBarrierShape(IShape** shape)
{
   CComPtr<ICompositeShapeItem> shapeItem;
   m_CompShape->get_Item(0, &shapeItem);

   return shapeItem->get_Shape(shape);
}

STDMETHODIMP CSidewalkBarrier::get_SidewalkShape(IShape** shape)
{
   CComPtr<ICompositeShapeItem> shapeItem;
   m_CompShape->get_Item(1, &shapeItem);

   return shapeItem->get_Shape(shape);
}

STDMETHODIMP CSidewalkBarrier::get_InteriorBarrierShape(IShape** shape)
{
   CComPtr<ICompositeShapeItem> shapeItem;
   m_CompShape->get_Item(2, &shapeItem);

   return shapeItem->get_Shape(shape);
}

STDMETHODIMP CSidewalkBarrier::put_IsInteriorStructurallyContinuous(VARIANT_BOOL bContinuous)
{
   m_bInteriorStructurallyContinuous = bContinuous;
   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::put_IsSidewalkStructurallyContinuous(VARIANT_BOOL bContinuous)
{
   m_bSidewalkStructurallyContinuous = bContinuous;
   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::put_IsExteriorStructurallyContinuous(VARIANT_BOOL bContinuous)
{
   m_bExteriorStructurallyContinuous = bContinuous;
   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CSidewalkBarrier::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("SidewalkBarrier"));

#pragma Reminder("IMPLEMENT: CSidewalkBarrier::Load")
   ATLASSERT(false); // not implemented

   //   load->get_Property(CComBSTR("E"),&var);
//   m_E = var.dblVal;
//
//   load->get_Property(CComBSTR("Density"),&var);
//   m_Density = var.dblVal;

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::Save(IStructuredSave2* save)
{
#pragma Reminder("IMPLEMENT: CSidewalkBarrier::Save")
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("SidewalkBarrier"),1.0);

   ATLASSERT(false); // not implemented

//   save->put_Property(CComBSTR("E"),CComVariant(m_E));
//   save->put_Property(CComBSTR("Density"),CComVariant(m_Density));

   save->EndUnit();

   return S_OK;
}
