///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2022  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_BRIDGEMODELIMP_H_
#define INCLUDED_BRIDGEANALYSIS_BRIDGEMODELIMP_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\BridgeModel.h>
#include <boost\shared_ptr.hpp>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class bamBridgeModelLoader;

// MISCELLANEOUS
//


class BAMCLASS bamBridgeModelImp : public bamBridgeModel
{
public:
   // LIFECYCLE

   // Method:      bamBridgeModelImp
   // Description: Default c'tor
   // Return:      N/A
   bamBridgeModelImp();

   // Method:      ~bamBridgeModelImp
   // Description: d'tor
   // Return:      N/A
   virtual ~bamBridgeModelImp(); 

   // OPERATORS
   // OPERATIONS
   // ACCESS
   // INQUIRY

protected:
   // DATA MEMBERS
   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   void AddBeam(rkRoarkBeam* beam);
   void AddReaction(Float64 P,PierIDType supportId);
   void FlushBeams();
   void FlushReactions();

   bamBridgeModel* DoClone() const;
   void DeepCopy(bamBridgeModel* pModel) const;

   virtual void DoCollectResults(PoiIDType poiId,bamSectionResults& results);
   virtual void DoCollectReactions(PierIDType supportId,bamReaction& reaction);

   bamLoadFactory* CreateLoadFactory();

   // ACCESS
   // INQUIRY

private:
   // DATA MEMBERS
   typedef std::vector<std::pair<SupportIDType,Float64> > ReactionContainer;
   typedef std::vector<boost::shared_ptr<rkRoarkBeam> > BeamContainer;
   typedef BeamContainer::iterator BeamIterator;

   #pragma warning (disable : 4251)
   BeamContainer m_Beams;
   ReactionContainer m_Reactions;

   // LIFECYCLE
   bamBridgeModelImp(const bamBridgeModelImp& /*rBridgeModel*/);               // Remove to enable copy

   // OPERATORS
   bamBridgeModelImp& operator = (const bamBridgeModelImp& /*rBridgeModel*/);  // Remove to enable assignment

   // OPERATIONS
   // ACCESS
   // INQUIRY

   friend bamBridgeModelLoader;
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEANALYSIS_BRIDGEMODELIMP_H_
