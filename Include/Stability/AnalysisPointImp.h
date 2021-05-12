///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2021  Washington State Department of Transportation
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

#pragma once

#include <Stability\StabilityExp.h>
#include <Stability\AnalysisPoint.h>

/// An analysis point
class STABILITYCLASS stbAnalysisPoint : public stbIAnalysisPoint
{
public:
   stbAnalysisPoint();
   stbAnalysisPoint(Float64 X); ///< Creates an analysis point at the specified distance from the left end of girder.
   stbAnalysisPoint(const stbAnalysisPoint& other); ///< Copy constructor
 
   /// Sets the location relative to the left end of the girder
   void SetLocation(Float64 X);

   /// Returns the analysis point location
   virtual Float64 GetLocation() const override;

   /// Returns a reporting string for the analysis point.
   virtual std::_tstring  AsString(
      const unitmgtLengthData& lengthUnit, ///< Indirect unit measure information
      Float64 offset, ///< an offset to be applied to the point location so the analysis point can appear to be relative to a different datum then the left end of the girder.
      bool bShowUnit ///< If true, the unit of measure is included in the resulting string
   ) const override;

   /// Creates a copy of the analysis point
   virtual stbIAnalysisPoint* Clone() const override;

private:
   Float64 m_X;
};
