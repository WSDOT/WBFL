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
#include "TestUGirderSection2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CTestUGirderSection2::Test()
{
   CComPtr<IUGirderSection2> beam_section;
   TRY_TEST(beam_section.CoCreateInstance(CLSID_UGirderSection2), S_OK);

   CComPtr<IUBeam2> beam;
   beam_section->get_Beam(&beam);
   TRY_TEST(beam != nullptr, true);

   // TxDOT U54
   beam->put_C1(0.75);
   beam->put_D1(54);
   beam->put_D2(8.25);
   beam->put_D3(3);
   beam->put_D4(0.875);
   beam->put_D5(5.875);
   beam->put_D6(21.625);
   beam->put_W1(55);
   beam->put_W2(96);
   beam->put_W3(3);
   beam->put_W4(0.375);
   beam->put_W5(8.25);
   beam->put_W6(15.75);
   beam->put_W7(1.75);

   CComQIPtr<IPrestressedGirderSection> section(beam_section);

   std::vector<std::pair<Float64, Float64>> vExpectedValues
   { 
      std::pair<Float64, Float64>( -6.75, 12.680662599015204),
      std::pair<Float64, Float64>(-21.625,10.273148148148152),
      std::pair<Float64, Float64>(-42.75, 10.273148148148152)
   };

   TestWebSections(section, vExpectedValues);
}
