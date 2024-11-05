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
#include <DManip/SocketFactoryImpl.h>
#include <vector>

namespace WBFL
{
   namespace DManip
   {
      /// @brief Template mix-in class that implements the iConnectable interface
      /// @tparam T Type of the parent class (CRTP idiom)
      template <class T>
      class DMANIPCLASS Connectable : public iConnectable
      {
      public:
         Connectable() = default;
         virtual ~Connectable() = default;

         void SetConnectableParent(std::weak_ptr<T> parent)
         {
            auto connectable = std::dynamic_pointer_cast<iConnectable>(parent.lock());
            m_ConnectableParent = connectable;
         }
   
         // iConnectable
         virtual void SetSocketFactory(std::shared_ptr<iSocketFactory> factory) override
         {
            m_pSocketFactory = factory;
         }

         virtual std::shared_ptr<iSocketFactory> GetSocketFactory() override
         {
            return m_pSocketFactory;
         }

         virtual std::shared_ptr<iSocket> AddSocket(IDType id, const WBFL::Geometry::Point2d& pos) override
         {
            auto new_socket = m_pSocketFactory->CreateSocket(id, pos);
            new_socket->SetConnectable(m_ConnectableParent);
            m_Sockets.push_back(new_socket);
            return new_socket;
         }

         virtual std::shared_ptr<iSocket> GetSocket(IDType key, AccessType access) override
         {
            auto iter = GetSocket_Private(key, access);
            if (iter != m_Sockets.end()) return *iter;
            return nullptr;
         }

         virtual std::shared_ptr<iSocket> FindSocket(const WBFL::Geometry::Rect2d& r) override
         {
            for (auto& socket : m_Sockets)
            {
               if (r.Contains(socket->GetPosition()))
                  return socket;
            }

            return nullptr;
         }

         virtual IndexType GetSocketCount() const override
         {
            return m_Sockets.size();
         }

         virtual bool RemoveSocket(IDType key, AccessType access) override
         {
            auto iter = GetSocket_Private(key, access);
            if (iter == m_Sockets.end())
               return false;

            auto& socket(*iter);
            socket->DisconnectAll();
            m_Sockets.erase(iter);
            return true;
         }

         virtual void RemoveAllSockets() override
         {
            if (!m_Sockets.empty())
            {
               std::for_each(m_Sockets.begin(), m_Sockets.end(), [](auto& socket) {socket->DisconnectAll(); });
               m_Sockets.clear();
            }
         }

         virtual void DrawSockets(CDC* pDC, std::shared_ptr<const iCoordinateMap> pMap) override
         {
            if (!m_Sockets.empty())
            {
               std::for_each(m_Sockets.begin(), m_Sockets.end(), [pDC, pMap](auto& socket) {socket->Draw(pDC, pMap); });
            }
         }

         virtual DWORD Connect(IDType key, AccessType access, std::shared_ptr<iPlug> plug) override
         {
            auto socket = GetSocket(key, access);
            if (socket)
            {
               return socket->Connect(plug);
            }
            return -1;
         }

         virtual void Disconnect(IDType key, AccessType access, DWORD dwCookie) override
         {
            auto socket = GetSocket(key, access);
            if (socket)
               socket->Disconnect(dwCookie);
         }

      protected:
         using SocketContainer = std::vector<std::shared_ptr<iSocket>>;
         SocketContainer m_Sockets;

      private:
         std::shared_ptr<iSocketFactory> m_pSocketFactory = std::make_shared<SocketFactory>();
         std::weak_ptr<iConnectable> m_ConnectableParent; // the parent of this connectable

         SocketContainer::iterator GetSocket_Private(IDType key, AccessType access)
         {
            if (access == AccessType::ByIndex)
            {
               IndexType index = (IndexType)key;
               if (index < 0 || m_Sockets.size() <= index)
                  return m_Sockets.end();

               return m_Sockets.begin() + index;
            }
            else
            {
               SocketContainer::iterator iter;
               for (iter = m_Sockets.begin(); iter != m_Sockets.end(); iter++)
               {
                  auto& socket(*iter);
                  if (socket->GetID() == key)
                  {
                     return iter;
                  }
               }
            }
            return m_Sockets.end();
         }
      };
   };
};
