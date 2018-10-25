///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2016  Washington State Department of Transportation
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

#ifndef INCLUDED_MATERIAL_CONCRETEEX_H_
#define INCLUDED_MATERIAL_CONCRETEEX_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Material\MaterialExp.h>
#include <Material\Concrete.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   matConcreteEx

   Extends the concrete product model to include the density of concrete
   used for weight calculations.


DESCRIPTION
   Extends the concrete product model to include the density of concrete
   used for weight calculations.  WSDOT typically uses a higher value for
   the density of concrete to account for the weight of rebar.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 12.16.1997 : Created file
*****************************************************************************/

class MATCLASS matConcreteEx : public matConcrete
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   matConcreteEx();

   //------------------------------------------------------------------------
   matConcreteEx(const std::_tstring& name,Float64 fc,Float64 density,Float64 wDensity,Float64 modE,Float64 frShear,Float64 frFlexure);

   //------------------------------------------------------------------------
   // Copy constructor
   matConcreteEx(const matConcreteEx& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~matConcreteEx();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   matConcreteEx& operator = (const matConcreteEx& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual matConcrete* CreateClone(bool bRegisterListeners = false) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetDensityForWeight(Float64 d);

   //------------------------------------------------------------------------
   Float64 GetDensityForWeight() const;

   void SetShearFr(Float64 fr);
   Float64 GetShearFr() const;
   void SetFlexureFr(Float64 fr);
   Float64 GetFlexureFr() const;

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
   void MakeCopy(const matConcreteEx& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const matConcreteEx& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_WeightDensity;
   Float64 m_FrShear;
   Float64 m_FrFlexure;

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

#endif // INCLUDED_MATERIAL_CONCRETEEX_H_
