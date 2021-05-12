///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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
CSidewalkBarrier::CSidewalkBarrier()
{
   m_Configuration = 0;
   m_bExteriorStructurallyContinuous = VARIANT_FALSE;
   m_bSidewalkStructurallyContinuous = VARIANT_FALSE;
   m_bInteriorStructurallyContinuous = VARIANT_FALSE;
   m_SidewalkPosition = swpBetweenBarriers;
}


HRESULT CSidewalkBarrier::FinalConstruct()
{
   m_SidewalkShape.CoCreateInstance(CLSID_PolyShape);
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
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSidewalkBarrier::Clone(ISidewalkBarrier** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CSidewalkBarrier>* pClone;
   CComObject<CSidewalkBarrier>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   CComPtr<IBarrier> extClone;
   m_ExtBarrier->Clone(&extClone);

   if ( m_Configuration == 1 )
   {
      pClone->put_Barrier1(extClone,m_Orientation);
   }
   else if ( m_Configuration == 2 )
   {
      pClone->put_Barrier2(extClone,m_H1,m_H2,m_W,m_Orientation,m_SidewalkPosition);
   }
   else if ( m_Configuration == 3 )
   {
      CComPtr<IBarrier> intClone;
      m_IntBarrier->Clone(&intClone);

      pClone->put_Barrier3(extClone,m_H1,m_H2,m_W,m_Orientation,m_SidewalkPosition,intClone);
   }

   pClone->put_IsExteriorStructurallyContinuous(m_bExteriorStructurallyContinuous);
   pClone->put_IsSidewalkStructurallyContinuous(m_bSidewalkStructurallyContinuous);
   pClone->put_IsInteriorStructurallyContinuous(m_bInteriorStructurallyContinuous);
 
   (*clone)->put_Path(m_Path);

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_HasSidewalk(VARIANT_BOOL *bHasSw)
{
   *bHasSw = m_Configuration > 1 ? VARIANT_TRUE : VARIANT_FALSE;

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_HasInteriorBarrier(VARIANT_BOOL *bHasIb)
{
   *bHasIb = m_Configuration == 3 ? VARIANT_TRUE : VARIANT_FALSE;

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_Shape(IShape** shape)
{
   CHECK_RETOBJ(shape);

   CComPtr<ICompositeShape> compShape;
   compShape.CoCreateInstance(CLSID_CompositeShape);

   // Copy shapes by reference here - could be dangerous
   CComPtr<IShape> extShape;
   m_ExtBarrier->get_Shape(&extShape);

   compShape->AddShape(extShape, VARIANT_FALSE);

   if (m_Configuration > 1)
   {
      CComQIPtr<IShape> swshape(m_SidewalkShape);
      compShape->AddShape(swshape, VARIANT_FALSE);

      if (m_Configuration > 2)
      {
         CComPtr<IShape> intShape;
         m_IntBarrier->get_Shape(&intShape);
         compShape->AddShape(intShape, VARIANT_FALSE);
      }
   }

   return compShape.QueryInterface(shape);
}


STDMETHODIMP CSidewalkBarrier::get_SidewalkShape(IShape** shape)
{
   CHECK_RETOBJ(shape);

   if (m_Configuration > 1)
   {
      return m_SidewalkShape.QueryInterface(shape);
   }
   else
   {
      ATLASSERT(false); 
      *shape = nullptr;
   }

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_StructuralShape(IShape** shape)
{
   if ( m_bExteriorStructurallyContinuous == VARIANT_FALSE && 
        m_bSidewalkStructurallyContinuous == VARIANT_FALSE &&
        m_bInteriorStructurallyContinuous == VARIANT_FALSE )
   {
      (*shape) = nullptr;
      return S_OK;
   }

   CComPtr<ICompositeShape> compShape;
   compShape.CoCreateInstance(CLSID_CompositeShape);

   if ( m_bExteriorStructurallyContinuous == VARIANT_TRUE )
   {
      CComPtr<IShape> extShape;
      m_ExtBarrier->get_Shape(&extShape);
      compShape->AddShape(extShape, VARIANT_FALSE);
   }

   if (m_Configuration > 1 && m_bSidewalkStructurallyContinuous == VARIANT_TRUE )
   {
      CComQIPtr<IShape> swshape(m_SidewalkShape);
      compShape->AddShape(swshape, VARIANT_FALSE);
   }

   if (m_Configuration > 2 && m_bInteriorStructurallyContinuous == VARIANT_TRUE )
   {
      CComPtr<IShape> intShape;
      m_IntBarrier->get_Shape(&intShape);
      compShape->AddShape(intShape, VARIANT_FALSE);
   }

   compShape.QueryInterface(shape);
   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::put_Barrier1(IBarrier* extBarrier,TrafficBarrierOrientation orientation)
{
   // single barrier configuration
   CHECK_IN(extBarrier);

   m_ExtBarrier = extBarrier;
   m_W = 0;
   m_Configuration = 1;
   m_Orientation = orientation;

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::put_Barrier2(IBarrier* extBarrier,Float64 h1,Float64 h2,Float64 swWidth,
                                            TrafficBarrierOrientation orientation,SidewalkPositionType swPosition)
{
   // single barrier and sidewalk configuration
   CHECK_IN(extBarrier);

   m_SidewalkPosition = swPosition;
   m_Orientation      = orientation;

   m_SidewalkShape->Clear();

   // get the bounding box of the exterior barrier
   // the sidewalk width is measured from at its right/left most point
   CComPtr<IShape> extShape;
   extBarrier->get_Shape(&extShape);

   CComPtr<IRect2d> bbox;
   extShape->get_BoundingBox(&bbox);

   // Get interior edge of barrier
   Float64 xextEdge;
   Float64 sign;
   if ( orientation == tboLeft )
   {
      bbox->get_Right(&xextEdge);
      sign = 1;
   }
   else
   {
      bbox->get_Left(&xextEdge);
      sign = -1;
   }

   Float64 xSwEnd = xextEdge + sign*swWidth; // interior edge of sw is always here

   // Exterior edge depends on sw position
   Float64 xSwStart;
   Float64 swIntToeOffset, swExtToeOffset;
   extBarrier->get_BarrierToeLocations(&swIntToeOffset, &swExtToeOffset);

   if ( m_SidewalkPosition == swpBetweenBarriers )
   {
      // Sidewalk starts at barrier's interior edge
      xSwStart = xextEdge - sign*swIntToeOffset;
   }
   else
   {
      // sidewalk starts at the max of deck's edge and exterior toe of barrier
      Float64 xSwExt;
      if ( orientation == tboLeft )
      {
         bbox->get_Left(&xSwExt);
         xSwExt += swExtToeOffset;
         xSwStart = max(0, xSwExt);
      }
      else
      {
         bbox->get_Right(&xSwExt);
         xSwExt -= swExtToeOffset;
         xSwStart = min(0, xSwExt);
      }

      // move the barrier so it is above the sidewalk
      CComQIPtr<IXYPosition> position(extShape);
      position->Offset(0, h1);
   }

   // sidewalk coordinates
   Float64 x[4], y[4];
   x[0] = xSwStart;
   y[0] = 0;

   x[1] = xSwStart;
   y[1] = h1;

   x[2] = xSwEnd;
   y[2] = h2;

   x[3] = xSwEnd;
   y[3] = 0;

   // Sidewalk shape boundary
   m_SidewalkShape->AddPoint(x[0],y[0]);
   m_SidewalkShape->AddPoint(x[1],y[1]);
   m_SidewalkShape->AddPoint(x[2],y[2]);
   m_SidewalkShape->AddPoint(x[3],y[3]);

   m_ExtBarrier = extBarrier;
   m_H1 = h1;
   m_H2 = h2;
   m_W  = swWidth;
   m_Configuration = 2;

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::put_Barrier3(IBarrier* extBarrier,Float64 h1,Float64 h2,Float64 swWidth,
                                            TrafficBarrierOrientation orientation,SidewalkPositionType swPosition,
                                            IBarrier* intBarrier)
{
   // int/ext barrier and sidewalk configuration
   CHECK_IN(extBarrier);
   CHECK_IN(intBarrier);

   m_SidewalkPosition = swPosition;
   m_Orientation      = orientation;

   m_SidewalkShape->Clear();

   // get the bounding boxes of barriers
   CComPtr<IShape> extShape, intShape;
   extBarrier->get_Shape(&extShape);
   intBarrier->get_Shape(&intShape);

   CComPtr<IRect2d> ext_bbox, int_bbox;
   extShape->get_BoundingBox(&ext_bbox);
   intShape->get_BoundingBox(&int_bbox);

   // The input (nominal) sidewalk width is measured from ext box interior-most point to swWidth
   Float64 extIntEdge;
   Float64 sign;
   if ( orientation == tboLeft )
   {
      ext_bbox->get_Right(&extIntEdge);
      sign = 1;
   }
   else
   {
      ext_bbox->get_Left(&extIntEdge);
      sign = -1;
   }

   // Edges of nominal sw
   Float64 extNomSwEdge = extIntEdge; 
   Float64 intNomSwEdge = extIntEdge + sign*swWidth;

   // Edges of real sidewalk depend on barrier toe locations and sw position
   Float64 extIntToeOffset, extExtToeOffset;
   extBarrier->get_BarrierToeLocations(&extIntToeOffset, &extExtToeOffset);

   Float64 intIntToeOffset, intExtToeOffset;
   intBarrier->get_BarrierToeLocations(&intIntToeOffset, &intExtToeOffset);

   Float64 extRealSwEdge;
   Float64 intRealSwEdge;
   if ( m_SidewalkPosition == swpBetweenBarriers )
   {
      // Sidewalk starts/ends at barriers' toes
      extRealSwEdge = extNomSwEdge - sign*extIntToeOffset;
      intRealSwEdge  = intNomSwEdge + sign*intExtToeOffset;
   }
   else
   {
      // move the exterior barrier so it is above the sidewalk
      CComQIPtr<IXYPosition> position(extShape);
      position->Offset(0, h1);

      // Sidewalk starts at the max of deck's edge and exterior toe of barrier
      // and ends at interior toe of interior barrier
      if ( orientation == tboLeft )
      {
         ext_bbox->get_Left(&extRealSwEdge);
         extRealSwEdge += extExtToeOffset;
         extRealSwEdge = max(0, extRealSwEdge);
      }
      else
      {
         ext_bbox->get_Right(&extRealSwEdge);
         extRealSwEdge -= extExtToeOffset;
         extRealSwEdge = min(0, extRealSwEdge);
      }

      Float64 intWid;
      int_bbox->get_Width(&intWid);
      intWid -= intIntToeOffset;

      intRealSwEdge = intNomSwEdge + sign*intWid;
   }

   // sidewalk coordinates
   Float64 x[4], y[4];
   x[0] = extRealSwEdge;
   y[0] = 0;

   x[1] = extRealSwEdge;
   y[1] = h1;

   x[2] = intRealSwEdge;
   y[2] = h2;

   x[3] = intRealSwEdge;
   y[3] = 0;

   // create the sidewalk shape
   m_SidewalkShape->AddPoint(x[0],y[0]);
   m_SidewalkShape->AddPoint(x[1],y[1]);
   m_SidewalkShape->AddPoint(x[2],y[2]);
   m_SidewalkShape->AddPoint(x[3],y[3]);

   // Move the interior barrier
   CComQIPtr<IXYPosition> position(intShape);

   LocatorPointType lp;
   lp = orientation == tboLeft ? lpBottomLeft : lpBottomRight;

   CComPtr<IPoint2d> point;
   position->get_LocatorPoint(lp,&point);

   Float64 locate_x;
   point->get_X(&locate_x);

   Float64 dx = intNomSwEdge-locate_x;
   Float64 dy;
   if ( m_SidewalkPosition == swpBetweenBarriers )
   {
      dy = 0;
   }
   else
   {
      dy = h2;
   }

   position->Offset(dx, dy);

   m_ExtBarrier = extBarrier;
   m_H1 = h1;
   m_H2 = h2;
   m_W  = swWidth;
   m_IntBarrier = intBarrier;
   m_Configuration = 3;

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_SidewalkWidth(Float64* width)
{
   CHECK_RETVAL(width);
   *width = m_W;
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

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_ExteriorCurbWidth(Float64* width)
{
   CHECK_RETVAL(width);

   // always have an exterior barrier
   CComPtr<IShape> ext_shape;
   m_ExtBarrier->get_Shape(&ext_shape);

   CComPtr<IRect2d> ext_bb;
   ext_shape->get_BoundingBox(&ext_bb);

   Float64 xextEdge;
   Float64 sign;
   if ( m_Orientation == tboLeft )
   {
      ext_bb->get_Right(&xextEdge);
      sign = 1;
   }
   else
   {
      ext_bb->get_Left(&xextEdge);
      sign = -1;
   }

   Float64 curb_loc;
   m_ExtBarrier->get_CurbLocation(&curb_loc);

   *width = sign*xextEdge - curb_loc;

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_CurbWidth(Float64* width)
{
   CHECK_RETVAL(width);

   // always have an exterior barrier
   CComPtr<IShape> ext_shape;
   m_ExtBarrier->get_Shape(&ext_shape);

   CComPtr<IRect2d> ext_bb;
   ext_shape->get_BoundingBox(&ext_bb);

   Float64 xextEdge;
   Float64 sign;
   if ( m_Orientation == tboLeft )
   {
      ext_bb->get_Right(&xextEdge);
      sign = 1;
   }
   else
   {
      ext_bb->get_Left(&xextEdge);
      sign = -1;
   }

   // width depends on configuration
   if (m_Configuration==1)
   {
      Float64 curb_loc;
      m_ExtBarrier->get_CurbLocation(&curb_loc);

      *width = sign*xextEdge - curb_loc;
   }
   else if (m_Configuration==2)
   {
      *width = sign*xextEdge + m_W;
   }
   else if (m_Configuration==3)
   {
      CComPtr<IShape> int_shape;
      m_IntBarrier->get_Shape(&int_shape);

      CComPtr<IRect2d> int_bb;
      int_shape->get_BoundingBox(&int_bb);

      Float64 int_width;
      int_bb->get_Width(&int_width);

      Float64 curb_loc;
      m_IntBarrier->get_CurbLocation(&curb_loc);

      *width = sign*xextEdge + m_W + int_width - curb_loc;
   }
   else
   {
      ATLASSERT(false); // this is bad
      *width = 0.0;
      return E_FAIL;
   }

   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::get_OverlayToeWidth(Float64* width)
{
   CHECK_RETVAL(width);

   // always have an exterior barrier
   CComPtr<IShape> ext_shape;
   m_ExtBarrier->get_Shape(&ext_shape);

   CComPtr<IRect2d> ext_bb;
   ext_shape->get_BoundingBox(&ext_bb);

   Float64 xextEdge;
   Float64 sign;
   if ( m_Orientation == tboLeft )
   {
      ext_bb->get_Right(&xextEdge);
      sign = 1;
   }
   else
   {
      ext_bb->get_Left(&xextEdge);
      sign = -1;
   }

   // width depends on configuration
   if (m_Configuration==1)
   {
      Float64 int_toe, ext_toe;
      m_ExtBarrier->get_BarrierToeLocations(&int_toe, &ext_toe);

      *width = sign*xextEdge - int_toe;
   }
   else if (m_Configuration==2)
   {
      // toe is edge of sw if no interior barrier
      *width = sign*xextEdge + m_W;
   }
   else if (m_Configuration==3)
   {
      CComPtr<IShape> int_shape;
      m_IntBarrier->get_Shape(&int_shape);

      CComPtr<IRect2d> int_bb;
      int_shape->get_BoundingBox(&int_bb);

      Float64 int_width;
      int_bb->get_Width(&int_width);

      Float64 int_toe, ext_toe;
      m_IntBarrier->get_BarrierToeLocations(&int_toe, &ext_toe);

      *width = sign*xextEdge + m_W + int_width - int_toe;
   }
   else
   {
      ATLASSERT(false); // this is bad
      *width = 0.0;
      return E_FAIL;
   }

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

STDMETHODIMP CSidewalkBarrier::put_IsInteriorStructurallyContinuous(VARIANT_BOOL bContinuous)
{
   m_bInteriorStructurallyContinuous = bContinuous;
   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::put_IsExteriorStructurallyContinuous(VARIANT_BOOL bContinuous)
{
   m_bExteriorStructurallyContinuous = bContinuous;
   return S_OK;
}

STDMETHODIMP CSidewalkBarrier::put_IsSidewalkStructurallyContinuous(VARIANT_BOOL bContinuous)
{
   m_bSidewalkStructurallyContinuous = bContinuous;
   return S_OK;
}


STDMETHODIMP CSidewalkBarrier::get_ExteriorBarrier(IBarrier** barr)
{
   CHECK_RETOBJ(barr);

   return m_ExtBarrier.CopyTo(barr);
}

STDMETHODIMP CSidewalkBarrier::get_InteriorBarrier(IBarrier** barr)
{
   CHECK_RETOBJ(barr);

   return m_IntBarrier.CopyTo(barr);
}

STDMETHODIMP CSidewalkBarrier::get_SidewalkPosition(SidewalkPositionType* posType)
{
   *posType = m_SidewalkPosition;
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
