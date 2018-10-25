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

#ifndef INCLUDED_BRIDGEANALYSIS_LRFDLOADCOMBINATION_H_
#define INCLUDED_BRIDGEANALYSIS_LRFDLOADCOMBINATION_H_
#pragma once

// SYSTEM INCLUDES
//
#include <map>

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\LoadCombination.h>
#include <Lrfd\LoadModifier.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bamLrfdLoadCombination

   Performs a optimal load combination on one of the degrees of freedom using
   the lrfd load factors.


DESCRIPTION
   Performs a optimal load combination on one of the degrees of freedom using
   the lrfd load factors.

LIMITATIONS
   Live load distribution factors are applied to all points of interest.  In
   reality,  different distribution factors would be applied at each point
   of interest.

   Additionally,  the same live load distribution factors are applied to
   reactions as are applied to the points of interest.  Again,  different
   distribution factors should be used.

   These limitations are due to the fact that we need to deliver PGSuper
   very soon. By taking a few short cuts, we get exactly what we need and
   but not the ultimate solution we would like to have.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 08.14.1997 : Created file
*****************************************************************************/

class BAMCLASS bamLrfdLoadCombination : public bamLoadCombination
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bamLrfdLoadCombination(IDType id,
                          lrfdTypes::LimitState ls,
                          bamOptimumType type = otMaximum,
                          bamOptimumVariable variable = ovMz );

   //------------------------------------------------------------------------
   bamLrfdLoadCombination(const bamLrfdLoadCombination& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bamLrfdLoadCombination();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual bamSectionResults CombineSectionResults( PoiIDType poiId );
   
   //------------------------------------------------------------------------
   virtual bamSectionStress CombineSectionStress( PoiIDType poiId, CollectionIndexType spIdx );
   
   //------------------------------------------------------------------------
   virtual bamReaction CombineReactions( SupportIDType supportId );

   //------------------------------------------------------------------------
   void SetDCLoading(IDType lcid);

   //------------------------------------------------------------------------
   IDType GetDCLoading() const;

   //------------------------------------------------------------------------
   void SetDWLoading(IDType lcid);

   //------------------------------------------------------------------------
   IDType GetDWLoading() const;

   //------------------------------------------------------------------------
   void SetLLIMLoading(IDType lcid);

   //------------------------------------------------------------------------
   IDType GetLLIMLoading() const;

   //------------------------------------------------------------------------
   void SetLiveLoadDistFactors(Float64 gFx,Float64 gFy,Float64 gMz,
                               Float64 gDx,Float64 gDy,Float64 gRz);

   //------------------------------------------------------------------------
   void GetLiveLoadDistFactors(Float64* pgFx,Float64* pgFy,Float64* pgMz,
                               Float64* pgDx,Float64* pgDy,Float64* pgRz);

   //------------------------------------------------------------------------
   virtual bamLoadCombination* Clone() const;

   //------------------------------------------------------------------------
   void SetLoadModifier(const lrfdLoadModifier& lm);

   //------------------------------------------------------------------------
   const lrfdLoadModifier& GetLoadModifier() const;

   //------------------------------------------------------------------------
   void SetOptimizationType(bamOptimumType type);

   //------------------------------------------------------------------------
   bamOptimumType GetOptimizationType() const;

   //------------------------------------------------------------------------
   void SetOptimizationVariable(bamOptimumVariable variable);

   //------------------------------------------------------------------------
   bamOptimumVariable GetOptimizationVariable() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   virtual void GetLoadings(std::vector<IDType>& loadingIds) const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   lrfdTypes::LimitState m_LimitState;
   bamOptimumType m_Type;
   bamOptimumVariable m_Variable;

   Float64 m_gFx;
   Float64 m_gFy;
   Float64 m_gMz;
   Float64 m_gDx;
   Float64 m_gDy;
   Float64 m_gRz;

   IDType m_lcidDC;
   IDType m_lcidDW;
   IDType m_lcidLLIM;

   lrfdLoadModifier m_LoadModifier;

   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   bamLrfdLoadCombination& operator=(const bamLrfdLoadCombination&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEANALYSIS_LRFDLOADCOMBINATION_H_

