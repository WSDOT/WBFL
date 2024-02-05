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
#include <map>
#include <DManip/Connections.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief An object that represents a socket in an iPlug - iSocket connection
      class DMANIPCLASS Socket : public iSocket, public std::enable_shared_from_this<Socket>
      {
      public:
	      Socket() = default;
         Socket(IDType id, const WBFL::Geometry::Point2d& pos);
	      virtual ~Socket() = default;

         // iSocket
         virtual void SetID(IDType id) override;
         virtual IDType GetID() const override;
         virtual void SetPosition(const WBFL::Geometry::Point2d& pos) override;
         virtual const WBFL::Geometry::Point2d& GetPosition() const override;
         virtual void Move(const WBFL::Geometry::Size2d& offset) override;
         virtual DWORD Connect(std::weak_ptr<iPlug> plug) override;
         virtual void Disconnect(std::shared_ptr<iPlug> plug) override;
         virtual void Disconnect(DWORD dwCookie) override;
         virtual void DisconnectAll() override;
         virtual void Draw(CDC* pDC, std::shared_ptr<const iCoordinateMap> pMap) override;
         virtual void SetConnectable(std::weak_ptr<iConnectable> pConnectable) override;
         virtual std::shared_ptr<iConnectable> GetConnectable() override;

      private:
         static DWORD ms_dwCookies;
         IDType m_ID = INVALID_ID;
         WBFL::Geometry::Point2d m_Position;
         using PlugContainer = std::map<DWORD,std::weak_ptr<iPlug>>;
         PlugContainer m_Plugs;
         std::weak_ptr<iConnectable> m_pConnectable;
         void Notify();
      };
   };
};
