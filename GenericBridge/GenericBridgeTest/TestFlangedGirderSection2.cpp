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
#include "TestFlangedGirderSection2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CTestFlangedGirderSection2::Test()
{
   CComPtr<IFlangedGirderSection2> beam_section;
   TRY_TEST(beam_section.CoCreateInstance(CLSID_FlangedGirderSection2), S_OK);

   // WSDOT WF100G Modified
   CComPtr<IPrecastBeam2> beam;
   TRY_TEST(beam.CoCreateInstance(CLSID_PrecastBeam2), S_OK);
   beam->put_W1(6);
   beam->put_W2(18.4375);
   beam->put_W3(3);
   beam->put_W4(3);
   beam->put_W5(13.125);
   beam->put_D1(3);
   beam->put_D2(3);
   beam->put_D3(3);
   beam->put_D4(3);
   beam->put_D5(4.5);
   beam->put_D6(5.125);
   beam->put_H(100);
   beam->put_T1(6.125);
   beam->put_T2(6.125);
   beam->put_C1(1.0);

   beam_section->put_Beam(beam);

   CComQIPtr<IPrestressedGirderSection> section(beam_section);

   std::vector<std::pair<Float64, Float64>> vExpectedValues
   { 
      std::pair<Float64, Float64>(-6.0, 12.125),
      std::pair<Float64, Float64>(-9.0, 6.125),
      std::pair<Float64, Float64>(-87.375, 6.125),
      std::pair<Float64, Float64>(-90.375, 12.125)
   };

   TestWebSections(section, vExpectedValues);
}
