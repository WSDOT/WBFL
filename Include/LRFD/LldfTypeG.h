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

#ifndef INCLUDED_LRFD_LLDFTYPEG_H_
#define INCLUDED_LRFD_LLDFTYPEG_H_
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
   lrfdLldfTypeG

   Live load distribution factor calculator for cross section types H and I and J
   if not sufficiently connected.


DESCRIPTION
   Live load distribution factor calculator for cross section types H and I and J
   if not sufficiently connected.


COPYRIGHT
   Copyright © 2005
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 07.15.2005 : Created file
*****************************************************************************/

class LRFDCLASS lrfdLldfTypeG : public lrfdLiveLoadDistributionFactorBase
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdLldfTypeG(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                 Uint32 Nl, Float64 wLane,
                 Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                 Float64 leftDe,Float64 rightDe,
                 Float64 PossionRatio, bool ignoreSkew,
                 Float64 skewAngle1, Float64 skewAngle2);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdLldfTypeG(const lrfdLldfTypeG& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdLldfTypeG();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdLldfTypeG& operator = (const lrfdLldfTypeG& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual Float64 MomentSkewCorrectionFactor() const;

   //------------------------------------------------------------------------
   virtual Float64 ShearSkewCorrectionFactor() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   Float64 m_L;
   Float64 m_W;
   Float64 m_I;
   Float64 m_J;
   Float64 m_b;
   Float64 m_d;
   Float64 m_LeftDe;
   Float64 m_RightDe;
   Float64 m_PoissonRatio;
   Float64 m_SkewAngle1;
   Float64 m_SkewAngle2;
   bool    m_IgnoreSkew;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const lrfdLldfTypeG& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdLldfTypeG& rOther);

   //------------------------------------------------------------------------
   virtual bool TestRangeOfApplicability(Location loc) const;

   virtual bool InteriorMomentEquationRule(bool bSISpec, bool doThrow) const;
   virtual bool ExteriorMomentEquationRule(bool bSISpec, bool doThrow) const;
   bool InteriorShearEquationRule(bool bSISpec) const;
   bool ExteriorShearEquationRule(bool bSISpec) const;
   bool IandJOutOfRangeRule(bool bSISpec) const;

   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Int_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Int_2_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_2_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Int_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Int_2_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_2_Strength() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};


/*****************************************************************************
CLASS 
   lrfdLldfTypeF

   Live load distribution factor calculator for cross section type F
   if not sufficiently connected.


DESCRIPTION
   Live load distribution factor calculator for cross section type F
   if not sufficiently connected.


COPYRIGHT
   Copyright © 2005
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 07.15.2005 : Created file
*****************************************************************************/

class LRFDCLASS lrfdLldfTypeF : public lrfdLldfTypeG
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdLldfTypeF(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                 Uint32 Nl, Float64 wLane,
                 Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                 Float64 leftDe,Float64 rightDe,
                 Float64 PossionRatio, bool ignoreSkew,
                 Float64 skewAngle1, Float64 skewAngle2);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdLldfTypeF(const lrfdLldfTypeF& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdLldfTypeF();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdLldfTypeF& operator = (const lrfdLldfTypeF& rOther);


   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const lrfdLldfTypeF& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdLldfTypeF& rOther);

   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Int_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Int_2_Strength() const;
   //------------------------------------------------------------------------
   virtual bool TestRangeOfApplicability(Location loc) const;

   virtual bool InteriorMomentEquationRule(bool bSISpec, bool doThrow) const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

/*****************************************************************************
CLASS 
   lrfdTxdotVoidedSlab

   Live load distribution factor calculator for cross section types F and G
   accounting for WSDOT modifications.


DESCRIPTION
   Live load distribution factor calculator for Slab Sections

   The Txdot modifications are:
   1) Live load distribution factors for all beams, both moment and shear, 
      must conform to AASHTO LRFD Bridge Design Specifications. Table 4.6.2.2.2b-1, 
      using cross section (g), if the beams are connected only enough to prevent 
      relative vertical displacement at their interfaces. 
      This is called S/D distribution.

   2) Do not apply the skew correction factors for moment as suggested in 
      Article 4.6.2.2.2e nor for shear as suggested in Article 4.6.2.2.3c.


COPYRIGHT
   Copyright © 1997-2001
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.09.2001 : Created file
*****************************************************************************/

class LRFDCLASS lrfdTxdotVoidedSlab: public lrfdLldfTypeG
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdTxdotVoidedSlab(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                 Uint32 Nl, Float64 wLane,
                 Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                 Float64 leftDe,Float64 rightDe,
                 Float64 PossionRatio,
                 Float64 skewAngle1, Float64 skewAngle2);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdTxdotVoidedSlab(const lrfdTxdotVoidedSlab& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdTxdotVoidedSlab();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdTxdotVoidedSlab& operator = (const lrfdTxdotVoidedSlab& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   
   //------------------------------------------------------------------------
   // Override these methods so the correct multiple presense factor is applied.
   virtual Float64 MomentSkewCorrectionFactor() const;
   //------------------------------------------------------------------------
   virtual Float64 ShearSkewCorrectionFactor() const;

   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Int_2_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_2_Strength() const;

   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Int_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Int_2_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_2_Strength() const;

   //------------------------------------------------------------------------
   void MakeCopy(const lrfdTxdotVoidedSlab& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdTxdotVoidedSlab& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};


// INLINE METHODS
//

// EXTERNAL REFERENCES
//


/*****************************************************************************
CLASS 
   lrfdTxdotLldfAdjacentBox

   Live load distribution factor calculator for adjacent box
   accounting for TxDOT modifications.


DESCRIPTION
   Live load distribution factor calculator for Slab Sections

   The Txdot modifications are:
   1) Beams are always treated a connected as unit transversely

   2) Do not apply the skew correction factors for moment as suggested in 
      Article 4.6.2.2.2e nor for shear as suggested in Article 4.6.2.2.3c.

   3) Exterior g cannot exceed interior factor


COPYRIGHT
   Copyright © 1997-2001
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.09.2001 : Created file
*****************************************************************************/

class LRFDCLASS lrfdTxdotLldfAdjacentBox: public lrfdLldfTypeF
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdTxdotLldfAdjacentBox(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                            Uint32 Nl, Float64 wLane,
                            Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                            Float64 leftDe,Float64 rightDe,
                            Float64 PossionRatio,
                            Float64 skewAngle1, Float64 skewAngle2);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdTxdotLldfAdjacentBox(const lrfdTxdotLldfAdjacentBox& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdTxdotLldfAdjacentBox();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdTxdotLldfAdjacentBox& operator = (const lrfdTxdotLldfAdjacentBox& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   
   //------------------------------------------------------------------------
   // No skew correction for txdot
   virtual Float64 MomentSkewCorrectionFactor() const;

   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_2_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_2_Strength() const;

   //------------------------------------------------------------------------
   void MakeCopy(const lrfdTxdotLldfAdjacentBox& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdTxdotLldfAdjacentBox& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};


// INLINE METHODS
//

// EXTERNAL REFERENCES
//



#endif // INCLUDED_LRFD_LLDFTYPEG_H_
