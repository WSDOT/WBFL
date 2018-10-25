///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2010  Washington State Department of Transportation
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
#include <Lrfd\Losses.h>
#include <Lrfd\XPsLosses.h>
#include <Lrfd\VersionMgr.h>
#include <Units\SysUnits.h>
#include <System\XProgrammingError.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdLosses
****************************************************************************/

lrfdLosses::lrfdLosses(  Float64 x,
                         Float64 Lg,
                         matPsStrand::Grade gr,
                         matPsStrand::Type type,
                         Float64 fpjPerm, // fpj permanent strands
                         Float64 fpjTemp,  // fpj of temporary strands
                         Float64 ApsPerm,  // area of permanent strand
                         Float64 ApsTemp,   // area of TTS 
                         Float64 aps,      // area of one temp strand
                         Float64 eperm, // eccentricty of permanent ps strands with respect to CG of girder
                         Float64 etemp, // eccentricty of temporary strands with respect to CG of girder
                         lrfdLosses::TempStrandUsage usage,
                         Float64 anchorSet,
                         Float64 wobble,
                         Float64 friction,
                         Float64 angleChange,

                         Float64 Fc,   // 28 day strength of girder concrete
                         Float64 Fci,  // Release strength
                         Float64 FcSlab,   
                         Float64 Ec,   // Modulus of elasticity of girder
                         Float64 Eci,  // Modulus of elasticity of girder at transfer
                         Float64 Ecd,  // Modulus of elasticity of deck

                         Float64 Mdlg,  // Dead load moment of girder only
                         Float64 Madlg,  // Additional dead load on girder section
                         Float64 Msidl, // Superimposed dead loads

                         Float64 Ag,   // area of girder
                         Float64 Ig,   // moment of inertia of girder
                         Float64 Ybg,   // Centroid of girder measured from bottom
                         Float64 Ac,    // Area of the composite girder and deck
                         Float64 Ic,    // Moment of inertia of composite
                         Float64 Ybc,   // Centroid of composite measured from bottom

                         Float64 rh, // relative humidity
                         Float64 ti,   // Time until prestress transfer

                         bool bIgnoreInitialRelaxation
                         )
{
   Init();

   m_Grade                 = gr;
   m_Type                  = type;
   m_FpjPerm               = fpjPerm;
   m_FpjTemp               = fpjTemp;
   m_ApsPerm               = ApsPerm;
   m_ApsTemp               = ApsTemp;
   m_aps                   = aps;
   m_eperm                 = eperm;
   m_etemp                 = etemp;
   m_Fc                    = Fc;
   m_Fci                   = Fci;
   m_FcSlab                = FcSlab;
   m_Ec                    = Ec;
   m_Eci                   = Eci;
   m_Ecd                   = Ecd;

   m_X = x;
   m_Lg = Lg;

   m_TempStrandUsage = usage;
   m_AnchorSet = anchorSet;
   m_WobbleCoefficient = wobble;
   m_FrictionCoefficient = friction;
   m_AngleChange = angleChange;

   m_Ep                    = lrfdPsStrand::GetModE();
   m_Fpu                   = lrfdPsStrand::GetUltimateStrength( m_Grade );
   m_Fpy                   = lrfdPsStrand::GetYieldStrength( m_Grade, m_Type );

   m_Mdlg                  = Mdlg;
   m_Madlg                 = Madlg;
   m_Msidl                 = Msidl;
   
   m_bIgnoreInitialRelaxation = bIgnoreInitialRelaxation;

   m_Ag                    = Ag;
   m_Ig                    = Ig;
   m_Ybg                   = Ybg;
   m_Ac                    = Ac;
   m_Ic                    = Ic;
   m_Ybc                   = Ybc;

   m_H = rh;

   m_ti = ti;

   m_IsDirty               = true;
}

lrfdLosses::lrfdLosses()
{
   Init();

   m_Type                  = matPsStrand::LowRelaxation;
   m_Grade                 = matPsStrand::Gr1860;
   m_TempStrandUsage = tsPretensioned;

   m_FpjPerm               = 0;
   m_FpjTemp               = 0;
   m_ApsPerm               = 0;
   m_ApsTemp               = 0;
   m_aps                   = 0;
   m_eperm                 = 0;
   m_etemp                 = 0;
   m_Fc                    = 0;
   m_Fci                   = 0;
   m_FcSlab                = 0;
   m_Ec                    = 0;
   m_Eci                   = 0;
   m_Ecd                   = 0;

   m_X = 0;
   m_Lg = 0;

   m_AnchorSet = 0;
   m_WobbleCoefficient = 0.0002;
   m_FrictionCoefficient = 0.25;
   m_AngleChange = 0.0;

   m_Ep                    = lrfdPsStrand::GetModE();
   m_Fpu                   = lrfdPsStrand::GetUltimateStrength( m_Grade );
   m_Fpy                   = lrfdPsStrand::GetYieldStrength( m_Grade, m_Type );

   m_Mdlg                  = 0;
   m_Madlg                 = 0;
   m_Msidl                 = 0;
   
   m_bIgnoreInitialRelaxation = true;

   m_Ag                    = 0;
   m_Ig                    = 0;
   m_Ybg                   = 0;
   m_Ac                    = 0;
   m_Ic                    = 0;
   m_Ybc                   = 0;

   m_H = 0;

   m_ti = 0;

   m_IsDirty               = true;
}


lrfdLosses::lrfdLosses(const lrfdLosses& rOther)
{
   MakeCopy( rOther );
}

void lrfdLosses::Init()
{
   m_dfpR0[0] = 0;
   m_dfpR0[1] = 0;
   m_dfpES[0] = 0;
   m_dfpES[1] = 0;
   m_dfpED = 0;
   m_dfpp = 0;
   m_fpL = 0;
   m_fpD = 0;
   m_fpMax = 0;
   m_fptMax = 0;
   m_fptMin = 0;
   m_fptAvg = 0;
   m_Fcgpt = 0;
   m_Fcgpp = 0;
   m_dfpt = 0;
   m_dfptAvg = 0;
   m_PptMax = 0;
   m_PptMin = 0;
   m_PptAvg = 0;
   m_fptr = 0;
   m_dfptr = 0;
   m_Ptr = 0;
   m_DeltaFcd1 = 0;
   m_dfpF = 0;
   m_dfpFT = 0;
   m_dfpA = 0;
   m_dfpAT = 0;
   m_La = 0;
}

lrfdLosses& lrfdLosses::operator=(const lrfdLosses& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

void lrfdLosses::OnUpdate()
{
   lrfdVersionMgrListener::OnUpdate();

   // Nothing actually changes.
}

Float64 lrfdLosses::GetFpy() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_Fpy;
}

Float64 lrfdLosses::GetEp() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_Ep;
}

Float64 lrfdLosses::GetApsPermanent() const
{ 
   return m_ApsPerm; 
}

void lrfdLosses::SetApsPermanent(Float64 Aps)
{ 
   if ( !IsEqual(m_ApsPerm,Aps) )
   {
      m_ApsPerm = Aps;
      m_IsDirty = true; 
   }
}

Float64 lrfdLosses::GetApsTemporary() const
{ 
   return m_ApsTemp; 
}

void lrfdLosses::SetApsTemporary(Float64 Aps)
{ 
   if ( !IsEqual(m_ApsTemp,Aps) )
   {
      m_ApsTemp = Aps;
      m_IsDirty = true; 
   }
}

void lrfdLosses::SetStrandArea(Float64 aps)
{
   if ( !IsEqual(m_aps,aps) )
   {
      m_aps = aps;
      m_IsDirty = true;
   }
}

Float64 lrfdLosses::GetStrandArea() const
{
   return m_aps;
}

void lrfdLosses::SetEccPermanent(Float64 e)
{
   if ( !IsEqual(m_eperm,e) )
   {
      m_eperm = e;
      m_IsDirty = true;
   }
}

Float64 lrfdLosses::GetEccPermanent() const
{
   return m_eperm;
}

void lrfdLosses::SetEccTemporary(Float64 e)
{
   if ( !IsEqual(m_etemp,e) )
   {
      m_etemp = e;
      m_IsDirty = true;
   }
}

Float64 lrfdLosses::GetEccTemporary() const
{
   return m_etemp;
}

Float64 lrfdLosses::GetEccpc() const
{
   // eccentricty of permanent strand on composite girder
   return m_eperm + (m_Ybc - m_Ybg);
}

Float64 lrfdLosses::GetEccpg() const
{
   // eccentricty of all strand on non-composite girder
   Float64 aps = m_ApsPerm + m_ApsTemp;
   Float64 ecc = IsZero(aps) ? 0 : (m_ApsPerm*m_eperm + m_ApsTemp*m_etemp)/aps;
   return ecc;
}

const lrfdElasticShortening& lrfdLosses::ElasticShortening() const 
{ 
   if ( m_IsDirty )
      UpdateLosses();

   return m_ElasticShortening; 
}


Float64 lrfdLosses::PermanentStrand_BeforeTransfer() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return PermanentStrand_RelaxationLossesBeforeTransfer();
}

Float64 lrfdLosses::PermanentStrand_AfterTransfer() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return PermanentStrand_RelaxationLossesBeforeTransfer() + PermanentStrand_ElasticShorteningLosses();
}

Float64 lrfdLosses::PermanentStrand_AtLifting() const
{
   if ( m_IsDirty )
      UpdateLosses();

   Float64 loss = PermanentStrand_AfterTransfer();

   if ( m_TempStrandUsage == tsPTBeforeLifting )
      loss += GetDeltaFpp();//m_dfpp;

   return loss;
}

Float64 lrfdLosses::PermanentStrand_AtShipping() const
{
   if ( m_IsDirty )
      UpdateLosses();

   Float64 loss = PermanentStrand_AtLifting() + PermanentStrand_TimeDependentLossesAtShipping();

   if ( m_TempStrandUsage == tsPTBeforeShipping )
      loss += GetDeltaFpp();//m_dfpp;

   return loss;
}

Float64 lrfdLosses::PermanentStrand_AfterTemporaryStrandInstallation() const
{
   if ( m_IsDirty )
      UpdateLosses();

   Float64 loss = PermanentStrand_AfterTransfer();

   if ( m_TempStrandUsage != tsPretensioned )
      loss += GetDeltaFpp();//m_dfpp;

   if ( m_TempStrandUsage == tsPTBeforeShipping )
      loss += PermanentStrand_TimeDependentLossesAtShipping();

   return loss;
}

Float64 lrfdLosses::PermanentStrand_BeforeTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
      UpdateLosses();

   Float64 loss = PermanentStrand_AtShipping();
   return loss;
}

Float64 lrfdLosses::PermanentStrand_AfterTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
      UpdateLosses();

   Float64 loss = PermanentStrand_AtShipping() + GetDeltaFptr();//m_dfptr;
   return loss;
}

Float64 lrfdLosses::PermanentStrand_AfterDeckPlacement() const
{
   if ( m_IsDirty )
      UpdateLosses();

   Float64 loss = PermanentStrand_AfterTransfer() + TimeDependentLossesBeforeDeck() + ElasticGainDueToDeckPlacement() + GetDeltaFptr();

   if ( m_TempStrandUsage != tsPretensioned )
      loss += GetDeltaFpp();//m_dfpp;

   return loss;
}

Float64 lrfdLosses::PermanentStrand_Final() const
{
   if ( m_IsDirty )
      UpdateLosses();

   Float64 loss = PermanentStrand_AfterDeckPlacement() + TimeDependentLossesAfterDeck();
   return loss;
}

Float64 lrfdLosses::TemporaryStrand_BeforeTransfer() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return TemporaryStrand_RelaxationLossesBeforeTransfer();
}

Float64 lrfdLosses::TemporaryStrand_AfterTransfer() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return TemporaryStrand_RelaxationLossesBeforeTransfer() + TemporaryStrand_ElasticShorteningLosses();
}

Float64 lrfdLosses::TemporaryStrand_AtLifting() const
{
   if ( m_IsDirty )
      UpdateLosses();

   Float64 loss = 0;
   
   if ( m_TempStrandUsage == tsPretensioned )
      loss = TemporaryStrand_AfterTransfer();
   else if ( m_TempStrandUsage == tsPTBeforeLifting )
      loss = TemporaryStrand_AfterTemporaryStrandInstallation();

   return loss;
}


Float64 lrfdLosses::TemporaryStrand_AtShipping() const
{
   if ( m_IsDirty )
      UpdateLosses();

   Float64 loss = 0;

   if (m_TempStrandUsage == tsPretensioned )
      loss = TemporaryStrand_AtLifting() + TemporaryStrand_TimeDependentLossesAtShipping();
   else if ( m_TempStrandUsage == tsPTBeforeShipping )
      loss = TemporaryStrand_AfterTemporaryStrandInstallation();
   else // tsPTBeforeLifting || tsPTAfterLifting
      loss = TemporaryStrand_AfterTemporaryStrandInstallation() + TemporaryStrand_TimeDependentLossesAtShipping();

   return loss;
}

Float64 lrfdLosses::TemporaryStrand_AfterTemporaryStrandInstallation() const
{
   if ( m_IsDirty )
      UpdateLosses();

   Float64 loss = 0;
   if (m_TempStrandUsage == tsPretensioned )
      loss = TemporaryStrand_AfterTransfer();
   else
      loss = FrictionLoss() + AnchorSetLoss() + GetDeltaFptAvg(); //m_dfpF + m_dfpA + m_dfptAvg;

   return loss;
}

Float64 lrfdLosses::TemporaryStrand_BeforeTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
      UpdateLosses();

   Float64 loss = 0;
   switch ( m_TempStrandUsage )
   {
   case lrfdLosses::tsPretensioned:
      loss = TemporaryStrand_AtShipping();
      break;

   case lrfdLosses::tsPTBeforeLifting:
   case lrfdLosses::tsPTAfterLifting:
      loss = TemporaryStrand_AtLifting() + TimeDependentLossesBeforeDeck();
      break;

   case lrfdLosses::tsPTBeforeShipping:
      loss = TemporaryStrand_AtShipping();
      break;

   default:
      CHECK(false);
      break;
   }

   return loss;
}

Float64 lrfdLosses::TemporaryStrand_AfterTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return 0;
}

Float64 lrfdLosses::TemporaryStrand_AfterDeckPlacement() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return 0;
}

Float64 lrfdLosses::TemporaryStrand_Final() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return 0;
}

Float64 lrfdLosses::PermanentStrand_RelaxationLossesBeforeTransfer() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpR0[1];
}

Float64 lrfdLosses::PermanentStrand_ElasticShorteningLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpES[1];
}

Float64 lrfdLosses::TemporaryStrand_RelaxationLossesBeforeTransfer() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpR0[0];
}

Float64 lrfdLosses::TemporaryStrand_ElasticShorteningLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpES[0];
}

Float64 lrfdLosses::ElasticGainDueToDeckPlacement() const
{
   if ( m_IsDirty ) UpdateLosses();
   return m_dfpED;
}

Float64 lrfdLosses::FrictionLoss() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpF;
}

Float64 lrfdLosses::TotalFrictionLoss() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpFT;
}

Float64 lrfdLosses::AnchorSetLoss() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpA;
}

Float64 lrfdLosses::TotalAnchorSetLoss() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpAT;
}

Float64 lrfdLosses::AnchorSetZone() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_La;
}

Float64 lrfdLosses::GetFptMax() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_fptMax;
}

Float64 lrfdLosses::GetFptMin() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_fptMin;
}

Float64 lrfdLosses::GetFptAvg() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_fptAvg;
}

Float64 lrfdLosses::GetPptMax() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_PptMax;
}

Float64 lrfdLosses::GetPptMin() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_PptMin;
}

Float64 lrfdLosses::GetPptAvg() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_PptAvg;
}

Float64 lrfdLosses::GetDeltaFptAvg() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfptAvg;
}

Float64 lrfdLosses::GetFcgpt() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_Fcgpt;
}

Float64 lrfdLosses::GetDeltaFpt() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpt;
}

Float64 lrfdLosses::GetFptr() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_fptr;
}

Float64 lrfdLosses::GetDeltaFptr() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfptr;
}

Float64 lrfdLosses::GetPtr() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_Ptr;
}

Float64 lrfdLosses::GetFcgpp() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_Fcgpp;
}

Float64 lrfdLosses::GetDeltaFpp() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpp;
}

Float64 lrfdLosses::GetDeltaFcd1() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_DeltaFcd1;
}

void lrfdLosses::UpdateLosses() const
{
   static bool bUpdating = false;

   if ( !bUpdating )
   {
      bUpdating = true;
      try
      {
         ValidateParameters();
         UpdateInitialLosses();
         UpdateHaulingLosses();
         UpdateTemporaryStrandRemovalEffect();
         UpdateLongTermLosses();
      }
      catch(...)
      {
         bUpdating = false;
         throw;
      }
      bUpdating = false;
   }

   m_IsDirty = false;
}


void lrfdLosses::UpdateInitialLosses() const
{
   UpdateRelaxationBeforeTransfer();
   UpdateElasticShortening();
   UpdatePostTensionLosses();
}

void lrfdLosses::UpdateRelaxationBeforeTransfer() const
{
   // requirement per 2004 LRFD 5.9.5.4.4b
   if ( !IsZero( m_FpjPerm ) && !(0.5*m_Fpu < m_FpjPerm) )
      THROW(lrfdXPsLosses,fpjOutOfRange);

   if ( !IsZero( m_FpjTemp ) && !(0.5*m_Fpu < m_FpjTemp) )
      THROW(lrfdXPsLosses,fpjOutOfRange);

   // Losses from jacking to release
   // Using methodology from LRFD 2004... these losses were taken out of the 2005 spec
   // and not guidance was given for their computation...
   if ( !m_bIgnoreInitialRelaxation )
   {
      // WSDOT
      Float64 t_days = ::ConvertFromSysUnits( m_ti, unitMeasure::Day );
      Float64 A = (m_Type == matPsStrand::LowRelaxation ? 40. : 10. );

      if ( m_TempStrandUsage == tsPretensioned )
      {
         if ( t_days*24. < 1 )
            m_dfpR0[0] = 0; // log10(<1) = < 0... t_days < 1/24 is less than one hour
         else
            m_dfpR0[0] = (log10(24.*t_days)/A) * (m_FpjTemp/m_Fpy - 0.55) * m_FpjTemp;
      }
      else
      {
         m_dfpR0[0] = 0; // no initial relaxation if not pre-tensioned
      }


      if ( t_days*24. < 1 )
         m_dfpR0[1] = 0; // log10(<1) = < 0... t_days < 1/24 is less than one hour
      else
         m_dfpR0[1] = (log10(24.*t_days)/A) * (m_FpjPerm/m_Fpy - 0.55) * m_FpjPerm;
   }
   else
   {
      // AASHTO
      m_dfpR0[0] = 0;
      m_dfpR0[1] = 0;
   }
}

void lrfdLosses::UpdateElasticShortening() const
{
   // Elastic shortening
   lrfdElasticShortening es(m_FpjPerm,
                            (m_TempStrandUsage == tsPretensioned ? m_FpjTemp : 0),
                            m_dfpR0[1], // perm
                            m_dfpR0[0], // temp
                            m_ApsPerm,
                            (m_TempStrandUsage == tsPretensioned ? m_ApsTemp : 0),
                            m_Ag,
                            m_Ig,
                            m_eperm,
                            m_etemp,
                            m_Mdlg,
                            1.0,
                            m_Eci,
                            m_Ep);

   m_ElasticShortening = es;

   m_dfpES[0] = m_ElasticShortening.TemporaryStrand_ElasticShorteningLosses();
   m_dfpES[1] = m_ElasticShortening.PermanentStrand_ElasticShorteningLosses();
}

void lrfdLosses::UpdatePostTensionLosses() const
{
   // initialize values relating to effect of post-tensioning
   m_dfpp   = 0;
   m_dfpF   = 0;
   m_dfpFT  = 0;
   m_La     = 0;
   m_dfpA   = 0;
   m_dfpAT  = 0;
   m_fpL    = 0;
   m_fpD    = 0;
   m_fpMax  = 0;
   m_fptMax = 0;
   m_PptMax = 0;
   m_PptMin = 0;
   m_Fcgpt  = 0;
   m_Fcgpp  = 0;
   m_dfpt   = 0;
   m_fptMin = 0;
   m_fptAvg = 0;
   m_PptAvg = 0;
   m_dfptAvg = 0;
   m_Ptr     = 0;
   m_dfptr   = 0;

   // if temp strands are post-tensioned compute losses in PT strands AND
   // effect on permanent strands
   if ( m_TempStrandUsage != tsPretensioned && !IsZero(m_FpjTemp*m_ApsTemp))
   {
      // compute loss and stress profile of one post-tensioned strand
      // friction loss
      Float64 K, x, lg;
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      {
         K = ::ConvertFromSysUnits(m_WobbleCoefficient,unitMeasure::PerMillimeter);
         x = ::ConvertFromSysUnits(m_X,unitMeasure::Millimeter);
         lg = ::ConvertFromSysUnits(m_Lg,unitMeasure::Millimeter);
      }
      else
      {
         K = ::ConvertFromSysUnits(m_WobbleCoefficient,unitMeasure::PerFeet);
         x = ::ConvertFromSysUnits(m_X,unitMeasure::Feet);
         lg = ::ConvertFromSysUnits(m_Lg,unitMeasure::Feet);
      }

      m_dfpF  = m_FpjTemp*(1 - exp(-K*x + m_AngleChange*m_FrictionCoefficient));
      m_dfpFT = m_FpjTemp*(1 - exp(-K*lg + m_AngleChange*m_FrictionCoefficient));

      // anchor set loss
      m_La = sqrt(m_Ep*m_AnchorSet*m_Lg/m_dfpFT);

      m_dfpAT = -99999;

      // strand stress at dead end and max stress over length of girder
      if ( m_La <= m_Lg )
      {
         // case 1
         // seating zone length is less than girder length
         m_dfpAT = 2*m_dfpFT*m_La/m_Lg;

         // strand stress at live end
         m_fpL = m_FpjTemp - m_dfpAT;

         // strand stress at dead end
         m_fpD   = m_FpjTemp - m_dfpFT;

         m_fpMax = m_FpjTemp - m_La*m_dfpFT/m_Lg;

         // determine effect of one pt-strand on the permanent strands
         if ( m_X <= m_La )
         {
            m_fptMax = m_fpL + m_dfpAT*m_X/(2*m_La);
         }
         else
         {
            m_fptMax = m_fpL + m_dfpAT/2 - (m_X - m_La)*m_dfpFT/m_Lg;
         }
      }
      else
      {
         // case 2
         // seating zone length is greater than girder length
         m_dfpAT = (m_AnchorSet*m_Ep + m_dfpFT*m_Lg)/m_Lg;

         // strand stress at live end
         m_fpL = m_FpjTemp - m_dfpAT;

         // strand stress at dead end
         m_fpD = m_FpjTemp - m_dfpAT + m_dfpFT;

         m_fpMax = m_fpD;

         // determine effect of one pt-strand on the permanent strands
         m_fptMax = m_FpjTemp - m_dfpAT + m_X*m_dfpFT/m_Lg;
      }

      if ( m_X <= m_La )
      {
         m_dfpA = m_dfpAT - m_dfpFT*m_X/m_La;
         m_dfpF = 0;
      }
      else
      {
         m_dfpA = 0;
      }

      // force in one strand
      m_PptMax = m_aps*m_fptMax;

      // compressive stress due to 1 strand at level of prestressing
      m_Fcgpt = m_PptMax/m_Ag + m_PptMax*m_etemp*m_etemp/m_Ig;

      // effect on the stress in the previously jacked strands is
      if ( m_TempStrandUsage == tsPTBeforeShipping )
         m_dfpt = m_Fcgpt*m_Ep/m_Ec;
      else
         m_dfpt = m_Fcgpt*m_Ep/m_Eci;

      Float64 N = m_ApsTemp/m_aps;
      m_dfptAvg = (m_dfpt + (N-1)*m_dfpt)/2;

      // stress in the last pt strand to be jacked
      m_fptMin = m_fptMax - (N-1)*m_dfpt;
      m_PptMin = m_aps*m_fptMin;

      // average stress in all pt strands
      m_fptAvg = (m_fptMax + m_fptMin)/2;

      // average pt force
      m_PptAvg = m_ApsTemp*m_fptAvg;

      // compute effect of pt on the perminate strands
      m_Fcgpp = m_PptAvg/m_Ag + m_PptAvg*m_etemp*m_eperm/m_Ig; 

      if ( m_TempStrandUsage == tsPTBeforeShipping )
         m_dfpp  = m_Fcgpp*(m_Ep/m_Ec);
      else
         m_dfpp  = m_Fcgpp*(m_Ep/m_Eci);
   }
}

void lrfdLosses::UpdateTemporaryStrandRemovalEffect() const
{
   // Change in permanent strand stress due to removal of temporary strand
   Float64 f;
   Float64 fpj = GetFpjTemporary();

   if ( IsZero(fpj) )
   {
      f = 0;
   }
   else if ( m_TempStrandUsage == tsPretensioned )
   {
      f = fpj - m_dfpR0[0]
              - m_dfpES[0]
              - TemporaryStrand_TimeDependentLossesAtShipping()
              - m_dfpp;
   }
   else if ( m_TempStrandUsage == tsPTBeforeShipping )
   {
      f = fpj - m_dfpF
              - m_dfpA
              - m_dfpt;
   }
   else
   {
      f = fpj - m_dfpF
              - m_dfpA
              - m_dfpt
              - TemporaryStrand_TimeDependentLossesAtShipping();
   }

   //_ASSERTE( f <= fpj );

   m_Ptr   = m_ApsTemp*f; // force in temporary strands immediately before removal
   m_fptr  = -m_Ptr/m_Ag - m_Ptr*m_eperm*m_etemp/m_Ig; // concrete stress change due to removal
   m_dfptr = m_fptr*m_Ep/m_Ec; // change in prestress due to removal
}

void lrfdLosses::MakeAssignment( const lrfdLosses& rOther )
{
   MakeCopy( rOther );
}

void lrfdLosses::MakeCopy( const lrfdLosses& rOther )
{
   m_Type                  = rOther.m_Type;
   m_Grade                 = rOther.m_Grade;
   m_eperm                 = rOther.m_eperm;
   m_etemp                 = rOther.m_etemp;
   m_ApsPerm               = rOther.m_ApsPerm;
   m_ApsTemp               = rOther.m_ApsTemp;
   m_aps                   = rOther.m_aps;
   m_Eci                   = rOther.m_Eci;
   m_Ec                    = rOther.m_Ec;
   m_Ecd                   = rOther.m_Ecd;
   m_Ep                    = rOther.m_Ep;
   m_Fpu                   = rOther.m_Fpu;
   m_FpjPerm               = rOther.m_FpjPerm;
   m_FpjTemp               = rOther.m_FpjTemp;
   m_Fpy                   = rOther.m_Fpy;
   m_TempStrandUsage       = rOther.m_TempStrandUsage;
   m_Fc                    = rOther.m_Fc;
   m_Fci                   = rOther.m_Fci;
   m_FcSlab                = rOther.m_FcSlab;
   m_X                     = rOther.m_X;
   m_Lg                    = rOther.m_Lg;
   m_Mdlg                  = rOther.m_Mdlg;
   m_Madlg                 = rOther.m_Madlg;
   m_Msidl                 = rOther.m_Msidl;
   m_ti                    = rOther.m_ti;
   
   m_Ag                    = rOther.m_Ag;
   m_Ig                    = rOther.m_Ig;
   m_Ybg                   = rOther.m_Ybg;
   m_Ac                    = rOther.m_Ac;
   m_Ic                    = rOther.m_Ic;
   m_Ybc                   = rOther.m_Ybc;

   m_H                     = rOther.m_H;

   m_bIgnoreInitialRelaxation = rOther.m_bIgnoreInitialRelaxation;

   m_dfpR0[0]              = rOther.m_dfpR0[0];
   m_dfpES[0]              = rOther.m_dfpES[0];

   m_dfpR0[1]              = rOther.m_dfpR0[1];
   m_dfpES[1]              = rOther.m_dfpES[1];

   m_dfpED                 = rOther.m_dfpED;

   m_dfpF                  = rOther.m_dfpF;
   m_dfpFT                 = rOther.m_dfpFT;
   m_dfpA                  = rOther.m_dfpA;
   m_dfpAT                 = rOther.m_dfpAT;
   m_dfpt                  = rOther.m_dfpt;

   m_La                    = rOther.m_La;
   m_AnchorSet             = rOther.m_AnchorSet;
   m_WobbleCoefficient     = rOther.m_WobbleCoefficient;
   m_FrictionCoefficient   = rOther.m_FrictionCoefficient;
   m_AngleChange           = rOther.m_AngleChange;

   m_fptMax                = rOther.m_fptMax;
   m_fptMin                = rOther.m_fptMin;
   m_fptAvg                = rOther.m_fptAvg;

   m_PptMax                = rOther.m_PptMax;
   m_PptMin                = rOther.m_PptMin;
   m_PptAvg                = rOther.m_PptAvg;

   m_dfptAvg               = rOther.m_dfptAvg;
   m_Fcgpt                 = rOther.m_Fcgpt;

   m_Fcgpp                 = rOther.m_Fcgpp;
   m_dfpp                  = rOther.m_dfpp;

   m_fptr                  = rOther.m_fptr;
   m_dfptr                 = rOther.m_dfptr;
   m_Ptr                   = rOther.m_Ptr;

   m_DeltaFcd1             = rOther.m_DeltaFcd1;
   m_ElasticShortening     = rOther.m_ElasticShortening;

   m_IsDirty               = rOther.m_IsDirty;
}
