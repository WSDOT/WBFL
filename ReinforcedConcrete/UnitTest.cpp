///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
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

#include <ReinforcedConcrete\ReinfConcLib.h>
#include <ReinforcedConcrete\UnitTest.h>

#include <ReinforcedConcrete\CapacityProblem.h>
#include <ReinforcedConcrete\CapacitySolution.h>
#include <ReinforcedConcrete\CapacitySolver.h>
#include <ReinforcedConcrete\ConcreteElement.h>
#include <ReinforcedConcrete\NaamanCapacityProblem.h>
#include <ReinforcedConcrete\ReinforcementElement.h>
#include <ReinforcedConcrete\WhitneyCapacityProblem.h>

#include <GeomModel\WsdotPrecastBeams.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rcaUnitTest
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
bool run_integration_tests(dbgLog& rlog);


bool rcaUnitTest::TestMe(dbgLog& rlog)
{
   bool tst = true;

#if defined _UNITTEST

   tst &= rcaCapacityProblem::TestMe(rlog);
   tst &= rcaCapacitySolution::TestMe(rlog);
   tst &= rcaCapacitySolver::TestMe(rlog);
   tst &= rcaConcreteElement::TestMe(rlog);
   tst &= rcaNaamanCapacityProblem::TestMe(rlog);
   tst &= rcaReinforcementElement::TestMe(rlog);
   tst &= rcaWhitneyCapacityProblem::TestMe(rlog);

   tst &= run_integration_tests(rlog);
#endif

   return tst;
}


#if defined _UNITTEST

// This is debatably integration testing, but no where else to put it for now:
#include <MathEx.h>
#include <GeomModel\Rectangle.h>
#include <GeomModel\Circle.h>
#include <Material\Concrete.h>
#include <Material\Metal.h>
#include <Units\SysUnits.h>
#include <Material\PsStrand.h>


void WriteSolution(dbgDumpContext& os, const gpPoint2d& pc, const rcaCapacitySolution& sol);

// allowable tolerances
const Float64 MOMENT_TOL=10;
const Float64 NA_TOL=0.01;


// crappy little example class for creating example problems
class Example
{
public:
   enum ProblemMode {WhitneyMode, NaamanMode};
   static ProblemMode m_Mode;
   // constructor creates different types of problems based on mode. Could have used
   // a factory class, but hey, this is a crappy little example problem.
   Example(Float64 rightMoment, Float64 rightNaLocation) :
      m_RightMoment(rightMoment),
      m_RightNaLocation(rightNaLocation)
   {
      if (m_Mode==WhitneyMode)
         m_pProblem = new rcaWhitneyCapacityProblem();
      else
         m_pProblem = new rcaNaamanCapacityProblem();
   }
      ~Example() {  if ( m_pProblem ) delete m_pProblem; }
   virtual bool Run(dbgDumpContext& os,int solverType);

#if defined _DEBUG
   void Dump(dbgDumpContext& os)
   {
      rcaSectionForceDetails sfd;
      m_pProblem->GetSectionForcesEx(&sfd);
      sfd.Dump(os);
   }
#endif

protected:
   rcaCapacityProblem* m_pProblem;
   Float64     m_RightMoment;
   Float64     m_RightNaLocation;
private:
   Example();
};
// default to Whitney
Example::ProblemMode Example::m_Mode=Example::WhitneyMode;

bool Example::Run(dbgDumpContext& os,int solverType)
{
   // get plastic centroid location
   gpPoint2d pc = m_pProblem->GetPlasticCentroid();

   // let's try a solver
   rcaCapacitySolver my_solver(solverType);

   // Initialize the axial force to zero since these are pure bending problems.
   my_solver.SetAxialForce(0);

   // For bending about the X-axis with compression on the top of the section,
   // the neutral axis angle is 0 deg (Compression on left side of NA).
   my_solver.SetMomentInteractionAngle( M_PI );

//   my_solver.SetTolerance(0.01);
   my_solver.SetTolerance(1.0e-5,1.0e-20);

   rcaCapacitySolution sol = my_solver.Solve(*m_pProblem);
   WriteSolution(os, pc, sol);
   os << _T("Total Iterations = ")<< my_solver.m_TotalIter << endl;
   os << endl;

#if defined _DEBUG
   Dump(os);
#endif

   // check if solution is "correct"
   if (!IsZero(sol.GetMx() - m_RightMoment, MOMENT_TOL))
      return false;

   gpLine2d naline;
   sol.GetNeutralAxis(&naline);
   gpPoint2d pnt = naline.PointOnLineNearest(gpPoint2d(0,0));
   if (!IsEqual(pnt.Y(), m_RightNaLocation, NA_TOL))
      return false;

   return true;
}


class Example1: Example 
{
public:
   Example1(Float64 rightMoment, Float64 rightNaLocation):
      Example(rightMoment, rightNaLocation) {}
   virtual void Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat);
   virtual bool Run(dbgDumpContext& os,int solverType);
};

bool Example1::Run(dbgDumpContext& os,int solverType)
{
   os << _T(" ====================================================================================") << endl;
   os << _T("  let's try a simple rectangular section - From Wang & Salmon, 3rd Edition, Page 50  ") << endl;
   os << _T(" ====================================================================================") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                        < ---- .3556 m --->                                          ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                         -----------------   -                                       ") << endl;
   os << _T("                        |                 |  ^                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |        Y        |  |                                       ") << endl;
   os << _T("                        |        ^        |  |                                       ") << endl;
   os << _T("                  ^     |        |        |  |                                       ") << endl;
   os << _T("                  |     |        |        | .5461m                                   ") << endl;
   os << _T("               .6096m   |        |        |  |                                       ") << endl;
   os << _T("                depth   |        -----> X |  |                                       ") << endl;
   os << _T("                  |     |                 |  |                                       ") << endl;
   os << _T("                  v     |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |      As=.004658 |  |                                       ") << endl;
   os << _T("                        |  [[[[[[]]]]]]]  |  v                                       ") << endl;
   os << _T("                        |                 |                                          ") << endl;
   os << _T("                        |                 |                                          ") << endl;
   os << _T("                        |                 |                                          ") << endl;
   os << _T("                         -----------------                                           ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("      All units are N's & m's                                                        ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("         Right answer for moment capacity is 444 ft-kips ~ 602550 N-m's              ") << endl;
   os << _T("                          neutral axis location is ~ 0.123m                          ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T(" ====================================================================================") << endl;

   return Example::Run(os,solverType);

}
void Example1::Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat)
{

   Int32 conc_idx = m_pProblem->AddConcrete(*pconc_mat);
   Int32 msid = m_pProblem->AddMildSteel(*prebar_mat);

   // rectangular shape
   gmRectangle my_rect(gpPoint2d(0,0), 0.3556, 0.6096);
   m_pProblem->AddConcreteElement(my_rect, conc_idx, 1.0);
   // rebar - use a rectangular shape for steel
   gmRectangle bar_rect(gpPoint2d(0,-0.2413), 0.25, 0.004658*4.0);
   m_pProblem->AddReinforcementElement(bar_rect, msid, 0.0);

   bar_rect.MakeSolid(false);
   m_pProblem->AddConcreteElement(bar_rect, conc_idx, 1.0);
}


class Example2: Example 
{
public:
   Example2(Float64 rightMoment, Float64 rightNaLocation):
      Example(rightMoment, rightNaLocation) {}
   virtual void Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat);
   virtual bool Run(dbgDumpContext& os,int solverType);
};

bool Example2::Run(dbgDumpContext& os,int solverType)
{
   os << _T(" ====================================================================================") << endl;
   os << _T("  let's try a doubly reinforced rect. section - Wang & Salmon, 3rd Edition, Page 63  ") << endl;
   os << _T(" ====================================================================================") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                        < ----0.3556 m -->                                           ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                    ^    -----------------   -                                       ") << endl;
   os << _T("                .0762m  |                 |  ^                                       ") << endl;
   os << _T("                    v   |  o  2-#8's   o  |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |        Y        |  |                                       ") << endl;
   os << _T("                        |        ^        |  |                                       ") << endl;
   os << _T("                  ^     |        |        |  |                                       ") << endl;
   os << _T("                  |     |        |        | .6604m                                   ") << endl;
   os << _T("               0.7112m  |        |        |  |                                       ") << endl;
   os << _T("                depth   |        -----> X |  |                                       ") << endl;
   os << _T("                  |     |                 |  |                                       ") << endl;
   os << _T("                  v     |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        | As=5.8903e-2m^2 |                                          ") << endl;
   os << _T("                        |  [[[[[[]]]]]]]  |  v                                       ") << endl;
   os << _T("                        |                 |                                          ") << endl;
   os << _T("                        |                 |                                          ") << endl;
   os << _T("                        |                 |                                          ") << endl;
   os << _T("                         -----------------                                           ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("      All units are lb - in's                                                        ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("         Right answer for moment capacity is 988e5 N-m                               ") << endl;
   os << _T("                          neutral axis location is 0.192 m                           ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T(" ====================================================================================") << endl;

   return Example::Run(os,solverType);
}

void Example2::Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat)
{

   Int32 conc_idx = m_pProblem->AddConcrete(*pconc_mat);
   Int32 msid = m_pProblem->AddMildSteel(*prebar_mat);

   // rectangular shape
   gmRectangle my_rect(gpPoint2d(0,0), 0.3556, 0.7112);
   m_pProblem->AddConcreteElement(my_rect, conc_idx, 1.0);

   // bottom rebar - use a rectangular shape for steel
   gmRectangle bot_bar_rect(gpPoint2d(0,-0.3048), 0.25, 0.004025798*4.0);
   m_pProblem->AddReinforcementElement(bot_bar_rect, msid, 0.0);
   bot_bar_rect.MakeSolid(false);
   m_pProblem->AddConcreteElement(bot_bar_rect, conc_idx, 1.0);

   // top rebar - use a rectangular shape for steel
   gmRectangle top_bar_rect(gpPoint2d(0,0.2794), 0.25, 0.001019353*4.0);
   m_pProblem->AddReinforcementElement(top_bar_rect, msid, 0.0);
   top_bar_rect.MakeSolid(false);
   m_pProblem->AddConcreteElement(top_bar_rect, conc_idx, 1.0);
}

class Example3: Example 
{
public:
   Example3(Float64 rightMoment, Float64 rightNaLocation):
      Example(rightMoment, rightNaLocation) {}
   virtual void Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat);
   virtual bool Run(dbgDumpContext& os,int solverType);
};

bool Example3::Run(dbgDumpContext& os,int solverType)
{
   os << _T(" ====================================================================================") << endl;
   os << _T("  let's try a singly reinforced Tee section with compresssion in slab only           ") << endl;
   os << _T(" ====================================================================================") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("         |<------------------  1.9812m      ----------------------->|                ") << endl;
   os << _T("    v                                                                                ") << endl;
   os << _T("    -     ----------------------------------------------------------                 ") << endl;
   os << _T("         |                                                          |                ") << endl;
   os << _T("    -     ----------------------------------------------------------                 ") << endl;
   os << _T("    ^                              |         |                                       ") << endl;
   os << _T(" .1143m                            |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("        d=0.635m                   |         |                                       ") << endl;
   os << _T("        Depth= 0.7112m             |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                   |  As=    |                                       ") << endl;
   os << _T("                                   | .0041m^2|                                       ") << endl;
   os << _T("                                   | ooooooo |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                    ---------                                        ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                   |<------->|                                       ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                     .3302m                                          ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("      All units are lb - in's                                                        ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("         Right answer for moment capacity is 858927 N-m                              ") << endl;
   os << _T("                          neutral axis location is -0.04717 m                        ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T(" ====================================================================================") << endl;

   return Example::Run(os,solverType);
}

void Example3::Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat)
{

   Int32 conc_idx = m_pProblem->AddConcrete(*pconc_mat);
   Int32 msid = m_pProblem->AddMildSteel(*prebar_mat);

   // slab
   gmRectangle my_slab(gpPoint2d(0,-0.05715), 1.9812, 0.1143);
   m_pProblem->AddConcreteElement(my_slab, conc_idx, 1.0);

   // girder
   gmRectangle my_gird(gpPoint2d(0,-0.41275), 0.3302, 0.5969);
   m_pProblem->AddConcreteElement(my_gird, conc_idx, 1.0);

   // bottom rebar - use a rectangular shape for steel
   gmRectangle bot_bar_rect(gpPoint2d(0,-0.635), 0.25, 0.004051605*4.0);
   m_pProblem->AddReinforcementElement(bot_bar_rect, msid, 0.0);
   bot_bar_rect.MakeSolid(false);
   m_pProblem->AddConcreteElement(bot_bar_rect, conc_idx, 1.0);
}


class Example4: Example 
{
public:
   Example4(Float64 rightMoment, Float64 rightNaLocation):
      Example(rightMoment, rightNaLocation) {}
   virtual void Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat);
   virtual bool Run(dbgDumpContext& os,int solverType);
};

bool Example4::Run(dbgDumpContext& os,int solverType)
{
   os << _T(" ====================================================================================") << endl;
   os << _T("  let's try a singly reinforced Tee. section with compression in the web             ") << endl;
   os << _T(" ====================================================================================") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                           |<---  0.762m    ------>|                                 ") << endl;
   os << _T("    v                                                                                ") << endl;
   os << _T("    -                       -----------------------                                  ") << endl;
   os << _T("                           |                       |                                 ") << endl;
   os << _T("                           |                       |                                 ") << endl;
   os << _T("                           |                       |                                 ") << endl;
   os << _T("                           |                       |                                 ") << endl;
   os << _T("    -                       -----------------------                                  ") << endl;
   os << _T("    ^                              |         |                                       ") << endl;
   os << _T(" .1778m                            |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("        d=0.9144m                  |         |                                       ") << endl;
   os << _T("        Depth= 0.9652m             |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                   |  As=    |                                       ") << endl;
   os << _T("                                   | .0081m^2|                                       ") << endl;
   os << _T("                                   | ooooooo |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                    ---------                                        ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                   |<------->|                                       ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                     .3556m                                          ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("      All units are lb - in's                                                        ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("         Right answer for moment capacity is 2.24e6 N-m                              ") << endl;
   os << _T("                          neutral axis location is -0.2833 m                         ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T(" ====================================================================================") << endl;

   return Example::Run(os,solverType);
}

void Example4::Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat)
{

   Int32 conc_idx = m_pProblem->AddConcrete(*pconc_mat);
   Int32 msid = m_pProblem->AddMildSteel(*prebar_mat);

   // slab
   gmRectangle my_slab(gpPoint2d(0,-0.0889), 0.762, 0.1778);
   m_pProblem->AddConcreteElement(my_slab, conc_idx, 1.0);

   // girder
   gmRectangle my_gird(gpPoint2d(0,-0.5715), 0.3556, 0.7874);
   m_pProblem->AddConcreteElement(my_gird, conc_idx, 1.0);

   // bottom rebar - use a rectangular shape for steel
   gmRectangle bot_bar_rect(gpPoint2d(0,-0.9144), 0.25, 0.008051597*4.0);
   m_pProblem->AddReinforcementElement(bot_bar_rect, msid, 0.0);
   bot_bar_rect.MakeSolid(false);
   m_pProblem->AddConcreteElement(bot_bar_rect, conc_idx, 1.0);
}

class Example5: Example 
{
public:
   Example5(Float64 rightMoment, Float64 rightNaLocation):
      Example(rightMoment, rightNaLocation) {}
   virtual void Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat);
   virtual bool Run(dbgDumpContext& os,int solverType);
};

bool Example5::Run(dbgDumpContext& os,int solverType)
{
   os << _T(" ====================================================================================") << endl;
   os << _T("  let's try a simple prestressed rectangular section - J.R. Libby -                  ") << endl;
   os << _T("  Modern Prestressed Concrete, 4th Ed. Page 192                                      ") << endl;
   os << _T(" ====================================================================================") << endl;
   os << _T("                                  ^ Y                                                ") << endl;
   os << _T("                                  |                                                  ") << endl;
   os << _T("                        < ---- .6096 m --->                                          ") << endl;
   os << _T("                                  |                                                  ") << endl;
   os << _T("                         -------- --->X --   -                                       ") << endl;
   os << _T("                        |                 |  ^                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |     Effective prestressing stress     ") << endl;
   os << _T("                        |                 |  |     = 1.103161e9 Pa                   ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                  ^     |                 |  |                                       ") << endl;
   os << _T("                  |     |                 | .62992m                                  ") << endl;
   os << _T("               .7620m   |                 |  |                                       ") << endl;
   os << _T("                depth   |                 |  |                                       ") << endl;
   os << _T("                  |     |                 |  |                                       ") << endl;
   os << _T("                  v     |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |    As=.0.00177  |  |                                       ") << endl;
   os << _T("                        |         @       |  v                                       ") << endl;
   os << _T("                        |                 |                                          ") << endl;
   os << _T("                        |                 |                                          ") << endl;
   os << _T("                        |                 |                                          ") << endl;
   os << _T("                         -----------------                                           ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("      All units are N's & m's                                                        ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("         Right answer for moment capacity is 1321 ft-kips ~ 1.8e6 N-m's              ") << endl;
   os << _T("                          neutral axis location is ~ -0.173 m                        ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T(" ====================================================================================") << endl;

   return Example::Run(os,solverType);
}

void Example5::Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat)
{

   Int32 conc_idx = m_pProblem->AddConcrete(*pconc_mat);
   Int32 psid = m_pProblem->AddStrand(*pstrand_mat);

   // girder
   gmRectangle my_gird(gpPoint2d(0,0), 0.6096, 0.7620);
   my_gird.Move(gmIShape::TopCenter, gpPoint2d(0,0));
   m_pProblem->AddConcreteElement(my_gird, conc_idx, 1.0);

   // bottom rebar - use a circlular shape for strand
   gmCircle bot_strand(gpPoint2d(0,-0.62992), 0.023764);
   m_pProblem->AddReinforcementElement(bot_strand, psid, .00034+.0057);
   bot_strand.MakeSolid(false);
   m_pProblem->AddConcreteElement(bot_strand, conc_idx, 1.0);
}


class Example6: Example 
{
public:
   Example6(Float64 rightMoment, Float64 rightNaLocation):
      Example(rightMoment, rightNaLocation) {}
   virtual void Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat);
   virtual bool Run(dbgDumpContext& os,int solverType);
};

bool Example6::Run(dbgDumpContext& os,int solverType)
{
   os << _T(" ====================================================================================") << endl;
   os << _T("  let's try a prestressed rectangular section with compression rebar                 ") << endl;
   os << _T("  - J.R. Libby -  Modern Prestressed Concrete, 4th Ed. Page 195                      ") << endl;
   os << _T(" ====================================================================================") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                        < ---- .6096 m --->                                          ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                         -----------------   -                                       ") << endl;
   os << _T("                  ^     |                 |  ^                                       ") << endl;
   os << _T("      dc=0.1143m  |     |  Asc=.001935    |  |                                       ") << endl;
   os << _T("                  v     |  [[[[[[[]]]]]]  |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |     Effective prestressing stress     ") << endl;
   os << _T("                        |        Y        |  |     = 1.103161e9 Pa                   ") << endl;
   os << _T("                        |        ^        |  |                                       ") << endl;
   os << _T("                  ^     |        |        |  |                                       ") << endl;
   os << _T("                  |     |        |        | .62992m                                  ") << endl;
   os << _T("               .7620m   |        |        |  |                                       ") << endl;
   os << _T("                depth   |        -----> X |  |                                       ") << endl;
   os << _T("                  |     |                 |  |                                       ") << endl;
   os << _T("                  v     |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |                 |  |                                       ") << endl;
   os << _T("                        |    As=.0.00129  |  |                                       ") << endl;
   os << _T("                        |         @       |  v                                       ") << endl;
   os << _T("                        |                 |                                          ") << endl;
   os << _T("                        |                 |                                          ") << endl;
   os << _T("                        |                 |                                          ") << endl;
   os << _T("                         -----------------                                           ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("      All units are N's & m's                                                        ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("         Book answer is wrong, debug hand check gives 1.36e6 N-m's                   ") << endl;
   os << _T("                          neutral axis location is ~ -0.123 m                        ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T(" ====================================================================================") << endl;

   return Example::Run(os,solverType);
}


void Example6::Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat)
{

   Int32 conc_idx = m_pProblem->AddConcrete(*pconc_mat);
   Int32 msid = m_pProblem->AddMildSteel(*prebar_mat);
   Int32 psid = m_pProblem->AddStrand(*pstrand_mat);

   // girder
   gmRectangle my_gird(gpPoint2d(0,0), 0.6096, 0.7620);
   my_gird.Move(gmIShape::TopCenter, gpPoint2d(0,0));
   m_pProblem->AddConcreteElement(my_gird, conc_idx, 1.0);

   // bottom rebar - use a circlular shape for strand
   gmCircle bot_strand(gpPoint2d(0,-0.62992), 0.0202663);
   m_pProblem->AddReinforcementElement(bot_strand, psid, .00024+.0057);
   bot_strand.MakeSolid(false);
   m_pProblem->AddConcreteElement(bot_strand, conc_idx, 1.0);

   // top rebar - use a rectangular shape for steel
   gmRectangle top_bar_rect(gpPoint2d(0,-0.1143), 0.25, 0.001935*4.0);
   m_pProblem->AddReinforcementElement(top_bar_rect, msid, 0.0);
   top_bar_rect.MakeSolid(false);
   m_pProblem->AddConcreteElement(top_bar_rect, conc_idx, 1.0);
}


class Example7: Example 
{
public:
   Example7(Float64 rightMoment, Float64 rightNaLocation):
      Example(rightMoment, rightNaLocation) {}
   virtual void Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat);
   virtual bool Run(dbgDumpContext& os,int solverType);
};

bool Example7::Run(dbgDumpContext& os,int solverType)
{
   os << _T(" ====================================================================================") << endl;
   os << _T("Zero capacity problem - no reinforcement") << endl;
   os << _T(" ====================================================================================") << endl;
   return Example::Run(os,solverType);
}


void Example7::Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat)
{

   Int32 conc_idx = m_pProblem->AddConcrete(*pconc_mat);
   Int32 msid = m_pProblem->AddMildSteel(*prebar_mat);
   Int32 psid = m_pProblem->AddStrand(*pstrand_mat);

   // girder
   gmRectangle my_gird(gpPoint2d(0,0), 0.6096, 0.7620);
   my_gird.Move(gmIShape::TopCenter, gpPoint2d(0,0));
   m_pProblem->AddConcreteElement(my_gird, conc_idx, 1.0);
}


class Example8: Example 
{
public:
   Example8(Float64 rightMoment, Float64 rightNaLocation):
      Example(rightMoment, rightNaLocation) {}
   virtual void Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat);
   virtual bool Run(dbgDumpContext& os,int solverType);
};

bool Example8::Run(dbgDumpContext& os,int solverType)
{
   os << _T(" ====================================================================================") << endl;
   os << _T("Zero capacity problem - No concrete elements") << endl;
   os << _T(" ====================================================================================") << endl;

   return Example::Run(os,solverType);
}


void Example8::Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat)
{

   Int32 conc_idx = m_pProblem->AddConcrete(*pconc_mat);
   Int32 msid = m_pProblem->AddMildSteel(*prebar_mat);
   Int32 psid = m_pProblem->AddStrand(*pstrand_mat);

   // bottom rebar - use a circlular shape for strand
   gmCircle bot_strand(gpPoint2d(0,-0.62992), 0.0202663);
   m_pProblem->AddReinforcementElement(bot_strand, psid, .00024+.0057);
   bot_strand.MakeSolid(false);
   m_pProblem->AddConcreteElement(bot_strand, conc_idx, 1.0);

   // top rebar - use a rectangular shape for steel
   gmRectangle top_bar_rect(gpPoint2d(0,-0.1143), 1., 0.001935);
   m_pProblem->AddReinforcementElement(top_bar_rect, msid, 0.0);
   top_bar_rect.MakeSolid(false);
   m_pProblem->AddConcreteElement(top_bar_rect, conc_idx, 1.0);
}

class Example9: Example 
{
public:
   Example9(Float64 rightMoment, Float64 rightNaLocation):
      Example(rightMoment, rightNaLocation) {}
   virtual void Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat);
   virtual bool Run(dbgDumpContext& os,int solverType);
};

bool Example9::Run(dbgDumpContext& os,int solverType)
{
   os << _T(" ====================================================================================") << endl;
   os << _T("Zero capacity problem - f'c = 0") << endl;
   os << _T("Only run this in Release builds") << endl;
   os << _T(" ====================================================================================") << endl;
   return Example::Run(os,solverType);
}


void Example9::Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat)
{
   std::auto_ptr<matConcrete> p_my_conc( pconc_mat->CreateClone() );
   p_my_conc->SetFc(0);
   Int32 conc_idx = m_pProblem->AddConcrete(*p_my_conc);
   Int32 msid = m_pProblem->AddMildSteel(*prebar_mat);
   Int32 psid = m_pProblem->AddStrand(*pstrand_mat);

   // girder
   gmRectangle my_gird(gpPoint2d(0,0), 0.6096, 0.7620);
   my_gird.Move(gmIShape::TopCenter, gpPoint2d(0,0));
   m_pProblem->AddConcreteElement(my_gird, conc_idx, 1.0);

   // bottom rebar - use a circlular shape for strand
   gmCircle bot_strand(gpPoint2d(0,-0.62992), 0.0202663);
   m_pProblem->AddReinforcementElement(bot_strand, psid, .00024+.0057);
   bot_strand.MakeSolid(false);
   m_pProblem->AddConcreteElement(bot_strand, conc_idx, 1.0);

   // top rebar - use a rectangular shape for steel
   gmRectangle top_bar_rect(gpPoint2d(0,-0.1143), 1., 0.001935);
   m_pProblem->AddReinforcementElement(top_bar_rect, msid, 0.0);
   top_bar_rect.MakeSolid(false);
   m_pProblem->AddConcreteElement(top_bar_rect, conc_idx, 1.0);
}

class Example10: Example 
{
public:
   Example10(Float64 rightMoment, Float64 rightNaLocation):
      Example(rightMoment, rightNaLocation) {}
   virtual void Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat);
   virtual bool Run(dbgDumpContext& os,int solverType);
};

bool Example10::Run(dbgDumpContext& os,int solverType)
{
   os << _T(" ====================================================================================") << endl;
   os << _T("Highly prestressed WSDOT W74G girder") << endl;
   os << _T(" ====================================================================================") << endl;

   return Example::Run(os,solverType);
}


void Example10::Build(matConcrete* pconc_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat)
{

   Int32 conc_idx = m_pProblem->AddConcrete(*pconc_mat);
   Int32 msid = m_pProblem->AddMildSteel(*prebar_mat);
   Int32 strandCookie = m_pProblem->AddStrand(*pstrand_mat);

   Float64 radius = pstrand_mat->GetNominalDiameter()/2.0;

   gmWsdotPrecastBeams& wsdotBeams = gmWsdotPrecastBeams::GetInstance();
   gmPrecastBeam beam = wsdotBeams.W74MG();
   beam.Move(gmIShape::BottomCenter,gpPoint2d(0,0));
   m_pProblem->AddConcreteElement(beam, conc_idx, 1.0);

   Float64 init_strain = 0.0065;

   // Straight Strands
   gpPoint2d straight_strands[] = 
   {
      gpPoint2d( 0.2667,0.047625),
      gpPoint2d(-0.2667,0.047625),
      gpPoint2d( 0.1651,0.047625),
      gpPoint2d(-0.1651,0.047625),
      gpPoint2d( 0.0635,0.047625),
      gpPoint2d(-0.0635,0.047625),
      gpPoint2d( 0.2159,0.047625),
      gpPoint2d(-0.2159,0.047625),
      gpPoint2d( 0.1143,0.047625),
      gpPoint2d(-0.1143,0.047625),
      gpPoint2d( 0.1143,0.098425),
      gpPoint2d(-0.1143,0.098425),
      gpPoint2d( 0.1651,0.098425),
      gpPoint2d(-0.1651,0.098425),
      gpPoint2d( 0.2159,0.098425),
      gpPoint2d(-0.2159,0.098425),
      gpPoint2d( 0.2667,0.098425),
      gpPoint2d(-0.2667,0.098425),
      gpPoint2d( 0.1143,0.149225),
      gpPoint2d(-0.1143,0.149225),
      gpPoint2d( 0.1651,0.149225),
      gpPoint2d(-0.1651,0.149225),
      gpPoint2d( 0.0635,0.098425),
      gpPoint2d(-0.0635,0.098425),
      gpPoint2d( 0.0635,0.149225),
      gpPoint2d(-0.0635,0.149225)
   };

   // Harped Strands
   gpPoint2d harped_strands[] =
   {
      gpPoint2d( 0.0249175,1.78305),
      gpPoint2d(-0.0249175,1.78305),
      gpPoint2d( 0.0249175,1.73321),
      gpPoint2d(-0.0249175,1.73321),
      gpPoint2d( 0.0249175,1.68338),
      gpPoint2d(-0.0249175,1.68338),
      gpPoint2d( 0.0249175,1.63354),
      gpPoint2d(-0.0249175,1.63354),
      gpPoint2d( 0.0249175,1.58371),
      gpPoint2d(-0.0249175,1.58371),
      gpPoint2d( 0.0249175,1.53387),
      gpPoint2d(-0.0249175,1.53387),
      gpPoint2d( 0.0249175,1.48404),
      gpPoint2d(-0.0249175,1.48404),
      gpPoint2d( 0.0249175,1.43565),
      gpPoint2d(-0.0249175,1.43565),
      gpPoint2d( 0.0249175,1.38582),
      gpPoint2d(-0.0249175,1.38582),
      gpPoint2d( 0.0249175,1.33598),
      gpPoint2d(-0.0249175,1.33598),
      gpPoint2d( 0.0249175,1.28615),
      gpPoint2d(-0.0249175,1.28615)
   };

   int cStraight = sizeof(straight_strands)/sizeof(gpPoint2d);
   int cHarped   = sizeof(harped_strands)/sizeof(gpPoint2d);
   for ( int i = 0; i < cStraight; i++ )
   {
      gmCircle barShape( straight_strands[i],radius );
      gmCircle holeShape(straight_strands[i],radius);
      holeShape.MakeSolid(false);

      m_pProblem->AddReinforcementElement( barShape, strandCookie, init_strain );
      m_pProblem->AddConcreteElement( holeShape, conc_idx, 1.0 );
   }

   for ( int i = 0; i < cHarped; i++ )
   {
      gmCircle barShape( harped_strands[i],radius );
      gmCircle holeShape(harped_strands[i],radius);
      holeShape.MakeSolid(false);

      m_pProblem->AddReinforcementElement( barShape, strandCookie, init_strain );
      m_pProblem->AddConcreteElement( holeShape, conc_idx, 1.0 );
   }
}


class Example11: Example 
{
public:
   Example11(Float64 rightMoment, Float64 rightNaLocation):
      Example(rightMoment, rightNaLocation) {}
   virtual void Build(matConcrete* pgird_mat, matConcrete* pslab_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat);
   virtual bool Run(dbgDumpContext& os,int solverType);
};

bool Example11::Run(dbgDumpContext& os,int solverType)
{
   os << _T(" ====================================================================================") << endl;
   os << _T("  let's try a singly reinforced Tee. section with compression in the web             ") << endl;
   os << _T("  also f'c is different for girder and slab                                          ") <<endl;
   os << _T(" ====================================================================================") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                           |<---  0.762m    ------>|                                 ") << endl;
   os << _T("    v                                                                                ") << endl;
   os << _T("    -                       -----------------------                                  ") << endl;
   os << _T("                           |                       |                                 ") << endl;
   os << _T("                           |      f'c=4ksi         |                                 ") << endl;
   os << _T("                           |                       |                                 ") << endl;
   os << _T("                           |                       |                                 ") << endl;
   os << _T("    -                       -----------------------                                  ") << endl;
   os << _T("    ^                              |         |                                       ") << endl;
   os << _T(" .1778m                            |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                   |f'c=7.5ksi                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("        d=0.9144m                  |         |                                       ") << endl;
   os << _T("        Depth= 0.9652m             |         |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                   |  As=    |                                       ") << endl;
   os << _T("                                   | .0081m^2|                                       ") << endl;
   os << _T("                                   | ooooooo |                                       ") << endl;
   os << _T("                                   |         |                                       ") << endl;
   os << _T("                                    ---------                                        ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                   |<------->|                                       ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                     .3556m                                          ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("      All units are lb - in's                                                        ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T("         Right answer for moment capacity is ")<<m_RightMoment<<_T(" N-m                 ") << endl;
   os << _T("                          neutral axis location is ")<<m_RightNaLocation<<_T(" m         ") << endl;
   os << _T("                                                                                     ") << endl;
   os << _T(" ====================================================================================") << endl;

   return Example::Run(os,solverType);
}

void Example11::Build(matConcrete* pgird_mat, matConcrete* pslab_mat, matMetal* prebar_mat, matPsStrand* pstrand_mat)
{

   Int32 slab_idx = m_pProblem->AddConcrete(*pslab_mat);
   Int32 gird_idx = m_pProblem->AddConcrete(*pgird_mat);
   Int32 msid = m_pProblem->AddMildSteel(*prebar_mat);

   // slab
   gmRectangle my_slab(gpPoint2d(0,-0.0889), 0.762, 0.1778);
   m_pProblem->AddConcreteElement(my_slab, slab_idx, 1.0);

   // girder
   gmRectangle my_gird(gpPoint2d(0,-0.5715), 0.3556, 0.7874);
   m_pProblem->AddConcreteElement(my_gird, gird_idx, 1.0);

   // bottom rebar - use a rectangular shape for steel
   gmRectangle bot_bar_rect(gpPoint2d(0,-0.9144), 0.25, 0.008051597*4.0);
   m_pProblem->AddReinforcementElement(bot_bar_rect, msid, 0.0);
   bot_bar_rect.MakeSolid(false);
   m_pProblem->AddConcreteElement(bot_bar_rect, gird_idx, 1.0);
}




void WriteSolution(dbgDumpContext& os, const gpPoint2d& pc, const rcaCapacitySolution& sol)
{

   os<<_T("Plastic Centroid X = ")<< pc.X() << endl;
   os<<_T("Plastic Centroid Y = ")<< pc.Y() << endl;
   os<<_T("Mx Capacity        = ")<< sol.GetMx()<<endl;
   os<<_T("My Capacity        = ")<< sol.GetMy()<<endl;
   os<<_T("Axial Residual     = ")<< sol.GetAxialForce() << endl;
   gpLine2d naline;
   sol.GetNeutralAxis(&naline);
   gpPoint2d pnt = naline.PointOnLineNearest(gpPoint2d(0,0));
   os<<_T("Y of n.a.          = ")<< pnt.Y() << endl;
   Float64 compRes, tensRes;
   gpPoint2d compResLoc, tensResLoc;
   sol.GetForceRes(&compRes, &compResLoc, &tensRes, &tensResLoc);
   os<<_T("Compression Resultant = ")<<compRes<<_T(" at (")<<compResLoc.X()<<_T(",")<<compResLoc.Y()<<_T(")") << endl;
   os<<_T("Tension     Resultant = ")<<tensRes<<_T(" at (")<<tensResLoc.X()<<_T(",")<<tensResLoc.Y()<<_T(")") << endl;
   os<<_T("Beta1                 = ")<<sol.GetBeta1()<<endl;
   os<<_T("Total Compr. Area     = ")<< sol.GetAreaAboveNeutralAxis()<<endl;
   os<<_T("Compression Block Area= ")<<sol.GetCompressionBlockArea()<<endl;
}


bool run_integration_tests(dbgLog& rlog)
{
   TESTME_PROLOGUE("Integration Tests for Reinforced Concrete");

   dbgDumpContext& os = rlog.GetDumpCtx();

   // create some materials
   matConcrete conc_3000(_T("3ksi Concrete"),
                          ::ConvertToSysUnits(3.,unitMeasure::KSI),
                          ::ConvertToSysUnits(150.,unitMeasure::PCF),
                          ::ConvertToSysUnits(3.7e6,unitMeasure::KSI));

   matConcrete conc_4000(_T("4ksi Concrete"),
                          ::ConvertToSysUnits(4.,unitMeasure::KSI),
                          ::ConvertToSysUnits(150.,unitMeasure::PCF),
                          ::ConvertToSysUnits(3.7e6,unitMeasure::KSI));

   matConcrete conc_5000(_T("5ksi Concrete"),
                          ::ConvertToSysUnits(5.,unitMeasure::KSI),
                          ::ConvertToSysUnits(150.,unitMeasure::PCF),
                          ::ConvertToSysUnits(3.7e6,unitMeasure::KSI));

   matConcrete conc_6000(_T("6ksi Concrete"),
                          ::ConvertToSysUnits(6.,unitMeasure::KSI),
                          ::ConvertToSysUnits(150.,unitMeasure::PCF),
                          ::ConvertToSysUnits(3.7e6,unitMeasure::KSI));

   matConcrete conc_7500(_T("7.5ksi Concrete"),
                          ::ConvertToSysUnits(7.5,unitMeasure::KSI),
                          ::ConvertToSysUnits(150.,unitMeasure::PCF),
                          ::ConvertToSysUnits(3.7e6,unitMeasure::KSI));

   matMetal  rebar_40(_T("40ksi Rebar"), 
                      ::ConvertToSysUnits(490.,unitMeasure::PCF),
                      ::ConvertToSysUnits(29000.,unitMeasure::KSI),
                      ::ConvertToSysUnits(40.,unitMeasure::KSI));

   matMetal  rebar_50(_T("50ksi Rebar"), 
                      ::ConvertToSysUnits(490.,unitMeasure::PCF),
                      ::ConvertToSysUnits(29000.,unitMeasure::KSI),
                      ::ConvertToSysUnits(50.,unitMeasure::KSI));

   matMetal  rebar_60(_T("60ksi Rebar"), 
                      ::ConvertToSysUnits(490.,unitMeasure::PCF),
                      ::ConvertToSysUnits(29000.,unitMeasure::KSI),
                      ::ConvertToSysUnits(60.,unitMeasure::KSI));

   matPsStrand ps_270(_T("Grade 270"),matPsStrand::Gr1860,matPsStrand::LowRelaxation,matPsStrand::D1270,
                      ::ConvertToSysUnits(270.,unitMeasure::KSI),
                      ::ConvertToSysUnits(243.,unitMeasure::KSI),
                      ::ConvertToSysUnits(28000.,unitMeasure::KSI),
                      ::ConvertToSysUnits(0.5279,unitMeasure::Inch),
                      ::ConvertToSysUnits(2.75,unitMeasure::Inch2) );

   // run in whitney mode.
   Example::m_Mode=Example::WhitneyMode;

   os << _T("************* Examples in Whitney Mode ****************") << endl;
   os << endl<<endl;

   Example1 example1(-602550, .1234);
   example1.Build(&conc_4000, &rebar_40, 0);
   TRY_TESTME ( example1.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( example1.Run(os,RCA_BISECTION)); 

   Example2 example2(-987325,.192);
   example2.Build(&conc_5000, &rebar_60, 0);
   TRY_TESTME ( example2.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( example2.Run(os,RCA_BISECTION)); 

   Example3 example3(-858930, -.047);
   example3.Build(&conc_3000, &rebar_50, 0);
   TRY_TESTME ( example3.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( example3.Run(os,RCA_BISECTION)); 

   Example4 example4(-2.24395e6, -.2832);
   example4.Build(&conc_3000, &rebar_50, 0);
   TRY_TESTME ( example4.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( example4.Run(os,RCA_BISECTION)); 

   Example5 example5(-1.839858e6,-.177);
   example5.Build(&conc_7500, 0, &ps_270);
   TRY_TESTME ( example5.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( example5.Run(os,RCA_BISECTION)); 

   Example6 example6(-1385419,-0.125);
   example6.Build(&conc_7500, &rebar_60, &ps_270);
   TRY_TESTME ( example6.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( example6.Run(os,RCA_BISECTION)); 

   Example7 example7(0,0);
   example7.Build(&conc_7500, &rebar_60, &ps_270);
   TRY_TESTME ( example7.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( example7.Run(os,RCA_BISECTION)); 

   Example8 example8(0,0);
   example8.Build(&conc_7500, &rebar_60, &ps_270);
   TRY_TESTME ( example8.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( example8.Run(os,RCA_BISECTION)); 

   Example9 example9(0,0);
   example9.Build(&conc_7500, &rebar_60, &ps_270);
   TRY_TESTME ( example9.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( example9.Run(os,RCA_BISECTION)); 

   Example10 example10(-8826707,0.67940299466364);
   example10.Build(&conc_6000,&rebar_60,&ps_270);
   TRY_TESTME( example10.Run(os,RCA_BRENTS) );
   TRY_TESTME( example10.Run(os,RCA_BISECTION) );

   Example11 example11(-2.32244e6, -.183873);
   example11.Build(&conc_7500,&conc_4000, &rebar_50, 0);
   TRY_TESTME ( example11.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( example11.Run(os,RCA_BISECTION)); 

   // run in naaman mode.
   os << endl<<endl;
   os << _T("************* Examples in Naaman Mode ****************") << endl;
   os << endl<<endl;
   Example::m_Mode=Example::NaamanMode;

   Example1 n_example1(-602550, .1234);
   n_example1.Build(&conc_4000, &rebar_40, 0);
   TRY_TESTME ( n_example1.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( n_example1.Run(os,RCA_BISECTION)); 

   Example2 n_example2(-987270,.192);
   n_example2.Build(&conc_5000, &rebar_60, 0);
   TRY_TESTME ( n_example2.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( n_example2.Run(os,RCA_BISECTION)); 

   Example3 n_example3(-858930, -.047);
   n_example3.Build(&conc_3000, &rebar_50, 0);
   TRY_TESTME ( n_example3.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( n_example3.Run(os,RCA_BISECTION)); 

   Example4 n_example4(-2243940, -.319);
   n_example4.Build(&conc_3000, &rebar_50, 0);
   TRY_TESTME ( n_example4.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( n_example4.Run(os,RCA_BISECTION)); 

   Example5 n_example5(-1.839858e06,-.177);
   n_example5.Build(&conc_7500, 0, &ps_270);
   TRY_TESTME ( n_example5.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( n_example5.Run(os,RCA_BISECTION)); 

   Example6 n_example6(-1384469,-0.127);
   n_example6.Build(&conc_7500, &rebar_60, &ps_270);
   TRY_TESTME ( n_example6.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( n_example6.Run(os,RCA_BISECTION)); 

   Example7 n_example7(0,0);
   n_example7.Build(&conc_7500, &rebar_60, &ps_270);
   TRY_TESTME ( n_example7.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( n_example7.Run(os,RCA_BISECTION)); 

   Example8 n_example8(0,0);
   n_example8.Build(&conc_7500, &rebar_60, &ps_270);
   TRY_TESTME ( n_example8.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( n_example8.Run(os,RCA_BISECTION)); 

#ifndef _DEBUG // Release only test
   try
   {
      Example9 n_example9(0,0);
      n_example9.Build(&conc_7500, &rebar_60, &ps_270);
      TRY_TESTME ( n_example9.Run(os,RCA_BRENTS)); 
      TRY_TESTME ( n_example9.Run(os,RCA_BISECTION)); 
   }
   catch(...)
   {
   }
#endif

   Example10 n_example10(-8558671,0.550);
   n_example10.Build(&conc_6000,&rebar_60,&ps_270);
   TRY_TESTME( n_example10.Run(os,RCA_BRENTS) );
   TRY_TESTME( n_example10.Run(os,RCA_BISECTION) );

   Example11 n_example11(-2.32244e6, -.194581);
   n_example11.Build(&conc_7500,&conc_4000, &rebar_50, 0);
   TRY_TESTME ( n_example11.Run(os,RCA_BRENTS)); 
   TRY_TESTME ( n_example11.Run(os,RCA_BISECTION)); 

   // big string dump
//   rlog << os.str();

TESTME_EPILOG("Integration Tests for Reinforced Concrete");
}

#endif

//======================== ACCESS     =======================================
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
