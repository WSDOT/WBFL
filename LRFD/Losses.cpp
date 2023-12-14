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
#include <Lrfd\Losses.h>
#include <Lrfd\XPsLosses.h>
#include <Lrfd/BDSManager.h>
#include <Units\Convert.h>

using namespace WBFL::LRFD;

// NOTE: Eccentricities have the opposite sign from the coordinate system used to compute stresses
// That is [(Pex*Ixx + Pey*Ixy)(x) - (Pey*Iyy + Pex*Ixy)(y)]/(IxxIyy - Ixy^2)
// x = -ex, y = -ey
// positive ex is to the left of Y axis
// positive ey is below the X axis
// these are negative coordinates

Losses::Losses(Float64 x,
   Float64 Lg,
   Losses::SectionPropertiesType sectionProperties,
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
   const WBFL::Geometry::Point2d& epermRelease, // eccentricity of permanent ps strands with respect to CG of girder
   const WBFL::Geometry::Point2d& epermFinal,
   const WBFL::Geometry::Point2d& etemp, // eccentricity of temporary strands with respect to CG of girder
   Losses::TempStrandUsage usage,
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
   const std::vector<std::pair<Float64, Float64>>& Madlg,  // Additional dead load on girder section
   const std::vector<std::pair<Float64, Float64>>& Msidl1, // Superimposed dead loads
   const std::vector<std::pair<Float64, Float64>>& Msidl2, // Superimposed dead loads

   Float64 Ag,   // area of girder
   Float64 Ixx,   // moment of inertia of girder
   Float64 Iyy,
   Float64 Ixy,
   Float64 Ybg,   // Centroid of girder measured from bottom
   Float64 Ac1,    // Area of the composite girder and deck
   Float64 Ic1,    // Moment of inertia of composite
   Float64 Ybc1,   // Centroid of composite measured from bottom
   Float64 Ac2,    // Area of the composite girder and deck
   Float64 Ic2,    // Moment of inertia of composite
   Float64 Ybc2,   // Centroid of composite measured from bottom

   Float64 An,   // area of girder
   Float64 Ixxn,   // moment of inertia of girder
   Float64 Iyyn,
   Float64 Ixyn,
   Float64 Ybn,   // Centroid of girder measured from bottom
   Float64 Acn,    // Area of the composite girder and deck
   Float64 Icn,    // Moment of inertia of composite
   Float64 Ybcn,   // Centroid of composite measured from bottom

   Float64 rh, // relative humidity
   Float64 ti,   // Time until prestress transfer

   bool bIgnoreInitialRelaxation,
   bool bValidateParameters
)
{
   Init();

   m_bValidateParameters = bValidateParameters;
   m_GradePerm = gradePerm;
   m_TypePerm = typePerm;
   m_CoatingPerm = coatingPerm;
   m_GradeTemp = gradeTemp;
   m_TypeTemp = typeTemp;
   m_CoatingTemp = coatingTemp;
   m_FpjPerm = fpjPerm;
   m_FpjTemp = fpjTemp;
   m_ApsPerm = ApsPerm;
   m_ApsTemp = ApsTemp;
   m_aps = aps;
   m_epermRelease = epermRelease;
   m_epermFinal = epermFinal;
   m_etemp = etemp;
   m_Fc = Fc;
   m_Fci = Fci;
   m_FcSlab = FcSlab;
   m_Ec = Ec;
   m_Eci = Eci;
   m_Ecd = Ecd;

   m_X = x;
   m_Lg = Lg;

   m_TempStrandUsage = usage;
   m_AnchorSet = anchorSet;
   m_WobbleCoefficient = wobble;
   m_FrictionCoefficient = friction;
   m_AngleChange = angleChange;

   m_Ep = PsStrand::GetModE();

   m_FpuPerm = PsStrand::GetUltimateStrength(m_GradePerm);
   m_FpyPerm = PsStrand::GetYieldStrength(m_GradePerm, m_TypePerm);
   m_FpuTemp = PsStrand::GetUltimateStrength(m_GradeTemp);
   m_FpyTemp = PsStrand::GetYieldStrength(m_GradeTemp, m_TypeTemp);

   m_Mdlg = Mdlg;
   m_InputMadlg = Madlg;
   m_InputMsidl1 = Msidl1;
   m_InputMsidl2 = Msidl2;

   m_bIgnoreInitialRelaxation = bIgnoreInitialRelaxation;

   m_SectionProperties = sectionProperties;

   m_Ag                    = Ag;
   m_Ixx = Ixx;
   m_Iyy = Iyy;
   m_Ixy = Ixy;
   m_Ybg                   = Ybg;
   m_Ac1 = Ac1;
   m_Ic1 = Ic1;
   m_Ybc1 = Ybc1;
   m_Ac2 = Ac2;
   m_Ic2 = Ic2;
   m_Ybc2 = Ybc2;

   m_An                    = An;
   m_Ixxn = Ixxn;
   m_Iyyn = Iyyn;
   m_Ixyn = Ixyn;
   m_Ybn                   = Ybn;
   m_Acn                   = Acn;
   m_Icn                   = Icn;
   m_Ybcn                  = Ybcn;

   m_H = rh;

   m_ti = ti;

   m_IsDirty               = true;
}

Losses::Losses()
{
   Init();

   m_TypePerm                  = WBFL::Materials::PsStrand::Type::LowRelaxation;
   m_GradePerm                 = WBFL::Materials::PsStrand::Grade::Gr1860;
   m_CoatingPerm               = WBFL::Materials::PsStrand::Coating::None;

   m_TypeTemp                  = WBFL::Materials::PsStrand::Type::LowRelaxation;
   m_GradeTemp                 = WBFL::Materials::PsStrand::Grade::Gr1860;
   m_CoatingTemp               = WBFL::Materials::PsStrand::Coating::None;

   m_TempStrandUsage = TempStrandUsage::Pretensioned;

   m_FpjPerm               = 0;
   m_FpjTemp               = 0;
   m_ApsPerm               = 0;
   m_ApsTemp               = 0;
   m_aps                   = 0;
   //m_epermRelease          = 0;
   //m_epermFinal            = 0;
   //m_etemp                 = 0;
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

   m_Ep                    = PsStrand::GetModE();
   m_FpuPerm               = PsStrand::GetUltimateStrength( m_GradePerm );
   m_FpyPerm               = PsStrand::GetYieldStrength( m_GradePerm, m_TypePerm );
   m_FpuTemp               = PsStrand::GetUltimateStrength( m_GradeTemp );
   m_FpyTemp               = PsStrand::GetYieldStrength( m_GradeTemp, m_TypeTemp );

   m_Mdlg                  = 0;
   //m_Madlg                 = 0;
   //m_Msidl1 = 0;
   //m_Msidl2 = 0;

   m_bIgnoreInitialRelaxation = true;

   m_SectionProperties = SectionPropertiesType::Gross;

   m_Ag                    = 0;
   m_Ixx                    = 0;
   m_Iyy = 0;
   m_Ixy = 0;
   m_Ybg                   = 0;
   m_Ac1 = 0;
   m_Ic1 = 0;
   m_Ybc1 = 0;
   m_Ac2 = 0;
   m_Ic2 = 0;
   m_Ybc2 = 0;

   m_An                    = 0;
   m_Ixxn                    = 0;
   m_Iyyn = 0;
   m_Ixyn = 0;
   m_Ybn                   = 0;
   m_Acn                   = 0;
   m_Icn                   = 0;
   m_Ybcn                  = 0;

   m_H = 0;

   m_ti = 0;

   m_IsDirty               = true;
}

void Losses::Init()
{
   m_bValidateParameters = true;
   m_dfpR0[TEMPORARY_STRAND] = 0;
   m_dfpR0[PERMANENT_STRAND] = 0;
   m_dfpES[TEMPORARY_STRAND] = 0;
   m_dfpES[PERMANENT_STRAND] = 0;
   m_dfpED[WITH_ELASTIC_GAIN_REDUCTION] = 0;
   m_dfpED[WITHOUT_ELASTIC_GAIN_REDUCTION] = 0;
   m_dfpSIDL[WITH_ELASTIC_GAIN_REDUCTION] = 0;
   m_dfpSIDL[WITHOUT_ELASTIC_GAIN_REDUCTION] = 0;
   m_dfpSS = 0;
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
   m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION] = 0;
   m_DeltaFcd1[WITHOUT_ELASTIC_GAIN_REDUCTION] = 0;
   m_DeltaFcd2[WITH_ELASTIC_GAIN_REDUCTION] = 0;
   m_DeltaFcd2[WITHOUT_ELASTIC_GAIN_REDUCTION] = 0;
   m_dfpF = 0;
   m_dfpFT = 0;
   m_dfpA = 0;
   m_dfpAT = 0;
   m_La = 0;
}

void Losses::OnUpdate()
{
   BDSManagerListener::OnUpdate(); // call base class

   // Nothing actually changes.
}

Float64 Losses::GetFpyPermanent() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_FpyPerm;
}

Float64 Losses::GetFpyTemporary() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_FpyTemp;
}

Float64 Losses::GetEp() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_Ep;
}

Float64 Losses::GetApsPermanent() const
{ 
   return m_ApsPerm; 
}

void Losses::SetApsPermanent(Float64 Aps)
{ 
   if ( !IsEqual(m_ApsPerm,Aps) )
   {
      m_ApsPerm = Aps;
      m_IsDirty = true; 
   }
}

Float64 Losses::GetApsTemporary() const
{ 
   return m_ApsTemp; 
}

void Losses::SetApsTemporary(Float64 Aps)
{ 
   if ( !IsEqual(m_ApsTemp,Aps) )
   {
      m_ApsTemp = Aps;
      m_IsDirty = true; 
   }
}

void Losses::SetStrandArea(Float64 aps)
{
   if ( !IsEqual(m_aps,aps) )
   {
      m_aps = aps;
      m_IsDirty = true;
   }
}

Float64 Losses::GetStrandArea() const
{
   return m_aps;
}

void Losses::SetEccPermanentRelease(const WBFL::Geometry::Point2d& e)
{
   if ( m_epermRelease != e )
   {
      m_epermRelease = e;
      m_IsDirty = true;
   }
}

const WBFL::Geometry::Point2d& Losses::GetEccPermanentRelease() const
{
   return m_epermRelease;
}

void Losses::SetEccPermanentFinal(const WBFL::Geometry::Point2d& e)
{
   if ( m_epermFinal != e )
   {
      m_epermFinal = e;
      m_IsDirty = true;
   }
}

const WBFL::Geometry::Point2d& Losses::GetEccPermanentFinal() const
{
   return m_epermFinal;
}

void Losses::SetEccTemporary(const WBFL::Geometry::Point2d& e)
{
   if ( m_etemp != e )
   {
      m_etemp = e;
      m_IsDirty = true;
   }
}

const WBFL::Geometry::Point2d& Losses::GetEccTemporary() const
{
   return m_etemp;
}

Float64 Losses::GetEccpc() const
{
   // eccentricity of permanent strand on composite girder
   return m_epermFinal.Y() + (m_Ybc2 - m_Ybg);
}

WBFL::Geometry::Point2d Losses::GetEccpgRelease() const
{
   // eccentricity of all strand on non-composite girder
   Float64 Aps = m_ApsPerm + m_ApsTemp;
   WBFL::Geometry::Point2d ecc = IsZero(Aps) ? WBFL::Geometry::Point2d(0,0) : (m_ApsPerm*m_epermRelease + m_ApsTemp*m_etemp)/Aps;
   return ecc;
}

WBFL::Geometry::Point2d Losses::GetEccpgFinal() const
{
   // eccentricity of all strand on non-composite girder
   Float64 Aps = m_ApsPerm + m_ApsTemp;
   WBFL::Geometry::Point2d ecc = IsZero(Aps) ? WBFL::Geometry::Point2d(0,0) : (m_ApsPerm*m_epermFinal + m_ApsTemp*m_etemp)/Aps;
   return ecc;
}

void Losses::SetNoncompositeProperties(Float64 Ag, Float64 Ybg, Float64 Ixx, Float64 Iyy, Float64 Ixy)
{
   m_Ag = Ag;
   m_Ybg = Ybg;
   m_Ixx = Ixx;
   m_Iyy = Iyy;
   m_Ixy = Ixy;
   m_IsDirty = true;
}

void Losses::GetNoncompositeProperties(Float64* pAg, Float64* pYbg, Float64* pIxx, Float64* pIyy, Float64* pIxy) const
{
   *pAg = m_Ag;
   *pYbg = m_Ybg;
   *pIxx = m_Ixx;
   *pIyy = m_Iyy;
   *pIxy = m_Ixy;
}

void Losses::SetNetNoncompositeProperties(Float64 Ag, Float64 Ybg, Float64 Ixx, Float64 Iyy, Float64 Ixy)
{
   m_An = Ag;
   m_Ybn = Ybg;
   m_Ixxn = Ixx;
   m_Iyyn = Iyy;
   m_Ixyn = Ixy;
   m_IsDirty = true;
}

void Losses::GetNetNoncompositeProperties(Float64* pAg, Float64* pYbg, Float64* pIxx, Float64* pIyy, Float64* pIxy) const
{
   *pAg = m_An;
   *pYbg = m_Ybn;
   *pIxx = m_Ixxn;
   *pIyy = m_Iyyn;
   *pIxy = m_Ixyn;
}

void Losses::SetCompositeProperties1(Float64 Ag, Float64 Ybg, Float64 Ixx)
{
   m_Ac1 = Ag;
   m_Ybc1 = Ybg;
   m_Ic1 = Ixx;
   m_IsDirty = true;
}

void Losses::GetCompositeProperties1(Float64* pAg, Float64* pYbg, Float64* pIxx) const
{
   *pAg = m_Ac1;
   *pYbg = m_Ybc1;
   *pIxx = m_Ic1;
}

void Losses::SetCompositeProperties2(Float64 Ag, Float64 Ybg, Float64 Ixx)
{
   m_Ac2 = Ag;
   m_Ybc2 = Ybg;
   m_Ic2 = Ixx;
   m_IsDirty = true;
}

void Losses::GetCompositeProperties2(Float64* pAg, Float64* pYbg, Float64* pIxx) const
{
   *pAg = m_Ac2;
   *pYbg = m_Ybc2;
   *pIxx = m_Ic2;
}

void Losses::SetNetCompositeProperties(Float64 Ag, Float64 Ybg, Float64 Ixx)
{
   m_Acn = Ag;
   m_Ybcn = Ybg;
   m_Icn = Ixx;
   m_IsDirty = true;
}

void Losses::GetNetCompositeProperties(Float64* pAg, Float64* pYbg, Float64* pIxx) const
{
   *pAg = m_Acn;
   *pYbg = m_Ybcn;
   *pIxx = m_Icn;
}

const ElasticShortening& Losses::GetElasticShortening() const 
{ 
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_ElasticShortening; 
}


Float64 Losses::PermanentStrand_BeforeTransfer() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return PermanentStrand_RelaxationLossesBeforeTransfer();
}

Float64 Losses::PermanentStrand_AfterTransfer() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   // we want time-dependent losses only... don't include elastic shortening
   Float64 loss = PermanentStrand_RelaxationLossesBeforeTransfer();
   return loss;
}

Float64 Losses::PermanentStrand_AtLifting() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AfterTransfer();

   return loss;
}

Float64 Losses::PermanentStrand_AtShipping() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AtLifting() + PermanentStrand_TimeDependentLossesAtShipping();

   return loss;
}

Float64 Losses::PermanentStrand_AfterTemporaryStrandInstallation() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AfterTransfer();

   if ( m_TempStrandUsage == TempStrandUsage::PTBeforeShipping )
   {
      loss += PermanentStrand_TimeDependentLossesAtShipping();
   }

   return loss;
}

Float64 Losses::PermanentStrand_BeforeTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AtShipping();
   return loss;
}

Float64 Losses::PermanentStrand_AfterTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AtShipping();
   return loss;
}

Float64 Losses::PermanentStrand_AfterDeckPlacement() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AfterTransfer() + TimeDependentLossesBeforeDeck();

   return loss;
}

Float64 Losses::PermanentStrand_AfterSIDL() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AfterDeckPlacement();

   return loss;
}

Float64 Losses::PermanentStrand_Final() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AfterSIDL() + TimeDependentLossesAfterDeck();
   return loss;
}

Float64 Losses::TemporaryStrand_BeforeTransfer() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return TemporaryStrand_RelaxationLossesBeforeTransfer();
}

Float64 Losses::TemporaryStrand_AfterTransfer() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   // we want time-dependent losses only... don't include elastic shortening
   return TemporaryStrand_RelaxationLossesBeforeTransfer();
}

Float64 Losses::TemporaryStrand_AtLifting() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = 0;
   
   if ( m_TempStrandUsage == TempStrandUsage::Pretensioned )
   {
      loss = TemporaryStrand_AfterTransfer();
   }
   else if ( m_TempStrandUsage == TempStrandUsage::PTBeforeLifting || m_TempStrandUsage == TempStrandUsage::PTAfterLifting )
   {
      loss = TemporaryStrand_AfterTemporaryStrandInstallation();
   }

   return loss;
}


Float64 Losses::TemporaryStrand_AtShipping() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = 0;

   switch (m_TempStrandUsage)
   {
   case TempStrandUsage::Pretensioned:
      loss = TemporaryStrand_AtLifting() + TemporaryStrand_TimeDependentLossesAtShipping();
      break;

   case TempStrandUsage::PTBeforeShipping:
      loss = TemporaryStrand_AfterTemporaryStrandInstallation();
      break;

   case TempStrandUsage::PTBeforeLifting:
   case TempStrandUsage::PTAfterLifting:
      loss = TemporaryStrand_AfterTemporaryStrandInstallation() + TemporaryStrand_TimeDependentLossesAtShipping();
      break;

   default:
      CHECK(false); // is there a new type?
   }

   return loss;
}

Float64 Losses::TemporaryStrand_AfterTemporaryStrandInstallation() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = 0;
   if (m_TempStrandUsage == TempStrandUsage::Pretensioned )
   {
      loss = TemporaryStrand_AfterTransfer();
   }
   else
   {
      loss = m_dfpF + m_dfpA + m_dfptAvg;
   }

   return loss;
}

Float64 Losses::TemporaryStrand_BeforeTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = TemporaryStrand_AtShipping();
   return loss;
}

Float64 Losses::TemporaryStrand_AfterTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return 0;
}

Float64 Losses::TemporaryStrand_AfterDeckPlacement() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return 0;
}

Float64 Losses::TemporaryStrand_AfterSIDL() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return 0;
}

Float64 Losses::TemporaryStrand_Final() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return 0;
}

Float64 Losses::PermanentStrand_RelaxationLossesBeforeTransfer() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[PERMANENT_STRAND];
}

Float64 Losses::PermanentStrand_ElasticShorteningLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpES[PERMANENT_STRAND];
}

Float64 Losses::TemporaryStrand_RelaxationLossesBeforeTransfer() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[TEMPORARY_STRAND];
}

Float64 Losses::TemporaryStrand_ElasticShorteningLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpES[TEMPORARY_STRAND];
}

Float64 Losses::ElasticGainDueToDeckPlacement(bool bApplyElasticGainReduction) const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }

   return bApplyElasticGainReduction ? m_dfpED[WITH_ELASTIC_GAIN_REDUCTION] : m_dfpED[WITHOUT_ELASTIC_GAIN_REDUCTION];
}

Float64 Losses::ElasticGainDueToSIDL(bool bApplyElasticGainReduction) const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }

   return bApplyElasticGainReduction ? m_dfpSIDL[WITH_ELASTIC_GAIN_REDUCTION] : m_dfpSIDL[WITHOUT_ELASTIC_GAIN_REDUCTION];
}

Float64 Losses::ElasticGainDueToDeckShrinkage() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpSS;
}

Float64 Losses::ElasticGainDueToLiveLoad(Float64 Mllim) const
{
   Float64 dFcdLL = GetDeltaFcdLL(Mllim);
   Float64 dfLL = IsZero(m_ApsPerm) ? 0 : (m_Ep / m_Ec)*dFcdLL;
   return dfLL;
}

void Losses::GetDeckShrinkageEffects(Float64* pA,Float64* pM) const
{
   *pA = 0;
   *pM = 0;
}

Float64 Losses::FrictionLoss() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpF;
}

Float64 Losses::TotalFrictionLoss() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpFT;
}

Float64 Losses::AnchorSetLoss() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpA;
}

Float64 Losses::TotalAnchorSetLoss() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpAT;
}

Float64 Losses::AnchorSetZone() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_La;
}

Float64 Losses::GetFptMax() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_fptMax;
}

Float64 Losses::GetFptMin() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_fptMin;
}

Float64 Losses::GetFptAvg() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_fptAvg;
}

Float64 Losses::GetPptMax() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_PptMax;
}

Float64 Losses::GetPptMin() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_PptMin;
}

Float64 Losses::GetPptAvg() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_PptAvg;
}

Float64 Losses::GetDeltaFptAvg() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfptAvg;
}

Float64 Losses::GetFcgpt() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_Fcgpt;
}

Float64 Losses::GetDeltaFpt() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpt;
}

Float64 Losses::GetFptr() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_fptr;
}

Float64 Losses::GetDeltaFptr() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfptr;
}

Float64 Losses::GetPtr() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_Ptr;
}

Float64 Losses::GetFcgpp() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_Fcgpp;
}

Float64 Losses::GetDeltaFpp() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpp;
}

Float64 Losses::GetDeltaFcd1(bool bApplyElasticGainReduction) const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return bApplyElasticGainReduction ? m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION] : m_DeltaFcd1[WITHOUT_ELASTIC_GAIN_REDUCTION];
}

Float64 Losses::GetDeltaFcd2(bool bApplyElasticGainReduction) const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return bApplyElasticGainReduction ? m_DeltaFcd2[WITH_ELASTIC_GAIN_REDUCTION] : m_DeltaFcd2[WITHOUT_ELASTIC_GAIN_REDUCTION];
}

Float64 Losses::GetDeltaFcdLL(Float64 Mllim) const
{
   return Mllim * (m_Ybc2 - m_Ybg + m_epermFinal.Y()) / m_Ic2;
}

void Losses::UpdateLosses() const
{
   static bool bUpdating = false;

   if ( !bUpdating )
   {
      bUpdating = true;

      m_Madlg[WITH_ELASTIC_GAIN_REDUCTION] = 0;
      m_Madlg[WITHOUT_ELASTIC_GAIN_REDUCTION] = 0;
      for (const auto& [moment,elastic_gain_factor]: m_InputMadlg)
      {
         m_Madlg[WITH_ELASTIC_GAIN_REDUCTION] += moment * elastic_gain_factor; // moment*factor
         m_Madlg[WITHOUT_ELASTIC_GAIN_REDUCTION] += moment; // moment
      }

      m_Msidl1[WITH_ELASTIC_GAIN_REDUCTION] = 0;
      m_Msidl1[WITHOUT_ELASTIC_GAIN_REDUCTION] = 0;
      for (const auto& [moment, elastic_gain_factor] : m_InputMsidl1)
      {
         m_Msidl1[WITH_ELASTIC_GAIN_REDUCTION] += moment * elastic_gain_factor;
         m_Msidl1[WITHOUT_ELASTIC_GAIN_REDUCTION] += moment;
      }

      m_Msidl2[WITH_ELASTIC_GAIN_REDUCTION] = 0;
      m_Msidl2[WITHOUT_ELASTIC_GAIN_REDUCTION] = 0;
      for (const auto& [moment, elastic_gain_factor] : m_InputMsidl2)
      {
         m_Msidl2[WITH_ELASTIC_GAIN_REDUCTION] += moment * elastic_gain_factor;
         m_Msidl2[WITHOUT_ELASTIC_GAIN_REDUCTION] += moment;
      }

      try
      {
         if ( m_bValidateParameters )
         {
            ValidateParameters();
         }

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


void Losses::UpdateInitialLosses() const
{
   UpdateRelaxationBeforeTransfer();
   UpdateElasticShortening();
   UpdatePostTensionLosses();
}

void Losses::UpdateRelaxationBeforeTransfer() const
{
   // Losses from jacking to release
   // Using methodology from LRFD 2004... these losses were taken out of the 2005 spec
   // and no guidance was given for their computation...
   if ( !m_bIgnoreInitialRelaxation )
   {
      // requirement per 2004 LRFD 5.9.5.4.4b
      if ( !IsZero( m_FpjPerm ) && !(0.5*m_FpuPerm < m_FpjPerm) )
      {
         WBFL_LRFD_THROW(XPsLosses,fpjOutOfRange);
      }

      if ( !IsZero( m_FpjTemp ) && !(0.5*m_FpuPerm < m_FpjTemp) )
      {
         WBFL_LRFD_THROW(XPsLosses,fpjOutOfRange);
      }

      Float64 t_days = WBFL::Units::ConvertFromSysUnits( m_ti, WBFL::Units::Measure::Day );
      Float64 Aperm = (m_TypePerm == WBFL::Materials::PsStrand::Type::LowRelaxation ? 40. : 10. );
      Float64 Atemp = (m_TypeTemp == WBFL::Materials::PsStrand::Type::LowRelaxation ? 40. : 10. );

      if ( m_TempStrandUsage == TempStrandUsage::Pretensioned )
      {
         if ( t_days*24. < 1 || IsZero(m_FpjTemp))
         {
            m_dfpR0[TEMPORARY_STRAND] = 0; // log10(<1) = < 0... t_days < 1/24 is less than one hour
         }
         else
         {
            m_dfpR0[TEMPORARY_STRAND] = (log10(24.*t_days)/Atemp) * (m_FpjTemp/m_FpyTemp - 0.55) * m_FpjTemp;
         }
      }
      else
      {
         m_dfpR0[TEMPORARY_STRAND] = 0; // no initial relaxation if not pre-tensioned
      }


      if ( t_days*24. < 1 || IsZero(m_FpjPerm))
      {
         m_dfpR0[PERMANENT_STRAND] = 0; // log10(<1) = < 0... t_days < 1/24 is less than one hour
      }
      else
      {
         m_dfpR0[PERMANENT_STRAND] = (log10(24.*t_days)/Aperm) * (m_FpjPerm/m_FpyPerm - 0.55) * m_FpjPerm;
      }
   }
   else
   {
      // AASHTO
      m_dfpR0[TEMPORARY_STRAND] = 0;
      m_dfpR0[PERMANENT_STRAND] = 0;
   }

   // See PCI Guidelines for the use of epoxy-coated strand
   // PCI Journal July-August 1993. Section 5.3
   if ( m_CoatingPerm != WBFL::Materials::PsStrand::Coating::None )
   {
      m_dfpR0[PERMANENT_STRAND] *= 2;
   }
   if ( m_CoatingTemp != WBFL::Materials::PsStrand::Coating::None )
   {
      m_dfpR0[TEMPORARY_STRAND] *= 2;
   }
}

void Losses::UpdateElasticShortening() const
{
   // Elastic shortening
   WBFL::LRFD::ElasticShortening es(m_FpjPerm,
                        (m_TempStrandUsage == TempStrandUsage::Pretensioned ? m_FpjTemp : 0),
                        m_dfpR0[PERMANENT_STRAND], // perm
                        m_dfpR0[TEMPORARY_STRAND], // temp
                        m_ApsPerm,
                        (m_TempStrandUsage == TempStrandUsage::Pretensioned ? m_ApsTemp : 0),
                        m_SectionProperties == SectionPropertiesType::Gross ? true : false,
                        m_Ag,
                        m_Ixx,
                        m_Iyy,
                        m_Ixy,
                        m_epermRelease,
                        m_etemp,
                        m_Mdlg,
                        1.0,
                        m_Eci,
                        m_Ep,
                        WBFL::LRFD::ElasticShortening::FcgpComputationMethod::Iterative);

   m_ElasticShortening = es;

   m_dfpES[TEMPORARY_STRAND] = m_ElasticShortening.TemporaryStrand_ElasticShorteningLosses();
   m_dfpES[PERMANENT_STRAND] = m_ElasticShortening.PermanentStrand_ElasticShorteningLosses();
}

void Losses::UpdatePostTensionLosses() const
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
   if ( m_TempStrandUsage != TempStrandUsage::Pretensioned && !IsZero(m_FpjTemp*m_ApsTemp))
   {
      // compute loss and stress profile of one post-tensioned strand
      // friction loss
      Float64 K, x, lg;
      if ( BDSManager::GetUnits() == BDSManager::Units::SI )
      {
         K = WBFL::Units::ConvertFromSysUnits(m_WobbleCoefficient,WBFL::Units::Measure::PerMillimeter);
         x = WBFL::Units::ConvertFromSysUnits(m_X,WBFL::Units::Measure::Millimeter);
         lg = WBFL::Units::ConvertFromSysUnits(m_Lg,WBFL::Units::Measure::Millimeter);
      }
      else
      {
         K = WBFL::Units::ConvertFromSysUnits(m_WobbleCoefficient,WBFL::Units::Measure::PerFeet);
         x = WBFL::Units::ConvertFromSysUnits(m_X,WBFL::Units::Measure::Feet);
         lg = WBFL::Units::ConvertFromSysUnits(m_Lg,WBFL::Units::Measure::Feet);
      }

      m_dfpF  = m_FpjTemp*(1 - exp(-(K*x  + m_AngleChange*m_FrictionCoefficient)));
      m_dfpFT = m_FpjTemp*(1 - exp(-(K*lg + m_AngleChange*m_FrictionCoefficient)));

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
         m_dfpA = m_dfpAT - m_dfpFT*m_X/m_Lg;
         m_dfpF = 0;
      }
      else
      {
         m_dfpA = 0;
      }

      // force in one strand
      m_PptMax = m_aps*m_fptMax;

      // compressive stress due to 1 strand at level of prestressing
      //m_Fcgpt = m_PptMax/m_Ag + m_PptMax*m_etemp.Y()*m_etemp.Y()/m_Ixx;
      Float64 mx = m_PptMax*m_etemp.Y();
      Float64 my = 0;
      Float64 D = m_Ixx*m_Iyy - m_Ixy*m_Ixy;
      m_Fcgpt = m_PptMax / m_Ag + (my*m_Ixx + mx*m_Ixy)*-m_etemp.X() / D - (mx*m_Iyy + my*m_Ixy)*-m_etemp.Y() / D;

      // effect on the stress in the previously jacked strands is
      if ( m_TempStrandUsage == TempStrandUsage::PTBeforeShipping )
      {
         m_dfpt = m_Fcgpt*m_Ep/m_Ec;
      }
      else
      {
         m_dfpt = m_Fcgpt*m_Ep/m_Eci;
      }

      Float64 N = m_ApsTemp/m_aps;
      m_dfptAvg = (m_dfpt + (N-1)*m_dfpt)/2;

      // stress in the last pt strand to be jacked
      m_fptMin = m_fptMax - (N-1)*m_dfpt;
      m_PptMin = m_aps*m_fptMin;

      // average stress in all pt strands
      m_fptAvg = (m_fptMax + m_fptMin)/2;

      // average pt force
      m_PptAvg = m_ApsTemp*m_fptAvg;

      // compute effect of pt on the permanent strands
      //m_Fcgpp = m_PptAvg/m_Ag + m_PptAvg*m_etemp.Y()*m_epermFinal.Y()/m_Ixx;
      mx = m_PptAvg*m_etemp.Y();
      m_Fcgpp = m_PptAvg / m_Ag + (my*m_Ixx + mx*m_Ixy)*-m_epermFinal.X() / D - (mx*m_Iyy + my*m_Ixy)*-m_epermFinal.Y() / D;

      if ( m_TempStrandUsage == TempStrandUsage::PTBeforeShipping )
      {
         m_dfpp  = m_Fcgpp*(m_Ep/m_Ec);
      }
      else
      {
         m_dfpp  = m_Fcgpp*(m_Ep/m_Eci);
      }
   }
}

void Losses::UpdateTemporaryStrandRemovalEffect() const
{
   // Change in permanent strand stress due to removal of temporary strand
   Float64 f;
   Float64 fpj = GetFpjTemporary();

   if ( IsZero(fpj) )
   {
      f = 0;
   }
   else if ( m_TempStrandUsage == TempStrandUsage::Pretensioned )
   {
      f = fpj - m_dfpR0[TEMPORARY_STRAND]
              - TemporaryStrand_TimeDependentLossesAtShipping()
              - m_dfpp - m_dfpES[TEMPORARY_STRAND];
   }
   else if ( m_TempStrandUsage == TempStrandUsage::PTBeforeShipping )
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

   m_Ptr   = m_ApsTemp*f; // force in temporary strands immediately before removal

   //m_fptr  = -m_Ptr/m_Ag - m_Ptr*m_epermFinal.Y()*m_etemp.Y()/m_Ixx; // concrete stress change due to removal
   Float64 mx = m_Ptr*m_etemp.Y();
   Float64 my = 0;
   Float64 D = m_Ixx*m_Iyy - m_Ixy*m_Ixy;
   m_fptr = m_Ptr / m_Ag + (my*m_Ixx + mx*m_Ixy)*-m_epermFinal.X() / D - (mx*m_Iyy + my*m_Ixy)*-m_epermFinal.Y() / D;
   m_fptr *= -1; // because we are removing the strands, the stresses are opposite


   if ( 0.0 < m_ApsPerm )
   {
      m_dfptr = m_fptr*m_Ep/m_Ec; // change in prestress due to removal
   }
   else
   {
      m_dfptr = 0.0; // no permanent strands, so the effect is zero
   }
}
