///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
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

#ifndef INCLUDED_REINFORCEDCONCRETE_CAPACITYSOLVER_H_
#define INCLUDED_REINFORCEDCONCRETE_CAPACITYSOLVER_H_
#pragma once

// SYSTEM INCLUDES
//
#include <memory>
#include <fstream>
#include <boost\shared_ptr.hpp>

// PROJECT INCLUDES
//
//
#include <WBFLGeometry.h>
#include <ReinforcedConcrete\ReinfConcExp.h>
#include <ReinforcedConcrete\CapacitySolution.h>
#include <ReinforcedConcrete\CapacitySolverError.h>
#include <Math\Function2d.h>
#include <MathEx.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class rcaCapacityProblem;
class mathRootFinder2d;

// MISCELLANEOUS
//

#if !defined INCLUDED_SYSTEM_SYSXBASE_H_
#include <System\Exception.h>
#endif

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#define RCA_BRENTS    0x0001
#define RCA_BISECTION 0x0002

/*****************************************************************************
CLASS 
   rcaCapacitySolver

   This class solves the concrete capacity problem by performing a biaxial
   analysis.


DESCRIPTION
   This class solves the concrete capacity problem by performing a biaxial
   analysis.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 02.05.1998 : Created file
*****************************************************************************/

class REINFCONCCLASS rcaCapacitySolver : private mathFunction2d
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rcaCapacitySolver(Uint32 solverType = RCA_BRENTS);

   //------------------------------------------------------------------------
   // Copy constructor
   rcaCapacitySolver(const rcaCapacitySolver& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rcaCapacitySolver();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rcaCapacitySolver& operator = (const rcaCapacitySolver& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Solve Using Biaxial Solution
   // Solves the capacity problems and returns a solution object.  Throws a 
   // rcaXCapacitySolverError exception if a solution could not be found.
   rcaCapacitySolution Solve(rcaCapacityProblem& problem) const;

   //------------------------------------------------------------------------
   // Solve Using Uniaxial Solution.
   // Assumes that the angle of the neutral axis is normal to the applied moment.
   // Problem had better be symetrical about moment axis or the solution returned
   // will not give correct results.
   // Solves the capacity problems and returns a solution object.  Throws a 
   // rcaXCapacitySolverError exception if a solution could not be found.
   rcaCapacitySolution SolveUniaxial(rcaCapacityProblem& problem) const;

   //------------------------------------------------------------------------
   // SetAxialForce
   // Sets the applied axial force to be solved for.
   void SetAxialForce(Float64 f);

   //------------------------------------------------------------------------
   // GetAxialForce
   // Returns the applied axial force.
   Float64 GetAxialForce() const;

   //------------------------------------------------------------------------
   // SetMomentInteractionAngle
   // Sets the moment interaction angle.  The moment interaction angle is the
   // arctangent of My/Mx.  A moment interaction angle is used because its 
   // range is between ±p/2 where the actual My/Mx ratio is between ±infinity.
   // The moment interaction angle is measured clockwise in radians from the 
   // positive X axis.
   void SetMomentInteractionAngle(Float64 angle);

   //------------------------------------------------------------------------
   // GetMomentInteractionAngle
   // Returns the moment interaction angle.
   Float64 GetMomentInteractionAngle() const;

   //------------------------------------------------------------------------
   // SetMaxIter
   // Sets the maximum number of iterations before the solver fails.
   void SetMaxIter(Int32 maxIter);

   //------------------------------------------------------------------------
   // GetMaxIter
   // Returns the maximum number of iterations before the solver fails.
   Int32 GetMaxIter() const;

   //------------------------------------------------------------------------
   // SetTolerance
   // Sets the solution tolerance for the angle and location of the  neutral
   // axis
   void SetTolerance(Float64 angleTol,Float64 locTol);

   //------------------------------------------------------------------------
   // GetAngleTolerance
   // Returns the tolerance for the angle of the neutral axis.
   Float64 GetAngleTolerance() const;

   //------------------------------------------------------------------------
   // GetLocationTolerance
   // Returns the tolerance for the location of the neutral axis.
   Float64 GetLocationTolerance() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const rcaCapacitySolver& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const rcaCapacitySolver& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // solver adapter class
   // This class is used to adapt the number line - oriented solver to
   // radial coordinates for this problem. It does so by insuring that the 
   // angle values are montonic and continuous in the quadrants where the 
   // moment angle and NA angle can be.
   class SolverAdapter
   {
   public:
      void Init(Float64 momentAngle)
      {
         ATLASSERT( InRange(0.0, momentAngle, TWO_PI) );
         // compute anti angle = 180 off of moment angle
         // this is the only angle that it's not possible for the 
         m_AntiMomentAngle = gpGeomOp2d::NormalizeAngle(momentAngle+M_PI);

         // compute quadrant
         if (momentAngle<PI_OVER_2)
         {
            m_Quadrant = 1;
            m_dT = m_AntiMomentAngle - M_PI;
         }
         else if (momentAngle<M_PI)
         {
            m_Quadrant = 2;
            m_dT = m_AntiMomentAngle - 3.0*M_PI/2.0;
         }
         else if (momentAngle<1.5*M_PI)
         {
            m_Quadrant = 3;
            m_dT = m_AntiMomentAngle;
         }
         else
         {
            m_Quadrant = 4;
            m_dT = m_AntiMomentAngle - PI_OVER_2;
         }

         ATLASSERT( InRange(0.0, m_dT, PI_OVER_2) );

      }

      // this routine converts angles into solver coordinates
      Float64 P2Solver(Float64 origAngle) const
      {
         Float64 angle = origAngle;
         ATLASSERT( InRange(-M_PI, angle, TWO_PI) );

         if (angle<0.0)
            angle += TWO_PI;

         switch (m_Quadrant)
         {
         case 1:
           
            // Quadrant I.  -M_PI+dT <= angle <= M_PI+dT
            if (angle>M_PI)
               angle -= TWO_PI;

            if (angle < -M_PI+m_dT)
               angle += TWO_PI;

            break;
         case 2:
            // quadrant II. -PI_OVER_2 + dT <= angle <= 3*PI_OVER_2 + dT
            if(angle>1.5*M_PI)
               angle -= TWO_PI;

            if (angle < -PI_OVER_2+m_dT)
               angle += TWO_PI;

            break;
         case 3:
            // Quadrant III.  0+dT <= angle <= 2*M_PI+dT
            if (angle<0)
               angle += TWO_PI;

            if (angle < m_dT)
               angle += TWO_PI;

            break;
          case 4:
            // Quadrant IV.  PI_OVER_2+dT <= angle <= 5*PI_OVER_2+dT
            if (angle<PI_OVER_2)
               angle += TWO_PI;

            if (angle < PI_OVER_2+m_dT)
               angle += TWO_PI;

            break;
         }


         return angle;
      }

   private:
      int     m_Quadrant;
      Float64 m_AntiMomentAngle; 
      Float64 m_dT;
   };

   // GROUP: DATA MEMBERS
   Float64  m_AxialForce;
   mutable Float64  m_MomentAngle;
   Int32    m_MaxIterations;
   boost::shared_ptr<mathRootFinder2d> m_pAxialSolver;
   boost::shared_ptr<mathRootFinder2d> m_pAngleSolver;

   // solver status state variables
   enum EvalMode {AngleMode, AxialMode};

   mutable SolverAdapter m_Adapter;
   mutable EvalMode m_EvalMode;
   mutable Float64                   m_D;      // D and theta in plastic centroid coord's
   mutable Float64                   m_Theta;
   // don't know if solver will return current or last solution
   // so we must cache them both
   mutable Float64                   m_DPrev;   
   mutable Float64                   m_ThetaPrev;
   mutable Float64                   m_DCurrent;
   mutable Float64                   m_ThetaCurrent;
   mutable Float64                   m_ThetaOriginalLower;
   mutable Float64                   m_ThetaOriginalUpper;
   mutable gpLine2d                  m_NaLoc;  // n.a. location in section coord's
   mutable gpPoint2d m_PlasticCentroid;
   mutable rcaCapacityProblem*       m_pTheProblem;
   Float64  m_ToleranceD;
   Float64  m_ToleranceTheta;

public:
   mutable long m_TotalIter;
#ifdef DUMP_LOG
   mutable long m_AxialIter;
   mutable long m_AngleIter;
   mutable std::_tofstream m_Log;
#endif

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
private:
   //------------------------------------------------------------------------
   // Private version of mathFunction2d interface to be used by math solvers.
   virtual Float64 Evaluate(Float64 x) const;

   virtual mathFunction2d* Clone() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REINFORCEDCONCRETE_CAPACITYSOLVER_H_
