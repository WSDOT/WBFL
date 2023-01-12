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

#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <LRFD\LrfdExp.h>
#include <LRFD\CreepCoefficient2005.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdPCIUHPCCreepCoefficient

   Computes the creep coefficient per PCI UHPC Structure Design Guidance 4.3.2
*****************************************************************************/

class LRFDCLASS lrfdPCIUHPCCreepCoefficient : public lrfdCreepCoefficient2005
{
public:
   lrfdPCIUHPCCreepCoefficient();
   virtual ~lrfdPCIUHPCCreepCoefficient();

   bool PostCureThermalTreatment() const { return m_bPCTT; }
   void PostCureThermalTreatment(bool bPCTT) { m_bPCTT = bPCTT; m_bUpdate = true; }

protected:
   virtual Float64 GetUltimateCreep() const override;
   virtual Float64 ComputeKvs() const override;
   virtual Float64 ComputeKhc() const override;
   virtual Float64 ComputeKf() const override;
   virtual Float64 ComputeKtd(Float64 t) const override;

private:
   bool m_bPCTT;

#if defined _UNITTEST
public:
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
};
