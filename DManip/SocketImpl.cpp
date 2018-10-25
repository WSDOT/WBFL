///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

// SocketImpl.cpp: implementation of the CSocketImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "SocketImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DWORD CSocketImpl::ms_dwCookies = 1;

CSocketImpl::CSocketImpl():
m_pConnectable(0)
{
}

CSocketImpl::~CSocketImpl()
{
}

HRESULT CSocketImpl::FinalConstruct()
{
   m_ID = -1;
   return m_Position.CoCreateInstance(CLSID_Point2d);
}

STDMETHODIMP_(void) CSocketImpl::SetID(IDType id)
{
   m_ID = id;
}

STDMETHODIMP_(IDType) CSocketImpl::GetID()
{
   return m_ID;
}

STDMETHODIMP_(void) CSocketImpl::SetPosition(IPoint2d* pos)
{
   Float64 x,y;
   pos->get_X(&x);
   pos->get_Y(&y);

   m_Position->put_X(x);
   m_Position->put_Y(y);

   PlugContainer::iterator iter;
   for ( iter = m_Plugs.begin(); iter != m_Plugs.end(); iter++ )
   {
      iPlug* plug = (*iter).second;
      plug->Notify(this);
   }
   
}

STDMETHODIMP_(void) CSocketImpl::GetPosition(IPoint2d* *pos)
{
   CComPtr<IPoint2d> position;
   position.CoCreateInstance(CLSID_Point2d);
   
   Float64 x,y;
   m_Position->get_X(&x);
   m_Position->get_Y(&y);

   position->put_X(x);
   position->put_Y(y);

   (*pos) = position;
   (*pos)->AddRef();
}

STDMETHODIMP_(void) CSocketImpl::Move(ISize2d* offset)
{
   m_Position->OffsetEx(offset);

   PlugContainer::iterator iter;
   for ( iter = m_Plugs.begin(); iter != m_Plugs.end(); iter++ )
   {
      iPlug* plug = (*iter).second;
      plug->Notify(this);
   }
}

STDMETHODIMP_(void) CSocketImpl::Connect(iPlug* plug,DWORD* pdwCookie)
{
   *pdwCookie = ms_dwCookies++;
   plug->SetSocket(this);
   m_Plugs.insert(PlugContainer::value_type(*pdwCookie,plug));
}

STDMETHODIMP_(void) CSocketImpl::Disconnect(DWORD dwCookie)
{
   PlugContainer::iterator found;
   found = m_Plugs.find(dwCookie);

   if ( found != m_Plugs.end() )
   {
      iPlug* pPlug = (*found).second;
      pPlug->SetSocket(NULL);
      m_Plugs.erase(found);
   }
}

STDMETHODIMP_(void) CSocketImpl::DisconnectAll()
{
   PlugContainer::iterator iter;
   for ( iter = m_Plugs.begin(); iter != m_Plugs.end(); iter++ )
   {
      iPlug* pPlug = (*iter).second;
      pPlug->SetSocket(NULL);
   }

   m_Plugs.clear();
}

STDMETHODIMP_(void) CSocketImpl::Draw(CDC* pDC,iCoordinateMap* pMap)
{
   CPen red(PS_SOLID,1,RGB(255,0,0));

   CPoint pos;
   pMap->WPtoLP(m_Position,&pos.x,&pos.y);
   CRect r(pos,pos);

   r.InflateRect(1,1,1,1);
   CPen* oldPen = pDC->SelectObject(&red);
   pDC->Ellipse(r);
   pDC->SelectObject(oldPen);
}

STDMETHODIMP_(void) CSocketImpl::SetConnectable(iConnectable* pConnectable)
{
   m_pConnectable = pConnectable;
}

STDMETHODIMP_(void) CSocketImpl::GetConnectable(iConnectable** connectable)
{
   *connectable = m_pConnectable;
   if (m_pConnectable!=NULL)
      (*connectable)->AddRef();
}
