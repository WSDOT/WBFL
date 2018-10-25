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
// NAME:          bamDeadLoadCase           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <BridgeAnalysis\DeadLoadCase.h>
#include <BridgeAnalysis\BridgeModel.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

bamDeadLoadCase::bamDeadLoadCase(Int32 loadCaseIdx) :
bamLoadCase(loadCaseIdx)
{
} // bamDeadLoadCase

bamDeadLoadCase::~bamDeadLoadCase()
{
} // ~bamDeadLoadCase

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamDeadLoadCase::Apply()
{
   bamLoadCase::Apply();
   Int32 element_count;
   Int32* element_list;

   element_count = GetBridgeModel().GetSpanElementCount();
   element_list = new Int32[element_count];
   GetBridgeModel().EnumSpanElements( &element_list, element_count );

   for (Int32 spanIdx = 0; spanIdx < element_count; spanIdx++)
   {
      // Skip this span if its id is in the exclusion list
      if ( std::find(m_ExcludedSpans.begin(),
                     m_ExcludedSpans.end(),
                     element_list[spanIdx]) != m_ExcludedSpans.end() )
         continue;

      bamLoad* pLoad;
      bamSpanElement* pSpanElement;

      pSpanElement = GetBridgeModel().GetSpanElement( element_list[spanIdx] );
      pLoad = pSpanElement->GetSelfWeightLoad();

      if ( pLoad != 0 )
      {
         pLoad->SetLoadCase( this );
		 m_PrivateLoads.push_back( boost::shared_ptr<bamLoad>(pLoad) );
         pLoad->Apply();
      }
   }
   delete[] element_list;

   element_count = GetBridgeModel().GetSupportElementCount();
   element_list = new Int32[element_count];
   GetBridgeModel().EnumSupportElements( &element_list, element_count );

   for (Int32 supportIdx = 0; supportIdx < element_count; supportIdx++)
   {
      bamLoad* pLoad;
      bamSupportElement* pSupportElement;

      // Skip this support if its id is in the exclusion list
      if ( std::find(m_ExcludedSupports.begin(),
                m_ExcludedSupports.end(),
                element_list[supportIdx]) != m_ExcludedSupports.end() )
         continue;

      pSupportElement = GetBridgeModel().GetSupportElement( element_list[supportIdx] );
      pLoad = pSupportElement->GetSelfWeightLoad();

      if ( pLoad != 0 )
      {
         pLoad->SetLoadCase( this );
		 m_PrivateLoads.push_back( boost::shared_ptr<bamLoad>(pLoad) );
         pLoad->Apply();
      }
   }

   delete[] element_list;
} // Apply

void bamDeadLoadCase::Remove()
{
   bamLoadCase::Remove();

   LoadIterator begin = m_PrivateLoads.begin();
   LoadIterator end   = m_PrivateLoads.end();
   while ( begin != end )
   {
      boost::shared_ptr<bamLoad>& pLoad = *begin++;
      pLoad->Remove();
   }

} // Remove

void bamDeadLoadCase::ExcludeSpan(Int32 spanElementId)
{
   m_ExcludedSpans.push_back( spanElementId );
}

void bamDeadLoadCase::ExcludeSupport(Int32 supportElementId)
{
   m_ExcludedSupports.push_back( supportElementId );
}

void bamDeadLoadCase::ExcludeSpans(Int32** ppSpans,Int32 count)
{
   for (Int32 idx = 0; idx < count; idx++)
   {
      m_ExcludedSpans.push_back( (*ppSpans)[idx] );
   }
} // ExcludeSpans

void bamDeadLoadCase::ExcludeSupports(Int32** ppSupports,Int32 count)
{
   for (Int32 idx = 0; idx < count; idx++)
   {
      m_ExcludedSupports.push_back( (*ppSupports)[idx] );
   }
} // ExcludeSupports

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

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bamDeadLoadCase::AssertValid() const
{
   return bamLoadCase::AssertValid();
}

void bamDeadLoadCase::Dump(dbgDumpContext& os) const
{
   os << "Dump for bamDeadLoadCase" << endl;
   bamLoadCase::Dump( os );

   std::vector<Int32>::const_iterator i;
   os << "Excluded Spans" << endl;
   for ( i = m_ExcludedSpans.begin(); i < m_ExcludedSpans.end(); i++ )
   {
      os << (*i) << endl;
   }

   os << endl;

   os << "Excluded Supports" << endl;
   for ( i = m_ExcludedSupports.begin(); i < m_ExcludedSupports.end(); i++ )
   {
      os << (*i) << endl;
   }

   os << endl;

   os << "Private Load Cases" << endl;
   LoadContainer::const_iterator iter;
   for ( iter = m_PrivateLoads.begin(); iter != m_PrivateLoads.end(); iter++ )
   {
      (*iter)->Dump(os);
      os << endl;
   }

}
#endif // _DEBUG

#if defined _UNITTEST
bool bamDeadLoadCase::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bamDeadLoadCase");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bamDeadLoadCase");

   TESTME_EPILOG("DeadLoadCase");
}
#endif // _UNITTEST
