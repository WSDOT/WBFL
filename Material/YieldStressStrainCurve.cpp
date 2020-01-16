///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2020  Washington State Department of Transportation
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

#include <Material\MatLib.h>
#include <Material\YieldStressStrainCurve.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   matYieldStressStrainCurve
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
matYieldStressStrainCurve::matYieldStressStrainCurve() :
matStressStrainCurve(),
m_ModE( 1 ),
m_TensYieldStress( 0 ),
m_CompYieldStress( 0 ),
m_TensUltStrain( 0 ),
m_TensUltStress( 0 ),
m_CompUltStrain( 0 ),
m_CompUltStress( 0 ),
m_TensYieldStrain( 0 ),
m_CompYieldStrain( 0 )
{
   ASSERTVALID;
}

matYieldStressStrainCurve::matYieldStressStrainCurve(const std::_tstring& name,
                                                     Float64 E,
                                                     Float64 tensYieldStress,
                                                     Float64 compYieldStress,
                                                     Float64 tensUltStrain,
                                                     Float64 tensUltStress,
                                                     Float64 compUltStrain,
                                                     Float64 compUltStress,
                                                     Float64 fractureStrain,
                                                     Float64 fractureStress,
                                                     Float64 crushingStrain,
                                                     Float64 crushingStress) :
matStressStrainCurve(name,fractureStrain,fractureStress,crushingStrain,crushingStress),
m_ModE( E ),
m_TensYieldStress( tensYieldStress ),
m_CompYieldStress( compYieldStress ),
m_TensUltStrain( tensUltStrain ),
m_TensUltStress( tensUltStress ),
m_CompUltStrain( compUltStrain ),
m_CompUltStress( compUltStress )
{
   m_TensYieldStrain = m_TensYieldStress / m_ModE;
   m_CompYieldStrain = m_CompYieldStress / m_ModE;
   ASSERTVALID;
}

matYieldStressStrainCurve::matYieldStressStrainCurve(const matYieldStressStrainCurve& rOther) :
matStressStrainCurve(rOther)
{
   MakeCopy(rOther);
}

matYieldStressStrainCurve::~matYieldStressStrainCurve()
{
}

//======================== OPERATORS  =======================================
matYieldStressStrainCurve& matYieldStressStrainCurve::operator= (const matYieldStressStrainCurve& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
Float64 matYieldStressStrainCurve::GetE() const
{
   return m_ModE;
}

Float64 matYieldStressStrainCurve::GetTensYieldStrain() const
{
   return m_TensYieldStrain;
}

Float64 matYieldStressStrainCurve::GetTensYieldStress() const
{
   return m_TensYieldStress;
}

Float64 matYieldStressStrainCurve::GetCompYieldStrain() const
{
   return m_CompYieldStrain;
}

Float64 matYieldStressStrainCurve::GetCompYieldStress() const
{
   return m_CompYieldStress;
}

Float64 matYieldStressStrainCurve::GetTensUltStrain() const
{
   return m_TensUltStrain;
}

Float64 matYieldStressStrainCurve::GetTensUltStress() const
{
   return m_TensUltStress;
}

Float64 matYieldStressStrainCurve::GetCompUltStrain() const
{
   return m_CompUltStrain;
}

Float64 matYieldStressStrainCurve::GetCompUltStress() const
{
   return m_CompUltStress;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool matYieldStressStrainCurve::AssertValid() const
{
   if ( !matStressStrainCurve::AssertValid() )
      return false;

   if ( m_ModE <= 0 )
      return false;

   if ( m_CompUltStrain > 0 || m_CompUltStress > 0 )
      return false;

   if ( m_TensUltStrain < 0 || m_TensUltStress < 0 )
      return false;

   if ( m_CompYieldStress > 0 || m_TensYieldStress < 0 )
      return false;

   if ( m_TensUltStress < m_TensYieldStress ||
        m_TensUltStress < GetFractureStress() )
      return false;

   if ( m_CompUltStress > m_CompYieldStress ||
        m_CompUltStress > GetCrushingStress() )
      return false;

   if ( GetFractureStrain() < m_TensUltStrain )
      return false;

   if ( GetCrushingStrain() > m_CompUltStrain )
      return false;

   if ( !IsEqual( m_TensYieldStrain, m_TensYieldStress/m_ModE ) )
      return false;

   if ( !IsEqual( m_CompYieldStrain, m_CompYieldStress/m_ModE ) )
      return false;

   return true;
}

void matYieldStressStrainCurve::Dump(dbgDumpContext& os) const
{
   os << "Dump for matYieldStressStrainCurve" << endl;
   os << "==================================" << endl;
   matStressStrainCurve::Dump( os );
   os << "==================================" << endl;
   os << "Mod E           : " << m_ModE            << endl;
   os << "CompYieldStress : " << m_CompYieldStress << endl;
   os << "CompUltStrain   : " << m_CompUltStrain   << endl;
   os << "CompUltStress   : " << m_CompUltStress   << endl;
   os << "TensYieldStress : " << m_TensYieldStress << endl;
   os << "TensUltStrain   : " << m_TensUltStrain   << endl;
   os << "TensUltStress   : " << m_TensUltStress   << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool matYieldStressStrainCurve::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("matYieldStressStrainCurve");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for matYieldStressStrainCurve");
   TESTME_EPILOG("matYieldStressStrainCurve");
}
#endif // _UNITTEST

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void matYieldStressStrainCurve::MakeCopy(const matYieldStressStrainCurve& rOther)
{
   m_ModE            = rOther.m_ModE;
   m_TensYieldStress = rOther.m_TensYieldStress;
   m_CompYieldStress = rOther.m_CompYieldStress;
   m_TensUltStrain   = rOther.m_TensUltStrain;
   m_TensUltStress   = rOther.m_TensUltStress;
   m_CompUltStrain   = rOther.m_CompUltStrain;
   m_CompUltStress   = rOther.m_CompUltStress;
   m_TensYieldStrain = rOther.m_TensYieldStrain;
   m_CompYieldStrain = rOther.m_CompYieldStrain;

   ASSERTVALID;
}

void matYieldStressStrainCurve::MakeAssignment(const matYieldStressStrainCurve& rOther)
{
   matStressStrainCurve::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================

void matYieldStressStrainCurve::SetE(Float64 E)
{
   PRECONDITION( E > 0 );
   m_ModE = E;
   m_TensYieldStrain = m_TensYieldStress / m_ModE;
   m_CompYieldStrain = m_CompYieldStress / m_ModE;
}

void matYieldStressStrainCurve::SetTensYieldStress(Float64 tys)
{
   PRECONDITION( tys >= 0 );
   m_TensYieldStress = tys;
   m_TensYieldStrain = m_TensYieldStress / m_ModE;
}

void matYieldStressStrainCurve::SetCompYieldStress(Float64 cys)
{
   PRECONDITION( cys <= 0 );
   m_CompYieldStress = cys;
   m_CompYieldStrain = m_CompYieldStress / m_ModE;
}

void matYieldStressStrainCurve::SetTensUltStrain(Float64 tys)
{
   PRECONDITION( tys >= 0 );
   m_TensUltStrain = tys;
}

void matYieldStressStrainCurve::SetTensUltStress(Float64 tys)
{
   PRECONDITION( tys >= 0 );
   m_TensUltStress = tys;
}

void matYieldStressStrainCurve::SetCompUltStrain(Float64 cys)
{
   PRECONDITION( cys <= 0 );
   m_CompUltStrain = cys;
}

void matYieldStressStrainCurve::SetCompUltStress(Float64 cys)
{
   PRECONDITION( cys <= 0 );
   m_CompUltStress = cys;
}

//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


