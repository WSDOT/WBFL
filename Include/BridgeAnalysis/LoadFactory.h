///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
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

#ifndef INCLUDED_BRIDGEANALYSIS_LOADFACTORY_H_
#define INCLUDED_BRIDGEANALYSIS_LOADFACTORY_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

class bamLoad;
class bamSpanElement;
class bamSupportElement;
class bamBridgeModel;

// MISCELLANEOUS
//

class BAMCLASS bamLoadFactory
{
public:
   // LIFECYCLE
   //------------------------------------------------------------------------
   bamLoadFactory(bamBridgeModel* m_pModel);

   //------------------------------------------------------------------------
   virtual ~bamLoadFactory();

   // OPERATORS
   // OPERATIONS

   //------------------------------------------------------------------------
   // Method:      CreateConcForceY
   // Description: Creates a concentrated force in the Y direction
   // Return:      Id of the load
   CollectionIndexType CreateConcForceY(IDType loadCaseId,                  // load case id to which to add this load
                         IDType elementId,                   // element id where this load will be applied
                         bamElementType type,               // the element type
                         Float64 location,                  // location of the load measured from the start of the element
                         Float64 p,                         // magnitude of the load 
                         bool isFractional = false,        // fractional measure flag
                         bamLoadDirection direction = Local); // direction of Y

   //------------------------------------------------------------------------
   // Method:      CreateUnifForceY
   // Description: Creates a uniform force in the Y direction
   // Return:      Id of the load
   CollectionIndexType CreateUnifForceY(IDType loadCaseId,
                         IDType elementId,
                         bamElementType type,
                         Float64 start,
                         Float64 end,
                         Float64 w,
                         bool isFractional = false,
                         bamLoadDirection direction = Local);

   //------------------------------------------------------------------------
   // Method:      CreateConcMomentZ
   // Description: Creates a concentrated moment about the Z axis
   // Return:      Id of the load
   CollectionIndexType CreateConcMomentZ(IDType loadCaseId,                  // load case id to which to add this load
                           IDType elementId,                   // element id where this load will be applied
                           bamElementType type,               // the element type
                           Float64 location,                  // location of the load measured from the start of the element
                           Float64 m,                         // magnitude of the load 
                           bool isFractional = false);        // fractional measure flag

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
                                      bamLoadDirection direction = Local) = 0;
   virtual bamLoad* DoCreateUnifForceY(IDType elementId,
                                      bamElementType type,
                                      Float64 start,
                                      Float64 end,
                                      Float64 w,
                                      bool isFractional = false,
                                      bamLoadDirection direction = Local) = 0;
   virtual bamLoad* DoCreateConcMomentZ(IDType elementId,
                                        bamElementType type,
                                        Float64 location,
                                        Float64 m,
                                        bool isFractional = false) = 0;

   // ACCESS
   // INQUIRY

private:
   // DATA MEMBERS
   bamBridgeModel* m_pModel;

   // LIFECYCLE
   bamLoadFactory(const bamLoadFactory& /*LoadFactory*/);

   // OPERATORS
   bamLoadFactory& operator = (const bamLoadFactory& /*LoadFactory*/);

   // OPERATIONS
   // ACCESS
   // INQUIRY

   friend bamSpanElement; // Need to call DoCreate for self-weight
   friend bamSupportElement; // Need to call DoCreate for self-weight
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEANALYSIS_LOADFACTORY_H_
