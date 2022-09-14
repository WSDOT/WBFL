///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
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

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/Primitives.h>
#include <System/Exception.h>

#define THROW_GEOMETRY(reason) throw WBFL::Geometry::XGeometry(reason,_T(__FILE__),__LINE__)

namespace WBFL
{
   namespace Geometry
   {
      /// A geometric modeling error has occured
      class GEOMMODELCLASS XGeometry : public WBFL::System::XBase
      {
      public:
         XGeometry() = delete;
         XGeometry(const std::_tstring& strReason, const std::_tstring& file, Uint32 line);
         virtual ~XGeometry() = default;

         XGeometry& operator=(const XGeometry&) = default;

         virtual void Throw() const override;
         virtual Int32 GetReason() const noexcept override;
         virtual void GetErrorMessage(std::_tstring* pMsg) const override;

      private:
         std::_tstring m_Reason;
      };
   }; // Geometry
}; // WBFL
