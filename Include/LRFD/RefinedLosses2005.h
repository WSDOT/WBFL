///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2022  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_REFINEDLOSSES2005_H_
#define INCLUDED_LRFD_REFINEDLOSSES2005_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <Lrfd\Losses.h>
#include <Lrfd\CreepCoefficient2005.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdRefinedLosses2005

   Utility class for computing prestress losses using the LRFD Refined Estimate
   Method.


DESCRIPTION
   Utility class for computing prestress losses using the LRFD Refined Estimate
   Method. Encapsulates Articles 5.9.5.2.3 and 5.9.5.4.

LOG
   rab : 12.01.1997 : Created file
*****************************************************************************/

class LRFDCLASS lrfdRefinedLosses2005 : public lrfdLosses
{
public:
   enum RelaxationLossMethod { 
      Simplified, // use LRFD Eqn 5.9.5.4.2c-1
      Refined,    // use LRFD Eqn C5.9.5.4.2c-1
      LumpSum     // use lump sum value of 1.2 KSI (only for low-relaxation strands)
      };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.
   // Strand type = LowRelaxation
   // Relative Humidity = 70%
   // Ep = 197000 MPa
   // Eci = 25000 MPa
   // fpu = 1860 MPa
   // fpj = 0.80*fpu
   // fpy = 0.90*fpu
   // Time to prestress transfer = 1 day
   // Aps = 1mm^2
   // A = 1mm^2
   // I = 1mm^4
   // e = 0 mm
   // Mg = 0 N-m
   // Mdl = 0 N-m
   lrfdRefinedLosses2005();

   //------------------------------------------------------------------------
   // Constructor.  Initializes the object with the give values.
   // fpy is initialized to 0.85fpu for StressRelieved strands and
   // 0.90fpu for LowRelaxation strands.
   lrfdRefinedLosses2005(Float64 x, // location along girder where losses are computed
                         Float64 Lg,    // girder length
                         lrfdLosses::SectionPropertiesType sectionProperties,
                         matPsStrand::Grade gradePerm, // strand grade
                         matPsStrand::Type typePerm, // strand type
                         matPsStrand::Coating coatingPerm, // strand coating (none, epoxy)
                         matPsStrand::Grade gradeTemp, // strand grade
                         matPsStrand::Type typeTemp, // strand type
                         matPsStrand::Coating coatingTemp, // strand coating (none, epoxy)
                         Float64 fpjPerm, // fpj permanent strands
                         Float64 fpjTemp, // fpj of temporary strands
                         Float64 ApsPerm,  // area of permanent strand
                         Float64 ApsTemp,  // area of TTS 
                         Float64 aps,      // area of one strand
                         const WBFL::Geometry::Point2d& epermRelease, // eccentricty of permanent ps strands with respect to CG of girder at release
                         const WBFL::Geometry::Point2d& epermFinal, // eccentricty of permanent ps strands with respect to CG of girder at final
                         const WBFL::Geometry::Point2d& etemp, // eccentricty of temporary strands with respect to CG of girder
                         TempStrandUsage usage,
                         Float64 anchorSet,
                         Float64 wobble,
                         Float64 friction,
                         Float64 angleChange,

                         //Float64 CreepK1,
                         //Float64 CreepK2,
                         Float64 ShrinkageK1,
                         Float64 ShrinkageK2,
                         
                         //Float64 DeckCreepK1,
                         //Float64 DeckCreepK2,
                         Float64 DeckShrinkageK1,
                         Float64 DeckShrinkageK2,

                         Float64 Fc,   // 28 day strength of girder concrete
                         Float64 Fci,  // Release strength
                         Float64 FcSlab,   
                         Float64 Ec,   // Modulus of elasticity of girder
                         Float64 Eci,  // Modulus of elasticity of girder at transfer
                         Float64 Ecd,  // Modulus of elasticity of deck
                         
                         //Float64 V,    // Volumne of girder
                         //Float64 S,    // Surface area of girder
                         //Float64 VSlab,    // Volumne of slab
                         //Float64 SSlab,    // Surface area of slab

                         Float64 Ag,   // area of girder
                         Float64 Ixx,   // moment of inertia of girder
                         Float64 Iyy,
                         Float64 Ixy,
                         Float64 Ybg,  // Centroid of girder measured from bottom
                         Float64 Ac1,   // area of composite girder, stage 1
                         Float64 Ic1,   // moment of inertia of composite, stage 1
                         Float64 Ybc1,  // Centroid of composite measured from bottom, stage 1
                         Float64 Ac2,   // area of composite girder, stage 2
                         Float64 Ic2,   // moment of inertia of composite, stage 2
                         Float64 Ybc2,  // Centroid of composite measured from bottom, stage 2

                         Float64 An,   // area of girder
                         Float64 Ixxn,   // moment of inertia of girder
                         Float64 Iyyn,
                         Float64 Ixyn,
                         Float64 Ybn,  // Centroid of girder measured from bottom
                         Float64 Acn,   // area of composite girder
                         Float64 Icn,   // moment of inertia of composite
                         Float64 Ybcn,  // Centroid of composite measured from bottom

                         Float64 Ad,   // area of deck
                         Float64 ed,   // eccentricity of deck CG with respect to CG of composite
                         Float64 Ksh,  // deck shrinkage strain effectiveness
                         
                         Float64 Mdlg,  // Dead load moment of girder only
                         const std::vector<std::pair<Float64, Float64>>& Madlg,  // Additional dead load on girder section (first value is moment, second is elastic gain reduction factor)
                         const std::vector<std::pair<Float64, Float64>>& Msidl1, // Superimposed dead loads, stage 1
                         const std::vector<std::pair<Float64, Float64>>& Msidl2, // Superimposed dead loads, stage 2

                         Float64 rh,  // Relative humidity [0,100]
                         Float64 ti,   // Time until prestress transfer
                         Float64 th,   // Time at hauling
                         Float64 td,   // Time to deck placement
                         Float64 tf,   // Final time
                         //lrfdCreepCoefficient2005::CuringMethod curingMethod,
                         //Float64 tCuringAdjustment, // time scale factor for curing method
                         bool bIgnoreInitialRelaxation,
                         bool bValidateParameters,
                         RelaxationLossMethod relaxationMethod,
                         std::shared_ptr<const lrfdCreepCoefficient2005>& pGirderCreepLoaded,
                         std::shared_ptr<const lrfdCreepCoefficient2005>& pDeckCreep
                         );

   //------------------------------------------------------------------------
   // Destructor
   ~lrfdRefinedLosses2005();


   //------------------------------------------------------------------------
   // loss from transfer to shipping
   Float64 TemporaryStrand_ShrinkageLossAtShipping() const;
   Float64 TemporaryStrand_CreepLossAtShipping() const;
   Float64 TemporaryStrand_RelaxationLossAtShipping() const;

   Float64 PermanentStrand_ShrinkageLossAtShipping() const;
   Float64 PermanentStrand_CreepLossAtShipping() const;
   Float64 PermanentStrand_RelaxationLossAtShipping() const;

   //------------------------------------------------------------------------
   // loss from transfer to deck placement
   Float64 ShrinkageLossBeforeDeckPlacement() const;
   Float64 CreepLossBeforeDeckPlacement() const;
   Float64 RelaxationLossBeforeDeckPlacement() const;

   //------------------------------------------------------------------------
   // loss from deck placement to final
   Float64 ShrinkageLossAfterDeckPlacement() const;
   Float64 CreepLossAfterDeckPlacement() const;
   Float64 RelaxationLossAfterDeckPlacement() const;

   //------------------------------------------------------------------------
   virtual Float64 TemporaryStrand_TimeDependentLossesAtShipping() const override;
   virtual Float64 PermanentStrand_TimeDependentLossesAtShipping() const override;
   virtual Float64 TimeDependentLossesBeforeDeck() const override;
   virtual Float64 TimeDependentLossesAfterDeck() const override;
   Float64 TimeDependentLosses() const;


   //------------------------------------------------------------------------
   std::shared_ptr<const lrfdCreepCoefficient2005> GetGirderCreep() const;
   std::shared_ptr<const lrfdCreepCoefficient2005> GetDeckCreep() const;

   //------------------------------------------------------------------------
   Float64 GetTemporaryStrandFcgp() const;
   Float64 GetPermanentStrandFcgp() const;
   Float64 GetTemporaryStrandFpt() const;
   Float64 GetPermanentStrandFpt() const;
   Float64 GetDeltaFcd() const; // for creep deck to final
   Float64 GetDeltaFcdf() const;

   //------------------------------------------------------------------------
   // Creep and shrinkage parameters
   Float64 Getkhs() const;
   Float64 Get_ebid() const;
   Float64 Get_ebih() const;
   Float64 GetKid() const;
   Float64 GetTemporaryStrandKih() const;
   Float64 GetPermanentStrandKih() const;
   Float64 GetTemporaryStrandKL() const;
   Float64 GetPermanentStrandKL() const;
   Float64 Get_ebdf() const;
   Float64 Get_ebif() const;
   Float64 GetKdf() const;
   Float64 Get_eddf() const;

   // GROUP: ACCESS


   // Returns true if the girder concrete strinkage strain is increased by 20%
   // per LRFD 5.4.2.3.3
   bool AdjustShrinkageStrain() const;

   void SetAgeAtHauling(Float64 t);
   Float64 GetAgeAtHauling() const;

   void SetAgeAtDeckPlacement(Float64 t);
   Float64 GetAgeAtDeckPlacement() const;

   void SetFinalAge(Float64 t);
   Float64 GetFinalAge() const;

   Float64 GetMaturityAtHauling() const;
   Float64 GetMaturityAtDeckPlacement() const;
   Float64 GetMaturityAtFinal() const;
   Float64 GetMaturityDeckPlacementToFinal() const;

   Float64 GetDeckInitialAge() const;
   Float64 GetDeckMaturityAtFinal() const;

   virtual void GetDeckShrinkageEffects(Float64* pA,Float64* pM) const override;

   //------------------------------------------------------------------------
   // Deck Geometry

   // eccentricty of deck
   void SetDeckEccentricity(Float64 e);
   Float64 GetDeckEccentricity() const;

   // area of deck
   void SetAd(Float64 Ad);
   Float64 GetAd() const;

   // factor that is multiplied with the deck shrinkage strain
   // to set the effectiveness of the shrinkage strain.
   // Use 0.0 to remove deck shrinkage, 1.0 to account for full deck shrinkage
   // 0.5 for half deck shrinage, and so on.
   void SetDeckShrinkageFactor(Float64 Ksh);
   Float64 GetDeckShrinakgeFactor() const;


   Float64 GetGdrK1Shrinkage() const { return m_ShrinkageK1; }
   Float64 GetGdrK2Shrinkage() const { return m_ShrinkageK2; }

   Float64 GetDeckK1Shrinkage() const { return m_DeckShrinkageK1; }
   Float64 GetDeckK2Shrinkage() const { return m_DeckShrinkageK2; }

   void SetRelaxationLossMethod(RelaxationLossMethod method);
   RelaxationLossMethod GetRelaxationLossMethod() const;
   
   // GROUP: INQUIRY
   // GROUP: DEBUG
   #if defined _UNITTEST
   static bool TestMe(WBFL::Debug::Log& rlog);
   #endif // _UNITTEST

protected:
   virtual void ValidateParameters() const override;
   virtual void UpdateLongTermLosses() const override;
   virtual void UpdateHaulingLosses() const override;
   virtual Float64 GetShrinkageHumidityFactor() const;
   virtual Float64 GetShrinkageStrainAtHauling() const;
   virtual Float64 GetShrinkageStrainAtDeckPlacement() const;
   virtual Float64 GetShrinkageStrainAtFinal() const;
   virtual Float64 GetDeckShrinkageStrain() const;
   virtual Float64 GetShrinkageStrain_Girder() const;
   virtual Float64 GetShrinkageStrain_Deck() const;

   Float64 m_th; // time at hauling
   Float64 m_td; // age at deck placement
   Float64 m_tf; // final time
   Float64 m_ShrinkageK1;
   Float64 m_ShrinkageK2;
   Float64 m_DeckShrinkageK1;
   Float64 m_DeckShrinkageK2;

   std::shared_ptr<const lrfdCreepCoefficient2005> m_pGirderCreep;
   std::shared_ptr<const lrfdCreepCoefficient2005> m_pDeckCreep;

   
   Float64 m_Ad;    // Area of composite deck
   Float64 m_ed;    // Eccentricity of deck with respect to the transformed net composite section (neg if deck is above girder)
   Float64 m_Ksh;   // deck shrinkage factor

   RelaxationLossMethod m_RelaxationMethod;


   mutable Float64 m_DeltaFcd3;
   mutable Float64 m_DeltaFcd;
   mutable Float64 m_DeltaFcdf;


   mutable Float64 m_khs;
   mutable Float64 m_ebid;
   mutable Float64 m_ebih;
   mutable Float64 m_Kid;
   mutable std::array<Float64, 2> m_Kih;
   mutable std::array<Float64, 2> m_KL;
   mutable Float64 m_ebif;
   mutable Float64 m_ebdf;
   mutable Float64 m_Kdf;
   mutable Float64 m_eddf;

   mutable Float64 m_dfpSR;
   mutable Float64 m_dfpCR;
   mutable Float64 m_dfpR1;
   mutable Float64 m_dfpSD;
   mutable Float64 m_dfpCD;
   mutable Float64 m_dfpR2;

   // hauling losses
   mutable std::array<Float64, 2> m_dfpSRH;
   mutable std::array<Float64, 2> m_dfpCRH;
   mutable std::array<Float64, 2> m_dfpR1H;
   mutable std::array<Float64, 2> m_dfpTH;
};

// INLINE METHODS
//
inline void lrfdRefinedLosses2005::SetDeckEccentricity(Float64 e) { m_ed; m_IsDirty = true; }
inline Float64 lrfdRefinedLosses2005::GetDeckEccentricity() const { return m_ed; }
inline void lrfdRefinedLosses2005::SetAd(Float64 Ad) { m_Ad = Ad; m_IsDirty = true; }
inline Float64 lrfdRefinedLosses2005::GetAd() const { return m_Ad; }
inline void lrfdRefinedLosses2005::SetDeckShrinkageFactor(Float64 Ksh) { m_Ksh = Ksh; m_IsDirty = true; }
inline Float64 lrfdRefinedLosses2005::GetDeckShrinakgeFactor() const { return m_Ksh; }

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_REFINEDLOSSES2005_H_
