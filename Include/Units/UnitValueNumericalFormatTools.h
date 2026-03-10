///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
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

#include <Units\UnitsExp.h>
#include <Units\IndirectMeasure.h>
#include <Units\Convert.h>
#include <System\NumericFormatTool.h>

namespace WBFL
{
   namespace Units
   {
      /// Base class for indirect conversion of physical units of measure
      class UNITSCLASS PhysicalConverter: public WBFL::System::NumericFormatTool
      {
      public:
         PhysicalConverter(Format format = Format::Automatic, Uint16 width = 0, Uint16 precision = 0) :
            WBFL::System::NumericFormatTool(format,width,precision)
            {
            }

         virtual Float64 Convert(Float64 value) const = 0;
         virtual std::_tstring UnitTag() const  = 0;
      };

      /// A template class for printing out physical values
      template <class T>
      class UnitValueNumericalFormatToolT : public PhysicalConverter
      {
      public:
         // built to take a IndirectMeasureDataT
         UnitValueNumericalFormatToolT(const T& umd) :
            PhysicalConverter(umd.Format, umd.Width, umd.Precision),
            m_rT(umd)
            {
            }

         std::_tstring AsString(Float64 val) const
         {
            if ( m_rT.Tol/10. < fabs(val) )
            {
               return PhysicalConverter::AsString(val);
            }
            else
            {
               return PhysicalConverter::AsString(0.0);
            }
         }

         Float64 Convert(Float64 value) const
         {
            return WBFL::Units::ConvertFromSysUnits(value, m_rT.UnitOfMeasure);
         }

         std::_tstring UnitTag() const
         {
            return m_rT.UnitOfMeasure.UnitTag();
         }

         const T& GetType() const { return m_rT; }

      private:
         const T&             m_rT;
      };

      /// a template class for printing out scalar values
      template <class T>
      class ScalarFormatToolT : public PhysicalConverter
      {
      public:
         // built to take a IndirectMeasureDataT
         ScalarFormatToolT(const T& umd) :
            PhysicalConverter(umd.Format,umd.Width,umd.Precision)
            {
            }

         Float64 Convert(Float64 value) const
         {
            return value;
         }

         std::_tstring UnitTag() const
         {
            return _T("");
         }
      };

      UNITSTPL ScalarFormatToolT<ScalarData>;
      UNITSTPL UnitValueNumericalFormatToolT<LengthData>;
      UNITSTPL UnitValueNumericalFormatToolT<MomentData>;
      UNITSTPL UnitValueNumericalFormatToolT<LengthData>;
      UNITSTPL UnitValueNumericalFormatToolT<AngleData>;
      UNITSTPL UnitValueNumericalFormatToolT<StressData>;
      UNITSTPL UnitValueNumericalFormatToolT<ForceData>;
      UNITSTPL UnitValueNumericalFormatToolT<ForceData>;
      UNITSTPL UnitValueNumericalFormatToolT<TimeData>;
      UNITSTPL UnitValueNumericalFormatToolT<Length2Data>;
      UNITSTPL UnitValueNumericalFormatToolT<Length3Data>;
      UNITSTPL UnitValueNumericalFormatToolT<Length4Data>;
      UNITSTPL UnitValueNumericalFormatToolT<PerLengthData>;

      using ScalarTool = ScalarFormatToolT<ScalarData>;
      using LengthTool = UnitValueNumericalFormatToolT<LengthData>;
      using MomentTool = UnitValueNumericalFormatToolT<MomentData>;
      using DeflectionTool = UnitValueNumericalFormatToolT<LengthData>;
      using RotationTool = UnitValueNumericalFormatToolT<AngleData>;
      using StressTool = UnitValueNumericalFormatToolT<StressData>;
      using ShearTool = UnitValueNumericalFormatToolT<ForceData>;
      using ForceTool = UnitValueNumericalFormatToolT<ForceData>;
      using TimeTool = UnitValueNumericalFormatToolT<TimeData>;
      using AreaTool = UnitValueNumericalFormatToolT<Length2Data>;
      using SectionModulusTool = UnitValueNumericalFormatToolT<Length3Data>;
      using MomentOfInertiaTool = UnitValueNumericalFormatToolT<Length4Data>;
      using CurvatureTool = UnitValueNumericalFormatToolT<PerLengthData>;
      using AxialTool = UnitValueNumericalFormatToolT<ForceData>;
   };
};
