///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2022  Washington State Department of Transportation
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

#include <Units\UnitsLib.h>
#include <Units\SysUnits.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void convert_from( Float64* pValue, Float64 preTerm, Float64 cf, Float64 postTerm, Float64 dim )
{
   if (dim != 0)
   {
      if ( dim == 1 )
         *pValue += preTerm;

      PRECONDITION( cf > 0 );
      cf = pow(cf,dim); 
      (*pValue) *= cf;

      if ( dim == 1 )
         *pValue += postTerm;
   }
}

void convert_to( Float64* pValue, Float64 preTerm, Float64 cf, Float64 postTerm, Float64 dim )
{
   if (dim != 0)
   {
      if ( dim == 1 )
         *pValue -= postTerm;

      PRECONDITION( cf > 0 );
      cf = pow(cf, dim);
      (*pValue) /= cf;

      if ( dim == 1 )
         *pValue -= preTerm;
   }
}



