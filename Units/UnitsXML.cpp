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

#include <Units\UnitsLib.h>
#include <Units\UnitsXML.h>
#include "Schema\WBFLUnits.hxx"
#include <Units\Measure.h>
#include <Units\System.h>
#include <Units\Convert.h>
#include <Units\XUnit.h>


using namespace WBFL::Units;

// Wraps DynamicUnitTypeManager::AddUnitType()/AddUnit() in a block scope so BEGIN_NEWUNITTYPE/NEWUNIT/
// END_NEWUNITTYPE read like the classic macro table, while every number is sourced from
// WBFL::Units::Measure:: (the single native source of truth) rather than being hand-transcribed here a
// second time. This mirrors WBFLUnitServer's historical CUnitTypes::InitDefaultUnits(), minus the
// SI/US/All unit-system tag (nothing downstream reads it back).
#define BEGIN_NEWUNITTYPE(name,m,l,t,k,a) \
   { \
      const std::_tstring unitTypeName(_T(name)); \
      mgr.AddUnitType(unitTypeName, (m),(l),(t),(k),(a));

#define NEWUNIT(tag,pre,cf,post) \
      mgr.AddUnit(unitTypeName, _T(tag), (pre),(cf),(post));

#define END_NEWUNITTYPE() \
   }

void UnitsXML::InitDefaultUnits(DynamicUnitTypeManager& mgr)
{
   // Every built-in unit added below intentionally has the same dimensionality as one of WBFLUnits'
   // compile-time PhysicalT aliases (that's the whole point - built-in and dynamically-added unit types
   // share one catalog). Suppress DynamicPhysical's "this duplicates a compile-time dimension" diagnostic
   // for the duration of this seeding; it stays fully active for any other, non-built-in caller.
#if defined _DEBUG
   DynamicPhysical::SuppressDuplicateDimensionWarningScope suppressWarnings;
#endif

   // Mass
   BEGIN_NEWUNITTYPE("Mass", 1,0,0,0,0);
      NEWUNIT("kg",      0.0, Measure::Kilogram.GetConvFactor(),  0.0);
      NEWUNIT("Mg",      0.0, Measure::Megagram.GetConvFactor(),  0.0);
      NEWUNIT("g",       0.0, Measure::Gram.GetConvFactor(),      0.0);
      NEWUNIT("MT",      0.0, Measure::MetricTon.GetConvFactor(), 0.0);
      NEWUNIT("slug",    0.0, Measure::Slug.GetConvFactor(),      0.0);
      NEWUNIT("lb",      0.0, Measure::PoundMass.GetConvFactor(), 0.0);
      NEWUNIT("kslug",   0.0, Measure::KSlug.GetConvFactor(),     0.0);
      NEWUNIT("12slug",  0.0, Measure::_12Slug.GetConvFactor(),   0.0);
      NEWUNIT("12kslug", 0.0, Measure::_12KSlug.GetConvFactor(),  0.0);
   END_NEWUNITTYPE();

   // Length
   BEGIN_NEWUNITTYPE("Length", 0,1,0,0,0);
      NEWUNIT("m",              0.0, Measure::Meter.GetConvFactor(),        0.0);
      NEWUNIT("mm",             0.0, Measure::Millimeter.GetConvFactor(),   0.0);
      NEWUNIT("cm",             0.0, Measure::Centimeter.GetConvFactor(),   0.0);
      NEWUNIT("km",             0.0, Measure::Kilometer.GetConvFactor(),    0.0);
      NEWUNIT("ft",             0.0, Measure::Feet.GetConvFactor(),         0.0);
      NEWUNIT("in",             0.0, Measure::Inch.GetConvFactor(),         0.0);
      NEWUNIT("mile",           0.0, Measure::Mile.GetConvFactor(),         0.0);
      NEWUNIT("yd",             0.0, Measure::Yard.GetConvFactor(),         0.0);
      NEWUNIT("ft(US survey)",  0.0, Measure::USSurveyFoot.GetConvFactor(), 0.0);
      NEWUNIT("yd(US survey)",  0.0, Measure::USSurveyYard.GetConvFactor(), 0.0);
   END_NEWUNITTYPE();

   // Time
   BEGIN_NEWUNITTYPE("Time", 0,0,1,0,0);
      NEWUNIT("sec", 0.0, Measure::Second.GetConvFactor(), 0.0);
      NEWUNIT("min", 0.0, Measure::Minute.GetConvFactor(), 0.0);
      NEWUNIT("hr",  0.0, Measure::Hour.GetConvFactor(),   0.0);
      NEWUNIT("day", 0.0, Measure::Day.GetConvFactor(),    0.0);
   END_NEWUNITTYPE();

   // Temperature
   BEGIN_NEWUNITTYPE("Temperature", 0,0,0,1,0);
      NEWUNIT("C", Measure::Celsius.GetPreTerm(),    Measure::Celsius.GetConvFactor(),    Measure::Celsius.GetPostTerm());
      NEWUNIT("F", Measure::Fahrenheit.GetPreTerm(), Measure::Fahrenheit.GetConvFactor(), Measure::Fahrenheit.GetPostTerm());
   END_NEWUNITTYPE();

   // Angle
   BEGIN_NEWUNITTYPE("Angle", 0,0,0,0,1);
      NEWUNIT("rad", 0.0, Measure::Radian.GetConvFactor(), 0.0);
      NEWUNIT("deg", 0.0, Measure::Degree.GetConvFactor(), 0.0);
   END_NEWUNITTYPE();

   // Mass Per Length
   BEGIN_NEWUNITTYPE("MassPerLength", 1,-1,0,0,0);
      NEWUNIT("kg/m",    0.0, Measure::KgPerMeter.GetConvFactor(),  0.0);
      NEWUNIT("slug/ft", 0.0, Measure::SlugPerFeet.GetConvFactor(), 0.0);
      NEWUNIT("lb/ft",   0.0, Measure::LbfPerFeet.GetConvFactor(),  0.0);
   END_NEWUNITTYPE();

   // Area
   BEGIN_NEWUNITTYPE("Length2", 0,2,0,0,0);
      NEWUNIT("m^2",    0.0, Measure::Meter2.GetConvFactor(),      0.0);
      NEWUNIT("mm^2",   0.0, Measure::Millimeter2.GetConvFactor(), 0.0);
      NEWUNIT("cm^2",   0.0, Measure::Centimeter2.GetConvFactor(), 0.0);
      NEWUNIT("km^2",   0.0, Measure::Kilometer2.GetConvFactor(),  0.0);
      NEWUNIT("ft^2",   0.0, Measure::Feet2.GetConvFactor(),       0.0);
      NEWUNIT("in^2",   0.0, Measure::Inch2.GetConvFactor(),       0.0);
      NEWUNIT("mile^2", 0.0, Measure::Mile2.GetConvFactor(),       0.0);
      NEWUNIT("yd^2",   0.0, Measure::Yard2.GetConvFactor(),       0.0);
   END_NEWUNITTYPE();

   // Volume
   BEGIN_NEWUNITTYPE("Length3", 0,3,0,0,0);
      NEWUNIT("m^3",    0.0, Measure::Meter3.GetConvFactor(),      0.0);
      NEWUNIT("mm^3",   0.0, Measure::Millimeter3.GetConvFactor(), 0.0);
      NEWUNIT("cm^3",   0.0, Measure::Centimeter3.GetConvFactor(), 0.0);
      NEWUNIT("km^3",   0.0, Measure::Kilometer3.GetConvFactor(),  0.0);
      NEWUNIT("ft^3",   0.0, Measure::Feet3.GetConvFactor(),       0.0);
      NEWUNIT("in^3",   0.0, Measure::Inch3.GetConvFactor(),       0.0);
      NEWUNIT("mile^3", 0.0, Measure::Mile3.GetConvFactor(),       0.0);
      NEWUNIT("yd^3",   0.0, Measure::Yard3.GetConvFactor(),       0.0);
   END_NEWUNITTYPE();

   // Length4 (Moment of Inertia)
   BEGIN_NEWUNITTYPE("Length4", 0,4,0,0,0);
      NEWUNIT("m^4",    0.0, Measure::Meter4.GetConvFactor(),      0.0);
      NEWUNIT("mm^4",   0.0, Measure::Millimeter4.GetConvFactor(), 0.0);
      NEWUNIT("cm^4",   0.0, Measure::Centimeter4.GetConvFactor(), 0.0);
      NEWUNIT("km^4",   0.0, Measure::Kilometer4.GetConvFactor(),  0.0);
      NEWUNIT("ft^4",   0.0, Measure::Feet4.GetConvFactor(),       0.0);
      NEWUNIT("in^4",   0.0, Measure::Inch4.GetConvFactor(),       0.0);
      NEWUNIT("mile^4", 0.0, Measure::Mile4.GetConvFactor(),       0.0);
      NEWUNIT("yd^4",   0.0, Measure::Yard4.GetConvFactor(),       0.0);
   END_NEWUNITTYPE();

   // Pressure
   BEGIN_NEWUNITTYPE("Pressure", 1,-1,-2,0,0);
      NEWUNIT("Pa",  0.0, Measure::Pa.GetConvFactor(),  0.0);
      NEWUNIT("kPa", 0.0, Measure::kPa.GetConvFactor(), 0.0);
      NEWUNIT("MPa", 0.0, Measure::MPa.GetConvFactor(), 0.0);
      NEWUNIT("psi", 0.0, Measure::PSI.GetConvFactor(), 0.0);
      NEWUNIT("psf", 0.0, Measure::PSF.GetConvFactor(), 0.0);
      NEWUNIT("ksi", 0.0, Measure::KSI.GetConvFactor(), 0.0);
      NEWUNIT("ksf", 0.0, Measure::KSF.GetConvFactor(), 0.0);
   END_NEWUNITTYPE();

   // Unit Weight
   BEGIN_NEWUNITTYPE("UnitWeight", 1,-3,-3,0,0);
      NEWUNIT("N/m^3", 0.0, Measure::NewtonPerMeter3.GetConvFactor(), 0.0);
      NEWUNIT("pci",   0.0, Measure::PCI.GetConvFactor(),             0.0);
      NEWUNIT("pcf",   0.0, Measure::PCF.GetConvFactor(),             0.0);
   END_NEWUNITTYPE();

   // Density
   BEGIN_NEWUNITTYPE("Density", 1,-3,0,0,0);
      NEWUNIT("kg/m^3",    0.0, Measure::KgPerMeter3.GetConvFactor(),  0.0);
      NEWUNIT("slug/ft^3", 0.0, Measure::SlugPerFeet3.GetConvFactor(), 0.0);
      NEWUNIT("lb/ft^3",   0.0, Measure::LbmPerFeet3.GetConvFactor(),  0.0);
   END_NEWUNITTYPE();

   // Force
   BEGIN_NEWUNITTYPE("Force", 1,1,-2,0,0);
      NEWUNIT("N",   0.0, Measure::Newton.GetConvFactor(),     0.0);
      NEWUNIT("kN",  0.0, Measure::Kilonewton.GetConvFactor(), 0.0);
      NEWUNIT("lbf", 0.0, Measure::Pound.GetConvFactor(),      0.0);
      NEWUNIT("kip", 0.0, Measure::Kip.GetConvFactor(),        0.0);
      NEWUNIT("ton", 0.0, Measure::Ton.GetConvFactor(),        0.0);
   END_NEWUNITTYPE();

   // Force Per Length
   BEGIN_NEWUNITTYPE("ForcePerLength", 1,0,-2,0,0);
      NEWUNIT("N/m",    0.0, Measure::NewtonPerMeter.GetConvFactor(),      0.0);
      NEWUNIT("N/mm",   0.0, Measure::NewtonPerMillimeter.GetConvFactor(), 0.0);
      NEWUNIT("lbf/ft", 0.0, Measure::LbfPerFoot.GetConvFactor(),         0.0);
      NEWUNIT("lbf/in", 0.0, Measure::LbfPerInch.GetConvFactor(),         0.0);
      NEWUNIT("kip/ft", 0.0, Measure::KipPerFoot.GetConvFactor(),         0.0);
      NEWUNIT("kip/in", 0.0, Measure::KipPerInch.GetConvFactor(),         0.0);
   END_NEWUNITTYPE();

   // Moment
   BEGIN_NEWUNITTYPE("Moment", 1,2,-2,0,0);
      NEWUNIT("N-m",    0.0, Measure::NewtonMeter.GetConvFactor(),      0.0);
      NEWUNIT("N-mm",   0.0, Measure::NewtonMillimeter.GetConvFactor(), 0.0);
      NEWUNIT("kN-m",   0.0, Measure::KilonewtonMeter.GetConvFactor(), 0.0);
      NEWUNIT("lbf-in", 0.0, Measure::InchLbf.GetConvFactor(),         0.0);
      NEWUNIT("lbf-ft", 0.0, Measure::PoundFeet.GetConvFactor(),       0.0);
      NEWUNIT("kip-ft", 0.0, Measure::KipFeet.GetConvFactor(),         0.0);
      NEWUNIT("kip-in", 0.0, Measure::KipInch.GetConvFactor(),         0.0);
   END_NEWUNITTYPE();

   // Thermal expansion
   BEGIN_NEWUNITTYPE("ThermalExpansion", 0,0,0,-1,0);
      NEWUNIT("1/C", 0.0, Measure::PerCelsius.GetConvFactor(),    0.0);
      NEWUNIT("1/F", 0.0, Measure::PerFahrenheit.GetConvFactor(), 0.0);
   END_NEWUNITTYPE();
}

#undef BEGIN_NEWUNITTYPE
#undef NEWUNIT
#undef END_NEWUNITTYPE

void UnitsXML::Initialize(UnitsDeclarationType* pDeclaration, DynamicUnitTypeManager& mgr)
{
   auto& extendedUnits = pDeclaration->ExtendedUnits();
   if (extendedUnits.present())
   {
      // <ExtendedUnits><UnitOfMeasure> - additional units of measure under an existing (built-in or
      // extended) unit type
      for (auto& unitOfMeasure : extendedUnits->UnitOfMeasure())
      {
         Float64 pre = unitOfMeasure.PreConvertTerm().present() ? unitOfMeasure.PreConvertTerm().get() : 0.0;
         Float64 post = unitOfMeasure.PostConvertTerm().present() ? unitOfMeasure.PostConvertTerm().get() : 0.0;
         mgr.AddUnit(unitOfMeasure.UnitType(), unitOfMeasure.name(), pre, unitOfMeasure.ConversionFactor(), post);
      }

      // <ExtendedUnits><UnitTypes><UnitType> - entirely new unit types, each with its own units of measure
      if (extendedUnits->UnitTypes().present())
      {
         for (auto& unitType : extendedUnits->UnitTypes()->UnitType())
         {
            mgr.AddUnitType(unitType.name(), unitType.mass(), unitType.length(), unitType.time(), unitType.temperature(), unitType.angle());

            for (auto& unitOfMeasure : unitType.UnitOfMeasure())
            {
               Float64 pre = unitOfMeasure.PreConvertTerm().present() ? unitOfMeasure.PreConvertTerm().get() : 0.0;
               Float64 post = unitOfMeasure.PostConvertTerm().present() ? unitOfMeasure.PostConvertTerm().get() : 0.0;
               mgr.AddUnit(unitType.name(), unitOfMeasure.name(), pre, unitOfMeasure.ConversionFactor(), post);
            }
         }
      }
   }

   auto& consistentUnits = pDeclaration->ConsistentUnits();
   if (consistentUnits.present())
   {
      mgr.SetBaseUnits(consistentUnits->mass(), consistentUnits->length(), consistentUnits->time(), consistentUnits->temperature(), consistentUnits->angle());
   }
}

DynamicUnitTypeManager UnitsXML::CreateUnitTypeManager(UnitsDeclarationType* pDeclaration)
{
   DynamicUnitTypeManager mgr;
   InitDefaultUnits(mgr);
   // kg/m/sec/C/rad is the default base units every WBFLUnitServer IUnitServer historically started with
   // (set unconditionally in CUnitServerImp::FinalConstruct()), before any <ConsistentUnits> declaration is
   // applied below. A document without a <ConsistentUnits> element relies on this default remaining in
   // effect.
   mgr.SetBaseUnits(_T("kg"), _T("m"), _T("sec"), _T("C"), _T("rad"));
   if (pDeclaration != nullptr)
   {
      Initialize(pDeclaration, mgr);
   }
   return mgr;
}

DynamicUnitTypeManager UnitsXML::CreateSystemUnitManager()
{
   DynamicUnitTypeManager mgr;
   InitDefaultUnits(mgr);
   mgr.SetBaseUnits(System::GetMassUnit().UnitTag(), System::GetLengthUnit().UnitTag(), System::GetTimeUnit().UnitTag(), System::GetTemperatureUnit().UnitTag(), System::GetAngleUnit().UnitTag());
   return mgr;
}

Float64 UnitsXML::detail::ConvertBetweenBaseUnitsImpl(Float64 value, bool hasExplicitUnit, const std::_tstring& explicitUnitTag, LPCTSTR unitTypeName, const DynamicUnitTypeManager& fromMgr, const DynamicUnitTypeManager& toMgr)
{
   if (hasExplicitUnit)
   {
      value = Convert(value, fromMgr.GetUnit(unitTypeName, explicitUnitTag), fromMgr.GetBaseUnit(unitTypeName));
   }
   return Convert(value, fromMgr.GetBaseUnit(unitTypeName), toMgr.GetBaseUnit(unitTypeName));
}
