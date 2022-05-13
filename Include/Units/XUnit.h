///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
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

#include <Units\UnitsExp.h>
#include <System\Exception.h>

namespace WBFL
{
   namespace Units
   {
      /// Unit system exception.
      class UNITSCLASS XUnit : public sysXBase
      {
      public:
         enum class Reason { BadStationFormat };

         XUnit(Reason reason,LPCTSTR file,Int16 line);

         virtual ~XUnit();

         virtual void Throw() const override;
         virtual Int32 GetReason() const override;
         Reason GetReasonCode() const;

      #if defined _DEBUG
         virtual bool AssertValid() const;
      #endif // _DEBUG

      private:
         Reason m_Reason;
      };
   };
};