///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
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

#include "stdafx.h"
#include "TestVoidedSlabSection2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CTestVoidedSlabSection2::Test()
{
   CComPtr<IVoidedSlabSection2> beam_section;
   TRY_TEST(beam_section.CoCreateInstance(CLSID_VoidedSlabSection2), S_OK);

   CComPtr<IVoidedSlab2> beam;
   beam_section->get_Beam(&beam);
   TRY_TEST(beam != nullptr, true);

   beam->put_Height(36);
   beam->put_Width(54);
   beam->put_ExteriorVoidDiameter(18);
   beam->put_ExteriorVoidSpacing(24);
   beam->put_ExteriorVoidElevation(12);
   beam->put_InteriorVoidDiameter(18);
   beam->put_InteriorVoidSpacing(24);
   beam->put_InteriorVoidElevation(12);
   beam->put_VoidCount(3);

   CComQIPtr<IPrestressedGirderSection> section(beam_section);

   std::vector<std::pair<Float64, Float64>> vExpectedValues
   { 
      std::pair<Float64, Float64>(-15.0, 54.0),
      std::pair<Float64, Float64>(-33.0, 54.0)
   };

   TestWebSections(section, vExpectedValues);

   // no voids, no web sections
   beam->put_VoidCount(0);
   vExpectedValues.clear();
   TestWebSections(section, vExpectedValues);
}
