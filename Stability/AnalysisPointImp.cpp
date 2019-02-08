///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2019  Washington State Department of Transportation
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

#include <Stability\StabilityLib.h>
#include <Stability\AnalysisPointImp.h>
#include <UnitMgt\UnitMgt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

stbAnalysisPoint::stbAnalysisPoint() :
m_X(0.0)
{
}

stbAnalysisPoint::stbAnalysisPoint(Float64 X) :
m_X(X)
{
}

stbAnalysisPoint::stbAnalysisPoint(const stbAnalysisPoint& other) :
m_X(other.m_X)
{
}

void stbAnalysisPoint::SetLocation(Float64 X)
{
   m_X = X;
}

Float64 stbAnalysisPoint::GetLocation() const
{
   return m_X;
}

std::_tstring stbAnalysisPoint::AsString(const unitmgtLengthData& lengthUnit,Float64 offset,bool bShowUnit) const
{
   LengthTool formatTool(lengthUnit);
   std::_tstring str = formatTool.AsString(formatTool.Convert(m_X-offset));
   if ( bShowUnit )
   {
      str += _T(" ") + lengthUnit.UnitOfMeasure.UnitTag();
   }

   return str;   
}

stbIAnalysisPoint* stbAnalysisPoint::Clone() const
{
   return new stbAnalysisPoint(*this);
}
