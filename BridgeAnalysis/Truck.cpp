///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2011  Washington State Department of Transportation
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

#include <BridgeAnalysis\BridgeAnalysisLib.h>
//////////////////X////////////////////X/////////////////////////////////////
// NAME:          bamTruck           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <BridgeAnalysis\Truck.h>                 // class implementation

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////


//======================== LIFECYCLE  =======================================

bamTruck::bamTruck()
{
} // bamTruck

bamTruck::bamTruck(const bamTruck& rOther)
{
   MakeCopy( rOther );
} // bamTruck

bamTruck::~bamTruck()
{
} // ~bamTruck

//======================== OPERATORS  =======================================

bamTruck& bamTruck::operator = (const bamTruck& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
} // operator =

bool bamTruck::operator < (const bamTruck& /*rOther*/) const
{
   return false;
}

bool bamTruck::operator == (const bamTruck& /*rOther*/) const
{
   return false;
}

//======================== OPERATIONS =======================================

void bamTruck::AddAxle(Float64 wgt, bamAxleSpacing& space)
{
   PRECONDITION( wgt >= 0 );

   m_AxleWeight.push_back(wgt);
   m_AxleSpacing.push_back(space);
}

//======================== ACCESS     =======================================

Float64 bamTruck::GetAxleWeight(AxleIndexType axleIndex)
{
	return m_AxleWeight[axleIndex];
}

Float64 bamTruck::GetAxleSpacing(AxleIndexType axleIndex)
{
   bamAxleSpacing s = m_AxleSpacing[axleIndex];
	return s.GetMinSpacing();
}

AxleIndexType bamTruck::GetNumAxles()
{
   return m_AxleWeight.size();
}

Float64 bamTruck::GetMinLength() const
{
   Float64 length = 0;
   SpacingContainer::const_iterator iter;
   for ( iter = m_AxleSpacing.begin(); iter != m_AxleSpacing.end(); iter++ )
   {
      const bamAxleSpacing& spacing = *iter;
      length += spacing.GetMinSpacing();
   }

   return length;
}

Float64 bamTruck::GetMaxLength() const
{
   Float64 length = 0;
   SpacingContainer::const_iterator iter;
   for ( iter = m_AxleSpacing.begin(); iter != m_AxleSpacing.end(); iter++ )
   {
      const bamAxleSpacing& spacing = *iter;
      length += spacing.GetMaxSpacing();
   }

   return length;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamTruck::MakeCopy(const bamTruck& rOther)
{
   m_AxleWeight  = rOther.m_AxleWeight;
   m_AxleSpacing = rOther.m_AxleSpacing;
}

void bamTruck::MakeAssignment(const bamTruck& rOther)
{
   //Base::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY ==========================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bamTruck::AssertValid() const
{
   return true;
}

void bamTruck::Dump(dbgDumpContext& os) const
{
   os << "Dump for bamTruck" << endl;
   AxleWgtContainer::const_iterator wgtIter = m_AxleWeight.begin();
   SpacingContainer::const_iterator spcIter = m_AxleSpacing.begin();
   Int16 count = 1;
   for ( ; spcIter != m_AxleSpacing.end() && wgtIter != m_AxleWeight.end(); spcIter++, wgtIter++ )
   {
      os << "Axle " << count;
      os << " Spacing" << endl;
      (*spcIter).Dump(os);
      os << " Wgt = " << (*wgtIter) << endl;
      os << endl;
      count++;
   }
}
#endif // _DEBUG

#if defined _UNITTEST
bool bamTruck::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bamTruck");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bamTruck");

   TESTME_EPILOG("Truck");
}
#endif // _UNITTEST
