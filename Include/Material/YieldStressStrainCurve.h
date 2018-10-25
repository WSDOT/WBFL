///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_MATERIAL_YIELDSTRESSSTRAINCURVE_H_
#define INCLUDED_MATERIAL_YIELDSTRESSSTRAINCURVE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Material\MaterialExp.h>
#include <Material\StressStrainCurve.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   matYieldStressStrainCurve

   Abstract base class for stress strain models that exhibit a defined
   elastic region and yield points.


DESCRIPTION
   Abstract base class for stress strain models that exhibit a defined
   elastic region and yield points.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class MATCLASS matYieldStressStrainCurve : public matStressStrainCurve
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   matYieldStressStrainCurve();

   //------------------------------------------------------------------------
   // Constructor. Initializes the stress strain curve with the supplied parameters.
   matYieldStressStrainCurve(const std::_tstring& name,
                             Float64 E,
                             Float64 tensYieldStress,
                             Float64 compYieldStress,
                             Float64 tensUltStrain,
                             Float64 tensUltStress,
                             Float64 compUltStrain,
                             Float64 compUltStress,
                             Float64 fractureStrain,
                             Float64 fractureStress,
                             Float64 crushingStrain,
                             Float64 crushingStress);

   //------------------------------------------------------------------------
   // Copy constructor
   matYieldStressStrainCurve(const matYieldStressStrainCurve& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~matYieldStressStrainCurve();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   matYieldStressStrainCurve& operator = (const matYieldStressStrainCurve& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetE(Float64 E);

   //------------------------------------------------------------------------
   Float64 GetE() const;

   //------------------------------------------------------------------------
   Float64 GetTensYieldStrain() const;

   //------------------------------------------------------------------------
   Float64 GetTensYieldStress() const;

   //------------------------------------------------------------------------
   Float64 GetCompYieldStrain() const;

   //------------------------------------------------------------------------
   Float64 GetCompYieldStress() const;

   //------------------------------------------------------------------------
   Float64 GetTensUltStrain() const;

   //------------------------------------------------------------------------
   Float64 GetTensUltStress() const;

   //------------------------------------------------------------------------
   Float64 GetCompUltStrain() const;

   //------------------------------------------------------------------------
   Float64 GetCompUltStress() const;
   
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
   //------------------------------------------------------------------------
   void MakeCopy(const matYieldStressStrainCurve& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const matYieldStressStrainCurve& rOther);

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetTensYieldStress(Float64 tys);

   //------------------------------------------------------------------------
   void SetCompYieldStress(Float64 cys);

   //------------------------------------------------------------------------
   void SetTensUltStrain(Float64 tys);

   //------------------------------------------------------------------------
   void SetTensUltStress(Float64 tys);

   //------------------------------------------------------------------------
   void SetCompUltStrain(Float64 cys);

   //------------------------------------------------------------------------
   void SetCompUltStress(Float64 cys);

   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_ModE;
   Float64 m_TensYieldStress;
   Float64 m_CompYieldStress;
   Float64 m_TensUltStrain;
   Float64 m_TensUltStress;
   Float64 m_CompUltStrain;
   Float64 m_CompUltStress;
   Float64 m_TensYieldStrain;
   Float64 m_CompYieldStrain;

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

#endif // INCLUDED_MATERIAL_YIELDSTRESSSTRAINCURVE_H_
