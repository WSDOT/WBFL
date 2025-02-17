///////////////////////////////////////////////////////////////////////
// Stability
// Copyright � 1999-2025  Washington State Department of Transportation
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

#include <Stability/StabilityLib.h>
#include <Stability/AnalysisPointImp.h>
#include <Units\Units.h>

namespace WBFL
{
   namespace Stability
   {

      AnalysisPoint::AnalysisPoint() :
         m_X(0.0)
      {
      }

      AnalysisPoint::AnalysisPoint(Float64 X) :
         m_X(X)
      {
      }

      AnalysisPoint::AnalysisPoint(const AnalysisPoint& other) :
         m_X(other.m_X)
      {
      }

      void AnalysisPoint::SetLocation(Float64 X)
      {
         m_X = X;
      }

      Float64 AnalysisPoint::GetLocation() const
      {
         return m_X;
      }

      std::_tstring AnalysisPoint::AsString(const WBFL::Units::LengthData& lengthUnit, Float64 offset, bool bShowUnit) const
      {
         WBFL::Units::LengthTool formatTool(lengthUnit);
         std::_tstring str = formatTool.AsString(formatTool.Convert(m_X - offset));
         if (bShowUnit)
         {
            str += _T(" ") + lengthUnit.UnitOfMeasure.UnitTag();
         }

         return str;
      }

      std::unique_ptr<IAnalysisPoint> AnalysisPoint::Clone() const
      {
         return std::make_unique<AnalysisPoint>(*this);
      }
   }
}