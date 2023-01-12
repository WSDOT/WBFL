///////////////////////////////////////////////////////////////////////
// UnitMgt - Service for managing display units indirectly
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <UnitMgt\UnitMgtExp.h>
#include <System\NumericFormatTool.h>
#include <UnitMgt\IndirectMeasure.h>

class UNITMGTCLASS arvPhysicalConverter: public sysNumericFormatTool
{
public:
   arvPhysicalConverter(Format format = Automatic, Uint16 width = 0, Uint16 precision = 0) :
      sysNumericFormatTool(format,width,precision)
      {
      }

   virtual Float64 Convert(Float64 value) const = 0;
   virtual std::_tstring UnitTag() const  = 0;
};

// a template class for printing out physical values
template <class T>
class UnitValueNumericalFormatToolT : public arvPhysicalConverter
{
public:
   // built to take a unitmgtIndirectMeasureDataT
   UnitValueNumericalFormatToolT(const T& umd) :
      arvPhysicalConverter(umd.Format, umd.Width, umd.Precision),
      m_rT(umd)
      {
      }

   std::_tstring AsString(Float64 val) const
   {
      if ( m_rT.Tol/10. < fabs(val) )
      {
         return arvPhysicalConverter::AsString(val);
      }
      else
      {
         return arvPhysicalConverter::AsString(0.0);
      }
   }

   Float64 Convert(Float64 value) const
   {
      return ::ConvertFromSysUnits(value, m_rT.UnitOfMeasure);
   }

   std::_tstring UnitTag() const
   {
      return m_rT.UnitOfMeasure.UnitTag();
   }
private:
   const T&             m_rT;
};

// a template class for printing out scalar values
template <class T>
class ScalarFormatToolT : public arvPhysicalConverter
{
public:
   // built to take a unitmgtIndirectMeasureDataT
   ScalarFormatToolT(const T& umd) :
      arvPhysicalConverter(umd.Format,umd.Width,umd.Precision)
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

UNITMGTTPL ScalarFormatToolT<unitmgtScalar>;
UNITMGTTPL UnitValueNumericalFormatToolT<unitmgtLengthData>;
UNITMGTTPL UnitValueNumericalFormatToolT<unitmgtMomentData>;
UNITMGTTPL UnitValueNumericalFormatToolT<unitmgtLengthData>;
UNITMGTTPL UnitValueNumericalFormatToolT<unitmgtAngleData>;
UNITMGTTPL UnitValueNumericalFormatToolT<unitmgtStressData>;
UNITMGTTPL UnitValueNumericalFormatToolT<unitmgtForceData>;
UNITMGTTPL UnitValueNumericalFormatToolT<unitmgtForceData>;
UNITMGTTPL UnitValueNumericalFormatToolT<unitmgtTimeData>;
UNITMGTTPL UnitValueNumericalFormatToolT<unitmgtLength2Data>;
UNITMGTTPL UnitValueNumericalFormatToolT<unitmgtLength3Data>;
UNITMGTTPL UnitValueNumericalFormatToolT<unitmgtLength4Data>;
UNITMGTTPL UnitValueNumericalFormatToolT<unitmgtPerLengthData>;

typedef ScalarFormatToolT<unitmgtScalar>          ScalarTool;
typedef UnitValueNumericalFormatToolT<unitmgtLengthData>    LengthTool;
typedef UnitValueNumericalFormatToolT<unitmgtMomentData>    MomentTool;
typedef UnitValueNumericalFormatToolT<unitmgtLengthData>    DeflectionTool;
typedef UnitValueNumericalFormatToolT<unitmgtAngleData>     RotationTool;
typedef UnitValueNumericalFormatToolT<unitmgtStressData>    StressTool;
typedef UnitValueNumericalFormatToolT<unitmgtForceData>     ShearTool;
typedef UnitValueNumericalFormatToolT<unitmgtForceData>     ForceTool;
typedef UnitValueNumericalFormatToolT<unitmgtTimeData>      TimeTool;
typedef UnitValueNumericalFormatToolT<unitmgtLength2Data>   AreaTool;
typedef UnitValueNumericalFormatToolT<unitmgtLength3Data>   SectionModulusTool;
typedef UnitValueNumericalFormatToolT<unitmgtLength4Data>   MomentOfInertiaTool;
typedef UnitValueNumericalFormatToolT<unitmgtPerLengthData> CurvatureTool;
typedef UnitValueNumericalFormatToolT<unitmgtForceData>   AxialTool;
