///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <Lrfd\VersionMgrListener.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Utility class for computing losses using the LRFD Refined Estimate Method for post-tension members.
      class LRFDCLASS PTRefinedLosses : public LRFDVersionMgrListener
      {
      public:
         PTRefinedLosses();

         PTRefinedLosses(WBFL::Materials::PsStrand::Grade gr,
                      WBFL::Materials::PsStrand::Type type,
				          Float64 fpj,    // Actual jacking stress
                      Float64 Ag,     // area of girder
                      Float64 Ig,     // moment of inertia of girder
                      Float64 Ybg,    // centroid of girder measured from bottom
                      Float64 Ic,     // moment of inertia of composite
                      Float64 Ybc,    // centroid of composite measured from bottom
                      Float64 e,      // eccentricity of ps strands
                      Float64 Aps,    // area of ps strands
                      Float64 Mdlg,   // Dead load moment of girder only
                      Float64 Madlg,  // Additional dead load on girder
                      Float64 Msidl,  // Superimposed dead loads
                      Float64 rh,     // Relative humidity [0,100]
                      Float64 Eci,    // Modulus of elasticity of concrete at transfer
                      Float64 dfFR,   // Friction losses
                      Float64 Fcgp,
                      Float64 dfES);

         PTRefinedLosses(const PTRefinedLosses&) = default;
         ~PTRefinedLosses() = default;

         PTRefinedLosses& operator=(const PTRefinedLosses&) = default;

         void OnUpdate();

         //------------------------------------------------------------------------
         Float64 ShrinkageLosses() const;

         //------------------------------------------------------------------------
         Float64 CreepLosses() const;

         //------------------------------------------------------------------------
         Float64 RelaxationLossesAfterXfer() const;

         //------------------------------------------------------------------------
         Float64 FinalLosses() const;

         //------------------------------------------------------------------------
         Float64 GetDeltaFcdp() const;

         //------------------------------------------------------------------------
         Float64 GetFpy() const;

         //------------------------------------------------------------------------
         Float64 GetEp() const;

         // GROUP: ACCESS
         //------------------------------------------------------------------------
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
         void SetIc(Float64 Ic);
         Float64 GetIc() const;
         void SetYbc(Float64 Ybc);
         Float64 GetYbc() const;
         void SetEcc(Float64 e);
         Float64 GetEcc() const;
         void SetAreaPT(Float64 Aps);
         Float64 GetAreaPT() const;
         void SetGdrMoment(Float64 Mdlg);
         Float64 GetGdrMoment() const;
         void SetAddlGdrMoment(Float64 Madlg);
         Float64 GetAddlGdrMoment() const;
         void SetSidlMoment(Float64 Msidl);
         Float64 GetSidlMoment() const;
         void SetRelativeHumidity(Float64 rh);
         Float64 GetRelativeHumidity() const;
         void SetEci(Float64 Eci);
         Float64 GetEci() const;
         void SetN(Float64 n);
         Float64 GetN() const;
         void SetFR(Float64 fr);
         Float64 GetFR() const;
         void SetFcgp(Float64 f);
         Float64 GetFcgp() const;
         void SetES(Float64 es);
         Float64 GetES() const;

      private:
         WBFL::Materials::PsStrand::Type m_Type;
         WBFL::Materials::PsStrand::Grade m_Grade;
         Float64 m_Ag;    // Area of the girder
         Float64 m_Ig;    // Moment of inertia of the girder
         Float64 m_Ybg;   // Centroid of girder measured from bottom
         Float64 m_Ic;    // Moment of inertia of composite
         Float64 m_Ybc;   // Centroid of composite measured from bottom
         Float64 m_e;     // Eccentricity of prestress force
         Float64 m_Aps;   // Area of ps strands
         Float64 m_Mdlg;  // Dead load moment of girder
         Float64 m_Madlg; // Additional dead load moment on girder section
         Float64 m_Msidl; // Superimposed dead loads
         Float64 m_Rh;
         Float64 m_Eci;

         Float64 m_dfFR; // friction losses
         Float64 m_Fcgp;
         Float64 m_dfES;

         Float64 m_Ep;
         Float64 m_Fpu;
         Float64 m_Fpj;
         Float64 m_Fpy;


         mutable Float64 m_DeltaFcdp;

         mutable Float64 m_dfSR;
         mutable Float64 m_dfCR;
         mutable Float64 m_dfR2;

         mutable bool    m_IsDirty;

         void Init();
         void UpdateLosses() const;
         void UpdateLongTermLosses() const;
      };

      inline void PTRefinedLosses::SetStrandType(WBFL::Materials::PsStrand::Type type) { m_Type = type; m_IsDirty = true; }
      inline WBFL::Materials::PsStrand::Type PTRefinedLosses::GetStrandType() const { return m_Type; }
      inline void PTRefinedLosses::SetStrandGrade(WBFL::Materials::PsStrand::Grade gr) { m_Grade = gr; m_IsDirty = true; }
      inline WBFL::Materials::PsStrand::Grade PTRefinedLosses::GetStrandGrade() const { return m_Grade; }
      inline void PTRefinedLosses::SetFpj(Float64 fpj) { m_Fpj = fpj; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetFpj() const { return m_Fpj; }
      inline void PTRefinedLosses::SetAg(Float64 Ag) { m_Ag = Ag; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetAg() const { return m_Ag; }
      inline void PTRefinedLosses::SetIg(Float64 Ig) { m_Ig = Ig; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetIg() const { return m_Ig; }
      inline void PTRefinedLosses::SetYbg(Float64 Ybg) { m_Ybg = Ybg; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetYbg() const { return m_Ybg; }
      inline void PTRefinedLosses::SetIc(Float64 Ic) { m_Ic = Ic; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetIc() const { return m_Ic; }
      inline void PTRefinedLosses::SetYbc(Float64 Ybc) { m_Ybc = Ybc; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetYbc() const { return m_Ybc; }
      inline void PTRefinedLosses::SetEcc(Float64 e) { m_e = e; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetEcc() const { return m_e; }
      inline void PTRefinedLosses::SetAreaPT(Float64 Aps) { m_Aps = Aps; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetAreaPT() const { return m_Aps; }
      inline void PTRefinedLosses::SetGdrMoment(Float64 Mdlg) { m_Mdlg = Mdlg; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetGdrMoment() const { return m_Mdlg; }
      inline void PTRefinedLosses::SetAddlGdrMoment(Float64 Madlg) { m_Madlg = Madlg; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetAddlGdrMoment() const { return m_Madlg; }
      inline void PTRefinedLosses::SetSidlMoment(Float64 Msidl) { m_Msidl = Msidl; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetSidlMoment() const { return m_Msidl; }
      inline void PTRefinedLosses::SetRelativeHumidity(Float64 rh) { m_Rh = rh; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetRelativeHumidity() const { return m_Rh; }
      inline void PTRefinedLosses::SetEci(Float64 Eci) { m_Eci = Eci; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetEci() const { return m_Eci; }
      inline void PTRefinedLosses::SetFR(Float64 fr) { m_dfFR = fr; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetFR() const { return m_dfFR; }
      inline void PTRefinedLosses::SetFcgp(Float64 f) { m_Fcgp = f; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetFcgp() const { return m_Fcgp; }
      inline void PTRefinedLosses::SetES(Float64 es) { m_dfES = es; m_IsDirty = true; }
      inline Float64 PTRefinedLosses::GetES() const { return m_dfES; }
   };
};
