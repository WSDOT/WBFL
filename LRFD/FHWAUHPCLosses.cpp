///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <Lrfd\FHWAUHPCLosses.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//======================== LIFECYCLE  =======================================
lrfdFHWAUHPCLosses::lrfdFHWAUHPCLosses()
{
}

lrfdFHWAUHPCLosses::lrfdFHWAUHPCLosses(
                         Float64 x,
                         Float64 Lg,
                         lrfdLosses::SectionPropertiesType sectionProperties,
                         WBFL::Materials::PsStrand::Grade gradePerm, // strand grade
                         WBFL::Materials::PsStrand::Type typePerm, // strand type
                         WBFL::Materials::PsStrand::Coating coatingPerm, // strand coating (none, epoxy)
                         WBFL::Materials::PsStrand::Grade gradeTemp, // strand grade
                         WBFL::Materials::PsStrand::Type typeTemp, // strand type
                         WBFL::Materials::PsStrand::Coating coatingTemp, // strand coating (none, epoxy)
                         Float64 fpjPerm, // fpj permanent strands
                         Float64 fpjTemp,  // fpj of temporary strands
                         Float64 ApsPerm,  // area of permanent strand
                         Float64 ApsTemp,   // area of TTS 
                         Float64 aps,      // area of one temp strand
                         const WBFL::Geometry::Point2d& epermRelease, // eccentricty of permanent ps strands with respect to CG of girder
                         const WBFL::Geometry::Point2d& epermFinal,
                         const WBFL::Geometry::Point2d& etemp, // eccentricty of temporary strands with respect to CG of girder
                         lrfdLosses::TempStrandUsage usage,
                         Float64 anchorSet,
                         Float64 wobble,
                         Float64 friction,
                         Float64 angleChange,

                         Float64 ShrinkageK1,
                         Float64 ShrinkageK2,
                         
                         Float64 DeckShrinkageK1,
                         Float64 DeckShrinkageK2,

                         Float64 Fc,   // 28 day strength of girder concrete
                         Float64 Fci,  // Release strength
                         Float64 FcSlab,   
                         Float64 Ec,   // Modulus of elasticity of girder
                         Float64 Eci,  // Modulus of elasticity of girder at transfer
                         Float64 Ecd,  // Modulus of elasticity of deck
                         
                         Float64 Ag,   // area of girder
                         Float64 Ixx,   // moment of inertia of girder
                         Float64 Iyy,
                         Float64 Ixy,
                         Float64 Ybg,  // Centroid of girder measured from bottom
                         Float64 Ac1,   // area of composite girder
                         Float64 Ic1,   // moment of inertia of composite
                         Float64 Ybc1,  // Centroid of composite measured from bottom
                         Float64 Ac2,   // area of composite girder
                         Float64 Ic2,   // moment of inertia of composite
                         Float64 Ybc2,  // Centroid of composite measured from bottom

                         Float64 An,   // area of girder
                         Float64 Ixxn,   // moment of inertia of girder
                         Float64 Iyyn,
                         Float64 Ixyn,
                         Float64 Ybn,  // Centroid of girder measured from bottom
                         Float64 Acn,   // area of composite girder
                         Float64 Icn,   // moment of inertia of composite
                         Float64 Ybcn,  // Centroid of composite measured from bottom
                         
                         Float64 Ad,   // area of deck
                         Float64 ed,   // eccentricity of deck CG with respect to CG of composite
                         Float64 Ksh,  // deck shrinkage strain effectiveness
                         
                         Float64 Mdlg,  // Dead load moment of girder only
                         const std::vector<std::pair<Float64, Float64>>& Madlg,  // Additional dead load on girder section (first value is moment, second is elastic gain reduction factor)
                         const std::vector<std::pair<Float64, Float64>>& Msidl1, // Superimposed dead loads, stage 1
                         const std::vector<std::pair<Float64, Float64>>& Msidl2, // Superimposed dead loads, stage 2

                         Float64 rh,  // Relative humidity [0,100]
                         Float64 ti,   // Time until prestress transfer
                         Float64 th,   // Time at hauling
                         Float64 td,   // Time to deck placement
                         Float64 tf,   // Final time
                         bool bIgnoreInitialRelaxation,
                         bool bValidateParameters,
                         RelaxationLossMethod relaxationMethod,
                         std::shared_ptr<const lrfdCreepCoefficient2005>& pGirderCreep,
                         std::shared_ptr<const lrfdCreepCoefficient2005>& pDeckCreep
                         ) :
lrfdRefinedLosses2005(x, Lg, sectionProperties, gradePerm, typePerm, coatingPerm, gradeTemp, typeTemp, coatingTemp, fpjPerm, fpjTemp, ApsPerm, ApsTemp, aps, epermRelease, epermFinal, etemp, usage, anchorSet, wobble, friction, angleChange, ShrinkageK1, ShrinkageK2,  DeckShrinkageK1, DeckShrinkageK2, 
   Fc, Fci,FcSlab, Ec, Eci, Ecd, 
   Ag,Ixx, Iyy, Ixy, Ybg, Ac1, Ic1, Ybc1, Ac2, Ic2, Ybc2,
   An, Ixxn, Iyyn, Ixyn, Ybn, Acn, Icn, Ybcn,
   Ad, ed, Ksh,
   Mdlg, Madlg, Msidl1, Msidl2,
   rh, ti,th, td, tf, bIgnoreInitialRelaxation, bValidateParameters, relaxationMethod, pGirderCreep, pDeckCreep
)
{
}

lrfdFHWAUHPCLosses::~lrfdFHWAUHPCLosses()
{
}

Float64 lrfdFHWAUHPCLosses::GetShrinkageHumidityFactor_Girder() const
{
   return 1.5 - 0.01*m_H;
}

Float64 lrfdFHWAUHPCLosses::GetShrinkageStrain_Girder() const
{
   return 0.6e-03;
}

#if defined _UNITTEST
#include <Lrfd\AutoVersion.h>
bool lrfdFHWAUHPCLosses::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("lrfdFHWAUHPCLosses");

   lrfdAutoVersion av;

   std::shared_ptr<lrfdFHWAUHPCCreepCoefficient> pGirderCreep = std::make_shared<lrfdFHWAUHPCCreepCoefficient>();
   pGirderCreep->SetFci(WBFL::Units::ConvertToSysUnits(14.0,WBFL::Units::Measure::KSI));
   pGirderCreep->SetRelHumidity(73);
   pGirderCreep->SetK1(0.62);

   std::shared_ptr<lrfdCreepCoefficient2005> pDeckCreep = std::make_shared<lrfdCreepCoefficient2005>();
   pDeckCreep->SetCuringMethod(lrfdCreepCoefficient2005::Normal);
   pDeckCreep->SetCuringMethodTimeAdjustmentFactor(WBFL::Units::ConvertToSysUnits(7, WBFL::Units::Measure::Day));
   pDeckCreep->SetFci(0.8 * WBFL::Units::ConvertToSysUnits(4.0,WBFL::Units::Measure::KSI)); // deck is non-prestressed. Use 80% of strength. See NCHRP 496 (page 27 and 30)
   pDeckCreep->SetRelHumidity(73);
   pDeckCreep->SetSurfaceArea(1.0);
   pDeckCreep->SetVolume(WBFL::Units::ConvertToSysUnits(3.940,WBFL::Units::Measure::Inch));
   pDeckCreep->SetK1(1.0);
   pDeckCreep->SetK2(1.0);

   lrfdFHWAUHPCLosses loss(19.5072, // location along girder where losses are computed
                         39.0144,    // girder length
                         sptGross,
                         WBFL::Materials::PsStrand::Grade::Gr1860,
                         WBFL::Materials::PsStrand::Type::LowRelaxation,
                         WBFL::Materials::PsStrand::Coating::None,
                         WBFL::Materials::PsStrand::Grade::Gr1860,
                         WBFL::Materials::PsStrand::Type::LowRelaxation,
                         WBFL::Materials::PsStrand::Coating::None,
                         1396186227.0505831, // fpj permanent strands
                         1396188385.8038988, // fpj of temporary strands
                         0.0051799896399999995,  // area of permanent strand
                         0.00055999887999999998,  // area of TTS 
                         0.00013999972000000000,      // area of one strand
                         WBFL::Geometry::Point2d(0,0.73344249937779116), // eccentricty of permanent ps strands with respect to CG of girder
                         WBFL::Geometry::Point2d(0,0.73344249937779116), // eccentricty of permanent ps strands with respect to CG of girder
                         WBFL::Geometry::Point2d(0,-0.81870344656815441), // eccentricty of temporary strands with respect to CG of girder
                         
                         tsPretensioned, // temporary strand usage

                         0.0095250000000000005, // anchor set
                         0.00065616797900200005, // wobble
                         0.25000000000000000, // friction
                         0, // angle change

                         0.41,1, // K for girder
                         1,1, // K fog slab

                         41368543.759020001,   // 28 day strength of girder concrete
                         35852736.609413415,  // Release strength
                         27579029.172680002,   
                         35668801112.349388,   // Modulus of elasticity of girder
                         33205846111.428368,  // Modulus of elasticity of girder at transfer
                         29123454154.024353,  // Modulus of elasticity of deck
                         
                         // Gross
                         0.56485774124999988,   // area of girder
                         0.23197765412628035,   // moment of inertia of girder Ixx
                         0.23197765412628035,   // moment of inertia of girder Iyy
                         0.0, // Ixy
                         0.80689655343184530,  // Centroid of girder measured from bottom
                         0.83035029207347855,   // area of composite girder
                         0.39856959307884982,   // moment of inertia of composite
                         1.1133322567444859,  // Centroid of composite measured from bottom
                         0.83035029207347855,   // area of composite girder
                         0.39856959307884982,   // moment of inertia of composite
                         1.1133322567444859,  // Centroid of composite measured from bottom

                         // Net
                         0.56485774124999988,   // area of girder
                         0.23197765412628035,   // moment of inertia of girder
                         0.23197765412628035,   // moment of inertia of girder Iyy
                         0.0, // Ixy
                         0.80689655343184530,  // Centroid of girder measured from bottom
                         0.83035029207347855,   // area of composite girder
                         0.39856959307884982,   // moment of inertia of composite
                         1.1133322567444859,  // Centroid of composite measured from bottom

                         0.34838640001448046,   // area of deck
                         -0.65196774325551399,   // eccentricity of deck CG with respect to CG of composite
                         1.0,
                         
                         2701223.1744837998,  // Dead load moment of girder only
                         std::vector<std::pair<Float64, Float64>>{std::make_pair(2144430.8154568151, 1.0)},  // Additional dead load on girder section
                         std::vector<std::pair<Float64, Float64>>{std::make_pair(0, 1.0)},
                         std::vector<std::pair<Float64, Float64>>{std::make_pair(494526.00384487113, 1.0)}, // Superimposed dead loads

                         75,  // Relative humidity [0,100]
                         86400.000000000000,   // Time until prestress transfer
                         864000.00000000000,   // Time at hauling
                         10368000.000000000,   // Time to deck placement
                         172800000.00000000,   // Final time
                         false,true,Refined,
                         std::shared_ptr<const lrfdCreepCoefficient2005>(std::dynamic_pointer_cast<const lrfdCreepCoefficient2005>(pGirderCreep)),
                         std::shared_ptr<const lrfdCreepCoefficient2005>(pDeckCreep)
                         );

   lrfdVersionMgr::RegisterListener( &loss );
   lrfdVersionMgr::SetVersion( lrfdVersionMgr::NinthEdition2020);
   lrfdVersionMgr::SetUnits( lrfdVersionMgr::US );

   Float64 value;

   // permanent strands
   value = loss.PermanentStrand_BeforeTransfer();
   TRY_TESTME( IsEqual(value, 13649748.378800517) );

   value = loss.PermanentStrand_AfterTransfer();
   TRY_TESTME( IsEqual(value, 13649748.378800517) );

   value = loss.PermanentStrand_AfterTemporaryStrandInstallation();
   TRY_TESTME( IsEqual(value, 13649748.378800517) );

   value = loss.PermanentStrand_AtLifting();
   TRY_TESTME( IsEqual(value, 13649748.378800517) );

   value = loss.PermanentStrand_AtShipping();
   TRY_TESTME( IsEqual(value, 81340582.966499269) );

   value = loss.PermanentStrand_BeforeTemporaryStrandRemoval();
   TRY_TESTME( IsEqual(value, 81340582.966499269) );

   value = loss.PermanentStrand_AfterTemporaryStrandRemoval();
   TRY_TESTME( IsEqual(value, 81340582.966499269) );

   value = loss.PermanentStrand_AfterDeckPlacement();
   TRY_TESTME( IsEqual(value, 139856443.92492411) );

   value = loss.PermanentStrand_AfterSIDL();
   TRY_TESTME( IsEqual(value, 139856443.92492411) );

   value = loss.PermanentStrand_Final();
   TRY_TESTME( IsEqual(value, 140798870.67772746) );

   // temporary strands
   value = loss.TemporaryStrand_BeforeTransfer();
   TRY_TESTME( IsEqual(value, 13649831.557409566) );

   value = loss.TemporaryStrand_AfterTransfer();
   TRY_TESTME( IsEqual(value, 13649831.557409566) );

   value = loss.TemporaryStrand_AfterTemporaryStrandInstallation();
   TRY_TESTME( IsEqual(value, 13649831.557409566) );

   value = loss.TemporaryStrand_AtLifting();
   TRY_TESTME( IsEqual(value, 13649831.557409566) );

   value = loss.TemporaryStrand_AtShipping();
   TRY_TESTME( IsEqual(value, 70200702.851341456) );

   value = loss.TemporaryStrand_BeforeTemporaryStrandRemoval();
   TRY_TESTME( IsEqual(value, 70200702.851341456) );

   value = loss.TemporaryStrand_AfterTemporaryStrandRemoval();
   TRY_TESTME( IsEqual(value,0.) );

   value = loss.TemporaryStrand_AfterDeckPlacement();
   TRY_TESTME( IsEqual(value,0.) );

   value = loss.TemporaryStrand_AfterSIDL();
   TRY_TESTME( IsEqual(value,0.) );

   value = loss.TemporaryStrand_Final();
   TRY_TESTME( IsEqual(value,0.) );

   lrfdVersionMgr::UnregisterListener( &loss );

   TESTME_EPILOG("lrfdFHWAUHPCLosses");
}

#endif // _UNITTEST


