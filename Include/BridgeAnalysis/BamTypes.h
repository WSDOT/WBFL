///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_BAMTYPES_H_
#define INCLUDED_BRIDGEANALYSIS_BAMTYPES_H_
#pragma once

enum bamLoadDirection { Local, Global, GlobalProjected };
enum bamSupportFixity { Pin, HRoller, VRoller, Fixed, HGuide, VGuide };
enum bamElementType   { etSpan, etSupport };
enum bamGravityDirection { PositiveX, NegativeX, PositiveY, NegativeY };
enum bamOptimumType { otMaximum, otMinimum };
enum bamOptimumVariable { ovFx, ovFy, ovMz };

struct bamElementExcludeInfo
{
   Int32 m_ElementId;
   bamElementType m_ElementType;
};

#endif // INCLUDED_BRIDGEANALYSIS_BAMTYPES_H_