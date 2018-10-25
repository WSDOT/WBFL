///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2015  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation, 
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but 
// distribution is AS IS, WITHOUT ANY WARRANTY; without even the implied 
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See 
// the Alternate Route Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source 
// License along with this program; if not, write to the Washington 
// State Department of Transportation, Bridge and Structures Office, 
// P.O. Box  47340, Olympia, WA 98503, USA or e-mail 
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WbflUnitServer.h"
#include <WBFLUnitServer\UnitServerUtils.h>

UnitSystemType GetWBFLUnitSystemType(OpenBridgeML::Units::UnitSystemEnum ust)
{
   switch(ust)
   {
   case OpenBridgeML::Units::UnitSystemEnum::unitsUS:
      return unitsUS;

   case OpenBridgeML::Units::UnitSystemEnum::unitsSI:
      return unitsSI;

   case OpenBridgeML::Units::UnitSystemEnum::unitsAll:
      return unitsAll;
   }

   ATLASSERT(false); // should never get here
   return unitsAll;
}

BOOL InitializeWBFLUnitServer(OpenBridgeML::Units::UnitsDeclarationType* pDeclaration,IUnitServer* pUnitServer)
{
   USES_CONVERSION;
   HRESULT hr = S_OK;
   OpenBridgeML::Units::UnitsDeclarationType::ExtendedUnits_optional& extendedUnits(pDeclaration->ExtendedUnits());
   if ( extendedUnits.present() )
   {
      // The <ExtendedUnits> element is present... that means the instance document has unit types and/or
      // units of measure we need to learn about

      CComPtr<IUnitTypes> objUnitTypes;
      pUnitServer->get_UnitTypes(&objUnitTypes);
      
      // Add Units of Measure for all <ExtendedUnits><UnitOfMeasure> elements
      OpenBridgeML::Units::ExtendedUnitsType::UnitOfMeasure_sequence& unitsOfMeasure(extendedUnits->UnitOfMeasure());
      OpenBridgeML::Units::ExtendedUnitsType::UnitOfMeasure_sequence::iterator iter(unitsOfMeasure.begin());
      OpenBridgeML::Units::ExtendedUnitsType::UnitOfMeasure_sequence::iterator end(unitsOfMeasure.end());
      for ( ; iter != end; iter++ )
      {
         OpenBridgeML::Units::UnitOfMeasureExType& unitOfMeasure(*iter);
         CComPtr<IUnitType> unitType;
         hr = objUnitTypes->get_Item(CComVariant(T2BSTR(unitOfMeasure.UnitType().c_str())),&unitType);
         ATLASSERT(SUCCEEDED(hr)); // if this fires, the unit type is invalid

         CComPtr<IUnits> units;
         unitType->get_Units(&units);

         Float64 pre = 0.0;
         if ( unitOfMeasure.PreConvertTerm().present() )
            pre = unitOfMeasure.PreConvertTerm().get();

         Float64 post = 0.0;
         if ( unitOfMeasure.PostConvertTerm().present() )
            post = unitOfMeasure.PostConvertTerm().get();

         CComPtr<IUnit> unit;
         hr = units->Add(T2BSTR(unitOfMeasure.name().c_str()),
                         pre,
                         unitOfMeasure.ConversionFactor(),
                         post,
                         GetWBFLUnitSystemType(unitOfMeasure.UnitSystem()),
                         &unit);
         ATLASSERT(SUCCEEDED(hr)); // if this fires, then a unit of measure with this name is already defined
      }

      // Add Unit Types and Units of Measure for all <ExtendedUnits><UnitTypes> elements
      OpenBridgeML::Units::ExtendedUnitsType::UnitTypes_optional& UnitTypes(extendedUnits->UnitTypes());
      if ( UnitTypes.present() )
      {
         // there are custom unit types... loop over each <UnitType>
         OpenBridgeML::Units::ExtendedUnitTypeType::UnitType_sequence::iterator iter(extendedUnits->UnitTypes()->UnitType().begin());
         OpenBridgeML::Units::ExtendedUnitTypeType::UnitType_sequence::iterator end(extendedUnits->UnitTypes()->UnitType().end());
         for ( ; iter != end; iter++ )
         {
            OpenBridgeML::Units::UnitTypeType& UnitType(*iter);

            // Create a new WBFL Unit Type
            CComPtr<IUnitType> objUnitType;
            objUnitTypes->Add(T2BSTR(UnitType.name().c_str()),
                              UnitType.mass(),
                              UnitType.length(),
                              UnitType.time(),
                              UnitType.temperature(),
                              UnitType.angle(),
                              &objUnitType);

            CComPtr<IUnits> units;
            objUnitType->get_Units(&units);

            // Add units of measure
            OpenBridgeML::Units::UnitTypeType::UnitOfMeasure_sequence::iterator umIter(UnitType.UnitOfMeasure().begin());
            OpenBridgeML::Units::UnitTypeType::UnitOfMeasure_sequence::iterator umEnd(UnitType.UnitOfMeasure().end());
            for ( ; umIter != umEnd; umIter++ )
            {
               OpenBridgeML::Units::UnitOfMeasureType& unitOfMeasure(*umIter);

               Float64 pre = 0.0;
               if ( unitOfMeasure.PreConvertTerm().present() )
                  pre = unitOfMeasure.PreConvertTerm().get();

               Float64 post = 0.0;
               if ( unitOfMeasure.PostConvertTerm().present() )
                  post = unitOfMeasure.PostConvertTerm().get();

               CComPtr<IUnit> objUnit;
               units->Add(T2BSTR(unitOfMeasure.name().c_str()),
                          pre,
                          unitOfMeasure.ConversionFactor(),
                          post,
                          GetWBFLUnitSystemType(unitOfMeasure.UnitSystem()),
                          &objUnit);
            }
         }
      }
   }

   OpenBridgeML::Units::UnitsDeclarationType::ConsistentUnits_optional& consistentUnits(pDeclaration->ConsistentUnits());
   if ( consistentUnits.present() )
   {
      // The <ConsistantUnits> element is present
      CComBSTR bstrMass(   T2BSTR(consistentUnits->mass().c_str())        );
      CComBSTR bstrLength( T2BSTR(consistentUnits->length().c_str())      );
      CComBSTR bstrTime(   T2BSTR(consistentUnits->time().c_str())        );
      CComBSTR bstrTemp(   T2BSTR(consistentUnits->temperature().c_str()) );
      CComBSTR bstrAngle(  T2BSTR(consistentUnits->angle().c_str())       );
      hr = pUnitServer->SetBaseUnits(bstrMass,bstrLength,bstrTime,bstrTemp,bstrAngle);
      ATLASSERT(SUCCEEDED(hr)); // if this fires, one of the unit of measure is invalid
   }

   return TRUE;
}

template <class U>
void ConvertBetweenBaseUnitsT(U& unitValueType,LPCTSTR unitTypeName,IUnitServer* pFromUnitServer,IUnitServer* pToUnitServer)
{
   USES_CONVERSION;
   Float64 value = unitValueType;

   if ( unitValueType.unit().present() )
   {
      // The unit of measure for ModE was specified in the instance document

      // Convert the value from the specified unit of measure to the
      // consistent unit of measure defined in <UnitsDeclaration> in the instance document
      CComQIPtr<IUnitConvert> fromUnitConverter(pFromUnitServer);
      HRESULT hr = fromUnitConverter->ConvertToBaseUnits(value,T2BSTR(unitValueType.unit().get().c_str()),&value);
      ATLASSERT(SUCCEEDED(hr)); // if this fires, then the unit of measure was not valid

      unitValueType.unit().reset(); // no longer using the specified unit of measure
   }

   CComPtr<IUnitTypes> unitTypes;
   pFromUnitServer->get_UnitTypes(&unitTypes);
   CComPtr<IUnitType> unitTypePressure;
   unitTypes->get_Item(CComVariant(CComBSTR(unitTypeName)),&unitTypePressure);
   CComPtr<IUnits> pressureUnits;
   unitTypePressure->get_Units(&pressureUnits);
   CComPtr<IUnit> pressureUnit;
   pressureUnits->get_Item(CComVariant(0),&pressureUnit);

   CComQIPtr<IUnitConvert2> fromUnitConverter(pFromUnitServer);
   CComQIPtr<IUnitConvert2> toUnitConverter(pToUnitServer);

   fromUnitConverter->ConvertFromBaseUnits(value,pressureUnit,&value); // convert from base units to a neutral unit
   toUnitConverter->ConvertToBaseUnits(value,pressureUnit,&value); // convert from the neutral unit to our base units

   unitValueType = value;
}

#define IMPLEMENT_BASE_UNIT_CONVERTER(V,S) \
void ConvertBetweenBaseUnits(OpenBridgeML::Units::##V& unitValueType,IUnitServer* pFromUnitServer,IUnitServer* pToUnitServer) \
{ \
   ConvertBetweenBaseUnitsT<OpenBridgeML::Units::##V>(unitValueType,_T(S),pFromUnitServer,pToUnitServer);\
}

IMPLEMENT_BASE_UNIT_CONVERTER(MassValueType, "Mass");
IMPLEMENT_BASE_UNIT_CONVERTER(LengthValueType, "Length");
IMPLEMENT_BASE_UNIT_CONVERTER(TimeValueType, "Time");
IMPLEMENT_BASE_UNIT_CONVERTER(TemperatureValueType, "Temperature");
IMPLEMENT_BASE_UNIT_CONVERTER(AngleValueType, "Angle");
IMPLEMENT_BASE_UNIT_CONVERTER(MassPerLengthValueType, "MassPerLength");
IMPLEMENT_BASE_UNIT_CONVERTER(Length2ValueType, "Length2");
IMPLEMENT_BASE_UNIT_CONVERTER(Length3ValueType, "Length3");
IMPLEMENT_BASE_UNIT_CONVERTER(Length4ValueType, "Length4");
IMPLEMENT_BASE_UNIT_CONVERTER(PressureValueType, "Pressure");
IMPLEMENT_BASE_UNIT_CONVERTER(UnitWeightValueType, "ValueWeight");
IMPLEMENT_BASE_UNIT_CONVERTER(DensityValueType, "Density");
IMPLEMENT_BASE_UNIT_CONVERTER(ForceValueType, "Force");
IMPLEMENT_BASE_UNIT_CONVERTER(ForcePerLengthValueType, "ForcePerLength");
IMPLEMENT_BASE_UNIT_CONVERTER(MomentValueType, "Moment");
IMPLEMENT_BASE_UNIT_CONVERTER(ThermalExpansionValueType, "ThermalExpansion");
