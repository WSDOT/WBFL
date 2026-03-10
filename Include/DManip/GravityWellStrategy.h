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

namespace WBFL
{
   namespace DManip
   {
      class iDisplayObject;

      /// @brief Interface defining a gravity well. A gravity well is used in hit testing.
      /// From a display object, a region can be defined. Screen points are tested for
      /// inclusion within the region
      class DMANIPCLASS iGravityWellStrategy
      {
      public:
         /// @brief Creates a CRgn object based on a display object
         virtual void GetGravityWell(std::shared_ptr<const iDisplayObject> pDO,CRgn* pRgn) = 0;
      };
   };
};
