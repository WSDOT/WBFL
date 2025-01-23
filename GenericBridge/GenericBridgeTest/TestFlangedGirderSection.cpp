///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include "TestFlangedGirderSection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CTestFlangedGirderSection::Test()
{
   CComPtr<IFlangedGirderSection> beam_section;
   TRY_TEST(beam_section.CoCreateInstance(CLSID_FlangedGirderSection), S_OK);

   CComPtr<IBeamShapeFactory> factory;
   factory.CoCreateInstance(CLSID_BeamShapeFactory);

   // WSDOT WF100G
   CComPtr<IShape> shape;
   factory->CreateShape(WSDOT_WF100G, &shape);

   CComQIPtr<IPrecastBeam> beam(shape);
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

   // AASHTO Type III
   shape.Release();
   beam.Release();
   factory->CreateShape(AASHTO_TypeIII, &shape);
   shape.QueryInterface(&beam);
   beam_section->put_Beam(beam);
   vExpectedValues.clear();
   vExpectedValues.emplace_back(-7.0, 16.0);
   vExpectedValues.emplace_back(-11.5, 7.0);
   vExpectedValues.emplace_back(-30.5, 7.0);
   vExpectedValues.emplace_back(-38.0,22.0);
   TestWebSections(section, vExpectedValues);
}
