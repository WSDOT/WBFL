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

#ifndef INCLUDED_LRFD_SHEAR_H_
#define INCLUDED_LRFD_SHEAR_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Lrfd\LrfdExp.h>

// LOCAL INCLUDES
//
#include <Materials/Concrete.h>

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdShearData

   Encapsulates shear data.


DESCRIPTION
   Encapsulates shear data.

LOG
   rab : 02.03.1998 : Created file
*****************************************************************************/
struct LRFDCLASS lrfdShearData
{
   lrfdShearData()
   {
      memset((void*)this, 0, sizeof(lrfdShearData));
   };

   // Input Parameters
   Float64 Mu;
   Float64 Nu;
   Float64 Vu;
   Float64 phi;
   Float64 Vp;
   Float64 dv;
   Float64 bv;
   Float64 Es;
   Float64 As;
   Float64 Eps;
   Float64 Aps;
   Float64 EptSegment;
   Float64 AptSegment;
   Float64 EptGirder;
   Float64 AptGirder;
   Float64 Ec;
   Float64 Ac;
   Float64 fpops;
   Float64 fpoptSegment;
   Float64 fpoptGirder;
   Float64 fc;
   WBFL::Materials::ConcreteType ConcreteType;
   bool bHasfct;
   Float64 fct;
   Float64 ag; // max aggregate size
   Float64 sx; // spacing between layers of longitudinal cracking steel
   bool bLimitNetTensionStrainToPositiveValues; // sets strain at the tensile reinforcement to zero if computed to be negative
   bool bIgnoreMiniumStirrupRequirementForBeta; // if true, LRFD Equation 5.7.3.4.2-1 is used to compute Beta regardless of the amount of stirrups

   // Vci/Vcw parameters
   Float64 Vd;
   Float64 Vi; // shear corresponding to Mu (Mu = Mmax)
   Float64 Mcre; // cracking moment per LRFD 5.8.3.4.3-2
   Float64 fpc;
   Float64 lambda; //concrete density modification factor per LRFD2016 5.4.2.8

   Float64 fy;  // Yield strength of stirrup material. Only applicable for 2nd Edition 2000 Interims or later
   Float64 AvS; // Av/s per 5.8.2.5 (equation 5.8.2.5-1)
                // Only applicable for 2nd Edition 2000 Interims or later.

   // Output Parameters
   Float64 Beta;
   Float64 Theta;
   Float64 ex;
   Float64 Fe; // = -1 if not applicable
   Float64 vu; // from 2.8.9.2
   Float64 vufc;   // v/fc
   Float64 vufc_tbl; // vfc from table (2000 and later)

   Float64 sxe; // crack spacing parameter
   Float64 sxe_tbl; // crack spacing parameter from table

   Float64 ex_tbl; // ex from table (2000 and later)
   Int16 Eqn; // Equation used to compute strain (ex). Only applicable
              // 2nd Edition, 2000 Interims and later.
              // 0 = Not applicable
              // 1 = Eqn 5.8.3.4.2-1
              // 2 = Eqn 5.8.3.4.2-2
              // 31 = Eqn 5.8.3.4.2-3 after 5.8.3.4.2-1
              // 32 = Eqn 5.8.3.4.2-3 after 5.8.3.4.2-2

   Int16 BetaEqn; // Equation used to compute Beta. Only applicable 2009 and after
              // 0 = Not applicable
              // 1 = Eqn 5.8.3.4.2-1
              // 2 = Eqn 5.8.3.4.2-2 - lacks minimum shear reinforcement

   Int16 BetaTheta_tbl; // Table used to retreive Beta/Theta
              // 0 = Not applicable
              // 1 = Table 5.8.3.4.2-1
              // 2 = Table 5.8.3.4.2-2 - lacks minimum shear reinforcement
 
   Float64 VciMin; // Minimum Vci calculated by equation 5.8.3.4.3-1
   Float64 VciCalc; // Vci calculated by equation 5.8.3.4.3-1
   Float64 Vci; // Controlling Vci (max of VciCalc and Vci)
   Float64 Vcw; // Vcw
};

/*****************************************************************************
CLASS 
   lrfdShear

   Utility class for shear related provisions.


DESCRIPTION
   Utility class for shear related provisions.

LOG
   rab : 02.03.1998 : Created file
*****************************************************************************/

class LRFDCLASS lrfdShear
{
public:
   typedef enum Method { Tables, Equations } Method;
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdShear();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Computes the Theta and Beta factors for LRFD shear design.
   // If the beta and theta factors could not be determined, a
   // lrfdXShear exception will be thrown.
   // See Article 5.8.3.4
   static void ComputeThetaAndBeta(lrfdShearData* pData, Method method = Tables);


   //------------------------------------------------------------------------
   // Computes Vci and Vcw per LRFD 4th edition 2007
   static void ComputeVciVcw(lrfdShearData* pData);

   //------------------------------------------------------------------------
   // Computes shear stress via 5.8.9.2
   static Float64 ComputeShearStress(Float64 Vu, Float64 Vp, Float64 phi, Float64 bv, Float64 dv);


   // GROUP: ACCESS
   // GROUP: INQUIRY

   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(WBFL::Debug::LogContext& os) const;

#endif // _DEBUG

#if defined _UNITTEST
   static bool TestMe(WBFL::Debug::Log& rlog);
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
   lrfdShear();

   // Prevent accidental copying and assignment
   lrfdShear(const lrfdShear&);
   lrfdShear& operator=(const lrfdShear&) = delete;

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

/*****************************************************************************
CLASS 
   lrfdWsdotShear

   Utility class for shear related provisions.


DESCRIPTION
   Utility class for shear related provisions, incorporating WSDOT specific procedures

LOG
   rab : 10.17.2001 : Created file
*****************************************************************************/

class LRFDCLASS lrfdWsdotShear : public lrfdShear
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdWsdotShear() override;

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Computes the Theta and Beta factors for LRFD shear design.
   // If the beta and theta factors could not be determined, a
   // lrfdXShear exception will be thrown.
   // See Article 5.8.3.4
   //
   // If based on LRFD 2005, we need to know if shear is being computed in the end region
   // If it is not in the end region, Theta is limited to 25 degrees... See BDM 5.2.4F.2
   static void ComputeThetaAndBeta(lrfdShearData* pData,bool bEndRegion = true);

   // GROUP: ACCESS
   // GROUP: INQUIRY

   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const override;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(WBFL::Debug::LogContext& os) const override;

#endif // _DEBUG

#if defined _UNITTEST
   static bool TestMe(WBFL::Debug::Log& rlog);
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
   lrfdWsdotShear();

   // Prevent accidental copying and assignment
   lrfdWsdotShear(const lrfdWsdotShear&);
   lrfdWsdotShear& operator=(const lrfdWsdotShear&) = delete;

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_SHEAR_H_
