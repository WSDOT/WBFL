///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2025  Washington State Department of Transportation
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

// CrossBeamRebarPattern.cpp : Implementation of CCrossBeamRebarPattern
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "CrossBeamRebarPattern.h"
#include <LRFD\LRFD.h>
#include <Math\Math.h>
#include <MathEx.h>


/////////////////////////////////////////////////////////////////////////////
// CCrossBeamRebarPattern
HRESULT CCrossBeamRebarPattern::FinalConstruct()
{
   m_Count = 0;
   m_Spacing = 0;
   m_Cover = 0;
   m_Datum = xbBottom;

   m_HookType[qcbLeft]  = htNone;
   m_HookType[qcbRight] = htNone;

   m_pCrossBeam = nullptr;
   m_pRebarLayoutItem = nullptr;

   return S_OK;
}

void CCrossBeamRebarPattern::FinalRelease()
{
}

STDMETHODIMP CCrossBeamRebarPattern::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
  	  &IID_ICrossBeamRebarPattern,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
      {
			return S_OK;
      }
	}
	return S_FALSE;
}

//////////////////////////////////////////////////////////////////
// IRebarPattern
STDMETHODIMP CCrossBeamRebarPattern::putref_Rebar(IRebar* rebar)
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

STDMETHODIMP CCrossBeamRebarPattern::get_Rebar(IRebar** rebar)
{
   CHECK_RETOBJ(rebar);
   (*rebar) = m_Rebar;

   if ( m_Rebar )
   {
      (*rebar)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::putref_RebarLayoutItem(IRebarLayoutItem* rebarLayoutItem)
{
   CHECK_IN(rebarLayoutItem);
   m_pRebarLayoutItem = rebarLayoutItem;
   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::put_Hook(/*[in]*/DirectionType side,/*[in]*/HookType hook)
{
   m_HookType[side] = hook;
   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::get_Hook(/*[in]*/DirectionType side,/*[out,retval]*/HookType* hook)
{
   CHECK_RETVAL(hook);
   *hook = m_HookType[side];
   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::get_Count(IndexType* count)
{
   CHECK_RETVAL(count);
   *count = m_Count;
   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::put_Count(RowIndexType count)
{
   m_Count = count;
   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::get_Location(Float64 Xxb,IndexType barIdx,IPoint2d** location)
{
   CHECK_RETOBJ(location);
   if ( barIdx < 0 || (IndexType)m_Count < barIdx )
   {
      return E_INVALIDARG;
   }

   CComPtr<IPoint2dCollection> profile;
   get_Profile(barIdx,&profile);

   WBFL::Math::PiecewiseFunction fn;
   CComPtr<IEnumPoint2d> enumPoints;
   profile->get__Enum(&enumPoints);
   CComPtr<IPoint2d> point;
   while ( enumPoints->Next(1,&point,nullptr) != S_FALSE )
   {
      Float64 x,y;
      point->Location(&x,&y);
      fn.AddPoint(x,y);
      point.Release();
   }

   Float64 y = fn.Evaluate(Xxb);

   Float64 row_width = (m_Count-1)*m_Spacing;
   Float64 x = barIdx*m_Spacing - row_width/2;

   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance(CLSID_Point2d);
   pnt->Move(x,y);

   pnt.CopyTo(location);

   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::get_Profile(/*[in]*/IndexType barIdx,/*[out,retval]*/IPoint2dCollection** ppProfile)
{
   CHECK_RETOBJ(ppProfile);

   Float64 db;
   m_Rebar->get_NominalDiameter(&db);

   Float64 offset; // offset from surface profile
   if ( m_Datum == xbTop )
   {
      offset = -(m_Cover + db/2);
   }
   else if ( m_Datum == xbTopLowerXBeam )
   {
      offset = -(m_Cover + db/2);
   }
   else
   {
      offset = m_Cover + db/2;
   }

   CComPtr<IPoint2dCollection> profile;
   m_pCrossBeam->get_Surface(m_Datum, offset, &profile);

   // The surface profile is in Pier coordinates
   // Need to convert it to Cross Beam Coordinates
   CComPtr<IPier> pier;
   m_pCrossBeam->get_Pier(&pier);
   Float64 Xp;
   pier->ConvertCrossBeamToPierCoordinate(0,&Xp);
   // 0 in Cross Beam coordinates is Xp in Pier coordinates
   // so 0 in Pier coordinates is -Xp in Cross Beam coordinates
   // Add -Xp to the X-value all the profile points
   //profile->Offset(-Xp, offset);
   profile->Offset(-Xp, 0.0);

   Float64 XxbStart, L;
   m_pRebarLayoutItem->get_Start(&XxbStart); // Cross Beam Coordinates
   m_pRebarLayoutItem->get_Length(&L);
   Float64 XxbEnd = XxbStart + L; // Cross Beam coordinates

   CComPtr<IPoint2dCollection> points;
   points.CoCreateInstance(CLSID_Point2dCollection);

   IndexType nPoints;
   profile->get_Count(&nPoints);
   CComPtr<IPoint2d> prevPoint;
   profile->get_Item(0,&prevPoint);
   Float64 Xprev,Yprev;
   prevPoint->Location(&Xprev,&Yprev);
   if ( ::InRange(XxbStart,Xprev,XxbEnd) )
   {
      points->Add(prevPoint);
   }

   for ( IndexType pntIdx = 1; pntIdx < nPoints; pntIdx++ )
   {
      CComPtr<IPoint2d> point;
      profile->get_Item(pntIdx,&point);
      Float64 X,Y;
      point->Location(&X,&Y);

      if ( Xprev < XxbStart && XxbStart < X )
      {
         // the previous point and the current point straddle
         // the start of the bar. get the Y value for the bar
         // at the start point. add this point
         Float64 y = ::LinInterp(XxbStart-Xprev,Yprev,Y,X-Xprev);
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance(CLSID_Point2d);
         pnt->Move(XxbStart,y);
         points->Add(pnt);
      }

      if ( Xprev < XxbEnd && XxbEnd < X )
      {
         // the previous point and the current point straddle
         // the end of the bar. get the Y value for the bar
         // at the end point. add this point
         Float64 y = ::LinInterp(XxbEnd-Xprev,Yprev,Y,X-Xprev);
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance(CLSID_Point2d);
         pnt->Move(XxbEnd,y);
         points->Add(pnt);
      }

      if ( ::InRange(XxbStart,X,XxbEnd) )
      {
         points->Add(point);
      }

      prevPoint = point;
      Xprev = X;
      Yprev = Y;
   }

   // points is in Cross Beam coordinates
   // convert it to rebar layout coordinates
   points->Offset(-XxbStart,0);

   points->RemoveDuplicatePoints();

   points.CopyTo(ppProfile);
   return S_OK;
}

//////////////////////////////////////////////////////
// ICrossBeamRebarPattern
STDMETHODIMP CCrossBeamRebarPattern::putref_CrossBeam(/*[in]*/ICrossBeam* pXBeam)
{
   CHECK_IN(pXBeam);
   m_pCrossBeam = pXBeam;
   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::get_CrossBeam(/*[out,retval]*/ICrossBeam** ppXBeam)
{
   CHECK_RETOBJ(ppXBeam);
   if ( m_pCrossBeam )
   {
      (*ppXBeam) = m_pCrossBeam;
      (*ppXBeam)->AddRef();
   }
   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::put_Datum(/*[in]*/CrossBeamRebarDatum datum)
{
   m_Datum = datum;
   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::get_Datum(/*[out,retval]*/CrossBeamRebarDatum* pDatum)
{
   CHECK_RETVAL(pDatum);
   *pDatum = m_Datum;
   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::put_Cover(/*[in]*/Float64 cover)
{
   m_Cover = cover;
   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::get_Cover(/*[out,retval]*/Float64* pCover)
{
   CHECK_RETVAL(pCover);
   *pCover = m_Cover;
   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::put_Spacing(Float64 spacing)
{
   m_Spacing = spacing;
   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::get_Spacing(Float64* spacing)
{
   CHECK_RETVAL(spacing);
   *spacing = m_Spacing;
   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::get_DisplayProfile(/*[in]*/IndexType barIdx,/*[out,retval]*/IPoint2dCollection** ppProfile)
{
   HRESULT hr = get_Profile(barIdx,ppProfile);
   if ( FAILED(hr) )
   {
      return hr;
   }

   USES_CONVERSION;

   // Add Hooks

   // hooks are represented by straigh lines... in a future
   // implementation we will make the hooks curved as they really are.
   CComPtr<ICogoEngine> cogoEngine;
   cogoEngine.CoCreateInstance(CLSID_CogoEngine);
   CComQIPtr<ILocate2> locate(cogoEngine);

   CComPtr<IRebar> rebar;
   get_Rebar(&rebar);
   CComBSTR bstrSize;
   rebar->get_Name(&bstrSize);
   WBFL::Materials::Rebar::Size size = WBFL::LRFD::RebarPool::GetBarSize(OLE2CT(bstrSize));
   Float64 db;
   rebar->get_NominalDiameter(&db);

   if ( m_HookType[qcbLeft] != htNone )
   {
      CComPtr<IPoint2d> pnt1, pnt2;
      (*ppProfile)->get_Item(0,&pnt1);
      (*ppProfile)->get_Item(1,&pnt2);

      ATLASSERT(pnt1->SameLocation(pnt2) == S_FALSE);

      Float64 angle = (m_HookType[qcbLeft] == ht90 ? PI_OVER_2 : (m_HookType[qcbLeft] == ht180 ? M_PI : ToRadians(135)));
      //if ( IsEqual(angle,M_PI) )
      if ( m_HookType[qcbLeft] == ht180)
      {
         // 180 degree hooks will loop back on themselves to reduce
         // the angle a little bit so there is something to display
         angle -= WBFL::Units::ConvertToSysUnits(15,WBFL::Units::Measure::Degree);
      }
      else if (m_HookType[qcbLeft] == ht90)
      {
         angle += WBFL::Units::ConvertToSysUnits(15, WBFL::Units::Measure::Degree);
      }

      if ( m_Datum == xbBottom )
      {
         angle *= -1;
      }

      Float64 hookExtension = WBFL::LRFD::Rebar::GetHookExtension(size,db, WBFL::LRFD::Rebar::Usage::Longitudinal,(WBFL::LRFD::Rebar::Hook)m_HookType[qcbLeft]);
   
      CComPtr<IPoint2d> pnt;
      locate->ByDistDefAngle(pnt2,pnt1,hookExtension,CComVariant(angle),0.0,&pnt);

      (*ppProfile)->Insert(0,pnt);
   }

   if ( m_HookType[qcbRight] != htNone )
   {
      IndexType nPoints;
      (*ppProfile)->get_Count(&nPoints);
      CComPtr<IPoint2d> pnt1, pnt2;
      (*ppProfile)->get_Item(nPoints-1,&pnt1);
      (*ppProfile)->get_Item(nPoints-2,&pnt2);
   
      ATLASSERT(pnt1->SameLocation(pnt2) == S_FALSE);

      Float64 angle = (m_HookType[qcbRight] == ht90 ? PI_OVER_2 : (m_HookType[qcbRight] == ht180 ? M_PI : ToRadians(135)));
//      if ( IsEqual(angle,M_PI) )
      if ( m_HookType[qcbLeft] == ht180)
      {
         // 180 degree hooks will loop back on themselves to reduce
         // the angle a little bit so there is something to display
         angle -= WBFL::Units::ConvertToSysUnits(15,WBFL::Units::Measure::Degree);
      }
      else if (m_HookType[qcbRight] == ht90)
      {
         angle += WBFL::Units::ConvertToSysUnits(15, WBFL::Units::Measure::Degree);
      }

      if ( m_Datum != xbBottom )
      {
         angle *= -1;
      }

      Float64 hookExtension = WBFL::LRFD::Rebar::GetHookExtension(size,db, WBFL::LRFD::Rebar::Usage::Longitudinal,(WBFL::LRFD::Rebar::Hook)m_HookType[qcbRight]);

      CComPtr<IPoint2d> pnt;
      locate->ByDistDefAngle(pnt2,pnt1,hookExtension,CComVariant(angle),0.0,&pnt);

      (*ppProfile)->Add(pnt);
   }

   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CCrossBeamRebarPattern::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("CrossBeamRebarPattern"));

   //load->get_Property(CComBSTR("Rebar"),&var);
   // _CopyVariantToInterface<IRebar>::copy(&m_Rebar,&var);

   //load->get_Property(CComBSTR("StartAnchorPoint"),&var);
   // _CopyVariantToInterface<IPoint2d>::copy(&m_AnchorPoint[etStart],&var);

   //load->get_Property(CComBSTR("EndAnchorPoint"),&var);
   // _CopyVariantToInterface<IPoint2d>::copy(&m_AnchorPoint[etEnd],&var);

   // load->get_Property(CComBSTR("Count"),&var);
   // m_Count = var.iVal;

   // load->get_Property(CComBSTR("Spacing"),&var);
   // m_Spacing = var.dblVal;

   // load->get_Property(CComBSTR("Orientation"),&var);
   // m_Orientation = (RebarRowOrientation)(var.lVal);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CCrossBeamRebarPattern::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("CrossBeamRebarPattern"),1.0);
   //save->put_Property(CComBSTR("Rebar"),CComVariant(m_Rebar));
   //save->put_Property(CComBSTR("StartAnchorPoint"),CComVariant(m_AnchorPoint[etStart]));
   //save->put_Property(CComBSTR("EndAnchorPoint"),CComVariant(m_AnchorPoint[etEnd]));
   //save->put_Property(CComBSTR("Count"),CComVariant(m_Count));
   //save->put_Property(CComBSTR("Spacing"),CComVariant(m_Spacing));
   //save->put_Property(CComBSTR("Orientation"),CComVariant(m_Orientation));
   save->EndUnit();

   return S_OK;
}
