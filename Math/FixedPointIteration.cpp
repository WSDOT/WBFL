///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
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

#include <Math\MathLib.h>
#include <Math\FixedPointIteration.h>
#include <xutility>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   mathXFixedPointIterationFailed
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
mathXFixedPointIterationFailed::mathXFixedPointIterationFailed(Reason reason,Float64 last,LPCTSTR file,Int16 line) :
   WBFL::System::XBase(file,line)
{
   m_Reason = reason;
   m_Last = last;
}

mathXFixedPointIterationFailed::mathXFixedPointIterationFailed(const mathXFixedPointIterationFailed& rOther) :
   WBFL::System::XBase( rOther )
{
   m_Reason = rOther.m_Reason;
   m_Last = rOther.m_Last;
}

mathXFixedPointIterationFailed::~mathXFixedPointIterationFailed()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
mathXFixedPointIterationFailed& mathXFixedPointIterationFailed::operator=(const mathXFixedPointIterationFailed& rOther)
{
   if ( this != &rOther )
   {
      WBFL::System::XBase::operator=( rOther);
      m_Reason = rOther.m_Reason;
      m_Last = rOther.m_Last;
   }

   return *this;
}

//======================== ACCESS     =======================================
void mathXFixedPointIterationFailed::Throw() const
{
   throw *static_cast<const mathXFixedPointIterationFailed*>(this);
}

Float64 mathXFixedPointIterationFailed::GetLast() const
{
   return m_Last;
}

Int32 mathXFixedPointIterationFailed::GetReason() const noexcept
{
   return m_Reason;
}

mathXFixedPointIterationFailed::Reason mathXFixedPointIterationFailed::GetReasonCode() const noexcept
{
   return m_Reason;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

/****************************************************************************
CLASS
   mathFixedPointIteration
****************************************************************************/
////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
mathFixedPointIteration::mathFixedPointIteration()
{
}


mathFixedPointIteration::~mathFixedPointIteration()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

Float64 mathFixedPointIteration::Solve(const mathFunction2d& eval,Float64 xo,Float64 tol,long maxIter)
{
   Float64 x = xo;
   for ( long i = 0; i < maxIter; i++ )
   {
      Float64 x1 = eval.Evaluate(x);
      if ( IsEqual(x1,x,tol) )
         return x1;

      x = x1;
   }

   mathXFixedPointIterationFailed mx(mathXFixedPointIterationFailed::MaxIterExceeded,x,_T(__FILE__),__LINE__);
   mx.Throw();
   return x;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool mathFixedPointIteration::AssertValid() const
{
   return true;
}

void mathFixedPointIteration::Dump(WBFL::Debug::LogContext& os) const
{
}
#endif // _DEBUG

#if defined _UNITTEST
bool mathFixedPointIteration::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("mathFixedPointIteration");
   // Unit Tests implemented on package level
   TESTME_EPILOG("mathFixedPointIteration");
}
#endif

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


