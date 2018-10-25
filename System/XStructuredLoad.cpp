///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2015  Washington State Department of Transportation
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
   sysXStructuredLoad
****************************************************************************/

#include <System\XStructuredLoad.h>

#ifdef _DEBUG
#if defined(_AFX_NO_DEBUG_CRT)
#pramga message("WARNING - Memory debugging disabled")
#endif
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
sysXStructuredLoad::sysXStructuredLoad(sysXStructuredLoad::Reason reason,
                                       LPCTSTR file, Int16 line) :
sysXBase(file,line),
m_Reason(reason)
{
}

sysXStructuredLoad::sysXStructuredLoad(const sysXStructuredLoad& rOther) :
sysXBase(rOther)
{
   MakeCopy(rOther);
}

sysXStructuredLoad::~sysXStructuredLoad()
{
}

//======================== OPERATORS  =======================================
sysXStructuredLoad& sysXStructuredLoad::operator= (const sysXStructuredLoad& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void sysXStructuredLoad::Throw() const
{
   throw *this; //*static_cast<const sysXStructuredLoad*>(this);
}

Int32 sysXStructuredLoad::GetReason() const
{
   return m_Reason;
}

sysXStructuredLoad::Reason sysXStructuredLoad::GetExplicitReason() const
{
   return m_Reason;
}

void sysXStructuredLoad::GetErrorMessage(std::_tstring* pMsg) const
{
   sysXBase::GetErrorMessage(pMsg);

   switch (m_Reason)
   {
   case (sysXStructuredLoad::InvalidFileFormat):
      *pMsg += _T("File format was invalid\n");
      break;
   case (sysXStructuredLoad::EndOfFile):
      *pMsg += _T("Unexpected end of file\n");
      break;
   case (sysXStructuredLoad::BadRead):
      *pMsg += _T("Unexpected error trying to read file\n");
      break;
   case (sysXStructuredLoad::BadVersion):
      *pMsg += _T("Unexpected version number reading structured data\n");
      break;
   case (sysXStructuredLoad::MemoryError):
      *pMsg += _T("Memory allocation error during structured read\n");
      break;
   case (sysXStructuredLoad::CantInitializeTheParser):
      *pMsg += _T("Could not initialize the parser. Perhaps the parser component is not installed\n");
      break;
   default:
      *pMsg += _T("Unknown error reading structured data\n");
      break;
   }
   *pMsg += _T("\n");
   *pMsg +=m_ExtendedMessage;
}

void sysXStructuredLoad::SetExtendedMessage(LPCTSTR msg)
{
   m_ExtendedMessage = std::_tstring(msg);
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void sysXStructuredLoad::MakeCopy(const sysXStructuredLoad& rOther)
{
   m_Reason          = rOther.m_Reason;
   m_ExtendedMessage = rOther.m_ExtendedMessage;
}

void sysXStructuredLoad::MakeAssignment(const sysXStructuredLoad& rOther)
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

