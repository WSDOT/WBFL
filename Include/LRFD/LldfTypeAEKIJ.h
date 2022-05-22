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

#ifndef INCLUDED_LRFD_LLDFTYPEAEKIJ_H_
#define INCLUDED_LRFD_LLDFTYPEAEKIJ_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <Lrfd\LiveLoadDistributionFactorBase.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdLldfTypeAEKIJ

   Live load distribution factor calculator for cross section types A, E, K,
   I, and J.


DESCRIPTION
   Live load distribution factor calculator for cross section types A, E, K,
   I, and J.

LOG
   rab : 11.12.1998 : Created file
*****************************************************************************/

class LRFDCLASS lrfdLldfTypeAEKIJ : public lrfdLiveLoadDistributionFactorBase
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdLldfTypeAEKIJ(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                     Uint32 Nl, Float64 wLane,
                     Float64 deLeft,Float64 deRight,Float64 L,Float64 ts,Float64 n,
                     Float64 I, Float64 A, Float64 eg,
                     Float64 skewAngle1, Float64 skewAngle2,
                     bool bSkewMoment,
                     bool bSkewShear);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdLldfTypeAEKIJ(const lrfdLldfTypeAEKIJ& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdLldfTypeAEKIJ() override;

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdLldfTypeAEKIJ& operator = (const lrfdLldfTypeAEKIJ& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   Float64 MomentSkewCorrectionFactor() const;

   //------------------------------------------------------------------------
   Float64 ShearSkewCorrectionFactor() const;
   
   //------------------------------------------------------------------------
   Float64 GetKg() const;


   //------------------------------------------------------------------------
   virtual bool TestRangeOfApplicability(Location loc) const override;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Int_1_Strength() const override;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Int_2_Strength() const override;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_1_Strength() const override;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_2_Strength() const override;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Int_1_Strength() const override;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Int_2_Strength() const override;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_1_Strength() const override;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_2_Strength() const override;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   Float64 m_LeftDe;
   Float64 m_RightDe;
   Float64 m_L;
   Float64 m_ts;
   Float64 m_n;
   Float64 m_A;
   Float64 m_I;
   Float64 m_eg;
   Float64 m_SkewAngle1;
   Float64 m_SkewAngle2;
   bool m_bIgnoreDe; // not the best OO design, but some of our children would like to ignore the check for this

   Float64 m_Kg;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const lrfdLldfTypeAEKIJ& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdLldfTypeAEKIJ& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

   // rules for determining which equation to use
   bool SpGreaterThan16_Rule(bool bSISpec) const;
   bool InteriorMomentEquationRule(bool bSISpec, bool doThrow) const;
   bool InteriorShearEquationRule(bool bSISpec, bool doThrow) const;
   bool ExteriorMomentEquationRule(bool bSISpec, bool doThrow) const;
   bool DeRule(bool bSISpec, bool doThrow) const;

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const override;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(WBFL::Debug::LogContext& os) const override;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(WBFL::Debug::Log& rlog);
   #endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_LLDFTYPEAEKIJ_H_
