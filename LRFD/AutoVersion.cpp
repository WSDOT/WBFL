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
#include <Lrfd\AutoVersion.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdAutoVersion
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdAutoVersion::lrfdAutoVersion()
{
   m_Version = lrfdVersionMgr::GetVersion();
   m_Units   = lrfdVersionMgr::GetUnits();
}

lrfdAutoVersion::lrfdAutoVersion(lrfdVersionMgr::Version v, lrfdVersionMgr::Units u)
{
   m_Version = v;
   m_Units   = u;
}

lrfdAutoVersion::lrfdAutoVersion(const lrfdAutoVersion& rOther)
{
   MakeCopy(rOther);
}

lrfdAutoVersion::~lrfdAutoVersion()
{
   lrfdVersionMgr::BeginDamage();
   lrfdVersionMgr::SetVersion( m_Version );
   lrfdVersionMgr::SetUnits( m_Units );
   lrfdVersionMgr::EndDamage();
}

//======================== OPERATORS  =======================================
lrfdAutoVersion& lrfdAutoVersion::operator= (const lrfdAutoVersion& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void lrfdAutoVersion::SetVersion(lrfdVersionMgr::Version v)
{
   m_Version = v;
}

void lrfdAutoVersion::SetUnits(lrfdVersionMgr::Units u)
{
   m_Units = u;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdAutoVersion::AssertValid() const
{
   return true;
}

void lrfdAutoVersion::Dump(dbgDumpContext& os) const
{
   os << "Dump for lrfdAutoVersion" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool lrfdAutoVersion::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdAutoVersion");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for lrfdAutoVersion");
   TESTME_EPILOG("lrfdAutoVersion");
}
#endif // _UNITTEST

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdAutoVersion::MakeCopy(const lrfdAutoVersion& rOther)
{
   m_Version = rOther.m_Version;
   m_Units   = rOther.m_Units;
}

void lrfdAutoVersion::MakeAssignment(const lrfdAutoVersion& rOther)
{
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


