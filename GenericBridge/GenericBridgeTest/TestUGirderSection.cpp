///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2020  Washington State Department of Transportation
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
#include "TestUGirderSection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CTestUGirderSection::Test()
{
   CComPtr<IUGirderSection> beam_section;
   TRY_TEST(beam_section.CoCreateInstance(CLSID_UGirderSection), S_OK);

   CComPtr<IUBeam> beam;
   beam_section->get_Beam(&beam);
   TRY_TEST(beam != nullptr, true);

   // WSDOT UF84G5
   beam->put_D1(84);
   beam->put_D2(6);
   beam->put_D3(6);
   beam->put_D4(4.5);
   beam->put_D5(1.5);
   beam->put_D6(4.5);
   beam->put_D7(1.5);
   beam->put_T(7);
   beam->put_W1(60);
   beam->put_W2(92.285714);
   beam->put_W3(12);
   beam->put_W4(3);
   beam->put_W5(5);

   CComQIPtr<IPrestressedGirderSection> section(beam_section);

   std::vector<std::pair<Float64, Float64>> vExpectedValues
   { 
      std::pair<Float64, Float64>( -6.0,14.142135620104760),
      std::pair<Float64, Float64>(-72.0,14.142135620104760)
   };

   TestWebSections(section, vExpectedValues);


   // WSDOT U78G5
   beam->put_D1(78);
   beam->put_D2(6);
   beam->put_D3(6);
   beam->put_D4(0);
   beam->put_D5(0);
   beam->put_D6(0);
   beam->put_D7(0);
   beam->put_T(7);
   beam->put_W1(60);
   beam->put_W2(82.285714);
   beam->put_W3(12);
   beam->put_W4(0);
   beam->put_W5(0);

   vExpectedValues.clear();
   vExpectedValues.emplace_back(  0.0, 14.142135620104760);
   vExpectedValues.emplace_back(-66.0, 14.142135620104760);

   TestWebSections(section, vExpectedValues);
}
