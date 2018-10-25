///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

HRESULT CUSplicedGirderSegment::GetSection(StageIndexType stageIdx,Float64 distAlongSegment,ISection** ppSection)
{
   CHECK_RETOBJ(ppSection);

   if (m_Shapes.size() == 0 )
   {
      *ppSection = 0;
      return S_OK;
   }

   HRESULT hr;
   CComPtr<IShape> primaryShape;
   hr = GetPrimaryShape(distAlongSegment,&primaryShape);
   ATLASSERT(SUCCEEDED(hr));
   if ( FAILED(hr) )
      return hr;


   // create our section object
   CComPtr<ICompositeSectionEx> section;
   section.CoCreateInstance(CLSID_CompositeSectionEx);

   section->QueryInterface(IID_ISection,(void**)ppSection);
   ATLASSERT(*ppSection != NULL);

   // add the primary shape
   Float64 Efg = 0;
   m_Shapes.front().FGMaterial->get_E(stageIdx,&Efg);
   
   Float64 Ebg = 0;
   if ( m_Shapes.front().BGMaterial )
      m_Shapes.front().BGMaterial->get_E(stageIdx,&Ebg);

   Float64 Dfg = 0;
   m_Shapes.front().FGMaterial->get_Density(stageIdx,&Dfg);
   
   Float64 Dbg = 0;
   if ( m_Shapes.front().BGMaterial )
      m_Shapes.front().BGMaterial->get_Density(stageIdx,&Dbg);

   section->AddSection(primaryShape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);

   // add all the secondary shapes
   std::vector<ShapeData>::iterator iter(m_Shapes.begin());
   std::vector<ShapeData>::iterator end(m_Shapes.end());
   iter++; // skip the first shape, we already processed it

   for ( ; iter != end; iter++ )
   {
      ShapeData& shapeData = *iter;

      Float64 Efg = 0;
      if ( shapeData.FGMaterial )
         shapeData.FGMaterial->get_E(stageIdx,&Efg);

      Float64 Ebg;
      if ( shapeData.BGMaterial )
         shapeData.BGMaterial->get_E(stageIdx,&Ebg);

      Float64 Dfg = 0;
      if ( shapeData.FGMaterial )
         shapeData.FGMaterial->get_Density(stageIdx,&Dfg);

      Float64 Dbg = 0;
      if ( shapeData.BGMaterial )
         shapeData.BGMaterial->get_Density(stageIdx,&Dbg);

      CComPtr<IShape> shape;
      shapeData.Shape->Clone(&shape);

      section->AddSection(shape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);
   }

   return S_OK;
}

HRESULT CUSplicedGirderSegment::GetPrimaryShape(Float64 distAlongSegment,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   if (m_Shapes.size() == 0 )
   {
      *ppShape = 0;
      return S_OK;
   }

   CComQIPtr<IUGirderSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is NULL... how did it get in the system????

   // This object reprsents a prismatic shape... all sections are the same
   HRESULT hr = S_OK;
   CComPtr<IUBeam> pcBeam;
   beam->get_Beam(&pcBeam);

   Float64 Wt, Wb;
   GetEndBlockWidth(distAlongSegment,&Wt,&Wb);

   Float64 W1, W2, W3, W4, W5;
   Float64 D1, D2, D3, D4, D5, D6, D7;
   Float64 T;

   pcBeam->get_W1(&W1);
   pcBeam->get_W2(&W2);
   pcBeam->get_W3(&W3);
   pcBeam->get_W4(&W4);
   pcBeam->get_W5(&W5);

   pcBeam->get_D1(&D1);
   pcBeam->get_D2(&D2);
   pcBeam->get_D3(&D3);
   pcBeam->get_D4(&D4);
   pcBeam->get_D5(&D5);
   pcBeam->get_D6(&D6);
   pcBeam->get_D7(&D7);

   pcBeam->get_T(&T);

   Float64 w1 = W1;
   Float64 w2 = W2;
   Float64 w3 = W3;
   Float64 w4 = W4;
   Float64 w5 = W5;
   Float64 d1 = D1;
   Float64 d2 = D2;
   Float64 d3 = D3;
   Float64 d4 = D4;
   Float64 d5 = D5;
   Float64 d6 = D6;
   Float64 d7 = D7;
   Float64 t  = T;

   //
   // Adjust D2 based on the bottom flange height
   // If bottom flange height is zero then don't make any adjustments (take zero to be don't change bottom flange)
   //
   Float64 bottom_flange_height = GetBottomFlangeHeight(distAlongSegment);
   if ( !IsZero(bottom_flange_height) )
   {
      d2 = bottom_flange_height;
   }

   if ( d2 < 0 )
   {
      // there really isn't a bottom flange if d2 < 0
      ATLASSERT(false); // I don't think this should ever happen for a U-beam
      d2 = 0;
      d3 = 0;
   }

   //
   // Adjust D1 based on the spliced girder profile
   //
   Float64 section_height = GetSectionDepth(distAlongSegment);
   d1 = section_height;
   ATLASSERT( 0 <= d1 );

   // create a new shape that is a clone of the original
   CComQIPtr<IShape> shape(beam);
   CComPtr<IShape> newShape;
   hr = shape->Clone(&newShape);

   // set the dimensions
   CComQIPtr<IUGirderSection> newUGirderSection(newShape);
   CComPtr<IUBeam> newBeam;
   newUGirderSection->get_Beam(&newBeam);
   newBeam->put_D1(d1);
   newBeam->put_D2(d2);
   newBeam->put_D3(d3);
   newBeam->put_D4(d4);
   newBeam->put_D5(d5);
   newBeam->put_D6(d6);
   newBeam->put_D7(d7);
   newBeam->put_W1(w1);
   newBeam->put_W2(w2);
   newBeam->put_W3(w3);
   newBeam->put_W4(w4);
   newBeam->put_W5(w5);
   newBeam->put_T(t);

   // position the shape
   CComPtr<IPoint2d> pntTopCenter;
   GB_GetSectionLocation(this,distAlongSegment,&pntTopCenter);

   CComQIPtr<IXYPosition> position(newUGirderSection);
   position->put_LocatorPoint(lpTopCenter,pntTopCenter);

   *ppShape = newShape;
   (*ppShape)->AddRef();

   return S_OK;
}

void CUSplicedGirderSegment::GetEndBlockWidth(Float64 distAlongSegment,Float64* pWtop,Float64* pWbot)
{
}
