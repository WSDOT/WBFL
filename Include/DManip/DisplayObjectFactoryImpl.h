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
#include <DManip/DisplayObjectFactory.h>

namespace WBFL
{
   namespace DManip
   {
      class iDisplayObject;

      /// @brief A basic implementation of a display object factory
      /// Creates LegendDisplayObject instances
      class DMANIPCLASS DisplayObjectFactory : public iDisplayObjectFactory
      {
      protected:
         DisplayObjectFactory() = default;

      public:
         static std::shared_ptr<DisplayObjectFactory> Create() { return std::shared_ptr<DisplayObjectFactory>(new DisplayObjectFactory()); }
         virtual ~DisplayObjectFactory() = default;
         
         virtual std::shared_ptr<iDisplayObject> Create(CLIPFORMAT cfFormat,COleDataObject* pDataObject) const override;
      };
   };
};
