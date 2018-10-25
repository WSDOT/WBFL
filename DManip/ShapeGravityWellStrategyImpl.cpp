///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2012  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// ShapeGravityWellStrategyImpl.cpp: implementation of the CShapeGravityWellStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "ShapeGravityWellStrategyImpl.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShapeGravityWellStrategyImpl::CShapeGravityWellStrategyImpl()
{
}

CShapeGravityWellStrategyImpl::~CShapeGravityWellStrategyImpl()
{
}

STDMETHODIMP_(void) CShapeGravityWellStrategyImpl::SetShape(IShape* pShape)
{
   m_Shape = pShape;

   m_CompositeShape.Release();
   m_Shape.QueryInterface(&m_CompositeShape);
}

STDMETHODIMP_(void) CShapeGravityWellStrategyImpl::GetShape(IShape** ppShape)
{
   (*ppShape) = m_Shape;
   if ( m_Shape )
      (*ppShape)->AddRef();
}

STDMETHODIMP_(void) CShapeGravityWellStrategyImpl::GetGravityWell(iDisplayObject* pDO,CRgn* pRgn)
{
   CComPtr<iDisplayList> dl;
   pDO->GetDisplayList(&dl);

   CComPtr<iDisplayMgr> dm;
   dl->GetDisplayMgr(&dm);

   CComPtr<iCoordinateMap> map;
   dm->GetCoordinateMap(&map);

   if ( m_CompositeShape )
   {
   }
   else
   {
      CComPtr<IPoint2dCollection> points;
      m_Shape->get_PolyPoints(&points);

      CollectionIndexType nPoints;
      points->get_Count(&nPoints);

      POINT* logical_points = new POINT[nPoints];

      CComPtr<IEnumPoint2d> enum_points;
      points->get__Enum(&enum_points);
      CComPtr<IPoint2d> point;
      CollectionIndexType i = 0;
      while( enum_points->Next(1,&point,NULL) != S_FALSE )
      {
         POINT p;
         Float64 x,y;
         map->MPtoWP(point,&x,&y);
         map->WPtoLP(x,y,&p.x,&p.y);

         logical_points[i++] = p;
         
         point.Release();
      }
      pRgn->CreatePolygonRgn(logical_points,(int)nPoints,ALTERNATE);

      delete [] logical_points;
   }
}
