///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
// NAME:          bamAxleSpacing           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <BridgeAnalysis\AxleSpacing.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

bamAxleSpacing::bamAxleSpacing(Float64 minSpace,Float64 maxSpace,Measure measure)
{
   SetSpacing(measure,minSpace,maxSpace);
} // bamAxleSpacing

bamAxleSpacing::bamAxleSpacing(const bamAxleSpacing& rOther)
{
   MakeCopy( rOther );
} // bamAxleSpacing

bamAxleSpacing::~bamAxleSpacing()
{
} // ~bamAxleSpacing

//======================== OPERATORS  =======================================

bamAxleSpacing& bamAxleSpacing::operator = (const bamAxleSpacing& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
} // operator =

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void bamAxleSpacing::SetSpacing(Measure measure,Float64 minSpace,Float64 maxSpace)
{
   m_Measure    = measure;
   m_MinSpacing = minSpace;
   m_MaxSpacing = maxSpace;

   if ( m_Measure == UpperBound && m_MinSpacing > m_MaxSpacing )
   {
      Float64 tmp = m_MinSpacing;
      m_MinSpacing = m_MaxSpacing;
      m_MaxSpacing = tmp;
   }

   if ( m_Measure == Fixed )
      m_MaxSpacing = m_MinSpacing;

   ASSERTVALID;
}

Float64 bamAxleSpacing::GetMinSpacing() const
{
   Float64 space;
   switch (m_Measure)
   {
   case Fixed:
   case LowerBound:
   case Bounded:
        space = m_MinSpacing;
        break;

   case UpperBound:
        space = 0;
        break;
   }

   return space;
}

Float64 bamAxleSpacing::GetMaxSpacing() const
{
   Float64 space;
   switch (m_Measure)
   {
   case Fixed:
        space = m_MinSpacing;
        break;

   case UpperBound:
   case Bounded:
        space = m_MaxSpacing;
        break;

   case LowerBound:
        space = Float64_Max;
        break;
   }

   return space;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamAxleSpacing::MakeCopy(const bamAxleSpacing& rOther)
{
   m_Measure    = rOther.m_Measure;
   m_MinSpacing = rOther.m_MinSpacing;
   m_MaxSpacing = rOther.m_MaxSpacing;

   ASSERTVALID;
}

void bamAxleSpacing::MakeAssignment(const bamAxleSpacing& rOther)
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

//======================== DEBUG   ==========================================
#if defined _DEBUG
bool bamAxleSpacing::AssertValid() const
{
   if ( GetMinSpacing() < 0 )
      return false;

   if ( GetMaxSpacing() < 0 )
      return false;

   if ( GetMaxSpacing() < GetMinSpacing() )
      return false;

   return true;
}

void bamAxleSpacing::Dump(dbgDumpContext& os) const
{
   os << "Dump for bamAxleSpacing" << endl;
   os << "m_Measure    = " << m_Measure << endl;
   os << "m_MinSpacing = " << m_MinSpacing << endl;
   os << "m_MaxSpacing = " << m_MaxSpacing << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bamAxleSpacing::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bamAxleSpacing");

   bamAxleSpacing spacing(10,50,Bounded);
   TRY_TESTME( IsEqual( spacing.GetMinSpacing(),10.) );
   TRY_TESTME( IsEqual( spacing.GetMaxSpacing(),50.) );

   spacing.SetSpacing(Fixed,10);
   TRY_TESTME( IsEqual( spacing.GetMinSpacing(),10.) );
   TRY_TESTME( IsEqual( spacing.GetMaxSpacing(),10.) );

   spacing.SetSpacing(LowerBound,10);
   TRY_TESTME( IsEqual( spacing.GetMinSpacing(),10.) );
   TRY_TESTME( IsEqual( spacing.GetMaxSpacing()-1e5,Float64_Max-1e5) );

   spacing.SetSpacing(UpperBound,10);
   TRY_TESTME( IsEqual( spacing.GetMinSpacing(),0.) );
   TRY_TESTME( IsEqual( spacing.GetMaxSpacing(),10.) );

   TESTME_EPILOG("bamAxleSpacing");
}
#endif // _UNITTEST
