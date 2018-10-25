///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2016  Washington State Department of Transportation
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

/****************************************************************************
CLASS
   bamStagedLoadCombination
****************************************************************************/

#include <BridgeAnalysis\StagedLoadCombination.h>
#include <BridgeAnalysis\BridgeModel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bamStagedLoadCombination::bamStagedLoadCombination(Int32 id) :
bamLoadCombination(id)
{
}

bamStagedLoadCombination::bamStagedLoadCombination(const bamStagedLoadCombination& rOther) :
bamLoadCombination(rOther)
{
   MakeCopy(rOther);
}

bamStagedLoadCombination::~bamStagedLoadCombination()
{
}

//======================== OPERATORS  =======================================
bamStagedLoadCombination& bamStagedLoadCombination::operator= (const bamStagedLoadCombination& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void bamStagedLoadCombination::AddLoading(IDType loadingId)
{
   m_Loads.push_back( loadingId );
}

void bamStagedLoadCombination::AddModel(bamBridgeModel* pModel)
{
   m_Models.push_back( pModel );
}

bamSectionResults bamStagedLoadCombination::CombineSectionResults( PoiIDType poiId )
{
   bamBridgeModel* pMyModel = &GetBridgeModel();
   bamAnalysisResultsManager* pMyArm = pMyModel->GetAnalysisResultsManager();

   bamSectionResults results;

   std::vector<IDType>::iterator iter;
   for ( iter = m_Loads.begin(); iter < m_Loads.end(); iter++ )
   {
      IDType loadingId = *iter;
      results += pMyArm->ReadSectionResults( bamSectionResultsKey(poiId,loadingId) );

      std::vector<bamBridgeModel*>::iterator model_iter;
      for ( model_iter = m_Models.begin(); model_iter < m_Models.end(); model_iter++ )
      {
         bamBridgeModel* pModel = *model_iter;
         bamAnalysisResultsManager* pArm = pModel->GetAnalysisResultsManager();
         results += pArm->ReadSectionResults( bamSectionResultsKey(poiId,loadingId) );
      }
   }

   return results;
}

bamSectionStress bamStagedLoadCombination::CombineSectionStress( PoiIDType poiId, CollectionIndexType spIdx )
{
   bamBridgeModel* pMyModel = &GetBridgeModel();
   bamAnalysisResultsManager* pMyArm = pMyModel->GetAnalysisResultsManager();

   bamSectionStress results;

   std::vector<IDType>::iterator iter;
   for ( iter = m_Loads.begin(); iter < m_Loads.end(); iter++ )
   {
      IDType loadingId = *iter;
      results += pMyArm->ReadSectionStress( bamSectionStressKey(poiId,spIdx,loadingId) );

      std::vector<bamBridgeModel*>::iterator model_iter;
      for ( model_iter = m_Models.begin(); model_iter < m_Models.end(); model_iter++ )
      {
         bamBridgeModel* pModel = *model_iter;
         bamAnalysisResultsManager* pArm = pModel->GetAnalysisResultsManager();
         results += pArm->ReadSectionStress( bamSectionStressKey(poiId,spIdx,loadingId) );
      }
   }

   return results;
}

bamReaction bamStagedLoadCombination::CombineReactions( PierIDType supportId )
{
   bamBridgeModel* pMyModel = &GetBridgeModel();
   bamAnalysisResultsManager* pMyArm = pMyModel->GetAnalysisResultsManager();

   bamReaction results;

   std::vector<IDType>::iterator iter;
   for ( iter = m_Loads.begin(); iter < m_Loads.end(); iter++ )
   {
      IDType loadingId = *iter;
      results += pMyArm->ReadReaction( bamReactionKey(supportId,loadingId) );

      std::vector<bamBridgeModel*>::iterator model_iter;
      for ( model_iter = m_Models.begin(); model_iter < m_Models.end(); model_iter++ )
      {
         bamBridgeModel* pModel = *model_iter;
         bamAnalysisResultsManager* pArm = pModel->GetAnalysisResultsManager();
         results += pArm->ReadReaction( bamReactionKey(supportId,loadingId) );
      }
   }

   return results;
}

bamLoadCombination* bamStagedLoadCombination::Clone() const
{
   return new bamStagedLoadCombination(*this);
}

//======================== ACCESS     =======================================

void bamStagedLoadCombination::GetLoadings(std::vector<IDType>& loadingIds) const
{
   loadingIds = m_Loads;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamStagedLoadCombination::MakeCopy(const bamStagedLoadCombination& rOther)
{
   // Add copy code here...
   m_Loads  = rOther.m_Loads;
   m_Models = rOther.m_Models;
}

void bamStagedLoadCombination::MakeAssignment(const bamStagedLoadCombination& rOther)
{
//   bamLoadCombination::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bamStagedLoadCombination::AssertValid() const
{
//   return bamLoadCombination::AssertValid();
   return true;
}

void bamStagedLoadCombination::Dump(dbgDumpContext& os) const
{
//   bamLoadCombination::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool bamStagedLoadCombination::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bamStagedLoadCombination");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bamStagedLoadCombination");

   TESTME_EPILOG("StagedLoadCombination");
}
#endif // _UNITTEST
