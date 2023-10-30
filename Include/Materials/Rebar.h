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
#include <string>

namespace WBFL
{
   namespace Materials
   {
      /// Product model for mild steel reinforcement (rebar).  Reinforcement bars may be circular or square.
      class MATCLASS Rebar
      {
      public:
         /// US bar designations
         enum class Size { 
                     bs3  = 0x0001,
                     bs4  = 0x0002,
                     bs5  = 0x0004,
                     bs6  = 0x0008,
                     bs7  = 0x0010,
                     bs8  = 0x0020,
                     bs9  = 0x0040,
                     bs10 = 0x0080,
                     bs11 = 0x0100,
                     bs14 = 0x0200,
                     bs18 = 0x0400,
                     bsNone = 0x0FFF
         }; 

         /// Material type based on ASTM specification name
         enum class Type { 
                     A615  = 0x1000,  ///< ASTM A615
                     A706  = 0x2000,  ///< ASTM A706
                     A1035 = 0x4000   ///< ASTM A1035
         };

         /// Material grade
         enum Grade { 
                      Grade40  = 0x00010000, 
                      Grade60  = 0x00020000,
                      Grade75  = 0x00040000,
                      Grade80  = 0x00080000,
                      Grade100 = 0x00100000,
                      Grade120 = 0x00200000,
         };
         
         Rebar();

         Rebar(const std::_tstring& name, Grade grade, Type type, Size size);

         Rebar(const Rebar& rOther) = default;
         Rebar& operator=(const Rebar&) = default;

         void SetName(const std::_tstring& name);
         std::_tstring GetName() const;

         void SetSize(Size size);
         Size GetSize() const;

         void SetGrade(Grade grade);
         Grade GetGrade() const;

         void SetType(Type type);
         Type GetType() const;

         Float64 GetNominalDimension() const;
         Float64 GetNominalArea() const;
         Float64 GetUltimateStrength() const;
         Float64 GetYieldStrength() const;
         Float64 GetE() const;
         Float64 GetElongation() const;

         static Float64 GetUltimateStrength(Type type,Grade grade);
         static Float64 GetYieldStrength(Type type,Grade grade);
         static Float64 GetE(Type type,Grade grade);
         static Float64 GetElongation(Type type, Grade grade, Size size);


      #if defined _DEBUG
         bool AssertValid() const;
      #endif // _DEBUG

      private:
         std::_tstring m_Name;
         Size m_Size;
         Grade m_Grade;
         Type m_Type;
         Float64     m_Dimension;
         Float64     m_Area;

      };

      inline void Rebar::SetName(const std::_tstring& name)
      {
         m_Name = name;
      }

      inline std::_tstring Rebar::GetName() const
      {
         return m_Name;
      }

      inline void Rebar::SetType(Type type)
      {
         m_Type = type;
      }

      inline Rebar::Type Rebar::GetType() const
      {
         return m_Type;
      }

      inline void Rebar::SetGrade(Grade grade)
      {
         m_Grade = grade;
      }

      inline Rebar::Grade Rebar::GetGrade() const
      {
         return m_Grade;
      }

      inline void Rebar::SetSize(Size size)
      {
         m_Size = size;
      }

      inline Rebar::Size Rebar::GetSize() const
      {
         return m_Size;
      }

      inline Float64 Rebar::GetNominalDimension() const
      {
         return m_Dimension;
      }

      inline Float64 Rebar::GetNominalArea() const
      {
         return m_Area;
      }

      inline Float64 Rebar::GetUltimateStrength() const
      {
         return Rebar::GetUltimateStrength(m_Type,m_Grade);
      }

      inline Float64 Rebar::GetYieldStrength() const
      {
         return Rebar::GetYieldStrength(m_Type,m_Grade);
      }

      inline Float64 Rebar::GetE() const
      {
         return Rebar::GetE(m_Type,m_Grade);
      }

      inline Float64 Rebar::GetElongation() const
      {
         return Rebar::GetElongation(m_Type, m_Grade, m_Size);
      }

      inline constexpr auto operator+(Rebar::Size t) noexcept { return std::underlying_type<Rebar::Size>::type(t); }
      inline constexpr auto operator+(Rebar::Type t) noexcept { return std::underlying_type<Rebar::Type>::type(t); }
      inline constexpr auto operator+(Rebar::Grade t) noexcept { return std::underlying_type<Rebar::Grade>::type(t); }
   };
};
