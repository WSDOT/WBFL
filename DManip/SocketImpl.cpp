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

#include "pch.h"
#include <DManip/SocketImpl.h>
#include <DManip/CoordinateMap.h>
#include <Colors.h>

using namespace WBFL::DManip;

DWORD Socket::ms_dwCookies = 1;

Socket::Socket(IDType id, const WBFL::Geometry::Point2d& pos) :
   m_ID(id), m_Position(pos)
{
}

void Socket::SetID(IDType id)
{
   m_ID = id;
}

IDType Socket::GetID() const
{
   return m_ID;
}

void Socket::SetPosition(const WBFL::Geometry::Point2d& pos)
{
   m_Position.Move(pos);
   Notify();
}

const WBFL::Geometry::Point2d& Socket::GetPosition() const
{
   return m_Position;
}

void Socket::Move(const WBFL::Geometry::Size2d& offset)
{
   m_Position.Offset(offset);
   Notify();
}

DWORD Socket::Connect(std::weak_ptr<iPlug> plug)
{
   DWORD dwCookie = ms_dwCookies++;
   plug.lock()->SetSocket(shared_from_this());
   m_Plugs.insert(PlugContainer::value_type(dwCookie,plug));
   return dwCookie;
}

void Socket::Disconnect(DWORD dwCookie)
{
   PlugContainer::iterator found;
   found = m_Plugs.find(dwCookie);

   if ( found != m_Plugs.end() )
   {
      auto pPlug = (*found).second;
      pPlug.lock()->SetSocket(std::shared_ptr<iSocket>());
      m_Plugs.erase(found);
   }
}

void Socket::Disconnect(std::shared_ptr<iPlug> plug)
{
   auto iter = m_Plugs.begin();
   const auto& end = m_Plugs.end();
   for ( ; iter != end; iter++)
   {
      auto pPlug = (*iter).second;
      if (pPlug.lock() == plug)
      {
         pPlug.lock()->SetSocket(std::shared_ptr<iSocket>());
         m_Plugs.erase(iter);
         return;
      }
   }
}

void Socket::DisconnectAll()
{
   for (auto& item : m_Plugs)
   {
      item.second.lock()->SetSocket(std::shared_ptr<iSocket>());
   }

   m_Plugs.clear();
}

void Socket::Draw(CDC* pDC,std::shared_ptr<const iCoordinateMap> pMap)
{
   CPen red(PS_SOLID,1,RED);

   CPoint pos;
   pMap->WPtoLP(m_Position,&pos.x,&pos.y);
   CRect r(pos,pos);

   r.InflateRect(1,1,1,1);
   CPen* oldPen = pDC->SelectObject(&red);
   pDC->Ellipse(r);
   pDC->SelectObject(oldPen);
}

void Socket::SetConnectable(std::weak_ptr<iConnectable> pConnectable)
{
   m_pConnectable = pConnectable;
}

std::shared_ptr<iConnectable> Socket::GetConnectable()
{
   return m_pConnectable.lock();
}

void Socket::Notify()
{
   auto me = shared_from_this();
   std::for_each(m_Plugs.begin(), m_Plugs.end(), [me](auto& plug_record) 
      {
         if (auto plug = plug_record.second.lock())
            plug->Notify(me); 
      }
   );
}
