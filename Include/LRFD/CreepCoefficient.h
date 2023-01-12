///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2023  Washington State Department of Transportation
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

LOG
   rab : 03.16.1999 : Created file
*****************************************************************************/

class LRFDCLASS lrfdCreepCoefficient
{
public:
   enum CuringMethod { Normal, Accelerated };

   lrfdCreepCoefficient();
   virtual ~lrfdCreepCoefficient();

   virtual Float64 GetCreepCoefficient(Float64 t, Float64 ti) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetRelHumidity(Float64 H);
   Float64 GetRelHumidity() const;

   void SetVolume(Float64 V);
   Float64 GetVolume() const;

   void SetSurfaceArea(Float64 S);
   Float64 GetSurfaceArea() const;

   void SetFci(Float64 fci);
   Float64 GetFci() const;

   virtual Float64 GetAdjustedInitialAge(Float64 ti) const;

   void SetCuringMethod(CuringMethod method);
   CuringMethod GetCuringMethod() const;

   void SetCuringMethodTimeAdjustmentFactor(Float64 f);
   Float64 GetCuringMethodTimeAdjustmentFactor() const;

   Float64 GetKf() const;
   virtual Float64 GetKtd(Float64 t) const;

   // GROUP: INQUIRY

protected:
   Float64 m_H;
   Float64 m_Fci;
   Float64 m_V;
   Float64 m_S;
   CuringMethod m_CuringMethod;
   Float64 m_CuringMethodTimeAdjustmentFactor;

   mutable Float64 m_kc;
   mutable Float64 m_kf;
   mutable bool m_bUpdate; // True if a parameter has been changed and an update is required

   virtual void Update() const;
   virtual Float64 ComputeKf() const;
   virtual Float64 ComputeKtd(Float64 t) const;

public:
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

#endif // INCLUDED_LRFD_CREEPCOEFFICIENT_H_
