///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2017  Washington State Department of Transportation
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
#include <Lrfd\XPsLosses.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdXPsLosses
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdXPsLosses::lrfdXPsLosses(Reason reason,
                             LPCTSTR file,
                             Int16 line) :
sysXBase(file,line),
m_Reason( reason )
{
}

lrfdXPsLosses::lrfdXPsLosses(const lrfdXPsLosses& rOther) :
sysXBase(rOther)
{
   MakeCopy(rOther);
}

lrfdXPsLosses::~lrfdXPsLosses()
{
}

//======================== OPERATORS  =======================================
lrfdXPsLosses& lrfdXPsLosses::operator= (const lrfdXPsLosses& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void lrfdXPsLosses::Throw() const
{
   throw *static_cast<const lrfdXPsLosses*>(this);
}

Int32 lrfdXPsLosses::GetReason() const
{
   return m_Reason;
}

lrfdXPsLosses::Reason lrfdXPsLosses::GetReasonCode() const
{
   return m_Reason;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdXPsLosses::AssertValid() const
{
   return true;
}

void lrfdXPsLosses::Dump(dbgDumpContext& os) const
{
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdXPsLosses::MakeCopy(const lrfdXPsLosses& rOther)
{
   m_Reason = rOther.m_Reason;
}

void lrfdXPsLosses::MakeAssignment(const lrfdXPsLosses& rOther)
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


