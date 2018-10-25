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

#ifndef INCLUDED_LRFD_LLDFTYPEBC_H_
#define INCLUDED_LRFD_LLDFTYPEBC_H_
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
   lrfdLldfTypeBC

   Live load distribution factor calculator for cross section types B and C
   with concrete decks.


DESCRIPTION
   Live load distribution factor calculator for cross section types B and C
   with concrete decks.

LOG
   rab : 10.09.2001 : Created file
*****************************************************************************/

class LRFDCLASS lrfdLldfTypeBC : public lrfdLiveLoadDistributionFactorBase
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdLldfTypeBC(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                  Uint32 Nl, Float64 wLane,
                  Float64 d,Float64 L,
                  Float64 leftDe,Float64 rightDe,
                  Float64 skewAngle1, Float64 skewAngle2,
                  bool bMomentSkew, bool bShearSkew);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdLldfTypeBC(const lrfdLldfTypeBC& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdLldfTypeBC() override;

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdLldfTypeBC& operator = (const lrfdLldfTypeBC& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   Float64 MomentSkewCorrectionFactor() const;

   //------------------------------------------------------------------------
   Float64 ShearSkewCorrectionFactor() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   Float64 m_d;
   Float64 m_L;
   Float64 m_LeftDe;
   Float64 m_RightDe;
   Float64 m_SkewAngle1;
   Float64 m_SkewAngle2;


   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const lrfdLldfTypeBC& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdLldfTypeBC& rOther);

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


   // Rules for ROA
   bool InteriorMomentEquationRule(bool bSISpec, bool doThrow) const;
   bool ExteriorMomentEquationRule(bool bSISpec, bool doThrow) const;
   bool SpacingTriggersLeverRule(bool bSISpec) const;


   // GROUP: ACCESS
   // GROUP: INQUIRY
   virtual bool DoApplySkew() const;

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
   virtual bool AssertValid() const override;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const override;
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
   lrfdWsdotLldfTypeBC

   Live load distribution factor calculator for cross section types B and C,
   accounting for WSDOT modifications.


DESCRIPTION
   Live load distribution factor calculator for cross section types B and C,
   accounting for WSDOT modifications.  These modifications are documented
   in a memorandum by C. C. Ruth, dated February 22, 1999.

   The WSDOT modifications are:
   1. For exterior girders with a slab cantilever length less than or equal to
      one-half of the adjacent interior girder spacing,  compute the distribution
      factor using the equations for an interior girder.  The slab cantilever
      length is defined as the distance from the centerline of the exterior girder
      to the edge of the slab.
   2. For exterior girders with a slab cantilever length exceeding one-half
      of the adjacent interior girder spacing, compute the live load distribution
      factor in accordance with the LRFD specification, except use a multiple
      presence factor of 1.0 for one design lane loaded.
   3. The special analysis based on the conventional approximation of loads on 
      piles per AASHTO-LRFD Article C4.6.2.2.2d shall not be used unless the
      effectiveness of diaphragms on the laterial distribution of truck loads
      is investigated.

LOG
   rab : 10.09.2001 : Created file
*****************************************************************************/

class LRFDCLASS lrfdWsdotLldfTypeBC: public lrfdLldfTypeBC
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdWsdotLldfTypeBC(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                       Uint32 Nl, Float64 wLane,
                       Float64 d,Float64 L,
                       Float64 leftDe,Float64 rightDe,
                       Float64 leftSlabOverhang,Float64 rightSlabOverhang,
                       Float64 skewAngle1, Float64 skewAngle2,
                       bool bMomentSkew, bool bShearSkew);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdWsdotLldfTypeBC(const lrfdWsdotLldfTypeBC& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdWsdotLldfTypeBC() override;

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdWsdotLldfTypeBC& operator = (const lrfdWsdotLldfTypeBC& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_1_Strength() const override;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_2_Strength() const override;

   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_1_Strength() const override;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_2_Strength() const override;

   //------------------------------------------------------------------------
   void MakeCopy(const lrfdWsdotLldfTypeBC& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdWsdotLldfTypeBC& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64      m_LeftSlabOverhang; // cl beam to edge of slab
   Float64      m_RightSlabOverhang;

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
   virtual bool AssertValid() const override;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const override;
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
   lrfdTxDotLldfTypeBC

   Live load distribution factor calculator for cross section types B and C,
   accounting for TxDot modifications.


DESCRIPTION
   Live load distribution factor calculator for cross section types B and C,
   accounting for TxDot modifications.  These modifications are documented
   in a memorandum by C. C. Ruth, dated February 22, 1999.

   The TxDot modifications are:
   1) Live load distribution factors must conform to AASHTO LRFD Bridge Design Specifications,
      Article 4.6.2.2.2 for flexural moment and Article 4.6.2.2.3 for
      shear, except for exterior beam design. For exterior beam design, use a distribution factor
      for two or more design lanes loaded only. 

   2) Do not use the distribution factor for one design
      lane loaded unless the clear roadway width is less than 20.0 ft. Use 1.0 for the multiple
      presence factor for one lane loaded. For exterior beams,
      multiply the result of the lever rule by 0.9 to account for continuity.

   3) The live load used to design the exterior beam must never be less than the live
      load used to design an interior beam.

LOG
   rab : 10.09.2001 : Created file
*****************************************************************************/

class LRFDCLASS lrfdTxDotLldfTypeBC: public lrfdLldfTypeBC
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdTxDotLldfTypeBC(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                  Uint32 Nl, Float64 wLane,
                  Float64 d,Float64 L,
                  Float64 leftDe,Float64 rightDe,
                  Float64 roadwayWidth,
                  Float64 skewAngle1, Float64 skewAngle2,
                  bool bMomentSkew, bool bShearSkew);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdTxDotLldfTypeBC(const lrfdTxDotLldfTypeBC& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdTxDotLldfTypeBC() override;

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdTxDotLldfTypeBC& operator = (const lrfdTxDotLldfTypeBC& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // TxDOT is more lax than aashto
   virtual bool TestRangeOfApplicability(Location loc) const override;
   
   //------------------------------------------------------------------------
   // Override this method so 90% of lever rule is applied to exterior beams for continuity.
   virtual lrfdILiveLoadDistributionFactor::LeverRuleMethod DistributeByLeverRule(GirderIndexType beamNum,const std::vector<Float64>& Spacings, Float64 leftOverhang, Float64 rightOverhang,Float64 wLane,IndexType Nl) const override;

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

   //
   // For fatigue, we need to use single lane behavior only
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Int_Fatigue() const;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_Fatigue() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Int_Fatigue() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_Fatigue() const;
   //------------------------------------------------------------------------
   virtual DFResult GetReactionDF_Ext_Fatigue() const;
   //------------------------------------------------------------------------
   virtual DFResult GetReactionDF_Int_Fatigue() const;


   //------------------------------------------------------------------------
   void MakeCopy(const lrfdTxDotLldfTypeBC& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdTxDotLldfTypeBC& rOther);

   // GROUP: ACCESS
   virtual bool DoApplySkew() const override;
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_RoadwayWidth;

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
   virtual bool AssertValid() const override;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const override;
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



#endif // INCLUDED_LRFD_LLDFTYPEBC_H_
