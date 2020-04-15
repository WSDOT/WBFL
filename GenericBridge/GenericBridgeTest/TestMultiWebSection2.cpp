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
#include "TestMultiWebSection2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CTestMultiWebSection2::Test()
{
   CComPtr<IMultiWebSection2> beam_section;
   TRY_TEST(beam_section.CoCreateInstance(CLSID_MultiWebSection2), S_OK);

   CComPtr<IMultiWeb2> beam;
   beam_section->get_Beam(&beam);
   TRY_TEST(beam != nullptr, true);

   beam->put_H1(24);
   beam->put_H2(3);
   beam->put_H3(6);
   beam->put_C1(0);
   beam->put_C2(0);
   beam->put_F1(6);
   beam->put_F2(6);
   beam->put_W1(6);
   beam->put_W2(12);
   beam->put_T1(1);
   beam->put_T2(6);
   beam->put_T3(1);
   beam->put_T4(2);
   beam->put_T5(8);
   beam->put_WebCount(3);

   CComQIPtr<IGirderSection> section(beam_section);

   std::vector<std::pair<Float64, Float64>> vExpectedValues
   { 
      std::pair<Float64, Float64>(-9.0,64.0),
      std::pair<Float64, Float64>(-15.0,28.0)
   };

   TestWebSections(section, vExpectedValues);
}
