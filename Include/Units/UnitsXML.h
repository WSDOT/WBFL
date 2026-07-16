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
#include <Units\DynamicUnitTypeManager.h>

namespace WBFL
{
   namespace Units
   {
      // Forward declarations of the XSD-generated data-binding classes for the UnitsXML schema
      // (WBFL\Units\Schema\WBFLUnits.xsd / WBFLUnits.hxx). Only pointers/references to these types appear in
      // this header; a caller that actually constructs one (typically by parsing a document whose own schema
      // imports WBFLUnits.xsd) will already have the full definition in scope via its own generated header.
      class UnitsDeclarationType;
      class MassValueType;
      class LengthValueType;
      class PositiveLengthValueType;
      class TimeValueType;
      class TemperatureValueType;
      class AngleValueType;
      class MassPerLengthValueType;
      class Length2ValueType;
      class Length3ValueType;
      class Length4ValueType;
      class PressureValueType;
      class UnitWeightValueType;
      class DensityValueType;
      class ForceValueType;
      class ForcePerLengthValueType;
      class MomentValueType;
      class ThermalExpansionValueType;

      /// Support for the units-declaration portion of the UnitsXML schema (WBFLUnits.xsd): reading a
      /// document's <UnitsDeclaration> (custom unit types/units of measure, and the document's consistent/
      /// base units) into a DynamicUnitTypeManager, and converting unit-bearing values between two such
      /// managers' base units. This is the non-COM counterpart of what WBFLUnitServer historically provided
      /// through its IUnitServer COM object model.
      namespace UnitsXML
      {
         /// Seeds mgr with the built-in unit types and units of measure that every UnitsXML document
         /// implicitly starts with (Mass, Length, Time, Temperature, Angle, and the derived types built from
         /// them), mirroring WBFLUnitServer's historical CUnitTypes::InitDefaultUnits(). Call once on a
         /// freshly constructed DynamicUnitTypeManager, before Initialize().
         void UNITSFUNC InitDefaultUnits(DynamicUnitTypeManager& mgr);

         /// Reads pDeclaration's <ExtendedUnits> and <ConsistentUnits> into mgr, which must already be
         /// seeded via InitDefaultUnits(): registers any custom unit types/units of measure declared under
         /// <ExtendedUnits>, and designates mgr's base units, via DynamicUnitTypeManager::SetBaseUnits(),
         /// from <ConsistentUnits>. pDeclaration must not be null.
         void UNITSFUNC Initialize(UnitsDeclarationType* pDeclaration, DynamicUnitTypeManager& mgr);

         /// Convenience: constructs a manager, seeds it with the built-in units (InitDefaultUnits()), sets
         /// its base units to kg/m/sec/C/rad, and, if pDeclaration is not null, initializes it from
         /// pDeclaration (Initialize()) - whose own <ConsistentUnits>, if present, overrides that default.
         DynamicUnitTypeManager UNITSFUNC CreateUnitTypeManager(UnitsDeclarationType* pDeclaration = nullptr);

         /// Convenience: constructs a manager seeded with the built-in units, whose base units are set to
         /// WBFL::Units::System's current mass/length/time/temperature/angle units.
         DynamicUnitTypeManager UNITSFUNC CreateSystemUnitManager();

         namespace detail
         {
            template <class U> struct UnitTypeNameOf;
            template <> struct UnitTypeNameOf<MassValueType> { static constexpr LPCTSTR Name = _T("Mass"); };
            template <> struct UnitTypeNameOf<LengthValueType> { static constexpr LPCTSTR Name = _T("Length"); };
            // PositiveLengthValueType is a schema restriction of LengthValueType (used where a length must
            // be >= 0, e.g. VerticalCurveDataType::Length) - it shares Length's unit type and dimensionality.
            template <> struct UnitTypeNameOf<PositiveLengthValueType> { static constexpr LPCTSTR Name = _T("Length"); };
            template <> struct UnitTypeNameOf<TimeValueType> { static constexpr LPCTSTR Name = _T("Time"); };
            template <> struct UnitTypeNameOf<TemperatureValueType> { static constexpr LPCTSTR Name = _T("Temperature"); };
            template <> struct UnitTypeNameOf<AngleValueType> { static constexpr LPCTSTR Name = _T("Angle"); };
            template <> struct UnitTypeNameOf<MassPerLengthValueType> { static constexpr LPCTSTR Name = _T("MassPerLength"); };
            template <> struct UnitTypeNameOf<Length2ValueType> { static constexpr LPCTSTR Name = _T("Length2"); };
            template <> struct UnitTypeNameOf<Length3ValueType> { static constexpr LPCTSTR Name = _T("Length3"); };
            template <> struct UnitTypeNameOf<Length4ValueType> { static constexpr LPCTSTR Name = _T("Length4"); };
            template <> struct UnitTypeNameOf<PressureValueType> { static constexpr LPCTSTR Name = _T("Pressure"); };
            template <> struct UnitTypeNameOf<UnitWeightValueType> { static constexpr LPCTSTR Name = _T("UnitWeight"); };
            template <> struct UnitTypeNameOf<DensityValueType> { static constexpr LPCTSTR Name = _T("Density"); };
            template <> struct UnitTypeNameOf<ForceValueType> { static constexpr LPCTSTR Name = _T("Force"); };
            template <> struct UnitTypeNameOf<ForcePerLengthValueType> { static constexpr LPCTSTR Name = _T("ForcePerLength"); };
            template <> struct UnitTypeNameOf<MomentValueType> { static constexpr LPCTSTR Name = _T("Moment"); };
            template <> struct UnitTypeNameOf<ThermalExpansionValueType> { static constexpr LPCTSTR Name = _T("ThermalExpansion"); };

            /// Implements ConvertBetweenBaseUnits() below without depending on the schema value type U, so
            /// the logic lives once in WBFLUnits.lib rather than being duplicated at every template
            /// instantiation site.
            Float64 UNITSFUNC ConvertBetweenBaseUnitsImpl(Float64 value, bool hasExplicitUnit, const std::_tstring& explicitUnitTag, LPCTSTR unitTypeName, const DynamicUnitTypeManager& fromMgr, const DynamicUnitTypeManager& toMgr);
         }

         /// Converts unitValueType, a schema-bound value from the UnitsXML schema (one of the XxxValueType
         /// classes above), from fromMgr's base units to toMgr's base units. If unitValueType carries an
         /// explicit unit attribute, it is first converted from that unit (resolved against fromMgr) to
         /// fromMgr's base units, and the attribute is cleared. unitTypeName is inferred from U's type (see
         /// the UnitTypeNameOf specializations above). Throws XUnit with reason XUnit::Reason::UnitNotFound
         /// if unitValueType's explicit unit attribute doesn't name a unit registered in fromMgr.
         template <class U>
         void ConvertBetweenBaseUnits(U& unitValueType, const DynamicUnitTypeManager& fromMgr, const DynamicUnitTypeManager& toMgr)
         {
            Float64 value = unitValueType;
            bool hasExplicitUnit = unitValueType.unit().present();
            value = detail::ConvertBetweenBaseUnitsImpl(value, hasExplicitUnit,
               hasExplicitUnit ? unitValueType.unit().get() : std::_tstring(),
               detail::UnitTypeNameOf<U>::Name, fromMgr, toMgr);

            if (hasExplicitUnit)
            {
               unitValueType.unit().reset();
            }
            unitValueType = value;
         }
      };
   };
};
