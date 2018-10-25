///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2013  Washington State Department of Transportation
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

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfXBridgeModel
****************************************************************************/
#include <BridgeModeling\XBridgeModel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfXBridgeModel::bmfXBridgeModel(Reason reason,
                                 LPCTSTR file,
                                 Int16 line) :
sysXBase( file, line ),
m_Reason( reason )
{
}


bmfXBridgeModel::bmfXBridgeModel(const bmfXBridgeModel& rOther) :
sysXBase( rOther )
{
   m_Reason = rOther.m_Reason;
}

bmfXBridgeModel::~bmfXBridgeModel()
{
}

//======================== OPERATORS  =======================================
bmfXBridgeModel& bmfXBridgeModel::operator= (const bmfXBridgeModel& rOther)
{
   if( this != &rOther )
   {
      sysXBase::operator=(rOther);
      m_Reason = rOther.m_Reason;
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void bmfXBridgeModel::Throw() const
{
   throw *static_cast<const bmfXBridgeModel*>(this);
}

Int32 bmfXBridgeModel::GetReason() const
{
   return m_Reason;
}

bmfXBridgeModel::Reason bmfXBridgeModel::GetReasonCode() const
{
   return m_Reason;
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
//======================== INQUERY    =======================================
//======================== DEBUG      =======================================
