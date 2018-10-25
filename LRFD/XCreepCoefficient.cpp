///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <Lrfd\LrfdLib.h>

#include <Lrfd\XCreepCoefficient.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdXCreepCoefficient
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdXCreepCoefficient::lrfdXCreepCoefficient(Reason reason,
                                             LPCTSTR file,
                                             Int16 line) :
sysXBase(file,line),
m_Reason( reason )
{
}

lrfdXCreepCoefficient::lrfdXCreepCoefficient(const lrfdXCreepCoefficient& rOther) :
sysXBase(rOther)
{
   MakeCopy(rOther);
}

lrfdXCreepCoefficient::~lrfdXCreepCoefficient()
{
}

//======================== OPERATORS  =======================================
lrfdXCreepCoefficient& lrfdXCreepCoefficient::operator= (const lrfdXCreepCoefficient& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void lrfdXCreepCoefficient::Throw() const
{
   throw *static_cast<const lrfdXCreepCoefficient*>(this);
}

Int32 lrfdXCreepCoefficient::GetReason() const
{
   return m_Reason;
}

lrfdXCreepCoefficient::Reason lrfdXCreepCoefficient::GetReasonCode() const
{
   return m_Reason;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdXCreepCoefficient::AssertValid() const
{
   return true;
}

void lrfdXCreepCoefficient::Dump(dbgDumpContext& os) const
{
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdXCreepCoefficient::MakeCopy(const lrfdXCreepCoefficient& rOther)
{
   m_Reason = rOther.m_Reason;
}

void lrfdXCreepCoefficient::MakeAssignment(const lrfdXCreepCoefficient& rOther)
{
   sysXBase::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


