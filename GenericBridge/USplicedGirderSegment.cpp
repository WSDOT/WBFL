///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// USplicedGirderSegment.cpp : Implementation of CUSplicedGirderSegment
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "USplicedGirderSegment.h"
#include <MathEx.h>
#include <algorithm>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUSplicedGirderSegment
HRESULT CUSplicedGirderSegment::FinalConstruct()
{
   return S_OK;
}

void CUSplicedGirderSegment::FinalRelease()
{
}

////////////////////////////////////////////////////////////////////
// ISplicedGirderSegment implementation

HRESULT CUSplicedGirderSegment::GetPrimaryShape(Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem, IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   if (m_Shapes.size() == 0 )
   {
      *ppShape = 0;
      return S_OK;
   }

   CComQIPtr<IUGirderSection> UGirderSection(m_Shapes.front().Shape);
   ATLASSERT(UGirderSection); // if this is nullptr... how did it get in the system????

   // This object represents a prismatic shape... all sections are the same, no need to adjust dimensions based on Xs

#if defined _DEBUG
   CComPtr<IUBeam> pcBeam;
   UGirderSection->get_Beam(&pcBeam);
   Float64 d1,d2;
   pcBeam->get_D1(&d1);
   pcBeam->get_D2(&d2);
   Float64 section_height = GetSectionDepth(Xs);
   ATLASSERT(IsEqual(d1, section_height));
   Float64 bottom_flange_height = GetBottomFlangeHeight(Xs);
   ATLASSERT(IsEqual(d2, bottom_flange_height));
   Float64 Wt, Wb;
   GetEndBlockWidth(Xs, sectionBias, &Wt, &Wb);
   ATLASSERT(IsZero(Wt) && IsZero(Wb));
#endif 

   // create a new shape that is a clone of the original
   // so clients don't alter the original
   CComQIPtr<IShape> shape(UGirderSection);
   CComPtr<IShape> newShape;
   HRESULT hr = shape->Clone(&newShape);

   // position the shape
   CComQIPtr<IUGirderSection> newUGirderSection(newShape);
   if (coordinateSystem == cstBridge)
   {
      CComPtr<IPoint2d> pntTopCenter;
      GB_GetSectionLocation(this, Xs, &pntTopCenter);

      CComQIPtr<IXYPosition> position(newUGirderSection);
      position->put_LocatorPoint(lpTopCenter, pntTopCenter);
   }
   else
   {
      CComPtr<IPoint2d> pnt;
      pnt.CoCreateInstance(CLSID_Point2d);
      pnt->Move(0, 0);
      CComQIPtr<IXYPosition> position(newUGirderSection);
      position->put_LocatorPoint(lpTopCenter, pnt);
   }

   *ppShape = newShape;
   (*ppShape)->AddRef();

   return S_OK;
}

HRESULT CUSplicedGirderSegment::GetVolume_and_SurfaceArea(Float64* pVolume, Float64* pSurfaceArea)
{
   // U-beams are prismatic so don't call the base class version (it assumes a more general section)
   CHECK_RETVAL(pVolume);
   CHECK_RETVAL(pSurfaceArea);

   if (m_bUpdateVolumeAndSurfaceArea)
   {
      if (m_Shapes.size() == 0)
      {
         m_Volume = 0;
         m_SurfaceArea = 0;
      }
      else
      {
         CComPtr<IShape> shape;
         GetPrimaryShape(0.0, sbRight, cstGirder, &shape);
         Float64 perimeter;
         shape->get_Perimeter(&perimeter);

         CComPtr<IShapeProperties> shapeProps;
         shape->get_ShapeProperties(&shapeProps);

         Float64 area;
         shapeProps->get_Area(&area);

         Float64 L;
         get_Length(&L);

         m_Volume = area*L;
         m_SurfaceArea = perimeter*L + 2 * area;
      }

      m_bUpdateVolumeAndSurfaceArea = false;
   }

   *pVolume = m_Volume;
   *pSurfaceArea = m_SurfaceArea;
   return S_OK;
}

void CUSplicedGirderSegment::GetEndBlockWidth(Float64 Xs, SectionBias sectionBias,Float64* pWtop,Float64* pWbot)
{
   // not supporting end blocks
   *pWtop = 0;
   *pWbot = 0;
}
