///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <Lrfd\LrfdExp.h>
#include <Materials/Rebar.h>
#include <map>
#include <System\SingletonKiller.h>

namespace WBFL
{
   namespace LRFD
   {
      class RebarIter;

      ///@ brief Flyweight pool for mild steel reinforcement bars.  All of the bars described in AASHTO M31 are stored in this flyweight pool.
      class LRFDCLASS RebarPool
      {
      public:
         RebarPool(const RebarPool&) = delete;
         RebarPool& operator=(const RebarPool&) = delete;

         // Returns a pointer to an instance of the rebar pool.
         static const RebarPool* GetInstance();

         //------------------------------------------------------------------------
         const WBFL::Materials::Rebar* GetRebar(Int32 key) const;

         //------------------------------------------------------------------------
         const WBFL::Materials::Rebar* GetRebar(WBFL::Materials::Rebar::Type type,
                                      WBFL::Materials::Rebar::Grade grade,
                                      WBFL::Materials::Rebar::Size size ) const;

         //------------------------------------------------------------------------
         // Returns the lookup key for pRebar.  If pRebar is not a member of
         // the rebar pool, returns -1
         Int32 GetRebarKey(const WBFL::Materials::Rebar* pRebar) const;

         static bool MapOldRebarKey(Int32 oldKey,WBFL::Materials::Rebar::Grade& grade,WBFL::Materials::Rebar::Type& type,WBFL::Materials::Rebar::Size& size);

         static std::_tstring GetMaterialName(WBFL::Materials::Rebar::Type type,WBFL::Materials::Rebar::Grade grade);
         static std::_tstring GetBarSize(WBFL::Materials::Rebar::Size size);
         static WBFL::Materials::Rebar::Size GetBarSize(LPCTSTR strSize);

         static void GetBarSizeRange(WBFL::Materials::Rebar::Type type,WBFL::Materials::Rebar::Grade grade,WBFL::Materials::Rebar::Size& minSize,WBFL::Materials::Rebar::Size& maxSize);
         static void GetTransverseBarSizeRange(WBFL::Materials::Rebar::Type type,WBFL::Materials::Rebar::Grade grade,WBFL::Materials::Rebar::Size& minSize,WBFL::Materials::Rebar::Size& maxSize);


      private:
         RebarPool();
         virtual ~RebarPool() = default;

         static RebarPool* ms_pInstance;
         using Pool = std::map<Int32, std::shared_ptr<WBFL::Materials::Rebar>>;
         static Pool ms_Rebar;

         using Killer = WBFL::System::SingletonKiller<RebarPool>;
         friend Killer;
         static Killer ms_Killer;

         friend RebarIter;
      };

      /// @brief Iterates over the various rebar sizes stored in RebarPool.
      class LRFDCLASS RebarIter
      {
      public:
         RebarIter(WBFL::Materials::Rebar::Type type = WBFL::Materials::Rebar::Type::A615,WBFL::Materials::Rebar::Grade grade = WBFL::Materials::Rebar::Grade::Grade60,bool bTransverseBarsOnly=false);
         RebarIter(const RebarIter& rOther) = default;
         ~RebarIter() = default;
         RebarIter& operator=(const RebarIter& rOther) = default;

         //------------------------------------------------------------------------
         virtual void Begin();

         //------------------------------------------------------------------------
         virtual void End();

         //------------------------------------------------------------------------
         virtual void Next();

         //------------------------------------------------------------------------
         virtual void Move(Int32 pos);

         //------------------------------------------------------------------------
         virtual void MoveBy(Int32 dPos);

         //------------------------------------------------------------------------
         operator void*() const;

         //------------------------------------------------------------------------
         const WBFL::Materials::Rebar* GetCurrentRebar() const;

         //------------------------------------------------------------------------
         // Sets the grade of prestress steel for which the available sizes will
         // be iterated over. Sets the iterator to the first element in the
         // iteration sequence.
         void SetGrade(WBFL::Materials::Rebar::Grade grade);

         //------------------------------------------------------------------------
         // Returns the grade of prestress steel for which the available sizes
         // are being iterated over.
         WBFL::Materials::Rebar::Grade GetGrade() const;

         //------------------------------------------------------------------------
         // Sets the type of prestress steel for which the available sizes will
         // be iterated over. Sets the iterator to the first element in the
         // iteration sequence.
         void SetType(WBFL::Materials::Rebar::Type type);

         //------------------------------------------------------------------------
         // Returns the type of prestress steel for which the available sizes
         // are being iterated over.
         WBFL::Materials::Rebar::Type GetType() const;

      private:
         std::vector< const WBFL::Materials::Rebar* > m_Bars;
         std::vector< const WBFL::Materials::Rebar* >::iterator m_Begin;
         std::vector< const WBFL::Materials::Rebar* >::iterator m_End;
         std::vector< const WBFL::Materials::Rebar* >::iterator m_Current;
         WBFL::Materials::Rebar::Grade m_Grade;
         WBFL::Materials::Rebar::Type m_Type;
         bool m_bTransverseBarsOnly;
      };
   };
};
