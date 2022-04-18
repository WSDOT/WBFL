///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysLib.h>

/****************************************************************************
CLASS
   sysXProgrammingError
****************************************************************************/

#include <System\XProgrammingError.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
sysXProgrammingError::sysXProgrammingError(Reason reason, LPCTSTR file, Int32 line) :
sysXBase(file,line),
m_Reason( reason )
{
}

sysXProgrammingError::sysXProgrammingError(const sysXProgrammingError& rOther) :
sysXBase(rOther)
{
   MakeCopy(rOther);
}

sysXProgrammingError::~sysXProgrammingError()
{
}

//======================== OPERATORS  =======================================
sysXProgrammingError& sysXProgrammingError::operator= (const sysXProgrammingError& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void sysXProgrammingError::Throw() const
{
   throw *static_cast<const sysXProgrammingError*>(this);
}

//======================== ACCESS     =======================================
Int32 sysXProgrammingError::GetReason() const
{
   return m_Reason;
}

sysXProgrammingError::Reason sysXProgrammingError::GetReasonCode() const
{
   return m_Reason;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void sysXProgrammingError::MakeCopy(const sysXProgrammingError& rOther)
{
   m_Reason = rOther.m_Reason;
}

void sysXProgrammingError::MakeAssignment(const sysXProgrammingError& rOther)
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


