///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// BoxBeamEndBlockSegment.h : Declaration of the CSegment

#pragma once


#include "resource.h"       // main symbols
#include "EndBlockSegmentImpl.h"

// Template takes care of all
class CBoxBeamVoidSurfaceAreaCalculator;
using CBoxBeamEndBlockSegment = TEndBlockSegmentImpl<IBoxBeamEndBlockSegment, IBoxBeamSection, IBoxBeam, &CLSID_BoxBeamEndBlockSegment, IDR_BOXBEAMENDBLOCKSEGMENT, VoidedEndBlock<IBoxBeam>, CBoxBeamVoidSurfaceAreaCalculator>;

class CBoxBeamVoidSurfaceAreaCalculator
{
public:
   CBoxBeamVoidSurfaceAreaCalculator(CBoxBeamEndBlockSegment* pSegment) : m_pSegment(pSegment)
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

         CComQIPtr<IBoxBeamSection> section(m_pSegment->m_Shapes.front().Shape);
         CComPtr<IBoxBeam> beam;
         section->get_Beam(&beam);
         Float64 W3, H2, F1, F2;
         beam->get_W3(&W3);
         beam->get_H2(&H2);
         beam->get_F1(&F1);
         beam->get_F2(&F2);

         *pSurfaceArea = L*(2 * (H2 - F1 - F2) + 2 * (W3 - F1 - F2) + 2 * sqrt(2 * F1*F1) + 2 * sqrt(2 * F2*F2));
      }
      return S_OK;
   }
   
protected:
   CBoxBeamEndBlockSegment* m_pSegment;
};

