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

#include <DManip/Connections.h>
#include <vector>

namespace WBFL
{
   namespace DManip
   {
      /// @brief An object that represents a plug in an iPlug - iSocket connection
      class DMANIPCLASS Plug : public iPlug, public std::enable_shared_from_this<Plug>
      {
      public:
	      Plug() = default;
	      virtual ~Plug() = default;

         // iPlug
         virtual void Notify(std::shared_ptr<iSocket> socket) override;
         virtual void OnRemove(std::shared_ptr<iSocket> socket) override;
         virtual void SetSocket(std::shared_ptr<iSocket> socket) override;
         virtual std::shared_ptr<iSocket> GetSocket() override;
         virtual std::shared_ptr<const iSocket> GetSocket() const override;
         virtual void Register(std::weak_ptr<iPlugEvents> pEventSink) override;

      protected:
         DWORD m_dwCookie;
         std::shared_ptr<iSocket> m_pSocket;

         std::vector<std::weak_ptr<iPlugEvents>> m_EventSinks;
      };
   };
};
