///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2014  Washington State Department of Transportation
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

#include <Math\MathLib.h>
#include <Math\NumericIntegrator2d.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   mathXNumericIntegrator2dFailed
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
mathXNumericIntegrator2dFailed::mathXNumericIntegrator2dFailed(Reason reason,LPCTSTR file,Int16 line) :
sysXBase(file,line)
{
   m_Reason = reason;
}

mathXNumericIntegrator2dFailed::mathXNumericIntegrator2dFailed(const mathXNumericIntegrator2dFailed& rOther) :
sysXBase( rOther )
{
   m_Reason = rOther.m_Reason;
}

mathXNumericIntegrator2dFailed::~mathXNumericIntegrator2dFailed()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
mathXNumericIntegrator2dFailed& mathXNumericIntegrator2dFailed::operator=(const mathXNumericIntegrator2dFailed& rOther)
{
   if ( this != &rOther )
   {
      sysXBase::operator=( rOther);
      m_Reason = rOther.m_Reason;
   }

   return *this;
}

//======================== ACCESS     =======================================
void mathXNumericIntegrator2dFailed::Throw() const
{
   throw *static_cast<const mathXNumericIntegrator2dFailed*>(this);
}

Int32 mathXNumericIntegrator2dFailed::GetReason() const
{
   return m_Reason;
}

mathXNumericIntegrator2dFailed::Reason mathXNumericIntegrator2dFailed::GetReasonCode() const
{
   return m_Reason;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

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

