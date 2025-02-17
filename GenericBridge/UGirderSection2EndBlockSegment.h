///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright � 1999-2025  Washington State Department of Transportation
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

// UGirderSection2EndBlockSegment.h : Declaration of the CSegment

#pragma once


#include "resource.h"       // main symbols
#include "EndBlockSegmentImpl.h"

// Template takes care of all
class CUGirderVoidSurfaceAreaCalculator;
using CUGirderSection2EndBlockSegment = TEndBlockSegmentImpl<IUGirderSection2EndBlockSegment, IUGirderSection2, IUBeam2, &CLSID_UGirderSection2EndBlockSegment, IDR_UGIRDERSECTION2ENDBLOCKSEGMENT, OutlineEndBlock<IUBeam2>, CUGirderVoidSurfaceAreaCalculator>;

class CUGirderVoidSurfaceAreaCalculator
{
public:
   CUGirderVoidSurfaceAreaCalculator(CUGirderSection2EndBlockSegment* pSegment) : m_pSegment(pSegment)
   {
   }

   HRESULT CalculateVoidSurfaceArea(Float64* pSurfaceArea)
   {
      CHECK_RETVAL(pSurfaceArea);
      *pSurfaceArea = 0;
      return S_OK;
   }

protected:
   CUGirderSection2EndBlockSegment* m_pSegment;
};

