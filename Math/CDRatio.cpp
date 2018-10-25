///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2016  Washington State Department of Transportation
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

#include <Math\MathLib.h>
#include <Math\CDRatio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   mathCDRatio
****************************************************************************/

bool mathCDRatio::IsCDRatioLess(cdSense sense, Float64 capacity1, Float64 demand1, Float64 capacity2, Float64 demand2)
{
   // First do some input sanity checking
#if defined _DEBUG
   if (sense==cdPositive)
   {
      ATLASSERT(capacity1>=0.0 && capacity2>=0.0); // Signs of capacites cannot be different
   }
   else
   {
      ATLASSERT(capacity1<=0.0 && capacity2<=0.0); // ""
   }
#endif

   // We must deal with all of the edge cases
   bool icz1 = IsZero(capacity1);
   bool icz2 = IsZero(capacity2);
   if (icz1 && icz2)
   {
      // Both capacities are zero. Largest demand wins
      if (sense==cdPositive)
      {
         return demand1 > demand2;
      }
      else
      {
         return demand1 < demand2;
      }
   }
   else if (icz1)
   {
      // Capacity 1 is zero, and capacity 2 is not. Zero always wins
      return true;
   }
   else if (icz2)
   {
      // Capacity 2 is zero, and capacity 1 is not. Zero always wins
      return false;
   }
   else
   {
      // We have two non-zero capacities.
      // Make sure we don't divide by zero
      bool idz1 = IsZero(demand1);
      bool idz2 = IsZero(demand2);
      if (idz1 && idz2)
      {
         // Both demands are zero. smallest capacity wins
         if (sense==cdPositive)
         {
            return capacity1 < capacity2;
         }
         else
         {
            return capacity1 > capacity2;
         }
      }
      else if (idz1)
      {
         return false; // c/0 == inf
      }
      else if (idz2)
      {
         return true;
      }
      else
      {
         // We have numbers...
         Float64 cd1 = capacity1/demand1;
         Float64 cd2 = capacity2/demand2;

         // But, have to deal with negative c/d's
         if (cd2 < 0.0)
         {
            if(cd1>0.0)
            {
               return true;
            }
            else
            {
               // both negative
               return cd1 < cd2;
            }
         }
         else
         {
            if (cd1 < 0.0)
            {
               return false;
            }
            else
            {
               // Finally can compare two positive c/d's
               return cd1 < cd2;
            }
         }
      }
   }
}
