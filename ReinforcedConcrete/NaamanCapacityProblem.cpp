///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <ReinforcedConcrete\NaamanCapacityProblem.h>

#include <Material\Concrete.h>
#include <Lrfd\ConcreteUtil.h>
#include <GeomModel\Properties.h>
#include <Math\BrentsRootFinder2d.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rcaNaamanCapacityProblem
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rcaNaamanCapacityProblem::rcaNaamanCapacityProblem() :
rcaWhitneyCapacityProblem()
{
   Init();
}

rcaNaamanCapacityProblem::rcaNaamanCapacityProblem(const rcaNaamanCapacityProblem& rOther) :
rcaWhitneyCapacityProblem(rOther)
{
   Init();
   MakeCopy(rOther);
}

rcaNaamanCapacityProblem::~rcaNaamanCapacityProblem()
{
   Clean();
}

//======================== OPERATORS  =======================================
rcaNaamanCapacityProblem& rcaNaamanCapacityProblem::operator= (const rcaNaamanCapacityProblem& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool rcaNaamanCapacityProblem::AssertValid() const
{
   return rcaWhitneyCapacityProblem::AssertValid();
}

void rcaNaamanCapacityProblem::Dump(dbgDumpContext& os) const
{
   rcaWhitneyCapacityProblem::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
#include <Units\Units.h>
#include <Material\Material.h>
#include <GeometricPrimitives\GeometricPrimitives.h>
#include <GeomModel\GeomModel.h>
bool rcaNaamanCapacityProblem::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("rcaNaamanCapacityProblem");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for rcaNaamanCapacityProblem");

   // The purpose of this test is to determine of the Effective Compressive Area
   // is being computed correctly.
   matConcrete conc_4000(_T("4ksi Concrete"),
                          ::ConvertToSysUnits(4.,unitMeasure::KSI),
                          ::ConvertToSysUnits(150.,unitMeasure::PCF),
                          ::ConvertToSysUnits(3.7e6,unitMeasure::KSI));

   matMetal  rebar_60(_T("60ksi Rebar"), 
                      ::ConvertToSysUnits(490.,unitMeasure::PCF),
                      ::ConvertToSysUnits(29000.,unitMeasure::KSI),
                      ::ConvertToSysUnits(60.,unitMeasure::KSI));
   
   rcaNaamanCapacityProblem prob;
   CollectionIndexType conc_idx = prob.AddConcrete(conc_4000);
   CollectionIndexType rebar_idx = prob.AddMildSteel(rebar_60);

   //   Offset = 10
   //             .
   //            . .
   //           .   .
   //          .     .       Height = 50
   //         .       .      Width = 20
   // ------------------------ N/A at Y = 25
   //       .           .
   //      .             .
   //     .       o       .  // Rebar at (0,5)
   //    +-----------------+
   //   (-10,0) = Hook Point
   //
   gmTriangle shape(gpPoint2d(-10,0),50,20,10);
   prob.AddConcreteElement(shape,conc_idx,1.0);

   gmCircle circle(gpPoint2d(0,5),1);
   prob.AddReinforcementElement(circle,rebar_idx,0.0);

   gpLine2d na( gpPoint2d(-10,25), gpPoint2d(10,25) );
   prob.SetNeutralAxisLocation(na);

   Float64 cbb = prob.GetCompressionBlockBoundary();
   TRY_TESTME( IsEqual(cbb,1.9511,0.001) );

   Float64 beta1 = prob.GetBeta1();
   // total compression area above n.a.
   Float64 na_area = prob.GetCompressionArea();
   Float64 cb_area_check = beta1*na_area;

   // comp block area
   Float64 cb_area = prob.GetEffectiveCompressionArea();

   TRY_TESTME(IsEqual(cb_area_check,cb_area,0.001));
   TESTME_EPILOG("rcaNaamanCapacityProblem");
}
#endif

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================


Float64 rcaNaamanCapacityProblem::DoCalculateCompressionBlockBoundary()
{
   Float64 cbo;
   Float64 dist = GetFurthestDistance();
   if (dist > rcaCapacityProblem::PositionTolerance)
   {
      // use same beta1 as whitney method
      Float64 beta1 = GetBeta1();

      // need to determine compression block offset such that comp block
      // area is equal to beta1*(total area in compresssion)
      // Determine area of total compression region
      GetNeutralAxisLocation(&m_NaLine);

      // TRICKY:
      // If we set target area to zero and set compression block offset to zero,
      // Evaluate() will return the full compression area. This nonsense is done
      // to make the math solver work with this class. A cleaner method would likely
      // be less efficient.

      m_TargetArea = 0;
      m_TargetArea = Evaluate(0)*beta1;
      CHECK(m_TargetArea>0.);

      // Now have required area. Must clip shape at angle of neutral axis until the
      // location of the comp block creates the required area. This looks like a good
      // job for a root finder. However, most shapes are rectangular and will not require
      // an expensive root-finding search. Let's first assume the shape is a rectangle 
      // and try it.
      const Float64 TOL=0.0000001;
      Float64 root;

      Float64 rect_loc = dist*(1-beta1);
      Float64 rect_try = Evaluate(rect_loc);

      if ( fabs(rect_try) <= TOL)
         cbo = rect_loc;
      else
      {
         // not a rect, try solver
         // can improve left side guess by using results from rect_try
         Float64 left_guess;
         if (rect_try > -TOL/100.)
            left_guess = rect_loc;
         else
            left_guess = 0.0;

         mathBrentsRootFinder2d solver;
         try
         {
            root = solver.FindRootInRange(*this, left_guess, dist, TOL);
         }
         catch(mathXRootFinder2dFailed&)
         {
            rcaXRcCapProbError ex(rcaXRcCapProbError::InvalidProblemRep, _T(__FILE__), __LINE__);
            ex.Throw();
         }

         cbo = root;
      }
   }
   else
   {
      // none of the section is left of the n.a.
      // no offset.
      cbo=0.0;
   }

   return cbo;
}


void rcaNaamanCapacityProblem::MakeCopy(const rcaNaamanCapacityProblem& rOther)
{
   // Add copy code here...
}

void rcaNaamanCapacityProblem::MakeAssignment(const rcaNaamanCapacityProblem& rOther)
{
   Clean();
   Init();

   rcaWhitneyCapacityProblem::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

Float64 rcaNaamanCapacityProblem::Evaluate(Float64 x) const
{
   // this will be called by the mathRootFinder to solve for area as
   // a function of compression block offset.

   Float64 cla;
   gpLine2d cbb = m_NaLine.Parallel(x,gpLine2d::Left);

   // get the clipped concrete area - this is factored by N
   cla = GetClippedConcreteArea(cbb, gpLine2d::Right);

   return cla - m_TargetArea;
}

mathFunction2d* rcaNaamanCapacityProblem::Clone() const
{
   ASSERT(false); // this method should never be called
   return nullptr;
}

void rcaNaamanCapacityProblem::Init()
{
   // Add initialization code here...
}

void rcaNaamanCapacityProblem::Clean()
{
   // Add cleanup code here...
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


