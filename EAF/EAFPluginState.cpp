///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

#include "stdafx.h"
#include <EAF\EAFPluginState.h>

CEAFPluginState::CEAFPluginState(LPCTSTR lpszName,const CLSID& clsid,const CString& strCLSID,bool bInitiallyEnabled)
{
   m_Name = lpszName;
   m_CLSID = clsid;
   m_strCLSID = strCLSID;
   m_bInitiallyEnabled = bInitiallyEnabled;
   m_bNewState = m_bInitiallyEnabled;
}

bool CEAFPluginState::operator<(const CEAFPluginState& other)
{
   return m_Name < other.m_Name;
}

LPCTSTR CEAFPluginState::GetName() const
{
   return m_Name;
}

void CEAFPluginState::SetState(bool bNewState)
{
   m_bNewState = bNewState;
}

bool CEAFPluginState::InitiallyEnabled() const
{
   return m_bInitiallyEnabled;
}

bool CEAFPluginState::StateChanged() const
{
   return m_bInitiallyEnabled != m_bNewState ? true : false;
}

bool CEAFPluginState::IsEnabled() const
{
   if ( (InitiallyEnabled() && !StateChanged()) || (!InitiallyEnabled() && StateChanged()) )
      return true;

   return false;
}

CLSID CEAFPluginState::GetCLSID() const
{
   return m_CLSID;
}

CString CEAFPluginState::GetCLSIDString() const
{
   return m_strCLSID;
}

