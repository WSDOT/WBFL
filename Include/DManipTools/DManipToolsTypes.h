///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2020  Washington State Department of Transportation
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

#ifndef INCLUDED_DMANIPTOOLSTYPES_H_
#define INCLUDED_DMANIPTOOLSTYPES_H_
#pragma once

enum DataPointSymbolType
{
   dpstNone           =-1,
   dpst0              = 0,
   dpst1              = 1,
   dpst2              = 2,
   dpst3              = 3,
   dpst4              = 4,
   dpst5              = 5,
   dpst6              = 6,
   dpst7              = 7,
   dpst8              = 8, 
   dpst9              = 9, 
   dpstCircle         = 10,
   dpstTriangle       = 11,
   dpstCross          = 12,
   dpstLeft           = 13,
   dpstRight          = 14,
   dpstLastDefault    = 15  // this needs to always be the last in the list (for iterating)
};

#endif 