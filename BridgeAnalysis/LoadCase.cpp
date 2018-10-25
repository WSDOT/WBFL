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
#include <BridgeAnalysis\LoadCase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bamLoadCase::bamLoadCase(Int32 id)
{
   m_ID = id;
   m_Enabled = true;

   m_pModel = 0;
}

bamLoadCase::~bamLoadCase()
{
}

Int32 bamLoadCase::GetID()
{
   return m_ID;
}

Int32 bamLoadCase::AddLoad(bamLoad* pLoad)
{
   pLoad->SetLoadCase(this);
   m_Loads.push_back(boost::shared_ptr<bamLoad>(pLoad));

   return m_Loads.size() - 1;
}

void bamLoadCase::RemoveLoad(Int32 loadIdx)
{
   // Erase the load. All loads after that point will be moved
   // one position to the left.
   m_Loads.erase(m_Loads.begin() + loadIdx + 1);
}

void bamLoadCase::Apply()
{
   LoadIterator begin = m_Loads.begin();
   LoadIterator end   = m_Loads.end();
   while ( begin != end )
   {
      boost::shared_ptr<bamLoad>& load = *begin++;
      load->Apply();
   }
}

void bamLoadCase::Remove()
{
   LoadIterator begin = m_Loads.begin();
   LoadIterator end   = m_Loads.end();
   while ( begin != end )
   {
      boost::shared_ptr<bamLoad>& load = *begin++;
      load->Remove();
   }
}

Int32 bamLoadCase::GetLoadCount() const
{
   return m_Loads.size();
}

void bamLoadCase::Enable()
{
   m_Enabled = true;
}

void bamLoadCase::Disable()
{
   m_Enabled = false;
}

bool bamLoadCase::IsEnabled() const
{
   return m_Enabled;
}

Int32 bamLoadCase::GetID() const
{
   return m_ID;
}

bamBridgeModel& bamLoadCase::GetBridgeModel()
{
   return *m_pModel;
}

void bamLoadCase::SetBridgeModel(bamBridgeModel* model)
{
   m_pModel = model;
}

bool bamLoadCase::operator == (const bamLoadCase& other) const
{
   return m_ID == other.GetID();
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bamLoadCase::AssertValid() const
{
   LoadContainer::const_iterator iter;
   for ( iter = m_Loads.begin(); iter < m_Loads.end(); iter++ )
   {
      if ( (*iter)->AssertValid() == false )
         return false;
   }

   return true;
}

void bamLoadCase::Dump(dbgDumpContext& os) const
{
   os << "Dump for bamLoadCase" << endl;
   os << "m_ID = " << m_ID << endl;

   LoadContainer::const_iterator iter;
   for ( iter = m_Loads.begin(); iter < m_Loads.end(); iter++ )
   {
      (*iter)->Dump(os);
      os << endl;
   }
}
#endif // _DEBUG

#if defined _UNITTEST
bool bamLoadCase::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bamLoadCase");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bamLoadCase");

   TESTME_EPILOG("LoadCase");
}
#endif // _UNITTEST
