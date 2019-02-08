///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2019  Washington State Department of Transportation
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

#include <Lrfd\LrfdLib.h>
#include <Lrfd\LumpSumLosses.h>
#include <Lrfd\XPsLosses.h>
#include <Units\SysUnits.h>
#include <System\XProgrammingError.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdLumpSumLosses::lrfdLumpSumLosses()
{
}

lrfdLumpSumLosses::lrfdLumpSumLosses(Float64 ApsPerm,
                                     Float64 ApsTemp,
                                     Float64 FpjPerm,
                                     Float64 FpjTemp,
                                     lrfdLosses::TempStrandUsage usage,
                                     Float64 beforeXfer,
                                     Float64 afterXfer,
                                     Float64 atLifting,
                                     Float64 atShipping,
                                     Float64 beforeTempStrandRemoval,
                                     Float64 afterTempStrandRemoval,
                                     Float64 afterDeckPlacement,
                                     Float64 afterSIDL,
                                     Float64 final) :
lrfdLosses()
{
   m_ApsPerm                 = ApsPerm;
   m_ApsTemp                 = ApsTemp;
   m_FpjPerm                 = FpjPerm;
   m_FpjTemp                 = FpjTemp;
   m_TempStrandUsage         = usage;

   m_BeforeXfer              = beforeXfer;
   m_AfterXfer               = afterXfer;
   m_AtLifting               = atLifting;
   m_AtShipping              = atShipping;
   m_BeforeTempStrandRemoval = beforeTempStrandRemoval;
   m_AfterTempStrandRemoval  = afterTempStrandRemoval;
   m_AfterDeckPlacement      = afterDeckPlacement;
   m_AfterSIDL               = afterSIDL;
   m_Final                   = final;
}

lrfdLumpSumLosses::lrfdLumpSumLosses(const lrfdLumpSumLosses& rOther)
{
   MakeCopy( rOther );
}

lrfdLumpSumLosses::~lrfdLumpSumLosses()
{
}

//======================== OPERATORS  =======================================
lrfdLumpSumLosses& lrfdLumpSumLosses::operator=(const lrfdLumpSumLosses& rOther)
{
   if ( this != &rOther )
   {
      MakeAssignment( rOther );
   }

   return *this;
}

//======================== OPERATIONS =======================================
Float64 lrfdLumpSumLosses::PermanentStrand_BeforeTransfer() const
{
   return (m_ApsPerm != 0 && m_FpjPerm != 0) ? m_BeforeXfer : 0;
}

Float64 lrfdLumpSumLosses::PermanentStrand_AfterTransfer() const
{
   return (m_ApsPerm != 0 && m_FpjPerm != 0) ? m_AfterXfer : 0;
}

Float64 lrfdLumpSumLosses::PermanentStrand_AtLifting() const
{
   return (m_ApsPerm != 0 && m_FpjPerm != 0) ? m_AtLifting : 0;
}

Float64 lrfdLumpSumLosses::PermanentStrand_AtShipping() const
{
   return (m_ApsPerm != 0 && m_FpjPerm != 0) ? m_AtShipping : 0;
}

Float64 lrfdLumpSumLosses::PermanentStrand_AfterTemporaryStrandInstallation() const
{
   return (m_ApsPerm != 0 && m_FpjPerm != 0) ? m_AtShipping : 0;
}

Float64 lrfdLumpSumLosses::PermanentStrand_BeforeTemporaryStrandRemoval() const
{
   return (m_ApsPerm != 0 && m_FpjPerm != 0) ? m_BeforeTempStrandRemoval : 0;
}

Float64 lrfdLumpSumLosses::PermanentStrand_AfterTemporaryStrandRemoval() const
{
   return (m_ApsPerm != 0 && m_FpjPerm != 0) ? m_AfterTempStrandRemoval : 0;
}

Float64 lrfdLumpSumLosses::PermanentStrand_AfterDeckPlacement() const
{
   return (m_ApsPerm != 0 && m_FpjPerm != 0) ? m_AfterDeckPlacement : 0;
}

Float64 lrfdLumpSumLosses::PermanentStrand_AfterSIDL() const
{
   return (m_ApsPerm != 0 && m_FpjPerm != 0) ? m_AfterSIDL : 0;
}

Float64 lrfdLumpSumLosses::PermanentStrand_Final() const
{
   return (m_ApsPerm != 0 && m_FpjPerm != 0) ? m_Final : 0;
}

Float64 lrfdLumpSumLosses::TemporaryStrand_BeforeTransfer() const
{
   if ( m_ApsTemp != 0 && m_FpjTemp != 0 )
   {
      return (m_TempStrandUsage == lrfdLosses::tsPretensioned ? m_BeforeXfer : 0);
   }
   else
   {
      return 0;
   }
}

Float64 lrfdLumpSumLosses::TemporaryStrand_AfterTransfer() const
{
   if ( m_ApsTemp != 0 && m_FpjTemp != 0 )
   {
      return (m_TempStrandUsage == lrfdLosses::tsPretensioned ? m_AfterXfer : 0);
   }
   else
   {
      return 0;
   }
}

Float64 lrfdLumpSumLosses::TemporaryStrand_AtLifting() const
{
   if ( m_ApsTemp != 0 && m_FpjTemp != 0 )
   {
      return (m_TempStrandUsage == lrfdLosses::tsPTAfterLifting ||
              m_TempStrandUsage == lrfdLosses::tsPTBeforeShipping ) ? 0 : m_AtLifting;
   }
   else
   {
      return 0;
   }
}

Float64 lrfdLumpSumLosses::TemporaryStrand_AtShipping() const
{
   if ( m_ApsTemp != 0 && m_FpjTemp != 0 )
   {
      return m_AtShipping;
   }
   else
   {
      return 0;
   }
}

Float64 lrfdLumpSumLosses::TemporaryStrand_AfterTemporaryStrandInstallation() const
{
   if ( m_ApsTemp != 0 && m_FpjTemp != 0 )
   {
      switch ( m_TempStrandUsage )
      {
      case lrfdLosses::tsPretensioned:
         return m_AfterXfer;

      case lrfdLosses::tsPTBeforeLifting:
      case lrfdLosses::tsPTAfterLifting:
         return 0;

      case lrfdLosses::tsPTBeforeShipping:
         return 0;

      default:
         ASSERT(false); // is there a new temporary strand usage?
         return 0;
      }
   }

   return 0;
}

Float64 lrfdLumpSumLosses::TemporaryStrand_BeforeTemporaryStrandRemoval() const
{
   if ( m_ApsTemp != 0 && m_FpjTemp != 0 )
   {
      return m_BeforeTempStrandRemoval;
   }
   else
   {
      return 0;
   }
}

Float64 lrfdLumpSumLosses::TemporaryStrand_AfterTemporaryStrandRemoval() const
{
   return 0;
}

Float64 lrfdLumpSumLosses::TemporaryStrand_AfterDeckPlacement() const
{
   return 0;
}

Float64 lrfdLumpSumLosses::TemporaryStrand_AfterSIDL() const
{
   return 0;
}

Float64 lrfdLumpSumLosses::TemporaryStrand_Final() const
{
   return 0;
}

Float64 lrfdLumpSumLosses::TemporaryStrand_TimeDependentLossesAtShipping() const
{
   return m_AtShipping;
}

Float64 lrfdLumpSumLosses::PermanentStrand_TimeDependentLossesAtShipping() const
{
   return m_AtShipping;
}

Float64 lrfdLumpSumLosses::PermanentStrand_RelaxationLossesBeforeTransfer() const
{
   // Initial relaxation is not know for lump sum
   // return 0
   return 0;
}

Float64 lrfdLumpSumLosses::TemporaryStrand_RelaxationLossesBeforeTransfer() const
{
   // Initial relaxation is not know for lump sum
   // return 0
   return 0;
}

Float64 lrfdLumpSumLosses::PermanentStrand_ElasticShorteningLosses() const
{
   // elastic shortening losses are not know when lump sum is used
   // simply return 0
   return 0;
}

Float64 lrfdLumpSumLosses::TemporaryStrand_ElasticShorteningLosses() const
{
   // elastic shortening losses are not know when lump sum is used
   // simply return 0
   return 0;
}

Float64 lrfdLumpSumLosses::TimeDependentLossesBeforeDeck() const
{
   return m_AfterTempStrandRemoval;
}

Float64 lrfdLumpSumLosses::TimeDependentLossesAfterDeck() const
{
   return m_AfterDeckPlacement;
}

Float64 lrfdLumpSumLosses::TimeDependentLosses() const
{
   return m_Final;
}

Float64 lrfdLumpSumLosses::GetBeforeXferLosses() const
{
   return m_BeforeXfer;
}

Float64 lrfdLumpSumLosses::GetAfterXferLosses() const
{
   return m_AfterXfer;
}

Float64 lrfdLumpSumLosses::GetLiftingLosses() const
{
   return m_AtLifting;
}

Float64 lrfdLumpSumLosses::GetShippingLosses() const
{
   return m_AtShipping;
}

Float64 lrfdLumpSumLosses::GetBeforeTempStrandRemovalLosses() const
{
   return m_BeforeTempStrandRemoval;
}

Float64 lrfdLumpSumLosses::GetAfterTempStrandRemovalLosses() const
{
   return m_AfterTempStrandRemoval;
}

Float64 lrfdLumpSumLosses::GetAfterDeckPlacementLosses() const
{
   return m_AfterDeckPlacement;
}

Float64 lrfdLumpSumLosses::GetFinalLosses() const
{
   return m_Final;
}

void lrfdLumpSumLosses::SetBeforeXferLosses(Float64 loss)
{
   m_BeforeXfer = loss;
}

void lrfdLumpSumLosses::SetAfterXferLosses(Float64 loss)
{
   m_AfterXfer = loss;
}

void lrfdLumpSumLosses::SetLiftingLosses(Float64 loss)
{
   m_AtLifting = loss;
}

void lrfdLumpSumLosses::SetShippingLosses(Float64 loss)
{
   m_AtShipping = loss;
}

void lrfdLumpSumLosses::SetBeforeTempStrandRemovalLosses(Float64 loss)
{
   m_BeforeTempStrandRemoval = loss;
}

void lrfdLumpSumLosses::SetAfterTempStrandRemovalLosses(Float64 loss)
{
   m_AfterTempStrandRemoval = loss;
}

void lrfdLumpSumLosses::SetAfterDeckPlacementLosses(Float64 loss)
{
   m_AfterDeckPlacement = loss;
}

void lrfdLumpSumLosses::SetFinalLosses(Float64 loss)
{
   m_Final = loss;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdLumpSumLosses::MakeAssignment( const lrfdLumpSumLosses& rOther )
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void lrfdLumpSumLosses::MakeCopy( const lrfdLumpSumLosses& rOther )
{
   lrfdLosses::MakeCopy(rOther);

   m_BeforeXfer              = rOther.m_BeforeXfer;
   m_AfterXfer               = rOther.m_AfterXfer;
   m_AtLifting               = rOther.m_AtLifting;
   m_AtShipping              = rOther.m_AtShipping;
   m_BeforeTempStrandRemoval = rOther.m_BeforeTempStrandRemoval;
   m_AfterTempStrandRemoval  = rOther.m_AfterTempStrandRemoval;
   m_AfterDeckPlacement      = rOther.m_AfterDeckPlacement;
   m_AfterSIDL               = rOther.m_AfterSIDL;
   m_Final                   = rOther.m_Final;
}

void lrfdLumpSumLosses::ValidateParameters() const
{
}

void lrfdLumpSumLosses::UpdateLongTermLosses() const
{
}

void lrfdLumpSumLosses::UpdateHaulingLosses() const
{
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST
#include <Units\SysUnitsMgr.h>
#include <Lrfd\AutoVersion.h>
bool lrfdLumpSumLosses::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdLumpSumLosses");

   TESTME_EPILOG("lrfdLumpSumLosses");
}

#endif // _UNITTEST


