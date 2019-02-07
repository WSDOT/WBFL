///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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

// ConnectableImpl.h: interface for the CConnectableImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTABLEIMPL_H__D88A0194_DCD4_11D4_8B74_006097C68A9C__INCLUDED_)
#define AFX_CONNECTABLEIMPL_H__D88A0194_DCD4_11D4_8B74_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include <vector>
#include "SocketFactoryImpl.h"

template <class T>
class ATL_NO_VTABLE CConnectableImpl : public iConnectable
{
public:
	CConnectableImpl()
   {
      CComObject<CSocketFactoryImpl>* pFactory;
      CComObject<CSocketFactoryImpl>::CreateInstance(&pFactory);
      m_pSocketFactory = pFactory;
   }

	virtual ~CConnectableImpl()
   {}
   
   // iConnectable
   STDMETHOD_(void,SetSocketFactory)(iSocketFactory* factory)
   {
      m_pSocketFactory = factory;
   }

   STDMETHOD_(void,GetSocketFactory)(iSocketFactory** factory)
   {
      (*factory) = m_pSocketFactory;
      (*factory)->AddRef();
   }

   STDMETHOD_(void,AddSocket)(IDType id,IPoint2d* pos,iSocket** socket)
   {
      CComPtr<iSocket> pNewSocket;
      m_pSocketFactory->CreateSocket(id,pos,&pNewSocket);
      m_Sockets.push_back(pNewSocket);
      pNewSocket->SetConnectable(this);

      (*socket) = pNewSocket;
      (*socket)->AddRef();
   }

   STDMETHOD_(void,GetSocket)(IDType key,AccessType access,iSocket** socket)
   {
      GetSocket_Private(key,access,socket);
   }

   STDMETHOD_(void,FindSocket)(IRect2d* r,iSocket** socket)
   {
      *socket = 0;

      SocketContainer::iterator iter;
      for ( iter = m_Sockets.begin(); iter != m_Sockets.end(); iter++ )
      {
         CComPtr<iSocket> pSocket = *iter;
         CComPtr<IPoint2d> socketPosition;
         pSocket->GetPosition(&socketPosition);
         VARIANT_BOOL bContainsPoint;
         r->ContainsPoint(socketPosition,&bContainsPoint);
         if ( bContainsPoint == VARIANT_TRUE )
         {
            (*socket) = pSocket;
            (*socket)->AddRef();
            return;
         }
      }
   }

   STDMETHOD_(CollectionIndexType,GetSocketCount)()
   {
      return m_Sockets.size();
   }

   STDMETHOD_(void,RemoveSocket)(IDType key,AccessType access)
   {
      CComPtr<iSocket> pSocket;
      SocketContainer::iterator iter = GetSocket_Private(key,access,&pSocket);
      if ( pSocket )
      {
         pSocket->DisconnectAll();
         m_Sockets.erase(iter);
      }
   }

   STDMETHOD_(void,RemoveAllSockets)()
   {
      SocketContainer::iterator iter;
      for ( iter = m_Sockets.begin(); iter != m_Sockets.end(); iter++ )
      {
         CComPtr<iSocket> socket = *iter;

         socket->DisconnectAll();
      }

      m_Sockets.clear();
   }

   STDMETHOD_(void,DrawSockets)(CDC* pDC,iCoordinateMap* pMap)
   {
      SocketContainer::iterator iter;
      for ( iter = m_Sockets.begin(); iter != m_Sockets.end(); iter++ )
      {
         CComPtr<iSocket> pSocket = *iter;
         pSocket->Draw(pDC,pMap);
      }
   }

   STDMETHOD_(void,Connect)(IDType key,AccessType access,iPlug* plug,DWORD* pdwCookie)
   {
      CComPtr<iSocket> pSocket;
      GetSocket(key,access,&pSocket);
      if ( pSocket )
      {
         pSocket->Connect(plug,pdwCookie);
      }
   }

   STDMETHOD_(void,Disconnect)(IDType key,AccessType access,DWORD dwCookie)
   {
      CComPtr<iSocket> pSocket;
      GetSocket(key,access,&pSocket);
      if ( pSocket )
         pSocket->Disconnect(dwCookie);
   }

protected:
   typedef std::vector<CComPtr<iSocket> > SocketContainer;
   SocketContainer m_Sockets;

private:
   CComPtr<iSocketFactory> m_pSocketFactory;

   SocketContainer::iterator GetSocket_Private(IDType key,AccessType access,iSocket** socket)
   {
      *socket = nullptr;
      if ( access == atByIndex )
      {
         IndexType index = (IndexType)key;
         if ( index < 0 || m_Sockets.size() <= index )
            return m_Sockets.end();

         (*socket) = m_Sockets[index];
         (*socket)->AddRef();
         return m_Sockets.begin() + index;
      }
      else
      {
         SocketContainer::iterator iter;
         for ( iter = m_Sockets.begin(); iter != m_Sockets.end(); iter++ )
         {
            CComPtr<iSocket> skt = *iter;
            if ( skt->GetID() == key )
            {
               (*socket) = skt;
               (*socket)->AddRef();
               return iter;
            }
         }
      }
      return m_Sockets.end();
   }
};

#endif // !defined(AFX_CONNECTABLEIMPL_H__D88A0194_DCD4_11D4_8B74_006097C68A9C__INCLUDED_)
