///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_LLDFTXDOTMULTIWEB_H_
#define INCLUDED_LRFD_LLDFTXDOTMULTIWEB_H_
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
   lrfdTxdotLldfMultiWeb

   Live load distribution factor calculator for cross section types H and I and J
   if not sufficiently connected.


DESCRIPTION
   Live load distribution factor calculator for cross section types H and I and J
   if not sufficiently connected.

LOG
   rab : 07.15.2005 : Created file
*****************************************************************************/

class LRFDCLASS lrfdTxdotLldfMultiWeb : public lrfdLiveLoadDistributionFactorBase
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdTxdotLldfMultiWeb(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                         Uint32 Nl, Float64 wLane,
                         Float64 W, Float64 L, Float64 Kfactor,
                         Float64 skewAngle1, Float64 skewAngle2);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdTxdotLldfMultiWeb(const lrfdTxdotLldfMultiWeb& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdTxdotLldfMultiWeb() override;

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdTxdotLldfMultiWeb& operator = (const lrfdTxdotLldfMultiWeb& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   Float64 MomentSkewCorrectionFactor() const;

   //------------------------------------------------------------------------
   Float64 ShearSkewCorrectionFactor() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   Float64 m_L;
   Float64 m_W;
   Float64 m_Kfactor;
   Float64 m_SkewAngle1;
   Float64 m_SkewAngle2;


   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const lrfdTxdotLldfMultiWeb& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdTxdotLldfMultiWeb& rOther);

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


// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_LLDFTXDOTMULTIWEB_H_
