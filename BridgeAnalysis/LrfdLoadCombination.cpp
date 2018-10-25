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
   bamLrfdLoadCombination
****************************************************************************/

#include <BridgeAnalysis\LrfdLoadCombination.h>        // class implementation
#include <BridgeAnalysis\BridgeModel.h>
#include <Lrfd\LimitStateCalculator.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bamLrfdLoadCombination::bamLrfdLoadCombination(Int32 id,
                                               lrfdTypes::LimitState ls,
                                               bamOptimumType type,
                                               bamOptimumVariable variable) :
bamLoadCombination(id)
{
   m_LimitState = ls;
   m_Type       = type;
   m_Variable   = variable;

   m_gFx = 1.0;
   m_gFy = 1.0;
   m_gMz = 1.0;
   m_gDx = 1.0;
   m_gDy = 1.0;
   m_gRz = 1.0;

   m_lcidDC = -1;
   m_lcidDW = -1;
   m_lcidLLIM = -1;
}

bamLrfdLoadCombination::bamLrfdLoadCombination(const bamLrfdLoadCombination& rOther) :
bamLoadCombination(rOther)
{
   m_LimitState = rOther.m_LimitState;
   m_Type       = rOther.m_Type;
   m_Variable   = rOther.m_Variable;

   m_gFx = rOther.m_gFx;
   m_gFy = rOther.m_gFy;
   m_gMz = rOther.m_gMz;
   m_gDx = rOther.m_gDx;
   m_gDy = rOther.m_gDy;
   m_gRz = rOther.m_gRz;

   m_lcidDC = rOther.m_lcidDC;
   m_lcidDW = rOther.m_lcidDW;
   m_lcidLLIM = rOther.m_lcidLLIM;

   m_LoadModifier = rOther.m_LoadModifier;
}

bamLrfdLoadCombination::~bamLrfdLoadCombination()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
bamSectionResults bamLrfdLoadCombination::CombineSectionResults( Int32 poiId )
{
   bamBridgeModel* pBridge = &GetBridgeModel();
   bamAnalysisResultsManager* pArm = pBridge->GetAnalysisResultsManager();

   lrfdLimitStateCalculator lsc;
   lsc.SetLoadModifier( m_LoadModifier );

   if ( m_lcidDC >= 0 )
   {
      bamSectionResults dc = pArm->ReadSectionResults( bamSectionResultsKey(poiId, m_lcidDC) );
      lsc.SetDC( dc );
   }

   if ( m_lcidDW >= 0 )
   {
      bamSectionResults dw = pArm->ReadSectionResults( bamSectionResultsKey(poiId, m_lcidDW) );
      lsc.SetDW( dw );
   }

   if ( m_lcidLLIM >= 0 )
   {
      bamSectionResults llim = pArm->ReadSectionResults( bamSectionResultsKey(poiId,m_lcidLLIM) );
      lsc.SetLLIM( llim );
   }

   lsc.SetLiveLoadDistFactors( m_gFx, m_gFy, m_gMz, m_gDx, m_gDy, m_gRz );

   lrfdTypes::Optimization opt;
   switch (m_Type)
   {
   case otMaximum:
      opt = lrfdTypes::Max;
      break;

   case otMinimum:
      opt =lrfdTypes::Min;
      break;
   }

   lrfdLimitStateCalculator::Action action;
   switch( m_Variable )
   {
   case ovFx:
      action = lrfdLimitStateCalculator::Fx;
      break;

   case ovFy:
      action = lrfdLimitStateCalculator::Fy;
      break;

   case ovMz:
      action = lrfdLimitStateCalculator::Mz;
      break;
   }

   bamSectionResults results = lsc.ComputeLimitState(m_LimitState,action,opt);

   return results;
}

bamSectionStress bamLrfdLoadCombination::CombineSectionStress( Int32 poiId, Int32 spIdx )
{
   bamBridgeModel* pBridge = &GetBridgeModel();
   bamAnalysisResultsManager* pArm = pBridge->GetAnalysisResultsManager();

   lrfdLimitStateCalculator lsc;
   lsc.SetLoadModifier( m_LoadModifier );

   if ( m_lcidDC >= 0 )
   {
      bamSectionStress fdc = pArm->ReadSectionStress( bamSectionStressKey(poiId, spIdx, m_lcidDC) );
      bamSectionResults dc;
      dc.Mz() = fdc.F();
      lsc.SetDC( dc );
   }

   if ( m_lcidDW >= 0 )
   {
      bamSectionStress fdw = pArm->ReadSectionStress( bamSectionStressKey(poiId, spIdx, m_lcidDW) );
      bamSectionResults dw;
      dw.Mz() = fdw.F();
      lsc.SetDW( dw );
   }

   if ( m_lcidLLIM >= 0 )
   {
      bamSectionStress fllim = pArm->ReadSectionStress( bamSectionStressKey(poiId, spIdx, m_lcidLLIM) );
      bamSectionResults llim;
      llim.Mz() = fllim.F();
      lsc.SetLLIM( llim );
   }

   lsc.SetLiveLoadDistFactors( m_gFx, m_gFy, m_gMz, m_gDx, m_gDy, m_gRz );

   lrfdTypes::Optimization opt;
   switch (m_Type)
   {
   case otMaximum:
      opt = lrfdTypes::Max;
      break;

   case otMinimum:
      opt =lrfdTypes::Min;
      break;
   }

   lrfdLimitStateCalculator::Action action;
   switch( m_Variable )
   {
   case ovFx:
      action = lrfdLimitStateCalculator::Fx;
      break;

   case ovFy:
      action = lrfdLimitStateCalculator::Fy;
      break;

   case ovMz:
      action = lrfdLimitStateCalculator::Mz;
      break;
   }

   bamSectionResults results = lsc.ComputeLimitState(m_LimitState,action,opt);
   bamSectionStress fresults = results.Mz();
   return fresults;
}

bamReaction bamLrfdLoadCombination::CombineReactions( Int32 supportId )
{
   bamBridgeModel* pBridge = &GetBridgeModel();
   bamAnalysisResultsManager* pArm = pBridge->GetAnalysisResultsManager();

   lrfdLimitStateCalculator lsc;
   lsc.SetLoadModifier( m_LoadModifier );

   if ( m_lcidDC >= 0 )
   {
      bamReaction rdc = pArm->ReadReaction( bamReactionKey(supportId, m_lcidDC) );
      bamSectionResults dc;
      dc.Fx() = rdc.Fx();
      dc.Fy() = rdc.Fy();
      dc.Mz() = rdc.Mz();
      dc.Dx() = rdc.Dx();
      dc.Dy() = rdc.Dy();
      dc.Mz() = rdc.Mz();
      lsc.SetDC( dc );
   }

   if ( m_lcidDW >= 0 )
   {
      bamReaction rdw = pArm->ReadReaction( bamReactionKey(supportId, m_lcidDW) );
      bamSectionResults dw;
      dw.Fx() = rdw.Fx();
      dw.Fy() = rdw.Fy();
      dw.Mz() = rdw.Mz();
      dw.Dx() = rdw.Dx();
      dw.Dy() = rdw.Dy();
      dw.Mz() = rdw.Mz();
      lsc.SetDW( dw );
   }

   if ( m_lcidLLIM >= 0 )
   {
      bamReaction rllim = pArm->ReadReaction( bamReactionKey(supportId,m_lcidLLIM) );
      bamSectionResults llim;
      llim.Fx() = rllim.Fx();
      llim.Fy() = rllim.Fy();
      llim.Mz() = rllim.Mz();
      llim.Dx() = rllim.Dx();
      llim.Dy() = rllim.Dy();
      llim.Mz() = rllim.Mz();
      lsc.SetLLIM( llim );
   }

   lsc.SetLiveLoadDistFactors( m_gFx, m_gFy, m_gMz, m_gDx, m_gDy, m_gRz );

   lrfdTypes::Optimization opt;
   switch (m_Type)
   {
   case otMaximum:
      opt = lrfdTypes::Max;
      break;

   case otMinimum:
      opt =lrfdTypes::Min;
      break;
   }

   lrfdLimitStateCalculator::Action action;
   switch( m_Variable )
   {
   case ovFx:
      action = lrfdLimitStateCalculator::Fx;
      break;

   case ovFy:
      action = lrfdLimitStateCalculator::Fy;
      break;

   case ovMz:
      action = lrfdLimitStateCalculator::Mz;
      break;
   }

   bamSectionResults results = lsc.ComputeLimitState(m_LimitState,action,opt);
   bamReaction reaction;
   reaction.Fx() = results.Fx().Left();
   reaction.Fy() = results.Fy().Left();
   reaction.Mz() = results.Mz().Left();
   reaction.Dx() = results.Dx().Left();
   reaction.Dy() = results.Dy().Left();
   reaction.Rz() = results.Rz().Left();

   return reaction;
}

void bamLrfdLoadCombination::SetDCLoading(Int32 lcid)
{
   m_lcidDC = lcid;
}

Int32 bamLrfdLoadCombination::GetDCLoading() const
{
   return m_lcidDC;
}

void bamLrfdLoadCombination::SetDWLoading(Int32 lcid)
{
   m_lcidDW = lcid;
}

Int32 bamLrfdLoadCombination::GetDWLoading() const
{
   return m_lcidDW;
}

void bamLrfdLoadCombination::SetLLIMLoading(Int32 lcid)
{
   m_lcidLLIM = lcid;
}

Int32 bamLrfdLoadCombination::GetLLIMLoading() const
{
   return m_lcidLLIM;
}

void bamLrfdLoadCombination::SetLiveLoadDistFactors(Float64 gFx,Float64 gFy,Float64 gMz,
                                                    Float64 gDx,Float64 gDy,Float64 gRz)
{
   m_gFx = gFx;
   m_gFy = gFy;
   m_gMz = gMz;
   m_gDx = gDx;
   m_gDy = gDy;
   m_gRz = gRz;
}

void bamLrfdLoadCombination::GetLiveLoadDistFactors(Float64* pgFx,Float64* pgFy,Float64* pgMz,
                                                    Float64* pgDx,Float64* pgDy,Float64* pgRz)
{
   *pgFx = m_gFx;
   *pgFy = m_gFy;
   *pgMz = m_gMz;
   *pgDx = m_gDx;
   *pgDy = m_gDy;
   *pgRz = m_gRz;
}

bamLoadCombination* bamLrfdLoadCombination::Clone() const
{
   bamLrfdLoadCombination* pClone = new bamLrfdLoadCombination( *this );
   return pClone;
}

void bamLrfdLoadCombination::SetLoadModifier(const lrfdLoadModifier& lm)
{
   m_LoadModifier = lm;
}

const lrfdLoadModifier& bamLrfdLoadCombination::GetLoadModifier() const
{
   return m_LoadModifier;
}

void bamLrfdLoadCombination::SetOptimizationType(bamOptimumType type)
{
   m_Type = type;
}

bamOptimumType bamLrfdLoadCombination::GetOptimizationType() const
{
   return m_Type;
}

void bamLrfdLoadCombination::SetOptimizationVariable(bamOptimumVariable variable)
{
   m_Variable = variable;
}

bamOptimumVariable bamLrfdLoadCombination::GetOptimizationVariable() const
{
   return m_Variable;
}

//======================== ACCESS     =======================================
void bamLrfdLoadCombination::GetLoadings(std::vector<Int32>& loadingIds) const
{
   loadingIds.clear();
   loadingIds.push_back( m_lcidDC );
   loadingIds.push_back( m_lcidDW );
   loadingIds.push_back( m_lcidLLIM );
}

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
//======================== INQUERY    =======================================

