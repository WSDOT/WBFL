///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include "pch.h"
#include <DManip/EditableUnitValueTextBlock.h>

using namespace WBFL::DManip;

// Instantiate the template for various tool types
DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::LengthData>;
DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::MomentData>;
DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::AngleData>;
DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::StressData>;
DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::ForceData>;
DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::TimeData>;
DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::Length2Data>;
DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::Length3Data>;
DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::Length4Data>;
DMANIPTPL EditableUnitValueTextBlock<WBFL::Units::PerLengthData>;
