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

#pragma once

#include <DManip/DManipExp.h>
#include <DManip/Connections.h>
#include <DManip/PlugImpl.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief Template mix-in class that implements the iConnector interface
      /// @tparam T Type of the parent class (CRTP idiom)      
      template <class T>
      class DMANIPCLASS Connector : public iConnector, public iPlugEvents
      {
      public:
         Connector() = default;
         virtual ~Connector() = default;

         void SetConnectorParent(std::weak_ptr<T> parent)
         {
            m_pStart = std::make_shared<Plug>();
            m_pEnd = std::make_shared<Plug>();

            auto plug_events = std::dynamic_pointer_cast<iPlugEvents>(parent.lock());
            m_pStart->Register(plug_events);
            m_pEnd->Register(plug_events);
         }

         // iConnector
         virtual std::shared_ptr<iPlug> GetStartPlug() override 
         {
            return m_pStart;
         }

         virtual std::shared_ptr<const iPlug> GetStartPlug() const override
         {
            return m_pStart;
         }

         virtual std::shared_ptr<iPlug> GetEndPlug() override
         {
            return m_pEnd;
         }

         virtual std::shared_ptr<const iPlug> GetEndPlug() const override
         {
            return m_pEnd;
         }

         // iPlugListener
         virtual void Notify(std::shared_ptr<iPlug> plug) override
         {
            // Do nothing...
            // subclasses can do something interesting
         }

      private:
         std::shared_ptr<iPlug> m_pStart;
         std::shared_ptr<iPlug> m_pEnd;
      };
   };
};
