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
#include <Units\IndirectMeasure.h>
#include <Units\Convert.h>
#include <System\NumericFormatTool.h>

namespace WBFL
{
   namespace Units
   {
      /// Base class for indirect conversion of physical units of measure: converts a value from system
      /// units into some target unit of measure and formats it as a text string with its unit tag.
      class UNITSCLASS PhysicalConverter: public WBFL::System::NumericFormatTool
      {
      public:
         /// Constructs a converter with the given numeric notation, field width, and precision (see
         /// WBFL::System::NumericFormatTool).
         PhysicalConverter(Format format = Format::Automatic, Uint16 width = 0, Uint16 precision = 0) :
            WBFL::System::NumericFormatTool(format,width,precision)
            {
            }

         /// Converts value, expressed in system units, to this converter's target unit of measure.
         virtual Float64 Convert(Float64 value) const = 0;

         /// Returns the unit tag of this converter's target unit of measure.
         virtual std::_tstring UnitTag() const  = 0;
      };

      /// A template class for converting and formatting physical values, parameterized on an
      /// IndirectMeasureDataT<T> display profile (e.g. LengthData, ForceData - see IndirectMeasure.h).
      template <class T>
      class UnitValueNumericalFormatToolT : public PhysicalConverter
      {
      public:
         /// Constructs a converter using the unit of measure, tolerance, width, precision, and notation
         /// defined by umd (typically one of IndirectMeasure's fields, e.g. someIndirectMeasure.Stress).
         UnitValueNumericalFormatToolT(const T& umd) :
            PhysicalConverter(umd.Format, umd.Width, umd.Precision),
            m_rT(umd)
            {
            }

         /// Converts val from system units to the target unit of measure and formats it as a tagged text
         /// string. Values whose magnitude, in the target unit, is within one tenth of umd's Tol are
         /// formatted as zero.
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

         /// Converts value, expressed in system units, to the target unit of measure.
         Float64 Convert(Float64 value) const
         {
            return WBFL::Units::ConvertFromSysUnits(value, m_rT.UnitOfMeasure);
         }

         /// Returns the unit tag of the target unit of measure.
         std::_tstring UnitTag() const
         {
            return m_rT.UnitOfMeasure.UnitTag();
         }

         /// Returns the IndirectMeasureDataT<T> display profile this converter was constructed with.
         const T& GetType() const { return m_rT; }

      private:
         const T&             m_rT;
      };

      /// A template class for formatting dimensionless scalar values, parameterized on a ScalarData or
      /// similar display profile. Unlike UnitValueNumericalFormatToolT, Convert() is the identity (there is
      /// no unit of measure to convert to) and UnitTag() is always empty.
      template <class T>
      class ScalarFormatToolT : public PhysicalConverter
      {
      public:
         /// Constructs a formatter using the width, precision, and notation defined by umd (typically
         /// IndirectMeasure::Scalar or IndirectMeasure::Percentage).
         ScalarFormatToolT(const T& umd) :
            PhysicalConverter(umd.Format,umd.Width,umd.Precision)
            {
            }

         /// Returns value unchanged; scalar values have no unit of measure to convert.
         Float64 Convert(Float64 value) const
         {
            return value;
         }

         /// Returns an empty string; scalar values have no unit tag.
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

      using ScalarTool = ScalarFormatToolT<ScalarData>;                    ///< Formats dimensionless scalar values (see IndirectMeasure::Scalar)
      using LengthTool = UnitValueNumericalFormatToolT<LengthData>;        ///< Converts/formats length values
      using MomentTool = UnitValueNumericalFormatToolT<MomentData>;       ///< Converts/formats moment values
      using DeflectionTool = UnitValueNumericalFormatToolT<LengthData>;    ///< Converts/formats deflection values (a Length quantity)
      using RotationTool = UnitValueNumericalFormatToolT<AngleData>;       ///< Converts/formats rotation/angle values
      using StressTool = UnitValueNumericalFormatToolT<StressData>;       ///< Converts/formats stress values
      using ShearTool = UnitValueNumericalFormatToolT<ForceData>;         ///< Converts/formats shear force values (a Force quantity)
      using ForceTool = UnitValueNumericalFormatToolT<ForceData>;         ///< Converts/formats general force values
      using TimeTool = UnitValueNumericalFormatToolT<TimeData>;           ///< Converts/formats time duration values
      using AreaTool = UnitValueNumericalFormatToolT<Length2Data>;        ///< Converts/formats area values
      using SectionModulusTool = UnitValueNumericalFormatToolT<Length3Data>; ///< Converts/formats section modulus values
      using MomentOfInertiaTool = UnitValueNumericalFormatToolT<Length4Data>; ///< Converts/formats moment of inertia values
      using CurvatureTool = UnitValueNumericalFormatToolT<PerLengthData>;  ///< Converts/formats curvature values
      using AxialTool = UnitValueNumericalFormatToolT<ForceData>;         ///< Converts/formats axial force values (a Force quantity)
   };
};
