///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_CREEPCOEFFICIENT2005_H_
#define INCLUDED_LRFD_CREEPCOEFFICIENT2005_H_
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
   lrfdCreepCoefficient2005

   Computes the creep coefficient per Article 5.4.2.3.2 


DESCRIPTION
   Computes the creep coefficient per Article 5.4.2.3.2
   Based on 2005 interim provisions (and perhaps later)


COPYRIGHT
   Copyright © 1997-1999
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 09.16.2005 : Created file
*****************************************************************************/

class LRFDCLASS lrfdCreepCoefficient2005
{
public:
   enum CuringMethod { Normal, Accelerated };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdCreepCoefficient2005();

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdCreepCoefficient2005(const lrfdCreepCoefficient2005& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdCreepCoefficient2005();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdCreepCoefficient2005& operator = (const lrfdCreepCoefficient2005& rOther);

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

   void SetCuringMethodTimeAdjustmentFactor(Float64 f);
   Float64 GetCuringMethodTimeAdjustmentFactor() const;

   void SetK1(Float64 k1);
   Float64 GetK1() const;
   void SetK2(Float64 k2);
   Float64 GetK2() const;

   Float64 GetKvs() const;
   Float64 GetKhc() const;
   Float64 GetKf() const;
   Float64 GetKtd() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const lrfdCreepCoefficient2005& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const lrfdCreepCoefficient2005& rOther);

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
   Float64 m_CuringMethodTimeAdjustmentFactor;
   Float64 m_K1;
   Float64 m_K2;

   mutable Float64 m_tiAdjusted; // adjusted for curing method
   mutable Float64 m_Ct; // Creep factor
   mutable Float64 m_kvs; // volume-surface ratio factor
   mutable Float64 m_khc; // humidity factor
   mutable Float64 m_kf;  // concrete strength factor
   mutable Float64 m_ktd; // time factor

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

#endif // INCLUDED_LRFD_CREEPCOEFFICIENT2005_H_
