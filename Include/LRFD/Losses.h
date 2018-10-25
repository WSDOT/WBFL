///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#include <Lrfd\LrfdExp.h>
#include <Lrfd\VersionMgrListener.h>
#include <Lrfd\PsStrand.h>
#include <Lrfd\ElasticShortening.h>


class LRFDCLASS lrfdLosses : public lrfdVersionMgrListener
{
public:
   enum TempStrandUsage { tsPretensioned, tsPTBeforeLifting, tsPTAfterLifting, tsPTBeforeShipping };

   lrfdLosses();

   lrfdLosses(Float64 x, // location along girder where losses are computed
                         Float64 Lg,    // girder length
                         matPsStrand::Grade gr,
                         matPsStrand::Type type,
                         Float64 fpjPerm, // fpj permanent strands
                         Float64 fpjTemp, // fpj of temporary strands
                         Float64 ApsPerm,  // area of permanent strand
                         Float64 ApsTemp,  // area of TTS 
                         Float64 aps,      // area of one strand
                         Float64 eperm, // eccentricty of permanent ps strands with respect to CG of girder
                         Float64 etemp, // eccentricty of temporary strands with respect to CG of girder
                         TempStrandUsage usage,
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

                         Float64 Ag,    // Area of girder
                         Float64 Ig,    // Moment of inertia of girder
                         Float64 Ybg,   // Centroid of girder measured from bottom
                         Float64 Ac,    // Area of the composite girder and deck
                         Float64 Ic,    // Moment of inertia of composite
                         Float64 Ybc,   // Centroid of composite measured from bottom

                         Float64 rh, // relative humidity

                         Float64 ti,   // Time until prestress transfer
                         bool bIgnoreInitialRelaxation
                         );

   lrfdLosses(const lrfdLosses& rOther);
   lrfdLosses& operator=(const lrfdLosses& rOther);

   //------------------------------------------------------------------------
   // Called by lrfdVersion when ever the code version or unit system changes
   virtual void OnUpdate();

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

   Float64 GetFpy() const; // yield strength of strand 
   Float64 GetEp() const; // modulus of elasticity of strand

   //------------------------------------------------------------------------
   // Strand Area

   // temporary strand usage
   void SetTempStrandUsage(TempStrandUsage usage);
   TempStrandUsage GetTempStrandUsage() const;

   // strand type
   void SetStrandType(matPsStrand::Type type);
   matPsStrand::Type GetStrandType() const;
   
   // strand grade
   void SetStrandGrade(matPsStrand::Grade gr);
   matPsStrand::Grade GetStrandGrade() const;

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

   // eccentricty of permanent strands on non-composite section
   void SetEccPermanent(Float64 epc);
   Float64 GetEccPermanent() const;

   // eccentricty of temporary strands on non-composite section
   void SetEccTemporary(Float64 epc);
   Float64 GetEccTemporary() const;

   // eccenticity of permanent strand on composite section (computed value)
   Float64 GetEccpc() const;

   // eccentricty of all strands on non-composite section (computed value)
   Float64 GetEccpg() const; 

   //------------------------------------------------------------------------
   // Section Properties

   // Area of non-composite section
   void SetAg(Float64 Ag);
   Float64 GetAg() const;

   // Moment of inertia of non-composite section
   void SetIg(Float64 Ig);
   Float64 GetIg() const;

   // Centroid, from bottom of non-composite section
   void SetYbg(Float64 Ybg);
   Float64 GetYbg() const;

   // Area of composite section girder and deck
   void SetAc(Float64 Ac);
   Float64 GetAc() const;

   // Moment of inertia of composite section
   void SetIc(Float64 Ic);
   Float64 GetIc() const;

   // Centroid, from bottom of composite section
   void SetYbc(Float64 Ybc);
   Float64 GetYbc() const;

   //------------------------------------------------------------------------
   // Moments due to external loads

   // moment due toself weight of girder
   void SetGdrMoment(Float64 Mdlg);
   Float64 GetGdrMoment() const;

   // addition moment on non-composite girder
   void SetAddlGdrMoment(Float64 Madlg);
   Float64 GetAddlGdrMoment() const;

   // moment due to superimposed dead loads
   void SetSidlMoment(Float64 Msidl);
   Float64 GetSidlMoment() const;

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

   virtual Float64 PermanentStrand_BeforeTransfer() const;
   virtual Float64 PermanentStrand_AfterTransfer() const;
   virtual Float64 PermanentStrand_AtLifting() const;
   virtual Float64 PermanentStrand_AtShipping() const;
   virtual Float64 PermanentStrand_AfterTemporaryStrandInstallation() const;
   virtual Float64 PermanentStrand_BeforeTemporaryStrandRemoval() const;
   virtual Float64 PermanentStrand_AfterTemporaryStrandRemoval() const;
   virtual Float64 PermanentStrand_AfterDeckPlacement() const;
   virtual Float64 PermanentStrand_Final() const;

   virtual Float64 TemporaryStrand_BeforeTransfer() const;
   virtual Float64 TemporaryStrand_AfterTransfer() const;
   virtual Float64 TemporaryStrand_AtLifting() const;
   virtual Float64 TemporaryStrand_AtShipping() const;
   virtual Float64 TemporaryStrand_AfterTemporaryStrandInstallation() const;
   virtual Float64 TemporaryStrand_BeforeTemporaryStrandRemoval() const;
   virtual Float64 TemporaryStrand_AfterTemporaryStrandRemoval() const;
   virtual Float64 TemporaryStrand_AfterDeckPlacement() const;
   virtual Float64 TemporaryStrand_Final() const;

   //------------------------------------------------------------------------
   const lrfdElasticShortening& ElasticShortening() const;

   virtual Float64 PermanentStrand_RelaxationLossesBeforeTransfer() const;
   virtual Float64 PermanentStrand_ElasticShorteningLosses() const;

   virtual Float64 TemporaryStrand_RelaxationLossesBeforeTransfer() const;
   virtual Float64 TemporaryStrand_ElasticShorteningLosses() const;

   Float64 ElasticGainDueToDeckPlacement() const;


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
   // Change in stress in permanent strands due to post-tensioning strands
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
   Float64 GetDeltaFcd1() const;

protected:
   mutable bool m_IsDirty;
   void Init();

   void UpdateLosses() const;
   void UpdateInitialLosses() const;
   void UpdateRelaxationBeforeTransfer() const;
   void UpdateElasticShortening() const;
   void UpdatePostTensionLosses() const;

   virtual void ValidateParameters() const = 0;
   virtual void UpdateLongTermLosses() const = 0;
   virtual void UpdateHaulingLosses() const = 0;
   
   void UpdateTemporaryStrandRemovalEffect() const;

   void MakeAssignment( const lrfdLosses& rOther );
   void MakeCopy( const lrfdLosses& rOther );

   // Input Parameters
   Float64 m_Eci;
   Float64 m_Ec;
   Float64 m_Ecd;   // Modulus of elasticy of composite deck
   Float64 m_Fc; // 28 day strength (girder)
   Float64 m_Fci; // release strength (girder)
   Float64 m_FcSlab; // 28 day strength (slab)
   matPsStrand::Type m_Type;
   matPsStrand::Grade m_Grade;
   Float64 m_eperm; // CG of permanent prestress with respect to centroid of noncomposite section
   Float64 m_etemp; // CG of temporary prestress 
   Float64 m_ApsPerm; // Area of permanent strands
   Float64 m_ApsTemp; // Area of temporary strands
   Float64 m_aps;     // Area of one strand
   Float64 m_X;  // location along girder
   Float64 m_Lg; // length of girder
   Float64 m_Ep;
   Float64 m_Fpu;
   Float64 m_FpjPerm; // jacking force of permanent strands at transfer
   Float64 m_FpjTemp; // jacking force of temporary strands
   Float64 m_Fpy;
   TempStrandUsage m_TempStrandUsage;
   Float64 m_AnchorSet; // anchor set
   Float64 m_WobbleCoefficient;
   Float64 m_FrictionCoefficient;
   Float64 m_AngleChange;
   Float64 m_Mdlg;  // Dead load moment of girder
   Float64 m_Madlg; // Additional dead load moment on girder section
   Float64 m_Msidl; // Superimposed dead loads
   Float64 m_ti; // initial time

   Float64 m_Ag;    // Area of the girder
   Float64 m_Ig;    // Moment of inertia of the girder
   Float64 m_Ybg;   // Centroid of girder measured from bottom
   Float64 m_Ac;    // Area of the composite girder and deck
   Float64 m_Ic;    // Moment of inertia of composite
   Float64 m_Ybc;   // Centroid of composite measured from bottom

   Float64 m_H;  // relative humidity

   bool m_bIgnoreInitialRelaxation; // if true, dfpR0 is not computed

   mutable lrfdElasticShortening m_ElasticShortening;

   // array index is 0=temporary strand, 1 = permanent strand
   mutable Float64 m_dfpR0[2]; // initial relaxation
   mutable Float64 m_dfpES[2]; // elastic shrinkage

   mutable Float64 m_dfpED; // elastic gain due to deck placement

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

   mutable Float64 m_DeltaFcd1; // change in stress at level of permanent strand due to deck placement

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

inline void lrfdLosses::SetStrandType(matPsStrand::Type type) { m_Type = type; m_IsDirty = true; }
inline matPsStrand::Type lrfdLosses::GetStrandType() const { return m_Type; }
inline void lrfdLosses::SetStrandGrade(matPsStrand::Grade gr) { m_Grade = gr; m_IsDirty = true; }
inline matPsStrand::Grade lrfdLosses::GetStrandGrade() const { return m_Grade; }

inline void lrfdLosses::SetAg(Float64 Ag) { m_Ag = Ag; m_IsDirty = true; }
inline Float64 lrfdLosses::GetAg() const { return m_Ag; }
inline void lrfdLosses::SetIg(Float64 Ig) { m_Ig = Ig; m_IsDirty = true; }
inline Float64 lrfdLosses::GetIg() const { return m_Ig; }
inline void lrfdLosses::SetYbg(Float64 Ybg) { m_Ybg = Ybg; m_IsDirty = true; }
inline Float64 lrfdLosses::GetYbg() const { return m_Ybg; }
inline void lrfdLosses::SetAc(Float64 Ac) { m_Ac = Ac; m_IsDirty = true; }
inline Float64 lrfdLosses::GetAc() const { return m_Ac; }
inline void lrfdLosses::SetIc(Float64 Ic) { m_Ic = Ic; m_IsDirty = true; }
inline Float64 lrfdLosses::GetIc() const { return m_Ic; }
inline void lrfdLosses::SetYbc(Float64 Ybc) { m_Ybc = Ybc; m_IsDirty = true; }
inline Float64 lrfdLosses::GetYbc() const { return m_Ybc; }

inline void lrfdLosses::SetGdrMoment(Float64 Mdlg) { m_Mdlg = Mdlg; m_IsDirty = true; }
inline Float64 lrfdLosses::GetGdrMoment() const { return m_Mdlg; }
inline void lrfdLosses::SetAddlGdrMoment(Float64 Madlg) { m_Madlg = Madlg; m_IsDirty = true; }
inline Float64 lrfdLosses::GetAddlGdrMoment() const { return m_Madlg; }
inline void lrfdLosses::SetSidlMoment(Float64 Msidl) { m_Msidl = Msidl; m_IsDirty = true; }
inline Float64 lrfdLosses::GetSidlMoment() const { return m_Msidl; }

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