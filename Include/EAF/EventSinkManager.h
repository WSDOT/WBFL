///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

#pragma once

#include <EAF\EAFExp.h>
#include <map>

namespace WBFL
{
   namespace EAF
   {
      /// @brief Agents that callback to event sinks inherit from this template class for event sink management capabilities
      /// @tparam T Callback interface pointer
      /// 
      /// Refer to the implementation of CEAFDocProxyAgent and CProxyIEAFDisplayUnitsEventSink<IEAFDisplayUnitsEventSink> for an example
      /// defining an event sink callback interface, using this event sink manager class, and invoking methods on the event sink callback interface.
      template <typename T>
      class EventSinkManager
      {
      public:
         /// @brief Registers an event sink to receive callback events
         /// @param eventSink 
         /// @return A cookie value used to identify this specific connection. Use this cookie to unregister.
         IDType RegisterEventSink(std::weak_ptr<T> eventSink)
         {
            auto cookie = m_Cookie++;
            m_EventSinks.insert(std::make_pair(cookie, eventSink));
            return cookie;
         };

         /// @brief Unregisters the event sink so it no longer is called
         /// @param cookie Cookie value identifying the event sink, as returned from the RegisterEventSink method
         /// @return true if successful
         bool UnregisterEventSink(IDType cookie)
         {
            auto found = m_EventSinks.find(cookie);
            if (found == m_EventSinks.end())
               return false;

            m_EventSinks.erase(found);
            return true;
         };
      protected:
         IDType m_Cookie = 0; 

         // Registering callbacks can create circular references. To prevent this, this class holds weak_ptr to the event sink object.
         std::map<IDType,std::weak_ptr<T>> m_EventSinks;
      };
   };
};