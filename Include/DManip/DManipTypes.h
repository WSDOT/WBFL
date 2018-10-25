///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

#ifndef INCLUDED_DMANIPTYPES_H_
#define INCLUDED_DMANIPTYPES_H_
#pragma once

typedef enum AccessType
{
   atByID = 1,
   atByIndex = 2
} AccessType;


namespace DManip
{
   // mapping modes for scaling views
   enum MapMode {Isotropic, Anisotropic };
   enum MapModeModifier {NoFit, BestFitX, BestFitY, BestFitXY };

   typedef enum ArrowHeadStyleType
   {
      ahsLines  = 1, // Arrow heads are lines
      ahsOpen   = 2, // Arrow head is non-filled triangle
      ahsFilled = 3  // Arrow head is filled triangle
   } ArrowHeadStyleType;
}


#endif // INCLUDED_DMANIPTYPES_H_