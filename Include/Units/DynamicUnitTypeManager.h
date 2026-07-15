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
#include <Units\DynamicPhysical.h>
#include <map>
#include <vector>
#include <string>

namespace WBFL
{
   namespace Units
   {
      /// Describes the dimensionality of a unit type defined in a DynamicUnitTypeManager.
      struct DynamicUnitTypeDimension
      {
         Float64 Mass{ 0.0 };        ///< Mass dimensionality
         Float64 Length{ 0.0 };      ///< Length dimensionality
         Float64 Time{ 0.0 };        ///< Time dimensionality
         Float64 Temperature{ 0.0 }; ///< Temperature dimensionality
         Float64 Angle{ 0.0 };       ///< Angle dimensionality
      };

      /// Manages a named catalog of unit types, and the DynamicPhysical units of measure defined under
      /// them, all defined at run time.
      ///
      /// A unit type is a dimensionality (mass, length, time, temperature, and angle exponents) identified
      /// by a name, such as "Length" or "Force". Once a unit type has been added with AddUnitType(), any
      /// number of units of measure sharing that dimensionality can be added to it with AddUnit(), each
      /// identified within the unit type by its own tag, such as "ft" or "m". This mirrors the way an
      /// application (or a document format, such as WBFLUnitServer's OpenBridgeML XML persistence) might
      /// need to define custom unit types and units of measure whose dimensionality isn't known until run
      /// time.
      ///
      /// All of the query and mutation methods on this class throw WBFL::Units::XUnit when they are given a
      /// unit type name or unit tag that doesn't apply (see the individual method descriptions, and
      /// XUnit::Reason, for the specific conditions and reasons). HasUnitType() and HasUnit() are the
      /// non-throwing way to test whether a name or tag has been defined.
      class UNITSCLASS DynamicUnitTypeManager
      {
      public:
         DynamicUnitTypeManager() = default;
         DynamicUnitTypeManager(const DynamicUnitTypeManager&) = default;
         DynamicUnitTypeManager& operator=(const DynamicUnitTypeManager&) = default;
         ~DynamicUnitTypeManager() = default;

         /// Defines a new unit type, named name, with dimensionality (m,l,t,k,a). Throws XUnit with reason
         /// XUnit::Reason::UnitTypeAlreadyDefined if name is already in use.
         void AddUnitType(const std::_tstring& name, Float64 m, Float64 l, Float64 t, Float64 k, Float64 a);

         /// Removes the named unit type, and all of the units of measure defined under it. Throws XUnit
         /// with reason XUnit::Reason::UnitTypeNotFound if name hasn't been defined.
         void RemoveUnitType(const std::_tstring& name);

         /// Removes all unit types, and all of their units of measure, from this manager.
         void ClearUnitTypes();

         /// Returns true if a unit type named name has been defined.
         bool HasUnitType(const std::_tstring& name) const;

         /// Returns the number of unit types defined in this manager.
         IndexType GetUnitTypeCount() const;

         /// Returns the names of all unit types defined in this manager, in the order they were added
         /// (a unit type removed with RemoveUnitType and re-added with AddUnitType moves to the end).
         std::vector<std::_tstring> GetUnitTypeNames() const;

         /// Returns the name of the unit type at the given 0-based position, in the same order as
         /// GetUnitTypeNames(). Throws XUnit with reason XUnit::Reason::UnitTypeNotFound if index is out of
         /// range.
         const std::_tstring& GetUnitTypeName(IndexType index) const;

         /// Returns the dimensionality of the named unit type. Throws XUnit with reason
         /// XUnit::Reason::UnitTypeNotFound if name hasn't been defined.
         DynamicUnitTypeDimension GetUnitTypeDimension(const std::_tstring& name) const;

         /// Defines a new unit of measure, tagged tag, under the unit type named unitTypeName, with the
         /// conversion equation value*cf (equivalent to a PreTerm and PostTerm of 0). Throws XUnit with
         /// reason XUnit::Reason::UnitTypeNotFound if unitTypeName hasn't been defined, or
         /// XUnit::Reason::UnitAlreadyDefined if tag is already in use within that unit type.
         void AddUnit(const std::_tstring& unitTypeName, const std::_tstring& tag, Float64 cf);

         /// Defines a new unit of measure, tagged tag, under the unit type named unitTypeName, with the
         /// full conversion equation (value+preTerm)*cf+postTerm. Throws XUnit with reason
         /// XUnit::Reason::UnitTypeNotFound if unitTypeName hasn't been defined, or
         /// XUnit::Reason::UnitAlreadyDefined if tag is already in use within that unit type.
         void AddUnit(const std::_tstring& unitTypeName, const std::_tstring& tag, Float64 preTerm, Float64 cf, Float64 postTerm);

         /// Removes the unit of measure tagged tag from the unit type named unitTypeName. Throws XUnit with
         /// reason XUnit::Reason::UnitTypeNotFound if unitTypeName hasn't been defined, or
         /// XUnit::Reason::UnitNotFound if tag hasn't been defined within that unit type.
         void RemoveUnit(const std::_tstring& unitTypeName, const std::_tstring& tag);

         /// Removes all units of measure from the unit type named unitTypeName (the unit type itself, and
         /// its dimensionality, is retained). Throws XUnit with reason XUnit::Reason::UnitTypeNotFound if
         /// unitTypeName hasn't been defined.
         void ClearUnits(const std::_tstring& unitTypeName);

         /// Returns true if the unit type named unitTypeName has a unit of measure tagged tag. Returns
         /// false, rather than throwing, if unitTypeName hasn't been defined.
         bool HasUnit(const std::_tstring& unitTypeName, const std::_tstring& tag) const;

         /// Returns the number of units of measure defined under the unit type named unitTypeName. Throws
         /// XUnit with reason XUnit::Reason::UnitTypeNotFound if unitTypeName hasn't been defined.
         IndexType GetUnitCount(const std::_tstring& unitTypeName) const;

         /// Returns the tags of all units of measure defined under the unit type named unitTypeName, in the
         /// order they were added (a unit removed with RemoveUnit and re-added with AddUnit moves to the
         /// end). Throws XUnit with reason XUnit::Reason::UnitTypeNotFound if unitTypeName hasn't been
         /// defined.
         std::vector<std::_tstring> GetUnitTags(const std::_tstring& unitTypeName) const;

         /// Returns the tag of the unit of measure at the given 0-based position under the unit type named
         /// unitTypeName, in the same order as GetUnitTags(). Throws XUnit with reason
         /// XUnit::Reason::UnitTypeNotFound if unitTypeName hasn't been defined, or
         /// XUnit::Reason::UnitNotFound if index is out of range.
         const std::_tstring& GetUnitTag(const std::_tstring& unitTypeName, IndexType index) const;

         /// Returns the unit of measure tagged tag, defined under the unit type named unitTypeName. Throws
         /// XUnit with reason XUnit::Reason::UnitTypeNotFound if unitTypeName hasn't been defined, or
         /// XUnit::Reason::UnitNotFound if tag hasn't been defined within that unit type. The returned
         /// reference is invalidated by any subsequent call to RemoveUnit, ClearUnits, RemoveUnitType, or
         /// ClearUnitTypes for the same unit type.
         const DynamicPhysical& GetUnit(const std::_tstring& unitTypeName, const std::_tstring& tag) const;

      private:
         struct UnitTypeEntry
         {
            DynamicUnitTypeDimension Dimension;
            std::map<std::_tstring, DynamicPhysical> Units;
            std::vector<std::_tstring> UnitOrder; ///< insertion order of Units' keys
         };

         std::map<std::_tstring, UnitTypeEntry> m_UnitTypes;
         std::vector<std::_tstring> m_UnitTypeOrder; ///< insertion order of m_UnitTypes' keys

         UnitTypeEntry& GetUnitTypeEntry(const std::_tstring& name);
         const UnitTypeEntry& GetUnitTypeEntry(const std::_tstring& name) const;
      };
   };
};
