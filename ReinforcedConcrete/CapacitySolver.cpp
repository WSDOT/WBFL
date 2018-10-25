///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
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

#include <ReinforcedConcrete\ReinfConcLib.h>
#include <ReinforcedConcrete\CapacitySolver.h>

#include <ReinforcedConcrete\CapacitySolverError.h>
#include <Math\BrentsRootFinder2d.h>
#include <Math\BisectionRootFinder2d.h>
#include <ReinforcedConcrete\CapacityProblem.h>
#include <Material\Concrete.h>
#include <Lrfd\ConcreteUtil.h>
#include "RcHelper.h"
#include <strstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DIAG_DECLARE_GROUP(rca);

/****************************************************************************
CLASS
   rcaXCapacitySolverError 
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

/****************************************************************************
CLASS
   rcaCapacitySolver
****************************************************************************/




const int MAX_ITER_DEFAULT = 500;
////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rcaCapacitySolver::rcaCapacitySolver(Uint32 solverType) :
  m_AxialForce(0.),
  m_MomentAngle(0.),
  m_MaxIterations(MAX_ITER_DEFAULT),
  m_ToleranceTheta(rcaCapacityProblem::PositionTolerance),
#ifdef DUMP_LOG
  m_Log("Dump.txt"),
  m_AngleIter(0),
  m_AxialIter(0),
#endif
  m_TotalIter(0),
  m_ToleranceD(0.00001)
{
   if ( solverType == RCA_BRENTS )
   {
      m_pAxialSolver = std::auto_ptr<mathRootFinder2d>( new mathBrentsRootFinder2d() );
      m_pAngleSolver = std::auto_ptr<mathRootFinder2d>( new mathBrentsRootFinder2d() );
   }
   else
   {
      m_pAxialSolver = std::auto_ptr<mathRootFinder2d>( new mathBisectionRootFinder2d() );
      m_pAngleSolver = std::auto_ptr<mathRootFinder2d>( new mathBisectionRootFinder2d() );
   }

  m_pAngleSolver->SetMaxIter(MAX_ITER_DEFAULT);
  m_pAxialSolver->SetMaxIter(MAX_ITER_DEFAULT);
}

rcaCapacitySolver::rcaCapacitySolver(const rcaCapacitySolver& rOther):
  m_AxialForce(0.),
#ifdef DUMP_LOG
  m_Log("DumpCopy.txt"),
  m_AngleIter(0),
  m_AxialIter(0),
#endif
  m_TotalIter(0),
  m_MomentAngle(0.)
{
   MakeCopy(rOther);
}

rcaCapacitySolver::~rcaCapacitySolver()
{
}

//======================== OPERATORS  =======================================
rcaCapacitySolver& rcaCapacitySolver::operator= (const rcaCapacitySolver& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

bool is_zero_capacity_problem(rcaCapacityProblem& problem)
{
   // If the number of concrete elements or reinforcing elements is zero, 
   // there is no capacity.  If the concrete strength is zero, then there is
   // no capacity either.
   CollectionIndexType nc = problem.GetNumConcretes();
   if (nc==0)
      return true;

   Float64 fc=0.0;
   for (CollectionIndexType i=0; i<nc; i++)
       fc = max(fc, problem.GetConcrete(i).GetFc());

   if ( IsZero(fc) )
      return true;

   if ( problem.ConcreteElementCount() == 0  || problem.GetConcreteArea() <= 0)
      return true;

   if ( problem.ReinforcementElementCount() == 0 )
      return true;

   return false;
}

rcaCapacitySolution make_zero_capacity_solution(rcaCapacityProblem& problem)
{
   rcaCapacitySolution solution;

   Float64 beta1 = problem.GetBeta1();
   gpRect2d box  = problem.GetBoundingBox();
   gpPoint2d tc  = box.TopCenter();

   solution.SetBeta1( beta1 );
   solution.SetForceRes(0,tc,0,tc);
   solution.SetNeutralAxis(gpLine2d(box.TopLeft(),box.TopRight()));

   return solution;
}

rcaCapacitySolution rcaCapacitySolver::SolveUniaxial(rcaCapacityProblem& problem) const
{
   rcaCapacitySolution solution;

   ASSERTVALID( problem );

   // Before we get started, lets do a reality check to make sure the problem
   // actually has a chance of having a capacity.
   if ( is_zero_capacity_problem(problem) )
      return make_zero_capacity_solution(problem);

   // Make sure the applied axial load is between the tensile and compressive limit
   // This solver only works for P = (Pt,Pc)
   Float64 Pc,Mcx,Mcy;
   problem.GetCompressiveCapacity(&Pc,&Mcx,&Mcy);
   if ( Pc >= m_AxialForce )
      THROW(rcaXCapacitySolverError,CompressiveCapacityExceeded);

   Float64 Pt,Mtx,Mty;
   problem.GetTensileCapacity(&Pt,&Mtx,&Mty);
   if ( Pt <= m_AxialForce )
      THROW(rcaXCapacitySolverError,TensileCapacityExceeded);

   // enforce some real world tolerancing on the solution. The solution is good enough
   // if P is within P_TOL% of the right answer and the moment angle is good enough if
   // M_TOL is within 1%.

   // Store problem
   m_pTheProblem = &problem;

   // Store Plastic Centroid
   try 
   {
      m_PlasticCentroid = m_pTheProblem->GetPlasticCentroid();
   }
   catch(rcaXRcCapProbError)
   {
      rcaXCapacitySolverError ex(_T("Couldn't find the plastic centroid"),rcaXCapacitySolverError::ProblemRepError,_T(__FILE__),__LINE__);
      ex.Throw();
   }

   // the independent variable for the solution is the distance from the plastic
   // centroid to the neutral axis (m_D) 
   // put initial n.a. at plastic centroid and align it with moment interaction angle
   // noting that the vector angle for the nuetral axis line is 90deg less than the interaction angle
   m_D=0.;
   m_Theta = m_MomentAngle - PI_OVER_2;

   // set to axial mode and solve for n.a. location
   Float64   fz, mx, my;
   Float64   tensRes, compRes;
   gpPoint2d tensLoc, compLoc;
   Float64 beta1;
   Float64 cb_offset;
   Float64 na_area, cb_area;

   try
   {
      WATCHX(rca,0,_T("Solving Uniaxial for P = ") << m_AxialForce << _T(" Angle = ") << m_MomentAngle);

      // set iteration counts - for performance tuning
      m_TotalIter = 0;
#ifdef DUMP_LOG
      m_AxialIter = 0;
      m_AngleIter = 0;
#endif

      // must bound d to be to right of outermost compression fiber of problem
      // create a ficticous n.a. at the plastic centroid and oriented in the 
      // theta direction and calculate the bounding value for D
      gpVector2d tang(1.0,m_Theta-PI_OVER_2);
      gpLine2d tna(m_PlasticCentroid, tang);
      m_pTheProblem->SetNeutralAxisLocation(tna);
      Float64 dmax = m_pTheProblem->GetFurthestDistance();
      
      // If dmax is less than zero, then PC lies outside of the concrete boundary.
      // I'm not totally sure that solver won't converge if this is the case, but you will
      // want to do some heavy testing if you want to use it for these cases.
      CHECK(dmax>0.0);

      // find D
      m_EvalMode = AxialMode;
         m_D = m_pAxialSolver->FindRootConstrainedMax(*this, m_D, dmax, m_ToleranceD);

      // now can fill up solution object
      PcCoords2Na(m_PlasticCentroid, m_D, m_Theta, &m_NaLoc);
      m_pTheProblem->SetNeutralAxisLocation(m_NaLoc);
         m_pTheProblem->GetSectionForcesEx(&fz,&mx,&my,&compRes,&compLoc,&tensRes,&tensLoc);
         
      beta1 = m_pTheProblem->GetBeta1();

      // total compression area above n.a.
      na_area = m_pTheProblem->GetCompressionArea();

      // comp block area
      cb_offset = m_pTheProblem->GetCompressionBlockBoundary();
      cb_area = m_pTheProblem->GetEffectiveCompressionArea();

   }
   catch(mathXRootFinder2dFailed& e)
   {
      std::_tstring msg;
      e.GetErrorMessage( &msg );
      std::_tostringstream os;
      os << "mathXRootFinder2dFailed - Reason = " << msg << " File : " << e.GetFile() << " Line : " << e.GetLine() << std::endl << std::ends;
      rcaXCapacitySolverError ex(os.str(),rcaXCapacitySolverError::ProblemRepError,_T(__FILE__),__LINE__);
      ex.Throw();
   }
   catch(rcaXRcCapProbError& e)
   {
      std::_tstring msg;
      e.GetErrorMessage( &msg, 0 );
      std::_tostringstream os;
      os << "rcaXRcCapProbError - Reason = " << msg << " File : " << e.GetFile() << " Line : " << e.GetLine() << std::endl << std::ends;
      rcaXCapacitySolverError ex(os.str(),rcaXCapacitySolverError::ProblemRepError,_T(__FILE__),__LINE__);
      ex.Throw();
   }

#if defined _DEBUG
   // Check the results
   CHECK( IsZero(m_AxialForce-fz,1.0) );
   Float64 moment_angle = gpGeomOp2d::NormalizeAngle(atan2(my,mx));
   if ( IsZero(m_MomentAngle) )
   {
      Float64 moment_angle2 = moment_angle - TWO_PI;
      if ( fabs(moment_angle2) < fabs(moment_angle) )
         moment_angle = moment_angle2;
   }
   CHECK( IsEqual(m_MomentAngle,moment_angle,m_ToleranceTheta*1000.));
#endif

#ifdef DUMP_LOG
   m_Log << "Total Iterations = "<<m_TotalIter<<std::endl;
#endif

   solution.SetAxialForce(fz);
   solution.SetMx(mx);
   solution.SetMy(my);
   solution.SetBeta1(beta1);
   solution.SetNeutralAxis(m_NaLoc);
   solution.SetCompFiberDistance(m_pTheProblem->GetFurthestDistance());
   solution.SetCompressionBlockBoundary(cb_offset);
   solution.SetAreaAboveNeutralAxis(na_area);
   solution.SetCompressionBlockArea(cb_area);
   solution.SetForceRes(compRes,compLoc,tensRes,tensLoc);
   return solution;
}


rcaCapacitySolution rcaCapacitySolver::Solve(rcaCapacityProblem& problem) const
{
   rcaCapacitySolution solution;

   ASSERTVALID( problem );

   // Before we get started, lets do a reality check to make sure the problem
   // actually has a chance of having a capacity.
   if ( is_zero_capacity_problem(problem) )
      return make_zero_capacity_solution(problem);

   // Make sure the applied axial load is between the tensile and compressive limit
   // This solver only works for P = (Pt,Pc)
   Float64 Pc,Mcx,Mcy;
   problem.GetCompressiveCapacity(&Pc,&Mcx,&Mcy);
   if ( Pc >= m_AxialForce )
      THROW(rcaXCapacitySolverError,CompressiveCapacityExceeded);

   Float64 Pt,Mtx,Mty;
   problem.GetTensileCapacity(&Pt,&Mtx,&Mty);
   if ( Pt <= m_AxialForce )
      THROW(rcaXCapacitySolverError,TensileCapacityExceeded);

   // Store problem
   m_pTheProblem = &problem;

   // Store Plastic Centroid
   try 
   {
      m_PlasticCentroid = m_pTheProblem->GetPlasticCentroid();
      }
   catch(rcaXRcCapProbError)
   {
      rcaXCapacitySolverError ex(_T("Couldn't find the plastic centroid"),rcaXCapacitySolverError::ProblemRepError,_T(__FILE__),__LINE__);
      ex.Throw();
   }

   // the independent variables for the solution are the distance from the plastic
   // centroid to the neutral axis (m_D) and the rotation angle of the normal to the neutral 
   // axis (m_Theta). m_Theta is defined to be zero when the n.a. is parallel to the 
   // Y axis and positive m_D offsets the na along the positive X axis. These variables
   // must be transferred into global coordinates in order to work with CapacityProblem classes.

   // initialize angle adapter
   m_Adapter.Init(m_MomentAngle);
   m_MomentAngle = m_Adapter.P2Solver(m_MomentAngle);

   // put initial n.a. at plastic centroid and align it with moment interaction angle
   // noting that the vector angle for the nuetral axis line is 90deg less than the interaction angle
   m_D=0.;
   m_Theta = m_MomentAngle - PI_OVER_2;

   // assume bracket is +/- 90 degrees from initial guess. this should always be true.
   m_ThetaOriginalLower = m_Theta-PI_OVER_2;
   m_ThetaOriginalUpper = m_Theta+PI_OVER_2;

   // set to angle mode and solve for n.a. location
   Float64   fz, mx, my;
   Float64   tensRes, compRes;
   gpPoint2d tensLoc, compLoc;
   Float64 beta1;
   Float64 cb_offset;
   Float64 na_area, cb_area;

   try
   {
      WATCHX(rca,0,_T("Solving for P = ") << m_AxialForce << _T(" Angle = ") << m_MomentAngle);

      // set iteration counts - for performance tuning
      m_TotalIter = 0;
#ifdef DUMP_LOG
      m_AxialIter = 0;
      m_AngleIter = 0;
#endif

      m_EvalMode = AngleMode;
      // rotate values to positive coords before going into solver
      Float64 thetasol = m_pAngleSolver->FindRootInRange(*this, m_ThetaOriginalLower, m_ThetaOriginalUpper, m_ToleranceTheta);

      // solver will return the best of the last two solutions. 
      // make sure we capture the right one
      if (thetasol==m_ThetaPrev)
      {
         m_Theta = m_ThetaPrev;
         m_D     = m_DPrev;
      }
      else
      {
         m_Theta = m_ThetaCurrent;
         m_D     = m_DCurrent;
      }

      // now can fill up solution object
      PcCoords2Na(m_PlasticCentroid, m_D, m_Theta, &m_NaLoc);
      m_pTheProblem->SetNeutralAxisLocation(m_NaLoc);
      m_pTheProblem->GetSectionForcesEx(&fz, &mx, &my, &compRes, &compLoc, &tensRes, &tensLoc);

      beta1     = m_pTheProblem->GetBeta1();

      // total compression area above n.a.
      na_area   = m_pTheProblem->GetCompressionArea();

      // comp block area
      cb_offset = m_pTheProblem->GetCompressionBlockBoundary();
      cb_area   = m_pTheProblem->GetEffectiveCompressionArea();

   }
   catch(mathXRootFinder2dFailed& e)
   {
      std::_tstring msg;
      e.GetErrorMessage( &msg );
      std::_tostringstream os;
      os << "mathXRootFinder2dFailed - Reason = " << msg << " File : " << e.GetFile() << " Line : " << e.GetLine() << std::endl << std::ends;
      rcaXCapacitySolverError ex(os.str(),rcaXCapacitySolverError::ProblemRepError,_T(__FILE__),__LINE__);
      ex.Throw();
   }
   catch(rcaXRcCapProbError& e)
   {
      std::_tstring msg;
      e.GetErrorMessage( &msg, 0 );
      std::_tostringstream os;
      os << "rcaXRcCapProbError - Reason = " << msg << " File : " << e.GetFile() << " Line : " << e.GetLine() << std::endl << std::ends;
      rcaXCapacitySolverError ex(os.str(),rcaXCapacitySolverError::ProblemRepError,_T(__FILE__),__LINE__);
      ex.Throw();
   }

#if defined _DEBUG
   // Check the results
   CHECK( IsZero(m_AxialForce-fz,1.0) );
   Float64 moment_angle = gpGeomOp2d::NormalizeAngle(atan2(my,mx));
   if ( IsZero(m_MomentAngle) )
   {
      Float64 moment_angle2 = moment_angle - TWO_PI;
      if ( fabs(moment_angle2) < fabs(moment_angle) )
         moment_angle = moment_angle2;
   }
   CHECK( IsEqual(m_MomentAngle,moment_angle,m_ToleranceTheta*1000.));
#endif

#ifdef DUMP_LOG
   m_Log << "Total Iterations = "<<m_TotalIter<<std::endl;
#endif

   solution.SetAxialForce(fz);
   solution.SetMx(mx);
   solution.SetMy(my);
   solution.SetBeta1(beta1);
   solution.SetNeutralAxis(m_NaLoc);
   solution.SetCompFiberDistance(m_pTheProblem->GetFurthestDistance());
   solution.SetCompressionBlockBoundary(cb_offset);
   solution.SetAreaAboveNeutralAxis(na_area);
   solution.SetCompressionBlockArea(cb_area);
   solution.SetForceRes(compRes,compLoc,tensRes,tensLoc);
   return solution;
}

Float64 rcaCapacitySolver::Evaluate(Float64 x) const
{
   // Evaluate can be either in angle mode for the angle solver, or axial mode
   // for the axial solver. This may seem like a kludge, but it avoids the creation
   // of multiple adapter classes.

   DIAG_ENABLE( rca, DIAG_GROUP_ENABLE );

   // NOTE: These are static members
   static Float64 sfz = 0.0;
   static Float64 smx = 0.0;
   static Float64 smy = 0.0;

   if (m_EvalMode==AngleMode)
   {
      // angle solver is making the call. need to solve for axial

      m_Theta = x;
      CHECK( InRange(m_ThetaOriginalLower, m_Theta, m_ThetaOriginalUpper) );

      WATCHX(rca,0,_T("*** Trying Theta = ") << m_Theta);
      WATCHX(rca,0,_T("               D = ") << m_D);
#ifdef DUMP_LOG
      m_Log << "A "<<++m_AngleIter<<", "<<m_Theta << std::endl;
#endif

      // must bound d to be to right of outermost compression fiber of problem
      // create a ficticous n.a. at the plastic centroid and oriented in the 
      // theta direction and calculate the bounding value for D
      gpVector2d tang(1.0,m_Theta-PI_OVER_2);
      gpLine2d tna(m_PlasticCentroid, tang);
      m_pTheProblem->SetNeutralAxisLocation(tna);
      Float64 dmax = m_pTheProblem->GetFurthestDistance();

      // If dmax is less than zero, then PC lies outside of the concrete boundary.
      // I'm not totally sure that solver won't converge if this is the case, but you will
      // want to do some heavy testing if you want to use it for these cases.
      CHECK(dmax>0.0);

      // in most cases, we want to use previous solution for D as initial guess for new angle.
      // However, for some high-aspect shapes, using last guess for D will result in a D that's outside
      // of the section boundary. Check this and set initial guess for D appropriately.
      if (m_D>=dmax)
         m_D = dmax/2.0; 

      // find correct p for this angle
      m_EvalMode = AxialMode;
      m_D = m_pAxialSolver->FindRootConstrainedMax(*this, m_D, dmax, m_ToleranceD);
      m_EvalMode = AngleMode;
      // assumption here is that the last neutral axis location used is the 
      // current solution - be careful with this if switching to solvers other
      // than Brent's or bisection.
      // save previous solution
      m_ThetaPrev = m_ThetaCurrent; 
      m_DPrev     = m_DCurrent;
      m_ThetaCurrent = m_Theta;
      m_DCurrent     = m_D;

      Float64 angle = m_Adapter.P2Solver( atan2(smy,smx) );
      Float64 delta_angle = m_MomentAngle - angle;
      WATCHX(rca,0,_T("Delta Angle = ") << delta_angle);

#ifdef DUMP_LOG
      m_AxialIter=0;
      m_Log << "A "<<m_AngleIter<<", "<<m_Theta <<", "<< delta_angle << std::endl;
#endif

      return delta_angle;
   }
   else
   {
      // axial solver is making the call - return forces
      m_D = x;
      WATCHX(rca,0,_T("   Trying D = ") << m_D);
      WATCHX(rca,0,_T("   Theta = ") << m_Theta);

      PcCoords2Na(m_PlasticCentroid, m_D, m_Theta, &m_NaLoc);
      m_pTheProblem->SetNeutralAxisLocation(m_NaLoc);
      m_pTheProblem->GetSectionForces(&sfz, &smx, &smy);
      Float64 delta_force = sfz - m_AxialForce;
      m_TotalIter++;

      WATCHX(rca,0,_T("      Delta Force = ") << delta_force );
#ifdef DUMP_LOG
      m_Log <<"D "<<++m_AxialIter<<", "<<m_D <<", "<<sfz<<", "<<smx<<", "<<smy<<", "<<delta_force << std::endl;
#endif

   return delta_force;
}
}

mathFunction2d* rcaCapacitySolver::Clone() const
{
   ASSERT(false); // should never be called
   return NULL;
}

void rcaCapacitySolver::SetAxialForce(Float64 f)
{
   m_AxialForce = f;
}

Float64 rcaCapacitySolver::GetAxialForce() const
{
   return m_AxialForce;
}

void rcaCapacitySolver::SetMomentInteractionAngle(Float64 angle)
{
   m_MomentAngle = gpGeomOp2d::NormalizeAngle(angle);
}

Float64 rcaCapacitySolver::GetMomentInteractionAngle() const
{
   return m_MomentAngle;
}


void rcaCapacitySolver::SetMaxIter(Int32 maxIter)
{
   m_MaxIterations = maxIter;
   m_pAngleSolver->SetMaxIter(maxIter);
   m_pAxialSolver->SetMaxIter(maxIter);
}

Int32 rcaCapacitySolver::GetMaxIter() const
{
   return m_MaxIterations;
}

void rcaCapacitySolver::SetTolerance(Float64 angleTol,Float64 locTol)
{
   m_ToleranceTheta = angleTol;
   m_ToleranceD     = locTol;
}

Float64 rcaCapacitySolver::GetAngleTolerance() const
{
   return m_ToleranceTheta;
}

Float64 rcaCapacitySolver::GetLocationTolerance() const
{
   return m_ToleranceD;
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool rcaCapacitySolver::AssertValid() const
{
   return true;
}

void rcaCapacitySolver::Dump(dbgDumpContext& os) const
{
   os << "Dump for rcaCapacitySolver" << endl;
   os << "m_AxialForce        ="<<m_AxialForce       <<endl;
   os << "m_MomentAngle       ="<<m_MomentAngle      <<endl;
   os << "m_MaxIterations     ="<<m_MaxIterations    <<endl;
   os << "m_ToleranceTheta    ="<<m_ToleranceTheta   <<endl;
   os << "m_ToleranceD    ="<<m_ToleranceD   <<endl;
   os << "m_pAngleSolver      ="<<m_pAngleSolver.get() <<endl;
   os << "m_pAxialSolver      ="<<m_pAxialSolver.get() <<endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool rcaCapacitySolver::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("rcaCapacitySolver");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for rcaCapacitySolver");
   TESTME_EPILOG("rcaCapacitySolver");
}
#endif

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rcaCapacitySolver::MakeCopy(const rcaCapacitySolver& rOther)
{
   m_AxialForce        = rOther.m_AxialForce;      
   m_MomentAngle       = rOther.m_MomentAngle;     
   m_MaxIterations     = rOther.m_MaxIterations;   
   m_ToleranceTheta    = rOther.m_ToleranceTheta;  
   m_ToleranceD        = rOther.m_ToleranceD;  
   m_pAngleSolver      = rOther.m_pAngleSolver;    
   m_pAxialSolver      = rOther.m_pAxialSolver;    
}

void rcaCapacitySolver::MakeAssignment(const rcaCapacitySolver& rOther)
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


