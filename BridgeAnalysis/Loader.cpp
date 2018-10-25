///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2011  Washington State Department of Transportation
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
// NAME:          bamLoader           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <BridgeAnalysis\Loader.h>
#include <BridgeAnalysis\Load.h>
#include <BridgeAnalysis\BridgeModel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

bamLoader::bamLoader(bamBridgeModel* pModel,bamLoad* pLoad)
{
   m_pModel = pModel;
   m_pLoad = pLoad;
} // bamLoader

bamLoader::~bamLoader()
{
} // ~bamLoader

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void bamLoader::ApplyLoad()
{
   switch (m_pLoad->GetElementType())
   {
   case etSupport:
        ApplyToSupportElement();
        break;

   case etSpan:
        ApplyToSpanElement();
        break;
   }
}
   
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
bamSpanElement* bamLoader::GetSpanElement(SpanIDType spanElementId)
{
   return m_pModel->GetSpanElement(spanElementId);
} // GetSpanElement

bamSupportElement* bamLoader::GetSupportElement(SupportIDType supportElementId)
{
   return m_pModel->GetSupportElement(supportElementId);
} // GetSupportElement

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY ==========================================
