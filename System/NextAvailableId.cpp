///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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
   sysNextAvailableId           
****************************************************************************/

#include <System\NextAvailableId.h>  // class implementation

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

sysNextAvailableId::sysNextAvailableId() :
m_IdOverflowThreshold(Int32_Max)
{
   m_NextAvailableId = -1;
} // sysNextAvailableId

sysNextAvailableId::~sysNextAvailableId()
{
} // ~sysNextAvailableId

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
Int32 sysNextAvailableId::ReserveNextId()
{
   if ( !AreThereMore() )
   {
      // :TODO: rab 03.14.97: This is a runtime error state, thrown an exception
      // :METHOD: NextAvailableId::ReserveNextId()
      //
      // There are no more id's and the user has requested a new one.
      return -1;
   }

   return ++m_NextAvailableId;
}

void sysNextAvailableId::ReserveSequence(Int32 startId,Int32 endId)
{
   PRECONDITIONX(startId < endId,_T("Start must be less than end"));

   if ( IsUsed(startId) || IsUsed(endId) )
   {
      // :TODO: rab 03.14.97: This is a runtime error state, thrown an exception
      // :METHOD: NextAvailableId::ReserveSequence()
      //
      // Part of the requested sequence is used.
      CHECKX(false,_T("Part of the requested sequence is used"));
   }

   UsingId( endId );
}

void sysNextAvailableId::UsingId(Int32 id)
{
   if ( m_NextAvailableId <= id )
      m_NextAvailableId = id;
}

void sysNextAvailableId::RestoreId(Int32 /*id*/)
{
   // Do nothing.
   // In the current implementation, once an id is reserved, it
   // is used forever.
}

void sysNextAvailableId::Reset()
{
   m_NextAvailableId = -1;
}

//======================== ACCESS     =======================================
Int32 sysNextAvailableId::LargestedUsed() const
{
   return m_NextAvailableId;
}

bool sysNextAvailableId::IsUsed(Int32 id) const
{
   return (id < m_NextAvailableId) ? true : false;
}

bool sysNextAvailableId::AreThereMore() const
{
   // Return false if m_NextAvailablePoint will overflow if incremented
   return (m_NextAvailableId == m_IdOverflowThreshold) ? false : true;
}

//======================== INQUIRY    =======================================

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
//======================== INQUERY ==========================================
