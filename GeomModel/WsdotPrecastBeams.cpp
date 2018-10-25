///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2013  Washington State Department of Transportation
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

#include <GeomModel\GeomModelLib.h>

#include <GeomModel\WsdotPrecastBeams.h>
#include <GeomModel\Properties.h>
#include <Units\SysUnitsMgrListener.h>
#include <Units\Measure.h>
#include <Units\SysUnits.h>
#include <mathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS gmUnitWisePrecastBeam - private class to gmWsdotPrecastBeams which 
      automatically updates its dimensions to the current base units
****************************************************************************/

class gmUnitWisePrecastBeam : public gmPrecastBeam, public unitSysUnitsMgrListener
{
public:

   //------------------------------------------------------------------------
   // gmUnitWisePrecastBeam
   // Explicit constructor.  Creates an I-beam shape with the given 
   // dimensions.  The hook point is positioned at hookPnt. All beam 
   // dimensions must be nonnegative.
   // lunit is the length unit used for all dimensions.
   gmUnitWisePrecastBeam(Float64 w1, Float64 w2, Float64 w3, Float64 w4,
                         Float64 d1, Float64 d2, Float64 d3,  Float64 d4, 
                         Float64 d5, Float64 d6, Float64 d7,
                         Float64 t1, Float64 t2,
                         const gpPoint2d& hookPnt,
                         const unitLength& rLunit);

   //------------------------------------------------------------------------
   // Destructor
   ~gmUnitWisePrecastBeam();

   //------------------------------------------------------------------------
   // listen to the system unit manager and update all units when it is updated.
   virtual void OnUpdate();
private:
   // save all dimensions in input units
   Float64   m_uD1;
   Float64   m_uD2;
   Float64   m_uD3;
   Float64   m_uD4;
   Float64   m_uD5;
   Float64   m_uD6;
   Float64   m_uD7;
   Float64   m_uT1;
   Float64   m_uT2;
   Float64   m_uW1;
   Float64   m_uW2;
   Float64   m_uW3;
   Float64   m_uW4;
   const unitLength& m_rLunit;

   // update dimensions to current system units.
   void UpdateDimensions();
};

gmUnitWisePrecastBeam::gmUnitWisePrecastBeam(
                         Float64 w1, Float64 w2, Float64 w3, Float64 w4,
                         Float64 d1, Float64 d2, Float64 d3,  Float64 d4, 
                         Float64 d5, Float64 d6, Float64 d7,
                         Float64 t1, Float64 t2,
                         const gpPoint2d& hookPnt,
                         const unitLength& rLunit):
gmPrecastBeam(),
unitSysUnitsMgrListener(),
m_uD1(d1),
m_uD2(d2),
m_uD3(d3),
m_uD4(d4),
m_uD5(d5),
m_uD6(d6),
m_uD7(d7),
m_uT1(t1),
m_uT2(t2),
m_uW1(w1),
m_uW2(w2),
m_uW3(w3),
m_uW4(w4),
m_rLunit(rLunit)
{
   SetHookPoint(hookPnt);
   UpdateDimensions();
   unitSysUnitsMgr::RegisterListener(this);
}

gmUnitWisePrecastBeam::~gmUnitWisePrecastBeam()
{
   unitSysUnitsMgr::UnregisterListener(this);
}


void gmUnitWisePrecastBeam::OnUpdate()
{
   UpdateDimensions();
}

void gmUnitWisePrecastBeam::UpdateDimensions()
{
   SetD1(::ConvertToSysUnits(m_uD1, m_rLunit));
   SetD2(::ConvertToSysUnits(m_uD2, m_rLunit));
   SetD3(::ConvertToSysUnits(m_uD3, m_rLunit));
   SetD4(::ConvertToSysUnits(m_uD4, m_rLunit));
   SetD5(::ConvertToSysUnits(m_uD5, m_rLunit));
   SetD6(::ConvertToSysUnits(m_uD6, m_rLunit));
   SetD7(::ConvertToSysUnits(m_uD7, m_rLunit));
   SetT1(::ConvertToSysUnits(m_uT1, m_rLunit));
   SetT2(::ConvertToSysUnits(m_uT2, m_rLunit));
   SetW1(::ConvertToSysUnits(m_uW1, m_rLunit));
   SetW2(::ConvertToSysUnits(m_uW2, m_rLunit));
   SetW3(::ConvertToSysUnits(m_uW3, m_rLunit));
   SetW4(::ConvertToSysUnits(m_uW4, m_rLunit));
}


/****************************************************************************
CLASS
   gmWsdotPrecastBeams
****************************************************************************/

gmWsdotPrecastBeams* gmWsdotPrecastBeams::ms_pInstance = 0;
gmWsdotPrecastBeams::Killer gmWsdotPrecastBeams::ms_Killer;

////////////////////////// PUBLIC     ///////////////////////////////////////


// Now implement gmWsdotPrecastBeam
gmWsdotPrecastBeams& gmWsdotPrecastBeams::GetInstance()
{
   if ( !ms_pInstance )
   {
      ms_pInstance = new gmWsdotPrecastBeams;
      ms_Killer.SetDoomed( ms_pInstance );
   }

   return *ms_pInstance;
}



// Metric 

const gmPrecastBeam& gmWsdotPrecastBeams::W42MG()
{
   if (ms_pW42MG.get()==0)
      ms_pW42MG = std::auto_ptr<gmPrecastBeam> (new gmUnitWisePrecastBeam(
                                               0.114, 0.0,    0.178, 0.0,
                                               0.089, 0.038,  0.0,   0.127,
                                               0.051, 0.0,    0.762,
                                               0.152, 0.152,
                                               gpPoint2d(0,0),
                                               unitMeasure::Meter));
   return *ms_pW42MG;
}

const gmPrecastBeam& gmWsdotPrecastBeams::W50MG()
{
   if (ms_pW50MG.get()==0)
      ms_pW50MG = std::auto_ptr<gmPrecastBeam> (new gmUnitWisePrecastBeam(
                                              0.178, 0.0,    0.241, 0.0,
                                              0.127, 0.051,  0.0,   0.152,
                                              0.076, 0.0,    0.864,
                                              0.152, 0.152,
                                               gpPoint2d(0,0),
                                               unitMeasure::Meter));
   return *ms_pW50MG;
}

const gmPrecastBeam& gmWsdotPrecastBeams::W58MG()
{
   if (ms_pW58MG.get()==0)
      ms_pW58MG = std::auto_ptr<gmPrecastBeam> (new gmUnitWisePrecastBeam(
                                              0.241, 0.0,    0.241, 0.0,
                                              0.127, 0.051,  0.0,    0.152,
                                              0.076, 0.0,    1.067,
                                              0.152, 0.152,
                                               gpPoint2d(0,0),
                                               unitMeasure::Meter));
   return *ms_pW58MG;
}

const gmPrecastBeam& gmWsdotPrecastBeams::W74MG()
{
   if (ms_pW74MG.get()==0)
      ms_pW74MG = std::auto_ptr<gmPrecastBeam> (new gmUnitWisePrecastBeam(
                                              0.419, 0.051, 0.241, 0.0,
                                              0.073, 0.067, 0.051, 0.152,
                                              0.076, 0.0,   1.448,
                                              0.152, 0.152,
                                               gpPoint2d(0,0),
                                               unitMeasure::Meter));
   return *ms_pW74MG;
}

// English 

const gmPrecastBeam& gmWsdotPrecastBeams::W42G()
{
   if (ms_pW42G.get()==0)
      ms_pW42G = std::auto_ptr<gmPrecastBeam> (new gmUnitWisePrecastBeam(
                                              4.5  , 0.0,    7.0  , 0.0,
                                              3.5  , 1.5  ,  0.0,   5.0,
                                              2.0  , 0.0,   30.0,
                                              6.0,   6.0,  
                                               gpPoint2d(0,0),
                                               unitMeasure::Inch));
   return *ms_pW42G;
}

const gmPrecastBeam& gmWsdotPrecastBeams::W50G()
{
   if (ms_pW50G.get()==0)
      ms_pW50G = std::auto_ptr<gmPrecastBeam> (new gmUnitWisePrecastBeam(
                                              7.0  , 0.0,    9.5  , 0.0,
                                              5.0  , 2.0  ,  0.0,   6.0,
                                              3.0  , 0.0,   34.0,
                                              6.0,   6.0,  
                                               gpPoint2d(0,0),
                                               unitMeasure::Inch));
   return *ms_pW50G;
}

const gmPrecastBeam& gmWsdotPrecastBeams::W58G()
{
   if (ms_pW58G.get()==0)
      ms_pW58G = std::auto_ptr<gmPrecastBeam> (new gmUnitWisePrecastBeam(
                                              9.5  , 0.0,    9.5  , 0.0,
                                              5.0  , 2.0  ,  0.0,   6.0,
                                              3.0  , 0.0,   42.0,
                                              6.0,   6.0,  
                                               gpPoint2d(0,0),
                                               unitMeasure::Inch));
   return *ms_pW58G;
}

const gmPrecastBeam& gmWsdotPrecastBeams::W74G()
{
   if (ms_pW74G.get()==0)
      ms_pW74G = std::auto_ptr<gmPrecastBeam> (new gmUnitWisePrecastBeam(
                                             16.5  , 2.0,    9.5  , 0.0,
                                              2.875, 2.625,  2.0,   6.0,
                                              3.0  , 0.0,   57.0,
                                              6.0,   6.0,
                                              gpPoint2d(0,0),
                                              unitMeasure::Inch));
   return *ms_pW74G;
}

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _UNITTEST
bool gmWsdotPrecastBeams::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmWsdotPrecastBeams");

   gmWsdotPrecastBeams& ri = gmWsdotPrecastBeams::GetInstance();
   gmProperties aprops;
   // metric
   ri.W42MG().GetProperties(&aprops);
   TRY_TESTME ( IsEqual(ri.W42MG().GetHeight(), 1.067,.001)) ;
   TRY_TESTME ( IsEqual(ri.W42MG().GetShearWidth(), .152)) ;
   TRY_TESTME ( IsEqual(ri.W42MG().GetTopFlangeWidth(), .38)) ;
   TRY_TESTME ( IsEqual(ri.W42MG().GetBottomFlangeWidth(), .508)) ;
   TRY_TESTME ( IsEqual(aprops.Area(), .2415, .01)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  .0318, .001)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().X(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().Y(), -.5870   ,.01)) ;

   ri.W50MG().GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), .3397  ,.01)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  .0688, .001)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().X(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().Y(), -.6916   ,.01)) ;
   TRY_TESTME ( IsEqual(ri.W50MG().GetHeight(), 1.2700,.0001)) ;
   TRY_TESTME ( IsEqual(ri.W50MG().GetShearWidth(), .152)) ;

   ri.W58MG().GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), .3900  ,.01)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  .110, .01)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().X(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().Y(), -.7630   ,.01)) ;
   TRY_TESTME ( IsEqual(ri.W58MG().GetHeight(), 1.473,.001)) ;
   TRY_TESTME ( IsEqual(ri.W58MG().GetShearWidth(), .152)) ;

   ri.W74MG().GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), .4824  ,.01)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  .2278, .001)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().X(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().Y(), -.9012   ,.01)) ;
   TRY_TESTME ( IsEqual(ri.W74MG().GetHeight(), 1.867,.0001)) ;
   TRY_TESTME ( IsEqual(ri.W74MG().GetShearWidth(), .152)) ;
 
   // english
   ri.W42G().GetProperties(&aprops);
   TRY_TESTME ( IsEqual(ri.W42G().GetHeight(), 1.067,.001)) ;
   TRY_TESTME ( IsEqual(ri.W42G().GetShearWidth(), .1524)) ;
   TRY_TESTME ( IsEqual(ri.W42G().GetTopFlangeWidth(), .381)) ;
   TRY_TESTME ( IsEqual(ri.W42G().GetBottomFlangeWidth(), .508)) ;
   TRY_TESTME ( IsEqual(aprops.Area(), .2415, .01)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  .0318, .001)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().X(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().Y(), -.5870   ,.01)) ;

   ri.W50G().GetProperties(&aprops);
   TRY_TESTME ( IsEqual(ri.W50G().GetHeight(), 1.2700,.0001)) ;
   TRY_TESTME ( IsEqual(ri.W50G().GetShearWidth(), .1524)) ;
   TRY_TESTME ( IsEqual(aprops.Area(), .3397  ,.01)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  .0689,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().X(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().Y(), -.6916   ,.01)) ;

   ri.W58G().GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), .3900  ,.01)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  .110, .01)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().X(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().Y(), -.7630   ,.01)) ;
   TRY_TESTME ( IsEqual(ri.W58G().GetHeight(), 1.473,.001)) ;
   TRY_TESTME ( IsEqual(ri.W58G().GetShearWidth(), .1524)) ;

   // make sure conversions work
   unitLength oldul = unitSysUnitsMgr::SetLengthUnit(unitMeasure::Inch);

   ri.W74G().GetProperties(&aprops);
   TRY_TESTME ( IsEqual(aprops.Area(), 747.7  ,.1)) ;
   TRY_TESTME ( IsEqual(aprops.Ixx(),  547533.2, .1)) ;
   TRY_TESTME ( IsEqual(aprops.Ixy(),  0.     ,.1)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().X(),  0.     ,.001)) ;
   TRY_TESTME ( IsEqual(aprops.Centroid().Y(), -35.48   ,.01)) ;
   TRY_TESTME ( IsEqual(ri.W74G().GetHeight(), 73.5)) ;
   TRY_TESTME ( IsEqual(ri.W74G().GetShearWidth(), 6.)) ;

   unitSysUnitsMgr::SetLengthUnit(oldul);

   TESTME_EPILOG("gmWsdotPrecastBeams");
}
#endif // _UNITTEST

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

gmWsdotPrecastBeams::gmWsdotPrecastBeams()
{
}

gmWsdotPrecastBeams::~gmWsdotPrecastBeams()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


