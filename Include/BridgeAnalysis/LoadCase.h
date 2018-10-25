///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
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

#ifndef INCLUDED_BRIDGEANALYSIS_LOADCASE_H_
#define INCLUDED_BRIDGEANALYSIS_LOADCASE_H_
#pragma once

#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\Load.h>
#include <boost\shared_ptr.hpp>

// Forward Declarations
class bamBridgeModel;

class bamLoadCase
{
public:
   bamLoadCase(IDType id);
   virtual ~bamLoadCase();

   IDType GetID();

   CollectionIndexType AddLoad(bamLoad* pLoad);
   void RemoveLoad(CollectionIndexType loadIdx);

   virtual void Apply();
   virtual void Remove();

   CollectionIndexType GetLoadCount() const;

   void Enable();
   void Disable();
   bool IsEnabled() const;

   IDType GetID() const;

   bamBridgeModel& GetBridgeModel();

   bool operator == (const bamLoadCase& other) const;

   // The remaining portion of the interface if for the
   // Bridge Modeling Framework only. Do not call these functions
   // directly!!!

   void SetBridgeModel(bamBridgeModel* model);

   typedef std::vector<boost::shared_ptr<bamLoad> > LoadContainer;
   typedef LoadContainer::iterator LoadIterator;

private:
   IDType m_ID;
   bool m_Enabled;

   // :COMPILER: rab 11.17.96 : Supressed warning
   // :FILE: LoadCase.h
   // Warning C4251 has been suppressed.
   // not be exported.
   #pragma warning (disable : 4251)
   LoadContainer m_Loads;

   bamBridgeModel* m_pModel;

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

#endif // INCLUDED_BRIDGEANALYSIS_LOADCASE_H_