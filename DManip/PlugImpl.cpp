///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright (C) 2008  Washington State Department of Transportation
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

// PlugImpl.cpp: implementation of the CPlugImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "PlugImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlugImpl::CPlugImpl()
{

}

CPlugImpl::~CPlugImpl()
{

}

STDMETHODIMP_(void) CPlugImpl::Notify(iSocket* socket)
{
   // Does nothing by default
   std::vector< iPlugEvents* >::iterator iter;
   for ( iter = m_EventSinks.begin(); iter != m_EventSinks.end(); iter++ )
   {
      iPlugEvents* sink = *iter;
      sink->Notify(this);
   }
}

STDMETHODIMP_(void) CPlugImpl::OnRemove(iSocket* socket)
{
   socket->Disconnect(m_dwCookie);
}

STDMETHODIMP_(void) CPlugImpl::SetSocket(iSocket* pSocket)
{
   m_pSocket = pSocket;
}

STDMETHODIMP_(void) CPlugImpl::GetSocket(iSocket** socket)
{
   (*socket) = m_pSocket;
   (*socket)->AddRef();
}

STDMETHODIMP_(void) CPlugImpl::Register(iPlugEvents* pEventSink)
{
#pragma Reminder("Use a connection point here!!!")
   m_EventSinks.push_back( pEventSink );
}
