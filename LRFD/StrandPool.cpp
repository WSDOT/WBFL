///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2016  Washington State Department of Transportation
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
#include <Lrfd\VersionMgr.h>
#include <Lrfd\AutoVersion.h>
#include <Units\SysUnits.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdStrandPool
****************************************************************************/

lrfdStrandPool* lrfdStrandPool::ms_pInstance = 0;
std::map<Int32, boost::shared_ptr<matPsStrand> > lrfdStrandPool::ms_USStrand;
std::map<Int32, boost::shared_ptr<matPsStrand> > lrfdStrandPool::ms_SIStrand;
lrfdStrandPool::Killer lrfdStrandPool::ms_Killer;

Int32 hash( matPsStrand::Grade grade, matPsStrand::Type type, matPsStrand::Size size )
{
   Int32 hv = ((Int32)grade) | ((Int32)type) | ((Int32)size);
   return hv;
}

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdStrandPool::~lrfdStrandPool()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
lrfdStrandPool* lrfdStrandPool::GetInstance()
{
   if ( !ms_pInstance )
   {
      ms_pInstance = new lrfdStrandPool;
      ms_Killer.SetDoomed( ms_pInstance );
   }

   return ms_pInstance;
}

const matPsStrand* lrfdStrandPool::GetStrand(Int32 key,lrfdVersionMgr::Units units)
{
   std::map<Int32,boost::shared_ptr<matPsStrand> >::iterator found;

   if ( units == lrfdVersionMgr::US )
   {
      found = ms_USStrand.find( key );
      if ( found == ms_USStrand.end() )
         return 0;
   }
   else
   {
      found = ms_SIStrand.find( key );
      if ( found == ms_SIStrand.end() )
      return 0;
   }

   return (*found).second.get();
} 

const matPsStrand* lrfdStrandPool::GetStrand(Int32 key)
{
   return GetStrand(key,lrfdVersionMgr::GetUnits());
} 

const matPsStrand* lrfdStrandPool::GetStrand(matPsStrand::Grade grade,
                                             matPsStrand::Type type,
                                             matPsStrand::Size size )
{
   return GetStrand( hash(grade,type,size) );
}

Int32 lrfdStrandPool::GetStrandKey(const matPsStrand* pStrand)
{
   return hash( pStrand->GetGrade(), pStrand->GetType(), pStrand->GetSize() );
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdStrandPool::AssertValid() const
{
   return true;
}

void lrfdStrandPool::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for lrfdStrandPool") << endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

#define NEW_US_STRAND(name,grade,type,size,fpu,fpy,e,d,a) \
ms_USStrand.insert( std::make_pair(hash(grade,type,size), boost::shared_ptr<matPsStrand>(new matPsStrand(_T(name),grade,type,size,::ConvertToSysUnits(fpu,unitMeasure::KSI), ::ConvertToSysUnits(fpy, unitMeasure::KSI), ::ConvertToSysUnits(e, unitMeasure::KSI), ::ConvertToSysUnits(d,unitMeasure::Inch), ::ConvertToSysUnits(a, unitMeasure::Inch2) ) ) ) );

#define NEW_SI_STRAND(name,grade,type,size,fpu,fpy,e,d,a) \
ms_SIStrand.insert( std::make_pair(hash(grade,type,size), boost::shared_ptr<matPsStrand>(new matPsStrand(_T(name),grade,type,size,::ConvertToSysUnits(fpu,unitMeasure::MPa), ::ConvertToSysUnits(fpy, unitMeasure::MPa), ::ConvertToSysUnits(e, unitMeasure::MPa), ::ConvertToSysUnits(d,unitMeasure::Millimeter), ::ConvertToSysUnits(a, unitMeasure::Millimeter2) ) ) ) );

lrfdStrandPool::lrfdStrandPool()
{ 
   NEW_US_STRAND( "Grade 250 Stress Relieved 1/4\"",   matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D635,    250., 0.85*250., 28500., 0.25,   0.036 );
   NEW_US_STRAND( "Grade 250 Stress Relieved 5/16\"", matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D794,    250., 0.85*250., 28500., 0.3125, 0.058 );
   NEW_US_STRAND( "Grade 250 Stress Relieved 3/8\"",  matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D953,    250., 0.85*250., 28500., 0.375,  0.080 );
   NEW_US_STRAND( "Grade 250 Stress Relieved 7/16\"", matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D1111,   250., 0.85*250., 28500., 0.4375, 0.108 );
   NEW_US_STRAND( "Grade 250 Stress Relieved 1/2\"",   matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D1270,   250., 0.85*250., 28500., 0.50,   0.1440 );
   NEW_US_STRAND( "Grade 250 Stress Relieved 1/2\" Special (0.52in)",   matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D1320,   250., 0.85*250., 28500., 0.52,   0.167 );
   NEW_US_STRAND( "Grade 250 Stress Relieved 0.6\"",   matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D1524,   250., 0.85*250., 28500., 0.60,   0.216 );
   NEW_US_STRAND( "Grade 250 Stress Relieved 0.62\"",   matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D1575,   250., 0.85*250., 28500., 0.62,   0.240 );
   NEW_US_STRAND( "Grade 250 Stress Relieved 0.7\"",   matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D1778,   250., 0.85*250., 28500., 0.70,   0.294 );

   NEW_US_STRAND( "Grade 250 Low Relaxation 1/4\"",    matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D635,   250., 0.90*250., 28500., 0.25,   0.036 );
   NEW_US_STRAND( "Grade 250 Low Relaxation 5/16\"",  matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D794,   250., 0.90*250., 28500., 0.3125, 0.058 );
   NEW_US_STRAND( "Grade 250 Low Relaxation 3/8\"",   matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D953,   250., 0.90*250., 28500., 0.375,  0.080 );
   NEW_US_STRAND( "Grade 250 Low Relaxation 7/16\"",  matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D1111,  250., 0.90*250., 28500., 0.4375, 0.108 );
   NEW_US_STRAND( "Grade 250 Low Relaxation 1/2\"",    matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D1270,  250., 0.90*250., 28500., 0.50,   0.1440 );
   NEW_US_STRAND( "Grade 250 Low Relaxation 1/2\" Special (0.52in)",    matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D1320,  250., 0.90*250., 28500., 0.52,   0.167 );
   NEW_US_STRAND( "Grade 250 Low Relaxation 0.6\"",    matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D1524,  250., 0.90*250., 28500., 0.60,   0.216 );
   NEW_US_STRAND( "Grade 250 Low Relaxation 0.62\"",    matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D1575,  250., 0.90*250., 28500., 0.62,   0.240 );
   NEW_US_STRAND( "Grade 250 Low Relaxation 0.7\"",    matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D1778,  250., 0.90*250., 28500., 0.70,   0.294 );

   NEW_US_STRAND( "Grade 270 Stress Relieved 3/8\"",  matPsStrand::Gr1860, matPsStrand::StressRelieved, matPsStrand::D953,  270., 0.85*270., 28500., 0.375,  0.085 );
   NEW_US_STRAND( "Grade 270 Stress Relieved 7/16\"", matPsStrand::Gr1860, matPsStrand::StressRelieved, matPsStrand::D1111, 270., 0.85*270., 28500., 0.4375, 0.115 );
   NEW_US_STRAND( "Grade 270 Stress Relieved 1/2\"",   matPsStrand::Gr1860, matPsStrand::StressRelieved, matPsStrand::D1270, 270., 0.85*270., 28500., 0.50,   0.153 );
   NEW_US_STRAND( "Grade 270 Stress Relieved 1/2\" Special (0.52in)",   matPsStrand::Gr1860, matPsStrand::StressRelieved, matPsStrand::D1320, 270., 0.85*270., 28500., 0.52,   0.167 );
   NEW_US_STRAND( "Grade 270 Stress Relieved 0.6\"",   matPsStrand::Gr1860, matPsStrand::StressRelieved, matPsStrand::D1524, 270., 0.85*270., 28500., 0.60,   0.217 );
   NEW_US_STRAND( "Grade 270 Stress Relieved 0.62\"",   matPsStrand::Gr1860, matPsStrand::StressRelieved, matPsStrand::D1575, 270., 0.85*270., 28500., 0.62,   0.240 );
   NEW_US_STRAND( "Grade 270 Stress Relieved 0.7\"",   matPsStrand::Gr1860, matPsStrand::StressRelieved, matPsStrand::D1778, 270., 0.85*270., 28500., 0.70,   0.294 );

   NEW_US_STRAND( "Grade 270 Low Relaxation 3/8\"",   matPsStrand::Gr1860, matPsStrand::LowRelaxation, matPsStrand::D953,  270., 0.90*270., 28500.,  0.375,  0.085 );
   NEW_US_STRAND( "Grade 270 Low Relaxation 7/16\"",  matPsStrand::Gr1860, matPsStrand::LowRelaxation, matPsStrand::D1111, 270., 0.90*270., 28500.,  0.4375, 0.115 );
   NEW_US_STRAND( "Grade 270 Low Relaxation 1/2\"",    matPsStrand::Gr1860, matPsStrand::LowRelaxation, matPsStrand::D1270, 270., 0.90*270., 28500.,  0.50,   0.153 );
   NEW_US_STRAND( "Grade 270 Low Relaxation 1/2\" Special (0.52in)",    matPsStrand::Gr1860, matPsStrand::LowRelaxation, matPsStrand::D1320, 270., 0.90*270., 28500.,  0.52,   0.167 );
   NEW_US_STRAND( "Grade 270 Low Relaxation 0.6\"",    matPsStrand::Gr1860, matPsStrand::LowRelaxation, matPsStrand::D1524, 270., 0.90*270., 28500.,  0.60,   0.217 );
   NEW_US_STRAND( "Grade 270 Low Relaxation 0.62\"",    matPsStrand::Gr1860, matPsStrand::LowRelaxation, matPsStrand::D1575, 270., 0.90*270., 28500.,  0.62,   0.240 );
   NEW_US_STRAND( "Grade 270 Low Relaxation 0.7\"",    matPsStrand::Gr1860, matPsStrand::LowRelaxation, matPsStrand::D1778, 270., 0.90*270., 28500.,  0.70,   0.294 );


   NEW_SI_STRAND( "Grade 1725 Stress Relieved 6.35mm",  matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D635,  1725., 0.85*1725., 197000., 6.35,   23.22 );
   NEW_SI_STRAND( "Grade 1725 Stress Relieved 7.94mm",  matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D794,  1725., 0.85*1725., 197000., 7.94,   37.42 );
   NEW_SI_STRAND( "Grade 1725 Stress Relieved 9.53mm",  matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D953,  1725., 0.85*1725., 197000., 9.53,   51.61 );
   NEW_SI_STRAND( "Grade 1725 Stress Relieved 11.11mm", matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D1111, 1725., 0.85*1725., 197000., 11.11,  69.68 );
   NEW_SI_STRAND( "Grade 1725 Stress Relieved 12.70mm", matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D1270, 1725., 0.85*1725., 197000., 12.70,  92.90 );
   NEW_SI_STRAND( "Grade 1725 Stress Relieved 1/2\" Special (13.20mm)", matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D1320, 1725., 0.85*1725., 197000., 13.20, 107.7  );
   NEW_SI_STRAND( "Grade 1725 Stress Relieved 15.24mm", matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D1524, 1725., 0.85*1725., 197000., 15.24, 139.35 );
   NEW_SI_STRAND( "Grade 1725 Stress Relieved 15.75mm", matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D1575, 1725., 0.85*1725., 197000., 15.75, 154.84 );
   NEW_SI_STRAND( "Grade 1725 Stress Relieved 17.78mm", matPsStrand::Gr1725, matPsStrand::StressRelieved, matPsStrand::D1778, 1725., 0.85*1725., 197000., 17.78, 189.68 );

   NEW_SI_STRAND( "Grade 1725 Low Relaxation 6.35mm",  matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D635,  1725., 0.90*1725., 197000., 6.35,   23.22 );
   NEW_SI_STRAND( "Grade 1725 Low Relaxation 7.94mm",  matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D794,  1725., 0.90*1725., 197000., 7.94,   37.42 );
   NEW_SI_STRAND( "Grade 1725 Low Relaxation 9.53mm",  matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D953,  1725., 0.90*1725., 197000., 9.53,   51.61 );
   NEW_SI_STRAND( "Grade 1725 Low Relaxation 11.11mm", matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D1111, 1725., 0.90*1725., 197000., 11.11,  69.68 );
   NEW_SI_STRAND( "Grade 1725 Low Relaxation 12.70mm", matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D1270, 1725., 0.90*1725., 197000., 12.70,  92.90 );
   NEW_SI_STRAND( "Grade 1725 Low Relaxation 1/2\" Special (13.20mm)", matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D1320, 1725., 0.90*1725., 197000., 13.20, 107.70 );
   NEW_SI_STRAND( "Grade 1725 Low Relaxation 15.24mm", matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D1524, 1725., 0.90*1725., 197000., 15.24, 139.35 );
   NEW_SI_STRAND( "Grade 1725 Low Relaxation 15.75mm", matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D1575, 1725., 0.85*1725., 197000., 15.75, 154.84 );
   NEW_SI_STRAND( "Grade 1725 Low Relaxation 17.78mm", matPsStrand::Gr1725, matPsStrand::LowRelaxation, matPsStrand::D1778, 1725., 0.90*1725., 197000., 17.78, 189.68 );

   NEW_SI_STRAND( "Grade 1860 Stress Relieved 9.53mm",  matPsStrand::Gr1860, matPsStrand::StressRelieved, matPsStrand::D953,  1860., 0.85*1860., 197000., 9.53,   54.84 );
   NEW_SI_STRAND( "Grade 1860 Stress Relieved 11.11mm", matPsStrand::Gr1860, matPsStrand::StressRelieved, matPsStrand::D1111, 1860., 0.85*1860., 197000., 1.111,  74.19 );
   NEW_SI_STRAND( "Grade 1860 Stress Relieved 12.70mm", matPsStrand::Gr1860, matPsStrand::StressRelieved, matPsStrand::D1270, 1860., 0.85*1860., 197000., 12.70,  98.71 );
   NEW_SI_STRAND( "Grade 1860 Stress Relieved 1/2\" Special (13.20mm)", matPsStrand::Gr1860, matPsStrand::StressRelieved, matPsStrand::D1320, 1860., 0.85*1860., 197000., 13.20, 107.70 );
   NEW_SI_STRAND( "Grade 1860 Stress Relieved 15.24mm", matPsStrand::Gr1860, matPsStrand::StressRelieved, matPsStrand::D1524, 1860., 0.85*1860., 197000., 15.24, 140.00 );
   NEW_SI_STRAND( "Grade 1860 Stress Relieved 15.75mm", matPsStrand::Gr1860, matPsStrand::StressRelieved, matPsStrand::D1575, 1860., 0.85*1860., 197000., 15.75, 154.84 );
   NEW_SI_STRAND( "Grade 1860 Stress Relieved 17.78mm", matPsStrand::Gr1860, matPsStrand::StressRelieved, matPsStrand::D1778, 1860., 0.85*1860., 197000., 17.78, 189.68 );

   NEW_SI_STRAND( "Grade 1860 Low Relaxation 9.53mm",  matPsStrand::Gr1860, matPsStrand::LowRelaxation, matPsStrand::D953,  1860., 0.90*1860., 197000.,  9.53,   54.84 );
   NEW_SI_STRAND( "Grade 1860 Low Relaxation 11.11mm", matPsStrand::Gr1860, matPsStrand::LowRelaxation, matPsStrand::D1111, 1860., 0.90*1860., 197000.,  11.11,  74.19 );
   NEW_SI_STRAND( "Grade 1860 Low Relaxation 12.70mm", matPsStrand::Gr1860, matPsStrand::LowRelaxation, matPsStrand::D1270, 1860., 0.90*1860., 197000.,  12.70,  98.71 );
   NEW_SI_STRAND( "Grade 1860 Low Relaxation 1/2\" Special (13.20mm)", matPsStrand::Gr1860, matPsStrand::LowRelaxation, matPsStrand::D1320, 1860., 0.90*1860., 197000.,  13.20, 107.70 );
   NEW_SI_STRAND( "Grade 1860 Low Relaxation 15.24mm", matPsStrand::Gr1860, matPsStrand::LowRelaxation, matPsStrand::D1524, 1860., 0.90*1860., 197000.,  15.24, 140.00 );
   NEW_SI_STRAND( "Grade 1860 Low Relaxation 15.75mm", matPsStrand::Gr1860, matPsStrand::LowRelaxation, matPsStrand::D1575, 1860., 0.85*1860., 197000.,  15.75, 154.84 );
   NEW_SI_STRAND( "Grade 1860 Low Relaxation 17.78mm", matPsStrand::Gr1860, matPsStrand::LowRelaxation, matPsStrand::D1778, 1860., 0.90*1860., 197000.,  17.78,  189.68 );
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


/****************************************************************************
CLASS
   lrfdStrandIter
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdStrandIter::lrfdStrandIter(matPsStrand::Grade grade,matPsStrand::Type type)
{
   m_Grade = grade;
   m_Type  = type;

   // Make sure the strand pool is up and running
   lrfdStrandPool* pPool = lrfdStrandPool::GetInstance();

   Begin();
}

lrfdStrandIter::lrfdStrandIter(const lrfdStrandIter& rOther)
{
   // Make sure the strand pool is up and running
   lrfdStrandPool* pPool = lrfdStrandPool::GetInstance();

   MakeCopy( rOther );
}

lrfdStrandIter::~lrfdStrandIter()
{
}

//======================== OPERATORS  =======================================
lrfdStrandIter& lrfdStrandIter::operator=(const lrfdStrandIter& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

//======================== OPERATIONS =======================================
// predicate class to sort strands by diameter
class StrandDiaSorter
{
public:
   int operator() (const matPsStrand* ps1,const matPsStrand* ps2)
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


void lrfdStrandIter::Begin()
{
   m_Strands.clear();
   CHECK(m_Strands.size() == 0);
   CHECK(m_Strands.empty() == true);
   std::map< Int32, boost::shared_ptr<matPsStrand> >* pStrands = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI) ? &lrfdStrandPool::ms_SIStrand : &lrfdStrandPool::ms_USStrand;
   std::map< Int32, boost::shared_ptr<matPsStrand> >::const_iterator iter;
   for ( iter = pStrands->begin(); iter != pStrands->end(); iter++ )
   {
      // The following two lines are from the original implementation.  When we upgraded to
      // VC++ 6.0, the lrfdStrandPool::ms_Strand container started loosing ownership of the
      // of the matPsStrand objects.  This implementation seems to fix the problem.
      //const std::pair< Int32, std::auto_ptr<matPsStrand> >& pair = *iter;
      //const std::auto_ptr<matPsStrand>& AutoPtr = pair.second;
      const boost::shared_ptr<matPsStrand>& AutoPtr = iter->second;
      const matPsStrand* pStrand = AutoPtr.get();
      if ( pStrand->GetGrade() == m_Grade && pStrand->GetType() == m_Type )
         m_Strands.push_back( pStrand );
   }

   // sort by diameter to make list pretty
   std::sort(m_Strands.begin(), m_Strands.end(), StrandDiaSorter());

   m_Begin   = m_Strands.begin();
   m_Current = m_Begin;
   m_End     = m_Strands.end();
}

void lrfdStrandIter::End()
{
   m_Current = m_End;
}

void lrfdStrandIter::Next()
{
   if ( m_Current != m_End )
      m_Current++;
}

void lrfdStrandIter::Move(Int32 pos)
{
   m_Current = m_Begin;
   if ( m_Begin + pos > m_End )
      m_Current = m_End;
   else
      m_Current = m_Begin + pos;
}

void lrfdStrandIter::MoveBy(Int32 dPos)
{
   m_Current += dPos;
   if ( m_Current > m_End )
      m_Current = m_End;
}

lrfdStrandIter::operator void*() const
{
   if ( m_Current != m_End )
      return (void*)1;
   else
      return 0;
}

const matPsStrand* lrfdStrandIter::GetCurrentStrand() const
{
   if ( *this )
      return (*m_Current);
   else
      return 0;
}

//======================== ACCESS     =======================================
void lrfdStrandIter::SetGrade(matPsStrand::Grade grade)
{
   m_Grade = grade;
   Begin();
}

matPsStrand::Grade lrfdStrandIter::GetGrade() const
{
   return m_Grade;
}

void lrfdStrandIter::SetType(matPsStrand::Type type)
{
   m_Type = type;
   Begin();
}

matPsStrand::Type lrfdStrandIter::GetType() const
{
   return m_Type;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdStrandIter::AssertValid() const
{
   return true;
}

void lrfdStrandIter::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for lrfdStrandIter") << endl;
}

#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
void lrfdStrandIter::MakeAssignment(const lrfdStrandIter& rOther)
{
   MakeCopy( rOther );
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdStrandIter::MakeCopy(const lrfdStrandIter& rOther)
{
   m_Current = rOther.m_Current;
   m_Begin   = rOther.m_Begin;
   m_End     = rOther.m_End;
   m_Grade   = rOther.m_Grade;
   m_Type    = rOther.m_Type;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


#if defined _UNITTEST
bool lrfdStrandPool::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdStrandPool");

   lrfdAutoVersion auto_ver;

   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);

   lrfdStrandPool* pPool = lrfdStrandPool::GetInstance();
   const matPsStrand* pStrand;
   matPsStrand::Grade grade;
   matPsStrand::Type type;
   matPsStrand::Size size[] = { matPsStrand::D635,// 1/4"
                                matPsStrand::D794,// 5/16"
                                matPsStrand::D953,// 3/8"
                                matPsStrand::D1111,// 7/16"
                                matPsStrand::D1270,// 1/2"
                                matPsStrand::D1524,// 0.6"
                                matPsStrand::D1778,// 0.7"
                                matPsStrand::D1320,// 1/2 HBS (Special)
                                matPsStrand::D1575// 0.62"
   }; 

   Int32 hashval;
   Int16 cGrade, cType, cSize;
   Int16 nSize;
   Int16 cStrands = 0;

   for ( cGrade = 0; cGrade < 2; cGrade++ )
   {
      grade = (cGrade == 0 ? matPsStrand::Gr1725 : matPsStrand::Gr1860 );
      nSize = (cGrade == 0 ? 0 : 2);

      for ( cType = 0; cType < 2; cType++ )
      {
         type = (cType == 0 ? matPsStrand::StressRelieved : matPsStrand::LowRelaxation );

         for ( cSize = nSize; cSize < sizeof(size)/sizeof(matPsStrand::Size); cSize++ )
         {
            rlog << _T("Grade = ") << grade << _T(" Type = ") << type << _T(" Size = ") << size[cSize] << endl;
            hashval = hash( grade, type, size[cSize] );
            pStrand = pPool->GetStrand( hashval );
            TRY_TESTME( pStrand != 0 );
            TRY_TESTME( pStrand->GetGrade() == grade );
            TRY_TESTME( pStrand->GetType()  == type );
            TRY_TESTME( pStrand->GetSize()  == size[cSize] );

            cStrands++;
         }
      }
   }

   TRY_TESTME( cStrands == ms_USStrand.size() );


   TESTME_EPILOG("lrfdStrandPool");
}

bool lrfdStrandIter::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdStrandIter");

   lrfdStrandIter iter;
   matPsStrand::Grade grade;
   matPsStrand::Type type;
   Int16 cGrade, cType;
   Int16 nStrand;

   for ( cGrade = 0; cGrade < 2; cGrade++ )
   {
      grade = (cGrade == 0 ? matPsStrand::Gr1725 : matPsStrand::Gr1860 );
      for ( cType = 0; cType < 2; cType++ )
      {
         nStrand = 0;

         type = (cType == 0 ? matPsStrand::StressRelieved : matPsStrand::LowRelaxation );

         iter.SetGrade( grade );
         iter.SetType( type );

         for ( iter.Begin(); iter; iter.Next() )
         {
            const matPsStrand* pStrand = iter.GetCurrentStrand();
            TRY_TESTME( pStrand != 0 );

            rlog << pStrand->GetName() << endl;
            rlog << _T("Grade = ") << grade << _T(" Type = ") << type << _T(" Size = ") << pStrand->GetSize() << endl;

            TRY_TESTME( pStrand->GetGrade() == grade );
            TRY_TESTME( pStrand->GetType()  == type );
            nStrand++;
         }

         TRY_TESTME( nStrand == (cGrade == 0 ? 9 : 7) );
      }
   }

   TESTME_EPILOG("lrfdStrandIter");
}
#endif // _UNITTEST


