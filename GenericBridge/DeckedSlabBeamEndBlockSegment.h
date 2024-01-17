///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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

// DeckedSlabBeamEndBlockSegment.h : Declaration of the CSegment

#pragma once

#include "resource.h"       // main symbols
#include "Segments.h"
#include "EndBlockSegmentImpl.h"

// Template takes care of all
class CDeckedSlabBeamVoidSurfaceAreaCalculator;
using CDeckedSlabBeamEndBlockSegment = TEndBlockSegmentImpl<IDeckedSlabBeamEndBlockSegment, IDeckedSlabBeamSection, IDeckedSlabBeam, &CLSID_DeckedSlabBeamEndBlockSegment, IDR_DECKEDSLABBEAMENDBLOCKSEGMENT, VoidedEndBlock<IDeckedSlabBeam>, CDeckedSlabBeamVoidSurfaceAreaCalculator>;

class CDeckedSlabBeamVoidSurfaceAreaCalculator
{
public:
   CDeckedSlabBeamVoidSurfaceAreaCalculator(CDeckedSlabBeamEndBlockSegment* pSegment) : m_pSegment(pSegment)
   {
   }

   HRESULT CalculateVoidSurfaceArea(Float64* pSurfaceArea)
   {
      CHECK_RETVAL(pSurfaceArea);
      if (m_pSegment->m_Shapes.size() == 0)
      {
         *pSurfaceArea = 0;
      }
      else
      {
         Float64 L;
         m_pSegment->get_Length(&L);

         CComQIPtr<IDeckedSlabBeamSection> section(m_pSegment->m_Shapes.front().Shape);
         CComPtr<IDeckedSlabBeam> beam;
         section->get_Beam(&beam);
         Float64 A, B, C, W, Tb;
         beam->get_A(&A);
         beam->get_B(&B);
         beam->get_C(&C);
         beam->get_W(&W);
         beam->get_Tb(&Tb);

         Float64 void_perimeter = (A - 2 * (B + W)) * (C - Tb);

         *pSurfaceArea = (L - m_pSegment->m_EndBlockLength[etStart] - m_pSegment->m_EndBlockLength[etEnd])*(void_perimeter);
      }
      return S_OK;
   }

protected:
   CDeckedSlabBeamEndBlockSegment* m_pSegment;
};

