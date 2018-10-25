///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2011  Washington State Department of Transportation
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
   sysXBase
****************************************************************************/

#include <System\Exception.h>
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
sysXBase::sysXBase(LPCTSTR file, Int32 line ) :
m_File( file ),
m_Line( line )
{
}

sysXBase::sysXBase(const sysXBase& rOther)
{
   MakeCopy(rOther);
}

sysXBase::~sysXBase()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void sysXBase::GetErrorMessage(std::_tstring* pMsg) const
{
   const type_info& ti = typeid(*this);
   std::_tostringstream os;
   os << "A " << ti.name() << " error, number " << GetReason()
      << ", has occurred in " << GetFile() << " at line " << GetLine() << std::endl;
   *pMsg = os.str();
}

LPCTSTR sysXBase::GetFile() const
{
   return m_File.c_str();
}

Int32 sysXBase::GetLine() const
{
   return m_Line;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
sysXBase& sysXBase::operator= (const sysXBase& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void sysXBase::MakeCopy(const sysXBase& rOther)
{
   m_File = rOther.m_File;
   m_Line = rOther.m_Line;
}

void sysXBase::MakeAssignment(const sysXBase& rOther)
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


