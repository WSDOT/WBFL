///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam forumla, patterned after Roark's formulas
//         for Stress and Strain
// Copyright © 1999-2010  Washington State Department of Transportation
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

#include <Roark\RoarkLib.h>
#include <Roark\Roark.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

rkRoarkBeam::rkRoarkBeam(const rkRoarkBeam& rOther)
{
   L = rOther.L;
   EI = rOther.EI;
}

rkRoarkBeam::rkRoarkBeam(Float64 l,Float64 e,Float64 i)
{
   L = l; // Length of beam
   EI = e*i;
}

Float64 rkRoarkBeam::GetL() const
{
   return L;
}

Float64 rkRoarkBeam::GetEI() const
{
   return EI;
}


//======================== DEBUG      =======================================
#if defined _DEBUG
bool rkRoarkBeam::AssertValid() const
{
   if ( !(L > 0) ) // L must be > 0
      return false;

   if ( !(EI > 0) ) // EI must be > 0
      return false;

   return true;
}

void rkRoarkBeam::Dump(dbgDumpContext& os) const
{
   os << "Dump for rkRoarkBeam" << endl;
   os << "L  = " << L << endl;
   os << "EI = " << EI << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool rkRoarkBeam::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("rkRoarkBeam");

   // Nothing to test here... 
   // All meaningful tests are conducted on derived classes.

   TESTME_EPILOG("RoarkBeam");
}
#endif // _UNITTEST
