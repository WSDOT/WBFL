///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#ifndef INCLUDED_LRFD_NONCOMPOSITEAPPROXIMATELOSSES2005_H_
#define INCLUDED_LRFD_NONCOMPOSITEAPPROXIMATELOSSES2005_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <Lrfd\PsStrand.h>
#include <Lrfd\VersionMgrListener.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdNoncompositeApproximateLosses2005

   Utility class for computing prestress losses using the LRFD Approximate Lump
   Sum Method.


DESCRIPTION
   Utility class for computing prestress losses using the LRFD Approximate Lump
   Sum Method. Implements the provisions of Article 5.9.5.2.3 and 5.9.5.3.

COPYRIGHT
   Copyright (c) 1999
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 03.31.1999 : Created file
*****************************************************************************/

class LRFDCLASS lrfdNoncompositeApproximateLosses2005 : public lrfdVersionMgrListener
{
public:
   enum BeamType { SolidSlab, BoxBeam, SingleT, Float64T, TripleT, HollowCore, VoidedSlab};
   enum Level { UpperBound, Average };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.
   // Strand type = LowRelaxation
   // Ep = 197000 MPa
   // Eci = 25000 MPa
   // fpu = 1860 MPa
   // fpj = 0.80*fpu
   // fpy = 0.90*fpu
   // A = 1mm^2
   // I = 1mm^4
   // e = 0 mm
   // Mg = 0 N-m
   // BeamType = SingleT
   // Level = Average
   lrfdNoncompositeApproximateLosses2005();

   //------------------------------------------------------------------------
   // Constructor.  Initializes the object with the give values.
   // fpy is initialized to 0.85fpu for StressRelieved strands and
   // 0.90fpu for LowRelaxation strands.
   lrfdNoncompositeApproximateLosses2005(matPsStrand::Grade gr,
                         matPsStrand::Type type,
                         BeamType beamType,
                         Level level,
			                Float64 fpj,    // Actual jacking stress
                         Float64 Ag,     // area of girder
                         Float64 Ig,     // moment of inertia of girder
                         Float64 Ybg,    // centroid of girder measured from bottom
                         Float64 e,      // eccentricity of ps strands
                         Float64 eperm,
                         Float64 Aps, // area of ps strands
                         Float64 Mdlg,   // Dead load moment of girder only
                         Float64 K,      // Coefficent for elastic shortening for PT members (N-1)/(2N)
                         Float64 Eci,    // Modulus of elasticity of concrete at transfer
                         Float64 Fc,     // 28 day concrete strength
                         Float64 PPR,    // Partial Prestress Ratio
                         Float64 t );    // Time until prestress transfer

   //------------------------------------------------------------------------
   // Copy c'tor
   lrfdNoncompositeApproximateLosses2005(const lrfdNoncompositeApproximateLosses2005& rOther);

   //------------------------------------------------------------------------
   // Destructor
   ~lrfdNoncompositeApproximateLosses2005();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   lrfdNoncompositeApproximateLosses2005& operator=(const lrfdNoncompositeApproximateLosses2005& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Called by lrfdVersion when ever the code version or unit system changes
   void OnUpdate();

   //------------------------------------------------------------------------
   Float64 ElasticShorteningLosses() const;
 
   //------------------------------------------------------------------------
   Float64 RelaxationLossesAtXfer() const;

   //------------------------------------------------------------------------
   Float64 ImmediatelyBeforeXferLosses() const;

   //------------------------------------------------------------------------
   Float64 ImmediatelyAfterXferLosses() const;

   //------------------------------------------------------------------------
   Float64 ApproxLosses() const;

   //------------------------------------------------------------------------
   Float64 FinalLosses() const;

   //------------------------------------------------------------------------
   Float64 GetFcgp() const;

   //------------------------------------------------------------------------
   Float64 GetFpy() const;

   //------------------------------------------------------------------------
   Float64 GetP() const;

   //------------------------------------------------------------------------
   Float64 GetEp() const;

   // GROUP: ACCESS
   //------------------------------------------------------------------------
   void SetStrandType(matPsStrand::Type type);
   matPsStrand::Type GetStrandType() const;
   void SetStrandGrade(matPsStrand::Grade gr);
   matPsStrand::Grade GetStrandGrade() const;
   void SetFpj(Float64 fpj);
   Float64 GetFpj() const;
   void SetAg(Float64 Ag);
   Float64 GetAg() const;
   void SetIg(Float64 Ig);
   Float64 GetIg() const;
   void SetYbg(Float64 Ybg);
   Float64 GetYbg() const;
   void SetEcc(Float64 e);
   Float64 GetEcc() const;
   void SetEccPermanent(Float64 e);
   Float64 GetEccPermanent() const;
   void SetAreaPs(Float64 Aps);
   Float64 GetAreaPs() const;
   void SetGdrMoment(Float64 Mdlg);
   Float64 GetGdrMoment() const;
   void SetEci(Float64 Eci);
   Float64 GetEci() const;
   void SetFc(Float64 fc);
   Float64 GetFc() const;
   void SetPPR(Float64 ppr);
   Float64 GetPPR() const;
   void SetTimeToXfer(Float64 t);
   Float64 GetTimeToXfer() const;
   void SetBeamType(BeamType beamType);
   BeamType GetBeamType() const;
   void SetLevel(Level level);
   Level GetLevel() const;
   void SetK(Float64 K);
   Float64 GetK() const;

   // GROUP: INQUIRY
   // GROUP: DEBUG
   #if defined _UNITTEST
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeAssignment( const lrfdNoncompositeApproximateLosses2005& rOther );

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   BeamType m_BeamType;
   Level m_Level;
   matPsStrand::Type m_Type;
   matPsStrand::Grade m_Grade;
   Float64 m_Aps;   // Area of prestressing steel
   Float64 m_Ag;    // Area of the girder
   Float64 m_Ig;    // Moment of inertia of the girder
   Float64 m_Ybg;   // Centroid of girder measured from bottom
   Float64 m_e;     // Eccenricity of prestress force
   Float64 m_eperm; // Eccentricity of permanent ps force
   Float64 m_Mdlg;  // Dead load moment of girder
   Float64 m_K;
   Float64 m_Eci;
   Float64 m_Fc;
   Float64 m_PPR;
   Float64 m_Time;

   Float64 m_Ep;
   Float64 m_Fpu;
   Float64 m_Fpj;
   Float64 m_Fpy;

   mutable Float64 m_Fcgp;

   mutable Float64 m_P; // prestress force

   mutable Float64 m_dfES;
   mutable Float64 m_dfR1;
   mutable Float64 m_dfApprox;

   mutable bool    m_IsDirty;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void Init();

   //------------------------------------------------------------------------
   void MakeCopy( const lrfdNoncompositeApproximateLosses2005& rOther );

   //------------------------------------------------------------------------
   void UpdateLosses() const;

   //------------------------------------------------------------------------
   void UpdateInitialLosses() const;
   
   //------------------------------------------------------------------------
   void UpdateLongTermLosses() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//
inline void lrfdNoncompositeApproximateLosses2005::SetStrandType(matPsStrand::Type type) { m_Type = type; m_IsDirty = true; }
inline matPsStrand::Type lrfdNoncompositeApproximateLosses2005::GetStrandType() const { return m_Type; }
inline void lrfdNoncompositeApproximateLosses2005::SetStrandGrade(matPsStrand::Grade gr) { m_Grade = gr; m_IsDirty = true; }
inline matPsStrand::Grade lrfdNoncompositeApproximateLosses2005::GetStrandGrade() const { return m_Grade; }
inline void lrfdNoncompositeApproximateLosses2005::SetFpj(Float64 fpj) { m_Fpj = fpj; m_IsDirty = true; }
inline Float64 lrfdNoncompositeApproximateLosses2005::GetFpj() const { return m_Fpj; }
inline void lrfdNoncompositeApproximateLosses2005::SetAg(Float64 Ag) { m_Ag = Ag; m_IsDirty = true; }
inline Float64 lrfdNoncompositeApproximateLosses2005::GetAg() const { return m_Ag; }
inline void lrfdNoncompositeApproximateLosses2005::SetIg(Float64 Ig) { m_Ig = Ig; m_IsDirty = true; }
inline Float64 lrfdNoncompositeApproximateLosses2005::GetIg() const { return m_Ig; }
inline void lrfdNoncompositeApproximateLosses2005::SetYbg(Float64 Ybg) { m_Ybg = Ybg; m_IsDirty = true; }
inline Float64 lrfdNoncompositeApproximateLosses2005::GetYbg() const { return m_Ybg; }
inline void lrfdNoncompositeApproximateLosses2005::SetEcc(Float64 e) { m_e = e; m_IsDirty = true; }
inline Float64 lrfdNoncompositeApproximateLosses2005::GetEcc() const { return m_e; }
inline void lrfdNoncompositeApproximateLosses2005::SetEccPermanent(Float64 e) { m_eperm = e; m_IsDirty = true; }
inline Float64 lrfdNoncompositeApproximateLosses2005::GetEccPermanent() const { return m_eperm; }
inline void lrfdNoncompositeApproximateLosses2005::SetAreaPs(Float64 Aps) { m_Aps = Aps; m_IsDirty = true; }
inline Float64 lrfdNoncompositeApproximateLosses2005::GetAreaPs() const { return m_Aps; }
inline void lrfdNoncompositeApproximateLosses2005::SetGdrMoment(Float64 Mdlg) { m_Mdlg = Mdlg; m_IsDirty = true; }
inline Float64 lrfdNoncompositeApproximateLosses2005::GetGdrMoment() const { return m_Mdlg; }
inline void lrfdNoncompositeApproximateLosses2005::SetEci(Float64 Eci) { m_Eci = Eci; m_IsDirty = true; }
inline Float64 lrfdNoncompositeApproximateLosses2005::GetEci() const { return m_Eci; }
inline void lrfdNoncompositeApproximateLosses2005::SetFc(Float64 fc) { m_Fc = fc; m_IsDirty = true; }
inline Float64 lrfdNoncompositeApproximateLosses2005::GetFc() const { return m_Fc; }
inline void lrfdNoncompositeApproximateLosses2005::SetPPR(Float64 ppr) { m_PPR = ppr; m_IsDirty = true; }
inline Float64 lrfdNoncompositeApproximateLosses2005::GetPPR() const { return m_PPR; }
inline void lrfdNoncompositeApproximateLosses2005::SetTimeToXfer(Float64 t) { m_Time = t; m_IsDirty = true; }
inline Float64 lrfdNoncompositeApproximateLosses2005::GetTimeToXfer() const { return m_Time; }
inline void lrfdNoncompositeApproximateLosses2005::SetBeamType(lrfdNoncompositeApproximateLosses2005::BeamType beamType) { m_BeamType = beamType; m_IsDirty = true; }
inline lrfdNoncompositeApproximateLosses2005::BeamType lrfdNoncompositeApproximateLosses2005::GetBeamType() const { return m_BeamType; }
inline void lrfdNoncompositeApproximateLosses2005::SetLevel(lrfdNoncompositeApproximateLosses2005::Level level) { m_Level = level; m_IsDirty = true; }
inline lrfdNoncompositeApproximateLosses2005::Level lrfdNoncompositeApproximateLosses2005::GetLevel() const { return m_Level; }
inline void lrfdNoncompositeApproximateLosses2005::SetK(Float64 K) { m_K = K; m_IsDirty = true; }
inline Float64 lrfdNoncompositeApproximateLosses2005::GetK() const { return m_K; }

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_NONCOMPOSITEAPPROXIMATELOSSES2005_H_
