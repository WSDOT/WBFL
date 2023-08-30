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
#include <Lrfd\StrandPool.h>
#include <Lrfd/BDSManager.h>
#include <Lrfd\AutoVersion.h>
#include <algorithm>

using namespace WBFL::LRFD;

StrandPool* StrandPool::ms_pInstance = nullptr;
std::map<Int64, std::shared_ptr<WBFL::Materials::PsStrand> > StrandPool::ms_USStrand;
std::map<Int64, std::shared_ptr<WBFL::Materials::PsStrand> > StrandPool::ms_SIStrand;
StrandPool::Killer StrandPool::ms_Killer;

Int64 hash( WBFL::Materials::PsStrand::Grade grade, WBFL::Materials::PsStrand::Type type, WBFL::Materials::PsStrand::Coating coating, WBFL::Materials::PsStrand::Size size )
{
   Int64 hv = ((Int64)grade) | ((Int64)type) | ((Int64)coating) | ((Int64)size);
   return hv;
}

const StrandPool* StrandPool::GetInstance()
{
   if ( !ms_pInstance )
   {
      ms_pInstance = new StrandPool;
      ms_Killer.SetSingleton( ms_pInstance );
   }

   return ms_pInstance;
}

const WBFL::Materials::PsStrand* StrandPool::GetStrand(Int64 key,BDSManager::Units units) const
{
   std::map<Int64, std::shared_ptr<WBFL::Materials::PsStrand> >::iterator found;

   if ( units == BDSManager::Units::US )
   {
      found = ms_USStrand.find( key );
      if ( found == ms_USStrand.end() )
         return nullptr;
   }
   else
   {
      found = ms_SIStrand.find( key );
      if ( found == ms_SIStrand.end() )
      return nullptr;
   }

   return (*found).second.get();
} 

const WBFL::Materials::PsStrand* StrandPool::GetStrand(Int64 key) const
{
   return GetStrand(key,BDSManager::GetUnits());
} 

const WBFL::Materials::PsStrand* StrandPool::GetStrand(WBFL::Materials::PsStrand::Grade grade,
                                             WBFL::Materials::PsStrand::Type type,
                                             WBFL::Materials::PsStrand::Coating coating,
                                             WBFL::Materials::PsStrand::Size size ) const
{
   return GetStrand( hash(grade,type,coating, size) );
}

Int64 StrandPool::GetStrandKey(const WBFL::Materials::PsStrand* pStrand) const
{
   return hash( pStrand->GetGrade(), pStrand->GetType(), pStrand->GetCoating(), pStrand->GetSize() );
}

Int64 StrandPool::GetStrandKey(WBFL::Materials::PsStrand::Grade grade, WBFL::Materials::PsStrand::Type type, WBFL::Materials::PsStrand::Coating coating, WBFL::Materials::PsStrand::Size size) const
{
   return hash(grade, type, coating, size);
}

bool StrandPool::CompareStrands(const WBFL::Materials::PsStrand* pStrandA, const WBFL::Materials::PsStrand* pStrandB, bool bCompareGrade, bool bCompareType, bool bCompareCoating, bool bCompareSize) const
{
   bool bSameGrade = bCompareGrade ? (pStrandA->GetGrade() == pStrandB->GetGrade() ? true : false) : true;
   bool bSameType = bCompareType ? (pStrandA->GetType() == pStrandB->GetType() ? true : false) : true;
   bool bSameCoating = bCompareCoating ? (pStrandA->GetCoating() == pStrandB->GetCoating() ? true : false) : true;
   bool bSameSize = bCompareSize ? (pStrandA->GetSize() == pStrandB->GetSize() ? true : false) : true;
   return bSameGrade && bSameType && bSameCoating && bSameSize;
}

#define NEW_US_STRAND(name,grade,type,coasting,size,fpu,fpy,e,d,a) \
   ms_USStrand.insert( std::make_pair(hash(grade,type,coating,size), std::make_shared<WBFL::Materials::PsStrand>(_T(name),grade,type,coating,size,WBFL::Units::ConvertToSysUnits(fpu,WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(fpy, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(e, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(d,WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(a, WBFL::Units::Measure::Inch2) ) ) );

#define NEW_SI_STRAND(name,grade,type,coating,size,fpu,fpy,e,d,a) \
ms_SIStrand.insert( std::make_pair(hash(grade,type,coating,size), std::make_shared<WBFL::Materials::PsStrand>(_T(name),grade,type,coating,size,WBFL::Units::ConvertToSysUnits(fpu,WBFL::Units::Measure::MPa), WBFL::Units::ConvertToSysUnits(fpy, WBFL::Units::Measure::MPa), WBFL::Units::ConvertToSysUnits(e, WBFL::Units::Measure::MPa), WBFL::Units::ConvertToSysUnits(d,WBFL::Units::Measure::Millimeter), WBFL::Units::ConvertToSysUnits(a, WBFL::Units::Measure::Millimeter2) ) ) );

StrandPool::StrandPool()
{ 
   for ( int i = 0; i < 2; i++ )
   {
      WBFL::Materials::PsStrand::Coating coating = (i == 0 ? WBFL::Materials::PsStrand::Coating::None : WBFL::Materials::PsStrand::Coating::GritEpoxy);
      NEW_US_STRAND( "Grade 250 Stress Relieved 1/4\"",   WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D635,    250., 0.85*250., 28500., 0.25,   0.036 );
      NEW_US_STRAND( "Grade 250 Stress Relieved 5/16\"", WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D794,    250., 0.85*250., 28500., 0.3125, 0.058 );
      NEW_US_STRAND( "Grade 250 Stress Relieved 3/8\"",  WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D953,    250., 0.85*250., 28500., 0.375,  0.080 );
      NEW_US_STRAND( "Grade 250 Stress Relieved 7/16\"", WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1111,   250., 0.85*250., 28500., 0.4375, 0.108 );
      NEW_US_STRAND( "Grade 250 Stress Relieved 1/2\"",   WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1270,   250., 0.85*250., 28500., 0.50,   0.1440 );
      NEW_US_STRAND( "Grade 250 Stress Relieved 1/2\" Special (0.52in)",   WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1320,   250., 0.85*250., 28500., 0.52,   0.167 );
      NEW_US_STRAND( "Grade 250 Stress Relieved 0.6\"",   WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1524,   250., 0.85*250., 28500., 0.60,   0.216 );
      NEW_US_STRAND( "Grade 250 Stress Relieved 0.62\"",   WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1575,   250., 0.85*250., 28500., 0.62,   0.240 );
      NEW_US_STRAND( "Grade 250 Stress Relieved 0.7\"",   WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1778,   250., 0.85*250., 28500., 0.70,   0.294 );

      NEW_US_STRAND( "Grade 250 Low Relaxation 1/4\"",    WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D635,   250., 0.90*250., 28500., 0.25,   0.036 );
      NEW_US_STRAND( "Grade 250 Low Relaxation 5/16\"",  WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D794,   250., 0.90*250., 28500., 0.3125, 0.058 );
      NEW_US_STRAND( "Grade 250 Low Relaxation 3/8\"",   WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D953,   250., 0.90*250., 28500., 0.375,  0.080 );
      NEW_US_STRAND( "Grade 250 Low Relaxation 7/16\"",  WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1111,  250., 0.90*250., 28500., 0.4375, 0.108 );
      NEW_US_STRAND( "Grade 250 Low Relaxation 1/2\"",    WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1270,  250., 0.90*250., 28500., 0.50,   0.1440 );
      NEW_US_STRAND( "Grade 250 Low Relaxation 1/2\" Special (0.52in)",    WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1320,  250., 0.90*250., 28500., 0.52,   0.167 );
      NEW_US_STRAND( "Grade 250 Low Relaxation 0.6\"",    WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1524,  250., 0.90*250., 28500., 0.60,   0.216 );
      NEW_US_STRAND( "Grade 250 Low Relaxation 0.62\"",    WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1575,  250., 0.90*250., 28500., 0.62,   0.240 );
      NEW_US_STRAND( "Grade 250 Low Relaxation 0.7\"",    WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1778,  250., 0.90*250., 28500., 0.70,   0.294 );

      NEW_US_STRAND( "Grade 270 Stress Relieved 3/8\"",  WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D953,  270., 0.85*270., 28500., 0.375,  0.085 );
      NEW_US_STRAND( "Grade 270 Stress Relieved 7/16\"", WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1111, 270., 0.85*270., 28500., 0.4375, 0.115 );
      NEW_US_STRAND( "Grade 270 Stress Relieved 1/2\"",   WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1270, 270., 0.85*270., 28500., 0.50,   0.153 );
      NEW_US_STRAND( "Grade 270 Stress Relieved 1/2\" Special (0.52in)",   WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1320, 270., 0.85*270., 28500., 0.52,   0.167 );
      NEW_US_STRAND( "Grade 270 Stress Relieved 0.6\"",   WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1524, 270., 0.85*270., 28500., 0.60,   0.217 );
      NEW_US_STRAND( "Grade 270 Stress Relieved 0.62\"",   WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1575, 270., 0.85*270., 28500., 0.62,   0.240 );
      NEW_US_STRAND( "Grade 270 Stress Relieved 0.7\"",   WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1778, 270., 0.85*270., 28500., 0.70,   0.294 );

      NEW_US_STRAND( "Grade 270 Low Relaxation 3/8\"",   WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D953,  270., 0.90*270., 28500.,  0.375,  0.085 );
      NEW_US_STRAND( "Grade 270 Low Relaxation 7/16\"",  WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1111, 270., 0.90*270., 28500.,  0.4375, 0.115 );
      NEW_US_STRAND( "Grade 270 Low Relaxation 1/2\"",    WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1270, 270., 0.90*270., 28500.,  0.50,   0.153 );
      NEW_US_STRAND( "Grade 270 Low Relaxation 1/2\" Special (0.52in)",    WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1320, 270., 0.90*270., 28500.,  0.52,   0.167 );
      NEW_US_STRAND( "Grade 270 Low Relaxation 0.6\"",    WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1524, 270., 0.90*270., 28500.,  0.60,   0.217 );
      NEW_US_STRAND( "Grade 270 Low Relaxation 0.62\"",    WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1575, 270., 0.90*270., 28500.,  0.62,   0.240 );
      NEW_US_STRAND( "Grade 270 Low Relaxation 0.7\"",    WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1778, 270., 0.90*270., 28500.,  0.70,   0.294 );

      //NEW_US_STRAND("Grade 300 Low Relaxation 3/8\"", WBFL::Materials::PsStrand::Grade::Gr2070, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D953, 300., 0.90*300., 28500., 0.375, 0.085);
      //NEW_US_STRAND("Grade 300 Low Relaxation 7/16\"", WBFL::Materials::PsStrand::Grade::Gr2070, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1111, 300., 0.90*300., 28500., 0.4375, 0.115);
      //NEW_US_STRAND("Grade 300 Low Relaxation 1/2\"", WBFL::Materials::PsStrand::Grade::Gr2070, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1270, 300., 0.90*300., 28500., 0.50, 0.153);
      //NEW_US_STRAND("Grade 300 Low Relaxation 1/2\" Special (0.52in)", WBFL::Materials::PsStrand::Grade::Gr2070, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1320, 300., 0.90*300., 28500., 0.52, 0.167);
      NEW_US_STRAND("Grade 300 Low Relaxation 0.6\"", WBFL::Materials::PsStrand::Grade::Gr2070, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1524, 300., 0.90*300., 28500., 0.60, 0.217);
      //NEW_US_STRAND("Grade 300 Low Relaxation 0.62\"", WBFL::Materials::PsStrand::Grade::Gr2070, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1575, 300., 0.90*300., 28500., 0.62, 0.240);
      //NEW_US_STRAND("Grade 300 Low Relaxation 0.7\"", WBFL::Materials::PsStrand::Grade::Gr2070, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1778, 300., 0.90*300., 28500., 0.70, 0.294);

      NEW_SI_STRAND( "Grade 1725 Stress Relieved 6.35mm",  WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D635,  1725., 0.85*1725., 197000., 6.35,   23.22 );
      NEW_SI_STRAND( "Grade 1725 Stress Relieved 7.94mm",  WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D794,  1725., 0.85*1725., 197000., 7.94,   37.42 );
      NEW_SI_STRAND( "Grade 1725 Stress Relieved 9.53mm",  WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D953,  1725., 0.85*1725., 197000., 9.53,   51.61 );
      NEW_SI_STRAND( "Grade 1725 Stress Relieved 11.11mm", WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1111, 1725., 0.85*1725., 197000., 11.11,  69.68 );
      NEW_SI_STRAND( "Grade 1725 Stress Relieved 12.70mm", WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1270, 1725., 0.85*1725., 197000., 12.70,  92.90 );
      NEW_SI_STRAND( "Grade 1725 Stress Relieved 1/2\" Special (13.20mm)", WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1320, 1725., 0.85*1725., 197000., 13.20, 107.7  );
      NEW_SI_STRAND( "Grade 1725 Stress Relieved 15.24mm", WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1524, 1725., 0.85*1725., 197000., 15.24, 139.35 );
      NEW_SI_STRAND( "Grade 1725 Stress Relieved 15.75mm", WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1575, 1725., 0.85*1725., 197000., 15.75, 154.84 );
      NEW_SI_STRAND( "Grade 1725 Stress Relieved 17.78mm", WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1778, 1725., 0.85*1725., 197000., 17.78, 189.68 );

      NEW_SI_STRAND( "Grade 1725 Low Relaxation 6.35mm",  WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D635,  1725., 0.90*1725., 197000., 6.35,   23.22 );
      NEW_SI_STRAND( "Grade 1725 Low Relaxation 7.94mm",  WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D794,  1725., 0.90*1725., 197000., 7.94,   37.42 );
      NEW_SI_STRAND( "Grade 1725 Low Relaxation 9.53mm",  WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D953,  1725., 0.90*1725., 197000., 9.53,   51.61 );
      NEW_SI_STRAND( "Grade 1725 Low Relaxation 11.11mm", WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1111, 1725., 0.90*1725., 197000., 11.11,  69.68 );
      NEW_SI_STRAND( "Grade 1725 Low Relaxation 12.70mm", WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1270, 1725., 0.90*1725., 197000., 12.70,  92.90 );
      NEW_SI_STRAND( "Grade 1725 Low Relaxation 1/2\" Special (13.20mm)", WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1320, 1725., 0.90*1725., 197000., 13.20, 107.70 );
      NEW_SI_STRAND( "Grade 1725 Low Relaxation 15.24mm", WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1524, 1725., 0.90*1725., 197000., 15.24, 139.35 );
      NEW_SI_STRAND( "Grade 1725 Low Relaxation 15.75mm", WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1575, 1725., 0.85*1725., 197000., 15.75, 154.84 );
      NEW_SI_STRAND( "Grade 1725 Low Relaxation 17.78mm", WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1778, 1725., 0.90*1725., 197000., 17.78, 189.68 );

      NEW_SI_STRAND( "Grade 1860 Stress Relieved 9.53mm",  WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D953,  1860., 0.85*1860., 197000., 9.53,   54.84 );
      NEW_SI_STRAND( "Grade 1860 Stress Relieved 11.11mm", WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1111, 1860., 0.85*1860., 197000., 1.111,  74.19 );
      NEW_SI_STRAND( "Grade 1860 Stress Relieved 12.70mm", WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1270, 1860., 0.85*1860., 197000., 12.70,  98.71 );
      NEW_SI_STRAND( "Grade 1860 Stress Relieved 1/2\" Special (13.20mm)", WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1320, 1860., 0.85*1860., 197000., 13.20, 107.70 );
      NEW_SI_STRAND( "Grade 1860 Stress Relieved 15.24mm", WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1524, 1860., 0.85*1860., 197000., 15.24, 140.00 );
      NEW_SI_STRAND( "Grade 1860 Stress Relieved 15.75mm", WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1575, 1860., 0.85*1860., 197000., 15.75, 154.84 );
      NEW_SI_STRAND( "Grade 1860 Stress Relieved 17.78mm", WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, coating, WBFL::Materials::PsStrand::Size::D1778, 1860., 0.85*1860., 197000., 17.78, 189.68 );

      NEW_SI_STRAND( "Grade 1860 Low Relaxation 9.53mm",  WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D953,  1860., 0.90*1860., 197000.,  9.53,   54.84 );
      NEW_SI_STRAND( "Grade 1860 Low Relaxation 11.11mm", WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1111, 1860., 0.90*1860., 197000.,  11.11,  74.19 );
      NEW_SI_STRAND( "Grade 1860 Low Relaxation 12.70mm", WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1270, 1860., 0.90*1860., 197000.,  12.70,  98.71 );
      NEW_SI_STRAND( "Grade 1860 Low Relaxation 1/2\" Special (13.20mm)", WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1320, 1860., 0.90*1860., 197000.,  13.20, 107.70 );
      NEW_SI_STRAND( "Grade 1860 Low Relaxation 15.24mm", WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1524, 1860., 0.90*1860., 197000.,  15.24, 140.00 );
      NEW_SI_STRAND( "Grade 1860 Low Relaxation 15.75mm", WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1575, 1860., 0.85*1860., 197000.,  15.75, 154.84 );
      NEW_SI_STRAND( "Grade 1860 Low Relaxation 17.78mm", WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1778, 1860., 0.90*1860., 197000.,  17.78,  189.68 );

      //NEW_SI_STRAND("Grade 2070 Low Relaxation 9.53mm", WBFL::Materials::PsStrand::Grade::Gr2070, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D953, 2070., 0.90*2070., 197000., 9.53, 54.84);
      //NEW_SI_STRAND("Grade 2070 Low Relaxation 11.11mm", WBFL::Materials::PsStrand::Grade::Gr2070, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1111, 2070., 0.90*2070., 197000., 11.11, 74.19);
      //NEW_SI_STRAND("Grade 2070 Low Relaxation 12.70mm", WBFL::Materials::PsStrand::Grade::Gr2070, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1270, 2070., 0.90*2070., 197000., 12.70, 98.71);
      //NEW_SI_STRAND("Grade 2070 Low Relaxation 1/2\" Special (13.20mm)", WBFL::Materials::PsStrand::Grade::Gr2070, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1320, 2070., 0.90*2070., 197000., 13.20, 107.70);
      NEW_SI_STRAND("Grade 2070 Low Relaxation 15.24mm", WBFL::Materials::PsStrand::Grade::Gr2070, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1524, 2070., 0.90*2070., 197000., 15.24, 140.00);
      //NEW_SI_STRAND("Grade 2070 Low Relaxation 15.75mm", WBFL::Materials::PsStrand::Grade::Gr2070, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1575, 2070., 0.85*2070., 197000., 15.75, 154.84);
      //NEW_SI_STRAND("Grade 2070 Low Relaxation 17.78mm", WBFL::Materials::PsStrand::Grade::Gr2070, WBFL::Materials::PsStrand::Type::LowRelaxation, coating, WBFL::Materials::PsStrand::Size::D1778, 2070., 0.90*2070., 197000., 17.78, 189.68);
   }
}

////////////////////////////////////////////////////////////

StrandIter::StrandIter(WBFL::Materials::PsStrand::Grade grade,WBFL::Materials::PsStrand::Type type,WBFL::Materials::PsStrand::Coating coating)
{
   m_Grade = grade;
   m_Type  = type;
   m_Coating = coating;

   // Make sure the strand pool is up and running
   const StrandPool* pPool = StrandPool::GetInstance();

   Begin();
}


// predicate class to sort strands by diameter
class StrandDiaSorter
{
public:
   int operator() (const WBFL::Materials::PsStrand* ps1,const WBFL::Materials::PsStrand* ps2)
   {
      if (ps1->GetNominalDiameter() == ps2->GetNominalDiameter() )
      {
         return ps1->GetUltimateStrength() < ps2->GetUltimateStrength();
      }
      else
      {
         return ps1->GetNominalDiameter() < ps2->GetNominalDiameter();
      }
   }
};


void StrandIter::Begin()
{
   m_Strands.clear();
   CHECK(m_Strands.size() == 0);
   CHECK(m_Strands.empty() == true);
   std::map< Int64, std::shared_ptr<WBFL::Materials::PsStrand> >* pStrands = (BDSManager::GetUnits() == BDSManager::Units::SI) ? &StrandPool::ms_SIStrand : &StrandPool::ms_USStrand;
   std::map< Int64, std::shared_ptr<WBFL::Materials::PsStrand> >::const_iterator iter;
   for ( iter = pStrands->begin(); iter != pStrands->end(); iter++ )
   {
      // The following two lines are from the original implementation.  When we upgraded to
      // VC++ 6.0, the StrandPool::ms_Strand container started loosing ownership of the
      // of the WBFL::Materials::PsStrand objects.  This implementation seems to fix the problem.
      //const std::pair< Int64, std::unique_ptr<WBFL::Materials::PsStrand> >& pair = *iter;
      //const std::unique_ptr<WBFL::Materials::PsStrand>& AutoPtr = pair.second;
      const std::shared_ptr<WBFL::Materials::PsStrand>& AutoPtr = iter->second;
      const WBFL::Materials::PsStrand* pStrand = AutoPtr.get();
      if ( pStrand->GetGrade() == m_Grade && pStrand->GetType() == m_Type && pStrand->GetCoating() == m_Coating )
         m_Strands.push_back( pStrand );
   }

   // sort by diameter to make list pretty
   std::sort(m_Strands.begin(), m_Strands.end(), StrandDiaSorter());

   m_Begin   = m_Strands.begin();
   m_Current = m_Begin;
   m_End     = m_Strands.end();
}

void StrandIter::End()
{
   m_Current = m_End;
}

void StrandIter::Next()
{
   if ( m_Current != m_End )
      m_Current++;
}

void StrandIter::Move(Int64 pos)
{
   m_Current = m_Begin;
   if ( m_Begin + pos > m_End )
      m_Current = m_End;
   else
      m_Current = m_Begin + pos;
}

void StrandIter::MoveBy(Int64 dPos)
{
   m_Current += dPos;
   if ( m_Current > m_End )
      m_Current = m_End;
}

StrandIter::operator void*() const
{
   if ( m_Current != m_End )
      return (void*)1;
   else
      return nullptr;
}

const WBFL::Materials::PsStrand* StrandIter::GetCurrentStrand() const
{
   if ( *this )
      return (*m_Current);
   else
      return nullptr;
}

void StrandIter::SetGrade(WBFL::Materials::PsStrand::Grade grade)
{
   m_Grade = grade;
   Begin();
}

WBFL::Materials::PsStrand::Grade StrandIter::GetGrade() const
{
   return m_Grade;
}

void StrandIter::SetType(WBFL::Materials::PsStrand::Type type)
{
   m_Type = type;
   Begin();
}

WBFL::Materials::PsStrand::Type StrandIter::GetType() const
{
   return m_Type;
}

void StrandIter::SetCoating(WBFL::Materials::PsStrand::Coating coating)
{
   m_Coating = coating;
   Begin();
}

WBFL::Materials::PsStrand::Coating StrandIter::GetCoating() const
{
   return m_Coating;
}
