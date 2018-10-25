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
#include <Lrfd\XRangeOfApplicability.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdXRangeOfApplicability
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdXRangeOfApplicability::lrfdXRangeOfApplicability(Reason reason,const char* msg,const char* file, long line) :
sysXBase( file, line ),
m_Reason( reason ),
m_Message( msg )
{
}

lrfdXRangeOfApplicability::lrfdXRangeOfApplicability(const lrfdXRangeOfApplicability& rOther) :
sysXBase(rOther)
{
   MakeCopy(rOther);
}

lrfdXRangeOfApplicability::~lrfdXRangeOfApplicability()
{
}

//======================== OPERATORS  =======================================
lrfdXRangeOfApplicability& lrfdXRangeOfApplicability::operator= (const lrfdXRangeOfApplicability& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void lrfdXRangeOfApplicability::GetErrorMessage(std::string* pMsg) const
{
   *pMsg = m_Message;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdXRangeOfApplicability::MakeCopy(const lrfdXRangeOfApplicability& rOther)
{
   m_Reason = rOther.m_Reason;
   m_Message = rOther.m_Message;
}

void lrfdXRangeOfApplicability::MakeAssignment(const lrfdXRangeOfApplicability& rOther)
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

