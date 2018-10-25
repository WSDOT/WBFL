///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
/****************************************************************************
CLASS
   bamOptimumLoadCombination
****************************************************************************/

#include <BridgeAnalysis\OptimumLoadCombination.h>        // class implementation
#include <BridgeAnalysis\BridgeModel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bamOptimumLoadCombination::bamOptimumLoadCombination(Int32 id,
                                                     bamOptimumType type,
                                                     bamOptimumVariable variable) :
bamLoadCombination(id)
{
   m_Type       = type;
   m_Variable   = variable;
   m_Multiplier = 1.0;
}

bamOptimumLoadCombination::bamOptimumLoadCombination(const bamOptimumLoadCombination& rOther) :
bamLoadCombination(rOther)
{
   m_Type       = rOther.m_Type;
   m_Variable   = rOther.m_Variable;
   m_Multiplier = rOther.m_Multiplier;
}

bamOptimumLoadCombination::~bamOptimumLoadCombination()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
#define _MinFactor(a) ( (a).first )
#define _MaxFactor(a) ( (a).second )

bamSectionResults bamOptimumLoadCombination::CombineSectionResults( Int32 poiId )
{
   bamSectionResults combined_results;

   LoadEntryIterator begin = m_LoadEntries.begin();
   LoadEntryIterator end   = m_LoadEntries.end();

   while ( begin != end )
   {
      bamSectionResults current_results;
      Int32 loadingId = (*begin).first;
      LoadFactors loadFactors = (*begin++).second;

      current_results = GetSectionResults( bamSectionResultsKey( poiId, loadingId ) );

      // Determine the load factor
      sysSectionValue factor;
      sysSectionValue design_variable;
      switch( m_Variable )
      {
         case ovFx:
              design_variable = current_results.Fx();
              break;

         case ovFy:
              design_variable = current_results.Fy();
              break;

         case ovMz:
              design_variable = current_results.Mz();
              break;
      }

      if ( design_variable.Left() < 0 )
         factor.Left() = ( m_Type == otMinimum ) ? _MaxFactor(loadFactors) : _MinFactor(loadFactors);
      else
         factor.Left() = ( m_Type == otMinimum ) ? _MinFactor(loadFactors) : _MaxFactor(loadFactors);

      if ( design_variable.Right() < 0 )
         factor.Right() = ( m_Type == otMinimum ) ? _MaxFactor(loadFactors) : _MinFactor(loadFactors);
      else
         factor.Right() = ( m_Type == otMinimum ) ? _MinFactor(loadFactors) : _MaxFactor(loadFactors);

      combined_results += factor * current_results;
   }

   // We need to keep track of whether or not we are minimizing or
   // maximizing and use a GetMultiplier() method to get the multiplier.
   // In LRFD, the multiplier depends upon how the factors are being used.
   combined_results *= m_Multiplier;

   return combined_results;
}

bamSectionStress bamOptimumLoadCombination::CombineSectionStress( Int32 poiId, Int32 spIdx )
{
   bamSectionStress combined_results;

   LoadEntryIterator begin = m_LoadEntries.begin();
   LoadEntryIterator end   = m_LoadEntries.end();

   while ( begin != end )
   {
      bamSectionStress current_results;
      Int32 loadingId = (*begin).first;
      LoadFactors loadFactors = (*begin++).second;

      current_results = GetSectionStress( bamSectionStressKey( poiId, spIdx, loadingId ) );

      // Determine the load factor
      sysSectionValue factor;
      sysSectionValue design_variable = current_results.F();

      if ( design_variable.Left() < 0 )
         factor.Left() = ( m_Type == otMinimum ) ? _MaxFactor(loadFactors) : _MinFactor(loadFactors);
      else
         factor.Left() = ( m_Type == otMinimum ) ? _MinFactor(loadFactors) : _MaxFactor(loadFactors);

      if ( design_variable.Right() < 0 )
         factor.Right() = ( m_Type == otMinimum ) ? _MaxFactor(loadFactors) : _MinFactor(loadFactors);
      else
         factor.Right() = ( m_Type == otMinimum ) ? _MinFactor(loadFactors) : _MaxFactor(loadFactors);

      combined_results += factor * current_results;
   }

   // We need to keep track of whether or not we are minimizing or
   // maximizing and use a GetMultiplier() method to get the multiplier.
   // In LRFD, the multiplier depends upon how the factors are being used.
   combined_results *= m_Multiplier;

   return combined_results;
}

bamReaction bamOptimumLoadCombination::CombineReactions( Int32 supportId )
{
   bamReaction combo_reaction;

   LoadEntryIterator begin = m_LoadEntries.begin();
   LoadEntryIterator end   = m_LoadEntries.end();

   while ( begin != end )
   {
      bamReaction current_reaction;
      Int32 loadingId = (*begin).first;
      LoadFactors loadFactors = (*begin++).second;

      current_reaction = GetReaction( bamReactionKey(supportId,loadingId) );

      // Determine the load factor
      Float64 factor;
      Float64 design_variable;
      switch( m_Variable )
      {
         case ovFx:
              design_variable = current_reaction.Fx();
              break;

         case ovFy:
              design_variable = current_reaction.Fy();
              break;

         case ovMz:
              design_variable = current_reaction.Mz();
              break;
      }

      if ( design_variable < 0 )
         factor = ( m_Type == otMinimum ) ? _MaxFactor(loadFactors) : _MinFactor(loadFactors);
      else
         factor = ( m_Type == otMinimum ) ? _MinFactor(loadFactors) : _MaxFactor(loadFactors);

      combo_reaction += factor * current_reaction;
   }

   // We need to keep track of whether or not we are minimizing or
   // maximizing and use a GetMultiplier() method to get the multiplier.
   // In LRFD, the multiplier depends upon how the factors are being used.
   combo_reaction *= m_Multiplier;

   return combo_reaction;
}

bamLoadCombination* bamOptimumLoadCombination::Clone() const
{
   bamOptimumLoadCombination* pClone = new bamOptimumLoadCombination( *this );
   return pClone;
}

void bamOptimumLoadCombination::SetMultiplier(Float64 multiplier)
{
   m_Multiplier = multiplier;
}

Float64 bamOptimumLoadCombination::GetMultiplier() const
{
   return m_Multiplier;
}

void bamOptimumLoadCombination::AddLoading(Int32 loadingId,Float64 minFactor,Float64 maxFactor)
{
   m_LoadEntries.insert( LoadEntry( loadingId, LoadFactors(minFactor,maxFactor) ) );
}

void bamOptimumLoadCombination::SetOptimizationType(bamOptimumType type)
{
   m_Type = type;
}

bamOptimumType bamOptimumLoadCombination::GetOptimizationType() const
{
   return m_Type;
}

void bamOptimumLoadCombination::SetOptimizationVariable(bamOptimumVariable variable)
{
   m_Variable = variable;
}

bamOptimumVariable bamOptimumLoadCombination::GetOptimizationVariable() const
{
   return m_Variable;
}

//======================== ACCESS     =======================================
void bamOptimumLoadCombination::GetLoadings(std::vector<Int32>& loadingIds) const
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
bamSectionResults bamOptimumLoadCombination::GetSectionResults(const bamSectionResultsKey& key)
{
   return GetBridgeModel().ReadSectionResults( key );
}

bamSectionStress bamOptimumLoadCombination::GetSectionStress(const bamSectionStressKey& key)
{
   return GetBridgeModel().ReadSectionStress( key );
}

bamReaction bamOptimumLoadCombination::GetReaction(const bamReactionKey& key)
{
   return GetBridgeModel().ReadReaction( key );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

