///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

// ConnectorImpl.cpp: implementation of the CConnectorImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "ConnectorImpl.h"
#include "PlugImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConnectorImpl::CConnectorImpl()
{
}

CConnectorImpl::~CConnectorImpl()
{
}

HRESULT CConnectorImpl::FinalConstruct()
{
   HRESULT hr;
   CComObject<CPlugImpl>* pStartPlug;
   hr = CComObject<CPlugImpl>::CreateInstance(&pStartPlug);
   if ( FAILED(hr)) 
      return hr;

   m_pStart = pStartPlug;

   CComObject<CPlugImpl>* pEndPlug;
   hr = CComObject<CPlugImpl>::CreateInstance(&pEndPlug);
   if ( FAILED(hr)) 
      return hr;

   m_pEnd = pEndPlug;

   m_pStart->Register(this);
   m_pEnd->Register(this);

   return S_OK;
}

STDMETHODIMP_(void) CConnectorImpl::GetStartPlug(iPlug** plug)
{
   *plug = m_pStart;
   (*plug)->AddRef();
}

STDMETHODIMP_(void) CConnectorImpl::GetEndPlug(iPlug** plug)
{
   *plug = m_pEnd;
   (*plug)->AddRef();
}

STDMETHODIMP_(void) CConnectorImpl::Notify(iPlug* plug)
{
   // Do nothing...
}
