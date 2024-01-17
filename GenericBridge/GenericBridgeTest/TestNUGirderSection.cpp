///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include "TestNUGirderSection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CTestNUGirderSection::Test()
{
   CComPtr<INUGirderSection> beam_section;
   TRY_TEST(beam_section.CoCreateInstance(CLSID_NUGirderSection), S_OK);

   CComPtr<INUBeam> beam;
   beam_section->get_Beam(&beam);

   //NU2400
   beam->put_W1(1225);
   beam->put_W2(975);
   beam->put_D1(65);
   beam->put_D2(45);
   beam->put_D3(2015);
   beam->put_D4(140);
   beam->put_D5(135);
   beam->put_T(150);
   beam->put_R1(200);
   beam->put_R2(200);
   beam->put_R3(50);
   beam->put_R4(50);

   CComQIPtr<IPrestressedGirderSection> section(beam_section);

   std::vector<std::pair<Float64, Float64>> vExpectedValues
   { 
      std::pair<Float64, Float64>(-293.95550943497187, 150.0),
      std::pair<Float64, Float64>(-1981.6738403896406, 150.0)
   };

   TestWebSections(section, vExpectedValues);
}
