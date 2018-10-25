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

#ifndef INCLUDED_LRFD_PSSTRANDS_H_
#define INCLUDED_LRFD_PSSTRANDS_H_
#pragma once

// SYSTEM INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <Material\PsStrand.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdPsStrand

   Encapsulates constants and equations associated with prestressing strands.


DESCRIPTION
   Encapsulates constants and equations associated with prestressing strands.

LOG
   rab : 12.09.1997 : Created file
*****************************************************************************/

class LRFDCLASS lrfdPsStrand
{
public:
   // GROUP: ENUMERATIONS
   enum Stage { Jacking, BeforeTransfer, AfterTransfer, AfterAllLosses };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdPsStrand();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   static Float64 GetUltimateStrength(matPsStrand::Grade gr);
   static Float64 GetYieldStrength(matPsStrand::Grade gr,matPsStrand::Type type);
   static Float64 GetStressLimit(matPsStrand::Grade gr,matPsStrand::Type type,Stage stage);
   static Float64 GetModE();

   //------------------------------------------------------------------------
   // Calculates the maximum jacking force for the specified prestressing
   // strands.
   static Float64 GetPjack(const matPsStrand& strand,StrandIndexType nStrands,Float64 timeToXfer);
   static Float64 GetPjack(const matPsStrand& strand,StrandIndexType nStrands,Float64 timeToXfer,Float64 coeff);

   //------------------------------------------------------------------------
   // Calcuates the maximum jacking stress for the specified prestressing strands.
   static Float64 GetFpj(const matPsStrand& strand,Float64 timeToXfer);
   static Float64 GetFpj(const matPsStrand& strand,Float64 timeToXfer,Float64 coeff);

   //------------------------------------------------------------------------
   // Computes the prestress transfer length. 5.11.4.1
   static Float64 GetXferLength(const matPsStrand& strand,bool bEpoxyCoated);

   //------------------------------------------------------------------------
   // Returns the coefficient k used to compute the prestress development length. 5.11.4.2
   static Float64 GetDevLengthFactor(Float64 mbrDepth,bool bDebonded);

   //------------------------------------------------------------------------
   // Computes the prestress development length. 5.11.4.2
   static Float64 GetDevLength(const matPsStrand& strand,Float64 fps,Float64 fpe,Float64 mbrDepth,bool bDebonded=false);

   //------------------------------------------------------------------------
   // Computes the maximum jacking stress for post-tensioning
   static Float64 GetFpjPT(const matPsStrand& strand);

   //------------------------------------------------------------------------
   // Computes the maximum jacking force for post-tensioning
   static Float64 GetPjackPT(const matPsStrand& strand,StrandIndexType nStrands);

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
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG
#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
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
   lrfdPsStrand();

   // Prevent accidental copying and assignment
   lrfdPsStrand(const lrfdPsStrand&);
   lrfdPsStrand& operator=(const lrfdPsStrand&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_PSSTRANDS_H_
