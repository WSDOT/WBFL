// ConnectableImpl.cpp: implementation of the CConnectableImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <DManip\DManip.h>
#include "ConnectableImpl.h"
#include "SocketFactoryImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConnectableImpl::CConnectableImpl()
{
   CComObject<CSocketFactoryImpl>* pFactory;
   CComObject<CSocketFactoryImpl>::CreateInstance(&pFactory);
   m_pSocketFactory = pFactory;
}

CConnectableImpl::~CConnectableImpl()
{
}

STDMETHODIMP_(void) CConnectableImpl::SetSocketFactory(iSocketFactory* factory)
{
   m_pSocketFactory = factory;
}

STDMETHODIMP_(iSocketFactory*) CConnectableImpl::GetSocketFactory()
{
   return m_pSocketFactory;
}

STDMETHODIMP_(iSocket*) CConnectableImpl::AddSocket(WBFLGeometry::IPoint2dPtr pos)
{
   CComPtr<iSocket> pNewSocket = m_pSocketFactory->CreateSocket(pos);
   m_Sockets.push_back(pNewSocket);
   pNewSocket->SetConnectable(this);
   return pNewSocket;
}

STDMETHODIMP_(iSocket*) CConnectableImpl::GetSocket(long idx)
{
   if ( idx < 0 || m_Sockets.size() <= idx )
      return NULL;

   return m_Sockets[idx];
}

STDMETHODIMP_(iSocket*) CConnectableImpl::FindSocket(WBFLGeometry::IRect2dPtr r)
{
   CComPtr<iSocket> pFoundSocket;
   SocketContainer::iterator iter;
   for ( iter = m_Sockets.begin(); iter != m_Sockets.end(); iter++ )
   {
      CComPtr<iSocket> pSocket = *iter;
      if ( r->ContainsPoint(pSocket->GetPosition()) == VARIANT_TRUE )
      {
         pFoundSocket = pSocket;
         break;
      }
   }

   return pFoundSocket;
}

STDMETHODIMP_(long) CConnectableImpl::GetSocketCount()
{
   return m_Sockets.size();
}

STDMETHODIMP_(void) CConnectableImpl::RemoveSocket(long idx)
{
   CComPtr<iSocket> pSocket = GetSocket(idx);
   if ( pSocket )
   {
      m_Sockets.erase(m_Sockets.begin() + idx);
   }
}

STDMETHODIMP_(void) CConnectableImpl::DrawSockets(CDC* pDC,iCoordinateMap* pMap)
{
   SocketContainer::iterator iter;
   for ( iter = m_Sockets.begin(); iter != m_Sockets.end(); iter++ )
   {
      CComPtr<iSocket> pSocket = *iter;
      pSocket->Draw(pDC,pMap);
   }
}

STDMETHODIMP_(void) CConnectableImpl::Connect(long idx,iPlug* plug,DWORD* pdwCookie)
{
   CComPtr<iSocket> pSocket = GetSocket(idx);
   if ( pSocket )
   {
      pSocket->Connect(plug,pdwCookie);
   }
}

STDMETHODIMP_(void) CConnectableImpl::Disconnect(long idx,DWORD dwCookie)
{
   CComPtr<iSocket> pSocket = GetSocket(idx);
   if ( pSocket )
      pSocket->Disconnect(dwCookie);
}
