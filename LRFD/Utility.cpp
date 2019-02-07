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
#include <Lrfd\Utility.h>
#include <Lrfd\VersionMgr.h>
#include <Units\SysUnits.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// precomputed conversions
static const Float64 g_3600_MM = ::ConvertToSysUnits( 3600., unitMeasure::Millimeter );
static const Float64 g_6000_MM = ::ConvertToSysUnits( 6000., unitMeasure::Millimeter );
static const Float64 g_7200_MM = ::ConvertToSysUnits( 7200., unitMeasure::Millimeter );

static const Float64 g_12_FT = ::ConvertToSysUnits( 12., unitMeasure::Feet );
static const Float64 g_20_FT = ::ConvertToSysUnits( 20., unitMeasure::Feet );
static const Float64 g_24_FT = ::ConvertToSysUnits( 24., unitMeasure::Feet );


/****************************************************************************
CLASS
   lrfdUtility
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdUtility::~lrfdUtility()
{
}

//======================== OPERATORS  =======================================
Float64 lrfdUtility::IbeamEffFlangeWidth(Float64 effSpanLength,
                                         Float64 leftSpacing,
                                         Float64 rightSpacing,
                                         Float64 tSlab,
                                         Float64 tWeb,
                                         Float64 wTopFlange,
                                         GirderPosition position)
{
   Float64 wEff;

   if ( position == Interior)
   {
      //
      // Interior Girder
      //
      Float64 w1,w2,w3;

      w1 = 0.25*effSpanLength;
      w2 = 12.0*tSlab + max(tWeb,0.5*wTopFlange);
      w3 = (leftSpacing + rightSpacing) / 2;

      wEff = min(w1,min(w2,w3));
   }
   else
   {
      //
      // Exterior Girder
      //

      Float64 w1,w2,w3;
      Float64 wEff1, wEff2;

      // Effective width on inboard side
      w1 = 0.25*effSpanLength;
      w2 = 12.0*tSlab + max(tWeb,0.5*wTopFlange);
      w3 = (position == LeftExterior) ? rightSpacing : leftSpacing;
      
      wEff1 = min(w1,min(w2,w3)) / 2;

      // Effective width on outboard side
      w1 = 0.125*effSpanLength;
      w2 = 6.0*tSlab + max(0.5*tWeb,0.25*wTopFlange);
      w3 = (position == LeftExterior) ? leftSpacing : rightSpacing;

      wEff2 = min(w1,min(w2,w3));

      wEff = wEff1 + wEff2;
   }

   return wEff;
}

Float64 lrfdUtility::GetMultiplePresenceFactor(IndexType nLanesLoaded)
{
   if ( nLanesLoaded == 0 || nLanesLoaded == 1 )
      return 1.2;

   if ( nLanesLoaded == 2 )
      return 1.0;

   if ( nLanesLoaded == 3 )
      return 0.85;

   return 0.65;
}

Float64 lrfdUtility::GetDesignLaneWidth(Float64 wCurbToCurb)
{
   Float64 wDesignLane;
   Float64 wStdLane; // Standard design lane width
   Float64 wCurbToCurbMin;
   Float64 wCurbToCurbMax;
   Uint16  nDesignLanes;

   if (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      wStdLane       = g_3600_MM;
      wCurbToCurbMin = g_6000_MM;
      wCurbToCurbMax = g_7200_MM;
   }
   else
   {
      wStdLane       = g_12_FT;
      wCurbToCurbMin = g_20_FT;
      wCurbToCurbMax = g_24_FT;
   }

   nDesignLanes = (Uint16)floor(wCurbToCurb/wStdLane);

   if ( InRange(wCurbToCurbMin, wCurbToCurb, wCurbToCurbMax) )
      wDesignLane = wCurbToCurb/2.;
   else if (nDesignLanes == 0)
      wDesignLane = wCurbToCurb;
   else
      wDesignLane = wStdLane;

   return wDesignLane;
}

Uint16 lrfdUtility::GetNumDesignLanes(Float64 wCurbToCurb)
{
   Float64 wStdLane; // Standard design lane width
   Float64 wCurbToCurbMin;
   Float64 wCurbToCurbMax;
   Uint16  nDesignLanes;

   if (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      wStdLane       = g_3600_MM;
      wCurbToCurbMin = g_6000_MM;
      wCurbToCurbMax = g_7200_MM;
   }
   else
   {
      wStdLane       = g_12_FT;
      wCurbToCurbMin = g_20_FT;
      wCurbToCurbMax = g_24_FT;
   }

   nDesignLanes = (Uint16)floor(wCurbToCurb/wStdLane);
   if (wCurbToCurb/wStdLane - nDesignLanes > 0.99999 )
      nDesignLanes++; // we are so close to the next number of design lanes, assume round off error and increment

   if ( InRange(wCurbToCurbMin, wCurbToCurb, wCurbToCurbMax) )
      nDesignLanes = 2;

   if ( wCurbToCurb < wCurbToCurbMin && nDesignLanes != 0 )
      nDesignLanes--;

   if ( nDesignLanes == 0 )
      nDesignLanes++;

   return nDesignLanes;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================
#if defined _UNITTEST
#include <MathEx.h>
#include <Lrfd\AutoVersion.h>
#include <Lrfd\VersionMgr.h>

bool Test_IbeamEffFlangeWidth(dbgLog& rlog)
{
   // Reference: WBFL\UnitTest\Supporting Documents\Effective Flange Width.mcd

   TESTME_PROLOGUE("lrfdUtility - Test_IbeamEffFlangeWidth");

   Float64 effSpanLength = 30864.;
   Float64 spacing       = 1905.;
   Float64 overhang      = 990.;
   Float64 tSlab         = 175.;
   Float64 tWeb          = 152.;
   Float64 wTopFlange    = 635.;

   Float64 effFlangeWidth;

   effFlangeWidth = lrfdUtility::IbeamEffFlangeWidth(effSpanLength,
                                                     spacing,
                                                     spacing,
                                                     tSlab,
                                                     tWeb,
                                                     wTopFlange,
                                                     lrfdUtility::Interior);
   TRY_TESTME( IsEqual(effFlangeWidth,1905.) );

   effFlangeWidth = lrfdUtility::IbeamEffFlangeWidth(effSpanLength,
                                                     overhang,
                                                     spacing,
                                                     tSlab,
                                                     tWeb,
                                                     wTopFlange,
                                                     lrfdUtility::LeftExterior);
   TRY_TESTME( IsEqual(effFlangeWidth,1942.5) );

   effFlangeWidth = lrfdUtility::IbeamEffFlangeWidth(effSpanLength,
                                                     spacing,
                                                     overhang,
                                                     tSlab,
                                                     tWeb,
                                                     wTopFlange,
                                                     lrfdUtility::RightExterior);
   TRY_TESTME( IsEqual(effFlangeWidth,1942.5) );

   TESTME_EPILOG("lrfdUtility - Test_IbeamEffFlangeWidth");
}


bool Test_GetDesignLaneWidth(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdUtility - Test_GetDesignLaneWidth");
   lrfdAutoVersion av;

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);

   lrfdVersionMgr::SetUnits( lrfdVersionMgr::US );
   TRY_TESTME( IsEqual( lrfdUtility::GetDesignLaneWidth(::ConvertToSysUnits(10.,unitMeasure::Feet) ), ::ConvertToSysUnits( 10., unitMeasure::Feet ) ) );
   TRY_TESTME( IsEqual( lrfdUtility::GetDesignLaneWidth(::ConvertToSysUnits(18.,unitMeasure::Feet) ), ::ConvertToSysUnits( 12., unitMeasure::Feet ) ) );
   TRY_TESTME( IsEqual( lrfdUtility::GetDesignLaneWidth(::ConvertToSysUnits(22.,unitMeasure::Feet) ), ::ConvertToSysUnits( 11., unitMeasure::Feet ) ) );
   TRY_TESTME( IsEqual( lrfdUtility::GetDesignLaneWidth(::ConvertToSysUnits(28.,unitMeasure::Feet) ), ::ConvertToSysUnits( 12., unitMeasure::Feet ) ) );
   TRY_TESTME( IsEqual( lrfdUtility::GetDesignLaneWidth(::ConvertToSysUnits(37.,unitMeasure::Feet) ), ::ConvertToSysUnits( 12., unitMeasure::Feet ) ) );

   lrfdVersionMgr::SetUnits( lrfdVersionMgr::SI );
   TRY_TESTME( IsEqual( lrfdUtility::GetDesignLaneWidth(::ConvertToSysUnits(3200., unitMeasure::Millimeter) ), ::ConvertToSysUnits( 3200., unitMeasure::Millimeter ) ) );
   TRY_TESTME( IsEqual( lrfdUtility::GetDesignLaneWidth(::ConvertToSysUnits(5000., unitMeasure::Millimeter) ), ::ConvertToSysUnits( 3600., unitMeasure::Millimeter ) ) );
   TRY_TESTME( IsEqual( lrfdUtility::GetDesignLaneWidth(::ConvertToSysUnits(6500.,unitMeasure::Millimeter) ), ::ConvertToSysUnits( 3250., unitMeasure::Millimeter ) ) );
   TRY_TESTME( IsEqual( lrfdUtility::GetDesignLaneWidth(::ConvertToSysUnits(7500.,unitMeasure::Millimeter) ), ::ConvertToSysUnits( 3600., unitMeasure::Millimeter ) ) );
   TRY_TESTME( IsEqual( lrfdUtility::GetDesignLaneWidth(::ConvertToSysUnits(11000.,unitMeasure::Millimeter) ), ::ConvertToSysUnits( 3600., unitMeasure::Millimeter ) ) );

   TESTME_EPILOG("lrfdUtility - Test_GetDesignLaneWidth");
}


bool Test_GetNumDesignLanes(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdUtility - Test_GetNumDesignLanes");
   lrfdAutoVersion av;

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);

   lrfdVersionMgr::SetUnits( lrfdVersionMgr::US );
   TRY_TESTME( lrfdUtility::GetNumDesignLanes(::ConvertToSysUnits(10.,unitMeasure::Feet) ) == 1 );
   TRY_TESTME( lrfdUtility::GetNumDesignLanes(::ConvertToSysUnits(18.,unitMeasure::Feet) ) == 1 );
   TRY_TESTME( lrfdUtility::GetNumDesignLanes(::ConvertToSysUnits(22.,unitMeasure::Feet) ) == 2 );
   TRY_TESTME( lrfdUtility::GetNumDesignLanes(::ConvertToSysUnits(28.,unitMeasure::Feet) ) == 2 );
   TRY_TESTME( lrfdUtility::GetNumDesignLanes(::ConvertToSysUnits(37.,unitMeasure::Feet) ) == 3 );

   lrfdVersionMgr::SetUnits( lrfdVersionMgr::SI );
   TRY_TESTME( lrfdUtility::GetNumDesignLanes(::ConvertToSysUnits(3200., unitMeasure::Millimeter) ) == 1);
   TRY_TESTME( lrfdUtility::GetNumDesignLanes(::ConvertToSysUnits(5000., unitMeasure::Millimeter) ) == 1);
   TRY_TESTME( lrfdUtility::GetNumDesignLanes(::ConvertToSysUnits(6500.,unitMeasure::Millimeter) )  == 2);
   TRY_TESTME( lrfdUtility::GetNumDesignLanes(::ConvertToSysUnits(7500.,unitMeasure::Millimeter) )  == 2);
   TRY_TESTME( lrfdUtility::GetNumDesignLanes(::ConvertToSysUnits(11000.,unitMeasure::Millimeter) ) == 3);

   TESTME_EPILOG("lrfdUtility - Test_GetNumDesignLanes");
}

bool lrfdUtility::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdUtility");

   TRY_TESTME( Test_IbeamEffFlangeWidth(rlog) );
   TRY_TESTME( Test_GetDesignLaneWidth(rlog) );
   TRY_TESTME( Test_GetNumDesignLanes(rlog) );

   TESTME_EPILOG("lrfdUtility");
}
#endif // _UNITTEST
