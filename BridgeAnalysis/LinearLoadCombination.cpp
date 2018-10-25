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

#include <BridgeAnalysis\BridgeAnalysisLib.h>
//////////////////X////////////////////X/////////////////////////////////////
// NAME:          bamLinearLoadCombination           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <BridgeAnalysis\LinearLoadCombination.h> // class implementation
#include <BridgeAnalysis\BridgeModel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

bamLinearLoadCombination::bamLinearLoadCombination(IDType id) :
bamLoadCombination(id)
{
   m_Multiplier = 1.0;
} // bamLinearLoadCombination

bamLinearLoadCombination::bamLinearLoadCombination(const bamLinearLoadCombination& rOther) :
bamLoadCombination( rOther )
{
   m_Multiplier = rOther.m_Multiplier;
   m_LoadEntries = rOther.m_LoadEntries;
}

bamLinearLoadCombination::~bamLinearLoadCombination()
{
} // ~bamLinearLoadCombination

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamLinearLoadCombination::AddLoading(IDType loadingId,Float64 loadFactor)
{
   m_LoadEntries.insert( std::pair<IDType,Float64>(loadingId,loadFactor) );
}

void bamLinearLoadCombination::SetMultiplier(Float64 multiplier)
{
   m_Multiplier = multiplier;
}

bamSectionResults bamLinearLoadCombination::CombineSectionResults( PoiIDType poiId )
{
   bamSectionResults combo_results;

   LoadEntryIterator begin = m_LoadEntries.begin();
   LoadEntryIterator end   = m_LoadEntries.end();

   while ( begin != end )
   {
      IDType loadingId = (*begin).first;
      sysSectionValue loadFactor = (*begin++).second;

      bamSectionResultsKey key( poiId, loadingId );
      bamSectionResults current_result = GetBridgeModel().ReadSectionResults( key );

      combo_results += loadFactor * current_result;
   }

   combo_results *= m_Multiplier;
   return combo_results;
}

bamSectionStress bamLinearLoadCombination::CombineSectionStress( PoiIDType poiId, CollectionIndexType spIdx )
{
   bamSectionStress sect_stress;
   LoadEntryIterator begin = m_LoadEntries.begin();
   LoadEntryIterator end   = m_LoadEntries.end();

   while ( begin != end )
   {
      IDType loadingId = (*begin).first;
      Float64 loadFactor = (*begin++).second;

      bamSectionStressKey key( poiId, spIdx, loadingId );
      bamSectionStress current_result = GetBridgeModel().ReadSectionStress( key );

      sect_stress += loadFactor * current_result;
   }

   sect_stress *= m_Multiplier;
   return sect_stress;
}

bamReaction bamLinearLoadCombination::CombineReactions( SupportIDType supportId )
{
   bamReaction combo_reactions;

   LoadEntryIterator begin = m_LoadEntries.begin();
   LoadEntryIterator end   = m_LoadEntries.end();

   while ( begin != end )
   {
      IDType loadingId = (*begin).first;
      Float64 loadFactor = (*begin++).second;

      bamReactionKey key( supportId, loadingId );
      bamReaction current_reaction = GetBridgeModel().ReadReaction( key );

      combo_reactions += loadFactor * current_reaction;
   }

   combo_reactions *= m_Multiplier;

   return combo_reactions;
}

//======================== ACCESS     =======================================
void bamLinearLoadCombination::GetLoadings(std::vector<IDType>& loadingIds) const
{
   ConstLoadEntryIterator i;
   for ( i = m_LoadEntries.begin(); i != m_LoadEntries.end(); i++ )
   {
      const LoadEntry& load_entry = *i;
      loadingIds.push_back( load_entry.first );
   }
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

bamLoadCombination* bamLinearLoadCombination::Clone() const
{
   bamLinearLoadCombination* pClone = new bamLinearLoadCombination(*this);
   return pClone;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY ==========================================
