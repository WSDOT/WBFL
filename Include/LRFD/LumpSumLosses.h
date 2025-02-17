///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright � 1999-2025  Washington State Department of Transportation
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
#include <Lrfd\PsStrand.h>
#include <Lrfd\Losses.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Utility class to represent lump sum losses.
      class LRFDCLASS LumpSumLosses : public Losses
      {
      public:
         LumpSumLosses() = default;

         LumpSumLosses(Float64 ApsPerm,
                           Float64 ApsTemp,
                           Float64 FpjPerm,
                           Float64 FpjTemp,
                           Losses::TempStrandUsage usage,
                           Float64 beforeXfer,
                           Float64 afterXfer,
                           Float64 atLifting,
                           Float64 atShipping,
                           Float64 beforeTempStrandRemoval,
                           Float64 afterTempStrandRemoval,
                           Float64 afterDeckPlacement,
                           Float64 afterSIDL,
                           Float64 final);

         LumpSumLosses(const LumpSumLosses&) = default;

         ~LumpSumLosses() = default;

         LumpSumLosses& operator=(const LumpSumLosses&) = default;


         // override these virtual functions
         virtual Float64 PermanentStrand_BeforeTransfer() const override;
         virtual Float64 PermanentStrand_AfterTransfer() const override;
         virtual Float64 PermanentStrand_AtLifting() const override;
         virtual Float64 PermanentStrand_AtShipping() const override;
         virtual Float64 PermanentStrand_AfterTemporaryStrandInstallation() const override;
         virtual Float64 PermanentStrand_BeforeTemporaryStrandRemoval() const override;
         virtual Float64 PermanentStrand_AfterTemporaryStrandRemoval() const override;
         virtual Float64 PermanentStrand_AfterDeckPlacement() const override;
         virtual Float64 PermanentStrand_AfterSIDL() const override;
         virtual Float64 PermanentStrand_Final() const override;

         virtual Float64 TemporaryStrand_BeforeTransfer() const override;
         virtual Float64 TemporaryStrand_AfterTransfer() const override;
         virtual Float64 TemporaryStrand_AtLifting() const override;
         virtual Float64 TemporaryStrand_AtShipping() const override;
         virtual Float64 TemporaryStrand_AfterTemporaryStrandInstallation() const override;
         virtual Float64 TemporaryStrand_BeforeTemporaryStrandRemoval() const override;
         virtual Float64 TemporaryStrand_AfterTemporaryStrandRemoval() const override;
         virtual Float64 TemporaryStrand_AfterDeckPlacement() const override;
         virtual Float64 TemporaryStrand_AfterSIDL() const override;
         virtual Float64 TemporaryStrand_Final() const override;

         virtual Float64 PermanentStrand_RelaxationLossesBeforeTransfer() const override;
         virtual Float64 PermanentStrand_ElasticShorteningLosses() const override;

         virtual Float64 TemporaryStrand_RelaxationLossesBeforeTransfer() const override;
         virtual Float64 TemporaryStrand_ElasticShorteningLosses() const override;

         virtual Float64 PermanentStrand_TimeDependentLossesAtShipping() const override;
         virtual Float64 TemporaryStrand_TimeDependentLossesAtShipping() const override;
         virtual Float64 TimeDependentLossesBeforeDeck() const override;
         virtual Float64 TimeDependentLossesAfterDeck() const override;
         virtual Float64 TimeDependentLosses() const override;


         Float64 GetBeforeXferLosses() const;
         Float64 GetAfterXferLosses() const;
         Float64 GetLiftingLosses() const;
         Float64 GetShippingLosses() const;
         Float64 GetBeforeTempStrandRemovalLosses() const;
         Float64 GetAfterTempStrandRemovalLosses() const;
         Float64 GetAfterDeckPlacementLosses() const;
         Float64 GetFinalLosses() const;

         void SetBeforeXferLosses(Float64 loss);
         void SetAfterXferLosses(Float64 loss);
         void SetLiftingLosses(Float64 loss);
         void SetShippingLosses(Float64 loss);
         void SetBeforeTempStrandRemovalLosses(Float64 loss);
         void SetAfterTempStrandRemovalLosses(Float64 loss);
         void SetAfterDeckPlacementLosses(Float64 loss);
         void SetFinalLosses(Float64 loss);

      protected:
         Float64 m_BeforeXfer;
         Float64 m_AfterXfer;
         Float64 m_AtLifting;
         Float64 m_AtShipping;
         Float64 m_BeforeTempStrandRemoval;
         Float64 m_AfterTempStrandRemoval;
         Float64 m_AfterDeckPlacement;
         Float64 m_AfterSIDL;
         Float64 m_Final;

         virtual void ValidateParameters() const override;
         virtual void UpdateLongTermLosses() const override;
         virtual void UpdateHaulingLosses() const override;
      };
   };
};
