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
#include <GeomModel/Primitives.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Utility class for elastic shortening losses.  Implements Article 5.9.5.2.3a
      /// of the LRFD Bridge Design Specification.
      class LRFDCLASS ElasticShortening
      {
      public:

         /// @brief Indicates the method to compute Fcgp.
         enum class FcgpComputationMethod 
         {
            Iterative, ///< Use iterative (beam theory) method
            AssumedFpe ///< Assume that stress in strands after transfer is 0.7*Fpu (TxDOT 2013 research)
         };

         ElasticShortening();

         ElasticShortening(Float64 fpjPerm,   ///< jacking stress
                           Float64 fpjTemp,   ///< jacking stress
                           Float64 dfpR1Perm, ///< initial relaxation
                           Float64 dfpR1Temp, ///< initial relaxation
                           Float64 ApsPerm,   ///< Area of permanent prestressing steel 
                           Float64 ApsTemp,   ///< Area of temporary prestressing steel
                           bool    bGrossProperties, ///< true if using gross section properties
                           Float64 Ag,    ///< area of girder
                           Float64 Ixx,    ///< moment of inertia of girder
                           Float64 Iyy, ///< weak axis moment of inertia
                           Float64 Ixy, ///< product of inertia
                           const WBFL::Geometry::Point2d& ePerm, ///< eccentricity of permanent ps strands
                           const WBFL::Geometry::Point2d& eTemp, ///< eccentricity of temporary ps strands
                           Float64 Mdlg,  ///< Dead load moment of girder only
                           Float64 K,     ///< coefficient for post-tension members (N-1)/(2N)
                           Float64 Eci,   ///< Modulus of elasticity of concrete at transfer
                           Float64 Ep,    ///< Modulus of elasticity of prestressing steel
                           FcgpComputationMethod method ///< method for computing fcgp
         );

         ElasticShortening(const ElasticShortening& rOther) = default;

         ~ElasticShortening() = default;

         ElasticShortening& operator=(const ElasticShortening& rOther) = default;

         Float64 TemporaryStrand_ElasticShorteningLosses() const;
         Float64 PermanentStrand_ElasticShorteningLosses() const;

         Float64 P() const;

         Float64 TemporaryStrand_Fcgp() const;
         Float64 PermanentStrand_Fcgp() const;

         void    TemporaryStrand_Fpj(Float64 fpj);
         Float64 TemporaryStrand_Fpj() const;
         void    PermanentStrand_Fpj(Float64 fpj);
         Float64 PermanentStrand_Fpj() const;

         void    TemporaryStrand_InitialRelaxationLoss(Float64 dfpR1);
         Float64 TemporaryStrand_InitialRelaxationLoss() const;
         void    PermanentStrand_InitialRelaxationLoss(Float64 dfpR1);
         Float64 PermanentStrand_InitialRelaxationLoss() const;

         void    TemporaryStrand_Aps(Float64 Aps);
         Float64 TemporaryStrand_Aps() const;
         void    PermanentStrand_Aps(Float64 Aps);
         Float64 PermanentStrand_Aps() const;

         void    TemporaryStrand_eccentricity(const WBFL::Geometry::Point2d& e);
         const WBFL::Geometry::Point2d& TemporaryStrand_eccentricity() const;
         void    PermanentStrand_eccentricity(const WBFL::Geometry::Point2d& e);
         const WBFL::Geometry::Point2d& PermanentStrand_eccentricity() const;

         void GrossProperties(bool bGrossProperties);
         bool GrossProperties() const;

         void SetProperties(Float64 A, Float64 Ixx, Float64 Iyy, Float64 Ixy);
         void GetProperties(Float64* pA, Float64* pIxx, Float64* pIyy, Float64* pIxy) const;

         void    GdrMoment(Float64 Mdlg);
         Float64 GdrMoment() const;

         void    Eci(Float64 Eci);
         Float64 Eci() const;

         void    Ep(Float64 Ep);
         Float64 Ep() const;

         void    Coefficient(Float64 K);
         Float64 Coefficient() const;

         void    SetFcgpComputationMethod(FcgpComputationMethod m);
         FcgpComputationMethod GetFcgpComputationMethod() const;

      private:
         mutable bool m_bUpdate;
         void Update() const;

         Float64 m_ApsPerm;
         Float64 m_ApsTemp;
         WBFL::Geometry::Point2d m_ePerm;
         WBFL::Geometry::Point2d m_eTemp;

         Float64 m_FpjPerm;   // Jacking stress
         Float64 m_FpjTemp;   // Jacking stress

         Float64 m_dFpR1Perm; // Initial relaxation losses
         Float64 m_dFpR1Temp; // Initial relaxation losses

         bool m_bGrossProperties;
         Float64 m_Ag;    // Area of the girder
         Float64 m_Ixx;    // Moment of inertia of the girder
         Float64 m_Iyy;
         Float64 m_Ixy;
         Float64 m_Mdlg;  // Dead load moment of girder
         Float64 m_Eci;
         Float64 m_Ep;
         Float64 m_K; // Coefficient used for Post-tensioned members (N-1)/(2N)
         FcgpComputationMethod m_FcgpMethod;

         mutable Float64 m_P;     // prestress force
         mutable Float64 m_dfESPerm; // Elastic shortening losses
         mutable Float64 m_dfESTemp; // Elastic shortening losses
         mutable Float64 m_FcgpPerm; // Stress at cg;
         mutable Float64 m_FcgpTemp; // Stress at cg;
      };

      // INLINE METHODS
      //
      inline void    ElasticShortening::TemporaryStrand_Fpj(Float64 Fpj) { m_FpjTemp = Fpj; m_bUpdate = true; }
      inline Float64 ElasticShortening::TemporaryStrand_Fpj() const      { return m_FpjTemp; }
      inline void    ElasticShortening::PermanentStrand_Fpj(Float64 Fpj) { m_FpjPerm = Fpj; m_bUpdate = true; }
      inline Float64 ElasticShortening::PermanentStrand_Fpj() const      { return m_FpjPerm; }

      inline void    ElasticShortening::TemporaryStrand_InitialRelaxationLoss(Float64 dFpR1) { m_dFpR1Temp = dFpR1; m_bUpdate = true; }
      inline Float64 ElasticShortening::TemporaryStrand_InitialRelaxationLoss() const        { return m_dFpR1Temp; }
      inline void    ElasticShortening::PermanentStrand_InitialRelaxationLoss(Float64 dFpR1) { m_dFpR1Perm = dFpR1; m_bUpdate = true; }
      inline Float64 ElasticShortening::PermanentStrand_InitialRelaxationLoss() const        { return m_dFpR1Perm; }

      inline void    ElasticShortening::TemporaryStrand_Aps(Float64 Aps) { m_ApsTemp = Aps; m_bUpdate = true; }
      inline Float64 ElasticShortening::TemporaryStrand_Aps() const      { return m_ApsTemp; }
      inline void    ElasticShortening::PermanentStrand_Aps(Float64 Aps) { m_ApsPerm = Aps; m_bUpdate = true; }
      inline Float64 ElasticShortening::PermanentStrand_Aps() const      { return m_ApsPerm; }

      inline void ElasticShortening::GrossProperties(bool bGrossProperties) { m_bGrossProperties = bGrossProperties; m_bUpdate = true; }
      inline bool ElasticShortening::GrossProperties() const { return m_bGrossProperties; }

      inline void    ElasticShortening::TemporaryStrand_eccentricity(const WBFL::Geometry::Point2d& e) { m_eTemp = e; m_bUpdate = true; }
      inline const WBFL::Geometry::Point2d& ElasticShortening::TemporaryStrand_eccentricity() const    { return m_eTemp; }
      inline void    ElasticShortening::PermanentStrand_eccentricity(const WBFL::Geometry::Point2d& e) { m_ePerm = e; m_bUpdate = true; }
      inline const WBFL::Geometry::Point2d& ElasticShortening::PermanentStrand_eccentricity() const    { return m_ePerm; }

      inline void    ElasticShortening::GdrMoment(Float64 Mdlg) { m_Mdlg = Mdlg; m_bUpdate = true; }
      inline Float64 ElasticShortening::GdrMoment() const       { return m_Mdlg; }

      inline void    ElasticShortening::Eci(Float64 Eci) { m_Eci = Eci; m_bUpdate = true; }
      inline Float64 ElasticShortening::Eci() const      { return m_Eci; }

      inline void    ElasticShortening::Ep(Float64 Ep) { m_Ep = Ep; m_bUpdate = true; }
      inline Float64 ElasticShortening::Ep() const     { return m_Ep; }

      inline void    ElasticShortening::Coefficient(Float64 K) { m_K = K; m_bUpdate = true; }
      inline Float64 ElasticShortening::Coefficient() const    { return m_K; }

      inline void    ElasticShortening::SetFcgpComputationMethod(FcgpComputationMethod m) { m_FcgpMethod = m; m_bUpdate = true; }
      inline ElasticShortening::FcgpComputationMethod ElasticShortening::GetFcgpComputationMethod() const    { return m_FcgpMethod; }
   };
};
