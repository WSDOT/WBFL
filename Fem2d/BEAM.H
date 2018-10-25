///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2017  Washington State Department of Transportation
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

#if !defined FEM2D_BEAM_H_
#define FEM2D_BEAM_H_
#pragma once


#include <math.h>

#define BEAM_FIXED 0 
#define BEAM_RELEASE_MZ 0x0001
#define BEAM_RELEASE_FX 0x0002

class Beam
{
public:
   enum LoadDir {ForceX,ForceY,MomentZ};
   typedef LoadDir LoadDir;

// Public Implementation
public:
	Beam(Float64 l,Float64 ea,Float64 ei,long leftBC,long rightBC);
   Float64 GetLength();
	virtual void GetReactions(Float64 &fxl,Float64 &fyl,Float64 &mzl,
                             Float64 &fxr,Float64 &fyr,Float64 &mzr) = 0;
	virtual void GetDeflections(Float64 &dxl,Float64 &dyl,Float64 &rzl,
											Float64 &dxr,Float64 &dyr,Float64 &rzr) = 0;
	virtual void GetForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz) = 0;
	virtual void GetDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz) = 0;

// Protected Implementation
protected:
	Float64 m_L; // Length of the beam
	Float64 m_EA; // Cross sectional area
	Float64 m_EI; // Moment of inertia
	long m_LeftBC; // left end boundary condition
   long m_RightBC; // right end boundary condition
};

class ConcLdBeam : public Beam
{
// Public Implementation
public:
	ConcLdBeam(Float64 q,Float64 la,LoadDir dir,Float64 l,Float64 ea,Float64 ei,long leftBC,long rightBC);
   void GetLoad(Float64 &ld);
   void GetLocation(Float64 &loc);
   LoadDir GetDirection();
	void GetReactions(Float64 &fxl,Float64 &fyl,Float64 &mzl,Float64 &fxr,Float64 &fyr,Float64 &mzr);
	void GetDeflections(Float64 &dxl,Float64 &dyl,Float64 &rzl,
                         Float64 &dxr,Float64 &dyr,Float64 &rzr);
	void GetForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
	void GetDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);

// Private Implementation
private:
   Float64 m_Q; // Generalized load
   Float64 m_a,m_b;
   LoadDir m_Dir;
   Float64 m_Fxl, m_Fxr;
   Float64 m_Fyl, m_Fyr;
   Float64 m_Mzl, m_Mzr;
   Float64 m_Dxl, m_Dxr;
   Float64 m_Dyl, m_Dyr;
   Float64 m_Rzl, m_Rzr;

   void ComputeReactions();
   void ComputeDeflections();

   void ComputeAxialReactions();
   void ComputeBendingReactions();

   void ComputeAxialDeflections();
   void ComputeBendingDeflections();

   void ComputeAxialForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputeBendingForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputeAxialDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);
   void ComputeBendingDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);

   void ComputePPReactions();
   void ComputePFReactions();
   void ComputeFPReactions();
   void ComputeFFReactions();

   void ComputePPDeflections();
   void ComputePFDeflections();
   void ComputeFPDeflections();
   void ComputeFFDeflections();

   void ComputePPForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputePFForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputeFPForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputeFFForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

	void ComputePPDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);
	void ComputePFDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);
	void ComputeFPDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);
	void ComputeFFDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);

   void ComputePPReactionsFy();
   void ComputePPReactionsMz();

   void ComputePFReactionsFy();
   void ComputePFReactionsMz();

   void ComputeFPReactionsFy();
   void ComputeFPReactionsMz();

   void ComputeFFReactionsFy();
   void ComputeFFReactionsMz();

   void ComputePPDeflectionsFy();
   void ComputePPDeflectionsMz();

   void ComputePFDeflectionsFy();
   void ComputePFDeflectionsMz();

   void ComputeFPDeflectionsFy();
   void ComputeFPDeflectionsMz();

   void ComputeFFDeflectionsFy();
   void ComputeFFDeflectionsMz();

   void ComputePPForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputePPForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputePFForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputePFForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputeFPForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputeFPForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputeFFForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputeFFForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputePPDeflectionFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputePPDeflectionMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputePFDeflectionFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputePFDeflectionMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputeFPDeflectionFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputeFPDeflectionMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputeFFDeflectionFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputeFFDeflectionMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
};

class  TrapezoidalLdBeam : public Beam
{
// Public Implementation
// Equations based on Roark, Raymond J. and Young, Warren C. Formulas for Stress and Strain, 
// Fifth Edition, McGraw Hill, 1975, p104-113. 

public:
	TrapezoidalLdBeam(Float64 wa,Float64 wb,Float64 la,Float64 lb,LoadDir dir,Float64 l,Float64 ea,Float64 ei,long leftBC,long rightBC);
   void GetLoad(Float64 &wa, Float64& wb);
   void GetLocation(Float64 &la,Float64 &lb);
   LoadDir GetDirection();
	void GetReactions(Float64 &fxl,Float64 &fyl,Float64 &mzl,Float64 &fxr,Float64 &fyr,Float64 &mzr);
	void GetDeflections(Float64 &dxl,Float64 &dyl,Float64 &rzl,
                         Float64 &dxr,Float64 &dyr,Float64 &rzr);
	void GetForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
	void GetDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);

// Private Implementation
private:
   Float64 m_wa, m_wb;
   Float64 m_La,m_Lb;
   LoadDir m_Dir;

   // computed values
   Float64 m_Fxl, m_Fxr;
   Float64 m_Fyl, m_Fyr;
   Float64 m_Mzl, m_Mzr;
   Float64 m_Dxl, m_Dxr;
   Float64 m_Dyl, m_Dyr;
   Float64 m_Rzl, m_Rzr;

   // need to keep separate results for reactions at left end due to uniform and triangular
   // portions of load
   Float64 m_Fyl_u, m_Fyl_t;
   Float64 m_Fyr_u, m_Fyr_t;
   Float64 m_Mzl_u, m_Mzl_t;
   Float64 m_Mzr_u, m_Mzr_t;

   void ComputeReactions();
   void ComputeDeflections();

   void ComputeAxialReactions();
   void ComputeBendingReactions();

   void ComputeAxialDeflections();
   void ComputeBendingDeflections();

   void ComputeAxialForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputeBendingForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputeAxialDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);
   void ComputeBendingDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);

   void ComputePPReactions();
   void ComputePFReactions();
   void ComputeFPReactions();
   void ComputeFFReactions();

   void ComputePPDeflections();
   void ComputePFDeflections();
   void ComputeFPDeflections();
   void ComputeFFDeflections();

   void ComputePPForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputePFForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputeFPForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputeFFForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

	void ComputePPDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);
	void ComputePFDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);
	void ComputeFPDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);
	void ComputeFFDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);

   void ComputePPReactionsFy();
   void ComputePPReactionsMz();

   void ComputePFReactionsFy();
   void ComputePFReactionsMz();

   void ComputeFPReactionsFy();
   void ComputeFPReactionsMz();

   void ComputeFFReactionsFy();
   void ComputeFFReactionsMz();

   void ComputePPDeflectionsFy();
   void ComputePPDeflectionsMz();

   void ComputePFDeflectionsFy();
   void ComputePFDeflectionsMz();

   void ComputeFPDeflectionsFy();
   void ComputeFPDeflectionsMz();

   void ComputeFFDeflectionsFy();
   void ComputeFFDeflectionsMz();

   void ComputePPForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputePPForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputePFForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputePFForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputeFPForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputeFPForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputeFFForcesFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputeFFForcesMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputePPDeflectionFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputePPDeflectionMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputePFDeflectionFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputePFDeflectionMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputeFPDeflectionFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputeFPDeflectionMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   void ComputeFFDeflectionFy(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
   void ComputeFFDeflectionMz(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);

   Float64 ComputeFreeEndDeltaX(Float64 EA, Float64 W, Float64 wa, Float64 wb, Float64 a, Float64 b, Float64 x);
};


// Beam modeling uniform member distortions starting at point a, measured from the left
// end of the beam, and ending at the right end of the beam
class MemberStrainBeam : public Beam
{
// Public Implementation
public:
	MemberStrainBeam(Float64 qAxial, Float64 qCurvature,Float64 a,Float64 l,Float64 ea,Float64 ei,long leftBC,long rightBC);
   void GetLoad(Float64& qAxial, Float64& qCurvature,Float64& a);
	void GetReactions(Float64 &fxl,Float64 &fyl,Float64 &mzl,Float64 &fxr,Float64 &fyr,Float64 &mzr);
	void GetDeflections(Float64 &dxl,Float64 &dyl,Float64 &rzl,
                         Float64 &dxr,Float64 &dyr,Float64 &rzr);void GetForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
	void GetDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);

// Private Implementation
private:
   MemberStrainBeam();
   Float64 m_A; 
   Float64 m_Qx; // axial strain
   Float64 m_Qz; // curvature
   Float64 m_Fxl, m_Fxr;
   Float64 m_Fyl, m_Fyr;
   Float64 m_Mzl, m_Mzr;
   Float64 m_Dxl, m_Dxr;
   Float64 m_Dyl, m_Dyr;
   Float64 m_Rzl, m_Rzr;

   void ComputeReactions();
   void ComputeDeflections();

   void ComputePPReactions();
   void ComputePFReactions();
   void ComputeFPReactions();
   void ComputeFFReactions();

   void ComputePPDeflections();
   void ComputePFDeflections();
   void ComputeFPDeflections();
   void ComputeFFDeflections();
};

// Beam modeling uniform member distortions starting at point a and ending at point b, measured from the left
// end of the beam
class UniformMemberDistortionBeam : public Beam
{
// Public Implementation
public:
	UniformMemberDistortionBeam(Float64 qAxial, Float64 qCurvature,Float64 a,Float64 b,Float64 l,Float64 ea,Float64 ei,long leftBC,long rightBC);
   void GetLoad(Float64& qAxial, Float64& qCurvature,Float64& a,Float64& b);
	void GetReactions(Float64 &fxl,Float64 &fyl,Float64 &mzl,Float64 &fxr,Float64 &fyr,Float64 &mzr);
	void GetDeflections(Float64 &dxl,Float64 &dyl,Float64 &rzl,
                         Float64 &dxr,Float64 &dyr,Float64 &rzr);void GetForces(Float64 x,Float64 &fx,Float64 &fy,Float64 &mz);
	void GetDeflection(Float64 x,Float64 &dx,Float64 &dy,Float64 &rz);

// Private Implementation
private:
   UniformMemberDistortionBeam();
   MemberStrainBeam m_Case1Beam; // distortion from point a to the end of beam
   MemberStrainBeam m_Case2Beam; // distortion from point b to end of beam
   // what we want is case 1 - case 2, distortion from point a to b.
   //
   // (==== is the portion of the beam with the applied distortion)
   //
   //           |<---- a ------>|
   // Case 1    ----------------===============
   //
   //           |<---- b -------------->|
   // Case 2    ------------------------=======
   //
   // Case 1 - Case 2
   //           |<---- a ------>|
   //           |<---- b -------------->|
   //           ----------------=========------
};


#endif // FEM2D_BEAM_H_
