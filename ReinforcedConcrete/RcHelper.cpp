///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
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
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <ReinforcedConcrete\ReinfConcLib.h>
#include "RcHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//------------------------------------------------------------------------
// conversion routines for transforming back and forth between global (na)
// coordinates and plastic centroid coordinates
void Na2PcCoords(const gpPoint2d& pc, const gpLine2d& na, 
                 Float64* d, Float64* theta)
{
   // theta is easy. it's just the line normal vector
   Float64    c;
   gpVector2d n;
   na.GetImplicit(&c, &n);
   *theta = gpGeomOp2d::NormalizeAngle(n.GetDirection());

   // have to be careful to get the right sign of d.
   gpPoint2d pn = na.PointOnLineNearest(pc);
   *d = pc.Distance(pn);
   if (*d!=0.0)
   {
      gpVector2d dir(pn.X()-pc.X(), pn.Y()-pc.Y());
      if (n.Dot(dir)<0)
         *d = -*d;
   }
}

void PcCoords2Na(const gpPoint2d& pc, Float64 d, 
                 Float64 theta, gpLine2d* na)
{

   gpVector2d n(1.0, gpGeomOp2d::NormalizeAngle(theta));
   na->SetImplicit(d,n);
   na->Offset(pc.X(), pc.Y());
}


bool IsZeroCapacityProblem(rcaCapacityProblem& problem)
{
   // If the number of concrete elements or reinforcing elements is zero, 
   // there is no capacity.  If the concrete strength is zero, then there is
   // no capacity either.
   Int32 nc = problem.GetNumConcretes();
   if (nc==0)
      return true;

   Float64 fc=0.0;
   for (Int32 i=0; i<nc; i++)
       fc = max(fc, problem.GetConcrete(i).GetFc());

   if ( IsZero(fc) )
      true;

   if ( problem.ConcreteElementCount() == 0  || problem.GetConcreteArea() <= 0)
      return true;

   if ( problem.ReinforcementElementCount() == 0 )
      return true;

   return false;
}

rcaCapacitySolution MakeZeroCapacitySolution(rcaCapacityProblem& problem)
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
