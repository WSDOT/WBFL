///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
// Copyright © 1999-2021  Washington State Department of Transportation
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

#pragma once

#include <GraphicsLib/GraphicsLibExp.h>
#include <WBFLTypes.h>

// Causes the compiler to instantiate the class and export it's symbols
GRTPL SimplePointT<Float64>;
GRTPL SimpleSizeT<Float64>;
GRTPL SimpleRectT<Float64>;

// Use alias declarations for a nice name (this is the modern version of typedef, see Modern Effective C++, Scott Meyers, Item #9)
using GraphPoint = SimplePointT<Float64>;
using GraphSize = SimpleSizeT<Float64>;
using GraphRect = SimpleRectT<Float64>;
