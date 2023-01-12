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

// CapacityReductionFactor.cpp : Implementation of CCapacityReductionFactor
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "CapacityReductionFactor.h"
#include <WBFLTools.h>
#include <WBFLGeometry.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCapacityReductionFactor

STDMETHODIMP CCapacityReductionFactor::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICapacityReductionFactor,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CCapacityReductionFactor::FinalConstruct()
{
   return S_OK;
}

void CCapacityReductionFactor::FinalRelease()
{
}

STDMETHODIMP CCapacityReductionFactor::Compute(IGeneralSection* section,CollectionIndexType nConcShapes,ILine2d* neutralAxis,Float64 ppr,Float64* c,Float64* dt,Float64* phi)
{
   CHECK_IN(section);

   // pull all of the shapes out of the section and put into concrete and reinforcement arrays
   // the concrete shapes must be in the first nConcShapes of the section
   CComPtr<IUnkArray> arrConcrete, arrReinf;
   arrConcrete.CoCreateInstance(CLSID_UnkArray);
   arrReinf.CoCreateInstance(CLSID_UnkArray);

   CollectionIndexType nShapes;
   section->get_ShapeCount(&nShapes);

   for ( CollectionIndexType i = 0; i < nShapes; i++ )
   {
      CComPtr<IShape> shape;
      section->get_Shape(i,&shape);

      CComPtr<IUnknown> punk;
      shape.QueryInterface(&punk);

      if ( i < nConcShapes )
         arrConcrete->Add(punk);
      else
         arrReinf->Add(punk);
   }

   return ComputeEx(arrConcrete,arrReinf,neutralAxis,ppr,c,dt,phi);
}

STDMETHODIMP CCapacityReductionFactor::ComputeEx(IUnkArray* pConcShapes,IUnkArray* pReinfShapes,ILine2d* neutralAxis,Float64 ppr,Float64* c,Float64* dt,Float64* phi)
{
   CHECK_IN(pConcShapes);
   CHECK_IN(pReinfShapes);
   CHECK_IN(neutralAxis);

   CHECK_RETVAL(c);
   CHECK_RETVAL(dt);
   CHECK_RETVAL(phi);

   HRESULT hr = ComputeC(pConcShapes,neutralAxis,c);
   if ( FAILED(hr) )
      return hr;

   hr = ComputeDt(pReinfShapes,neutralAxis,c,dt);
   if ( FAILED(hr) )
      return hr;

   Float64 k = 0.15*((*dt)/(*c) - 1);
   *phi = 0.65 + k + ppr*(k - 0.067);

   if ( (*phi) < 0.75 )
      *phi = 0.75;

   Float64 phi_max = 0.9 + 0.1*ppr;
   if ( phi_max < (*phi) )
      *phi = phi_max;

   return S_OK;
}

HRESULT CCapacityReductionFactor::ComputeC(IUnkArray* pConcShapes,ILine2d* neutralAxis,Float64* c)
{
   CComPtr<IGeomUtil2d> geom_util;
   geom_util.CoCreateInstance(CLSID_GeomUtil);

   // create a line that is in the opposite direction as the neutral axis line
   // we need this because IShape::FurthestDistance determines the furthest distance for the
   // right side of the line and the "compression" side of the neutral axis is the left side
   CComPtr<ILine2d> line;
   geom_util->CreateParallelLine(neutralAxis,0.00,&line);
   line->Reverse();

   Float64 max_distance = -999999;

   CollectionIndexType nShapes;
   pConcShapes->get_Count(&nShapes);
   for ( CollectionIndexType i = 0; i < nShapes; i++ )
   {
      CComPtr<IUnknown> punk;
      pConcShapes->get_Item(i,&punk);

      CComQIPtr<IShape> shape(punk);
      if ( shape == nullptr )
         return E_FAIL;

      Float64 d;
      shape->FurthestDistance(line,&d);

      max_distance = Max(max_distance,d);
   }

   if ( max_distance < 0 )
      max_distance = 0.001;

   *c = max_distance;

   return S_OK;
}

HRESULT CCapacityReductionFactor::ComputeDt(IUnkArray* pReinfShapes,ILine2d* neutralAxis,Float64* c,Float64* dt)
{
   CComPtr<IGeomUtil2d> geom_util;
   geom_util.CoCreateInstance(CLSID_GeomUtil);

   Float64 max_distance = -99999;

   CollectionIndexType nShapes;
   pReinfShapes->get_Count(&nShapes);
   for ( CollectionIndexType i = 0; i < nShapes; i++ )
   {
      CComPtr<IUnknown> punk;
      pReinfShapes->get_Item(i,&punk);

      CComQIPtr<IShape> shape(punk);
      if ( shape == nullptr )
         return E_FAIL;

      CComPtr<IShapeProperties> props;
      shape->get_ShapeProperties(&props);

      CComPtr<IPoint2d> cg;
      props->get_Centroid(&cg);

      Float64 d;
      geom_util->ShortestOffsetToPoint(neutralAxis,cg,&d);

      // d > 0 ==> reinforcement is on tension side of the neutral axis
      // d < 0 ==> reinforcement is on compression side of the neutral axis

      // get max distance because we want the tension side
      max_distance = Max(max_distance,d);
   }

   *dt = max_distance; // this is the max distance from the neutral axis

   (*dt) += (*c); // add the "c" distance
   return S_OK;
}
