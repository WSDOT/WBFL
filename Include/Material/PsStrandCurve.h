///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_MATERIAL_PSSTRANDCURVE_H_
#define INCLUDED_MATERIAL_PSSTRANDCURVE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Material\MaterialExp.h>
#include <Material\YieldStressStrainCurve.h>
#include <Material\PsStrand.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   matPsStrandCurve

   A class for prestress strand steel strain-strain models.


DESCRIPTION
   A class for prestress strand steel strain-strain models.
   The material curve is taken from Section 2.11 of the PCI Precast Prestressed
   Concrete Bridge Design Manual, Oct 1997.

   This class assumes that prestressing strands do not have any compressive
   capacity.  Zero stress will result for all compressive strains.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.18.1997 : Created file
*****************************************************************************/

class MATCLASS matPsStrandCurve : public matYieldStressStrainCurve
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   matPsStrandCurve(const matPsStrand& strand);

   //------------------------------------------------------------------------
   // Copy constructor
   matPsStrandCurve(const matPsStrandCurve& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~matPsStrandCurve();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   matPsStrandCurve& operator = (const matPsStrandCurve& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // CreateClone
   // Creates a polymorphic type-safe clone of this curve.
   virtual matStressStrainCurve * CreateClone() const;

   //------------------------------------------------------------------------
   matStressStrainCurve::StrainState GetStress(Float64 strain,Float64* pStress) const;

   //------------------------------------------------------------------------
   // Given stress, computes the corrosponding strain.  Returns the strain
   // state of the material for the give stress level.  If the return value
   // is TensileFractured or CompressionFractured, the strain is undefined.
   matStressStrainCurve::StrainState GetStrain(Float64 stress,Float64* pStrain) const;

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
   // Self diagnostic test
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const matPsStrandCurve& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const matPsStrandCurve& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   bool m_bIsGr1725;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_MATERIAL_PSSTRANDCURVE_H_
