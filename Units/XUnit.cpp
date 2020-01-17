///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2020  Washington State Department of Transportation
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
#include <Units\XUnit.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
CLASS
   unitXUnit
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
unitXUnit::unitXUnit(Reason reason,LPCTSTR file,Int16 line) :
sysXBase(file,line),
m_Reason( reason )
{
}

unitXUnit::unitXUnit(const unitXUnit& rOther) :
sysXBase(rOther)
{
   MakeCopy(rOther);
}

unitXUnit::~unitXUnit()
{
}

//======================== OPERATORS  =======================================
unitXUnit& unitXUnit::operator= (const unitXUnit& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void unitXUnit::Throw() const
{
   throw *static_cast<const unitXUnit*>(this);
}

Int32 unitXUnit::GetReason() const
{
   return m_Reason;
}

unitXUnit::Reason unitXUnit::GetReasonCode() const
{
   return m_Reason;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool unitXUnit::AssertValid() const
{
   return true; //sysXBase::AssertValid();
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void unitXUnit::MakeCopy(const unitXUnit& rOther)
{
   m_Reason = rOther.m_Reason;
}

void unitXUnit::MakeAssignment(const unitXUnit& rOther)
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


