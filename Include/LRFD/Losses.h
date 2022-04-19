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

#ifndef INCLUDED_LOSSES_H_
#define INCLUDED_LOSSES_H_
#pragma once

#include <LRFD\LrfdExp.h>
#include <LRFD\VersionMgrListener.h>
#include <LRFD\PsStrand.h>
#include <LRFD\ElasticShortening.h>
#include <LRFD\CreepCoefficient.h>

#include <array>


#define TEMPORARY_STRAND 0
#define PERMANENT_STRAND 1

#define SERVICE_I_LIVELOAD 0
#define SERVICE_III_LIVELOAD 1
#define FATIGUE_LIVELOAD 2

#define WITH_ELASTIC_GAIN_REDUCTION 0
#define WITHOUT_ELASTIC_GAIN_REDUCTION 1

class LRFDCLASS lrfdLosses : public lrfdVersionMgrListener
{
public:
   enum TempStrandUsage { tsPretensioned, tsPTBeforeLifting, tsPTAfterLifting, tsPTBeforeShipping };
   enum SectionPropertiesType { sptGross, sptTransformed };

   lrfdLosses();

   lrfdLosses(Float64 x, // location along girder where losses are computed
              Float64 Lg,    // girder length
              SectionPropertiesType sectionProperties, // type of section properties used
              matPsStrand::Grade gradePerm, // strand grade
              matPsStrand::Type typePerm, // strand type
              matPsStrand::Coating coatingPerm, // strand coating (none, epoxy)
              matPsStrand::Grade gradeTemp, // strand grade
              matPsStrand::Type typeTemp, // strand type
              matPsStrand::Coating coatingTemp, // strand coating (none, epoxy)
              Float64 fpjPerm, // fpj permanent strands
              Float64 fpjTemp, // fpj of temporary strands
              Float64 ApsPerm,  // area of permanent strand
              Float64 ApsTemp,  // area of TTS 
              Float64 aps,      // area of one strand
              const WBFL::Geometry::Point2d& epermRelease, // eccentricty of permanent ps strands with respect to CG of girder at release
              const WBFL::Geometry::Point2d& epermFinal, // eccentricty of permanent ps strands with respect to CG of girder at final
              const WBFL::Geometry::Point2d& etemp, // eccentricty of temporary strands with respect to CG of girder
              TempStrandUsage usage, // temporary strand usage type
              Float64 anchorSet, // anchor set for post-tensioned temporary top strands
              Float64 wobble,    // wobble coefficient for post-tensioned temporary top strands
              Float64 friction, // friction coefficient for post-tensioned temporary top strands
              Float64 angleChange, // angle change for post-tensioned temporary top strands

              Float64 Fc,   // 28 day strength of girder concrete
              Float64 Fci,  // Release strength
              Float64 FcSlab,   // 28 day strength for slab
              Float64 Ec,   // Modulus of elasticity of girder
              Float64 Eci,  // Modulus of elasticity of girder at transfer
              Float64 Ecd,  // Modulus of elasticity of deck

              Float64 Mdlg,  // Dead load moment of girder only
              const std::vector<std::pair<Float64, Float64>>& Madlg,  // Additional dead load on girder section (first value is moment, second is elastic gain reduction factor)
              const std::vector<std::pair<Float64, Float64>>& Msidl1, // Superimposed dead loads, stage 1
              const std::vector<std::pair<Float64, Float64>>& Msidl2, // Superimposed dead loads, stage 2

              // Transform/Gross properties
              Float64 Ag,    // Area of girder
              Float64 Ixx,    // Moment of inertia of girder
              Float64 Iyy,
              Float64 Ixy,
              Float64 Ybg,   // Centroid of girder measured from bottom
              Float64 Ac1,   // area of composite girder, stage 1
              Float64 Ic1,   // moment of inertia of composite, stage 1
              Float64 Ybc1,  // Centroid of composite measured from bottom, stage 1
              Float64 Ac2,   // area of composite girder, stage 2
              Float64 Ic2,   // moment of inertia of composite, stage 2
              Float64 Ybc2,  // Centroid of composite measured from bottom, stage 2

              // Net properties (use same values as gross for gross property analysis)
              Float64 An,    // Area of girder
              Float64 Inxx,    // Moment of inertia of girder
              Float64 Inyy,
              Float64 Inxy,
              Float64 Ybn,   // Centroid of girder measured from bottom
              Float64 Acn,    // Area of the composite girder and deck
              Float64 Icn,    // Moment of inertia of composite
              Float64 Ybcn,   // Centroid of composite measured from bottom

              Float64 rh, // relative humidity

              Float64 ti,   // Time until prestress transfer
              bool bIgnoreInitialRelaxation, // if true, initialize relaxation is not computed
              bool bValidateLosses // if true, ValidateLossParameters() is called and lrfdXPsLosses exceptions will be thrown if the loss parameters are not valid
   );

   //------------------------------------------------------------------------
   // Called by lrfdVersion when ever the code version or unit system changes
   virtual void OnUpdate() override;

   //------------------------------------------------------------------------
   // Input Parameters
   //------------------------------------------------------------------------

   //------------------------------------------------------------------------
   // Concrete
   void SetFc(Float64 fc);
   Float64 GetFc() const;

   void SetFcSlab(Float64 fc);
   Float64 GetFcSlab() const;

   void SetFci(Float64 fci);
   Float64 GetFci() const;

   void SetEc(Float64 Ec);
   Float64 GetEc() const;

   void SetEci(Float64 Eci);
   Float64 GetEci() const;

   void SetEcd(Float64 Ecd);
   Float64 GetEcd() const;

   //------------------------------------------------------------------------
   // Strand Material
   void SetFpjPermanent(Float64 fpj);
   Float64 GetFpjPermanent() const;

   void SetFpjTemporary(Float64 fpj);
   Float64 GetFpjTemporary() const;

   Float64 GetFpyPermanent() const; // yield strength of strand 
   Float64 GetFpyTemporary() const; // yield strength of strand 
   Float64 GetEp() const; // modulus of elasticity of strand

   //------------------------------------------------------------------------
   // Strand Area

   // temporary strand usage
   void SetTempStrandUsage(TempStrandUsage usage);
   TempStrandUsage GetTempStrandUsage() const;

   // strand type
   void SetPermanentStrandType(matPsStrand::Type type);
   matPsStrand::Type GetPermanentStrandType() const;
   void SetTemporaryStrandType(matPsStrand::Type type);
   matPsStrand::Type GetTemporaryStrandType() const;
   
   // strand grade
   void SetPermanentStrandGrade(matPsStrand::Grade gr);
   matPsStrand::Grade GetPermanentStrandGrade() const;
   void SetTemporaryStrandGrade(matPsStrand::Grade gr);
   matPsStrand::Grade GetTemporaryStrandGrade() const;
   
   // strand coating
   void SetPermanentStrandCoating(matPsStrand::Coating coating);
   matPsStrand::Coating GetPermanentStrandCoating() const;
   void SetTemporaryStrandCoating(matPsStrand::Coating coating);
   matPsStrand::Coating GetTemporaryStrandCoating() const;

   // area of permanent prestressing
   void SetApsPermanent(Float64 Aps);
   Float64 GetApsPermanent() const;

   // area of temporary strand
   void SetApsTemporary(Float64 Aps);
   Float64 GetApsTemporary() const;

   // area of a single strand
   void SetStrandArea(Float64 aps);
   Float64 GetStrandArea() const;

   //------------------------------------------------------------------------
   // Strand Eccentricity

   // eccentricty of permanent strands on non-composite section at release
   void SetEccPermanentRelease(const WBFL::Geometry::Point2d& epc);
   const WBFL::Geometry::Point2d& GetEccPermanentRelease() const;

   // eccentricty of permanent strands on non-composite section at final
   void SetEccPermanentFinal(const WBFL::Geometry::Point2d& epc);
   const WBFL::Geometry::Point2d& GetEccPermanentFinal() const;

   // eccentricty of temporary strands on non-composite section
   void SetEccTemporary(const WBFL::Geometry::Point2d& epc);
   const WBFL::Geometry::Point2d& GetEccTemporary() const;

   // eccenticity of permanent strand on composite section (computed value)
   Float64 GetEccpc() const;

   // eccentricty of all strands on non-composite section (computed value)
   WBFL::Geometry::Point2d GetEccpgRelease() const; 
   WBFL::Geometry::Point2d GetEccpgFinal() const; 

   //------------------------------------------------------------------------
   // Section Properties
   void SetSectionPropertiesType(lrfdLosses::SectionPropertiesType props);
   SectionPropertiesType GetSectionPropertiesType() const;

   // Noncomposite properties... could be gross or transformed
   void SetNoncompositeProperties(Float64 Ag, Float64 Ybg, Float64 Ixx, Float64 Iyy, Float64 Ixy);
   void GetNoncompositeProperties(Float64* pAg, Float64* pYbg, Float64* pIxx, Float64* pIyy, Float64* pIxy) const;

   // Net non-composite properites (if using gross section analysis, makes these equal to the noncomposite properties)
   void SetNetNoncompositeProperties(Float64 Ag, Float64 Ybg, Float64 Ixx, Float64 Iyy, Float64 Ixy);
   void GetNetNoncompositeProperties(Float64* pAg, Float64* pYbg, Float64* pIxx, Float64* pIyy, Float64* pIxy) const;

   // Composite properties... could be gross or transformed
   void SetCompositeProperties1(Float64 Ag, Float64 Ybg, Float64 Ixx);
   void GetCompositeProperties1(Float64* pAg, Float64* pYbg, Float64* pIxx) const;
   void SetCompositeProperties2(Float64 Ag, Float64 Ybg, Float64 Ixx);
   void GetCompositeProperties2(Float64* pAg, Float64* pYbg, Float64* pIxx) const;

   // Net composite properites (if using gross section analysis, makes these equal to the noncomposite properties)
   void SetNetCompositeProperties(Float64 Ag, Float64 Ybg, Float64 Ixx);
   void GetNetCompositeProperties(Float64* pAg, Float64* pYbg, Float64* pIxx) const;

   //------------------------------------------------------------------------
   // Moments due to external loads

   // moment due toself weight of girder
   void SetGdrMoment(Float64 Mdlg);
   Float64 GetGdrMoment() const;

   // addition moment on non-composite girder
   void SetAddlGdrMoment(const std::vector<std::pair<Float64, Float64>>& Madlg);
   Float64 GetAddlGdrMoment() const;
   const std::vector<std::pair<Float64, Float64>>& GetAddlGdrMoment2() const;

   // moment due to superimposed dead loads
   void SetSidlMoment1(const std::vector<std::pair<Float64, Float64>>& Msidl);
   Float64 GetSidlMoment1() const;
   const std::vector<std::pair<Float64, Float64>>& GetSidlMoment1_2() const;
   void SetSidlMoment2(const std::vector<std::pair<Float64, Float64>>& Msidl);
   Float64 GetSidlMoment2() const;
   const std::vector<std::pair<Float64, Float64>>& GetSidlMoment2_2() const;

   //------------------------------------------------------------------------
   // Post-tension related parameters

   // girder length
   void SetGirderLength(Float64 lg);
   Float64 GetGirderLength() const;

   // location from left end of girder where losses are computed
   void SetLocation(Float64 x);
   Float64 GetLocation() const;

   // anchor set
   void SetAnchorSet(Float64 lg);
   Float64 GetAnchorSet() const;

   void SetWobbleFrictionCoefficient(Float64 K);
   Float64 GetWobbleFrictionCoefficient() const;

   void SetCoefficientOfFriction(Float64 u);
   Float64 GetCoefficientOfFriction() const;

   void SetTendonAngleChange(Float64 a);
   Float64 GetTendonAngleChange() const;

   //------------------------------------------------------------------------
   void SetRelHumidity(Float64 H);
   Float64 GetRelHumidity() const;

   void SetInitialAge(Float64 ti);
   Float64 GetInitialAge() const;

   void IgnoreInitialRelaxation(bool bIgnore);
   bool IgnoreInitialRelaxation() const;

   //------------------------------------------------------------------------
   // These methods return only the time-dependent loss
   virtual Float64 PermanentStrand_BeforeTransfer() const;
   virtual Float64 PermanentStrand_AfterTransfer() const;
   virtual Float64 PermanentStrand_AtLifting() const;
   virtual Float64 PermanentStrand_AtShipping() const;
   virtual Float64 PermanentStrand_AfterTemporaryStrandInstallation() const;
   virtual Float64 PermanentStrand_BeforeTemporaryStrandRemoval() const;
   virtual Float64 PermanentStrand_AfterTemporaryStrandRemoval() const;
   virtual Float64 PermanentStrand_AfterDeckPlacement() const;
   virtual Float64 PermanentStrand_AfterSIDL() const;
   virtual Float64 PermanentStrand_Final() const;

   virtual Float64 TemporaryStrand_BeforeTransfer() const;
   virtual Float64 TemporaryStrand_AfterTransfer() const;
   virtual Float64 TemporaryStrand_AtLifting() const;
   virtual Float64 TemporaryStrand_AtShipping() const;
   virtual Float64 TemporaryStrand_AfterTemporaryStrandInstallation() const;
   virtual Float64 TemporaryStrand_BeforeTemporaryStrandRemoval() const;
   virtual Float64 TemporaryStrand_AfterTemporaryStrandRemoval() const;
   virtual Float64 TemporaryStrand_AfterDeckPlacement() const;
   virtual Float64 TemporaryStrand_AfterSIDL() const;
   virtual Float64 TemporaryStrand_Final() const;

   //------------------------------------------------------------------------
   const lrfdElasticShortening& ElasticShortening() const;

   virtual Float64 PermanentStrand_RelaxationLossesBeforeTransfer() const;
   virtual Float64 PermanentStrand_ElasticShorteningLosses() const;

   virtual Float64 TemporaryStrand_RelaxationLossesBeforeTransfer() const;
   virtual Float64 TemporaryStrand_ElasticShorteningLosses() const;

   Float64 ElasticGainDueToDeckPlacement(bool bApplyElasticGainReduction) const;
   Float64 ElasticGainDueToSIDL(bool bApplyElasticGainReduction) const;
   Float64 ElasticGainDueToDeckShrinkage() const;
   Float64 ElasticGainDueToLiveLoad(Float64 Mllim) const;

   virtual void GetDeckShrinkageEffects(Float64* pA,Float64* pM) const;


   virtual Float64 TemporaryStrand_TimeDependentLossesAtShipping() const = 0;
   virtual Float64 PermanentStrand_TimeDependentLossesAtShipping() const = 0;
   virtual Float64 TimeDependentLossesBeforeDeck() const = 0;
   virtual Float64 TimeDependentLossesAfterDeck() const = 0;
   virtual Float64 TimeDependentLosses() const = 0;

   //------------------------------------------------------------------------
   // loss in post-tensioned temporary strand
   Float64 FrictionLoss() const;
   Float64 TotalFrictionLoss() const;
   Float64 AnchorSetLoss() const;
   Float64 TotalAnchorSetLoss() const;
   Float64 AnchorSetZone() const; // length of the anchor set zone
   //------------------------------------------------------------------------
   // Max, min, and average stress in post-tensioned temporary strands
   Float64 GetFptMax() const;
   Float64 GetFptMin() const;
   Float64 GetFptAvg() const;

   //------------------------------------------------------------------------
   // Max and min force in ONE in post-tensioned temporary strands
   Float64 GetPptMax() const;
   Float64 GetPptMin() const;

   //------------------------------------------------------------------------
   // Average force in all PT strands
   Float64 GetPptAvg() const;

   //------------------------------------------------------------------------
   // Average effect of pt sequence on PT strands
   Float64 GetDeltaFptAvg() const;

   //------------------------------------------------------------------------
   // Stress in concrete at level of TTS due to post-tensioning ONE strand
   Float64 GetFcgpt() const;

   //------------------------------------------------------------------------
   // Change in stress in concrete at level of permanent strands due to post-tensioning strands
   Float64 GetFcgpp() const;

   //------------------------------------------------------------------------
   // Change in stress in permanent strands due to post-tensioning temporary strands strands
   Float64 GetDeltaFpp() const;

   //------------------------------------------------------------------------
   // The change in stress in a PT strand caused by jacking the next strand
   Float64 GetDeltaFpt() const;

   //------------------------------------------------------------------------
   // The change in stress in concrete at level of permanent strands due to removal of temporary strand
   Float64 GetFptr() const;

   //------------------------------------------------------------------------
   // The change in stress in permanent strands due to removal of temporary strand
   Float64 GetDeltaFptr() const;

   //------------------------------------------------------------------------
   // Returns the force in the temporary strand immediately before removal
   Float64 GetPtr() const;

   //------------------------------------------------------------------------
   // Change in stress at level of permanent strand due to deck placement
   Float64 GetDeltaFcd1(bool bApplyElasticGainReduction) const;

   //------------------------------------------------------------------------
   // Change in stress at level of permanent strand due to superimposed dead loads
   Float64 GetDeltaFcd2(bool bApplyElasticGainReduction) const;

   //------------------------------------------------------------------------
   // Change in stress at level of permanent strand due to live load
   Float64 GetDeltaFcdLL(Float64 Mllim) const;

protected:
   bool m_bValidateParameters;
   mutable bool m_IsDirty;
   void Init();

   void UpdateLosses() const;
   virtual void UpdateInitialLosses() const;
   virtual void UpdateRelaxationBeforeTransfer() const;
   virtual void UpdateElasticShortening() const;
   virtual void UpdatePostTensionLosses() const;

   // Called by the framework to validate the parameters in this object
   // Throw lrfdXPsLosses-based exceptions of there are invalid parameters
   virtual void ValidateParameters() const = 0;

   virtual void UpdateLongTermLosses() const = 0;
   virtual void UpdateHaulingLosses() const = 0;
   
   void UpdateTemporaryStrandRemovalEffect() const;

   // Input Parameters
   SectionPropertiesType m_SectionProperties;
   Float64 m_Eci;
   Float64 m_Ec;
   Float64 m_Ecd;   // Modulus of elasticy of composite deck
   Float64 m_Fc; // 28 day strength (girder)
   Float64 m_Fci; // release strength (girder)
   Float64 m_FcSlab; // 28 day strength (slab)
   matPsStrand::Type m_TypePerm;
   matPsStrand::Grade m_GradePerm;
   matPsStrand::Coating m_CoatingPerm;
   matPsStrand::Type m_TypeTemp;
   matPsStrand::Grade m_GradeTemp;
   matPsStrand::Coating m_CoatingTemp;
   WBFL::Geometry::Point2d m_epermRelease; // CG of permanent prestress with respect to centroid of noncomposite section
   WBFL::Geometry::Point2d m_epermFinal; // CG of permanent prestress with respect to centroid of composite section
   WBFL::Geometry::Point2d m_etemp; // CG of temporary prestress 
   Float64 m_ApsPerm; // Area of permanent strands
   Float64 m_ApsTemp; // Area of temporary strands
   Float64 m_aps;     // Area of one strand
   Float64 m_X;  // location along girder
   Float64 m_Lg; // length of girder
   Float64 m_Ep;
   Float64 m_FpuPerm;
   Float64 m_FpuTemp;
   Float64 m_FpjPerm; // jacking force of permanent strands at transfer
   Float64 m_FpjTemp; // jacking force of temporary strands
   Float64 m_FpyPerm;
   Float64 m_FpyTemp;
   TempStrandUsage m_TempStrandUsage;
   Float64 m_AnchorSet; // anchor set
   Float64 m_WobbleCoefficient;
   Float64 m_FrictionCoefficient;
   Float64 m_AngleChange;
   Float64 m_Mdlg;  // Dead load moment of girder
   mutable std::array<Float64, 2> m_Madlg; // Summation of additional dead load moment on girder section (with and without elastic gain reduction factor)
   mutable std::array<Float64, 2> m_Msidl1;// Superimposed dead loads
   mutable std::array<Float64, 2> m_Msidl2;// Superimposed dead loads
   std::vector<std::pair<Float64,Float64>> m_InputMadlg; // Additional dead load moment on girder section (moment, elastic gain reduction factor)
   std::vector<std::pair<Float64, Float64>> m_InputMsidl1; // Superimposed dead loads
   std::vector<std::pair<Float64, Float64>> m_InputMsidl2; // Superimposed dead loads
   Float64 m_ti; // initial time

   // Transformed/Gross Properties
   Float64 m_Ag;    // Area of the girder
   Float64 m_Ixx;    // Moment of inertia of the girder
   Float64 m_Iyy;
   Float64 m_Ixy;
   Float64 m_Ybg;   // Centroid of girder measured from bottom
   Float64 m_Ac1;    // Area of the composite girder and deck
   Float64 m_Ic1;    // Moment of inertia of composite
   Float64 m_Ybc1;   // Centroid of composite measured from bottom
   Float64 m_Ac2;    // Area of the composite girder and deck
   Float64 m_Ic2;    // Moment of inertia of composite
   Float64 m_Ybc2;   // Centroid of composite measured from bottom

   // Net Properties
   Float64 m_An;    // Area of the girder
   Float64 m_Ixxn;    // Moment of inertia of the girder
   Float64 m_Iyyn;
   Float64 m_Ixyn;
   Float64 m_Ybn;   // Centroid of girder measured from bottom
   Float64 m_Acn;   // Area of the composite girder and deck
   Float64 m_Icn;   // Moment of inertia of composite
   Float64 m_Ybcn;  // Centroid of composite measured from bottom

   Float64 m_H;  // relative humidity

   bool m_bIgnoreInitialRelaxation; // if true, dfpR0 is not computed

   mutable lrfdElasticShortening m_ElasticShortening;

   // array index is 0=temporary strand, 1 = permanent strand
   mutable std::array<Float64, 2> m_dfpR0; // initial relaxation
   mutable std::array<Float64, 2> m_dfpES; // elastic shrinkage

   // array index is 0=without elastic gain reduction, 1=with elastic gain reduction
   mutable std::array<Float64, 2> m_dfpED; // elastic gain due to deck placement
   mutable std::array<Float64, 2> m_dfpSIDL; // elastic gain due to superimposed dead loads
   mutable Float64 m_dfpSS; // elastic gain due to deck shrinkage

   // post tension losses
   mutable Float64 m_dfpp; // change in stress in perm strand due to pt
   mutable Float64 m_fpL;  // stress in pt at live end
   mutable Float64 m_fpD;  // stress in pt at dead end
   mutable Float64 m_fpMax;// max stress in pt strand
   mutable Float64 m_fptMax; // max pt stress at x (stress from 1st strand being jacked)
   mutable Float64 m_fptMin; // min pt stress at x (stress from last strand being jacked)
   mutable Float64 m_fptAvg; // average pt stress at x
   mutable Float64 m_Fcgpt; // stress in concrete at level of pt due to one strand
   mutable Float64 m_Fcgpp; // change in concrete at level of permanent strands due to pt tts
   mutable Float64 m_dfpt; // effect of one strand on another
   mutable Float64 m_dfptAvg; // average effect of pt strand jacking sequence
   mutable Float64 m_PptMax; //max force for one pt strand
   mutable Float64 m_PptMin; //min force for one pt strand
   mutable Float64 m_PptAvg; // average PT force

   mutable Float64 m_fptr;  // stress in concrete at level of perm strand due to removal of temp strands
   mutable Float64 m_dfptr; // change in stress in perm strands due to removal of temp strands
   mutable Float64 m_Ptr;   // force in temp strand at time of removal

   mutable std::array<Float64, 2> m_DeltaFcd1; // change in stress at level of permanent strand due to deck placement
   mutable std::array<Float64, 2> m_DeltaFcd2; // change in stress at level of permanent strand due to superimposed dead loads

   mutable Float64 m_dfpF;  // friction loss 
   mutable Float64 m_dfpFT; // total friction loss 
   mutable Float64 m_dfpA;  // anchor set loss
   mutable Float64 m_dfpAT; // total anchor set loss
   mutable Float64 m_La; // length of anchor set zone

};

inline void lrfdLosses::SetFpjPermanent(Float64 fpj) { m_FpjPerm = fpj; m_IsDirty = true; }
inline Float64 lrfdLosses::GetFpjPermanent() const { return m_FpjPerm; }
inline void lrfdLosses::SetFpjTemporary(Float64 fpj) { m_FpjTemp = fpj; m_IsDirty = true; }
inline Float64 lrfdLosses::GetFpjTemporary() const { return m_FpjTemp; }

inline void lrfdLosses::SetFc(Float64 fc) { m_Fc = fc; m_IsDirty = true; }
inline Float64 lrfdLosses::GetFc() const { return m_Fc; }
inline void lrfdLosses::SetFcSlab(Float64 fc) { m_FcSlab = fc; m_IsDirty = true; }
inline Float64 lrfdLosses::GetFcSlab() const { return m_FcSlab; }
inline void lrfdLosses::SetEc(Float64 Ec) { m_Ec = Ec; m_IsDirty = true; }
inline Float64 lrfdLosses::GetEc() const { return m_Ec; }
inline void lrfdLosses::SetEci(Float64 Eci) { m_Eci = Eci; m_IsDirty = true; }
inline Float64 lrfdLosses::GetEci() const { return m_Eci; }
inline void lrfdLosses::SetEcd(Float64 Ecd) { m_Ecd = Ecd; m_IsDirty = true; }
inline Float64 lrfdLosses::GetEcd() const { return m_Ecd; }
inline void lrfdLosses::SetFci(Float64 fci) { m_Fci = fci; m_IsDirty = true; }
inline Float64 lrfdLosses::GetFci() const { return m_Fci; }

inline void lrfdLosses::SetTempStrandUsage(lrfdLosses::TempStrandUsage usage) { m_TempStrandUsage = usage; m_IsDirty = true; }
inline lrfdLosses::TempStrandUsage lrfdLosses::GetTempStrandUsage() const { return m_TempStrandUsage; }

inline void lrfdLosses::SetPermanentStrandType(matPsStrand::Type type) { m_TypePerm = type; m_IsDirty = true; }
inline matPsStrand::Type lrfdLosses::GetPermanentStrandType() const { return m_TypePerm; }
inline void lrfdLosses::SetTemporaryStrandType(matPsStrand::Type type) { m_TypeTemp = type; m_IsDirty = true; }
inline matPsStrand::Type lrfdLosses::GetTemporaryStrandType() const { return m_TypeTemp; }

inline void lrfdLosses::SetPermanentStrandGrade(matPsStrand::Grade gr) { m_GradePerm = gr; m_IsDirty = true; }
inline matPsStrand::Grade lrfdLosses::GetPermanentStrandGrade() const { return m_GradePerm; }
inline void lrfdLosses::SetTemporaryStrandGrade(matPsStrand::Grade gr) { m_GradeTemp = gr; m_IsDirty = true; }
inline matPsStrand::Grade lrfdLosses::GetTemporaryStrandGrade() const { return m_GradeTemp; }

inline void lrfdLosses::SetPermanentStrandCoating(matPsStrand::Coating coating) { m_CoatingPerm = coating; m_IsDirty = true; }
inline matPsStrand::Coating lrfdLosses::GetPermanentStrandCoating() const { return m_CoatingPerm; }
inline void lrfdLosses::SetTemporaryStrandCoating(matPsStrand::Coating coating) { m_CoatingTemp = coating; m_IsDirty = true; }
inline matPsStrand::Coating lrfdLosses::GetTemporaryStrandCoating() const { return m_CoatingTemp; }

inline void lrfdLosses::SetSectionPropertiesType(lrfdLosses::SectionPropertiesType props) { m_SectionProperties = props; m_IsDirty = true; }
inline lrfdLosses::SectionPropertiesType lrfdLosses::GetSectionPropertiesType() const { return m_SectionProperties; }

inline void lrfdLosses::SetGdrMoment(Float64 Mdlg) { m_Mdlg = Mdlg; m_IsDirty = true; }
inline Float64 lrfdLosses::GetGdrMoment() const { return m_Mdlg; }
inline void lrfdLosses::SetAddlGdrMoment(const std::vector<std::pair<Float64, Float64>>& Madlg) { m_InputMadlg = Madlg; m_IsDirty = true; }
inline Float64 lrfdLosses::GetAddlGdrMoment() const { if (m_IsDirty) UpdateLosses();  return m_Madlg[WITH_ELASTIC_GAIN_REDUCTION]; }
inline const std::vector<std::pair<Float64, Float64>>& lrfdLosses::GetAddlGdrMoment2() const { return m_InputMadlg; }

inline void lrfdLosses::SetSidlMoment1(const std::vector<std::pair<Float64, Float64>>& Msidl) { m_InputMsidl1 = Msidl; m_IsDirty = true; }
inline Float64 lrfdLosses::GetSidlMoment1() const { if (m_IsDirty) UpdateLosses(); return m_Msidl1[WITH_ELASTIC_GAIN_REDUCTION]; }
inline const std::vector<std::pair<Float64, Float64>>& lrfdLosses::GetSidlMoment1_2() const { return m_InputMsidl1; }

inline void lrfdLosses::SetSidlMoment2(const std::vector<std::pair<Float64, Float64>>& Msidl) { m_InputMsidl2 = Msidl; m_IsDirty = true; }
inline Float64 lrfdLosses::GetSidlMoment2() const { if (m_IsDirty) UpdateLosses();  return m_Msidl2[WITH_ELASTIC_GAIN_REDUCTION]; }
inline const std::vector<std::pair<Float64, Float64>>& lrfdLosses::GetSidlMoment2_2() const { return m_InputMsidl2; }

inline void lrfdLosses::SetGirderLength(Float64 lg) { m_Lg = lg; m_IsDirty = true; }
inline Float64 lrfdLosses::GetGirderLength() const {  return m_Lg; }
inline void lrfdLosses::SetLocation(Float64 x) { m_X = x; m_IsDirty = true; }
inline Float64 lrfdLosses::GetLocation() const { return m_X; }
inline void lrfdLosses::SetAnchorSet(Float64 as) { m_AnchorSet = as; m_IsDirty = true; }
inline Float64 lrfdLosses::GetAnchorSet() const { return m_AnchorSet; }
inline void lrfdLosses::SetWobbleFrictionCoefficient(Float64 K) { m_WobbleCoefficient = K; m_IsDirty = true; }
inline Float64 lrfdLosses::GetWobbleFrictionCoefficient() const { return m_WobbleCoefficient; }
inline void lrfdLosses::SetCoefficientOfFriction(Float64 u) { m_FrictionCoefficient = u; m_IsDirty = true; }
inline Float64 lrfdLosses::GetCoefficientOfFriction() const { return m_FrictionCoefficient; }
inline void lrfdLosses::SetTendonAngleChange(Float64 a) { m_AngleChange = a; m_IsDirty = true; }
inline Float64 lrfdLosses::GetTendonAngleChange() const {return m_AngleChange;}

inline void lrfdLosses::SetRelHumidity(Float64 H) { m_H = H; m_IsDirty = true; }
inline Float64 lrfdLosses::GetRelHumidity() const { return m_H; }

inline void lrfdLosses::SetInitialAge(Float64 ti) { m_ti = ti; m_IsDirty = true; }
inline Float64 lrfdLosses::GetInitialAge() const { return m_ti; }

inline void lrfdLosses::IgnoreInitialRelaxation(bool bIgnore) { m_bIgnoreInitialRelaxation = bIgnore; m_IsDirty = true; }
inline bool lrfdLosses::IgnoreInitialRelaxation() const { return m_bIgnoreInitialRelaxation; }


#endif // INCLUDED_LOSSES_H_