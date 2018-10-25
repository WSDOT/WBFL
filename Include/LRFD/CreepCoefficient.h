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

#ifndef INCLUDED_LRFD_CREEPCOEFFICIENT_H_
#define INCLUDED_LRFD_CREEPCOEFFICIENT_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <LRFD\LrfdExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdCreepCoefficient

   Computes the creep coefficient per Article 5.4.2.3.2


DESCRIPTION
   Computes the creep coefficient per Article 5.4.2.3.2


COPYRIGHT
   Copyright © 1997-1999
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 03.16.1999 : Created file
*****************************************************************************/

class LRFDCLASS lrfdCreepCoefficient
{
public:
   enum CuringMethod { Normal, Accelerated };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdCreepCoefficient();

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdCreepCoefficient(const lrfdCreepCoefficient& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdCreepCoefficient();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdCreepCoefficient& operator = (const lrfdCreepCoefficient& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   Float64 GetCreepCoefficient() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetRelHumidity(Float64 H);
   Float64 GetRelHumidity() const;

   void SetVolume(Float64 V);
   Float64 GetVolume() const;

   void SetSurfaceArea(Float64 S);
   Float64 GetSurfaceArea() const;

   void SetFc(Float64 fc);
   Float64 GetFc() const;

   void SetMaturity(Float64 t);
   Float64 GetMaturity() const;

   void SetInitialAge(Float64 ti);
   Float64 GetInitialAge() const;
   Float64 GetAdjustedInitialAge() const;

   void SetCuringMethod(CuringMethod method);
   CuringMethod GetCuringMethod() const;

   Float64 GetKc() const;
   Float64 GetKf() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const lrfdCreepCoefficient& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdCreepCoefficient& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_H;
   Float64 m_Fc;
   Float64 m_V;
   Float64 m_S;
   Float64 m_t;
   Float64 m_ti;
   CuringMethod m_CuringMethod;

   mutable Float64 m_tiAdjusted; // adjusted for curing method
   mutable Float64 m_Ct; // Creep factor
   mutable Float64 m_kc;
   mutable Float64 m_kf;
   mutable bool m_bUpdate; // True if a parameter has been changed and an update is required

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Update() const;

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

#endif // INCLUDED_LRFD_CREEPCOEFFICIENT_H_
