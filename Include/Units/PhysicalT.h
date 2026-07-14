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

#include <string>
#include <System\Checks.h>
#include <System\LogContext.h>
#include <MathEx.h>

namespace WBFL
{
   namespace Units
   {

   /// Template class that defined a physical unit of measure such as length, time, pressure, etc.
   /// The template parameters m, l, t, k, and a define the dimensionality of the physical unit where
   /// m = mass, l = length, t = time, k = temperature, and a = angle.
   /// 
   /// Dimensionality is defined with the 10 times the unit exponent. For example, length
   /// has a length dimensionality of 1 so an instance of this template for length would be
   /// PhysicalT<0,10,0,0,0>. Acceleration is Length*Time^-2 (m/s/s). The template instance
   /// would be PhysicalT<0,10,-20,0,0>
   /// 
   /// Specific units of measures, such as Feet, Kips, Newton per square meter, are defined by
   /// their conversion factor and "tag". Conversion factors must convert values to the
   /// fundamental units KMSCR (Kilogram, Meter, Second, Celsius, Radian)
   template <Int16 m, Int16 l, Int16 t, Int16 k, Int16 a>
   class PhysicalT
   {
   public:
      /// Constructs a unit of measure with conversion equation value*cf, tagged tag.
      PhysicalT( Float64 cf, const std::_tstring& tag) :
         m_ConvFactor( cf ), m_UnitTag( tag )
         {
            CHECK( cf != 0.0 );
         }

      virtual ~PhysicalT()
      {
      }

      /// Returns true if other has the same conversion factor and unit tag as this unit of measure.
      /// Dimensionality is not compared since it is guaranteed to be equal by the compiler (m,l,t,k,a are
      /// template parameters, so other's C++ type already implies matching dimensionality).
      bool operator==(const PhysicalT<m, l, t, k, a>& other) const { return m_ConvFactor == other.m_ConvFactor && m_UnitTag == other.m_UnitTag; }

      /// Converts value, expressed in this unit of measure, to the fundamental unit implied by its
      /// conversion equation.
      virtual Float64 ConvertFrom(Float64 value) const { return value * m_ConvFactor; };

      /// Converts value, expressed in the fundamental unit implied by this unit's conversion equation, to
      /// this unit of measure.
      virtual Float64 ConvertTo(Float64 value) const { return value / m_ConvFactor; }

      /// Returns the conversion factor.
      Float64 GetConvFactor() const { return m_ConvFactor; }

      /// Returns the unit tag.
      const std::_tstring& UnitTag() const { return m_UnitTag; }

      /// Returns the mass dimensionality.
      static Float64 MassDim() { return m/10.; }

      /// Returns the length dimensionality.
      static Float64 LengthDim() { return l/10.; }

      /// Returns the time dimensionality.
      static Float64 TimeDim() { return t/10.; }

      /// Returns the temperature dimensionality.
      static Float64 TemperatureDim() { return k/10.; }

      /// Returns the angle dimensionality.
      static Float64 AngleDim() { return a/10.; }

   #if defined _DEBUG
      virtual bool AssertValid() const
      {
         // At least one of the dimensionalities must be non-zero
         if ( MassDim()        == 0 &&
              LengthDim()      == 0 &&
              TimeDim()        == 0 &&
              TemperatureDim() == 0 &&
              AngleDim()       == 0 )
         {
            return false;
         }

         // The conversion factor must be non-zero.
         if ( IsZero( m_ConvFactor, 1.0e-24 ))
            return false;

         return true;
      }

      virtual void Dump(WBFL::Debug::LogContext& os) const
      {
         os << m_UnitTag.c_str() << WBFL::Debug::endl;
         os << '\t' << "Dimensionality : (";
         os << MassDim() << ",";
         os << LengthDim() << ",";
         os << TimeDim() << ",";
         os << TemperatureDim() << ",";
         os << AngleDim();
         os << ")" << WBFL::Debug::endl;
         os << '\t' << "Conv Factor : " << m_ConvFactor << WBFL::Debug::endl;
      }
   #endif // _DEBUG

   private:
      Float64 m_ConvFactor;
      std::_tstring m_UnitTag;
   };

   /// Template class that defined an extended physical unit of measure that requires a pre and post-term
   /// for the unit conversion
   template <Int16 m, Int16 l, Int16 t, Int16 k, Int16 a>
   class PhysicalExT : public PhysicalT<m,l,t,k,a>
   {
   public:
      /// Constructs a unit of measure with the full conversion equation (value+pre)*cf+post, tagged tag.
      PhysicalExT(Float64 pre, Float64 cf, Float64 post, const std::_tstring& tag) :
         PhysicalT<m,l,t,k,a>(cf,tag),
         m_PreTerm(pre), m_PostTerm(post)
      {
      }

      /// Converts value, expressed in this unit of measure, to the fundamental unit implied by its
      /// conversion equation.
      virtual Float64 ConvertFrom(Float64 value) const override { return (value + m_PreTerm) * PhysicalT<m, l, t, k, a>::GetConvFactor() + m_PostTerm; }

      /// Converts value, expressed in the fundamental unit implied by this unit's conversion equation, to
      /// this unit of measure.
      virtual Float64 ConvertTo(Float64 value) const override { return (value - m_PostTerm) / PhysicalT<m, l, t, k, a>::GetConvFactor() - m_PreTerm; }

      /// Returns the pre-addition term.
      Float64 GetPreTerm() const { return m_PreTerm; }

      /// Returns the post-addition term.
      Float64 GetPostTerm() const { return m_PostTerm; }

#if defined _DEBUG
      virtual void Dump(WBFL::Debug::LogContext& os) const
      {
         __super::Dump(os);
         os << '\t' << "Pre Term    : " << m_PreTerm << WBFL::Debug::endl;
         os << '\t' << "Post Term   : " << m_PostTerm << WBFL::Debug::endl;
      }
#endif // _DEBUG

   private:
      Float64 m_PreTerm;
      Float64 m_PostTerm;
   };

   /// Explicitly instantiates and exports PhysicalT<m,l,t,k,a>, and declares name as an alias for it. Use
   /// this to declare a new compile-time-dimensioned physical quantity that does not require a pre- or
   /// post-addition term in its conversion equation (see DECLARE_PHYSICALEX_UNIT for quantities, such as
   /// Temperature, that do).
   #define DECLARE_PHYSICAL_UNIT(m,l,t,k,a,name) \
      UNITSTPL PhysicalT<m,l,t,k,a>; \
      using name = PhysicalT<m,l,t,k,a>

   /// Explicitly instantiates and exports PhysicalExT<m,l,t,k,a>, and declares name as an alias for it. Use
   /// this instead of DECLARE_PHYSICAL_UNIT for quantities whose conversion equation requires a pre- and
   /// post-addition term (e.g. Temperature, where Fahrenheit-to-Celsius is not a pure scale factor).
   #define DECLARE_PHYSICALEX_UNIT(m,l,t,k,a,name) \
      UNITSTPL PhysicalExT<m,l,t,k,a>; \
      using name = PhysicalExT<m,l,t,k,a>

   // Basic Physical Units
   DECLARE_PHYSICAL_UNIT( 10,  0,  0,  0,  0, Mass );          ///< Mass
   DECLARE_PHYSICAL_UNIT(  0, 10,  0,  0,  0, Length );        ///< Length
   DECLARE_PHYSICAL_UNIT(  0,  0, 10,  0,  0, Time );          ///< Time
   DECLARE_PHYSICALEX_UNIT(  0,  0,  0, 10,  0, Temperature ); ///< Temperature
   DECLARE_PHYSICAL_UNIT(  0,  0,  0,  0, 10, Angle );         ///< Angle

   // Complex Physical Units
   DECLARE_PHYSICAL_UNIT(  0, 10,-20,  0,  0, Acceleration );   ///< Length/Time^2
   DECLARE_PHYSICAL_UNIT( 10,-10,  0,  0,  0, MassPerLength );  ///< Mass/Length
   DECLARE_PHYSICAL_UNIT(  0, 20,  0,  0,  0, Length2 );        ///< Length^2 (area)
   DECLARE_PHYSICAL_UNIT(  0, 30,  0,  0,  0, Length3 );        ///< Length^3 (volume)
   DECLARE_PHYSICAL_UNIT(  0, 40,  0,  0,  0, Length4 );        ///< Length^4 (moment of inertia/section modulus)
   DECLARE_PHYSICAL_UNIT( 10,-10,-20,  0,  0, Pressure );       ///< Mass/(Length*Time^2) (pressure/stress)
   DECLARE_PHYSICAL_UNIT( 10,-30,-30,  0,  0, UnitWeight );     ///< Mass/(Length^3*Time^3) (weight density)
   DECLARE_PHYSICAL_UNIT( 10,-30,  0,  0,  0, Density );        ///< Mass/Length^3
   DECLARE_PHYSICAL_UNIT( 10, 10,-20,  0,  0, Force );          ///< Mass*Length/Time^2
   DECLARE_PHYSICAL_UNIT( 10,  0,-20,  0,  0, ForcePerLength ); ///< Force/Length
   DECLARE_PHYSICAL_UNIT( 10, 20,-20,  0,  0, Moment );         ///< Force*Length
   DECLARE_PHYSICAL_UNIT( 10, 20,-20,  0,-10, MomentPerAngle ); ///< Moment/Angle (rotational stiffness)
   DECLARE_PHYSICAL_UNIT(  5, -5,-10,  0,  0, SqrtPressure );   ///< sqrt(Pressure), used in concrete cracking/rupture-modulus formulas
   DECLARE_PHYSICAL_UNIT(  0,-10,  0,  0,  0, PerLength );      ///< 1/Length (curvature)
   DECLARE_PHYSICAL_UNIT( 10, 30,-20,  0,  0, ForceLength2 );   ///< Force*Length^2, used for flexural rigidity (E*I)
   DECLARE_PHYSICAL_UNIT(  0, 10,-10,  0,  0, Velocity );       ///< Length/Time
   DECLARE_PHYSICAL_UNIT(  0,  0,  0,-10,  0, ThermalExpansion ); ///< 1/Temperature (coefficient of thermal expansion)

   // Other aliases
   using Area = Length2;    ///< Alias for Length2
   using Volume = Length3;  ///< Alias for Length3
   using Stress = Pressure; ///< Alias for Pressure

   /// Alias for Length. Area-per-length quantities (e.g. shear area over spacing, Av/S) are dimensionally
   /// equivalent to Length, so they can only be expressed in units matching another Length unit (e.g. mm,
   /// not mm^2/mm).
   using AreaPerLength = Length;

   };
};

