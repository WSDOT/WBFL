///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <Cogo\CogoLib.h>

/****************************************************************************
CLASS
   cogoCurve
****************************************************************************/

#include <Cogo\Curve.h>
#include <Cogo\Engine.h>
#include <GeometricPrimitives\Primitives3d.h>
#include <GeometricPrimitives\Vector3d.h>
#include <GeometricPrimitives\GeomOp2d.h>
#include <MathEx.h>

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
cogoCurve::cogoCurve()
{
}

cogoCurve::cogoCurve(const gpPoint2d& pc,const gpPoint2d& pi,const gpPoint2d& pt, const gpPoint2d& cc)
{
   m_PC = pc;
   m_PI = pi;
   m_PT = pt;
   m_CC = cc;
}

cogoCurve::cogoCurve(const cogoDirection& bkBrg,const cogoDirection& fwdBrg,const gpPoint2d& pi,Float64 radius)
{
   cogoAngle delta = fwdBrg - bkBrg;
   Int16 sign = (delta.AsFloat64() > M_PI ? -1 : 1 );
   if ( delta.AsFloat64() > M_PI )
      delta = TWO_PI - delta.AsFloat64();

   // Tangent distance
   Float64 T = radius * tan( delta.AsFloat64()/2 );

   m_PI = pi;
   m_PC = cogoEngine::LocateByDistDir(pi,T,bkBrg+cogoAngle(180,0,0));
   m_PT = cogoEngine::LocateByDistDir(pi,T,fwdBrg);
   m_CC = cogoEngine::LocateByDistDir(m_PC,radius,bkBrg+cogoAngle(sign*90,0,0));
}

cogoCurve::cogoCurve(const cogoCurve& rOther)
{
   MakeCopy(rOther);
}

cogoCurve::~cogoCurve()
{
}

//======================== OPERATORS  =======================================
cogoCurve& cogoCurve::operator= (const cogoCurve& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void cogoCurve::SetPC(const gpPoint2d& pc)
{
   m_PC = pc;
}

gpPoint2d cogoCurve::GetPC() const
{
   return m_PC;
}

void cogoCurve::SetPI(const gpPoint2d& pi)
{
   m_PI = pi;
}

gpPoint2d cogoCurve::GetPI() const
{
   return m_PI;
}

void cogoCurve::SetPT(const gpPoint2d& pt)
{
   m_PT = pt;
}

gpPoint2d cogoCurve::GetPT() const
{
   return m_PT;
}

void cogoCurve::SetCC(const gpPoint2d& cc)
{
   m_CC = cc;
}

gpPoint2d cogoCurve::GetCC() const
{
   return m_CC;
}

Float64 cogoCurve::GetL() const
{
   cogoAngle delta = GetDelta();
   Float64 r  = GetR();
   Float64 L = r * delta.AsFloat64();
   return L;
}

Float64 cogoCurve::GetT() const
{
   Float64 t = m_PI.Distance(m_PC);

#if defined _DEBUG
   Float64 t2 = m_PI.Distance(m_PT);
   CHECK( IsEqual(t,t2) );
#endif

   return t;
}

Float64 cogoCurve::GetE() const
{
   Float64 r = GetR();
   cogoAngle delta = GetDelta();
   Float64 e = r/cos(delta.AsFloat64()/2) - r;
   return e;
}

Float64 cogoCurve::GetC() const
{
   Float64 r = GetR();
   cogoAngle delta = GetDelta();
   Float64 c = 2*r*sin(delta.AsFloat64()/2);
   return c;
}

Float64 cogoCurve::GetMO() const
{
   Float64 r = GetR();
   cogoAngle delta = GetDelta();
   Float64 mo = r*(1-cos(delta.AsFloat64()/2));
   return mo;
}

cogoAngle cogoCurve::GetDC() const
{
   return GetDelta()/2;
}

cogoAngle cogoCurve::GetDelta() const
{
   Float64 t = GetT();
   Float64 r = GetR();
   Float64 delta  = 2*atan2(t,r);
   return cogoAngle(delta);
}

Float64 cogoCurve::GetR() const
{
   Float64 r = m_PC.Distance(m_CC);

#if defined _DEBUG
   Float64 r2 = m_PT.Distance(m_CC);
   CHECK( IsEqual(r,r2) );
#endif

   return r;
}

cogoDirection cogoCurve::GetBackTangent() const
{
   cogoDirection dir;
   Float64 dist;
   cogoEngine::Inverse(&dist,&dir,m_PC,m_PI);
   return dir;
}

cogoDirection cogoCurve::GetAheadTangent() const
{
   cogoDirection dir;
   Float64 dist;
   cogoEngine::Inverse(&dist,&dir,m_PI,m_PT);
   return dir;
}

gpLine2d::Side cogoCurve::GetDirection() const
{
   // Bk Tangent
   Float64 dist;
   cogoDirection bk;
   cogoEngine::Inverse(&dist,&bk,m_PC,m_PI);

   // Fwd Tangent
   cogoDirection fwd;
   cogoEngine::Inverse(&dist,&fwd,m_PI,m_PT);

   cogoAngle delta = fwd - bk;
   gpLine2d::Side side = (delta.AsFloat64() > M_PI ? gpLine2d::Left : gpLine2d::Right);

   return side;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void cogoCurve::MakeCopy(const cogoCurve& rOther)
{
   m_PC = rOther.m_PC;
   m_PI = rOther.m_PI;
   m_PT = rOther.m_PT;
   m_CC = rOther.m_CC;
}

void cogoCurve::MakeAssignment(const cogoCurve& rOther)
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

//======================== DEBUG      =======================================
#if defined _DEBUG
bool cogoCurve::AssertValid() const
{
   return true;
}

void cogoCurve::Dump(dbgDumpContext& os) const
{
   os << "Dump for cogoCurve - Not Implemented" << endl;
   os << "PC" << endl;
   m_PC.Dump(os);
   os << "PI" << endl;
   m_PI.Dump(os);
   os << "PT" << endl;
   m_PT.Dump(os);
   os << "CC" << endl;
   m_CC.Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool cogoCurve::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("cogoCurve");
#pragma Reminder("Implement Unit Tests")
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for cogoCurve");
   TESTME_EPILOG("cogoCurve");
}
#endif