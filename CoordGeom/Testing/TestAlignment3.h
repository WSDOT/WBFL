///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright � 1999-2023  Washington State Department of Transportation
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

#include <System/Debug.h>

namespace WBFL
{
   namespace COGO
   {
      class Alignment;
   };
};

class CTestAlignment3
{
public:
   CTestAlignment3();

   static bool Test(WBFL::Debug::Log& rlog);

private:
   static bool Test1(WBFL::Debug::Log& rlog);
   static bool Test2(WBFL::Debug::Log& rlog);
   static bool Test3(WBFL::Debug::Log& rlog);
   static bool Test4(WBFL::Debug::Log& rlog);
   static bool Test5(WBFL::Debug::Log& rlog);
   static bool CompareAlignments(std::shared_ptr<const WBFL::COGO::Alignment> alignment1, std::shared_ptr<const WBFL::COGO::Alignment> alignment2, Float64 start, Float64 end, long nPoints);
};