///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysLib.h>

/****************************************************************************
CLASS
   sysXStructuredSave
****************************************************************************/

#include <System\XStructuredSave.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
sysXStructuredSave::sysXStructuredSave(sysXStructuredSave::Reason reason,
                                       const char* file, Int16 line) :
sysXBase(file,line),
m_Reason(reason)
{
}

sysXStructuredSave::sysXStructuredSave(const sysXStructuredSave& rOther) :
sysXBase(rOther)
{
   MakeCopy(rOther);
}

sysXStructuredSave::~sysXStructuredSave()
{
}

//======================== OPERATORS  =======================================
sysXStructuredSave& sysXStructuredSave::operator= (const sysXStructuredSave& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void sysXStructuredSave::Throw() const
{
   throw *this; //*static_cast<const sysXStructuredSave*>(this);
}

Int32 sysXStructuredSave::GetReason() const
{
   return m_Reason;
}

sysXStructuredSave::Reason sysXStructuredSave::GetExplicitReason() const
{
   return m_Reason;
}

void sysXStructuredSave::GetErrorMessage(std::string* pMsg) const
{
   sysXBase::GetErrorMessage(pMsg);

   switch (m_Reason)
   {
   case (BadWrite):
      *pMsg += "A unknown error occured writing to the file\n";
      break;
   case (sysXStructuredSave::CantInitializeTheParser):
      *pMsg += "Could not initialize the parser. Perhaps the parser component is not installed\n";
      break;
   default:
      *pMsg += "Unknown error saving structured data\n";
      break;
   }
   *pMsg += "\n";
   *pMsg +=m_ExtendedMessage;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void sysXStructuredSave::MakeCopy(const sysXStructuredSave& rOther)
{
   m_Reason          = rOther.m_Reason;
}

void sysXStructuredSave::MakeAssignment(const sysXStructuredSave& rOther)
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

//======================== DEBUG      =======================================

