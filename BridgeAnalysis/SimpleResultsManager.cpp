///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2010  Washington State Department of Transportation
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
// NAME:          bamSimpleResultsManager           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <BridgeAnalysis\SimpleResultsManager.h>  // class implementation
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

bamSimpleResultsManager::bamSimpleResultsManager() :
bamAnalysisResultsManager()
{
} // bamSimpleResultsManager


bamSimpleResultsManager::~bamSimpleResultsManager()
{
} // ~bamSimpleResultsManager

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamSimpleResultsManager::CreateStorage(Int32 loadingId)
{
   // Does nothing by default
}

void bamSimpleResultsManager::DestroyStorage(Int32 loadingId)
{
   // Does nothing by default
}

bamSectionResults bamSimpleResultsManager::ReadSectionResults(const bamSectionResultsKey& key) const
{
   ConstSectionResultsIterator found = m_SectionResults.find( key );
   CHECK( found != m_SectionResults.end() );
   return (*found).second;
}

void bamSimpleResultsManager::WriteSectionResults(const bamSectionResultsKey& key,const bamSectionResults& sr)
{
   m_SectionResults.insert( SectionResultEntry( key, sr ) );
}

bamReaction bamSimpleResultsManager::ReadReaction(const bamReactionKey& key) const
{
   ConstReactionIterator found = m_Reactions.find( key );
   CHECK( found != m_Reactions.end() );
   return (*found).second;
}

void bamSimpleResultsManager::WriteReaction(const bamReactionKey& key,const bamReaction& reaction)
{
   m_Reactions.insert( ReactionEntry( key, reaction ) );
}

void bamSimpleResultsManager::WriteSectionStress(const bamSectionStressKey& key,const bamSectionStress& s)
{
   m_SectionStresses.insert( SectionStressEntry( key, s ) );
}

bamSectionStress bamSimpleResultsManager::ReadSectionStress(const bamSectionStressKey& key) const
{
   ConstSectionStressIterator found = m_SectionStresses.find( key );
   CHECK( found != m_SectionStresses.end() );
   return (*found).second;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY ==========================================
