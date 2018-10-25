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

// RebarRowPattern.cpp : Implementation of CRebarRowPattern
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "RebarRowPattern.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRebarRowPattern
HRESULT CRebarRowPattern::FinalConstruct()
{
   return S_OK;
}

void CRebarRowPattern::FinalRelease()
{
}

STDMETHODIMP CRebarRowPattern::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
  	  &IID_IRebarRowPattern,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//////////////////////////////////////////////////////////////////
// IRebarPattern
STDMETHODIMP CRebarRowPattern::putref_Rebar(IRebar* rebar)
{
   CHECK_IN(rebar);
   CComQIPtr<IMaterial> material(rebar);
   if ( material == NULL )
   {
      ATLASSERT(false); // must implement the IMaterial interface
      return E_INVALIDARG;
   }

   m_Rebar = rebar;
   return S_OK;
}

STDMETHODIMP CRebarRowPattern::get_Rebar(IRebar** rebar)
{
   CHECK_RETOBJ(rebar);
   (*rebar) = m_Rebar;

   if ( m_Rebar )
      (*rebar)->AddRef();

   return S_OK;
}

STDMETHODIMP CRebarRowPattern::putref_RebarLayoutItem(IRebarLayoutItem* rebarLayoutItem)
{
   CHECK_IN(rebarLayoutItem);
   m_pRebarLayoutItem = rebarLayoutItem;
   return S_OK;
}

STDMETHODIMP CRebarRowPattern::put_Hook(/*[in]*/DirectionType side,/*[in]*/HookType hook)
{
   m_HookType[side] = hook;
   return S_OK;
}

STDMETHODIMP CRebarRowPattern::get_Hook(/*[in]*/DirectionType side,/*[out,retval]*/HookType* hook)
{
   CHECK_RETVAL(hook);
   *hook = m_HookType[side];
   return S_OK;
}

STDMETHODIMP CRebarRowPattern::get_Count(CollectionIndexType* count)
{
   CHECK_RETVAL(count);
   *count = m_Count;
   return S_OK;
}

STDMETHODIMP CRebarRowPattern::put_Count(RowIndexType count)
{
   m_Count = count;
   return S_OK;
}

STDMETHODIMP CRebarRowPattern::get_Location(Float64 distFromStartOfPattern,CollectionIndexType barIdx,IPoint2d** location)
{
   CHECK_RETOBJ(location);
   if ( barIdx < 0 || (CollectionIndexType)m_Count < barIdx )
      return E_INVALIDARG;


   Float64 row_length = (m_Count-1)*m_Spacing;

   Float64 layout_length;
   m_pRebarLayoutItem->get_Length(&layout_length);

   Float64 sax,say;
   m_AnchorPoint[etStart]->get_X(&sax);
   m_AnchorPoint[etStart]->get_Y(&say);

   Float64 eax,eay;
   m_AnchorPoint[etEnd]->get_X(&eax);
   m_AnchorPoint[etEnd]->get_Y(&eay);

   Float64 ax = ::LinInterp(distFromStartOfPattern,sax,eax,layout_length);
   Float64 ay = ::LinInterp(distFromStartOfPattern,say,eay,layout_length);

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

STDMETHODIMP CRebarRowPattern::get_Profile(/*[in]*/IndexType barIdx,/*[out,retval]*/IPoint2dCollection** ppProfile)
{
   CHECK_RETOBJ(ppProfile);
   CComPtr<IPoint2dCollection> points;
   points.CoCreateInstance(CLSID_Point2dCollection);

   Float64 Xstart, Xend;
   m_pRebarLayoutItem->get_Start(&Xstart);
   Float64 L;
   m_pRebarLayoutItem->get_Length(&L);
   Xend = Xstart + L;

   Float64 Ystart, Yend;
   m_AnchorPoint[etStart]->get_Y(&Ystart);
   m_AnchorPoint[etEnd]->get_Y(&Yend);

   CComPtr<IPoint2d> pntStart;
   CComPtr<IPoint2d> pntEnd;

   pntStart.CoCreateInstance(CLSID_Point2d);
   pntEnd.CoCreateInstance(CLSID_Point2d);

   pntStart->Move(Xstart,Ystart);
   pntEnd->Move(Xend,Yend);

   points->Add(pntStart);
   points->Add(pntEnd);

   points.CopyTo(ppProfile);
   return S_OK;
}

//////////////////////////////////////////////////////
// IRebarRowPattern
STDMETHODIMP CRebarRowPattern::put_AnchorPoint(EndType endType,IPoint2d* anchorPt)
{
   CHECK_IN(anchorPt);
   m_AnchorPoint[endType] = anchorPt;
   return S_OK;
}

STDMETHODIMP CRebarRowPattern::get_AnchorPoint(EndType endType,IPoint2d** anchorPt)
{
   CHECK_RETOBJ(anchorPt);
   (*anchorPt) = m_AnchorPoint[endType];
   (*anchorPt)->AddRef();
   return S_OK;
}

STDMETHODIMP CRebarRowPattern::put_Spacing(Float64 spacing)
{
   m_Spacing = spacing;
   return S_OK;
}

STDMETHODIMP CRebarRowPattern::get_Spacing(Float64* spacing)
{
   CHECK_RETVAL(spacing);
   *spacing = m_Spacing;
   return S_OK;
}

STDMETHODIMP CRebarRowPattern::put_Orientation(RebarRowOrientation orientation)
{
   m_Orientation = orientation;
   return S_OK;
}

STDMETHODIMP CRebarRowPattern::get_Orientation(RebarRowOrientation* orientation)
{
   CHECK_RETVAL(orientation);
   *orientation = m_Orientation;
   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CRebarRowPattern::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("RebarRowPattern"));

   load->get_Property(CComBSTR("Rebar"),&var);
    _CopyVariantToInterface<IRebar>::copy(&m_Rebar,&var);

   load->get_Property(CComBSTR("StartAnchorPoint"),&var);
    _CopyVariantToInterface<IPoint2d>::copy(&m_AnchorPoint[etStart],&var);

   load->get_Property(CComBSTR("EndAnchorPoint"),&var);
    _CopyVariantToInterface<IPoint2d>::copy(&m_AnchorPoint[etEnd],&var);

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

STDMETHODIMP CRebarRowPattern::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("RebarRowPattern"),1.0);
   save->put_Property(CComBSTR("Rebar"),CComVariant(m_Rebar));
   save->put_Property(CComBSTR("StartAnchorPoint"),CComVariant(m_AnchorPoint[etStart]));
   save->put_Property(CComBSTR("EndAnchorPoint"),CComVariant(m_AnchorPoint[etEnd]));
   save->put_Property(CComBSTR("Count"),CComVariant(m_Count));
   save->put_Property(CComBSTR("Spacing"),CComVariant(m_Spacing));
   save->put_Property(CComBSTR("Orientation"),CComVariant(m_Orientation));
   save->EndUnit();

   return S_OK;
}
