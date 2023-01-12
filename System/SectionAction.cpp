///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2023  Washington State Department of Transportation
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
   sysSectionAction
****************************************************************************/

#include <System\SectionAction.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
sysSectionAction::sysSectionAction(Float64 val)
{
   m_Fx = val;
   m_Fy = val;
   m_Mz = val;
   m_Dx = val;
   m_Dy = val;
   m_Rz = val;
}

sysSectionAction::sysSectionAction(const sysSectionAction& rOther)
{
   MakeCopy(rOther);
}

sysSectionAction::~sysSectionAction()
{
}

//======================== OPERATORS  =======================================
sysSectionAction& sysSectionAction::operator= (const sysSectionAction& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

sysSectionAction& sysSectionAction::operator=(const sysSectionValue& val)
{
   m_Fx = val;
   m_Fy = val;
   m_Mz = val;

   m_Dx = val;
   m_Dy = val;
   m_Rz = val;

   return *this;
}

sysSectionAction& sysSectionAction::operator=(Float64 val)
{
   m_Fx = val;
   m_Fy = val;
   m_Mz = val;

   m_Dx = val;
   m_Dy = val;
   m_Rz = val;

   return *this;
}

sysSectionAction& sysSectionAction::operator+=(const sysSectionAction& rOther)
{
   m_Fx += rOther.m_Fx;
   m_Fy += rOther.m_Fy;
   m_Mz += rOther.m_Mz;
   m_Dx += rOther.m_Dx;
   m_Dy += rOther.m_Dy;
   m_Rz += rOther.m_Rz;

   return *this;
}

sysSectionAction& sysSectionAction::operator-=(const sysSectionAction& rOther)
{
   m_Fx -= rOther.m_Fx;
   m_Fy -= rOther.m_Fy;
   m_Mz -= rOther.m_Mz;
   m_Dx -= rOther.m_Dx;
   m_Dy -= rOther.m_Dy;
   m_Rz -= rOther.m_Rz;

   return *this;
}

sysSectionAction& sysSectionAction::operator*=(const sysSectionAction& rOther)
{
   m_Fx *= rOther.m_Fx;
   m_Fy *= rOther.m_Fy;
   m_Mz *= rOther.m_Mz;
   m_Dx *= rOther.m_Dx;
   m_Dy *= rOther.m_Dy;
   m_Rz *= rOther.m_Rz;

   return *this;
}

sysSectionAction& sysSectionAction::operator/=(const sysSectionAction& rOther)
{
   m_Fx /= rOther.m_Fx;
   m_Fy /= rOther.m_Fy;
   m_Mz /= rOther.m_Mz;
   m_Dx /= rOther.m_Dx;
   m_Dy /= rOther.m_Dy;
   m_Rz /= rOther.m_Rz;

   return *this;
}

sysSectionAction sysSectionAction::operator-()
{
   sysSectionAction sa;
   sa.m_Fx = -m_Fx;
   sa.m_Fy = -m_Fy;
   sa.m_Mz = -m_Mz;
   sa.m_Dx = -m_Dx;
   sa.m_Dy = -m_Dy;
   sa.m_Rz = -m_Rz;

   return sa;
}

sysSectionAction& sysSectionAction::operator+=(Float64 val)
{
   m_Fx += val;
   m_Fy += val;
   m_Mz += val;
   m_Dx += val;
   m_Dy += val;
   m_Rz += val;

   return *this;
}

sysSectionAction& sysSectionAction::operator+=(const sysSectionValue& val)
{
   m_Fx += val;
   m_Fy += val;
   m_Mz += val;
   m_Dx += val;
   m_Dy += val;
   m_Rz += val;

   return *this;
}

sysSectionAction& sysSectionAction::operator-=(Float64 val)
{
   m_Fx -= val;
   m_Fy -= val;
   m_Mz -= val;
   m_Dx -= val;
   m_Dy -= val;
   m_Rz -= val;

   return *this;
}

sysSectionAction& sysSectionAction::operator-=(const sysSectionValue& val)
{
   m_Fx -= val;
   m_Fy -= val;
   m_Mz -= val;
   m_Dx -= val;
   m_Dy -= val;
   m_Rz -= val;

   return *this;
}

sysSectionAction& sysSectionAction::operator*=(Float64 val)
{
   m_Fx *= val;
   m_Fy *= val;
   m_Mz *= val;
   m_Dx *= val;
   m_Dy *= val;
   m_Rz *= val;

   return *this;
}

sysSectionAction& sysSectionAction::operator*=(const sysSectionValue& val)
{
   m_Fx *= val;
   m_Fy *= val;
   m_Mz *= val;
   m_Dx *= val;
   m_Dy *= val;
   m_Rz *= val;

   return *this;
}

sysSectionAction& sysSectionAction::operator/=(Float64 val)
{
   m_Fx /= val;
   m_Fy /= val;
   m_Mz /= val;
   m_Dx /= val;
   m_Dy /= val;
   m_Rz /= val;

   return *this;
}

sysSectionAction& sysSectionAction::operator/=(const sysSectionValue& val)
{
   m_Fx /= val;
   m_Fy /= val;
   m_Mz /= val;
   m_Dx /= val;
   m_Dy /= val;
   m_Rz /= val;

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
sysSectionValue& sysSectionAction::Fx()
{
   return m_Fx;
}

const sysSectionValue& sysSectionAction::Fx() const
{
   return m_Fx;
}

sysSectionValue& sysSectionAction::Fy()
{
   return m_Fy;
}

const sysSectionValue& sysSectionAction::Fy() const
{
   return m_Fy;
}

sysSectionValue& sysSectionAction::Mz()
{
   return m_Mz;
}

const sysSectionValue& sysSectionAction::Mz() const
{
   return m_Mz;
}

sysSectionValue& sysSectionAction::Dx()
{
   return m_Dx;
}

const sysSectionValue& sysSectionAction::Dx() const
{
   return m_Dx;
}

sysSectionValue& sysSectionAction::Dy()
{
   return m_Dy;
}

const sysSectionValue& sysSectionAction::Dy() const
{
   return m_Dy;
}

sysSectionValue& sysSectionAction::Rz()
{
   return m_Rz;
}

const sysSectionValue& sysSectionAction::Rz() const
{
   return m_Rz;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void sysSectionAction::MakeCopy(const sysSectionAction& rOther)
{
   // Add copy code here...
   m_Fx = rOther.m_Fx;
   m_Fy = rOther.m_Fy;
   m_Mz = rOther.m_Mz;
   m_Dx = rOther.m_Dx;
   m_Dy = rOther.m_Dy;
   m_Rz = rOther.m_Rz;
}

void sysSectionAction::MakeAssignment(const sysSectionAction& rOther)
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

SYSFUNC sysSectionAction operator+(const sysSectionAction& a,const sysSectionAction& b)
{
   sysSectionAction sa;
   sa.Fx() = a.Fx() + b.Fx();
   sa.Fy() = a.Fy() + b.Fy();
   sa.Mz() = a.Mz() + b.Mz();
   sa.Dx() = a.Dx() + b.Dx();
   sa.Dy() = a.Dy() + b.Dy();
   sa.Rz() = a.Rz() + b.Rz();
   return sa;
}

SYSFUNC sysSectionAction operator-(const sysSectionAction& a,const sysSectionAction& b)
{
   sysSectionAction sa;
   sa.Fx() = a.Fx() - b.Fx();
   sa.Fy() = a.Fy() - b.Fy();
   sa.Mz() = a.Mz() - b.Mz();
   sa.Dx() = a.Dx() - b.Dx();
   sa.Dy() = a.Dy() - b.Dy();
   sa.Rz() = a.Rz() - b.Rz();
   return sa;
}

SYSFUNC sysSectionAction operator*(const sysSectionAction& a,const sysSectionAction& b)
{
   sysSectionAction sa;
   sa.Fx() = a.Fx() * b.Fx();
   sa.Fy() = a.Fy() * b.Fy();
   sa.Mz() = a.Mz() * b.Mz();
   sa.Dx() = a.Dx() * b.Dx();
   sa.Dy() = a.Dy() * b.Dy();
   sa.Rz() = a.Rz() * b.Rz();
   return sa;
}

SYSFUNC sysSectionAction operator*(const sysSectionAction& a,const sysSectionValue& b)
{
   sysSectionAction sa;
   sa.Fx() = a.Fx() * b;
   sa.Fy() = a.Fy() * b;
   sa.Mz() = a.Mz() * b;
   sa.Dx() = a.Dx() * b;
   sa.Dy() = a.Dy() * b;
   sa.Rz() = a.Rz() * b;
   return sa;
}

SYSFUNC sysSectionAction operator*(const sysSectionValue& a,const sysSectionAction& b)
{
   return operator*(b,a);
}

SYSFUNC sysSectionAction operator/(const sysSectionAction& a,const sysSectionAction& b)
{
   sysSectionAction sa;
   sa.Fx() = a.Fx() / b.Fx();
   sa.Fy() = a.Fy() / b.Fy();
   sa.Mz() = a.Mz() / b.Mz();
   sa.Dx() = a.Dx() / b.Dx();
   sa.Dy() = a.Dy() / b.Dy();
   sa.Rz() = a.Rz() / b.Rz();
   return sa;
}

SYSFUNC std::_tostream& operator<<(std::_tostream& os,const sysSectionAction& a)
{
   os << _T("Fx = ") << a.Fx() << std::endl;
   os << _T("Fy = ") << a.Fy() << std::endl;
   os << _T("Mz = ") << a.Mz() << std::endl;
   os << _T("Dx = ") << a.Dx() << std::endl;
   os << _T("Dy = ") << a.Dy() << std::endl;
   os << _T("Rz = ") << a.Rz();

   return os;
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool sysSectionAction::AssertValid() const
{
   // Nothing to assert
   return true;
}

void sysSectionAction::Dump(dbgDumpContext& os) const
{
   os << "Dump for sysSectionAction" << endl;
//   os << "m_Fx = " << m_Fx << endl;
//   os << "m_Fy = " << m_Fy << endl;
//   os << "m_Mz = " << m_Mz << endl;
//   os << "m_Dx = " << m_Dx << endl;
//   os << "m_Dy = " << m_Dy << endl;
//   os << "m_Rz = " << m_Rz << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool sysSectionAction::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("sysSectionAction");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for sysSectionAction");

   TESTME_EPILOG("SectionAction");
}
#endif // _UNITTEST
