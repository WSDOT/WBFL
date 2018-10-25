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
#include <BridgeAnalysis\LoaderImp.h>
#include <BridgeAnalysis\SpanElement.h>
#include <BridgeAnalysis\SupportElement.h>
#include <BridgeAnalysis\LoadCase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bamBridgeModelLoader::bamBridgeModelLoader(bamBridgeModelImp* pModel, bamLoad* pLoad) :
bamLoader(pModel, pLoad)
{
}

bamBridgeModelLoader::~bamBridgeModelLoader()
{
}

void bamBridgeModelLoader::RemoveLoad()
{
   GetBridgeModel()->FlushBeams();
   GetBridgeModel()->FlushReactions();
}

bamBridgeModelImp* bamBridgeModelLoader::GetBridgeModel()
{
   return (bamBridgeModelImp*)m_pModel;
}

void bamBridgeModelLoader::AddBeam(rkRoarkBeam* pBeam)
{
   GetBridgeModel()->AddBeam(pBeam);
}

void bamBridgeModelLoader::AddReaction(Float64 P,Int32 supportId)
{
   GetBridgeModel()->AddReaction(P,supportId);
}

///////////////////////////////////////////////////////////////////////

bamConcForceYLoaderImp::bamConcForceYLoaderImp(bamBridgeModelImp* pModel,bamConcForceYImp* pLoad) :
bamBridgeModelLoader(pModel,pLoad)
{
   m_pMyLoad = pLoad;
}

void bamConcForceYLoaderImp::ApplyToSpanElement()
{
   Float64 w = m_pMyLoad->GetMagnitude();
   Float64 La = m_pMyLoad->GetLocation();
   bamSpanElement* pSpanElement = GetSpanElement(m_pMyLoad->GetElementId());
   Float64 l = pSpanElement->Length();
   Float64 i = pSpanElement->GetIz();
   Float64 e = pSpanElement->GetModE();

   // For this implementation, all three are the same!!!
   switch(m_pMyLoad->GetDirection())
   {
   case Local:  // drop down
   case Global: // drop down
   case GlobalProjected:
        La *= m_pMyLoad->IsFractional() ? l : 1.0;
        rkPPIntermediateLoad* beam = new rkPPIntermediateLoad(w,La,l,e,i);
        AddBeam(beam);
        break;
   }
}

void bamConcForceYLoaderImp::ApplyToSupportElement()
{
   AddReaction( m_pMyLoad->GetMagnitude(), m_pMyLoad->GetElementId() );
}


///////////////////////////////////////////////////////////////////////

bamUnifForceYLoaderImp::bamUnifForceYLoaderImp(bamBridgeModelImp* pModel,bamUnifForceYImp* pLoad) :
bamBridgeModelLoader(pModel,pLoad)
{
   m_pMyLoad = pLoad;
}

void bamUnifForceYLoaderImp::ApplyToSpanElement()
{
   Float64 w = m_pMyLoad->GetMagnitude();
   Float64 La = m_pMyLoad->GetStartLocation();
   Float64 Lb = m_pMyLoad->GetEndLocation();
   bamSpanElement* pSpanElement = GetSpanElement(m_pMyLoad->GetElementId());
   Float64 l = pSpanElement->Length();
   Float64 i = pSpanElement->GetIz();
   Float64 e = pSpanElement->GetModE();

   // For this implementation, all three are the same!!!
   switch(m_pMyLoad->GetDirection())
   {
   case Local:  // drop down
   case Global: // drop down
   case GlobalProjected:
        La *= m_pMyLoad->IsFractional() ? l : 1.0;
        Lb *= m_pMyLoad->IsFractional() ? l : 1.0;
        rkPPPartUniformLoad* beam = new rkPPPartUniformLoad(La,Lb,w,l,e,i);
        AddBeam(beam);
        break;
   }
}

void bamUnifForceYLoaderImp::ApplyToSupportElement()
{
   CHECKX( false, "Not yet supported");
}

///////////////////////////////////////////////////////////////////////

bamConcMomentZLoaderImp::bamConcMomentZLoaderImp(bamBridgeModelImp* pModel,bamConcMomentZImp* pLoad) :
bamBridgeModelLoader(pModel,pLoad)
{
   m_pMyLoad = pLoad;
}

void bamConcMomentZLoaderImp::ApplyToSpanElement()
{
   Float64 m = m_pMyLoad->GetMagnitude();
   Float64 La = m_pMyLoad->GetLocation();
   bamSpanElement* pSpanElement = GetSpanElement(m_pMyLoad->GetElementId());
   Float64 l = pSpanElement->Length();
   Float64 i = pSpanElement->GetIz();
   Float64 e = pSpanElement->GetModE();

   // For this implementation, all three are the same!!!
   switch(m_pMyLoad->GetDirection())
   {
   case Local:  // drop down
   case Global: // drop down
   case GlobalProjected:
        La *= m_pMyLoad->IsFractional() ? l : 1.0;
        rkPPIntermediateCouple* beam = new rkPPIntermediateCouple(m,La,l,e,i);
        AddBeam(beam);
        break;
   }
}

void bamConcMomentZLoaderImp::ApplyToSupportElement()
{
   AddReaction( m_pMyLoad->GetMagnitude(), m_pMyLoad->GetElementId() );
}

