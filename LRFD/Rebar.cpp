///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <Lrfd\LrfdLib.h>
#include <Lrfd\Rebar.h>
#include <Lrfd/BDSManager.h>
#include <Lrfd\XCodeVersion.h>
#include <Lrfd\RebarPool.h>
#include <Lrfd\ConcreteUtil.h>

using namespace WBFL::LRFD;

Float64 Rebar::GetMaxBurstingStress(Float64 fy)
{
   PRECONDITION(0.0 < fy);
   bool is_si = ( BDSManager::GetUnits() == BDSManager::Units::SI );
   if(BDSManager::Edition::FirstEditionWith1996Interims <= BDSManager::GetEdition() )
   {
      Float64 fym = is_si ? WBFL::Units::ConvertToSysUnits(140.0, WBFL::Units::Measure::MPa) : WBFL::Units::ConvertToSysUnits(20.0, WBFL::Units::Measure::KSI);

      fy = min(fy, fym);
   }

   return fy;
}

Float64 Rebar::GetBurstingZoneLength(Float64 h)
{
   // 1994 d/4
   // 1996 d/5
   // 2002 d/4

   if (BDSManager::GetEdition() < BDSManager::Edition::FirstEditionWith1996Interims || BDSManager::Edition::SecondEditionWith2002Interims <= BDSManager::GetEdition())
      return h / 4;
   else
      return h / 5;
}

WBFL::Materials::Rebar::Size Rebar::GetMinConfinementBarSize()
{
   return WBFL::Materials::Rebar::Size::bs3;
}

Float64 Rebar::GetMaxConfinementBarSpacing()
{
   bool is_si = ( BDSManager::GetUnits() == BDSManager::Units::SI );
   Float64 bss = is_si ? WBFL::Units::ConvertToSysUnits(150, WBFL::Units::Measure::Millimeter) : WBFL::Units::ConvertToSysUnits(6, WBFL::Units::Measure::Inch);
   return bss;
}

Float64 Rebar::GetMinConfinementAvS()
{
   // #3 bars at 6" max spacing
   const RebarPool* rp = RebarPool::GetInstance();
   CHECK(rp);
   const WBFL::Materials::Rebar* pr = rp->GetRebar(WBFL::Materials::Rebar::Type::A615,WBFL::Materials::Rebar::Grade::Grade60,WBFL::Materials::Rebar::Size::bs3);
   CHECK(pr);

   Float64 s  = Rebar::GetMaxConfinementBarSpacing();
   CHECK(0.0 < s);
   Float64 av = pr->GetNominalArea();
   return av/s;
}

Float64 Rebar::GetAvOverSMin(Float64 fc, Float64 bv, Float64 fy)
{
   PRECONDITION(0 < fc);
   PRECONDITION(0 < bv);
   PRECONDITION(0 < fy);

   Float64 avs = -999999999;
   if (BDSManager::GetUnits() == BDSManager::Units::SI)
   {
      Float64 bv_u = WBFL::Units::ConvertFromSysUnits(bv, WBFL::Units::Measure::Millimeter);
      Float64 fy_u = WBFL::Units::ConvertFromSysUnits(fy, WBFL::Units::Measure::MPa);
      Float64 fc_u = WBFL::Units::ConvertFromSysUnits(fc, WBFL::Units::Measure::MPa);
      Float64 avs_u = 0.083*sqrt(fc_u)*bv_u/fy_u;
      avs = ConvertToSysUnits(avs_u, WBFL::Units::Measure::Millimeter2PerMillimeter);
   }
   else
   {
      Float64 bv_u = WBFL::Units::ConvertFromSysUnits(bv, WBFL::Units::Measure::Inch);
      Float64 fy_u = WBFL::Units::ConvertFromSysUnits(fy, WBFL::Units::Measure::KSI);
      Float64 fc_u = WBFL::Units::ConvertFromSysUnits(fc, WBFL::Units::Measure::KSI);
      Float64 avs_u = 0.0316*sqrt(fc_u)*bv_u/fy_u;
      avs = ConvertToSysUnits(avs_u, WBFL::Units::Measure::Inch2PerInch);
   }

   return avs;

}

void Rebar::GetMaxStirrupSpacing(Float64* sUnderLimit, Float64* sOverLimit)
{
   if (BDSManager::GetUnits() == BDSManager::Units::SI)
   {
      *sUnderLimit = WBFL::Units::ConvertToSysUnits(600, WBFL::Units::Measure::Millimeter);
      *sOverLimit  = WBFL::Units::ConvertToSysUnits(300, WBFL::Units::Measure::Millimeter);
   }
   else
   {
      *sUnderLimit = WBFL::Units::ConvertToSysUnits(24, WBFL::Units::Measure::Inch);
      *sOverLimit  = WBFL::Units::ConvertToSysUnits(12, WBFL::Units::Measure::Inch);
   }
}

Float64 Rebar::GetTensileDevelopmentLength(const WBFL::Materials::Rebar& rebar, Float64 fc)
{
   PRECONDITION(BDSManager::GetEdition() < BDSManager::Edition::SeventhEditionWith2015Interims);
   PRECONDITION(0 < fc);

   Float64 dl=0.0;

   Float64 ab = rebar.GetNominalArea();
   Float64 db = rebar.GetNominalDimension();
   Float64 fy = rebar.GetYieldStrength();

   // get size
   WBFL::Materials::Rebar::Size size = rebar.GetSize();

   // Equations taken from 5.11.2.1.1
   if (BDSManager::GetUnits() == BDSManager::Units::SI)
   {
      Float64 ab_u = WBFL::Units::ConvertFromSysUnits(ab,WBFL::Units::Measure::Millimeter2);
      Float64 db_u = WBFL::Units::ConvertFromSysUnits(db,WBFL::Units::Measure::Millimeter);
      Float64 fy_u = WBFL::Units::ConvertFromSysUnits(fy,WBFL::Units::Measure::MPa);
      Float64 fc_u = WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::MPa);

      Float64 dl_u = 0;

      if (size==WBFL::Materials::Rebar::Size::bs3 || size==WBFL::Materials::Rebar::Size::bs4 || size==WBFL::Materials::Rebar::Size::bs5  || size==WBFL::Materials::Rebar::Size::bs6 || size==WBFL::Materials::Rebar::Size::bs7 ||
          size==WBFL::Materials::Rebar::Size::bs8 || size==WBFL::Materials::Rebar::Size::bs9 || size==WBFL::Materials::Rebar::Size::bs10 || size==WBFL::Materials::Rebar::Size::bs11)
      {
         dl_u = 0.02*ab_u*fy_u / sqrt(fc_u);
         dl_u = max(dl_u, 0.06 * db_u * fy_u);
      }
      else if (size==WBFL::Materials::Rebar::Size::bs14)
      {
         dl_u = 25 * fy_u / sqrt(fc_u);
      }
      else if (size==WBFL::Materials::Rebar::Size::bs18)
      {
         dl_u = 34 * fy_u / sqrt(fc_u);
      }
      else
      {
         CHECK(false); // an unknown bar snuck in.
      }

      dl_u = max(dl_u, 305);

      dl = ConvertToSysUnits(dl_u,WBFL::Units::Measure::Millimeter);
   }
   else
   {
      Float64 ab_u = WBFL::Units::ConvertFromSysUnits(ab,WBFL::Units::Measure::Inch2);
      Float64 db_u = WBFL::Units::ConvertFromSysUnits(db,WBFL::Units::Measure::Inch);
      Float64 fy_u = WBFL::Units::ConvertFromSysUnits(fy,WBFL::Units::Measure::KSI);
      Float64 fc_u = WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::KSI);

      Float64 dl_u = 0;

      if (size==WBFL::Materials::Rebar::Size::bs3 || size==WBFL::Materials::Rebar::Size::bs4 || size==WBFL::Materials::Rebar::Size::bs5  || size==WBFL::Materials::Rebar::Size::bs6 || size==WBFL::Materials::Rebar::Size::bs7 ||
          size==WBFL::Materials::Rebar::Size::bs8 || size==WBFL::Materials::Rebar::Size::bs9 || size==WBFL::Materials::Rebar::Size::bs10 || size==WBFL::Materials::Rebar::Size::bs11)
      {
         dl_u = 1.25*ab_u*fy_u / sqrt(fc_u);
         dl_u = max(dl_u, 0.4 * db_u * fy_u);
      }
      else if (size==WBFL::Materials::Rebar::Size::bs14)
      {
         dl_u = 2.7*fy_u / sqrt(fc_u);
      }
      else if (size==WBFL::Materials::Rebar::Size::bs18)
      {
         dl_u = 3.5*fy_u / sqrt(fc_u);
      }
      else
      {
         CHECK(false); // an unknown bar snuck in.
      }

      dl_u = max(dl_u, 12.0);

      dl = ConvertToSysUnits(dl_u,WBFL::Units::Measure::Inch);
   }

   return dl;
}

Float64 Rebar::GetHookExtension(WBFL::Materials::Rebar::Size size,Float64 db,Usage usage,Hook hook)
{
#pragma Reminder("WORKING HERE - Revise this method... the db should be implied from Size - maybe just pass in a Rebar object")
   if (hook == Hook::hookNone)
      return 0.0; // no hook, no extension

   if ( usage == Usage::Longitudinal )
   {
      if ( hook == Hook::hook90 )
      {
         return 12*db;
      }
      else if ( hook == Hook::hook180 )
      {
         return Max(WBFL::Units::ConvertToSysUnits(2.5,WBFL::Units::Measure::Inch),4*db);
      }
   }
   else if ( usage == Usage::Transverse )
   {
      if ( hook == Hook::hook90 )
      {
         if ( size <= WBFL::Materials::Rebar::Size::bs5 )
         {
            return 6*db;
         }
         else if ( WBFL::Materials::Rebar::Size::bs6 <= size && size <= WBFL::Materials::Rebar::Size::bs8 )
         {
            return 12*db;
         }
      }
      else if ( hook == Hook::hook135 )
      {
         if ( size <= WBFL::Materials::Rebar::Size::bs8 )
         {
            return 6*db;
         }
      }
   }
   else
   {
      CHECK(usage == Usage::Seismic);
      if ( hook == Hook::hook135 )
      {
         return Max(WBFL::Units::ConvertToSysUnits(3.0,WBFL::Units::Measure::Inch),6*db);
      }
   }

   throw std::invalid_argument("Invalid combination of usage and hook type.");
   // See LRFD 5.10.2.1 for longitudinal standard hooks
   return -9999999;
}

Float64 Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size size,Float64 db,Usage usage,bool bFractional)
{
#pragma Reminder("WORKING HERE - Revise this method... the db should be implied from Size - maybe just pass in a Rebar object")
   Float64 K = 0;
   switch(size)
   {
   case WBFL::Materials::Rebar::Size::bs3:
   case WBFL::Materials::Rebar::Size::bs4:
   case WBFL::Materials::Rebar::Size::bs5:
      if ( usage == Usage::Longitudinal )
      {
         K = 6; // general
      }
      else
      {
         K = 4; // stirrups and ties
      }
      break;

   case WBFL::Materials::Rebar::Size::bs6:
   case WBFL::Materials::Rebar::Size::bs7:
   case WBFL::Materials::Rebar::Size::bs8:
      K = 6;
      break;


   case WBFL::Materials::Rebar::Size::bs9:
   case WBFL::Materials::Rebar::Size::bs10:
   case WBFL::Materials::Rebar::Size::bs11:
      K = 8;
      break;

   case WBFL::Materials::Rebar::Size::bs14:
   case WBFL::Materials::Rebar::Size::bs18:
      K = 10;
      break;

   default:
      CHECK(false); // new bar size?
   }

   if ( bFractional )
   {
      return K;
   }

   Float64 D = K*db;
   return D;
}

Float64 Rebar::GetCompressionControlledStrainLimit(WBFL::Materials::Rebar::Grade grade)
{
   Float64 ecl;
   if ( grade <= WBFL::Materials::Rebar::Grade::Grade60 )
   {
      ecl = 0.002;
   }
   else if ( WBFL::Materials::Rebar::Grade::Grade100 <= grade )
   {
      ecl = 0.004;
   }
   else
   {
      CHECK(grade == WBFL::Materials::Rebar::Grade::Grade75 || grade == WBFL::Materials::Rebar::Grade::Grade80);
      Float64 fy = (grade == WBFL::Materials::Rebar::Grade::Grade75 ? 75 : 80);
      ecl = ::LinInterp(fy-60.,0.002,0.004,100.-60.);
   }

   return ecl;
}

Float64 Rebar::GetTensionControlledStrainLimit(WBFL::Materials::Rebar::Grade grade)
{
   Float64 etl;
   if ( grade <= WBFL::Materials::Rebar::Grade::Grade75 )
   {
      etl = 0.005;
   }
   else if ( WBFL::Materials::Rebar::Grade::Grade100 <= grade )
   {
      etl = 0.008;
   }
   else
   {
      CHECK(grade == WBFL::Materials::Rebar::Grade::Grade80);
      Float64 fy = 80;
      etl = ::LinInterp(fy-75,0.005,0.008,100.-75.);
   }

   return etl;
}

REBARDEVLENGTHDETAILS Rebar::GetRebarDevelopmentLengthDetails(WBFL::Materials::Rebar::Size size, Float64 Ab, Float64 db, Float64 fy, const WBFL::Materials::SimpleConcrete& concrete, bool bIsTopBar, bool bEpoxyCoated, bool bMeetsCoverRequirements)
{
#pragma Reminder("WORKING HERE - Revise this method... the db should be implied from Size - maybe just pass in a Rebar object")
   return Rebar::GetRebarDevelopmentLengthDetails(size,Ab,db,fy,concrete.GetType(),concrete.GetFc(),concrete.HasAggSplittingStrength(),concrete.GetAggSplittingStrength(),concrete.GetDensity(), bIsTopBar, bEpoxyCoated, bMeetsCoverRequirements);
}

REBARDEVLENGTHDETAILS Rebar::GetRebarDevelopmentLengthDetails(WBFL::Materials::Rebar::Size size, Float64 Ab, Float64 db, Float64 fy, WBFL::Materials::ConcreteType type, Float64 fc, bool isFct, Float64 Fct,Float64 density, bool bIsTopBar, bool bEpoxyCoated, bool bMeetsCoverRequirements)
{
#pragma Reminder("WORKING HERE - Revise this method... the db should be implied from Size - maybe just pass in a Rebar object")
   REBARDEVLENGTHDETAILS details;
   details.Ab = Ab;
   details.db = db;
   details.fy = fy;

   details.fc = fc;

   details.lambdaRl = 1.0; // initialize lambdas even though only used for 2015+
   details.lambdaLw = 1.0;

   if ( BDSManager::Edition::SeventhEditionWith2015Interims <= BDSManager::GetEdition())
   {
      Float64 Ab = WBFL::Units::ConvertFromSysUnits(details.Ab,WBFL::Units::Measure::Inch2);
      Float64 db = WBFL::Units::ConvertFromSysUnits(details.db,WBFL::Units::Measure::Inch);
      Float64 fc = WBFL::Units::ConvertFromSysUnits(details.fc,WBFL::Units::Measure::KSI);
      Float64 fy = WBFL::Units::ConvertFromSysUnits(details.fy,WBFL::Units::Measure::KSI);

  
      Float64 ldb_min = WBFL::Units::ConvertToSysUnits(12.0, WBFL::Units::Measure::Inch);
      if (type == WBFL::Materials::ConcreteType::PCI_UHPC)
      {
         details.ldb1 = 8.0 * db * fy / 60.0;
         details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1, WBFL::Units::Measure::Inch);
         ldb_min = 0.0; // no minimum requirement
      }
      else if (type == WBFL::Materials::ConcreteType::UHPC && size <= WBFL::Materials::Rebar::Size::bs8 && 14.0 < fc)
      {
         fy = Min(fy, 100.0); // fy cannot be taken greater than 100 ksi
         Float64 Nd = (fy <= 75.0 ? 10.0 : 12.0);
         details.ldb1 = Nd * db;
         details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1, WBFL::Units::Measure::Inch);
         ldb_min = 0.0; // no minimum requirement
      }
      else
      {
         if (type == WBFL::Materials::ConcreteType::UHPC)
         {
            // GS 1.10.8.2.1 - f'c shall not be taken greater than 15 ksi in LRFD Eq. 5.10.8.2.1a-2
            Float64 fc_max = WBFL::Units::ConvertToSysUnits(15.0, WBFL::Units::Measure::KSI);
            fc = Min(fc, fc_max);
         }

         details.ldb1 = 2.4 * db * fy / sqrt(fc);
         details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1, WBFL::Units::Measure::Inch);
      }
      details.ldb2 = 0.0;


      details.ldb = Max(details.ldb1,details.ldb2,ldb_min);
   
      if (type == WBFL::Materials::ConcreteType::UHPC)
      {
         // lambda Rl is always 1.0 for UHPC - GS 1.10.8.2
         details.lambdaRl = 1.0;
      }
      else
      {
         // if this is a top bar (there is more than 12" of fresh concrete is cast below reinforcement)
         // or this is not a top bar (not more than 12" of fresh concrete cast below reinforcement) and f'c > 10.ksi
         // use 1.3, other 1.0 LRFD 5.10.8.2.1b
         details.lambdaRl = (bIsTopBar || (!bIsTopBar && 10.0 < fc)) ? 1.3 : 1.0;
      }

      // lightweight concrete factor
      if ( BDSManager::Edition::SeventhEditionWith2016Interims <= BDSManager::GetEdition())
      {
         if (type == WBFL::Materials::ConcreteType::UHPC)
            details.lambdaLw = 1.0; // GS 1.10.8.2.1
         else
            details.lambdaLw = ConcreteUtil::ComputeConcreteDensityModificationFactor(type,density,isFct,Fct,fc);

         details.factor = 1 / details.lambdaLw;// Eqn 5.11.2.1.1-1 was modified in LRFD 2016... using lambdaLw for lambda in the equation
      }
      else
      {
         if (type== WBFL::Materials::ConcreteType::Normal || type == WBFL::Materials::ConcreteType::PCI_UHPC || type == WBFL::Materials::ConcreteType::UHPC)
         {
            details.lambdaLw = 1.0;
         }
         else if (type == WBFL::Materials::ConcreteType::AllLightweight || type == WBFL::Materials::ConcreteType::SandLightweight)
         {
            details.lambdaLw = 1.3;
         }
         else
         {
            CHECK(false); // new type?
            details.lambdaLw = 1.0;
         }

         // lambda cf is for epoxy coated bars - we don't current support epoxy coated bars so lambda.cf is 1.0
         // also, lambda.Rl * lambda.cf need not be greater than 1.7... since lambda.cf is always 1.0 and lambda.Rl
         // is never greater than 1.0, the 1.7 limit is always satisfied
         details.factor = details.lambdaLw;
      }

      details.lambdaCf = 1.0;
      if (bEpoxyCoated)
      {
         details.lambdaCf = (bMeetsCoverRequirements ? 1.2 : 1.5);
      }

      Float64 rl_cf = details.lambdaRl * details.lambdaCf;
      if (1.7 < rl_cf)
      {
         rl_cf = 1.7;
         details.bRlCfLimit = true;
      }
      else
      {
         details.bRlCfLimit = false;
      }
      details.factor *= rl_cf;
   }
   else
   {
      // UHPCs depend on LRFD 2020 or later so we should never get here with UHPC concrete
      PRECONDITION(type != WBFL::Materials::ConcreteType::PCI_UHPC);
      PRECONDITION(type != WBFL::Materials::ConcreteType::UHPC);

      if ( BDSManager::GetUnits() == BDSManager::Units::US )
      {
         Float64 Ab = WBFL::Units::ConvertFromSysUnits(details.Ab,WBFL::Units::Measure::Inch2);
         Float64 db = WBFL::Units::ConvertFromSysUnits(details.db,WBFL::Units::Measure::Inch);
         Float64 fc = WBFL::Units::ConvertFromSysUnits(details.fc,WBFL::Units::Measure::KSI);
         Float64 fy = WBFL::Units::ConvertFromSysUnits(details.fy,WBFL::Units::Measure::KSI);

         if (size == WBFL::Materials::Rebar::Size::bs14)
         {
            details.ldb1 = 2.70*fy/sqrt(fc);
            details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1,WBFL::Units::Measure::Inch);
         
            details.ldb2 = 0.0;
         }
         else if (size == WBFL::Materials::Rebar::Size::bs18)
         {
            details.ldb1 = 3.5*fy/sqrt(fc);
            details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1,WBFL::Units::Measure::Inch);
         
            details.ldb2 = 0.0;
         }
         else
         {
            details.ldb1 = 1.25*Ab*fy/sqrt(fc);
            details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1,WBFL::Units::Measure::Inch);

            details.ldb2 = 0.4*db*fy;
            details.ldb2 = WBFL::Units::ConvertToSysUnits(details.ldb2,WBFL::Units::Measure::Inch);
         }

         Float64 ldb_min = WBFL::Units::ConvertToSysUnits(12.0,WBFL::Units::Measure::Inch);

         details.ldb = Max(details.ldb1,details.ldb2,ldb_min);
      }
      else
      {
         Float64 Ab = WBFL::Units::ConvertFromSysUnits(details.Ab,WBFL::Units::Measure::Millimeter2);
         Float64 db = WBFL::Units::ConvertFromSysUnits(details.db,WBFL::Units::Measure::Millimeter);
         Float64 fc = WBFL::Units::ConvertFromSysUnits(details.fc,WBFL::Units::Measure::MPa);
         Float64 fy = WBFL::Units::ConvertFromSysUnits(details.fy,WBFL::Units::Measure::MPa);
      
         if (size == WBFL::Materials::Rebar::Size::bs14)
         {
            details.ldb1 = 25*fy/sqrt(fc);
            details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1,WBFL::Units::Measure::Millimeter);
         
            details.ldb2 = 0.0;
         }
         else if (size == WBFL::Materials::Rebar::Size::bs18)
         {
            details.ldb1 = 34*fy/sqrt(fc);
            details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1,WBFL::Units::Measure::Millimeter);
         
            details.ldb2 = 0.0;
         }
         else
         {
            details.ldb1 = 0.02*Ab*fy/sqrt(fc);
            details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1,WBFL::Units::Measure::Millimeter);
         
            details.ldb2 = 0.06*db*fy;
            details.ldb2 = WBFL::Units::ConvertToSysUnits(details.ldb2,WBFL::Units::Measure::Millimeter);
         }

         Float64 ldb_min = WBFL::Units::ConvertToSysUnits(12.0,WBFL::Units::Measure::Millimeter);

         details.ldb = Max(details.ldb1,details.ldb2,ldb_min);
      }

      // Compute and apply factor for LWC
      if (type == WBFL::Materials::ConcreteType::Normal)
      {
         details.factor = 1.0;
      }
      else
      {
         if (isFct)
         {
            // compute factor
            Float64 fck  = WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::KSI);
            Float64 fctk = WBFL::Units::ConvertFromSysUnits(Fct,WBFL::Units::Measure::KSI);

            details.factor = 0.22 * sqrt(fck) / fctk;
            details.factor = Min(details.factor, 1.0);
         }
         else
         {
            // fct not specified
            if (type == WBFL::Materials::ConcreteType::AllLightweight)
            {
               details.factor = 1.3;
            }
            else if (type == WBFL::Materials::ConcreteType::SandLightweight)
            {
               details.factor = 1.2;
            }
            else
            {
               CHECK(false); // new type?
               details.factor = 1.0;
            }
         }
      }
   }

   details.ld = details.ldb * details.factor;

   return details;
}
