///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright © 1999-2022  Washington State Department of Transportation
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

#include <RCSection/RCSectionExp.h>
#include <System/Exception.h>

#define THROW_RCSECTION(reason) throw XRCSection(reason,_T(__FILE__),__LINE__)

namespace WBFL
{
   namespace RCSection
   {
      /// A RC Section Modeling or Solution error has occured
      class RCSCLASS XRCSection : public WBFL::System::XBase
      {
      public:
         XRCSection() = default;
         XRCSection(const XRCSection&) = default;
         XRCSection(const std::_tstring& lpszReason, const std::_tstring& file, Uint32 line);
         virtual ~XRCSection() = default;

         XRCSection& operator=(const XRCSection&) = default;

         virtual void Throw() const override;
         virtual Int32 GetReason() const noexcept override;
         virtual void GetErrorMessage(std::_tstring* pMsg) const override;

      private:
         std::_tstring m_Reason;
      };
   };
};