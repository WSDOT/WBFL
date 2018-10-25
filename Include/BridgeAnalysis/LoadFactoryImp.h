///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2012  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_LOADFACTORYIMP_H_
#define INCLUDED_BRIDGEANALYSIS_LOADFACTORYIMP_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\LoadFactory.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

class BAMCLASS bamLoadFactoryImp : public bamLoadFactory
{
public:
   // LIFECYCLE
   bamLoadFactoryImp(bamBridgeModel* pModel);
   virtual ~bamLoadFactoryImp();

   // OPERATORS
   // OPERATIONS
   // ACCESS
   // INQUIRY

protected:
   // DATA MEMBERS
   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   virtual bamLoad* DoCreateConcForceY(IDType elementId,
                                       bamElementType type,
                                       Float64 location,
                                       Float64 p,
                                       bool isFractional = false,
                                       bamLoadDirection direction = Local);

   virtual bamLoad* DoCreateUnifForceY(IDType elementId,
                                       bamElementType type,
                                       Float64 start,
                                       Float64 end,
                                       Float64 w,
                                       bool isFractional = false,
                                       bamLoadDirection direction = Local);

   virtual bamLoad* DoCreateConcMomentZ(IDType elementId,
                                        bamElementType type,
                                        Float64 location,
                                        Float64 m,
                                        bool isFractional = false);

   // ACCESS
   // INQUIRY

private:
   // DATA MEMBERS
   // LIFECYCLE
   bamLoadFactoryImp(const bamLoadFactoryImp& /*MyLoadFactory*/);               // Remove to enable copy

   // OPERATORS
   bamLoadFactoryImp& operator = (const bamLoadFactoryImp& /*MyLoadFactory*/);  // Remove to enable assignment

   // OPERATIONS
   // ACCESS
   // INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEANALYSIS_LOADFACTORYIMP_H_
