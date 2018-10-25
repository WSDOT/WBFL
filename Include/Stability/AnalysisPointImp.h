///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2017  Washington State Department of Transportation
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

/*****************************************************************************
CLASS 
   stbIAnalysispoint

DESCRIPTION
   Abstract interface for an analysis point
*****************************************************************************/

class STABILITYCLASS stbAnalysisPoint : public stbIAnalysisPoint
{
public:
   stbAnalysisPoint();
   stbAnalysisPoint(Float64 X);
   stbAnalysisPoint(const stbAnalysisPoint& other);

   void SetLocation(Float64 X);

   // Returns the location of the analysis point relative to the left end of the girder
   virtual Float64 GetLocation() const;

   // Returns a reporting string for the analysis point.
   // if pLengthUnit is not NULL, the string should contain the unit of measure
   virtual std::_tstring AsString(const unitmgtLengthData& lengthUnit,Float64 offset,bool bShowUnit) const;

   virtual stbIAnalysisPoint* Clone() const;

protected:
   Float64 m_X;
};
