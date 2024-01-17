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

#include <map>
#include <Lrfd\LrfdExp.h>
#include <Materials/PsStrand.h>
#include <Lrfd\PsStrand.h>
#include <System\SingletonKiller.h>
#include <Lrfd/BDSManager.h>

namespace WBFL
{
   namespace LRFD
   {
      class StrandIter;

      /// @brief Flyweight pool for prestressing strands.
      class LRFDCLASS StrandPool
      {
      public:
         StrandPool(const StrandPool&) = delete;
         StrandPool& operator=(const StrandPool&) = delete;

         /// @brief Returns a pointer to an instance of the strand pool.
         static const StrandPool* GetInstance();

         const WBFL::Materials::PsStrand* GetStrand(Int64 key,BDSManager::Units units) const;

         const WBFL::Materials::PsStrand* GetStrand(Int64 key) const;

         const WBFL::Materials::PsStrand* GetStrand(WBFL::Materials::PsStrand::Grade grade,
                                      WBFL::Materials::PsStrand::Type type,
                                      WBFL::Materials::PsStrand::Coating coating,
                                      WBFL::Materials::PsStrand::Size size ) const;

         /// @brief Returns the lookup key for pStrand.  If pStrand is not a member of the strand pool, returns -1
         Int64 GetStrandKey(const WBFL::Materials::PsStrand* pStrand) const;
         Int64 GetStrandKey(WBFL::Materials::PsStrand::Grade grade, WBFL::Materials::PsStrand::Type type, WBFL::Materials::PsStrand::Coating coating, WBFL::Materials::PsStrand::Size size) const;

         bool CompareStrands(const WBFL::Materials::PsStrand* pStrandA, const WBFL::Materials::PsStrand* pStrandB, bool bCompareGrade = true, bool bCompareType = true, bool bCompareCoating = false, bool bCompareSize = false) const;

      private:
         static StrandPool* ms_pInstance;
         using Pool = std::map<Int64, std::shared_ptr<WBFL::Materials::PsStrand> >;
         static Pool ms_USStrand;
         static Pool ms_SIStrand;

         using Killer = WBFL::System::SingletonKiller<StrandPool>;
         friend Killer;
         static Killer ms_Killer;

         StrandPool();
         ~StrandPool() = default;

         friend StrandIter;
      };

      /// @brief Iterates over the various strand stored in StrandPool. The strands are filtered by Grade and Type.
      class LRFDCLASS StrandIter
      {
      public:
         StrandIter(WBFL::Materials::PsStrand::Grade grade = WBFL::Materials::PsStrand::Grade::Gr1725,
                        WBFL::Materials::PsStrand::Type type = WBFL::Materials::PsStrand::Type::LowRelaxation,
                        WBFL::Materials::PsStrand::Coating coating = WBFL::Materials::PsStrand::Coating::None);

         StrandIter(const StrandIter&) = default;
         ~StrandIter() = default;

         StrandIter& operator=(const StrandIter&) = default;

         virtual void Begin();

         virtual void End();

         virtual void Next();

         virtual void Move(Int64 pos);

         virtual void MoveBy(Int64 dPos);

         operator void*() const;

         const WBFL::Materials::PsStrand* GetCurrentStrand() const;

         /// @brief Sets the grade of prestress steel for which the available sizes will
         /// be iterated over. Sets the iterator to the first element in the
         /// iteration sequence.
         void SetGrade(WBFL::Materials::PsStrand::Grade grade);

         /// @brief Returns the grade of prestress steel for which the available sizes are being iterated over.
         WBFL::Materials::PsStrand::Grade GetGrade() const;

         /// @brief Sets the type of prestress steel for which the available sizes will
         /// be iterated over. Sets the iterator to the first element in the
         /// iteration sequence.
         void SetType(WBFL::Materials::PsStrand::Type type);

         /// @brief Returns the type of prestress steel for which the available sizes are being iterated over.
         WBFL::Materials::PsStrand::Type GetType() const;

         /// @brief Sets the coating type of prestress steel for which the available sizes will
         /// be iterated over. Sets the iterator to the first element in the
         /// iteration sequence.
         void SetCoating(WBFL::Materials::PsStrand::Coating coating);

         /// @brief Returns the coating type of prestress steel for which the available sizes are being iterated over.
         WBFL::Materials::PsStrand::Coating GetCoating() const;

      private:
         std::vector< const WBFL::Materials::PsStrand* > m_Strands;
         std::vector< const WBFL::Materials::PsStrand* >::iterator m_Begin;
         std::vector< const WBFL::Materials::PsStrand* >::iterator m_End;
         std::vector< const WBFL::Materials::PsStrand* >::iterator m_Current;
         WBFL::Materials::PsStrand::Grade m_Grade;
         WBFL::Materials::PsStrand::Type m_Type;
         WBFL::Materials::PsStrand::Coating m_Coating;
      };
   };
};
