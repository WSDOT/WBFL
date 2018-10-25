///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2012  Washington State Department of Transportation
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
#include <Material\StressStrainCurve.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   matXStressStrainEvalError
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
matXStressStrainEvalError::matXStressStrainEvalError(Reason reason,
                                                     LPCTSTR file,
                                                     Int16 line) :
sysXBase( file, line ),
m_Reason( reason )
{
}


matXStressStrainEvalError::matXStressStrainEvalError(const matXStressStrainEvalError& rOther) :
sysXBase( rOther )
{
   m_Reason = rOther.m_Reason;
}

matXStressStrainEvalError::~matXStressStrainEvalError()
{
}

//======================== OPERATORS  =======================================
matXStressStrainEvalError& matXStressStrainEvalError::operator= (const matXStressStrainEvalError& rOther)
{
   if( this != &rOther )
   {
      sysXBase::operator=(rOther);
      m_Reason          = rOther.m_Reason;
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void matXStressStrainEvalError::Throw() const
{
   throw *static_cast<const matXStressStrainEvalError*>(this);
}

Int32 matXStressStrainEvalError::GetReason() const
{
   return m_Reason;
}

matXStressStrainEvalError::Reason matXStressStrainEvalError::GetReasonCode() const
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


/****************************************************************************
CLASS
   matStressStrainCurve
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
matStressStrainCurve::matStressStrainCurve() :
m_Name( _T("Unknown") ),
m_FractureStrain( 0 ),
m_FractureStress( 0 ),
m_CrushingStrain( 0 ),
m_CrushingStress( 0 )
{
   ASSERTVALID;
}

matStressStrainCurve::matStressStrainCurve(const std::_tstring& name,
                                           Float64 fractureStrain,
                                           Float64 fractureStress,
                                           Float64 crushingStrain,
                                           Float64 crushingStress) :
m_Name( name ),
m_FractureStrain( fractureStrain ),
m_FractureStress( fractureStress ),
m_CrushingStrain( crushingStrain ),
m_CrushingStress( crushingStress )
{
   ASSERTVALID;
}

matStressStrainCurve::matStressStrainCurve(const matStressStrainCurve& rOther)
{
   MakeCopy(rOther);
}

matStressStrainCurve::~matStressStrainCurve()
{
}

//======================== OPERATORS  =======================================
matStressStrainCurve& matStressStrainCurve::operator= (const matStressStrainCurve& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void matStressStrainCurve::SetName(const std::_tstring& name)
{
   m_Name = name;
}

std::_tstring matStressStrainCurve::GetName() const
{
   return m_Name;
}

Float64 matStressStrainCurve::GetFractureStrain() const
{
   return m_FractureStrain;
}

Float64 matStressStrainCurve::GetFractureStress() const
{
   return m_FractureStress;
}

Float64 matStressStrainCurve::GetCrushingStrain() const
{
   return m_CrushingStrain;
}

Float64 matStressStrainCurve::GetCrushingStress() const
{
   return m_CrushingStress;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool matStressStrainCurve::AssertValid() const
{
   if ( m_CrushingStress > 0 || m_CrushingStrain > 0 )
      return false;

   if ( m_FractureStress < 0 || m_FractureStrain < 0 )
      return false;

   return true;
}

void matStressStrainCurve::Dump(dbgDumpContext& os) const
{
   os << "Dump for matStressStrainCurve" << endl;
   os << "=============================" << endl;
   os << "Name            : " << m_Name.c_str() << endl;
   os << "Crushing Strain : " << m_CrushingStrain << endl;
   os << "Crushing Stress : " << m_CrushingStress << endl;
   os << "Fracture Strain : " << m_FractureStrain << endl;
   os << "Fracture Stress : " << m_FractureStress << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool matStressStrainCurve::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("matStressStrainCurve");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for matStressStrainCurve");
   TESTME_EPILOG("matStressStrainCurve");
}
#endif // _UNITTEST

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void matStressStrainCurve::MakeCopy(const matStressStrainCurve& rOther)
{
   m_Name           = rOther.m_Name;
   m_FractureStrain = rOther.m_FractureStrain;
   m_FractureStress = rOther.m_FractureStress;
   m_CrushingStrain = rOther.m_CrushingStrain;
   m_CrushingStress = rOther.m_CrushingStress;

   ASSERTVALID;
}

void matStressStrainCurve::MakeAssignment(const matStressStrainCurve& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================

void matStressStrainCurve::SetFractureStrain(Float64 trs)
{
   PRECONDITION( trs >= 0 );
   m_FractureStrain = trs;
}

void matStressStrainCurve::SetFractureStress(Float64 trs)
{
   PRECONDITION( trs >= 0 );
   m_FractureStress = trs;
}

void matStressStrainCurve::SetCrushingStrain(Float64 crs)
{
   PRECONDITION( crs <= 0 );
   m_CrushingStrain = crs;
}

void matStressStrainCurve::SetCrushingStress(Float64 crs)
{
   PRECONDITION( crs <= 0 );
   m_CrushingStress = crs;
}

//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


