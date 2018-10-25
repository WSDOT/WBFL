///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_CONCRETEUTIL_H_
#define INCLUDED_LRFD_CONCRETEUTIL_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <System\Exception.h>
#include <System\SectionValue.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdConcreteUtil

   Utility class for concrete related calculations.


DESCRIPTION
   Utility class for concrete related calculations.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.14.1997 : Created file
*****************************************************************************/

class LRFDCLASS lrfdConcreteUtil
{
public:
   // GROUP: ENUMERATIONS
   enum DensityType { NormalDensity,
                      AllLowDensity,
                      SandLowDensity
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Destructor
   ~lrfdConcreteUtil();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Returns the minimum density for concrete to be considered normal weight
   // per LRFD 5.2
   static Float64 GetNWCDensityLimit();

   //------------------------------------------------------------------------
   // Returns the maximum density for concrete to be considered light weight
   // per LRFD 5.2
   static Float64 GetLWCDensityLimit();

   //------------------------------------------------------------------------
   // Returns the modulus of elasticity of concrete.  The modulus of elasticity
   // is computed in accordance with equation 5.4.2.4-1.
   // If density is out of range, a lrfdXModE exception is thrown.
   static Float64 ModE(Float64 fc,Float64 density,bool bCheckRange = true);

   //------------------------------------------------------------------------
   // Computes the concrete strength from the modulus of elasticy based on
   // LRFD Equation 5.2.4.2-1
   static Float64 FcFromEc(Float64 ec,Float64 density);

   //------------------------------------------------------------------------
   // Returns the modulus of rupture.  The modulus of rupture is computed in
   // accordnace with Article 5.4.2.6
   static Float64 ModRupture(Float64 fc, DensityType densityType);
   static Float64 ModRupture(Float64 fc, Float64 k);

   //------------------------------------------------------------------------
   // Returns the beta1 factor.  The beta1 factor is computed in accordance
   // with Article 5.7.2.2
   static Float64 Beta1(Float64 fc);

   //------------------------------------------------------------------------
   // Return shear friction factor per 5.8.4.2
   // normal density concrete only
   static Float64 ShearFrictionFactor(bool isRoughened);

   //------------------------------------------------------------------------
   // Return cohesion factor per 5.8.4.2
   // normal density concrete only
   static Float64 ShearCohesionFactor(bool isRoughened,lrfdConcreteUtil::DensityType girderDensityType,lrfdConcreteUtil::DensityType slabDensityType);

   //------------------------------------------------------------------------
   // Return K1 factor per 5.8.4.2
   // normal density concrete only
   static Float64 HorizShearK1(bool isRoughened);

   //------------------------------------------------------------------------
   // Return K2 factor per 5.8.4.2
   // normal density concrete only
   static Float64 HorizShearK2(bool isRoughened,lrfdConcreteUtil::DensityType girderDensityType,lrfdConcreteUtil::DensityType slabDensityType);

   //------------------------------------------------------------------------
   // Return nominal horizontal shear resistances per 5.8.4.1
   // Three resistances are returned for eqn's 1-3.
   // The governing resistance is determined by taking the min of these three
   static void HorizontalShearResistances(Float64 c, Float64 u, Float64 K1, Float64 K2,
                                          Float64 Acv, Float64 Avf, Float64 Pc,
                                          Float64 fc, Float64 fy,
                                          Float64* penqn1, Float64* penqn2, Float64* penqn3);

   //------------------------------------------------------------------------
   // Get lower limit of average shear strength Vn/Acv where steel is required by
   // 5.8.4.1-4.
   static Float64 LowerLimitOfShearStrength(bool isRoughened, bool doAllStirrupsEngageDeck);

   //------------------------------------------------------------------------
   // Get upper limit of bv for 5.8.4.1-4.
   static Float64 UpperLimitForBv();
   
   //------------------------------------------------------------------------
   // Get Min number of legs for a given bv  5.8.4.1-4.
   static Uint16 MinLegsForBv(Float64 bv);

   //------------------------------------------------------------------------
   // Calculate minimum Avf using 5.8.4.4
   // Use a struct to contain control information
   struct HsAvfOverSMinType
   {
      enum ValidEqnsType {eq41only, eqBoth}; // 
      ValidEqnsType ValidEqns; // Which equations were valid: 5.8.4.4-1, 5.8.4.1-3, or both
      Float64 res5_8_4_4_1;
      Float64 res5_8_4_1_3;
      Float64 AvfOverSMin; // Min of two values above, or zero if negative

      HsAvfOverSMinType(): // initialize with default constructor
      ValidEqns(eq41only), res5_8_4_4_1(0.0), res5_8_4_1_3(0.0), AvfOverSMin(0.0)
      {;}
   };

   static HsAvfOverSMinType AvfOverSMin(Float64 bv, Float64 fy,const sysSectionValue& Vuh,Float64 phi,Float64 c,Float64 u,Float64 pc);

   //------------------------------------------------------------------------
   // Max bar spacing 5.8.4.1/2
   static Float64 MaxStirrupSpacingForHoriz(Float64 Hg);

   //------------------------------------------------------------------------
   // Calculate required Avf for horizontal shear
   static Float64 AvfRequiredForHoriz(const sysSectionValue& Vuh, Float64 phi, Float64 AvfOverSMin,
                                      Float64 c, Float64 u, Float64 K1, Float64 K2,
                                      Float64 bv, Float64 Acv, Float64 Avf, Float64 Pc, 
                                      Float64 fc, Float64 fy);

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
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdConcreteUtil();

   // Prevent accidental copying and assignment
   lrfdConcreteUtil(const lrfdConcreteUtil&);
   lrfdConcreteUtil& operator=(const lrfdConcreteUtil&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
   static Float64 ModRupture(Float64 fc, DensityType densityType,Float64 k);
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_CONCRETEUTIL_H_
