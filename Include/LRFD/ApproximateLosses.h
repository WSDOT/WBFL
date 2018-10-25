///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2018  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_APPROXIMATELOSSES_H_
#define INCLUDED_LRFD_APPROXIMATELOSSES_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <Lrfd\PsStrand.h>
#include <Lrfd\Losses.h>
#include <Lrfd\ConcreteUtil.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdApproximateLosses

   Utility class for computing prestress losses using the LRFD Approximate Lump
   Sum Method.


DESCRIPTION
   Utility class for computing prestress losses using the LRFD Approximate Lump
   Sum Method. Implements the provisions of Article 5.9.5.2.3 and 5.9.5.3.

LOG
   rab : 03.31.1999 : Created file
*****************************************************************************/

class LRFDCLASS lrfdApproximateLosses : public lrfdLosses
{
public:
   enum BeamType { IBeam, UBeam, SolidSlab, BoxBeam, SingleT };

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
   // BeamType = IBeam
   lrfdApproximateLosses();

   //------------------------------------------------------------------------
   // Constructor.  Initializes the object with the give values.
   // fpy is initialized to 0.85fpu for StressRelieved strands and
   // 0.90fpu for LowRelaxation strands.
   lrfdApproximateLosses(BeamType beamType,
                         Float64 shipping,
                         Float64 ppr,
                         Float64 x, // location along girder where losses are computed
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
                         Float64 epermRelease, // eccentricty of permanent ps strands with respect to CG of girder at release
                         Float64 epermFinal, // eccentricty of permanent ps strands with respect to CG of girder at final
                         Float64 etemp, // eccentricty of temporary strands with respect to CG of girder
                         TempStrandUsage usage,
                         Float64 anchorSet,
                         Float64 wobble,
                         Float64 friction,
                         Float64 angleChange,

                         lrfdConcreteUtil::DensityType concreteType,
                         Float64 Fc,   // 28 day strength of girder concrete
                         Float64 Fci,  // Release strength
                         Float64 FcSlab,   
                         Float64 Ec,   // Modulus of elasticity of girder
                         Float64 Eci,  // Modulus of elasticity of girder at transfer
                         Float64 Ecd,  // Modulus of elasticity of deck

                         Float64 Mdlg,  // Dead load moment of girder only
                         Float64 Madlg,  // Additional dead load on girder section
                         Float64 Msidl, // Superimposed dead loads

                         Float64 Ag,    // Area of girder
                         Float64 Ig,    // Moment of inertia of girder
                         Float64 Ybg,   // Centroid of girder measured from bottom
                         Float64 Ac,    // Area of the composite girder and deck
                         Float64 Ic,    // Moment of inertia of composite
                         Float64 Ybc,   // Centroid of composite measured from bottom

                         Float64 An,    // Area of girder
                         Float64 In,    // Moment of inertia of girder
                         Float64 Ybn,   // Centroid of girder measured from bottom
                         Float64 Acn,    // Area of the composite girder and deck
                         Float64 Icn,    // Moment of inertia of composite
                         Float64 Ybcn,   // Centroid of composite measured from bottom

                         Float64 rh,      // relative humidity
                         Float64 ti,   // Time until prestress transfer
                         bool bIgnoreInitialRelaxation,
                         bool bValidateParameters
                         );

   //------------------------------------------------------------------------
   // Copy c'tor
   lrfdApproximateLosses(const lrfdApproximateLosses& rOther);

   //------------------------------------------------------------------------
   // Destructor
   ~lrfdApproximateLosses();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   lrfdApproximateLosses& operator=(const lrfdApproximateLosses& rOther);

   // GROUP: OPERATIONS
   virtual Float64 TemporaryStrand_TimeDependentLossesAtShipping() const override;
   virtual Float64 PermanentStrand_TimeDependentLossesAtShipping() const override;
   virtual Float64 TimeDependentLossesBeforeDeck() const override;
   virtual Float64 TimeDependentLossesAfterDeck() const override;
   virtual Float64 TimeDependentLosses() const override;

   virtual Float64 PermanentStrand_Final() const override;
   virtual Float64 PermanentStrand_BeforeTemporaryStrandRemoval() const override;
   virtual Float64 PermanentStrand_AfterTemporaryStrandRemoval() const override;

   // GROUP: INQUIRY
   void SetBeamType(BeamType beamType);
   BeamType GetBeamType() const;

   void SetPPR(Float64 ppr);
   Float64 GetPPR() const;

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
   void MakeAssignment( const lrfdApproximateLosses& rOther );

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   lrfdConcreteUtil::DensityType m_ConcreteType;
   BeamType m_BeamType;
   Float64 m_PPR;
   Float64 m_Shipping;

   mutable Float64 m_dfpLT;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeCopy( const lrfdApproximateLosses& rOther );

   virtual void ValidateParameters() const override;
   virtual void UpdateLongTermLosses() const override;
   virtual void UpdateHaulingLosses() const override;


   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

inline void lrfdApproximateLosses::SetBeamType(lrfdApproximateLosses::BeamType beamType) { m_BeamType = beamType; m_IsDirty = true; }
inline lrfdApproximateLosses::BeamType lrfdApproximateLosses::GetBeamType() const { return m_BeamType; }
inline void lrfdApproximateLosses::SetPPR(Float64 ppr) { m_PPR = ppr; m_IsDirty = true; }
inline Float64 lrfdApproximateLosses::GetPPR() const { return m_PPR; }

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_APPROXIMATELOSSES_H_
