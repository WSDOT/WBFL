///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2011  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_APPROXIMATELOSSES2005_H_
#define INCLUDED_LRFD_APPROXIMATELOSSES2005_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <Lrfd\PsStrand.h>
#include <Lrfd\VersionMgrListener.h>
#include <Lrfd\Losses.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdApproximateLosses2005

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

class LRFDCLASS lrfdApproximateLosses2005 : public lrfdLosses
{
public:
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
   lrfdApproximateLosses2005();

   //------------------------------------------------------------------------
   // Constructor.  Initializes the object with the give values.
   // fpy is initialized to 0.85fpu for StressRelieved strands and
   // 0.90fpu for LowRelaxation strands.
   lrfdApproximateLosses2005(Float64 x, // location along girder where losses are computed
                         Float64 Lg,    // girder length
                         matPsStrand::Grade gr,
                         matPsStrand::Type type,
                         Float64 fpjPerm, // fpj permanent strands
                         Float64 fpjTemp, // fpj of temporary strands
                         Float64 ApsPerm,  // area of permanent strand
                         Float64 ApsTemp,  // area of TTS 
                         Float64 aps,      // area of one strand
                         Float64 eperm, // eccentricty of permanent ps strands with respect to CG of girder
                         Float64 etemp, // eccentricty of temporary strands with respect to CG of girder
                         TempStrandUsage usage,
                         Float64 anchorSet,
                         Float64 wobble,
                         Float64 friction,
                         Float64 angleChange,

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

                         Float64 rh,      // relative humidity
                         Float64 ti,   // Time until prestress transfer
                         bool bIgnoreInitialRelaxation,
                         bool bValidateParameters
                         );

   //------------------------------------------------------------------------
   // Copy c'tor
   lrfdApproximateLosses2005(const lrfdApproximateLosses2005& rOther);

   //------------------------------------------------------------------------
   // Destructor
   ~lrfdApproximateLosses2005();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   lrfdApproximateLosses2005& operator=(const lrfdApproximateLosses2005& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   Float64 TemporaryStrand_RelaxationLossesAtXfer() const;
   Float64 PermanentStrand_RelaxationLossesAtXfer() const;

   //------------------------------------------------------------------------
   Float64 TemporaryStrand_ImmediatelyBeforeXferLosses() const;
   Float64 PermanentStrand_ImmediatelyBeforeXferLosses() const;

   //------------------------------------------------------------------------
   Float64 TemporaryStrand_ImmediatelyAfterXferLosses() const;
   Float64 PermanentStrand_ImmediatelyAfterXferLosses() const;

   //------------------------------------------------------------------------
   // Time dependent losses at shipping (assumed to occur at 10 days)
   virtual Float64 TemporaryStrand_TimeDependentLossesAtShipping() const;
   virtual Float64 PermanentStrand_TimeDependentLossesAtShipping() const;

   //------------------------------------------------------------------------
   Float64 TimeDependentLosses() const;

   Float64 TimeDependentLossesBeforeDeck() const;
   Float64 TimeDependentLossesAfterDeck() const;

   virtual Float64 PermanentStrand_Final() const;
   virtual Float64 PermanentStrand_BeforeTemporaryStrandRemoval() const;
   virtual Float64 PermanentStrand_AfterTemporaryStrandRemoval() const;

   Float64 GetHumidityFactor() const;
   Float64 GetStrengthFactor() const;

   Float64 GetFpi() const;

   // GROUP: ACCESS


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
   void MakeAssignment( const lrfdApproximateLosses2005& rOther );

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   mutable Float64 m_dfpTH; // time dependent losses at shipping/hauling
   mutable Float64 m_dfpLT;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   Float64 RelaxationLossesAtXfer() const;

   //------------------------------------------------------------------------
   void MakeCopy( const lrfdApproximateLosses2005& rOther );

   //------------------------------------------------------------------------
   virtual void ValidateParameters() const;

   //------------------------------------------------------------------------
   virtual void UpdateLongTermLosses() const;
   
   //------------------------------------------------------------------------
   virtual void UpdateHaulingLosses() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//


// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_APPROXIMATELOSSES2005_H_
