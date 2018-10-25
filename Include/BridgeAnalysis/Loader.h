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

#ifndef INCLUDED_BRIDGEANALYSIS_LOADER_H_
#define INCLUDED_BRIDGEANALYSIS_LOADER_H_
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

class bamBridgeModel;
class bamSpanElement;
class bamSupportElement;
class bamLoad;

// MISCELLANEOUS
//


class BAMCLASS bamLoader
{
public:
   // LIFECYCLE
   bamLoader(bamBridgeModel* pModel,bamLoad* pLoad);
   virtual ~bamLoader();

   // OPERATORS
   // OPERATIONS
   void ApplyLoad();
   virtual void RemoveLoad() = 0;

   // ACCESS
   // INQUIRY

protected:
   // DATA MEMBERS
   bamBridgeModel* m_pModel;
   bamLoad* m_pLoad;

   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   virtual void ApplyToSpanElement() = 0;
   virtual void ApplyToSupportElement() = 0;

   // ACCESS
   bamSpanElement* GetSpanElement(SpanIDType spanElementId);
   bamSupportElement* GetSupportElement(SupportIDType supportElementId);

   // INQUIRY

private:
   // DATA MEMBERS
   // LIFECYCLE
   bamLoader(const bamLoader& /*Loader*/);               // Remove to enable copy

   // OPERATORS
   bamLoader& operator = (const bamLoader& /*Loader*/);  // Remove to enable assignment

   // OPERATIONS
   // ACCESS
   // INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEANALYSIS_LOADER_H_
