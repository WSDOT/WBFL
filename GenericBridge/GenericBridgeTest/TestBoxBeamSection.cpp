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
#include "TestBoxBeamSection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CTestBoxBeamSection::Test()
{
   CComPtr<IBoxBeamSection> beam_section;
   TRY_TEST(beam_section.CoCreateInstance(CLSID_BoxBeamSection), S_OK);

   CComPtr<IBoxBeam> beam;
   beam_section->get_Beam(&beam);
   TRY_TEST(beam != nullptr, true);

   // TxDOT 5B40
   beam->put_H1(5.5);
   beam->put_H2(29.5);
   beam->put_H3(5);
   beam->put_H4(4);
   beam->put_H5(3);
   beam->put_H6(5);
   beam->put_H7(17);
   beam->put_W1(3);
   beam->put_W2(5);
   beam->put_W3(39.75);
   beam->put_W4(5);
   beam->put_F1(0);
   beam->put_F2(5);
   beam->put_C1(0.75);

   CComQIPtr<IPrestressedGirderSection> section(beam_section);

   std::vector<std::pair<Float64, Float64>> vExpectedValues
   { 
      std::pair<Float64, Float64>( -5.5,13.0),
      std::pair<Float64, Float64>( -7.0,10.0),
      std::pair<Float64, Float64>(-18.0,10.0),
      std::pair<Float64, Float64>(-23.0,20.0),
      std::pair<Float64, Float64>(-30.0,20.0),
      std::pair<Float64, Float64>(-35.0,30.0)
   };

   TestWebSections(section, vExpectedValues);
}
