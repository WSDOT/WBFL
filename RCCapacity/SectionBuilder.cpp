///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// SectionBuilder.cpp : Implementation of CSectionBuilder
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "SectionBuilder.h"
#include "GeneralSection.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HRESULT CSectionBuilder::FinalConstruct()
{
   return S_OK;
}

void CSectionBuilder::FinalRelease()
{
}


STDMETHODIMP CSectionBuilder::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGeneralSectionSlice,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CSectionBuilder
STDMETHODIMP CSectionBuilder::RectangularColumn(Float64 H,Float64 W,Float64 cover,long Nh,long Nw,Float64 As,IStressStrain* concrete,IStressStrain* rebar,IGeneralSection** section)
{
   CHECK_IN(concrete);
   CHECK_IN(rebar);
   CHECK_RETOBJ(section);

   CComObject<CGeneralSection>* pSection;
   CComObject<CGeneralSection>::CreateInstance(&pSection);


   // overall column shape
   CComPtr<IRectangle> column;
   column.CoCreateInstance(CLSID_Rect);
   column->put_Height(H);
   column->put_Width(W);
   CComQIPtr<IShape> column_shape(column);

   pSection->AddShape(CComBSTR("Column"),column_shape, concrete, nullptr, nullptr, 1.0, VARIANT_TRUE);


   // rebar
   Float64 radius = sqrt(As/M_PI);

   // do top and bottom rebars
   for (long i = 0; i < Nw; i++ )
   {
      CComPtr<ICircle> top_bar;
      top_bar.CoCreateInstance(CLSID_Circle);
      top_bar->put_Radius(radius);

      Float64 x = -W/2 + cover + i*(W-2*cover)/(Nw-1);
      Float64 y = H/2 - cover;
      CComPtr<IPoint2d> center;
      top_bar->get_Center(&center);
      center->Move(x,y);

      CComQIPtr<IShape> top_bar_shape(top_bar);
      pSection->AddShape(CComBSTR("Top Bar"),top_bar_shape, rebar, concrete, nullptr, 1.0, VARIANT_FALSE);

      CComPtr<ICircle> bottom_bar;
      bottom_bar.CoCreateInstance(CLSID_Circle);
      bottom_bar->put_Radius(radius);

      center.Release();
      bottom_bar->get_Center(&center);
      center->Move(x,-y);

      CComQIPtr<IShape> bottom_bar_shape(bottom_bar);
      pSection->AddShape(CComBSTR("Bottom Bar"),bottom_bar_shape, rebar, concrete, nullptr, 1.0, VARIANT_FALSE);
   }

   // do left and right bars
   for ( long i = 1; i < Nh - 1; i++ ) // skip first and last bar because they would Float64 up with top/bottom bars
   {
      CComPtr<ICircle> left_bar;
      left_bar.CoCreateInstance(CLSID_Circle);
      left_bar->put_Radius(radius);

      Float64 x = -W/2 + cover;
      Float64 y = H/2 - cover - i*(H-2*cover)/(Nh-1);
      CComPtr<IPoint2d> center;
      left_bar->get_Center(&center);
      center->Move(x,y);

      CComQIPtr<IShape> left_bar_shape(left_bar);
      pSection->AddShape(CComBSTR("Left Bar"),left_bar_shape, rebar, concrete, nullptr, 1.0, VARIANT_FALSE);

   
      CComPtr<ICircle> right_bar;
      right_bar.CoCreateInstance(CLSID_Circle);
      right_bar->put_Radius(radius);

      center.Release();
      right_bar->get_Center(&center);
      center->Move(-x,y);

      CComQIPtr<IShape> right_bar_shape(right_bar);
      pSection->AddShape(CComBSTR("Right Bar"),right_bar_shape, rebar, concrete, nullptr, 1.0, VARIANT_FALSE);
   }

   (*section) = pSection;
   (*section)->AddRef();

   return S_OK;
}
   
STDMETHODIMP CSectionBuilder::CircularColumn(Float64 D,Float64 cover,long Nb,Float64 As,IStressStrain* concrete,IStressStrain* rebar,IGeneralSection** section)
{
   CHECK_IN(concrete);
   CHECK_IN(rebar);
   CHECK_RETOBJ(section);

   CComObject<CGeneralSection>* pSection;
   CComObject<CGeneralSection>::CreateInstance(&pSection);


   // overall column shape
   CComPtr<ICircle> column;
   column.CoCreateInstance(CLSID_Circle);
   column->put_Radius(D/2);
   CComQIPtr<IShape> column_shape(column);

   pSection->AddShape(CComBSTR("Column"),column_shape, concrete, nullptr, nullptr, 1.0, VARIANT_TRUE);

   CComPtr<IPoint2d> center;
   column->get_Center(&center);


   // rebar of bar
   Float64 radius = sqrt(As/M_PI);

   // create a utility class that can layout the rebar points
   CComPtr<IGeomUtil> gu;
   gu.CoCreateInstance(CLSID_GeomUtil);
   CComQIPtr<IGeomUtil2d> geom_util(gu);

   // generate the rebar points
   CComPtr<IPoint2dCollection> points;
   geom_util->GenerateCircle(Nb,center,D/2-cover,0.00,&points);

   IndexType nPoints;
   points->get_Count(&nPoints);
   ATLASSERT(nPoints == Nb);

   // loop through the points, create new rebars, and add them to the section
   CComPtr<IEnumPoint2d> enum_points;
   points->get__Enum(&enum_points);
   CComPtr<IPoint2d> point;
   while ( enum_points->Next(1,&point,nullptr) != S_FALSE )
   {
      CComPtr<ICircle> bar;
      bar.CoCreateInstance(CLSID_Circle);

      bar->put_Radius(radius);

      CComPtr<IPoint2d> c;
      bar->get_Center(&c);
      c->MoveEx(point);

      CComQIPtr<IShape> bar_shape(bar);

      pSection->AddShape(CComBSTR("Bar"),bar_shape, rebar, concrete, nullptr, 1.0, VARIANT_FALSE);

      point.Release();
   }

   (*section) = pSection;
   (*section)->AddRef();

   return S_OK;
}

