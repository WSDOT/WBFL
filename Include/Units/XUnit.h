///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright � 1999-2026  Washington State Department of Transportation
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
      class UNITSCLASS XUnit : public WBFL::System::XBase
      {
      public:
         enum class Reason
         {
            BadStationFormat,        ///< StationFormat::FromString was given a string that isn't a validly formatted station

            DimensionMismatch,       ///< Attempted to convert between two DynamicPhysical objects that don't have the same dimensionality
            UnitTypeAlreadyDefined,  ///< DynamicUnitTypeManager::AddUnitType was called with a name that is already in use
            UnitTypeNotFound,        ///< A DynamicUnitTypeManager operation referenced a unit type name that hasn't been defined
            UnitAlreadyDefined,      ///< DynamicUnitTypeManager::AddUnit was called with a tag that is already in use within the unit type
            UnitNotFound             ///< A DynamicUnitTypeManager operation referenced a unit tag that hasn't been defined within the unit type
         };

         /// Constructs the exception with the given reason. file and line should be the source file and
         /// line number where the exception is being thrown, typically _T(__FILE__) and __LINE__.
         XUnit(Reason reason,const std::_tstring& file,Uint32 line);

         virtual ~XUnit();

         /// Throws this exception object.
         virtual void Throw() const override;

         /// Returns the reason for this exception, as the underlying integer value of Reason.
         virtual Int32 GetReason() const noexcept override;

         /// Returns the reason for this exception.
         Reason GetReasonCode() const noexcept;

      #if defined _DEBUG
         virtual bool AssertValid() const;
      #endif // _DEBUG

      private:
         Reason m_Reason;
      };
   };
};