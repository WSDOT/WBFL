///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2024  Washington State Department of Transportation
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

#pragma once

#include <Lrfd\LrfdExp.h>
#include <Lrfd\PsStrand.h>
#include <Lrfd/BDSManagerListener.h>

namespace WBFL
{
   namespace LRFD
   {

      /// @brief Utility class for computing prestress losses using the LRFD Approximate Lump
      /// Sum Method introduced in the LRFD 3rd Edition with 2005 interims. This method
      /// is very similar to the pre-2005 losses, but is constrained to only non-composite
      /// sections.
      class LRFDCLASS NoncompositeApproximateLosses2005 : public BDSManagerListener
      {
      public:
         enum class BeamType { SolidSlab, BoxBeam, SingleT, DoubleT, TripleT, HollowCore, VoidedSlab};
         enum class Level { UpperBound, Average };

         NoncompositeApproximateLosses2005();

         NoncompositeApproximateLosses2005(WBFL::Materials::PsStrand::Grade gr,
                               WBFL::Materials::PsStrand::Type type,
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
                               Float64 K,      // Coefficient for elastic shortening for PT members (N-1)/(2N)
                               Float64 Eci,    // Modulus of elasticity of concrete at transfer
                               Float64 Fc,     // 28 day concrete strength
                               Float64 PPR,    // Partial Prestress Ratio
                               Float64 t );    // Time until prestress transfer

         NoncompositeApproximateLosses2005(const NoncompositeApproximateLosses2005& rOther) = default;

         ~NoncompositeApproximateLosses2005() = default;

         NoncompositeApproximateLosses2005& operator=(const NoncompositeApproximateLosses2005&) = default;

         void OnUpdate();

         Float64 ElasticShorteningLosses() const;
         Float64 RelaxationLossesAtXfer() const;
         Float64 ImmediatelyBeforeXferLosses() const;
         Float64 ImmediatelyAfterXferLosses() const;
         Float64 ApproxLosses() const;
         Float64 FinalLosses() const;
         Float64 GetFcgp() const;
         Float64 GetFpy() const;
         Float64 GetP() const;
         Float64 GetEp() const;

         void SetStrandType(WBFL::Materials::PsStrand::Type type);
         WBFL::Materials::PsStrand::Type GetStrandType() const;
         void SetStrandGrade(WBFL::Materials::PsStrand::Grade gr);
         WBFL::Materials::PsStrand::Grade GetStrandGrade() const;
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

      private:
         // GROUP: DATA MEMBERS
         BeamType m_BeamType;
         Level m_Level;
         WBFL::Materials::PsStrand::Type m_Type;
         WBFL::Materials::PsStrand::Grade m_Grade;
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

         void Init();

         void UpdateLosses() const;
         void UpdateInitialLosses() const;
         void UpdateLongTermLosses() const;
      };

      inline void NoncompositeApproximateLosses2005::SetStrandType(WBFL::Materials::PsStrand::Type type) { m_Type = type; m_IsDirty = true; }
      inline WBFL::Materials::PsStrand::Type NoncompositeApproximateLosses2005::GetStrandType() const { return m_Type; }
      inline void NoncompositeApproximateLosses2005::SetStrandGrade(WBFL::Materials::PsStrand::Grade gr) { m_Grade = gr; m_IsDirty = true; }
      inline WBFL::Materials::PsStrand::Grade NoncompositeApproximateLosses2005::GetStrandGrade() const { return m_Grade; }
      inline void NoncompositeApproximateLosses2005::SetFpj(Float64 fpj) { m_Fpj = fpj; m_IsDirty = true; }
      inline Float64 NoncompositeApproximateLosses2005::GetFpj() const { return m_Fpj; }
      inline void NoncompositeApproximateLosses2005::SetAg(Float64 Ag) { m_Ag = Ag; m_IsDirty = true; }
      inline Float64 NoncompositeApproximateLosses2005::GetAg() const { return m_Ag; }
      inline void NoncompositeApproximateLosses2005::SetIg(Float64 Ig) { m_Ig = Ig; m_IsDirty = true; }
      inline Float64 NoncompositeApproximateLosses2005::GetIg() const { return m_Ig; }
      inline void NoncompositeApproximateLosses2005::SetYbg(Float64 Ybg) { m_Ybg = Ybg; m_IsDirty = true; }
      inline Float64 NoncompositeApproximateLosses2005::GetYbg() const { return m_Ybg; }
      inline void NoncompositeApproximateLosses2005::SetEcc(Float64 e) { m_e = e; m_IsDirty = true; }
      inline Float64 NoncompositeApproximateLosses2005::GetEcc() const { return m_e; }
      inline void NoncompositeApproximateLosses2005::SetEccPermanent(Float64 e) { m_eperm = e; m_IsDirty = true; }
      inline Float64 NoncompositeApproximateLosses2005::GetEccPermanent() const { return m_eperm; }
      inline void NoncompositeApproximateLosses2005::SetAreaPs(Float64 Aps) { m_Aps = Aps; m_IsDirty = true; }
      inline Float64 NoncompositeApproximateLosses2005::GetAreaPs() const { return m_Aps; }
      inline void NoncompositeApproximateLosses2005::SetGdrMoment(Float64 Mdlg) { m_Mdlg = Mdlg; m_IsDirty = true; }
      inline Float64 NoncompositeApproximateLosses2005::GetGdrMoment() const { return m_Mdlg; }
      inline void NoncompositeApproximateLosses2005::SetEci(Float64 Eci) { m_Eci = Eci; m_IsDirty = true; }
      inline Float64 NoncompositeApproximateLosses2005::GetEci() const { return m_Eci; }
      inline void NoncompositeApproximateLosses2005::SetFc(Float64 fc) { m_Fc = fc; m_IsDirty = true; }
      inline Float64 NoncompositeApproximateLosses2005::GetFc() const { return m_Fc; }
      inline void NoncompositeApproximateLosses2005::SetPPR(Float64 ppr) { m_PPR = ppr; m_IsDirty = true; }
      inline Float64 NoncompositeApproximateLosses2005::GetPPR() const { return m_PPR; }
      inline void NoncompositeApproximateLosses2005::SetTimeToXfer(Float64 t) { m_Time = t; m_IsDirty = true; }
      inline Float64 NoncompositeApproximateLosses2005::GetTimeToXfer() const { return m_Time; }
      inline void NoncompositeApproximateLosses2005::SetBeamType(NoncompositeApproximateLosses2005::BeamType beamType) { m_BeamType = beamType; m_IsDirty = true; }
      inline NoncompositeApproximateLosses2005::BeamType NoncompositeApproximateLosses2005::GetBeamType() const { return m_BeamType; }
      inline void NoncompositeApproximateLosses2005::SetLevel(NoncompositeApproximateLosses2005::Level level) { m_Level = level; m_IsDirty = true; }
      inline NoncompositeApproximateLosses2005::Level NoncompositeApproximateLosses2005::GetLevel() const { return m_Level; }
      inline void NoncompositeApproximateLosses2005::SetK(Float64 K) { m_K = K; m_IsDirty = true; }
      inline Float64 NoncompositeApproximateLosses2005::GetK() const { return m_K; }
   };
};
