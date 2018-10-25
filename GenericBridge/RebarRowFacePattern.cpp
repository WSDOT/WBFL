///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
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

// RebarRowFacePattern.cpp : Implementation of CRebarRowFacePattern
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "RebarRowFacePattern.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRebarRowFacePattern
HRESULT CRebarRowFacePattern::FinalConstruct()
{
   return S_OK;
}

void CRebarRowFacePattern::FinalRelease()
{
}

STDMETHODIMP CRebarRowFacePattern::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
  	  &IID_IRebarRowFacePattern,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//////////////////////////////////////////////////////////////////
// IRebarPattern
STDMETHODIMP CRebarRowFacePattern::putref_Rebar(IRebar* rebar)
{
   CHECK_IN(rebar);
   CComQIPtr<IMaterial> material(rebar);
   if ( material == nullptr )
   {
      ATLASSERT(false); // must implement the IMaterial interface
      return E_INVALIDARG;
   }

   m_Rebar = rebar;
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::get_Rebar(IRebar** rebar)
{
   CHECK_RETOBJ(rebar);
   (*rebar) = m_Rebar;

   if ( m_Rebar )
      (*rebar)->AddRef();

   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::putref_RebarLayoutItem(IRebarLayoutItem* rebarLayoutItem)
{
   CHECK_IN(rebarLayoutItem);
   m_pRebarLayoutItem = rebarLayoutItem;
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::put_Hook(/*[in]*/DirectionType side,/*[in]*/HookType hook)
{
   m_HookType[side] = hook;
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::get_Hook(/*[in]*/DirectionType side,/*[out,retval]*/HookType* hook)
{
   CHECK_RETVAL(hook);
   *hook = m_HookType[side];
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::get_Count(CollectionIndexType* count)
{
   CHECK_RETVAL(count);
   *count = m_Count;
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::put_Count(RowIndexType count)
{
   m_Count = count;
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::get_Location(Float64 distFromStartOfPattern,CollectionIndexType barIdx,IPoint2d** location)
{
   CHECK_RETOBJ(location);
   if ( barIdx < 0 || (CollectionIndexType)m_Count < barIdx )
      return E_INVALIDARG;


   Float64 row_length = (m_Count-1)*m_Spacing;

   Float64 layout_length;
   m_pRebarLayoutItem->get_Length(&layout_length);

   Float64 start;
   m_pRebarLayoutItem->get_Start(&start);

   Float64 ax = 0;
   Float64 ay;
   if ( m_Face == ftTopFace )
   {
      ay = -m_Offset;
   }
   else
   {
      CComPtr<IShape> shape;
      m_pSegment->get_PrimaryShape(start + distFromStartOfPattern,&shape);
      CComPtr<IRect2d> box;
      shape->get_BoundingBox(&box);
      Float64 h;
      box->get_Height(&h);
      ay = -h + m_Offset;
   }


   Float64 x,y;
   switch (m_Orientation)
   {
   case rroLeft:
      x = ax + barIdx*m_Spacing;
      y = ay;
      break;

   case rroHCenter:
      x = ax - row_length/2 + barIdx*m_Spacing;
      y = ay;
      break;

   case rroRight:
      x = ax - barIdx*m_Spacing;
      y = ay;
      break;

   case rroUp:
      x = ax;
      y = ay + barIdx*m_Spacing;
      break;

   case rroVCenter:
      x = ax;
      y = ay - row_length/2 + barIdx*m_Spacing;
      break;
      
   case rroDown:
      x = ax;
      y = ay - barIdx*m_Spacing;
      break;

   default:
      ATLASSERT(false);
   }

   CComPtr<IPoint2d> point;
   point.CoCreateInstance(CLSID_Point2d);
   point->Move(x,y);

   (*location) = point;
   (*location)->AddRef();

   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::get_Profile(/*[in]*/IndexType barIdx,/*[out,retval]*/IPoint2dCollection** ppProfile)
{
   CHECK_RETOBJ(ppProfile);
   CComPtr<IPoint2dCollection> points;
   points.CoCreateInstance(CLSID_Point2dCollection);

   Float64 Xstart;
   m_pRebarLayoutItem->get_Start(&Xstart);

   Float64 L;
   m_pRebarLayoutItem->get_Length(&L);

   int nPoints = 20;
   for ( int i = 0; i <= nPoints; i++ )
   {
      Float64 distFromStartOfPattern = i*L/nPoints;
      CComPtr<IPoint2d> point;
      get_Location(distFromStartOfPattern,0,&point);

      Float64 X = Xstart + distFromStartOfPattern;
      point->put_X(X);
      points->Add(point);
   }

   points.CopyTo(ppProfile);
   return S_OK;
}

//////////////////////////////////////////////////////
// IRebarRowFacePattern
STDMETHODIMP CRebarRowFacePattern::putref_Segment(ISegment* pSegment)
{
   m_pSegment = pSegment;
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::get_Segment(ISegment** pSegment)
{
   CHECK_RETOBJ(pSegment);
   *pSegment = m_pSegment;
   if ( *pSegment )
   {
      (*pSegment)->AddRef();
   }
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::put_Face(FaceType faceType)
{
   m_Face = faceType;
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::get_Face(FaceType* faceType)
{
   CHECK_RETVAL(faceType);
   *faceType = m_Face;
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::put_Offset(Float64 offset)
{
   m_Offset = offset;
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::get_Offset(Float64* offset)
{
   CHECK_RETVAL(offset);
   *offset = m_Offset;
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::put_Spacing(Float64 spacing)
{
   m_Spacing = spacing;
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::get_Spacing(Float64* spacing)
{
   CHECK_RETVAL(spacing);
   *spacing = m_Spacing;
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::put_Orientation(RebarRowOrientation orientation)
{
   m_Orientation = orientation;
   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::get_Orientation(RebarRowOrientation* orientation)
{
   CHECK_RETVAL(orientation);
   *orientation = m_Orientation;
   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CRebarRowFacePattern::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("RebarRowFacePattern"));

   load->get_Property(CComBSTR("Rebar"),&var);
    _CopyVariantToInterface<IRebar>::copy(&m_Rebar,&var);

   //load->get_Property(CComBSTR("StartAnchorPoint"),&var);
   // _CopyVariantToInterface<IPoint2d>::copy(&m_AnchorPoint[etStart],&var);

   //load->get_Property(CComBSTR("EndAnchorPoint"),&var);
   // _CopyVariantToInterface<IPoint2d>::copy(&m_AnchorPoint[etEnd],&var);

    load->get_Property(CComBSTR("Count"),&var);
    m_Count = var.iVal;

    load->get_Property(CComBSTR("Spacing"),&var);
    m_Spacing = var.dblVal;

    load->get_Property(CComBSTR("Orientation"),&var);
    m_Orientation = (RebarRowOrientation)(var.lVal);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CRebarRowFacePattern::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("RebarRowFacePattern"),1.0);
   save->put_Property(CComBSTR("Rebar"),CComVariant(m_Rebar));
   //save->put_Property(CComBSTR("StartAnchorPoint"),CComVariant(m_AnchorPoint[etStart]));
   //save->put_Property(CComBSTR("EndAnchorPoint"),CComVariant(m_AnchorPoint[etEnd]));
   save->put_Property(CComBSTR("Count"),CComVariant(m_Count));
   save->put_Property(CComBSTR("Spacing"),CComVariant(m_Spacing));
   save->put_Property(CComBSTR("Orientation"),CComVariant(m_Orientation));
   save->EndUnit();

   return S_OK;
}
