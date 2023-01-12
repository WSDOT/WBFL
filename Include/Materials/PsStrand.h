///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
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

#include <Materials/MaterialsExp.h>

namespace WBFL
{
   namespace Materials
   {
      /// Prestress strand steel product model. This product model is modeled after AASHTO M203, ASTM A416
      class MATCLASS PsStrand
      {
      public:
         /// Grade of strand material, designation is ultimate strength in MPa
         enum class Grade {
                      Gr1725 = 0x0001, ///< Grade 250
                      Gr1860 = 0x0002, ///< Grade 270
                      Gr2070 = 0x00080000 ///< Grade 300
         };

         /// Strand type
         enum class Type { 
            LowRelaxation  = 0x0004, 
            StressRelieved = 0x0008};

         /// Strand size, designation is in millimeter
         enum class Size {
                     D635  = 0x0010,///< 1/4"
                     D794  = 0x0020,///< 5/16"
                     D953  = 0x0040,///< 3/8"
                     D1111 = 0x0080,///< 7/16"
                     D1270 = 0x0100,///< 1/2"
                     D1524 = 0x0200,///< 0.6"
                     D1778 = 0x0400,///< 0.7"
                     D1320 = 0x0800,///< 1/2 HBS (Special)
                     D1575 = 0x1000,///< 0.62"
         }; 

         /// Strand coating type
         enum class Coating{ 
                        None = 0x00010000, ///< no coating
                        SmoothEpoxy = 0x00020000, ///< smooth epoxy coating
                        GritEpoxy   = 0x00040000 ///< grit impregnated epoxy coating
         };

         /// Initializes the strand to a .5" Grade 250 low relaxation strand (name is "Unknown").
         PsStrand();

         PsStrand(const std::_tstring& name,Grade grade,Type type,Coating coating,Size size,
                     Float64 fpu, Float64 fpy, Float64 modE,
                     Float64 d, Float64 a);

         PsStrand(const PsStrand&) = default;
         PsStrand& operator=(const PsStrand&) = default;

         bool operator==(const PsStrand& rOther) const;
         bool operator!=(const PsStrand& rOther) const;

         void SetName(const std::_tstring& name);
         std::_tstring GetName() const;

         void SetGrade(Grade grade);
         Grade GetGrade() const;

         void SetType(Type type);
         Type GetType() const;

         void SetSize(Size size);
         Size GetSize() const;

         void SetCoating(Coating coating);
         Coating GetCoating() const;

         void SetNominalDiameter(Float64 d);
         Float64 GetNominalDiameter() const;

         void SetNominalArea(Float64 a);
         Float64 GetNominalArea() const;

         void SetUltimateStrength(Float64 fpu);
         Float64 GetUltimateStrength() const;

         void SetYieldStrength(Float64 fpu);
         Float64 GetYieldStrength() const;

         void SetE(Float64 e);
         Float64 GetE() const;

         /// Returns the grade of the strand as a string
         static std::_tstring GetGrade(PsStrand::Grade grade, bool bUnitsUS);

         /// Returns the type of the strand as a string
         static std::_tstring GetType(PsStrand::Type type);
         
         /// Returns the coating of the strand as a string
         static std::_tstring GetCoating(PsStrand::Coating coating);

         /// Returns the size of the strand as a string
         static std::_tstring GetSize(PsStrand::Size size,bool bUnitsUS);

      #if defined _DEBUG
         bool AssertValid() const;
         void Dump(WBFL::Debug::LogContext& os) const;
      #endif // _DEBUG

      #if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST

      private:
         std::_tstring m_Name;
         Grade       m_Grade;
         Type        m_Type;
         Size        m_Size;
         Coating     m_Coating;
         Float64     m_Diameter;
         Float64     m_Area;
         Float64     m_Fpu;
         Float64     m_Fpy;
         Float64     m_ModE;
      };

      inline void PsStrand::SetSize(Size size)
      {
         m_Size = size;
      }

      inline PsStrand::Size PsStrand::GetSize() const
      {
         return m_Size;
      }

      inline void PsStrand::SetCoating(Coating coating)
      {
         m_Coating = coating;
      }

      inline PsStrand::Coating PsStrand::GetCoating() const
      {
         return m_Coating;
      }

      inline void PsStrand::SetNominalDiameter(Float64 d)
      {
         m_Diameter = d;
      }

      inline Float64 PsStrand::GetNominalDiameter() const
      {
         return m_Diameter;
      }

      inline void PsStrand::SetNominalArea(Float64 a)
      {
         m_Area = a;
      }

      inline Float64 PsStrand::GetNominalArea() const
      {
         return m_Area;
      }

      inline void PsStrand::SetUltimateStrength(Float64 fpu)
      {
         m_Fpu = fpu;
      }

      inline Float64 PsStrand::GetUltimateStrength() const
      {
         return m_Fpu;
      }

      inline void PsStrand::SetYieldStrength(Float64 fpy)
      {
         m_Fpy = fpy;
      }

      inline Float64 PsStrand::GetYieldStrength() const
      {
         return m_Fpy;
      }

      inline void PsStrand::SetE(Float64 e)
      {
         m_ModE = e;
      }

      inline Float64 PsStrand::GetE() const
      {
         return m_ModE;
      }

      inline constexpr auto operator+(PsStrand::Grade t) noexcept { return std::underlying_type<PsStrand::Grade>::type(t); }
      inline constexpr auto operator+(PsStrand::Type t) noexcept { return std::underlying_type<PsStrand::Type>::type(t); }
      inline constexpr auto operator+(PsStrand::Size t) noexcept { return std::underlying_type<PsStrand::Size>::type(t); }
      inline constexpr auto operator+(PsStrand::Coating t) noexcept { return std::underlying_type<PsStrand::Coating>::type(t); }
   };
};
