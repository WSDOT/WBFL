///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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

#pragma once

#include <DManip/DManipExp.h>
#include <DManip/DManipTypes.h>

namespace WBFL
{
   namespace Geometry
   {
      class Rect2d;
   };

   namespace DManip
   {
      class iPlug;
      class iPlugEvents;
      class iSocket;
      class iConnectable;
      class iCoordinateMap;

      /// @brief Interface defining plug objects. A plug object is attached to a Socket object to form a connection between Connectable objects and Connector objects.
      class DMANIPCLASS iPlug
      {
      public:
         /// @brief This method is called when this plug is connected to a socket
         /// @param socket The socket to which this plug is connected
         virtual void SetSocket(std::shared_ptr<iSocket> socket) = 0;

         /// @brief Returns the socket to which this plug is connected
         virtual std::shared_ptr<iSocket> GetSocket() = 0;
         virtual std::shared_ptr<const iSocket> GetSocket() const = 0;

         /// @brief Called by the framework when an event occurs on a socket. The plug forwards this event to all of its event sinks.
         virtual void Notify(std::shared_ptr<iSocket> socket) = 0;

         /// @brief Called when the socket is removed from the plug
         /// @param socket 
         virtual void OnRemove(std::shared_ptr<iSocket> socket) = 0;

         /// @brief Registers an event sink with this plug. The events are emitted to the event sink whenever this plug changes
         /// @param pEventSink 
         virtual void Register(std::weak_ptr<iPlugEvents> pEventSink) = 0;
      };

      /// @brief Interface to be implemented by objects wanting to receive plug notification events
      class iPlugEvents
      {
      public:
         /// @brief Called by the framework when a plug is changed
         /// @param plug The plug that was changed
         virtual void Notify(std::shared_ptr<iPlug> plug) = 0;
      };

      /// @brief Interface defining Socket objects. Sockets can be added to connectable objects. The Plug objects of a connector object are connected to Socket objects.
      class iSocket
      {
      public:
         /// @brief The socket identifier
         /// @param id 
         virtual void SetID(IDType id) = 0;
         virtual IDType GetID() const = 0;

         /// @brief The socket position in model space
         /// @param pos 
         virtual void SetPosition(const WBFL::Geometry::Point2d& pos) = 0;
         virtual const WBFL::Geometry::Point2d& GetPosition() const = 0;

         /// @brief Moves the socket by an offset
         /// @param offset 
         virtual void Move(const WBFL::Geometry::Size2d& offset) = 0;

         /// @brief Connects a plug
         /// @param plug 
         /// @return A connection identifier
         virtual DWORD Connect(std::weak_ptr<iPlug> plug) = 0;

         /// @brief Disconnects a plug from this socket
         /// @param plug 
         virtual void Disconnect(std::shared_ptr<iPlug> plug) = 0;

         /// @brief Disconnects the plug identified by dwCookie
         /// @param dwCookie 
         virtual void Disconnect(DWORD dwCookie) = 0;

         /// @brief Disconnects all plugs
         virtual void DisconnectAll() = 0;

         /// @brief Called by the framework whenever the socket needs to be drawn.
         /// @param pDC 
         /// @param pMap 
         virtual void Draw (CDC* pDC,std::shared_ptr<const iCoordinateMap> pMap) = 0;

         /// @brief Associates a connectable object with this socket
         /// @param pConnectable 
         virtual void SetConnectable(std::weak_ptr<iConnectable> pConnectable) = 0;
         virtual std::shared_ptr<iConnectable> GetConnectable() = 0;
      };

      /// @brief Interface defining a socket factory
      class iSocketFactory
      {
      public:
         /// @brief Creates a socket
         /// @param id The socket identifier
         /// @param pos Position of the socket in model space
         /// @return 
         virtual std::shared_ptr<iSocket> CreateSocket(IDType id,const WBFL::Geometry::Point2d& pos) const = 0;
      };

      /// @brief Interface defining a connectable object.
      class iConnectable
      {
      public:
         /// @brief Factory object used to create sockets
         /// @param factory 
         virtual void SetSocketFactory(std::shared_ptr<iSocketFactory> factory) = 0;
         virtual std::shared_ptr<iSocketFactory> GetSocketFactory() = 0;

         /// @brief Adds a socket to the connectable using the socket factory
         /// @param id 
         /// @param pos 
         /// @return 
         virtual std::shared_ptr<iSocket> AddSocket(IDType id,const WBFL::Geometry::Point2d& pos) = 0;

         /// @brief Returns the specified socket
         /// @param key 
         /// @param access 
         /// @return 
         virtual std::shared_ptr<iSocket> GetSocket(IDType key,AccessType access) = 0;

         /// @brief Find a socket within a rectangular space
         /// @param rect 
         /// @return 
         virtual std::shared_ptr<iSocket> FindSocket(const WBFL::Geometry::Rect2d& rect) = 0;

         /// @brief Returns the number of sockets
         /// @return 
         virtual IndexType GetSocketCount() const = 0;

         /// @brief Removes a socket
         /// @param key 
         /// @param access 
         /// @return 
         virtual bool RemoveSocket(IDType key,AccessType access) = 0;

         /// @brief Removes all sockets
         virtual void RemoveAllSockets() = 0;

         /// @brief Called by the framework whenever a socket needs to be drawn
         /// @param pDC 
         /// @param pMap 
         virtual void DrawSockets(CDC* pDC,std::shared_ptr<const iCoordinateMap> pMap) = 0;

         /// @brief Connects a plug to the specified socket
         /// @param key Key to identify the socket
         /// @param access Defines how key is interpreted
         /// @param plug 
         /// @return The plug identifier
         virtual DWORD Connect(IDType key,AccessType access,std::shared_ptr<iPlug> plug) = 0;

         /// @brief Disconnects a plug from the specifed socket
         /// @param key Key to identify the socket
         /// @param access Defines how key is interpreted
         /// @param dwCookie The plug identifier returned from Connect
         virtual void Disconnect(IDType key,AccessType access,DWORD dwCookie) = 0;
      };

      /// @brief Interface defining a connect object. Connectors are object such as lines that connect two connectable object together.
      class iConnector
      {
      public:
         /// @brief Returns the plug at the start of the connection
         /// @return 
         virtual std::shared_ptr<iPlug> GetStartPlug() = 0;
         virtual std::shared_ptr<const iPlug> GetStartPlug() const = 0;

         /// @brief Returns the plug at the end of the connection
         /// @return 
         virtual std::shared_ptr<iPlug> GetEndPlug() = 0;
         virtual std::shared_ptr<const iPlug> GetEndPlug() const = 0;
      };
   };
};
