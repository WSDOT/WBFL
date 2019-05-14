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

// FlangedSplicedGirderSegment.cpp : Implementation of CFlangedSplicedGirderSegment
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "FlangedSplicedGirderSegment.h"
#include <MathEx.h>
#include <algorithm>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlangedSplicedGirderSegment
HRESULT CFlangedSplicedGirderSegment::FinalConstruct()
{
   return S_OK;
}

void CFlangedSplicedGirderSegment::FinalRelease()
{
}

////////////////////////////////////////////////////////////////////
// ISplicedGirderSegment implementation
//

HRESULT CFlangedSplicedGirderSegment::GetPrimaryShape(Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem, IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   if (m_Shapes.size() == 0 )
   {
      *ppShape = 0;
      return S_OK;
   }

   CComQIPtr<IFlangedGirderSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is nullptr... how did it get in the system????

   // This object reprsents a prismatic shape... all sections are the same
   HRESULT hr = S_OK;

   // create a new shape that is a clone of the original
   CComQIPtr<IShape> shape(beam);
   CComPtr<IShape> newShape;
   hr = shape->Clone(&newShape);

   // set the dimensions
   CComQIPtr<IFlangedGirderSection> newFlangedBeam(newShape);
   CComPtr<IPrecastBeam> newBeam;
   newFlangedBeam->get_Beam(&newBeam);

   Float64 Hg = GetSectionDepth(Xs);
   Float64 Htf = GetBottomFlangeHeight(Xs);
   AdjustForVariableDepth(newBeam, Hg, Htf);

   // Get the end block dimensions
   // and adjust dimensions based on end block size
   Float64 Wt, Wb;
   GetEndBlockWidth(Xs, sectionBias, &Wt, &Wb);
   AdjustForEndBlocks(newBeam, Wt, Wb);

   // position the shape
   if (coordinateSystem == cstBridge)
   {
      CComPtr<IPoint2d> pntTopCenter;
      GB_GetSectionLocation(this, Xs, &pntTopCenter);

      CComQIPtr<IXYPosition> position(newFlangedBeam);
      position->put_LocatorPoint(lpTopCenter, pntTopCenter);
   }
   else
   {
      CComPtr<IPoint2d> pnt;
      pnt.CoCreateInstance(CLSID_Point2d);
      pnt->Move(0, 0);
      CComQIPtr<IXYPosition> position(newFlangedBeam);
      position->put_LocatorPoint(lpTopCenter, pnt);
   }

   *ppShape = newShape;
   (*ppShape)->AddRef();
   return S_OK;
}

void CFlangedSplicedGirderSegment::GetEndBlockWidth(Float64 Xs, SectionBias sectionBias,Float64* pWtop,Float64* pWbot)
{
   Float64 segLength;
   get_Length(&segLength);

   CComQIPtr<IFlangedGirderSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is nullptr... how did it get in the system????

   CComPtr<IPrecastBeam> pcBeam;
   beam->get_Beam(&pcBeam);

   ::GetEndBlockWidth(Xs, segLength, sectionBias, pcBeam, m_EndBlockWidth, m_EndBlockLength, m_EndBlockTransitionLength, pWtop, pWbot);
}
