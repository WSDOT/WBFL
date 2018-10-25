///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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
#include <EAF\EAFBrokerReportSpecification.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEAFBrokerReportSpecification::CEAFBrokerReportSpecification(LPCTSTR strReportName,IBroker* pBroker) :
CReportSpecification(strReportName)
{
   SetBroker(pBroker);
}

CEAFBrokerReportSpecification::~CEAFBrokerReportSpecification(void)
{
}

void CEAFBrokerReportSpecification::SetBroker(IBroker* pBroker)
{
   m_pBroker = pBroker;
}

HRESULT CEAFBrokerReportSpecification::GetBroker(IBroker** ppBroker)
{
   ATLASSERT( m_pBroker ); // did you forget to set the broker???
   //return m_Broker.CopyTo(ppBroker);
   (*ppBroker) = m_pBroker;
   (*ppBroker)->AddRef();
   return S_OK;
}

HRESULT CEAFBrokerReportSpecification::Validate() const
{
   if ( !m_pBroker )
      return E_FAIL;

   return CReportSpecification::Validate();
}