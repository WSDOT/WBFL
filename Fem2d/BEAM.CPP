///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2014  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// Revision Log
// ============
// May 1997 - Created, Richard Brice, PE
// Oct 1999 - Released as Open Source
#include "stdafx.h"
#include <MathEx.h>
#include "beam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const Float64 ZTOL=1.0e-9;

Beam::Beam(Float64 l,Float64 ea,Float64 ei,MbrType type)
{
   m_L  = l;
   m_EA = ea;
   m_EI = ei;
   m_Type = type;
}

Float64 Beam::GetLength()
{
   return m_L;
}

MbrType Beam::GetType()
{
   return m_Type;
}


//
// ConcLdBeam
//
ConcLdBeam::ConcLdBeam(Float64 q,Float64 la,LoadDir dir,Float64 l,Float64 ea,Float64 ei,MbrType type) :
Beam(l,ea,ei,type)
{
   m_Q = q;
   m_Dir = dir;
   m_a = la;
   m_b = m_L - m_a;

   ComputeReactions();
   ComputeDisplacements();
}

void ConcLdBeam::GetLoad(Float64 &ld)
{
   ld = m_Q;
}

void ConcLdBeam::GetLocation(Float64 &loc)
{
   loc = m_a;
}

Beam::LoadDir ConcLdBeam::GetDirection()
{
   return m_Dir;
}

void ConcLdBeam::GetReactions(Float64 &fxl,Float64 &fyl,Float64 &mzl,
                               Float64 &fxr,Float64 &fyr,Float64 &mzr)
{
   fxl = m_Fxl;
   fyl = m_Fyl;
   mzl = m_Mzl;
   fxr = m_Fxr;
   fyr = m_Fyr;
   mzr = m_Mzr;
}

void ConcLdBeam::GetDisplacements(Float64 &dxl,Float64 &dyl,Float64 &rzl,
                                   Float64 &dxr,Float64 &dyr,Float64 &rzr)
{
   dxl = m_Dxl;
   dyl = m_Dyl;
   rzl = m_Rzl;
   dxr = m_Dxr;
   dyr = m_Dyr;
   rzr = m_Rzr;
}

void ConcLdBeam::GetForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   switch(m_Type)
      {
      case mtPinPin:
           ComputePPForces(x,fx,fy,mz);
           break;

      case mtPinFix:
           ComputePFForces(x,fx,fy,mz);
           break;

      case mtFixPin:
           ComputeFPForces(x,fx,fy,mz);
           break;

      case mtFixFix:
           ComputeFFForces(x,fx,fy,mz);
           break;
      }
}

void ConcLdBeam::GetDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   switch(m_Type)
      {
      case mtPinPin:
           ComputePPDeflection(x,dx,dy,rz);
           break;

      case mtPinFix:
           ComputePFDeflection(x,dx,dy,rz);
           break;

      case mtFixPin:
           ComputeFPDeflection(x,dx,dy,rz);
           break;

      case mtFixFix:
           ComputeFFDeflection(x,dx,dy,rz);
           break;
      }
}

void ConcLdBeam::ComputeReactions()
{
   switch(m_Type)
      {
      case mtPinPin:
           ComputePPReactions();
           break;

      case mtPinFix:
           ComputePFReactions();
           break;

      case mtFixPin:
           ComputeFPReactions();
           break;

      case mtFixFix:
           ComputeFFReactions();
           break;
      }
}

void ConcLdBeam::ComputeDisplacements()
{
   switch(m_Type)
      {
      case mtPinPin:
           ComputePPDisplacements();
           break;

      case mtPinFix:
           ComputePFDisplacements();
           break;

      case mtFixPin:
           ComputeFPDisplacements();
           break;

      case mtFixFix:
           ComputeFFDisplacements();
           break;
      }
}

void ConcLdBeam::ComputePPReactions()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePPReactionsFx();
           break;

      case ForceY:
           ComputePPReactionsFy();
           break;

      case MomentZ:
           ComputePPReactionsMz();
           break;
      }
}

void ConcLdBeam::ComputePFReactions()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePFReactionsFx();
           break;

      case ForceY:
           ComputePFReactionsFy();
           break;

      case MomentZ:
           ComputePFReactionsMz();
           break;
      }
}

void ConcLdBeam::ComputeFPReactions()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFPReactionsFx();
           break;

      case ForceY:
           ComputeFPReactionsFy();
           break;

      case MomentZ:
           ComputeFPReactionsMz();
           break;
      }
}

void ConcLdBeam::ComputeFFReactions()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFFReactionsFx();
           break;

      case ForceY:
           ComputeFFReactionsFy();
           break;

      case MomentZ:
           ComputeFFReactionsMz();
           break;
      }
}

void ConcLdBeam::ComputePPDisplacements()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePPDisplacementsFx();
           break;

      case ForceY:
           ComputePPDisplacementsFy();
           break;

      case MomentZ:
           ComputePPDisplacementsMz();
           break;
      }
}

void ConcLdBeam::ComputePFDisplacements()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePFDisplacementsFx();
           break;

      case ForceY:
           ComputePFDisplacementsFy();
           break;

      case MomentZ:
           ComputePFDisplacementsMz();
           break;
      }
}

void ConcLdBeam::ComputeFPDisplacements()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFPDisplacementsFx();
           break;

      case ForceY:
           ComputeFPDisplacementsFy();
           break;

      case MomentZ:
           ComputeFPDisplacementsMz();
           break;
      }
}

void ConcLdBeam::ComputeFFDisplacements()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFFDisplacementsFx();
           break;

      case ForceY:
           ComputeFFDisplacementsFy();
           break;

      case MomentZ:
           ComputeFFDisplacementsMz();
           break;
      }
}

void ConcLdBeam::ComputePPForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePPForcesFx(x,fx,fy,mz);
           break;

      case ForceY:
           ComputePPForcesFy(x,fx,fy,mz);
           break;

      case MomentZ:
           ComputePPForcesMz(x,fx,fy,mz);
           break;
      }
}

void ConcLdBeam::ComputePFForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePFForcesFx(x,fx,fy,mz);
           break;

      case ForceY:
           ComputePFForcesFy(x,fx,fy,mz);
           break;

      case MomentZ:
           ComputePFForcesMz(x,fx,fy,mz);
           break;
      }
}

void ConcLdBeam::ComputeFPForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFPForcesFx(x,fx,fy,mz);
           break;

      case ForceY:
           ComputeFPForcesFy(x,fx,fy,mz);
           break;

      case MomentZ:
           ComputeFPForcesMz(x,fx,fy,mz);
           break;
      }
}

void ConcLdBeam::ComputeFFForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFFForcesFx(x,fx,fy,mz);
           break;

      case ForceY:
           ComputeFFForcesFy(x,fx,fy,mz);
           break;

      case MomentZ:
           ComputeFFForcesMz(x,fx,fy,mz);
           break;
      }
}

void ConcLdBeam::ComputePPDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePPDeflectionFx(x,dx,dy,rz);
           break;

      case ForceY:
           ComputePPDeflectionFy(x,dx,dy,rz);
           break;

      case MomentZ:
           ComputePPDeflectionMz(x,dx,dy,rz);
           break;
      }
}

void ConcLdBeam::ComputePFDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePFDeflectionFx(x,dx,dy,rz);
           break;

      case ForceY:
           ComputePFDeflectionFy(x,dx,dy,rz);
           break;

      case MomentZ:
           ComputePFDeflectionMz(x,dx,dy,rz);
           break;
      }
}

void ConcLdBeam::ComputeFPDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFPDeflectionFx(x,dx,dy,rz);
           break;

      case ForceY:
           ComputeFPDeflectionFy(x,dx,dy,rz);
           break;

      case MomentZ:
           ComputeFPDeflectionMz(x,dx,dy,rz);
           break;
      }
}

void ConcLdBeam::ComputeFFDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFFDeflectionFx(x,dx,dy,rz);
           break;

      case ForceY:
           ComputeFFDeflectionFy(x,dx,dy,rz);
           break;

      case MomentZ:
           ComputeFFDeflectionMz(x,dx,dy,rz);
           break;
      }
}

void ConcLdBeam::ComputePPReactionsFx()
{
  m_Fxl = -m_Q*m_b/m_L;
  m_Fyl = 0;
  m_Mzl = 0;

  m_Fxr = -m_Q*m_a/m_L;
  m_Fyr = 0;
  m_Mzr = 0;
}

void ConcLdBeam::ComputePPReactionsFy()
{
  m_Fxl = 0;
  m_Fyl = -m_Q*m_b/m_L;
  m_Mzl = 0;

  m_Fxr = 0;
  m_Fyr = -m_Q*m_a/m_L;
  m_Mzr = 0;
}

void ConcLdBeam::ComputePPReactionsMz()
{
  m_Fxl = 0;
  m_Fyl = m_Q/m_L;
  m_Mzl = 0;

  m_Fxr = 0;
  m_Fyr = -m_Q/m_L;
  m_Mzr = 0;
}

void ConcLdBeam::ComputePFReactionsFx()
{
   ComputePPReactionsFx();
}

void ConcLdBeam::ComputePFReactionsFy()
{
  Float64 mL2 = m_L*m_L;
  Float64 mL3 = mL2*m_L;
  Float64 mb2 = m_b*m_b;
  Float64 mb3 = mb2*m_b;

  m_Fxl = 0;
  m_Fyl = m_Q*(mb3 - 3*mb2*m_L)/(2*mL3);
  m_Mzl = 0;

  m_Fxr = 0;
  m_Fyr = -(m_Fyl + m_Q);
  m_Mzr = m_Fyl*m_L + m_Q*m_b;
}

void ConcLdBeam::ComputePFReactionsMz()
{
  Float64 mL2 = m_L*m_L;
  Float64 mL3 = mL2*m_L;
  Float64 ma2 = m_a*m_a;

  m_Fxl = 0;
  m_Fyl = 3*m_Q*(mL2 - ma2)/(2*mL3);
  m_Mzl = 0;

  m_Fxr = 0;
  m_Fyr = -3*m_Q*(mL2 - ma2)/(2*mL3);
  m_Mzr = m_Fyl*m_L - m_Q;
}

void ConcLdBeam::ComputeFPReactionsFx()
{
   ComputePPReactionsFx();
}

void ConcLdBeam::ComputeFPReactionsFy()
{
  Float64 mL2 = m_L*m_L;
  Float64 mL3 = mL2*m_L;
  Float64 ma2 = m_a*m_a;
  Float64 mb2 = m_b*m_b;

/*
  Fxr = 0;
  Fyr = Q*(b3 - 3*b2*L)/(2*L3);
  Mzr = 0;

  Fxl = 0;
  Fyl = -(Fyr + Q);
  Mzl = -(Fyr*L + Q*a);
*/
  m_Fxl = 0;
  m_Fyl = -m_Q*m_b*(3*mL2 - mb2)/(2*mL3);
  m_Mzl = -m_Q*m_a*m_b*(m_b+m_L)/(2*mL2);

  m_Fxr = 0;
  m_Fyr = -m_Q*ma2*(m_b+2*m_L)/(2*mL3);
  m_Mzr = 0;
}

void ConcLdBeam::ComputeFPReactionsMz()
{
  Float64 mL2 = m_L*m_L;
  Float64 mL3 = mL2*m_L;
  Float64 mb2 = m_b*m_b;

  m_Fxl = 0;
  m_Fyl = 3*m_Q*(mL2 - mb2)/(2*mL3);
  m_Mzl = m_Fyl*m_L - m_Q;

  m_Fxr = 0;
  m_Fyr = -3*m_Q*(mL2 - mb2)/(2*mL3);
  m_Mzr = 0;
}

void ConcLdBeam::ComputeFFReactionsFx()
{
   ComputePPReactionsFx();
}

void ConcLdBeam::ComputeFFReactionsFy()
{
   Float64 mL2 = m_L*m_L;
   Float64 mL3 = mL2*m_L;
   Float64 ma2 = m_a*m_a;
   Float64 mb2 = m_b*m_b;

   m_Fxl = 0;
   m_Fyl = -m_Q*mb2*(3*m_a + m_b)/mL3;
   m_Mzl = -m_Q*m_a*mb2/mL2;

   m_Fxr = 0;
   m_Fyr = -m_Q*ma2*(3*m_b + m_a)/mL3;
   m_Mzr =  m_Q*ma2*m_b/mL2;
}

void ConcLdBeam::ComputeFFReactionsMz()
{
  Float64 mL2 = m_L*m_L;
  Float64 mL3 = mL2*m_L;
  Float64 ma2 = m_a*m_a;

   m_Fxl = 0;
   m_Fyl = 6*m_Q*(m_a*m_L - ma2)/mL3;
   m_Mzl = m_Q*(4*m_L*m_a - 3*ma2 - mL2)/mL2;

   m_Fxr = 0;
   m_Fyr = -6*m_Q*(m_a*m_L - ma2)/mL3;
   m_Mzr = m_Q*(2*m_L*m_a - 3*ma2)/mL2;
}

void ConcLdBeam::ComputePPDisplacementsFx()
{
   m_Dxl = 0;
   m_Dyl = 0;
   m_Rzl = 0;

   m_Dxr = 0;
   m_Dyr = 0;
   m_Rzr = 0;
}

void ConcLdBeam::ComputePPDisplacementsFy()
{
   Float64 mb2 = m_b*m_b;
   Float64 mb3 = mb2*m_b;

   m_Dxl = 0;
   m_Dyl = 0;
   m_Rzl = m_Q*(m_b*m_L - mb3/m_L)/(6*m_EI);

   m_Dxr = 0;
   m_Dyr = 0;
   m_Rzr = -m_Q*(2*m_b*m_L + mb3/m_L - 3*mb2)/(6*m_EI);
}

void ConcLdBeam::ComputePPDisplacementsMz()
{
   Float64 ma2 = m_a*m_a;

   m_Dxl = 0;
   m_Dyl = 0;
   m_Rzl = m_Q*(2*m_L - 6*m_a + 3*ma2/m_L)/(6*m_EI);

   m_Dxr = 0;
   m_Dyr = 0;
   m_Rzr = -m_Q*(m_L - 3*ma2/m_L)/(6*m_EI);
}

void ConcLdBeam::ComputePFDisplacementsFx()
{
   ComputePPDisplacementsFx();
}

void ConcLdBeam::ComputePFDisplacementsFy()
{
   Float64 ma2 = m_a*m_a;
   Float64 ma3 = ma2*m_a;

   m_Dxl = 0;
   m_Dyl = 0;
   m_Rzl = m_Q*(ma2 - ma3/m_L)/(4*m_EI);

   m_Dxr = 0;
   m_Dyr = 0;
   m_Rzr = 0;
}

void ConcLdBeam::ComputePFDisplacementsMz()
{
   Float64 mL2 = m_L*m_L;

   m_Dxl = 0;
   m_Dyl = 0;
   m_Rzl = (m_Q*(m_L-m_a) - m_Fyl*mL2/2)/(m_EI);

   m_Dxr = 0;
   m_Dyr = 0;
   m_Rzr = 0;
}

void ConcLdBeam::ComputeFPDisplacementsFx()
{
   ComputePPDisplacementsFx();
}

void ConcLdBeam::ComputeFPDisplacementsFy()
{
   Float64 mL2 = m_L*m_L;
   Float64 ma2 = m_a*m_a;

   m_Dxl = 0;
   m_Dyl = 0;
   m_Rzl = 0;

   m_Dxr = 0;
   m_Dyr = 0;
   m_Rzr = (m_Q*(mL2 - 2*m_L*m_a + ma2) + m_Fyl*mL2 - 2*m_L*m_Mzl)/(2*m_EI);
}

void ConcLdBeam::ComputeFPDisplacementsMz()
{
   Float64 mL2 = m_L*m_L;

   m_Dxl = 0;
   m_Dyl = 0;
   m_Rzl = 0;

   m_Dxr = 0;
   m_Dyr = 0;
   m_Rzr = (m_Fyl*mL2 - 2*m_Mzl*m_L - 2*m_Q*(m_L-m_a))/(2*m_EI);
}

void ConcLdBeam::ComputeFFDisplacementsFx()
{
   ComputePPDisplacementsFx();
}

void ConcLdBeam::ComputeFFDisplacementsFy()
{
   m_Dxl = 0;
   m_Dyl = 0;
   m_Rzl = 0;

   m_Dxr = 0;
   m_Dyr = 0;
   m_Rzr = 0;
}

void ConcLdBeam::ComputeFFDisplacementsMz()
{
   m_Dxl = 0;
   m_Dyl = 0;
   m_Rzl = 0;

   m_Dxr = 0;
   m_Dyr = 0;
   m_Rzr = 0;
}

void ConcLdBeam::ComputePPForcesFx(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   fy = 0;
   mz = 0;
   if (x < m_a)
   {
      fx = -m_Fxl;
   }
   else
   {
      fx = -(m_Fxl + m_Q);
   }
}

void ConcLdBeam::ComputePPForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   fx = 0;
   if (x <m_a)
   {
      fy = m_Fyl;
      mz = m_Fyl*x;
   }
   else
   {
      fy = m_Fyl + m_Q;
      mz = m_Fyl*x + m_Q*(x-m_a);
   }
}

void ConcLdBeam::ComputePPForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   fx = 0;
   if (x < m_a)
   {
      fy = m_Fyl;
      mz = m_Fyl*x;
   }
   else
   {
      fy = m_Fyl;
      mz = m_Fyl*x - m_Q;
   }
}

void ConcLdBeam::ComputePFForcesFx(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   ComputePPForcesFx(x,fx,fy,mz);
}

void ConcLdBeam::ComputePFForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   fx = 0;
   if (x < m_a)
   {
      fy = m_Fyl;
      mz = m_Fyl*x;
   }
   else
   {
      fy = m_Fyl + m_Q;
      mz = m_Fyl*x + m_Q*(x-m_a);
   }
}

void ConcLdBeam::ComputePFForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   fx = 0;
   if (x < m_a)
   {
      fy = m_Fyl;
      mz = m_Fyl*x;
   }
   else
   {
      fy = m_Fyl;
      mz = m_Fyl*x - m_Q;
   }
}

void ConcLdBeam::ComputeFPForcesFx(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   ComputePPForcesFx(x,fx,fy,mz);
}

void ConcLdBeam::ComputeFPForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   fx = 0;
   if (x < m_a)
   {
      fy = m_Fyl;
      mz = m_Fyl*x - m_Mzl;
   }
   else
   {
      fy = m_Fyl + m_Q;
      mz = m_Fyl*x + m_Q*(x-m_a) - m_Mzl;
   }
}

void ConcLdBeam::ComputeFPForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   fx = 0;
   if (x < m_a)
   {
      fy = m_Fyl;
      mz = m_Fyl*x - m_Mzl;
   }
   else
   {
      fy = m_Fyl;
      mz = m_Fyl*x - m_Q - m_Mzl;
   }
}

void ConcLdBeam::ComputeFFForcesFx(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   ComputePPForcesFx(x,fx,fy,mz);
}

void ConcLdBeam::ComputeFFForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   fx = 0;
   if (x < m_a)
   {
      fy = m_Fyl;
      mz = m_Fyl*x - m_Mzl;
   }
   else
   {
      fy = m_Fyl + m_Q;
      mz = m_Fyl*x - m_Mzl + m_Q*(x-m_a);
   }
}

void ConcLdBeam::ComputeFFForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   fx = 0;
   if (x < m_a)
   {
      fy = m_Fyl;
      mz = m_Fyl*x - m_Mzl;
   }
   else
   {
      fy = m_Fyl;
      mz = m_Fyl*x - m_Mzl - m_Q;
   }
}

void ConcLdBeam::ComputePPDeflectionFx(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   dy = 0;
   rz = 0;

   if (x < m_a)
   {
      dx = m_Q*m_b*x/(m_EA*m_L);
   }
   else
   {
      dx = m_Q*m_a*(m_L-x)/(m_EA*m_L);
   }
}

void ConcLdBeam::ComputePPDeflectionFy(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   Float64 mb2 = m_b*m_b;
   Float64 mL2 = m_L*m_L;
   Float64 x2 = x*x;

   dx = 0;
   if (x < m_a)
   {
      dy = m_Q*m_b*x*(2*m_L*(m_L-x) - mb2 - pow((m_L-x),2))/(6*m_EI*m_L);
      rz = -m_Q*m_b*(3*x2 + mb2 - mL2)/(6*m_EI*m_L);
   }
   else
   {
      dy = m_Q*m_a*(m_L-x)*(2*m_L*m_b - mb2 - pow((m_L-x),2))/(6*m_EI*m_L);
      rz = m_Q*m_a*(3*x2 + mb2 + 3*mL2 - 2*m_L*m_b - 6*m_L*x)/(6*m_EI*m_L);
   }
}

void ConcLdBeam::ComputePPDeflectionMz(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   Float64 ma2 = m_a*m_a;
   Float64 x2 = x*x;
   Float64 x3 = x2*x;

   dx = 0;
   if (x < m_a)
   {
      dy = m_Q*(x3/m_L - (6*m_a - 3*ma2/m_L - 2*m_L)*x)/(6*m_EI);
      rz = m_Q*(3*x2/m_L - 6*m_a + 3*ma2/m_L + 2*m_L)/(6*m_EI);
   }
   else
   {
      dy = m_Q*(x3/m_L + (3*ma2/m_L + 2*m_L)*x - 3*ma2 - 3*x2)/(6*m_EI);
      rz = m_Q*(3*x2/m_L + 2*m_L + 3*ma2/m_L -6*x)/(6*m_EI);
   }
}

void ConcLdBeam::ComputePFDeflectionFx(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   ComputePPDeflectionFx(x,dx,dy,rz);
}

void ConcLdBeam::ComputePFDeflectionFy(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   Float64 mL2 = m_L*m_L;
   Float64 ma2 = m_a*m_a;
   Float64 x2 = x*x;
   Float64 x3 = x2*x;

   dx = 0;
   if (x < m_a)
   {
      dy = (m_Fyl*(x3 - 3*mL2*x) + m_Q*x*(6*m_a*m_L - 3*ma2 - 3*mL2))/(6*m_EI);
      rz = (m_Q*(2*m_a*m_L - ma2 - mL2) - m_Fyl*(mL2 - x2))/(2*m_EI);
   }
   else
   {
      Float64 mL3 = mL2*m_L;

      dy = (m_Fyl*(x3 - 3*mL2*x + 2*mL3) + m_Q*(x3 - 3*m_a*x2 + (6*m_a*m_L - 3*mL2)*x + 2*mL3 - 3*m_a*mL2))/(6*m_EI);
      rz = (m_Q*(x2 - 2*m_a*x - mL2 + 2*m_a*m_L) - m_Fyl*(mL2 - x2))/(2*m_EI);
   }
}

void ConcLdBeam::ComputePFDeflectionMz(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   Float64 mL2 = m_L*m_L;
   Float64 x2 = x*x;
   Float64 x3 = x2*x;

   dx = 0;
   if (x < m_a)
   {
      dy = (m_Q*x*(m_L-m_a) + m_Fyl*(x3/6 - mL2*x/2))/(m_EI);
      rz = (m_Q*(m_L-m_a) - m_Fyl*(mL2/2 - x2/2))/(m_EI);
   }
   else
   {
      Float64 mL3 = mL2*m_L;

      dy = (m_Q*(m_L*x - x2/2 - mL2/2) + m_Fyl*(x3/6 - mL2*x/2 + mL3/3))/(m_EI);
      rz = (m_Q*(m_L-x) - m_Fyl*(mL2/2 - x2/2))/(m_EI);
   }
}

void ConcLdBeam::ComputeFPDeflectionFx(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   ComputePPDeflectionFx(x,dx,dy,rz);
}

void ConcLdBeam::ComputeFPDeflectionFy(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   Float64 x2 = x*x;
   Float64 x3 = x2*x;

   dx = 0;
   if (x < m_a)
   {
      dy = (m_Fyl*x3 - 3*m_Mzl*x2)/(6*m_EI);
      rz = (m_Fyl*x2 - 2*m_Mzl*x)/(2*m_EI);
   }
   else
   {
      Float64 mL2 = m_L*m_L;
      Float64 ma2 = m_a*m_a;

      dy = (x-m_L)*(m_Q*(m_L*x + x2 - 3*x*m_a + mL2 + 3*ma2 - 3*m_L*m_a) - 3*(m_L+x)*m_Mzl + (x2 + m_L*x + mL2)*m_Fyl)/(6*m_EI);
      rz = (m_Q*(x2 - 2*m_a*x + ma2) + m_Fyl*x2 - 2*m_Mzl*x)/(2*m_EI);
   }
}

void ConcLdBeam::ComputeFPDeflectionMz(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   Float64 x2 = x*x;
   Float64 x3 = x2*x;

   dx = 0;
   if (x < m_a)
   {
      dy = (m_Fyl*x3 - 3*m_Mzl*x2)/(6*m_EI);
      rz = (m_Fyl*x2 - 2*m_Mzl*x)/(2*m_EI);
   }
   else
   {
      Float64 mL2 = m_L*m_L;

      dy = (m_L-x)*(3*(m_L+x)*m_Mzl - 3*m_Q*(2*m_a - x - m_L) - m_Fyl*(m_L*x + x2 + mL2))/(6*m_EI);
      rz = (m_Fyl*x2 - 2*m_Mzl*x - 2*m_Q*(x-m_a))/(2*m_EI);
   }
}

void ConcLdBeam::ComputeFFDeflectionFx(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   ComputePPDeflectionFx(x,dx,dy,rz);
}

void ConcLdBeam::ComputeFFDeflectionFy(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   Float64 mL2 = m_L*m_L;
   Float64 mL3 = mL2*m_L;

   dx = 0;
   if (x < m_a)
   {
      Float64 mb2 = m_b*m_b;
      Float64 x2 = x*x;

      dy = m_Q*mb2*x2*(3*m_a*m_L - 3*m_a*x - m_b*x)/(6*m_EI*mL3);
      rz = m_Q*mb2*x*(2*m_a*m_L - 3*m_a*x - m_b*x)/(2*m_EI*mL3);
   }
   else
   {
      Float64 ma2 = m_a*m_a;

      dy = m_Q*ma2*pow(m_L-x,2)*(3*m_b*m_L - (3*m_b + m_a)*(m_L-x))/(6*m_EI*mL3);
      rz = m_Q*ma2*(m_L-x)*(m_a*m_L + m_b*m_L - 3*m_b*x - m_a*x)/(2*m_EI*mL3);
   }
}

void ConcLdBeam::ComputeFFDeflectionMz(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   Float64 x2 = x*x;
   Float64 x3 = x2*x;

   dx = 0;
   if (x < m_a)
   {
      dy = (m_Fyl*x3 - 3*m_Mzl*x2)/(6*m_EI);
      rz = (3*m_Fyl*x2 - 6*m_Mzl*x)/(6*m_EI);
   }
   else
   {
      Float64 mL2 = m_L*m_L;
      Float64 mL3 = mL2*m_L;

      dy = (m_Fyl*(x3 + 2*mL3 - 3*mL2*x) + (m_Q+m_Mzl)*(6*m_L*x - 3*x2 - 3*mL2))/(6*m_EI);
      rz = (6*(m_Q+m_Mzl)*(m_L-x) - 3*m_Fyl*(mL2 - x2))/(6*m_EI);
   }
}



//
//

//
// MemberStrainBeam
//
MemberStrainBeam::MemberStrainBeam(Float64 qAxial, Float64 qCurvature,Float64 a,Float64 l,Float64 ea,Float64 ei,MbrType type) :
Beam(l,ea,ei,type),
m_A(a),
m_Qx(qAxial),
m_Qz(qCurvature)
{
   ComputeReactions();
   ComputeDisplacements();
}

void MemberStrainBeam::GetLoad(Float64& qAxial, Float64& qCurvature,Float64& a)
{
   qAxial = m_Qx;
   qCurvature = m_Qz;
   a = m_A;
}

void MemberStrainBeam::GetReactions(Float64 &fxl,Float64 &fyl,Float64 &mzl,
                                    Float64 &fxr,Float64 &fyr,Float64 &mzr)
{
   fxl = m_Fxl;
   fyl = m_Fyl;
   mzl = m_Mzl;
   fxr = m_Fxr;
   fyr = m_Fyr;
   mzr = m_Mzr;
}

void MemberStrainBeam::GetDisplacements(Float64 &dxl,Float64 &dyl,Float64 &rzl,
                                        Float64 &dxr,Float64 &dyr,Float64 &rzr)
{
   dxl = m_Dxl;
   dyl = m_Dyl;
   rzl = m_Rzl;
   dxr = m_Dxr;
   dyr = m_Dyr;
   rzr = m_Rzr;
}

void MemberStrainBeam::GetForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   ATLASSERT(x>=0.0 && x<=m_L);
   fx = m_Fxl;
   fy = m_Fyl;
   mz = m_Mzl + m_Fyl*x;
}

void MemberStrainBeam::GetDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   ATLASSERT(x>=0.0 && x<=m_L);
   Float64 x2 = x*x;
   Float64 x3 = x2*x;

   dx = 0.0;
   dy = m_Dyl + m_Rzl*x - m_Mzl*x2/(2*m_EI) + m_Fyl*x3/(6*m_EI);
   if ( m_A < x )
      dy += m_Qz*(x-m_A)*(x-m_A)/2;

   rz = m_Rzl - m_Mzl*x/m_EI + m_Fyl*x2/(2*m_EI);
   if ( m_A < x )
      rz += m_Qz*(x - m_A);
}

void MemberStrainBeam::ComputeReactions()
{
// axial is independent of beam type

   Float64 faxial = m_Qx*m_EA*(m_L-m_A)/m_L;
   m_Fxl = faxial;
   m_Fxr = -faxial;

   switch(m_Type)
      {
      case mtPinPin:
           ComputePPReactions();
           break;

      case mtPinFix:
           ComputePFReactions();
           break;

      case mtFixPin:
           ComputeFPReactions();
           break;

      case mtFixFix:
           ComputeFFReactions();
           break;
      }
}

void MemberStrainBeam::ComputeDisplacements()
{
   m_Dxl = 0.0;
   m_Dxr = 0.0;

   switch(m_Type)
      {
      case mtPinPin:
           ComputePPDisplacements();
           break;

      case mtPinFix:
           ComputePFDisplacements();
           break;

      case mtFixPin:
           ComputeFPDisplacements();
           break;

      case mtFixFix:
           ComputeFFDisplacements();
           break;
      }
}

// Equations taken from Roark's Formulas for Stress and Strain, 6th Edition
// Table 3, Equations 6c-6e

void MemberStrainBeam::ComputePPReactions()
{
  m_Fyl = 0;
  m_Mzl = 0;

  m_Fyr = 0;
  m_Mzr = 0;
}

void MemberStrainBeam::ComputePFReactions()
{
  // Table 3, Equation 6c
  m_Fyl = (-3.0*m_EI*m_Qz)*(m_L*m_L - m_A*m_A)/(2.0*m_L*m_L*m_L);
  m_Mzl = 0;

  m_Fyr = -m_Fyl;
  m_Mzr =  m_Fyl*m_L;
}

void MemberStrainBeam::ComputeFPReactions()
{
   // These formulas are derived from Table 3, Equation 6c.
   // The curvature is applied at the pinned end (in Eqn 6c the curvature is at the fixed end)
   // This case is is the mirror image of Equation 6c with a = 0 minus the mirror image of
   // Equation 6c with a measured from the right hand side.
   m_Fyr = -3*m_EI*m_Qz*(m_L-m_A)*(m_L-m_A)/(2.0*m_L*m_L*m_L);
   m_Mzr = 0;

   m_Fyl = -m_Fyr;
   m_Mzl = -m_Fyr*m_L;
}

void MemberStrainBeam::ComputeFFReactions()
{
   // Table 3, Equation 6d
  m_Fyl = -6*m_EI*m_A*m_Qz*(m_L - m_A)/(m_L*m_L*m_L);
  m_Mzl = -m_EI*m_Qz*(m_L - m_A)*(3*m_A - m_L)/(m_L*m_L);

  m_Fyr = -m_Fyl;
  m_Mzr = -m_EI*m_Qz*(m_L - m_A)*(3*m_A + m_L)/(m_L*m_L);
}

void MemberStrainBeam::ComputePPDisplacements()
{
   // Table 3, Equation 6e
   m_Dyl = 0;
   m_Rzl = -m_Qz*(m_L-m_A)*(m_L-m_A)/(2*m_L);

   m_Dyr = 0;
   m_Rzr = m_Qz*(m_L*m_L-m_A*m_A)/(2*m_L);
}

void MemberStrainBeam::ComputePFDisplacements()
{
   // Table 3, Equation 6c
   m_Dyl = 0;
   m_Rzl = m_Qz*(m_L-m_A)*(3*m_A - m_L)/(4*m_L);

   m_Dyr = 0;
   m_Rzr = 0;
}

void MemberStrainBeam::ComputeFPDisplacements()
{
   m_Dyl = 0;
   m_Rzl = 0;

   m_Dyr = 0;
   Float64 b = m_L - m_A;
   m_Rzr = m_Qz*m_L/4 + m_Qz*(m_L - b)*(3*b - m_L)/(4*m_L);
   //m_Rzr = m_Qz*(m_L*m_L - 2*m_A*m_L + 3*m_A*m_A)/(4*m_L); //???
}

void MemberStrainBeam::ComputeFFDisplacements()
{
   // Table 3, Equation 6d
   m_Dyl = 0;
   m_Rzl = 0;

   m_Dyr = 0;
   m_Rzr = 0;
}


//
// UniformMemberDistortionBeam
//
UniformMemberDistortionBeam::UniformMemberDistortionBeam(Float64 qAxial, Float64 qCurvature,Float64 a,Float64 b,Float64 l,Float64 ea,Float64 ei,MbrType type) :
Beam(l,ea,ei,type),
m_Case1Beam(qAxial,qCurvature,a,l,ea,ei,type),
m_Case2Beam(qAxial,qCurvature,b,l,ea,ei,type)
{
}

void UniformMemberDistortionBeam::GetLoad(Float64& qAxial, Float64& qCurvature,Float64& a,Float64& b)
{
   m_Case1Beam.GetLoad(qAxial,qCurvature,a);
   m_Case2Beam.GetLoad(qAxial,qCurvature,b);
}

void UniformMemberDistortionBeam::GetReactions(Float64 &fxl,Float64 &fyl,Float64 &mzl,
                                               Float64 &fxr,Float64 &fyr,Float64 &mzr)
{
   Float64 Fxl1,Fxl2;
   Float64 Fyl1,Fyl2;
   Float64 Mzl1,Mzl2;
   Float64 Fxr1,Fxr2;
   Float64 Fyr1,Fyr2;
   Float64 Mzr1,Mzr2;
   m_Case1Beam.GetReactions(Fxl1,Fyl1,Mzl1,Fxr1,Fyr1,Mzr1);
   m_Case2Beam.GetReactions(Fxl2,Fyl2,Mzl2,Fxr2,Fyr2,Mzr2);

   fxl = Fxl1 - Fxl2;
   fyl = Fyl1 - Fyl2;
   mzl = Mzl1 - Mzl2;
   fxr = Fxr1 - Fxr2;
   fyr = Fyr1 - Fyr2;
   mzr = Mzr1 - Mzr2;
}

void UniformMemberDistortionBeam::GetDisplacements(Float64 &dxl,Float64 &dyl,Float64 &rzl,
                                                   Float64 &dxr,Float64 &dyr,Float64 &rzr)
{
   Float64 Dxl1,Dxl2;
   Float64 Dyl1,Dyl2;
   Float64 Rzl1,Rzl2;
   Float64 Dxr1,Dxr2;
   Float64 Dyr1,Dyr2;
   Float64 Rzr1,Rzr2;
   m_Case1Beam.GetDisplacements(Dxl1,Dyl1,Rzl1,Dxr1,Dyr1,Rzr1);
   m_Case2Beam.GetDisplacements(Dxl2,Dyl2,Rzl2,Dxr2,Dyr2,Rzr2);

   dxl = Dxl1 - Dxl2;
   dyl = Dyl1 - Dyl2;
   rzl = Rzl1 - Rzl2;
   dxr = Dxr1 - Dxr2;
   dyr = Dyr1 - Dyr2;
   rzr = Rzr1 - Rzr2;
}

void UniformMemberDistortionBeam::GetForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   Float64 Fx1,Fy1,Mz1;
   Float64 Fx2,Fy2,Mz2;
   m_Case1Beam.GetForces(x,Fx1,Fy1,Mz1);
   m_Case2Beam.GetForces(x,Fx2,Fy2,Mz2);
   fx = Fx1 - Fx2;
   fy = Fy1 - Fy2;
   mz = Mz1 - Mz2;
}

void UniformMemberDistortionBeam::GetDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   Float64 Dx1,Dy1,Rz1;
   Float64 Dx2,Dy2,Rz2;
   m_Case1Beam.GetDeflection(x,Dx1,Dy1,Rz1);
   m_Case2Beam.GetDeflection(x,Dx2,Dy2,Rz2);
   dx = Dx1 - Dx2;
   dy = Dy1 - Dy2;
   rz = Rz1 - Rz2;
}

// 
//
//
TrapezoidalLdBeam::TrapezoidalLdBeam(Float64 wa, Float64 wb,Float64 la,Float64 lb,LoadDir dir,Float64 l,Float64 ea,Float64 ei,MbrType type) :
Beam(l,ea,ei,type)
{
   ATLASSERT(dir!=MomentZ); // not supported yet
   ATLASSERT(IsGE(0.0,la,ZTOL) && IsLE(la,l,ZTOL));
   ATLASSERT(IsGE(0.0,lb,ZTOL) && IsLE(lb,l,ZTOL));
   m_Dir = dir;
   if (la<lb)
   {
      m_La = la;
      m_Lb = lb;
      m_wa = wa;
      m_wb = wb;
   }
   else
   {
      m_La = lb;
      m_Lb = la;
      m_wa = wb;
      m_wb = wa;
   }

   ComputeReactions();
   ComputeDisplacements();
}

void TrapezoidalLdBeam::GetLoad(Float64 &wa, Float64& wb)
{
   wa = m_wa;
   wb = m_wb;
}

void TrapezoidalLdBeam::GetLocation(Float64 &la,Float64 &lb)
{
   la = m_La;
   lb = m_Lb;
}

Beam::LoadDir TrapezoidalLdBeam::GetDirection()
{
   return m_Dir;
}

void TrapezoidalLdBeam::GetReactions(Float64 &fxl,Float64 &fyl,Float64 &mzl,
                               Float64 &fxr,Float64 &fyr,Float64 &mzr)
{
   fxl = m_Fxl;
   fyl = m_Fyl;
   mzl = m_Mzl;
   fxr = m_Fxr;
   fyr = m_Fyr;
   mzr = m_Mzr;
}

void TrapezoidalLdBeam::GetDisplacements(Float64 &dxl,Float64 &dyl,Float64 &rzl,
                                   Float64 &dxr,Float64 &dyr,Float64 &rzr)
{
   dxl = m_Dxl;
   dyl = m_Dyl;
   rzl = m_Rzl;
   dxr = m_Dxr;
   dyr = m_Dyr;
   rzr = m_Rzr;
}

void TrapezoidalLdBeam::GetForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   switch(m_Type)
      {
      case mtPinPin:
           ComputePPForces(x,fx,fy,mz);
           break;

      case mtPinFix:
           ComputePFForces(x,fx,fy,mz);
           break;

      case mtFixPin:
           ComputeFPForces(x,fx,fy,mz);
           break;

      case mtFixFix:
           ComputeFFForces(x,fx,fy,mz);
           break;
      }
}

void TrapezoidalLdBeam::GetDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   switch(m_Type)
      {
      case mtPinPin:
           ComputePPDeflection(x,dx,dy,rz);
           break;

      case mtPinFix:
           ComputePFDeflection(x,dx,dy,rz);
           break;

      case mtFixPin:
           ComputeFPDeflection(x,dx,dy,rz);
           break;

      case mtFixFix:
           ComputeFFDeflection(x,dx,dy,rz);
           break;
      }
}

void TrapezoidalLdBeam::ComputeReactions()
{
   switch(m_Type)
      {
      case mtPinPin:
           ComputePPReactions();
           break;

      case mtPinFix:
           ComputePFReactions();
           break;

      case mtFixPin:
           ComputeFPReactions();
           break;

      case mtFixFix:
           ComputeFFReactions();
           break;
      }
}

void TrapezoidalLdBeam::ComputeDisplacements()
{
   switch(m_Type)
      {
      case mtPinPin:
           ComputePPDisplacements();
           break;

      case mtPinFix:
           ComputePFDisplacements();
           break;

      case mtFixPin:
           ComputeFPDisplacements();
           break;

      case mtFixFix:
           ComputeFFDisplacements();
           break;
      }
}

void TrapezoidalLdBeam::ComputePPReactions()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePPReactionsFx();
           break;

      case ForceY:
           ComputePPReactionsFy();
           break;

      case MomentZ:
           ComputePPReactionsMz();
           break;
      }
}

void TrapezoidalLdBeam::ComputePFReactions()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePFReactionsFx();
           break;

      case ForceY:
           ComputePFReactionsFy();
           break;

      case MomentZ:
           ComputePFReactionsMz();
           break;
      }
}

void TrapezoidalLdBeam::ComputeFPReactions()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFPReactionsFx();
           break;

      case ForceY:
           ComputeFPReactionsFy();
           break;

      case MomentZ:
           ComputeFPReactionsMz();
           break;
      }
}

void TrapezoidalLdBeam::ComputeFFReactions()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFFReactionsFx();
           break;

      case ForceY:
           ComputeFFReactionsFy();
           break;

      case MomentZ:
           ComputeFFReactionsMz();
           break;
      }
}

void TrapezoidalLdBeam::ComputePPDisplacements()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePPDisplacementsFx();
           break;

      case ForceY:
           ComputePPDisplacementsFy();
           break;

      case MomentZ:
           ComputePPDisplacementsMz();
           break;
      }
}

void TrapezoidalLdBeam::ComputePFDisplacements()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePFDisplacementsFx();
           break;

      case ForceY:
           ComputePFDisplacementsFy();
           break;

      case MomentZ:
           ComputePFDisplacementsMz();
           break;
      }
}

void TrapezoidalLdBeam::ComputeFPDisplacements()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFPDisplacementsFx();
           break;

      case ForceY:
           ComputeFPDisplacementsFy();
           break;

      case MomentZ:
           ComputeFPDisplacementsMz();
           break;
      }
}

void TrapezoidalLdBeam::ComputeFFDisplacements()
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFFDisplacementsFx();
           break;

      case ForceY:
           ComputeFFDisplacementsFy();
           break;

      case MomentZ:
           ComputeFFDisplacementsMz();
           break;
      }
}

void TrapezoidalLdBeam::ComputePPForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePPForcesFx(x,fx,fy,mz);
           break;

      case ForceY:
           ComputePPForcesFy(x,fx,fy,mz);
           break;

      case MomentZ:
           ComputePPForcesMz(x,fx,fy,mz);
           break;
      }
}

void TrapezoidalLdBeam::ComputePFForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePFForcesFx(x,fx,fy,mz);
           break;

      case ForceY:
           ComputePFForcesFy(x,fx,fy,mz);
           break;

      case MomentZ:
           ComputePFForcesMz(x,fx,fy,mz);
           break;
      }
}

void TrapezoidalLdBeam::ComputeFPForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFPForcesFx(x,fx,fy,mz);
           break;

      case ForceY:
           ComputeFPForcesFy(x,fx,fy,mz);
           break;

      case MomentZ:
           ComputeFPForcesMz(x,fx,fy,mz);
           break;
      }
}

void TrapezoidalLdBeam::ComputeFFForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFFForcesFx(x,fx,fy,mz);
           break;

      case ForceY:
           ComputeFFForcesFy(x,fx,fy,mz);
           break;

      case MomentZ:
           ComputeFFForcesMz(x,fx,fy,mz);
           break;
      }
}

void TrapezoidalLdBeam::ComputePPDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePPDeflectionFx(x,dx,dy,rz);
           break;

      case ForceY:
           ComputePPDeflectionFy(x,dx,dy,rz);
           break;

      case MomentZ:
           ComputePPDeflectionMz(x,dx,dy,rz);
           break;
      }
}

void TrapezoidalLdBeam::ComputePFDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputePFDeflectionFx(x,dx,dy,rz);
           break;

      case ForceY:
           ComputePFDeflectionFy(x,dx,dy,rz);
           break;

      case MomentZ:
           ComputePFDeflectionMz(x,dx,dy,rz);
           break;
      }
}

void TrapezoidalLdBeam::ComputeFPDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFPDeflectionFx(x,dx,dy,rz);
           break;

      case ForceY:
           ComputeFPDeflectionFy(x,dx,dy,rz);
           break;

      case MomentZ:
           ComputeFPDeflectionMz(x,dx,dy,rz);
           break;
      }
}

void TrapezoidalLdBeam::ComputeFFDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   switch(m_Dir)
      {
      case ForceX:
           ComputeFFDeflectionFx(x,dx,dy,rz);
           break;

      case ForceY:
           ComputeFFDeflectionFy(x,dx,dy,rz);
           break;

      case MomentZ:
           ComputeFFDeflectionMz(x,dx,dy,rz);
           break;
      }
}

// inline free function for determining deflection along bar between a and b
Float64 TrapezoidalLdBeamComputeFxFree(Float64 EA, Float64 W, Float64 wa, Float64 wb, Float64 a, Float64 b, Float64 x)
{
   Float64 x2 = x*x;
   Float64 x3 = x2*x;
   Float64 a2 = a*a;
   Float64 a3 = a2*a;

   ATLASSERT(b>a);
   ATLASSERT(IsGE(a,x,ZTOL) && IsLE(x,b,ZTOL));
   ATLASSERT(EA!=0);
   ATLASSERT(IsEqual(W, (wb+wa)/2.*(b-a),ZTOL));
   Float64 d = 1/EA * (W*x - (wb-wa)/(b-a)*(x3/6.-a*x2/2.+a2*x/2.-a3/6.)-wa*(x2/2.-a*x+a2/2.));
   return d;
}


void TrapezoidalLdBeam::ComputePPReactionsFx()
{
   m_Fyl=0;
   m_Fyr=0;
   m_Mzl=0;
   m_Mzr=0;
   m_Fyl_u=0;
   m_Fyl_t=0;
   m_Fyr_t=0;
   m_Mzl_u=0;
   m_Mzl_t=0;
   m_Fyr_u=0;
   m_Mzr_u=0;

   // Refer to Mathcad document AxialTrapezoidalLoad.mcd
   // and Imaging file AxialTrapezoidalLoad.tif for derivation of functions
   Float64 W = (m_wb+m_wa)/2. *(m_Lb-m_La); // force resultant
   Float64 db = TrapezoidalLdBeamComputeFxFree(m_EA,W,m_wa,m_wb,m_La,m_Lb, m_Lb); // deflection at b for free-ended bar

   m_Fxr = -db*m_EA/m_L;
   m_Fxl = -W-m_Fxr;
}

void TrapezoidalLdBeam::ComputePPReactionsFy()
{
   m_Fxl = 0;
   m_Fxr = 0;

   m_Mzl_u = 0;
   m_Mzl_t = 0;
   m_Mzl   = 0;

   m_Mzr_u = 0;
   m_Mzr_t = 0;
   m_Mzr   = 0;

   // reactions due to uniform portion
	// Fomulas 14 and 16
   Float64 d = m_L-0.5*m_Lb-0.5*m_La;  // distance from the right end to the center of the load
   Float64 c = m_Lb-m_La;	             // length of load
   Float64 W = m_wa*c;
   m_Fyl_u = -W*d/m_L;            // reaction at the left end
   m_Fyr_u = -W/m_L*(m_La+0.5*c); // reaction at the right end

	// Compute partial triangular load from a to b, load varying from zero to w
	// a and b measured from the left and. 
	// formulas 16
   d = m_L-m_La/3.-2./3.*m_Lb; // distance from the right end to the center of the load
   W = 0.5*(m_wb-m_wa)*c;		// total load

   m_Fyl_t = -W*d/m_L;
	m_Fyr_t = -W*(m_L-d)/m_L;
   m_Fyl = m_Fyl_u + m_Fyl_t;
	m_Fyr = m_Fyr_u + m_Fyr_t;
}

void TrapezoidalLdBeam::ComputePPReactionsMz()
{
   // Not implemented yet
   ATLASSERT(0);
   m_Fxl = 0;
   m_Fyl = 0;
   m_Mzl = 0;

   m_Fxr = 0;
   m_Fyr = 0;
   m_Mzr = 0;
}

void TrapezoidalLdBeam::ComputePFReactionsFx()
{
   ComputePPReactionsFx();
}

void TrapezoidalLdBeam::ComputePFReactionsFy()
{
   m_Fxr = 0;
   m_Fxl = 0;
   m_Mzl_u = 0;
   m_Mzl_t = 0;

   // shorten some variable names for readability
   Float64 L = m_L;
   Float64 a = L-m_Lb;
   Float64 b = L-m_La;

   Float64 L2 = L*L;
   Float64 L3 = L2*L;
   Float64 a2 = a*a;
   Float64 a3 = a2*a;
   Float64 b2 = b*b;
   Float64 b3 = b2*b;

   // compute for uniform portion
	// formulas 24
   Float64 d = L-b;    // distance from the right end to the center of the load
   Float64 c = b-a;    // length of load
   Float64 W = m_wa*c; // total load

   m_Fyl_u  = -W/(8.*L3)*(4.*L*(a2+a*b+b2)-a3-a*b2-a2*b-b3);
   m_Fyr_u  = -m_Fyl_u-W;
   m_Mzr_u  = m_Fyl_u*L + 0.5*W*(a+b);	    // reaction at the right end
   m_Mzl_u  = 0;

	// Compute partial triangular load from b to a, load varying from zero to w
	// a and b measured from the right and. 
	// formulas 26

   W = 0.5*(m_wb-m_wa)*c;		// total load

   Float64 rl = -W/(20.*L3)*((10.*a*b+15.*a2+5.*b2)*L-4.*a3-2.*a*b2-3.*a2*b-b3);        // reaction at the left end
   Float64 r2 = -W-rl;
   Float64 m2 = rl*L + W/3.*(2.*a+b);

   m_Fyl_t = rl;
   m_Fyr_t = r2;
   m_Mzr_t = m2;
   m_Mzl_t = 0;

   m_Fyl = m_Fyl_u + m_Fyl_t;
   m_Fyr = m_Fyr_u + m_Fyr_t;
   m_Mzr = m_Mzr_u + m_Mzr_t;
   m_Mzl = m_Mzl_u + m_Mzl_t;
}

void TrapezoidalLdBeam::ComputePFReactionsMz()
{
   // Not implemented yet
   ATLASSERT(0);
   m_Fxl = 0;
   m_Fyl = 0;
   m_Mzl = 0;

   m_Fxr = 0;
   m_Fyr = 0;
   m_Mzr = 0;
}

void TrapezoidalLdBeam::ComputeFPReactionsFx()
{
   ComputePPReactionsFx();
}

void TrapezoidalLdBeam::ComputeFPReactionsFy()
{
   m_Fxr = 0;
   m_Mzr = 0;
   m_Mzr_u = 0;
   m_Mzl_t = 0;
   m_Fxl = 0;

   // same equations as PF, just transposed
   Float64 L = m_L;
   Float64 a = m_La;
   Float64 b = m_Lb;
   Float64 wa = m_wb;
   Float64 wb = m_wa;

   // compute for uniform portion
	// formulas 24
   Float64 d = L-b;    // distance from the right end to the center of the load
   Float64 c = b-a;    // length of load
   Float64 W = wa*c; // total load

   Float64 L2 = L*L;
   Float64 L3 = L2*L;
   Float64 a2 = a*a;
   Float64 a3 = a2*a;
   Float64 b2 = b*b;
   Float64 b3 = b2*b;


   m_Fyr_u  = -W/(8.*L3)*(4.*L*(a2+a*b+b2)-a3-a*b2-a2*b-b3);
   m_Fyl_u  = -m_Fyr_u-W;
   m_Mzl_u  = -m_Fyr_u*L - 0.5*W*(a+b);	    // reaction at the right end

	// Compute partial triangular load from b to a, load varying from zero to w
	// a and b measured from the right and. 
	// formulas 26

   W = 0.5*(wb-wa)*c;		// total load

   Float64 r2 = -W/(20.*L3)*((10.*a*b+15.*a2+5.*b2)*L-4.*a3-2.*a*b2-3.*a2*b-b3);        // reaction at the left end
   Float64 r1 = -W-r2;
   Float64 m1 = -r2*L - W/3.*(2.*a+b);

   m_Fyr_t = r2;
   m_Fyr = m_Fyr_u + m_Fyr_t;
   m_Fyl = m_Fyl_u + r1;
   m_Mzl = m_Mzl_u + m1;
}

void TrapezoidalLdBeam::ComputeFPReactionsMz()
{
   // Not implemented yet
   ATLASSERT(0);
   m_Fxl = 0;
   m_Fyl = 0;
   m_Mzl = 0;

   m_Fxr = 0;
   m_Fyr = 0;
   m_Mzr = 0;
}

void TrapezoidalLdBeam::ComputeFFReactionsFx()
{
   ComputePPReactionsFx();
}

void TrapezoidalLdBeam::ComputeFFReactionsFy()
{
   m_Fxl = 0;
   m_Fxr = 0;

	// compute partial uniform load situation Fomulas 34
   // shorten some variable names for readability
   Float64 L = m_L;
   Float64 a = m_La;
   Float64 b = m_Lb;

   Float64 d = L-a/2.-b/2.; // distance from the right end to the center of the load
   Float64 c = b-a;         // length of load
   Float64 W = m_wa*c;		   // total load

   Float64 L2 = L*L;
   Float64 L3 = L2*L;
   Float64 c2 = c*c;
   Float64 c3 = c2*c;
   Float64 d2 = d*d;
   Float64 d3 = d2*d;

   m_Fyl_u  = -W/(4.*L2)*(12.*d2-8.*d3/L+2.*b*c2/L-c3/L-c2);        // reaction at the left end
   m_Fyr_u  = -W-m_Fyl_u;
   m_Mzl_u  = W/24./L*(24.*d3/L-6.*b*c2/L+3.*c3/L+4.*c2-24.*d2);
   m_Mzr_u  = W/24./L*(24.*d3/L-6.*b*c2/L+3.*c3/L+2.*c2-48.*d2+24.*d*L);	    // reaction at the right end

	// Compute partial triangular load from b to a, load varying from zero to w
	// a and b measured from the right and. 
	// formulas 36
   d = L-a/3.-2./3.*b;    // distance from the right end to the center of the load
   d2 = d*d;
   d3 = d2*d;

   W = 0.5*(m_wb-m_wa)*c; // total load

   Float64 rr1a = -W/L/L*(3.*d2-c2/6.+b*c2/3./L-17.*c3/135./L-2.*d3/L);        // reaction at the left end
   m_Fyl_t =  rr1a;
   m_Fyl = m_Fyl_u + m_Fyl_t;
   m_Fyr = m_Fyr_u - W-rr1a;

   Float64 mm1a = W/L*(d3/L+c2/9.+51./810.*c3/L-c2*b/6./L-d2);
   m_Mzl_t = mm1a;
   m_Mzl = m_Mzl_u + m_Mzl_t;
   m_Mzr = m_Mzr_u + W/L*(d3/L+c2/18.+51./810.*c3/L-c2*b/6./L-2.*d2+d*L);	    // reaction at the right end
}

void TrapezoidalLdBeam::ComputeFFReactionsMz()
{
   // Not implemented yet
   ATLASSERT(0);
   m_Fxl = 0;
   m_Fyl = 0;
   m_Mzl = 0;

   m_Fxr = 0;
   m_Fyr = 0;
   m_Mzr = 0;
}

void TrapezoidalLdBeam::ComputePPDisplacementsFx()
{
   // ends are fixed for axial loading
   m_Dxl = 0;
   m_Dyl = 0;
   m_Rzl = 0;

   m_Dxr = 0;
   m_Dyr = 0;
   m_Rzr = 0;
}

void TrapezoidalLdBeam::ComputePPDisplacementsFy()
{
   m_Dxl = 0;
   m_Dyl = 0;
   m_Dxr = 0;
   m_Dyr = 0;

   // compute partial uniform load situation 
	// Fomulas 14 and 16
   // shorten some variable names for readability
   Float64 L = m_L;
   Float64 a = m_La;
   Float64 b = m_Lb;

	Float64 d = L-0.5*b-0.5*a; // distance from the right end to the center of the load
	Float64 c = b-a;		// length of load
   Float64 W = m_wa*c;
	
   Float64 L2 = L*L;
   Float64 L3 = L2*L;
   Float64 c2 = c*c;
   Float64 c3 = c2*c;
   Float64 d2 = d*d;
   Float64 d3 = d2*d;

	m_Rzl = -1/(48.*m_EI)*((  8.*m_Fyl_u*L2) + W*(8.*d3/L -  2.*b*c2/L + c3/L + 2.*c2));
	m_Rzr = -1/(48.*m_EI)*((-16.*m_Fyl_u*L2) - W*(24.*d2 - 8.*d3/L + 2.*b*c2/L - c3/L ));

	// Compute partial triangular load from a to b, load varying from zero to w
	// a and b measured from the left and. 
	// formulas 16
   d = L-a/3.-2./3.*b; // distance from the right end to the center of the load
   d2 = d*d;
   d3 = d2*d;

   W = 0.5*(m_wb-m_wa)*c;		// total load
   Float64 rzl = -1./(6.*m_EI)*(     m_Fyl_t*L2 + W*(d3/L + 1./6.*c2 + 17./270.*c3/L - 1/6.*c2*b/L));
   Float64 rzr = -1./(6.*m_EI)*(-2.* m_Fyl_t*L2 + W*(d3/L + 17./270.*c3/L - 1/6.*c2*b/L - 3.*d2));

   m_Rzl += rzl;
   m_Rzr += rzr;
}

void TrapezoidalLdBeam::ComputePPDisplacementsMz()
{
   // Not implemented yet
   ATLASSERT(0);
   m_Dxl = 0;
   m_Dyl = 0;
   m_Rzl = 0;

   m_Dxr = 0;
   m_Dyr = 0;
   m_Rzr = 0;
}

void TrapezoidalLdBeam::ComputePFDisplacementsFx()
{
   ComputePPDisplacementsFx();
}

void TrapezoidalLdBeam::ComputePFDisplacementsFy()
{
   m_Dxl = 0;
   m_Dyl = 0;
   m_Dxr = 0;
   m_Dyr = 0;
	m_Rzr = 0;

   // compute partial uniform load situation 
	// Formulas 24
   // shorten some variable names for readability
   Float64 L = m_L;
   Float64 a = L-m_Lb;
   Float64 b = L-m_La;

	Float64 c = b-a;		// length of load
   Float64 W = m_wa*c;

   Float64 L2 = L*L;
   Float64 L3 = L2*L;
   Float64 a2 = a*a;
   Float64 a3 = a2*a;
   Float64 c2 = c*c;
   Float64 c3 = c2*c;

	m_Rzl = -1/(m_EI)*(m_Fyl_u*L2/2. + W*(a2/2. + a*c/2. + c2/6.));

	// Compute partial triangular load from a to b, load varying from zero to w
	// a and b measured from the left and. 
	// formulas 16
   W = 0.5*(m_wb-m_wa)*c; // total load
   Float64 rzl = -1/(m_EI)*(m_Fyl_t*L2/2. + W*(c2/12. + a*c/3. + a2/2.));

   m_Rzl += rzl;
}

void TrapezoidalLdBeam::ComputePFDisplacementsMz()
{
   // Not implemented yet
   ATLASSERT(0);
   m_Dxl = 0;
   m_Dyl = 0;
   m_Rzl = 0;

   m_Dxr = 0;
   m_Dyr = 0;
   m_Rzr = 0;
}

void TrapezoidalLdBeam::ComputeFPDisplacementsFx()
{
   ComputePPDisplacementsFx();
}

void TrapezoidalLdBeam::ComputeFPDisplacementsFy()
{
   m_Dxl = 0;
   m_Dyl = 0;
   m_Dxr = 0;
   m_Dyr = 0;
	m_Rzl = 0;

   // compute partial uniform load situation 
	// Formulas 24
   // shorten some variable names for readability
   Float64 L = m_L;
   Float64 a = m_La;
   Float64 b = m_Lb;
   Float64 wa = m_wb;
   Float64 wb = m_wa;

	Float64 c = b-a;		// length of load
   Float64 W = wa*c;
	
   Float64 L2 = L*L;
   Float64 L3 = L2*L;
   Float64 a2 = a*a;
   Float64 a3 = a2*a;
   Float64 c2 = c*c;
   Float64 c3 = c2*c;

	m_Rzr = 1/(m_EI)*(m_Fyr_u*L2/2. + W*(a2/2. + a*c/2. + c2/6.));

	// Compute partial triangular load from a to b, load varying from zero to w
	// a and b measured from the left and. 
	// formulas 16
   W = 0.5*(wb-wa)*c;
   Float64 rzr = 1/(m_EI)*(m_Fyr_t*L2/2. + W*(c2/12. + a*c/3. + a2/2.));

   m_Rzr += rzr;
}

void TrapezoidalLdBeam::ComputeFPDisplacementsMz()
{
   // Not implemented yet
   ATLASSERT(0);
   m_Dxl = 0;
   m_Dyl = 0;
   m_Rzl = 0;

   m_Dxr = 0;
   m_Dyr = 0;
   m_Rzr = 0;
}

void TrapezoidalLdBeam::ComputeFFDisplacementsFx()
{
   ComputePPDisplacementsFx();
}

void TrapezoidalLdBeam::ComputeFFDisplacementsFy()
{
   m_Dxl = 0;
   m_Dyl = 0;
   m_Dxr = 0;
   m_Dyr = 0;
	m_Rzr = 0;
	m_Rzl = 0;

}

void TrapezoidalLdBeam::ComputeFFDisplacementsMz()
{
   // Not implemented yet
   ATLASSERT(0);
   m_Dxl = 0;
   m_Dyl = 0;
   m_Rzl = 0;

   m_Dxr = 0;
   m_Dyr = 0;
   m_Rzr = 0;
}

void TrapezoidalLdBeam::ComputePPForcesFx(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   fy = 0.0;
   mz = 0.0;

   if (x<=m_La)
   {
      fx = -m_Fxl;
   }
   else if (x<m_Lb) // in region between a and b
   {
      Float64 a = m_La;
      Float64 b = m_Lb;

      Float64 a2 = a*a;

      Float64 W = (m_wb+m_wa)/2. *(b-a); // force resultant
      Float64 pdab = W - (m_wb-m_wa)/(b-a)*(x*x/2.-a*x+a2/2.) - m_wa*(x-a); // force if right end were free
      fx = pdab + m_Fxr;
   }
   else
   {
      fx = m_Fxr;
   }
}

void TrapezoidalLdBeam::ComputePPForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   ATLASSERT(x>=0.0 && x<=m_L);

   fx = 0.0;

   // shorten some variable names for readability
   Float64 L = m_L;
   Float64 a = m_La;
   Float64 b = m_Lb;

   // compute partial uniform load situation 
	// Formulas 14 and 16
   Float64 d = L-0.5*b-0.5*a; // distance from the right end to the center of the load
   Float64 c = b-a;           // length of load
   Float64 W = m_wa*c;

   if (x<a) 
   {
      fy = m_Fyl_u;
      mz = m_Fyl_u*x;			
   }
   else 
   {
      if (x<b)
      {
	      fy = m_Fyl_u-W*(x-a)/c;
	      mz = m_Fyl_u*x-W*pow(x-a,2)/(2*c);
      }
      else
      {
	      fy = m_Fyl_u-W;
	      mz = m_Fyl_u*x-W*(x-0.5*a-0.5*b);
      }
   }

   // Compute partial triangular load from a to b, load varying from zero to w
   // a and b measured from the left and. 
   // formulas 16
   if(m_wb-m_wa!=0)
   {
      d = L-a/3.-2./3.*b; // distance from the right end to the center of the load
      W = 0.5*(m_wb-m_wa)*c;		// total load

      // compute shear, moment
      if (x<a) 
      {
         fy += m_Fyl_t;
         mz += m_Fyl_t*x;			
      }
      else 
      {
	      if (x<b)
	      {
		      fy += m_Fyl_t-pow((x-a)/c,2)*W;
            mz += m_Fyl_t*x-W*pow(x-a,3)/(3*c*c);						
	      }
	      else
	      {
		      fy += m_Fyl_t-W;
    	      mz += m_Fyl_t*x-W/3*(3*x-a-2*b);
         }
      }
   }
}

void TrapezoidalLdBeam::ComputePPForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   // Not implemented yet
   ATLASSERT(0);
   fx = 0;
   fy = 0;
   mz = 0;
}

void TrapezoidalLdBeam::ComputePFForcesFx(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   ComputePPForcesFx(x,fx,fy,mz);
}

void TrapezoidalLdBeam::ComputePFForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   ATLASSERT(x>=0.0 && x<=m_L);

   // shorten some variable names for readability
   Float64 L = m_L;
   Float64 a = m_La;
   Float64 b = m_Lb;

 	// compute partial uniform load situation Formulas 24
	Float64 d = L-b;  // distance from the right end to the center of the load
	Float64 c = b-a;  // length of load
	Float64 W = m_wa*c; // total load
	
	if (x<L-b) 
	{
		fy = m_Fyl_u;
		mz = m_Fyl_u*x;			
	}
	else 
	{
		if (x<L-a)
		{
			fy = m_Fyl_u-W*(x-d)/c;
			mz = m_Fyl_u*x-W*pow(x-d,2.)/(2.*c);
		}
		else
		{
			fy = m_Fyl_u-W;
			mz = m_Fyl_u*x-W*(x-d-c/2.);
		}
	}

// Compute partial triangular load from b to a, load varying from zero to w
// a and b measured from the right and. 
// formulas 26
  if (m_wb-m_wa != 0.)
  {
    	W = 0.5*(m_wb-m_wa)*c;		// total load

      if (x<L-b) 
		{
         fy += m_Fyl_t;
    		mz += m_Fyl_t*x;
		}
    	else 
	   {
		   if (x<(L-a))
			{
				fy += m_Fyl_t-W*pow((x-d)/c,2.);
    			mz += m_Fyl_t*x-W/3.*pow(x-d,3.)/(c*c);
    		}
			 else
    		{
	    		fy += m_Fyl_t-W;
    			mz += m_Fyl_t*x-W*(x-d-2.*c/3.);
			}
		}
	}
}


void TrapezoidalLdBeam::ComputePFForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   // Not implemented yet
   ATLASSERT(0);
   fx = 0;
   fy = 0;
   mz = 0;
}

void TrapezoidalLdBeam::ComputeFPForcesFx(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   ComputePPForcesFx(x,fx,fy,mz);
}

void TrapezoidalLdBeam::ComputeFPForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   ATLASSERT(0);
}

void TrapezoidalLdBeam::ComputeFPForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   // Not implemented yet
   ATLASSERT(0);
   fx = 0;
   fy = 0;
   mz = 0;
}

void TrapezoidalLdBeam::ComputeFFForcesFx(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   ComputePPForcesFx(x,fx,fy,mz);
}

void TrapezoidalLdBeam::ComputeFFForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   ATLASSERT(x>=0.0 && x<=m_L);

   // shorten some variable names for readability
   Float64 L = m_L;
   Float64 a = m_La;
   Float64 b = m_Lb;

// compute partial uniform load situation Fomulas 34
	Float64 d = L-a/2.-b/2.; // distance from the right end to the center of the load
	Float64 c = b-a;		// length of load
	Float64 W = m_wa*c;		// total load

	if (x<a) 
	{
		fy = m_Fyl_u;
		mz = -m_Mzl_u+m_Fyl_u*x;			
	}
	else 
	{
		if (x<b)
		{
			fy = m_Fyl_u-W*(x-a)/c;
			mz = -m_Mzl_u+m_Fyl_u*x-0.5*W*pow(x-a,2.)/c;
		}
		else
		{
			fy = m_Fyl_u-W;
			mz = -m_Mzl_u+m_Fyl_u*x-W*(x-L+d);
		}
	}

// Compute partial triangular load from b to a, load varying from zero to w
// a and b measured from the right and. 
// formulas 36
   if (m_wb-m_wa!=0.)
   {
      d = L-a/3.-2./3.*b; // distance from the right end to the center of the load
      W = 0.5*(m_wb-m_wa)*c;		// total load

    	if (x<a) 
	   {
		   fy += m_Fyl_t;
			mz += -m_Mzl_t+m_Fyl_t*x;
    	}
	   else 
		{
			if (x<b)
			 {
				 fy += m_Fyl_t-W*pow((x-a)/c,2);
     			 mz += -m_Mzl_t+m_Fyl_t*x-W/3.*pow(x-a,3.)/(c*c);
			}
			 else
    		{
	    		fy += m_Fyl_t-W;
		    	mz += -m_Mzl_t+m_Fyl_t*x-W*(x-L+d);
			}
    	}
   }
}


void TrapezoidalLdBeam::ComputeFFForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz)
{
   // Not implemented yet
   ATLASSERT(0);
   fx = 0;
   fy = 0;
   mz = 0;
}

void TrapezoidalLdBeam::ComputePPDeflectionFx(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   dy = 0.0;
   rz = 0.0;

   if (x<=m_La)
   {
      dx = -m_Fxl/m_EA * x;
   }
   else if (x<m_Lb)
   {
      Float64 W = (m_wb+m_wa)/2. *(m_Lb-m_La); // force resultant
      Float64 db = TrapezoidalLdBeamComputeFxFree(m_EA,W,m_wa,m_wb,m_La,m_Lb, x); // deflection at x for free-ended bar
      dx = db + m_Fxr/m_EA*x;
   }
   else
   {
      dx = -m_Fxr/m_EA*(m_L-x);
   }
}

void TrapezoidalLdBeam::ComputePPDeflectionFy(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   dx = 0.0;

   // compute partial uniform load situation 
   // Fomulas 14 and 16
   Float64 L = m_L;
   Float64 a = m_La;
   Float64 b = m_Lb;

	Float64 d = L-0.5*b-0.5*a; // distance from the right end to the center of the load
	Float64 c = b-a;		// length of load
   Float64 W = m_wa*c;
	
   Float64 L2 = L*L;
   Float64 c2 = c*c;
   Float64 c3 = c2*c;
   Float64 d2 = d*d;
   Float64 d3 = d2*d;
   Float64 x2 = x*x;
   Float64 x3 = x2*x;

	if (x<a) 
	{
		dy = 1/(48*m_EI)*(8*m_Fyl_u*(x3-L2*x)
			+W*x*(8*d3/L-2*b*c2/L+c3/L+2*c2));

		rz = 1/(48*m_EI)*(8*m_Fyl_u*(3*x2-L2)
			+W*(8*d3/L-2*b*c2/L+c3/L+2*c2));
	}
	else 
	{
		if (x<b)
		{
			dy = 1/(48*m_EI)*(8*m_Fyl_u*(x3-L2*x)
				+W*x*(8*d3/L-2*b*c2/L+c3/L+2*c2)
				-2*W*pow(x-a,4)/c);

			rz = 1/(48*m_EI)*(8*m_Fyl_u*(3*x2-L2)
				+W*(8*d3/L-2*b*c2/L+c3/L+2*c2)
				-8.*W*pow(x-a,3)/c);
		}
		else
		{
			dy = 1/(48*m_EI)*(8*m_Fyl_u*(x3-L2*x)
				  +W*x*(8*d3/L-2*b*c2/L+c3/L)
				  -8*W*pow(x-0.5*a-0.5*b,3)+W*(2*b*c2-c3));

			rz = 1/(48*m_EI)*(8*m_Fyl_u*(3*x2-L2)
			 	  +W*(8*d3/L-2*b*c2/L+c3/L)
				  -24.*W*pow(x-0.5*a-0.5*b,2));
		}
	}

	// Compute partial triangular load from a to b, load varying from zero to w
	// a and b measured from the left and. 
	// formulas 16
		
	if(m_wb-m_wa!=0)
	{

    	d = L-a/3.-2./3.*b; // distance from the right end to the center of the load
      d2 = d*d;
      d3 = d2*d;

    	W = 0.5*(m_wb-m_wa)*c;		// total load

		if (x<a) 
		 {
	    	dy += 1./(6.*m_EI)*( m_Fyl_t*(x3-L2*x)
		    		 +W*x*(d3/L+1./6.*c2*(1.-b/L)+17./270.*c3/L));

         rz += 1./(6.*m_EI)*( m_Fyl_t*(3*x2-L2)
		    		 +W*(d3/L+1./6.*c2*(1.-b/L)+17./270.*c3/L));
      }
    	else 
	   {
		   if (x<b)
			{
    			dy += 1./(6.*m_EI)*(m_Fyl_t*(x3-L2*x)
	    				 -W/10.* pow(x-a,5.)/(c2)
		    			 +W*x*(d3/L+c2/6.-c2*b/6./L+17./270.*c3/L));

            rz += 1./(6.*m_EI)*(m_Fyl_t*(3*x2-L2)
	    				 -W/2.*pow(x-a,4.)/(c2)
		    			 +W*(d3/L+c2/6.-c2*b/6./L+17./270.*c3/L));
			}
			 else
			 {
	    		dy += 1./(6.*m_EI)*( m_Fyl_t*(x3-L2*x)
		    			 -W* ( pow(x-a/3.-2.*b/3.,3.)-d3*x/L
			    		 -b/6.*c2*(1.-x/L)+17./270.*c3*(1-x/L) ) );

            rz += 1./(6.*m_EI)*( m_Fyl_t*(3.*x2-L2)
		    			 -W*(3*pow(x-a/3.-2.*b/3.,2.) - d3/L
			    		 -b/6.*c2*(-1./L)+17./270.*c3*(-1./L) ) );
			 }
		 }
	}
}

void TrapezoidalLdBeam::ComputePPDeflectionMz(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   // Not implemented yet
   dx = 0;
   dy = 0;
   rz = 0;
}

void TrapezoidalLdBeam::ComputePFDeflectionFx(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   ComputePPDeflectionFx(x,dx,dy,rz);
}

void TrapezoidalLdBeam::ComputePFDeflectionFy(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   dx = 0.0;
	// compute partial uniform load situation Fomulas 24
   Float64 L = m_L;
   Float64 a = m_La;
   Float64 b = m_Lb;

	Float64 d = L-b; // distance from the right end to the center of the load
	Float64 c = b-a;		// length of load
	Float64 W = m_wa*c;		// total load

   Float64 L2 = L*L;
   Float64 L3 = L2*L;
   Float64 a2 = a*a;
   Float64 c2 = c*c;
   Float64 x2 = x*x;
   Float64 x3 = x2*x;

	if (x<L-b) 
	{
		dy = 1./(m_EI)*( m_Fyl_u*(x3/6.-.5*L2*x)
			+W*x*(0.5*a2+.5*a*c+c2/6.));

		rz = 1./(m_EI)*( m_Fyl_u*(3.*x2/6.-.5*L2)
			+W*(0.5*a2+.5*a*c+c2/6.));
	}
	else 
	{
		if (x<L-a)
		{
			dy = 1./(m_EI)*( m_Fyl_u*(x3/6.-.5*L2*x)
				 +W*x*(.5*a2+.5*a*c+c2/6.)
			 	 -W*pow(x-d,4.)/(24.*c) );

			rz = 1./(m_EI)*( m_Fyl_u*(3.*x2/6.-.5*L2)
				 +W*(.5*a2+.5*a*c+c2/6.)
			 	 -4.*W*pow(x-d,3.)/(24.*c) );
		}
		else
		{
			dy = 1./(m_EI)*( m_Fyl_u*(x3/6.-.5*L2*x+L3/3.)
				+W*( pow(a+0.5*c,3.)/6.-0.5*pow(a+0.5*c,2.)*L
				 -1./6.*pow(x-d-0.5*c,3)+0.5*pow(a+0.5*c,2.)*x) );

			rz = 1./(m_EI)*( m_Fyl_u*(3*x2/6.-.5*L2)
				+W*( -1./2.*pow(x-d-0.5*c,2.)+0.5*pow(a+0.5*c,2.)) );
		}
	}

// Compute partial triangular load from b to a, load varying from zero to w
// a and b measured from the right and. 
// formulas 26
   if (m_wb-m_wa!=0.)
   {
      d = L-b; // distance from the right end to the center of the load
      W = 0.5*(m_wb-m_wa)*c;		// total load

      if (x<L-b) 
      {
         dy += 1./(m_EI)*( m_Fyl_t*(x3/6.-.5*L2*x)
		         +W*x*(0.5*a2+a*c/3.+c2/12.));

         rz += 1./(m_EI)*( m_Fyl_t*(3.*x2/6.-.5*L2)
		         +W*(0.5*a2+a*c/3.+c2/12.));
      }
      else 
      {
         if (x<(L-a))
         {
            dy += 1./(m_EI)*( m_Fyl_t*(x3/6.-.5*L2*x)
	    	          +W*x*(0.5*a2+a*c/3.+c2/12.)
		            -W*pow(x-d,5.)/(60.*c2) );

            rz += 1./(m_EI)*( m_Fyl_t*(3.*x2/6.-.5*L2)
	    	          +W*(0.5*a2+a*c/3.+c2/12.)
		            -5.*W*pow(x-d,4.)/(60.*c2) );
         }
          else
         {
            dy += 1./(m_EI)*( m_Fyl_t*(x3/6.-.5*L2*x+L3/3.)
	    		          +W*( 0.5*pow(a+c/3.,2.)*x-1./6.*pow(x-d-2./3.*c,3.)
		             +1./6.*pow(a+1./3.*c,3.)-0.5*pow(a+c/3.,2.)*L));

            rz += 1./(m_EI)*( m_Fyl_t*(3.*x2/6.-.5*L2)
	    		          +W*( 0.5*pow(a+c/3.,2.)-1./2.*pow(x-d-2./3.*c,2.)) );
         }
	   }
   }
}

void TrapezoidalLdBeam::ComputePFDeflectionMz(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   // Not implemented yet
   dx = 0;
   dy = 0;
   rz = 0;
}

void TrapezoidalLdBeam::ComputeFPDeflectionFx(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   ComputePPDeflectionFx(x,dx,dy,rz);
}

void TrapezoidalLdBeam::ComputeFPDeflectionFy(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   ATLASSERT(0);
}

void TrapezoidalLdBeam::ComputeFPDeflectionMz(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   // Not implemented yet
   ATLASSERT(0);
   dx = 0;
   dy = 0;
   rz = 0;
}

void TrapezoidalLdBeam::ComputeFFDeflectionFx(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   ComputePPDeflectionFx(x,dx,dy,rz);
}

void TrapezoidalLdBeam::ComputeFFDeflectionFy(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   dx = 0.0;

	// compute partial uniform load situation Fomulas 34
   Float64 L = m_L;
   Float64 a = m_La;
   Float64 b = m_Lb;

   Float64 d = L-a/2.-b/2.; // distance from the right end to the center of the load
   Float64 c = b-a;		// length of load
   Float64 W = m_wa*c;		// total load

   Float64 x2 = x*x;
   Float64 x3 = x2*x;

	if (x<a) 
	{
		dy = 1./(6.*m_EI)*(  m_Fyl_u*x3-3.*m_Mzl_u*x2);

      rz = 1./(6.*m_EI)*(  m_Fyl_u*3.*x2-6.*m_Mzl_u*x);
	}
	else 
	{
		if (x<b)
		{
			dy = 1./(6.*m_EI)*(  m_Fyl_u*x3 - 3.*m_Mzl_u*x2
				+W/4.*pow(x-a,4.)/c);

         rz = 1./(6.*m_EI)*(  3.*m_Fyl_u*x2 - 6.*m_Mzl_u*x
				+W*pow(x-a,3.)/c);
		}
		else
		{
			dy = 1./(6.*m_EI)*( m_Fyr_u*pow(L-x,3.)+3.*m_Mzr_u*pow(L-x,2.));

			rz = 1./(6.*m_EI)*( -3.*m_Fyr_u*pow(L-x,2.)-6.*m_Mzr_u*(L-x));
		}
	}

   // Compute partial triangular load from b to a, load varying from zero to w
   // a and b measured from the right and. 
   // formulas 36
   if (m_wb-m_wa!=0.)
   {
      Float64 dyt, rzt;
      d = L-a/3.-2./3.*b; // distance from the right end to the center of the load
      W = 0.5*(m_wb-m_wa)*c;		// total load

    	if (x<a) 
	   {
			 dyt = 1./(6.*m_EI)*( m_Fyl_t*x3 - 3.*m_Mzl_t*x2);

			 rzt = 1./(6.*m_EI)*( 3.*m_Fyl_t*x2 - 6.*m_Mzl_t*x);
    	}
	   else 
		{
			if (x<b)
			{
	    		dyt = 1./(m_EI)*( 1./6.*m_Fyl_t*x3 - .5*m_Mzl_t*x2
		    			 +1./60.*W*pow(x-a,5.)/c/c );

	    		rzt = 1./(m_EI)*( 1./2.*m_Fyl_t*x2 - m_Mzl_t*x
		    			 +1./12.*W*pow(x-a,4.)/c/c );
			}
			 else
    		{
            Float64 L2 = L*L;
            Float64 L3 = L2*L;
            Float64 d2 = d*d;
            Float64 d3 = d2*d;

			   dyt = 1./(6.*m_EI)*( m_Fyl_t*(x3-3.*L2*x+2*L3)
				    	 -3.*m_Mzl_t*pow(L-x,2.)
                   -W*(3.*d2*x+d3-3.*d2*L-pow(x-L+d,3.)));

			   rzt = 1./(6.*m_EI)*( m_Fyl_t*(3.*x2-3.*L2)
			    	   +6.*m_Mzl_t*(L-x)
                  -W*(3.*d2-3.*pow(x-L+d,2.)));
         }
    	}

      dy += dyt;
      rz += rzt;
   }
}

void TrapezoidalLdBeam::ComputeFFDeflectionMz(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz)
{
   // Not implemented yet
   ATLASSERT(0);
   dx = 0;
   dy = 0;
   rz = 0;
}

