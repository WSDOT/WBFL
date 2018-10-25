///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#ifndef INCLUDED_CONNECTIONS_H_
#define INCLUDED_CONNECTIONS_H_
#pragma once

struct iPlug;
struct iPlugEvents;
struct iSocket;
struct iConnectable;
struct iCoordinateMap;

interface iPlug : public IUnknown
{
   STDMETHOD_(void,Notify)(iSocket* socket) PURE;
   STDMETHOD_(void,OnRemove)(iSocket* socket) PURE;
   STDMETHOD_(void,Register)(iPlugEvents* pEventSink) PURE;
   
   STDMETHOD_(void,SetSocket)(iSocket* pSocket) PURE;
   STDMETHOD_(void,GetSocket)(iSocket** socket) PURE;
};

interface iPlugEvents : public IUnknown
{
   STDMETHOD_(void,Notify)(iPlug* plug) PURE;
};

interface iSocket : public IUnknown
{
public:
   STDMETHOD_(void,SetID)(long id) PURE;
   STDMETHOD_(long,GetID)() PURE;
   STDMETHOD_(void,SetPosition)(IPoint2d* pos) PURE;
   STDMETHOD_(void,GetPosition)(IPoint2d* *pos) PURE;
   STDMETHOD_(void,Move)(ISize2d* offset) PURE;

   STDMETHOD_(void,Connect)(iPlug* plug,DWORD* pdwCookie) PURE;
   STDMETHOD_(void,Disconnect)(DWORD dwCookie) PURE;
   STDMETHOD_(void,DisconnectAll)() PURE;

   STDMETHOD_(void,Draw)(CDC* pDC,iCoordinateMap* pMap) PURE;

   STDMETHOD_(void,SetConnectable)(iConnectable* pConnectable) PURE;
   STDMETHOD_(void,GetConnectable)(iConnectable** connectable) PURE;
};

interface iSocketFactory : public IUnknown
{
public:
   STDMETHOD_(void,CreateSocket)(long id,IPoint2d* pos,iSocket** socket) PURE;
};

interface iConnectable : public IUnknown
{
public:
   STDMETHOD_(void,SetSocketFactory)(iSocketFactory* factory) PURE;
   STDMETHOD_(void,GetSocketFactory)(iSocketFactory** factory) PURE;

   STDMETHOD_(void,AddSocket)(long id,IPoint2d* pos,iSocket** socket) PURE;
   STDMETHOD_(void,GetSocket)(long key,AccessType access,iSocket** socket) PURE;
   STDMETHOD_(void,FindSocket)(IRect2d* rect,iSocket** socket) PURE;
   STDMETHOD_(long,GetSocketCount)() PURE;
   STDMETHOD_(void,RemoveSocket)(long key,AccessType access) PURE;
   STDMETHOD_(void,RemoveAllSockets)() PURE;

   STDMETHOD_(void,DrawSockets)(CDC* pDC,iCoordinateMap* pMap) PURE;

   STDMETHOD_(void,Connect)(long key,AccessType access,iPlug* plug,DWORD* pdwCookie) PURE;
   STDMETHOD_(void,Disconnect)(long key,AccessType access,DWORD dwCookie) PURE;
};

interface iConnector : public IUnknown
{
public:
   STDMETHOD_(void,GetStartPlug)(iPlug** plug) PURE;
   STDMETHOD_(void,GetEndPlug)(iPlug** plug) PURE;
};

#endif // INCLUDED_CONNECTIONS_H_