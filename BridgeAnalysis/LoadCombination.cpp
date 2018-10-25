///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2014  Washington State Department of Transportation
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
#include <BridgeAnalysis\LoadCombination.h>
#include <BridgeAnalysis\BridgeModel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bamLoadCombination::bamLoadCombination(IDType id)
{
   m_ID = id;
}

bamLoadCombination::bamLoadCombination(const bamLoadCombination& rOther)
{
   m_ID = rOther.m_ID;
}

bamLoadCombination::~bamLoadCombination()
{
}

void bamLoadCombination::SetBridgeModel(bamBridgeModel* pModel)
{
   m_pBridgeModel = pModel;
}

IDType bamLoadCombination::GetID() const
{
   return m_ID;
}

void bamLoadCombination::SetID(IDType id)
{
   m_ID = id;
}

bamBridgeModel& bamLoadCombination::GetBridgeModel() const
{
   return *m_pBridgeModel;
}
