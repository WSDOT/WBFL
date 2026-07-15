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
#include <Units\DynamicPhysical.h>
#include <System\Checks.h>
#include <MathEx.h>


using namespace WBFL::Units;

#if defined _DEBUG
namespace
{
   // Nesting-safe suppression counter for SuppressDuplicateDimensionWarningScope. Zero (the default) means
   // the diagnostic is active; non-zero means it's suppressed.
   //
   // TODO: this counter, and SuppressDuplicateDimensionWarningScope in DynamicPhysical.h, exist only as a
   // workaround for WBFLUnitServer's facade over WBFLUnits. Remove both once WBFLUnitServer is obsoleted
   // and removed from WBFL.
   int g_SuppressDuplicateDimensionWarningCount = 0;

   struct KnownDimension
   {
      Float64 Mass;
      Float64 Length;
      Float64 Time;
      Float64 Temperature;
      Float64 Angle;
      LPCTSTR Name;
   };

   // Mirrors the DECLARE_PHYSICAL_UNIT/DECLARE_PHYSICALEX_UNIT declarations in PhysicalT.h. The exponents
   // there are scaled by 10 (to allow fractional dimensions); the values here are the real, unscaled
   // exponents, matching what DynamicPhysical/MassDim() etc. and the PhysicalT dimension accessors return.
   // Area/Volume/Stress/AreaPerLength are aliases in PhysicalT.h (Length2/Length3/Pressure/Length,
   // respectively), so they don't need separate entries here.
   const KnownDimension g_KnownDimensions[] =
   {
      {  1,    0,    0,  0,  0, _T("Mass") },
      {  0,    1,    0,  0,  0, _T("Length") },
      {  0,    0,    1,  0,  0, _T("Time") },
      {  0,    0,    0,  1,  0, _T("Temperature") },
      {  0,    0,    0,  0,  1, _T("Angle") },
      {  0,    1,   -2,  0,  0, _T("Acceleration") },
      {  1,   -1,    0,  0,  0, _T("MassPerLength") },
      {  0,    2,    0,  0,  0, _T("Length2 (Area)") },
      {  0,    3,    0,  0,  0, _T("Length3 (Volume)") },
      {  0,    4,    0,  0,  0, _T("Length4") },
      {  1,   -1,   -2,  0,  0, _T("Pressure (Stress)") },
      {  1,   -3,   -3,  0,  0, _T("UnitWeight") },
      {  1,   -3,    0,  0,  0, _T("Density") },
      {  1,    1,   -2,  0,  0, _T("Force") },
      {  1,    0,   -2,  0,  0, _T("ForcePerLength") },
      {  1,    2,   -2,  0,  0, _T("Moment") },
      {  1,    2,   -2,  0, -1, _T("MomentPerAngle") },
      { 0.5, -0.5,   -1,  0,  0, _T("SqrtPressure") },
      {  0,   -1,    0,  0,  0, _T("PerLength") },
      {  1,    3,   -2,  0,  0, _T("ForceLength2") },
      {  0,    1,   -1,  0,  0, _T("Velocity") },
   };
}
#endif // _DEBUG

DynamicPhysical::DynamicPhysical(Float64 m, Float64 l, Float64 t, Float64 k, Float64 a, Float64 cf, const std::_tstring& tag) :
DynamicPhysical(m, l, t, k, a, 0.0, cf, 0.0, tag)
{
}

DynamicPhysical::DynamicPhysical(Float64 m, Float64 l, Float64 t, Float64 k, Float64 a, Float64 preTerm, Float64 cf, Float64 postTerm, const std::_tstring& tag) :
m_Mass(m), m_Length(l), m_Time(t), m_Temperature(k), m_Angle(a),
m_PreTerm(preTerm), m_ConvFactor(cf), m_PostTerm(postTerm), m_UnitTag(tag)
{
   CHECK(cf != 0.0);

#if defined _DEBUG
   if (g_SuppressDuplicateDimensionWarningCount == 0)
   {
      for (const auto& known : g_KnownDimensions)
      {
         bool bMatch = (m_Mass == known.Mass && m_Length == known.Length && m_Time == known.Time && m_Temperature == known.Temperature && m_Angle == known.Angle);
         WARN(bMatch, _T("DynamicPhysical \"") << m_UnitTag.c_str() << _T("\" has the same dimensionality as the compile-time unit type WBFL::Units::") << known.Name
            << _T(". Consider using that type, and the Measure catalog, instead of DynamicPhysical."));
         if (bMatch)
         {
            break;
         }
      }
   }
#endif // _DEBUG
}

#if defined _DEBUG
DynamicPhysical::SuppressDuplicateDimensionWarningScope::SuppressDuplicateDimensionWarningScope()
{
   ++g_SuppressDuplicateDimensionWarningCount;
}

DynamicPhysical::SuppressDuplicateDimensionWarningScope::~SuppressDuplicateDimensionWarningScope()
{
   --g_SuppressDuplicateDimensionWarningCount;
}
#endif // _DEBUG

bool DynamicPhysical::operator==(const DynamicPhysical& other) const
{
   return m_Mass == other.m_Mass
      && m_Length == other.m_Length
      && m_Time == other.m_Time
      && m_Temperature == other.m_Temperature
      && m_Angle == other.m_Angle
      && m_PreTerm == other.m_PreTerm
      && m_ConvFactor == other.m_ConvFactor
      && m_PostTerm == other.m_PostTerm
      && m_UnitTag == other.m_UnitTag;
}

Float64 DynamicPhysical::ConvertFrom(Float64 value) const
{
   return (value + m_PreTerm) * m_ConvFactor + m_PostTerm;
}

Float64 DynamicPhysical::ConvertTo(Float64 value) const
{
   return (value - m_PostTerm) / m_ConvFactor - m_PreTerm;
}

bool DynamicPhysical::IsSameDimension(const DynamicPhysical& other) const
{
   return m_Mass == other.m_Mass
      && m_Length == other.m_Length
      && m_Time == other.m_Time
      && m_Temperature == other.m_Temperature
      && m_Angle == other.m_Angle;
}

Float64 DynamicPhysical::GetPreTerm() const
{
   return m_PreTerm;
}

Float64 DynamicPhysical::GetConvFactor() const
{
   return m_ConvFactor;
}

Float64 DynamicPhysical::GetPostTerm() const
{
   return m_PostTerm;
}

const std::_tstring& DynamicPhysical::UnitTag() const
{
   return m_UnitTag;
}

Float64 DynamicPhysical::MassDim() const
{
   return m_Mass;
}

Float64 DynamicPhysical::LengthDim() const
{
   return m_Length;
}

Float64 DynamicPhysical::TimeDim() const
{
   return m_Time;
}

Float64 DynamicPhysical::TemperatureDim() const
{
   return m_Temperature;
}

Float64 DynamicPhysical::AngleDim() const
{
   return m_Angle;
}

#if defined _DEBUG
bool DynamicPhysical::AssertValid() const
{
   // At least one of the dimensionalities must be non-zero
   if ( m_Mass        == 0 &&
        m_Length      == 0 &&
        m_Time        == 0 &&
        m_Temperature == 0 &&
        m_Angle       == 0 )
   {
      return false;
   }

   // The conversion factor must be non-zero.
   if ( IsZero( m_ConvFactor, 1.0e-24 ))
      return false;

   return true;
}

void DynamicPhysical::Dump(WBFL::Debug::LogContext& os) const
{
   os << m_UnitTag.c_str() << WBFL::Debug::endl;
   os << '\t' << "Dimensionality : (";
   os << m_Mass << ",";
   os << m_Length << ",";
   os << m_Time << ",";
   os << m_Temperature << ",";
   os << m_Angle;
   os << ")" << WBFL::Debug::endl;
   os << '\t' << "Pre Term    : " << m_PreTerm << WBFL::Debug::endl;
   os << '\t' << "Conv Factor : " << m_ConvFactor << WBFL::Debug::endl;
   os << '\t' << "Post Term   : " << m_PostTerm << WBFL::Debug::endl;
}
#endif // _DEBUG
