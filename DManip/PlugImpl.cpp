///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <DManip/PlugImpl.h>

using namespace WBFL::DManip;

void Plug::Notify(std::shared_ptr<iSocket> socket)
{
   for (auto& sink : m_EventSinks)
   {
      sink.lock()->Notify(shared_from_this());
   }
}

void Plug::OnRemove(std::shared_ptr<iSocket> socket)
{
   socket->Disconnect(m_dwCookie);
}

void Plug::SetSocket(std::shared_ptr<iSocket> socket)
{
   m_pSocket = socket;
}

std::shared_ptr<iSocket> Plug::GetSocket()
{
   return m_pSocket;
}

std::shared_ptr<const iSocket> Plug::GetSocket() const
{
   return m_pSocket;
}

void Plug::Register(std::weak_ptr<iPlugEvents> pEventSink)
{
   m_EventSinks.push_back( pEventSink );
}
