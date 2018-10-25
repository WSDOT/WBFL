///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
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

#include <ReinforcedConcrete\ReinfConcLib.h>
#include <ReinforcedConcrete\WhitneyCapacityProblem.h>

#include <Material\Concrete.h>
#include <Material\Metal.h>
#include <Material\PsStrand.h>
#include <Material\PsStrandCurve.h>
#include <Material\YieldStressStrainCurve.h>
#include <Material\LinearStressStrainCurve.h>
#include <Lrfd\ConcreteUtil.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rcaWhitneyCapacityProblem
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rcaWhitneyCapacityProblem::rcaWhitneyCapacityProblem() :
rcaCapacityProblem()
{
   Init();
}

rcaWhitneyCapacityProblem::rcaWhitneyCapacityProblem(const rcaWhitneyCapacityProblem& rOther) :
rcaCapacityProblem(rOther)
{
   Init();
   MakeCopy(rOther);
}

rcaWhitneyCapacityProblem::~rcaWhitneyCapacityProblem()
{
   Clean();
}

//======================== OPERATORS  =======================================
rcaWhitneyCapacityProblem& rcaWhitneyCapacityProblem::operator= (const rcaWhitneyCapacityProblem& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

Float64 rcaWhitneyCapacityProblem::GetBeta1() const
{
   // take average beta 1
   gpLine2d na_line;
   GetNeutralAxisLocation(&na_line);

   Float64 mom=0.0, area=0.0;
   Int32 numconc = GetNumConcretes();
   for (Int32 ic=0; ic<numconc; ic++)
   {
      Float64 fc = GetConcrete(ic).GetFc();
      Float64 a  = GetClippedConcreteArea(ic, na_line, gpLine2d::Right);
      Float64 B1 = lrfdConcreteUtil::Beta1(fc);

      area += a * fc;
      mom  += a * fc * B1;
   }

   // If the location of the neutral axis line is such that it falls
   // on the extreme fiber in compression, "area" will be zero. When
   // this happens, take beta1 to be zero.
   Float64 beta1 = 0.0;
   if ( area > 0.0 )
      beta1 = mom/area;

   return beta1;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool rcaWhitneyCapacityProblem::AssertValid() const
{
   return rcaCapacityProblem::AssertValid();
}

void rcaWhitneyCapacityProblem::Dump(dbgDumpContext& os) const
{
   rcaCapacityProblem::Dump( os );
}
#endif // _DEBUG


#if defined _UNITTEST
bool rcaWhitneyCapacityProblem::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("rcaWhitneyCapacityProblem");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for rcaWhitneyCapacityProblem");
   TESTME_EPILOG("rcaWhitneyCapacityProblem");
}
#endif

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

matYieldStressStrainCurve* rcaWhitneyCapacityProblem::DoCreateMildSteelMaterialModel(const matMetal& steel)
{
   matLinearStressStrainCurve* tp = new matLinearStressStrainCurve(steel);
   tp->SetTensUltStrain(Float64_Max);
   tp->SetCompUltStrain(-Float64_Max);
   return tp;
}

matYieldStressStrainCurve* rcaWhitneyCapacityProblem::DoCreateStrandMaterialModel(const matPsStrand& strand)
{
   
   return new matPsStrandCurve(strand);
}

Float64 rcaWhitneyCapacityProblem::DoCalculateCompressionBlockBoundary()
{
   Float64 cbo;
   Float64 dist = GetFurthestDistance();
   if (dist>0)
   {
      Float64 beta1 = GetBeta1();
      cbo = dist*(1.0-beta1);
   }
   else
   {
      // none of the section is left of the n.a.
      // no offset.
      cbo=0.0;
   }

   return cbo;
}


void rcaWhitneyCapacityProblem::MakeCopy(const rcaWhitneyCapacityProblem& rOther)
{
   // Add copy code here...
}

void rcaWhitneyCapacityProblem::MakeAssignment(const rcaWhitneyCapacityProblem& rOther)
{
   Clean();
   Init();

   rcaCapacityProblem::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rcaWhitneyCapacityProblem::Init()
{
   // Add initialization code here...
}

void rcaWhitneyCapacityProblem::Clean()
{
   // Add cleanup code here...
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


