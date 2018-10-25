///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2012  Washington State Department of Transportation
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

#ifndef INCLUDED_UNITS_CONVERT_H_
#define INCLUDED_UNITS_CONVERT_H_
#pragma once

#include <Units\PhysicalT.h>
#include <Units\UnitsExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

// INLINE METHODS
//

template <class T>
Float64 Convert(Float64 value,const T& from, const T& to)
{
   PRECONDITION( from.GetConvFactor() > 0 && to.GetConvFactor() > 0 );

   Float64 i_value;

   i_value = ( value + from.GetPreTerm() ) * from.GetConvFactor() + from.GetPostTerm();
   i_value = ( i_value - to.GetPostTerm() )  / to.GetConvFactor()   - to.GetPreTerm();

   return i_value;
}

// EXTERNAL REFERENCES
//

#endif // INCLUDED_UNITS_CONVERT_H_

